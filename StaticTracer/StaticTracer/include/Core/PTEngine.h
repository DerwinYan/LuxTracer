#ifndef PTENGINE
#define PTENGINE

#include <memory>
#include <vector>
#include <Core/ISystem.h>
#include <Core/Window.h>

namespace pt
{
  class PTEngine
  {
   public:
    PTEngine(Window const& window);
    void run();
    ~PTEngine();

  private:
    EngineContext context;
    std::vector<std::shared_ptr<ISystem>> systems;
  };
}

#endif // !PTENGINE
