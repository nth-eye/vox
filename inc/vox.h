#ifndef VOX_H
#define VOX_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int     step_idx;
    int16_t last;
} VOX;

/**
 * @brief Reset codec state to default.
 * 
 * @param state Codec context
 */
void vox_init(VOX *state);

/**
 * @brief Encode 16-bit PCM samples to Dialogic ADPCM. Codec has 
 * 4x compression, so each 16-bit sample will be encoded to nibble
 * (4 bits). Two consecutive samples will be encoded as byte with 
 * first sample being most significant nibble. 
 * 
 * @param state Codec context
 * @param in Input samples
 * @param out Encoded output bytes
 * @param len Input length in samples, not in bytes
 */
void vox_encode(VOX *state, int16_t *in, uint8_t *out, size_t len);

/**
 * @brief Decode dialogic ADPCM to 16-bit raw PCM. Each byte has 2 
 * encoded samples and will be decoded as two int16_t's.
 * 
 * @param state Codec context
 * @param in Encoded input bytes
 * @param out Decoded output samples
 * @param len Input length in bytes, not in samples
 */
void vox_decode(VOX *state, uint8_t *in, int16_t *out, size_t len);

/**
 * @brief Single encoding step.
 * 
 * @param state Codec context
 * @param sample Sample to encode
 * @return Encoded nibble (4 bits)
 */
uint8_t vox_encode_step(VOX *state, int16_t sample);

/**
 * @brief Single decoding step.
 * 
 * @param state Codec context
 * @param code Encoded byte, contains 2 samples
 * @return Decoded PCM sample
 */
int16_t vox_decode_step(VOX *state, uint8_t code);

#ifdef __cplusplus
}
#endif

#endif
