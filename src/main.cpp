#include "event_handler.hpp"
#include "game_controller.hpp"
#include "renderer.hpp"

int main()
{
    Renderer renderer("Road Connections", 1900, 800);

    if (renderer.initialize_succesfully() == false)
    {
        return 1;
    }

    GameController::init();

    bool running = true;
    while (running)
    {
        running = EventHandler::update(renderer);
        renderer.clear();
        renderer.draw();
        renderer.present();
    }
    return 0;
}