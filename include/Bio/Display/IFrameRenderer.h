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

#ifndef BIO_IFRAMERENDERER_H
#define BIO_IFRAMERENDERER_H

/* INCLUDES ******************************************************************/

#include <memory>

/* CLASS DECLARATION *********************************************************/

namespace Bio
{

/**
 * Renders the next frame to be displayed.
 */
class IFrameRenderer
{
  public:

    /**
     * @brief Finalizes a new instance of the IFrameRenderer class.
     */
    virtual ~IFrameRenderer() {};

  public:

    /**
     * Renders the image on the buffer.
     * 
     * @param buffer The buffer where to render the image.
     * @param width  The width of the image to be rendered.
     * @param height The height of the image to be rendered.
     * @param channels The number of channels for each pixel.
     **/
    virtual void render(char* buffer, unsigned int width, unsigned int height, unsigned char channels) = 0;
};

} /* namespace Bio */

#endif //BIO_IFRAMERENDERER_H
