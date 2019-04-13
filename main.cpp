#include <Display/Display.h>
#include <Display/DisplayParams.h>
#include <Display/IFrameRenderer.h>
#include <Display/IInputHandler.h>

class Application: public Bio::IFrameRenderer, public Bio::IInputHandler
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
   Bio::DisplayParams params = { 500, 500, 0, 0, false };

   Application* application = new Application();
   Bio::Display display(application, application, params);
   display.start();
}