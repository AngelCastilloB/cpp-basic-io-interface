#include <Bio/Application.h>
#include <vector>

static const size_t APPLICATION_WIDTH  = 1920;
static const size_t APPLICATION_HEIGHT = 1080;
int main(int, char**)
{
    std::vector<char> canvas(APPLICATION_WIDTH * APPLICATION_HEIGHT * 3, 255);

    Bio::DisplayParams params = { APPLICATION_WIDTH, APPLICATION_HEIGHT, 0, 0, true, "My first Test" };
    Bio::Application app(params);

    app.initialize();

    Bio::Event event = app.getEvent();
    while (event.type != Bio::EventType::Quit)
    {
        if (event.type == Bio::EventType::Keyboard)
            return 0;

        char r = rand() % 255;
        char g = rand() % 255;
        char b = rand() % 255;
        for (size_t i = 0; i < APPLICATION_WIDTH * APPLICATION_HEIGHT * 3; i += 3)
        {
            canvas[i] = r;
            canvas[i + 1] = g;
            canvas[i + 2] = b;
        }

        app.render(&canvas[0], APPLICATION_WIDTH, APPLICATION_HEIGHT);
        event = app.getEvent();
    }
}