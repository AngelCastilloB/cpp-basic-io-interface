#include <Bio/Application.h>

int main(int, char**)
{
    Bio::DisplayParams params = { 500, 500, 0, 0, false };
    Bio::Application app(params);

    app.initialize();

    while (app.hasEvent())
    {
        Bio::Event event = app.getEvent();
        if (event.type == Bio::EventType::Quit)
            break;
    }

   //Bio::DisplayParams params = { 500, 500, 0, 0, false };

   //Application* application = new Application();
   //Bio::Display display(application, application, params);
   //display.start();
}