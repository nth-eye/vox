#include "vox.h"

static const int16_t step_size[49] = { 
    16, 17, 19, 21, 23, 25, 28, 31, 34, 37, 41, 45, 
    50, 55, 60, 66, 73, 80, 88, 97, 107, 118, 130, 143, 
    157, 173, 190, 209, 230, 253, 279, 307, 337, 371, 408, 449, 
    494, 544, 598, 658, 724, 796, 876, 963, 1060, 1166, 1282, 1411, 1552,
};

static const int step_adjust[8] = { 
    -1, -1, -1, -1, 2, 4, 6, 8,
};

static void next_step_idx(VOX *state, uint8_t sample)
{
    state->step_idx += step_adjust[sample & 0x7];

    if (state->step_idx < 0) 
        state->step_idx = 0;
    if (state->step_idx > 48) 
        state->step_idx = 48;
}

uint8_t vox_encode_step(VOX *state, int16_t sample)
{
    int16_t ss      = step_size[state->step_idx];
    int16_t diff    = sample - state->last;
    uint8_t code    = 0x0;

    if (diff < 0) {
        diff = -diff;
        code = 0x8;
    }

    if (diff >= ss) {
        diff -= ss;
        code |= 0x4;
    }

    if (diff >= ss >> 1) {
        diff -= ss >> 1;
        code |= 0x2;
    }

    if (diff >= ss >> 2)
        code |= 0x1;
    
    state->last = vox_decode_step(state, code);

    return code;
}

int16_t vox_decode_step(VOX *state, uint8_t code)
{
    int16_t ss      = step_size[state->step_idx];
    int16_t diff    = 
        ( ss        * ((code >> 2) & 0x1)) + 
        ((ss >> 1)  * ((code >> 1) & 0x1)) + 
        ((ss >> 2)  * ( code       & 0x1)) + 
        ( ss >> 3);

    if (code & 0x8)
        diff = -diff;

    int16_t sample  = state->last + diff;

    if (sample > 2047)
        sample = 2047;
    else 
    if (sample < -2048)
        sample = -2048;

    next_step_idx(state, code);

    return sample;
}

void vox_init(VOX *state)
{
    state->step_idx = 0;
    state->last     = 0;
}

void vox_encode(VOX *state, int16_t *in, uint8_t *out, size_t len)
{
    size_t even_len = len & ~1;

    for (size_t i = 0; i < even_len; i += 2) {

        uint8_t msb = vox_encode_step(state, in[i]     >> 4);
        uint8_t lsb = vox_encode_step(state, in[i + 1] >> 4);

        *out++ = (msb << 4) | lsb;
    }
}

void vox_decode(VOX *state, uint8_t *in, int16_t *out, size_t len)
{
    for (size_t i = 0; i < len; ++i) {
        *out++ = vox_decode_step(state, in[i] >> 4);
        *out++ = vox_decode_step(state, in[i] & 0xf);
    }
}
