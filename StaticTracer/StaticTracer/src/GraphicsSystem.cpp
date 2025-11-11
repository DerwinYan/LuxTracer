#include <GraphicsSystem.h>
#include <Renderer.h>

pt::GraphicsSystem::GraphicsSystem(pt::EngineContext const& context) 
  : ISystem{ context }, framebuffer{ context.window.getWidth(), context.window.getHeight() }
{

}

void pt::GraphicsSystem::init() {}

void pt::GraphicsSystem::update()
{
  Renderer renderer{ context.window };
  renderer.render();
  renderer.display();
}

void pt::GraphicsSystem::exit() {}
