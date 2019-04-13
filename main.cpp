#include <Display/Display.h>
#include <Display/DisplayParams.h>
#include <Display/IFrameRenderer.h>
#include <Display/IInputHandler.h>

class Application: public Bgi::IFrameRenderer, public Bgi::IInputHandler
{
    /**
     * Renders the image on the buffer.
     * 
     * @param buffer The buffer where to render the image.
     * @param width  The width of the image to be rendered.
     * @param height The height of the image to be rendered.
     * @param channels The number of channels for each pixel.
     **/
    virtual void render(char*, unsigned int, unsigned int, unsigned char)
    {
    }

    virtual void onInput(unsigned int)
    {
    }
};

int main(int, char**)
{
   Bgi::DisplayParams params = { 500, 500, false, false };

   Application* application = new Application();
   Bgi::Display display(application, application, params);
   display.start();
}