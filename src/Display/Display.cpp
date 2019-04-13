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

#if defined(_WIN32) || defined(_WIN64) || (defined(__CYGWIN__) && !defined(_WIN32))
    #include "./WindowsDisplay.cpp"
#elif defined(__linux__) ||defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
    #include "./UnixDisplay.cpp"
#endif