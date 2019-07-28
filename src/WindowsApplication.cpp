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
#include "config.h"
#endif

#include <Bio/Application.h>

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

/**
 * On paint event handler.
 * 
 * Paints the windows content.
 * 
 * @param hdc 
 **/ 
VOID OnPaint(HDC hdc)
{
  int width = GetSystemMetrics(SM_CXSCREEN);
  int height = GetSystemMetrics(SM_CYSCREEN);

  // create memory DC and memory bitmap where we shall do our drawing
  HDC memDC = CreateCompatibleDC(hdc);

  // now we can create bitmap where we shall do our drawing
  HBITMAP bmp = CreateCompatibleBitmap(hdc, width, height);
  HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, bmp);

  /* DRAWING *****************************************************************/
  static float counter = 10.0f;
  Gdiplus::Graphics graphics(memDC);
  Gdiplus::Pen pen(Gdiplus::Color(255, 0, 0, 255));

  RECT rect = {0, 0, width, height};
  FillRect(memDC, &rect, (HBRUSH)(COLOR_WINDOW + 1));
  
  graphics.DrawLine(&pen, 0, 0, 200, 100);

  Gdiplus::SolidBrush brush(Gdiplus::Color(255, 0, 0, 255));
  Gdiplus::FontFamily fontFamily(L"Times New Roman");
  Gdiplus::Font font(&fontFamily, 24, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
  Gdiplus::PointF pointF(counter, 20.0f);

  counter += 0.9f;
  graphics.DrawString(L"Hello World!", -1, &font, pointF, &brush);
  std::cout << "Updated" << std::endl;
  
  /* END RAWING **************************************************************/
	
  BitBlt(hdc, 0, 0, width, height, memDC, 0, 0, SRCCOPY);
  
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

/**
 * Sets the window to full screen.
 * 
 * @param hWnd The window handle.
 **/
static void
setFullScreen(HWND hWnd)
{
  LONG lStyle = GetWindowLong( hWnd, GWL_STYLE );
  lStyle &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZE | WS_MAXIMIZE | WS_SYSMENU);
  SetWindowLong(hWnd, GWL_STYLE, lStyle);
  SetWindowPos(hWnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SWP_FRAMECHANGED | SWP_SHOWWINDOW);
}
  
/* CLASS IMPLEMENTATION ******************************************************/

namespace Bio
{

Application::Application(DisplayParams params)
: m_params(params), m_height(params.height), m_width(params.width), m_context(NULL)
{
}

Application::~Application()
{
    Gdiplus::GdiplusShutdown(reinterpret_cast<ULONG_PTR>(m_context));
}

bool
Application::initialize()
{
  HWND hwnd;
  WNDCLASS wndClass;
  Gdiplus::GdiplusStartupInput gdiplusStartupInput;

  // Initialize GDI+.
  Gdiplus::GdiplusStartup(reinterpret_cast<ULONG_PTR*>(&m_context), &gdiplusStartupInput, NULL);

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

  hwnd = CreateWindow(
      TEXT("GettingStarted"),  // window class name
      TEXT("Getting Started"), // window caption
      WS_OVERLAPPEDWINDOW,     // window style
      m_params.x < 0 ? CW_USEDEFAULT : m_params.x,           // initial y position
      m_params.y < 0 ? CW_USEDEFAULT : m_params.y,          // initial x size
      m_params.width,         // initial y size
      m_params.height,         // initial y size
      NULL,                    // parent window handle
      NULL,                    // window menu handle
      g_moduleInstance,        // program instance handle
      NULL);

  if (m_params.isMaximized)
    setFullScreen(hwnd);

  ShowWindow(hwnd, 4);
  UpdateWindow(hwnd);

  m_window = hwnd;

  return true;
}

void
Application::render(char*, unsigned int, unsigned int, unsigned char)
{
  return;
}

bool
Application::hasEvent()
{
  return true;
}

Event
Application::getEvent()
{
  MSG msg;
  Event event;

  while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
  {
    std::cout << "Message" << msg.message  << std::endl;

    GetMessage(&msg, NULL, 0, 0);
    TranslateMessage(&msg);
    DispatchMessage(&msg);

    if (msg.message == WM_QUIT)
    {
      std::cout << "Exit" << std::endl;
        event.type = EventType::Quit;
        event.quitEvent.timestamp = 0;
        return event;
    }

    //RedrawWindow((HWND)m_window, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
  }

  std::cout << "End message" << std::endl;

  return event;
}

int
Application::getEventCount()
{
  return 0;
}

bool
Application::pushEvent(Event)
{
  return true;
}

Event
Application::waitForEvent(size_t)
{
  Event event;
  return event;
}

} // namespace Bio
