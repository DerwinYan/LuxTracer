#ifndef GRAPHICSSYSTEM
#define GRAPHICSSYSTEM

#include <Core/ISystem.h>
#include <Core/PTEngine.h>
#include <Graphics/Framebuffer.h>

namespace pt
{
  class GraphicsSystem : public ISystem
  {
  public:
    explicit GraphicsSystem(EngineContext const& context);
    void init() override;
    void update() override;
    void exit() override;

    ~GraphicsSystem() = default;

  private:
    Framebuffer framebuffer;
  };
}

#endif // !GRAPHICSSYSTEM

