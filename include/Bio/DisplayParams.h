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

#ifndef BIO_DISPLAYPARAMS_H
#define BIO_DISPLAYPARAMS_H

/* INCLUDES ******************************************************************/

#include <memory>

/* DEFINES *******************************************************************/

constexpr int DEFAULT_POSITION = -1;

/* CLASS DECLARATION *********************************************************/

namespace Bio
{

/**
 * The parameters of the display.
 */
struct DisplayParams
{
    unsigned int width;
    unsigned int height;
    int          x;
    int          y;
    bool         isMaximized;
    std::string  title;
};

} /* namespace Bio */

#endif //BIO_DISPLAYPARAMS_H