/**
 * Copyright 2019 Angel Castillo <angel.castillob@protonmail.com>
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 **/

/* INCLUDES ******************************************************************/

#ifdef HAVE_CONFIG_H
#include "../config.h"
#endif

#include <Display/Display.h>

#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <iostream>
#include <sstream>
#include <string>

/* USINGS ********************************************************************/

/* DEFINES  ******************************************************************/

/* STATIC VARIABLES **********************************************************/

static HINSTANCE g_moduleInstance = GetModuleHandle(0);

/* STATIC FUNCTIONS **********************************************************/

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

VOID OnPaint(HDC hdc)
{
  // create memory DC and memory bitmap where we shall do our drawing
  HDC memDC = CreateCompatibleDC(hdc);

  // now we can create bitmap where we shall do our drawing
  HBITMAP bmp = CreateCompatibleBitmap(hdc, 500, 500);
  HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, bmp);

  /* DRAWING *****************************************************************/
  static float counter = 10.0f;
  Gdiplus::Graphics graphics(memDC);
  Gdiplus::Pen pen(Gdiplus::Color(255, 0, 0, 255));

  RECT rect = {0, 0, 500, 500};
  FillRect(memDC, &rect, (HBRUSH)(COLOR_WINDOW + 1));
  
  graphics.DrawLine(&pen, 0, 0, 200, 100);

  Gdiplus::SolidBrush brush(Gdiplus::Color(255, 0, 0, 255));
  Gdiplus::FontFamily fontFamily(L"Times New Roman");
  Gdiplus::Font font(&fontFamily, 24, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
  Gdiplus::PointF pointF(counter, 20.0f);

  counter += 0.1f;
  graphics.DrawString(L"Hello World!", -1, &font, pointF, &brush);
  std::cout << "Updated" << std::endl;
  
  /* END RAWING **************************************************************/
	
  BitBlt(hdc, 0, 0, 500, 500, memDC, 0, 0, SRCCOPY);
  
  // all done, now we need to cleanup
  SelectObject(memDC, oldBmp); // select back original bitmap
  DeleteObject(bmp); // delete bitmap since it is no longer required
  DeleteDC(memDC);   // delete memory DC since it is no longer required
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  HDC hdc;
  PAINTSTRUCT ps;

  switch (message)
  {
  case WM_PAINT:
    hdc = BeginPaint(hWnd, &ps);
    OnPaint(hdc);
    EndPaint(hWnd, &ps);
    return 0;
  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;
  case WM_ERASEBKGND:
    return 1;

  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
  }
}

/* CLASS IMPLEMENTATION ******************************************************/

namespace Bio
{

Display::Display(IFrameRenderer *frameRenderer, IInputHandler *inputHandler, DisplayParams params)
    : m_frameRenderer(frameRenderer), m_inputHandler(inputHandler), m_params(params), m_height(params.height), m_width(params.width), m_isRunning(false)
{
}

Display::~Display()
{
}

void Display::start()
{
  m_isRunning = true;
  HWND hWnd;
  MSG msg;
  WNDCLASS wndClass;
  Gdiplus::GdiplusStartupInput gdiplusStartupInput;
  ULONG_PTR gdiplusToken;

  // Initialize GDI+.
  Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

  wndClass.style = CS_HREDRAW | CS_VREDRAW;
  wndClass.lpfnWndProc = WndProc;
  wndClass.cbClsExtra = 0;
  wndClass.cbWndExtra = 0;
  wndClass.hInstance = g_moduleInstance;
  wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
  wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
  wndClass.lpszMenuName = NULL;
  wndClass.lpszClassName = TEXT("GettingStarted");

  RegisterClass(&wndClass);

  hWnd = CreateWindow(
      TEXT("GettingStarted"),  // window class name
      TEXT("Getting Started"), // window caption
      WS_OVERLAPPEDWINDOW,     // window style
      CW_USEDEFAULT,           // initial x position
      CW_USEDEFAULT,           // initial y position
      m_params.width,          // initial x size
      m_params.height,         // initial y size
      NULL,                    // parent window handle
      NULL,                    // window menu handle
      g_moduleInstance,        // program instance handle
      NULL);

  // remove title bar
  /*
    LONG lStyle = GetWindowLong(hWnd, GWL_STYLE);
    lStyle &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU);
    SetWindowLong(hWnd, GWL_STYLE, lStyle);
    ShowScrollBar(hWnd, SB_VERT, FALSE);*/

  // creation parameters
  //1 normal: Activates and displays a window. If the window is minimized or maximized, the system restores it to its original size and position. An application should specify this flag when displaying the window for the first time.

  // 2 minimized: Activates the window and displays it as a minimized window.
  // 3 maximized: Activates the window and displays it as a maximized window.
  ShowWindow(hWnd, 4);
  UpdateWindow(hWnd);

  while (GetMessage(&msg, NULL, 0, 0) && m_isRunning)
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
    RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
  }

  Gdiplus::GdiplusShutdown(gdiplusToken);
}

void Display::stop()
{
  m_isRunning = true;
}
} // namespace Bio
