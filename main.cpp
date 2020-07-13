#include <windows.h>
#include <gdiplus.h>
#include <ObjIdl.h>
#include <math.h>
#include "main.h"

using namespace std;

BYTE *openImage(BYTE *in, UINT size[2], int outSize);

void process(HDC hdc)
{
    Gdiplus::Graphics window(hdc);
    Gdiplus::Bitmap in(L"images/image2.jpg");
    UINT inSize[2] = {in.GetWidth(), in.GetHeight()};
    Gdiplus::Rect inRect(0, 0, inSize[0], inSize[1]);
    Gdiplus::BitmapData inData;
    in.LockBits(&inRect, Gdiplus::ImageLockModeRead, in.GetPixelFormat(), &inData);
    BYTE *inPtr = (BYTE *)inData.Scan0;
    in.UnlockBits(&inData);
    int outSize = 448;
    BYTE *bits = openImage(inPtr, inSize, outSize);
    int channels = 3;
    int kernel[27] = {-1, -1, -1, 0, 1, -1, 0, 1, 1,
                      1, 0, 0, 1, -1, -1, 1, 0, -1,
                      0, 1, 1, 0, 1, 0, 1, -1, 1};
    int stride = 1;
    Convolver convolver;
    convolver.setPtr(bits);
    convolver.setSize(outSize);
    bits = convolver.convolve(kernel, channels, stride);
    Gdiplus::Bitmap out(outSize, outSize, outSize * 3, PixelFormat24bppRGB, bits); 
    Gdiplus::CachedBitmap cachedBitmap(&out, &window);
    window.DrawCachedBitmap(&cachedBitmap, 10, 10);
}

BYTE *openImage(BYTE *inData, UINT size[2], int outSize)
{
    BYTE *outData = new BYTE[outSize * outSize * 3];
    int mSize = size[0] > size[1] ? size[0] : size[1];
    float sFactor = (mSize - 1) / (float)outSize;
    int ix = (size[0] / sFactor), iy = (size[1] / sFactor);
    int px = ix < outSize ? ix : outSize, py = iy < outSize ? iy : outSize;
    for (int y = 0; y <= py; y++)
        for (int x = 0; x <= px; x++)
            for (int s = 0; s < 3; s++)
            {
                int outPixel = (size[0] * ceil(y * sFactor)) + ceil(x * sFactor);
                outData[((y * outSize) + x) * 3 + s] = inData[outPixel * 3 + s];
            }
    return outData;
}
