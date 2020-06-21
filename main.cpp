#include <windows.h>
#include <gdiplus.h>
#include <ObjIdl.h>
#include <memory>
#include "main.h"

VOID process(HDC hdc) 
{
    Gdiplus::Graphics window(hdc);
    Gdiplus::Bitmap in(L"images/image1.jpg");
    Gdiplus::CachedBitmap cachedBitmap(&in, &window);
    window.DrawCachedBitmap(&cachedBitmap, 10, 10);
}