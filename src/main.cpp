#include "renderer.hpp"
#include "event_handler.hpp"

int main()
{
  Renderer renderer("Road Connections", 800, 600);

  if (renderer.initialize_succesfully() == false)
  {
    return 1;
  }

  bool running = true;
  while (running)
  {
    running = EventHandler::update();
    renderer.clear();
    // renderer.draw(coloredObj);
    renderer.present();
  }
  return 0;
}