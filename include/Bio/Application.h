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

#ifndef BIO_APPLICATION_H
#define BIO_APPLICATION_H

/* INCLUDES ******************************************************************/

#include <memory>
#include <queue>

#include <Bio/DisplayParams.h>
#include <Bio/Events/Event.h>

/* CLASS DECLARATION *********************************************************/

namespace Bio
{

/**
 * Creates a basic input/output application. The application class will create a window with the given parameters.
 * This display object handles all the drawing in the actual window and also reports all events to the user.
 */
class Application
{
  public:

    /**
     * Initializes a new instance of the Application class.
     *
     * @param ApplicationParams The Application parameters of the window. 
     */
    Application(DisplayParams params);

    /**
     * @brief Finalizes a new instance of the Application class.
     */
    virtual ~Application();

  public:

    /**
     * Initializes the Application class.
     * 
     * @return true if the application was initialized; otherwise; false.
     */
    bool initialize();

    /**
     * Renders the image on the buffer.
     * 
     * @param buffer The buffer where to render the image.
     * @param width  The width of the image to be rendered.
     * @param height The height of the image to be rendered.
     * @param channels The number of channels for each pixel.
     **/
    void render(char* buffer, unsigned int width, unsigned int height, unsigned char channels);

    /**
     * Gets whether there are events to be processesd in the event queue.
     * 
     * @return true if there are events pending; otherwise; false.
     */
    bool hasEvent();

    /**
     * Gets the next event in the event queue.
     * 
     * @return Event The next event in the queue.
     * 
     * @remark if this function is call while the event queue is empty, the function will return a NULL
     *         event.
     */
    Event getEvent();

    /**
     * Gets the current number of events in the queue.
     * 
     * @return The number of event currently in the event queue.
     */
    int getEventCount();

    /**
     * Pushes an event to the event queue.
     * 
     * @param event The event to be added to the event queue.
     * 
     * @return true if the event was added; otherwise; false.
     */
    bool pushEvent(Event event);

    /**
     * Waits until there is an event in the queue. If the queue is not empty it will return immediatly
     * with the next event in the queue. Otherwise it will wait until a new event is added to the queue.
     * 
     * @param timeout The time (in milliseconds) the function will block until a new event is added to the queue.
     *                If the timeout value is 0 (zero) this function will block indefinetly until a new event arrives.
     * 
     * @return Event  The new event.
     * 
     * @remark if a timeout different than 0 (zero) is set, and no event arrives after the timout expires, the function will return a NULL
     *         event.
     */
    Event waitForEvent(size_t timeout = 0);

  private:

    DisplayParams     m_params;
    unsigned int      m_height;
    unsigned int      m_width;
    void*             m_context;
    void*             m_window;
    std::queue<Event> m_eventQueue;
};

} /* namespace Bio */

#endif //BIO_APPLICATION_H