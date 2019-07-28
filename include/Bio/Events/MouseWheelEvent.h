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

#ifndef BIO_MOUSEWHEELEVENT_H
#define BIO_MOUSEWHEELEVENT_H

/* DECLARATIONS **************************************************************/

namespace Bio
{

/**
 * The mouse button event structure.
 */
struct MouseWheelEvent
{
    /**
     * The tiemstamp of the event.
     */
    long timestamp;

    /**
     * X holds the amount of scrolling in the horizontal direction. A positive number
     * indicates a movement to the right while a negative number indicates a movement
     * to the left.
     */
    long x;

    /**
     * Y Holds the amount of scrolling in the vertical direction. A positive number
     * indicates a movement up while a negative number indicates a movement down.
     */
    long y;
};

}

#endif //BIO_MOUSEWHEELEVENT_H