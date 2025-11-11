#ifndef ISYSTEM
#define ISYSTEM

#include <Core/EngineContext.h>

namespace pt
{
  class ISystem
  {
  public:
    explicit ISystem(EngineContext const& context) : context{ context } {}
    virtual ~ISystem() = default;

    virtual void init() = 0;
    virtual void update() = 0;
    virtual void exit() = 0;

  protected:
    EngineContext const& context;
  };
}

#endif // !ISYSTEM
