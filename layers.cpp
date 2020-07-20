#include "main.h"

void Convolver::convolve(int *kernel, int channels, int stride)
{
    //BYTE *out = new BYTE[size * size * 3];

    for (int y = -1; y < (int)size - 1; y += stride)
        for (int x = -1; x < (int)size - 1; x += stride)
        {
            int convolved = 0;
            for (int b = 0; b < 3; b++)
                for (int a = 0; a < 3; a++)
                {
                    int xy[2] = {x + a, y + b};
                    if (xy[0] >= 0 && xy[1] >= 0 && xy[0] < size && xy[1] < size)
                        for (int p = 0; p < channels; p++) //Extract subpixels in RGB order
                        {
                            int subPixel = inPtr[((size * xy[1] * channels) + (2 - p) + (xy[0] * channels))];
                            convolved += (subPixel * kernel[p + 3 * (b + 3 * a)]);
                        }
                }
            convolved = (((0) > (convolved)) ? (0) : (convolved));
            inPtr[(size * (y + 1) + (x + 1)) * 3] = convolved;
        }
}
