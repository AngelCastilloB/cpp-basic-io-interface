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
#include <sstream>
#include <string>

/* USINGS ********************************************************************/

/* CONSTANTS  ****************************************************************/

static const char* WINDOWS_CLASS_NAME = "MainWindow";

/* STATIC VARIABLES **********************************************************/

static HINSTANCE g_moduleInstance = GetModuleHandle(0);

/* STATIC FUNCTIONS **********************************************************/

/**
 * An application-defined function that processes messages sent to a window.
 * The WNDPROC type defines a pointer to this callback function.
 * 
 * @param windowHandler A handle to the window.
 * @param message       The message. For lists of the system-provided messages, see @link https://docs.microsoft.com/en-us/windows/win32/winmsg/about-messages-and-message-queues
 * @param wParam        Additional message information. The contents of this parameter depend on the value of the uMsg parameter..
 * @param lParam        Additional message information. The contents of this parameter depend on the value of the uMsg parameter.
 * 
 * @return The return value is the result of the message processing and depends on the message sent.
 */
LRESULT CALLBACK WndProc(HWND windowHandler, UINT message, WPARAM wParam, LPARAM lParam)
{
  PAINTSTRUCT ps;

  switch (message)
  {
    case WM_PAINT:
      // draw nothing here. drawing happens in the render() function that
      // we MANUALLY call ourselves.
      BeginPaint(windowHandler, &ps);
      EndPaint(windowHandler, &ps);
      return 0;
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
    case WM_ERASEBKGND:
      return 1;
    default:
      return DefWindowProc(windowHandler, message, wParam, lParam);
  }
}

/**
 * Sets the window to full screen.
 * 
 * @param windowHandler The window handle.
 **/
static void
setFullScreen(HWND windowHandler)
{
  LONG style = GetWindowLong(windowHandler, GWL_STYLE);
  style &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZE | WS_MAXIMIZE | WS_SYSMENU);

  SetWindowLong(windowHandler, GWL_STYLE, style);
  SetWindowPos(windowHandler, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SWP_FRAMECHANGED | SWP_SHOWWINDOW);
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
  HWND windowHandler;
  WNDCLASS windowClass;
  Gdiplus::GdiplusStartupInput gdiplusStartupInput;

  Gdiplus::GdiplusStartup(reinterpret_cast<ULONG_PTR*>(&m_context), &gdiplusStartupInput, NULL);

  windowClass.style         = CS_HREDRAW | CS_VREDRAW;
  windowClass.lpfnWndProc   = WndProc;
  windowClass.cbClsExtra    = 0;
  windowClass.cbWndExtra    = 0;
  windowClass.hInstance     = g_moduleInstance;
  windowClass.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
  windowClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
  windowClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
  windowClass.lpszMenuName  = NULL;
  windowClass.lpszClassName = TEXT(WINDOWS_CLASS_NAME);

  RegisterClass(&windowClass);

  windowHandler = CreateWindow(
      TEXT(WINDOWS_CLASS_NAME),
      TEXT(m_params.title.c_str()),
      WS_OVERLAPPEDWINDOW,
      m_params.x < 0 ? CW_USEDEFAULT : m_params.x,
      m_params.y < 0 ? CW_USEDEFAULT : m_params.y,
      m_params.width,
      m_params.height,
      NULL,
      NULL,
      g_moduleInstance,
      NULL);

  if (m_params.isMaximized)
    setFullScreen((HWND)windowHandler);

  ShowWindow(windowHandler, 4);
  UpdateWindow(windowHandler);

  m_window = windowHandler;

  return true;
}

void
Application::render(char*, unsigned int, unsigned int, unsigned char)
{
  int width = GetSystemMetrics(SM_CXSCREEN);
  int height = GetSystemMetrics(SM_CYSCREEN);

  HDC hdc = GetDC((HWND)m_window);
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
  
  /* END RAWING **************************************************************/
	
  BitBlt(hdc, 0, 0, width, height, memDC, 0, 0, SRCCOPY);
  
  // all done, now we need to cleanup
  SelectObject(memDC, oldBmp); // select back original bitmap
  DeleteObject(bmp); // delete bitmap since it is no longer required
  DeleteDC(memDC);   // delete memory DC since it is no longer required
}

Event
Application::getEvent()
{
  MSG msg;
  Event event;

  while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);

    if (msg.message == WM_QUIT)
    {
        event.type = EventType::Quit;
        event.quitEvent.timestamp = 0;
        return event;
    }
  }

  return event;
}

bool
Application::pushEvent(Event)
{
  return true;
}

} // namespace Bio
