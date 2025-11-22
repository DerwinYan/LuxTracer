#ifndef RENDERER
#define RENDERER

#include <Core/Window.h>
#include <Graphics/Framebuffer.h>
#include <Graphics/Scene.h>

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
    Scene scene;
  };
}

#endif // !RENDERER
