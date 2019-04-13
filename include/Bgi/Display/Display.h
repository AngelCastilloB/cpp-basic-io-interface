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

#ifndef BGI_DISPLAY_H
#define BGI_DISPLAY_H

/* INCLUDES ******************************************************************/

#include <memory>
#include "IFrameRenderer.h"
#include "IInputHandler.h"
#include "DisplayParams.h"

/* CLASS DECLARATION *********************************************************/

namespace Bgi
{

/**
 * Creates a window with the given parameters. This display object handles all the drawing in the actual window and
 * also reports all input events to the user throughout the IInputHandler interface.
 */
class Display
{
  public:

    /**
     * Initializes a new instance of the Display class.
     *
     * @param frameRenderer An instance of a IFrameRenderer concrete class. This class takes ownership of the life
     *                      cycle of this object.
     * @param inputHandler  An instance of a IInputHandler class. This class takes ownership of the life
     *                      cycle of this object.
     * @param DisplayParams The display parameters of the window. 
     */
    Display(IFrameRenderer* frameRenderer, IInputHandler* inputHandler, DisplayParams params);

    /**
     * @brief Finalizes a new instance of the Display class.
     */
    virtual ~Display();

  public:

    /**
     * Starts the display instance. This method will block until the display is stopped.
     **/
    void start();

    /**
     * Stopts the display instance.
     **/
    void stop();

  private:

    std::unique_ptr<IFrameRenderer> m_frameRenderer;
    std::unique_ptr<IInputHandler>  m_inputHandler;
    DisplayParams                   m_params;
    unsigned int                    m_height;
    unsigned int                    m_width;
    bool                            m_isRunning;
};

} /* namespace Bgi */

#endif //BGI_DISPLAY_H
