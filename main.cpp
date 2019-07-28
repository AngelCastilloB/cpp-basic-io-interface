#include <Bio/Application.h>

int main(int, char**)
{
    Bio::DisplayParams params = { 500, 500, 500, 100, false, "My first Test" };
    Bio::Application app(params);

    app.initialize();

    Bio::Event event = app.getEvent();
    while (event.type != Bio::EventType::Quit)
    {
        app.render(NULL, 0, 0, 0);
        event = app.getEvent();
    }
}