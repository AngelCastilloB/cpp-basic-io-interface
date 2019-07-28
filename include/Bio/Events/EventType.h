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

#ifndef BIO_EVENTTYPE_H
#define BIO_EVENTTYPE_H

/* DECLARATIONS **************************************************************/

namespace Bio
{

/**
 * The different events handled by the event queue.
 */
enum class EventType
{
    /**
     * The application will quit.
     */
    Quit,

    /**
     * A keyboard event. Key presses and releases.
     */
    Keyboard,

    /**
     * The mouse was moved.
     */
    MouseMovement,

    /**
     * A mouse button was clicked.
     */
    MouseButton,

    /**
     * The mouse wheel was moved.
     */
    MouseWheel,

    /**
     * Custom event created by the user.
     */
    Custom
};

}

#endif //BIO_EVENTTYPE_H