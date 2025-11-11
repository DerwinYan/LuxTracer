#include <Core/PTEngine.h>
#include <Graphics/GraphicsSystem.h>

pt::PTEngine::PTEngine(Window const& window) : context{ window }
{
  systems.emplace_back(std::make_unique<GraphicsSystem>(context));
}

void pt::PTEngine::run()
{
  for (auto const& system : systems)
  {
    system.get()->update();
  }
}

pt::PTEngine::~PTEngine()
{
  for (auto rIT{ systems.crbegin() }; rIT != systems.crbegin(); --rIT)
  {
    rIT->get()->exit();
    rIT->~shared_ptr();
  }
}
