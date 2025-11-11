#ifndef RENDERER
#define RENDERER

#include <Window.h>
#include <Framebuffer.h>

namespace pt
{
  class Renderer
  {
  public:
    Renderer(Window window);
    void render();
    void display();

  private:
    Window window;
    Framebuffer framebuffer;
  };
}

#endif // !RENDERER
