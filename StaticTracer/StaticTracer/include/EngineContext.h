#ifndef ENGINECONTEXT
#define ENGINECONTEXT

namespace pt
{
  class Window;

  class EngineContext
  {
  public:
    EngineContext(Window const& window);
    Window const& window;
  };
}

#endif // !ENGINECONTEXT