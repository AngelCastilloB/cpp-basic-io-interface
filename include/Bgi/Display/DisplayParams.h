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

#ifndef BGI_DISPLAYPARAMS_H
#define BGI_DISPLAYPARAMS_H

/* INCLUDES ******************************************************************/

#include <memory>

/* CLASS DECLARATION *********************************************************/

namespace Bgi
{

/**
 * The parameters of the display.
 */
struct DisplayParams
{
    unsigned int width;
    unsigned int height;
    bool         isMaximized;
    bool         removeBorders;
};

} /* namespace Bgi */

#endif //BGI_DISPLAYPARAMS_H