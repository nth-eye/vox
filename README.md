# vox

Dialogic ADPCM codec in C.

## How to use

```c
VOX vox;

uint8_t encoded[512]; // must be at least sizeof(samples) / 4
int16_t samples[1024];

// ...fill samples...

vox_init(&vox);
vox_encode(&vox, samples, encoded, sizeof(samples));

```

Example with reading from file can be found in main.c

## TODO

**_Nothing_**
