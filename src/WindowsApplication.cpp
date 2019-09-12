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
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <share.h>

/* USINGS ********************************************************************/

/* CONSTANTS  ****************************************************************/

static const char* WINDOWS_CLASS_NAME  = "MainWindow";
static const int   IMAGE_CHANNELS      = 3;
static const int   IMAGE_INITIAL_VALUE = 0;
static const int   RED_CHANNEL_INDEX   = 0;
static const int   GREEN_CHANNEL_INDEX = 1;
static const int   BLUE_CHANNEL_INDEX  = 2;
static const int   PLANES_COUNT        = 1;
static const int   PIXEL_SIZE_IN_BITS  = 32;

static const WORD MAX_CONSOLE_LINES = 500;

/* DEFINES *******************************************************************/

#define BIO_DEBUG 1

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
 * Converts a byte array of pixels into a color ref collection.
 */
static std::vector<COLORREF>
toColorRef(char* data, unsigned int width, unsigned int height)
{
    std::vector<COLORREF> colorRef(width * height, IMAGE_INITIAL_VALUE);

    size_t colorRefIndex = 0;
    for (size_t i = 0; i < (width * height * 3); i += IMAGE_CHANNELS)
    {
      // For some reason the channels are inverted, so we must pass blue first and red last.
      colorRef[colorRefIndex] = RGB(data[i + BLUE_CHANNEL_INDEX], data[i + GREEN_CHANNEL_INDEX], data[i + RED_CHANNEL_INDEX]);
      ++colorRefIndex;
    }

    return colorRef;
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

/**
 * Redirects cout, wcout, cin, wcin, wcerr, cerr, wclog and clog to the console.
 */ 
#ifdef BIO_DEBUG
static void
redirectIoToConsole()
{
  int  hConHandle = 0;
  long lStdHandle = 0;

  CONSOLE_SCREEN_BUFFER_INFO coninfo = { {0, 0}, {0, 0},  0, {0, 0, 0, 0}, {0, 0} };

  FILE* fp = NULL;;

  AllocConsole();

  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);

  coninfo.dwSize.Y = MAX_CONSOLE_LINES;

  SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),coninfo.dwSize);

  lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
  hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);

  fp = _fdopen(hConHandle, "w");

  *stdout = *fp;

  setvbuf(stdout, NULL, _IONBF, 0 );

  lStdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);

  hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);

  fp = _fdopen(hConHandle, "r");

  *stdin = *fp;

  setvbuf( stdin, NULL, _IONBF, 0 );

  lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);

  hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);

  fp = _fdopen(hConHandle, "w");

  *stderr = *fp;

  setvbuf( stderr, NULL, _IONBF, 0 );

  std::ios::sync_with_stdio();
}
#endif

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

  #ifdef BIO_DEBUG
  redirectIoToConsole();
  #endif

  return true;
}

void
Application::render(char* data, unsigned int width, unsigned int height)
{   
  HDC hdc = GetDC((HWND)m_window);

  std::vector<COLORREF> colors = toColorRef(data, width, height);

  HBITMAP map = CreateBitmap(width, height, PLANES_COUNT, PIXEL_SIZE_IN_BITS, reinterpret_cast<void*>(&colors[0]));

  HDC src = CreateCompatibleDC(hdc);
  SelectObject(src, map);

  BitBlt(hdc, 0, 0, width, height, src, 0, 0, SRCCOPY);

  DeleteObject(map);
  DeleteDC(src);
}

Event
Application::getEvent()
{
  MSG msg;
  Event event;

  event.type = EventType::None;

  if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);

    if (msg.message == WM_QUIT)
    {
        event.type = EventType::Quit;
        event.quitEvent.timestamp = 0;
        return event;
      }
      
    if (msg.message == WM_KEYDOWN)
    {
      event.type = EventType::Keyboard;
      event.keyboardEvent.timestamp = 0;
      event.keyboardEvent.code = static_cast<KeyCode>(msg.wParam);
      event.keyboardEvent.wasPressed = true;

      m_keyState.insert(event.keyboardEvent.code);
      return event;
    }
    else if (msg.message == WM_KEYUP)
    {
      event.type = EventType::Keyboard;
      event.keyboardEvent.timestamp = 0;
      event.keyboardEvent.code = static_cast<KeyCode>(msg.wParam);
      event.keyboardEvent.wasPressed = false;

      m_keyState.erase(event.keyboardEvent.code);
      return event;
    }
  }

  return event;
}

bool
Application::isKeyPressed(KeyCode code)
{
  return m_keyState.find(code) != m_keyState.end();
}

bool
Application::pushEvent(Event)
{
  return true;
}

} // namespace Bio
