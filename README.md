# vox

Header-only dialogic ADPCM codec in C++.

## How to use

```c++
Vox vox;

uint8_t encoded[512]; // must be at least sizeof(samples) / 4
int16_t samples[1024];

// fill samples...

vox.init();
vox.encode(samples, encoded, sizeof(samples) / sizeof(int16_t));
```

Example with reading from file can be found in main.cpp
