#include <Bio/Application.h>
#include <vector>
#include <iostream>

static const size_t APPLICATION_WIDTH  = 500;
static const size_t APPLICATION_HEIGHT = 500;
int main(int, char**)
{
    std::vector<char> canvas(APPLICATION_WIDTH * APPLICATION_HEIGHT * 3, 255);

    Bio::DisplayParams params = { APPLICATION_WIDTH, APPLICATION_HEIGHT, 0, 0, false, "My first Test" };
    Bio::Application app(params);

    app.initialize();

    std::cout << "Test LOG" << std::endl;
    Bio::Event event = app.getEvent();
    size_t currentX = 0;
    size_t cunrretY = 0;
    size_t objectArea = 25;
    while (event.type != Bio::EventType::Quit)
    {
        if (app.isKeyPressed(Bio::KeyCode::Return))
        {
            break;
        }

        if (app.isKeyPressed(Bio::KeyCode::Left))
            --currentX;

        if (app.isKeyPressed(Bio::KeyCode::Right))
            ++currentX;

        if (app.isKeyPressed(Bio::KeyCode::Up))
            --cunrretY;

        if (app.isKeyPressed(Bio::KeyCode::Down))
            ++cunrretY;

        if (cunrretY > APPLICATION_HEIGHT - objectArea)
            cunrretY = APPLICATION_HEIGHT - objectArea;

        if (currentX > APPLICATION_WIDTH)
            currentX = APPLICATION_WIDTH - objectArea;

        char r = rand() % 255;
        char g = rand() % 255;
        char b = rand() % 255;
        for (size_t i = 0; i < APPLICATION_WIDTH * APPLICATION_HEIGHT * 3; i += 3)
        {
            canvas[i] = r;
            canvas[i + 1] = g;
            canvas[i + 2] = b;
        }

        for (size_t i = 0; i < objectArea; ++i)
        {
            for (size_t j = 0; j < objectArea; ++j)
            {
                canvas[(3 * (cunrretY + j) * APPLICATION_WIDTH) + (3 * (currentX + i)) ] = 0;
                canvas[(3 * (cunrretY + j) * APPLICATION_WIDTH) + (3 * (currentX + i)) + 1] = 0;
                canvas[(3 * (cunrretY + j) * APPLICATION_WIDTH) + (3 * (currentX + i)) + 2] = 0;
            }
        }

        app.render(&canvas[0], APPLICATION_WIDTH, APPLICATION_HEIGHT);
        event = app.getEvent();
    }
}