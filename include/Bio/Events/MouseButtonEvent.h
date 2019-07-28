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

#ifndef BIO_MOUSEBUTTONEVENT_H
#define BIO_MOUSEBUTTONEVENT_H

/* INCLUDES ******************************************************************/

#include <Bio/Events/MouseButtonCode.h>

/* DECLARATIONS **************************************************************/

namespace Bio
{

/**
 * The mouse button event structure.
 */
struct MouseButtonEvent
{
    /**
     * The tiemstamp of the event.
     */
    long timestamp;

    /**
     * The code of the button that trigger the event.
     */
    MouseButtonCode code;

    /**
     * Whether the button was pressed or not; true if the button was pressed; otherwise; false.
     */
    bool wasPressed;
};

}

#endif //BIO_MOUSEBUTTONEVENT_H