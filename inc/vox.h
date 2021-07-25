#ifndef VOX_H
#define VOX_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
#define extern "C" {
#endif

typedef struct {
    int     step_idx;
    int16_t last;
} VOX;

void vox_init(VOX *state);
void vox_encode(VOX *state, int16_t *in, uint8_t *out, size_t len);
void vox_decode(VOX *state, uint8_t *in, int16_t *out, size_t len);

uint8_t vox_encode_step(VOX *state, int16_t sample);
int16_t vox_decode_step(VOX *state, uint8_t code);

#ifdef __cplusplus
}
#endif

#endif // VOX_H
