#include <windows.h>
#include <gdiplus.h>
#include <ObjIdl.h>
#include <memory>
#include "main.h"

std::unique_ptr<Gdiplus::Bitmap> convolver();

VOID process(HDC hdc)
{
    Gdiplus::Graphics window(hdc);
    Gdiplus::Bitmap *out = convolver().release();
    Gdiplus::CachedBitmap cachedBitmap(out, &window);
    window.DrawCachedBitmap(&cachedBitmap, 10, 10);
}

std::unique_ptr<Gdiplus::Bitmap> convolver()
{
    int kernel[3][3] = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};
    int bias = 0;
    Gdiplus::Bitmap in(L"images/image1.jpg");
    UINT inSize[2] = {in.GetWidth(), in.GetHeight()};
    std::unique_ptr<Gdiplus::Bitmap> out(new Gdiplus::Bitmap(inSize[0], inSize[1]));

    for (int y = -1; y < (int)inSize[1] - 1; y++)
        for (int x = -1; x < (int)inSize[0] - 1; x++)
        {
            int convolved = 0;
            for (int b = 0; b < 3; b++)
                for (int a = 0; a < 3; a++)
                {
                    Gdiplus::Color inColor(0, 0, 0);
                    int xy[2] = {x + a, y + b};
                    if (xy[0] >= 0 && xy[1] >= 0 && xy[0] < inSize[0] && xy[1] < inSize[1])
                    {
                        in.GetPixel(xy[0], xy[1], &inColor);
                    }
                    convolved += (inColor.GetR() * kernel[a][b]) +
                                 (inColor.GetG() * kernel[a][b]) +
                                 (inColor.GetB() * kernel[a][b]) +
                                 bias;
                }
            Gdiplus::Color outColor(convolved, convolved, convolved);
            out->SetPixel(x + 1, y + 1, outColor);
        }
    return (out);
}