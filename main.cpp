#include <stdio.h>
#include "vox.h"

int main() 
{
    auto in = fopen("../../audio_2.raw", "rb");
    auto out = fopen("../../audio_2.vox", "w+b");

    if (!in || !out) {
        puts("couldn't open files");
        if (in)
            fclose(in);
        if (out)
            fclose(out);
        return 1;
    }

    Vox vox;
    int16_t samples[2];
    uint8_t byte;
    size_t cnt;
    size_t total = 0;

    vox.init();

    do {
        cnt = fread(samples, 2, 2, in);
        vox.encode(samples, &byte, 2);
        fwrite(&byte, 1, 1, out);
        ++total;
    } while (cnt == 2);

    printf("total 16-bit samples processed: %lu \n", total * 2);

    fclose(in);
    fclose(out);
}
