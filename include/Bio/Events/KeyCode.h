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


#ifndef BIO_KEYCODE_H
#define BIO_KEYCODE_H

/* DECLARATION ***************************************************************/

namespace Bio
{

/**
 *  The keyboard keycodes.
 */
enum class KeyCode
{
   Unknown = 0,
   A = 65,
   B = 66,
   C = 67,
   D = 68,
   E = 69,
   F = 70,
   G = 71,
   H = 72,
   I = 73,
   J = 74,
   K = 75,
   L = 76,
   M = 77,
   N = 78,
   O = 79,
   P = 80,
   Q = 81,
   R = 82,
   S = 83,
   T = 84,
   U = 85,
   V = 86,
   W = 87,
   X = 88,
   Y = 89,
   Z = 90,
   Numeric1 = 97,
   Numeric2 = 98,
   Numeric3 = 99,
   Numeric4 = 100,
   Numeric5 = 101,
   Numeric6 = 102,
   Numeric7 = 103,
   Numeric8 = 104,
   Numeric9 = 105,
   Numeric0 = 96,
   Return = 13,
   Ecape = 27,
   Backspace = 8,
   Tab = 9,
   Space = 32,
   Minus = 109,
   Equals = 187,
   LeftBracket = 219,
   RightBracket = 221,
   Backslash = 220,
   Semicolon = 186,
   Apostrophe = 222,
   Grave = 192,
   Comma = 188,
   Period = 192,
   Slash = 191,
   CapsLock = 20,
   F1 = 112,
   F2 = 113,
   F3 = 114,
   F4 = 115,
   F5 = 116,
   F6 = 117,
   F7 = 118,
   F8 = 119,
   F9 = 120,
   F10 = 121,
   F11 = 122,
   F12 = 123,
   ScrollLock = 145,
   Pause = 19,
   Insert = 45,
   Home = 36,
   PageUp = 33,
   Delete = 46,
   End = 35,
   PageDown = 34,
   Right = 39,
   Left = 37,
   Down = 40,
   Up = 38,
   Ctrl = 17,
   Shift = 16,
   Alt = 18,
   LeftCommand = 91,
   RightCommand = 92
};

}

#endif /* BIO_KEYCODE_H */