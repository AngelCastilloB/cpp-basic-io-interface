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

#ifndef BIO_MOUSEMOVEMENTEVENT_H
#define BIO_MOUSEMOVEMENTEVENT_H

/* DECLARATIONS **************************************************************/

namespace Bio
{

/**
 * The mouse movement event structure.
 */
struct MouseMovementEvent
{
    /**
     * The tiemstamp of the event.
     */
    long timestamp;

    /**
     * The current position of the cursor in the X axis.
     */
    long x;

    /**
     * The current position of the cursor in the Y axis.
     */
    long y;

    /**
     * The amount of movement relative to the last pointer position in the X a axis.
     */
    long relativeX;

    /**
     * The amount of movement relative to the last pointer position in the Y a axis.
     */
    long relativeY;
};

}

#endif //BIO_MOUSEMOVEMENTEVENT_H