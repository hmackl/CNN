#include <iostream>
#include <windows.h>
#include <gdiplus.h>
#include <objidl.h>
#include "main.h"
using namespace std;
using namespace Gdiplus;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
{
   HWND hWnd;
   MSG msg;
   WNDCLASS wndClass;
   GdiplusStartupInput gdiplusStartupInput;
   ULONG_PTR gdiplusToken;

   GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

   wndClass.style = CS_HREDRAW | CS_VREDRAW;
   wndClass.lpfnWndProc = WndProc;
   wndClass.cbClsExtra = 0;
   wndClass.cbWndExtra = 0;
   wndClass.hInstance = hInstance;
   wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
   wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
   wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
   wndClass.lpszMenuName = NULL;
   wndClass.lpszClassName = TEXT("CNN");

   RegisterClass(&wndClass);

   hWnd = CreateWindow(
       TEXT("CNN"),
       TEXT("CNN"),
       WS_OVERLAPPEDWINDOW,
       CW_USEDEFAULT,
       CW_USEDEFAULT,
       CW_USEDEFAULT,
       CW_USEDEFAULT,
       NULL,
       NULL,
       hInstance,
       NULL);

   ShowWindow(hWnd, iCmdShow);
   UpdateWindow(hWnd);

   while (GetMessage(&msg, NULL, 0, 0))
   {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
   }

   GdiplusShutdown(gdiplusToken);
   return msg.wParam;
} // WinMain

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
   HDC hdc;
   PAINTSTRUCT ps;

   switch (message)
   {
   case WM_PAINT:
      hdc = BeginPaint(hWnd, &ps);
      process(hdc);
      EndPaint(hWnd, &ps);
      return 0;
   case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
   default:
      return DefWindowProc(hWnd, message, wParam, lParam);
   }
}