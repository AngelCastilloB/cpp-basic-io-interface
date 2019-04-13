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

#ifndef BIO_IINPUTHANDLER_H
#define BIO_IINPUTHANDLER_H

/* INCLUDES ******************************************************************/

#include <memory>

/* CLASS DECLARATION *********************************************************/

namespace Bio
{

/**
 * Event handler for the user input (keyboard and mouse).
 */
class IInputHandler
{
  public:

    /**
     * @brief Finalizes a new instance of the IInputHandler class.
     */
    virtual ~IInputHandler() {};

  public:

    /**
     * Event handler called when an input arrive.
     * 
     * @param event The input event.
     **/
    virtual void onInput(unsigned int event) = 0;
};

} /* namespace Bio */

#endif //BIO_IINPUTHANDLER_H