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

#ifndef BIO_EVENT_H
#define BIO_EVENT_H

/* INCLUDES ******************************************************************/

#include <Bio/Events/EventType.h>
#include <Bio/Events/QuitEvent.h>
#include <Bio/Events/KeyCode.h>
#include <Bio/Events/MouseButtonEvent.h>
#include <Bio/Events/MouseWheelEvent.h>
#include <Bio/Events/MouseMovementEvent.h>
#include <Bio/Events/KeyboardEvent.h>

/* DECLARATIONS **************************************************************/

namespace Bio
{

/**
 * This structure holds events generated by the OS or the application.
 */ 
struct Event
{
    /**
     * The type of the event.
     */
    EventType type;

    /**
     * Keyboard related events.
     */
    KeyboardEvent keyboardEvent;

    /**
     * Mouse button press related events.
     */
    MouseButtonEvent mouseButtonEvent;

    /**
     * Mouse wheel movement related events.
     */
    MouseWheelEvent mouseWheelEvent;

    /**
     * Mouse movement related events.
     */
    MouseMovementEvent mouseMovementEvent;

    /**
     * Quit event, this event is trigger when the application
     * is about to exit.
     */
    QuitEvent quitEvent;
};

}

#endif //BIO_EVENT_H