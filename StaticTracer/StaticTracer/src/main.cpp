
#include <cassert>
#include <memory>

#include <PTEngine.h>

int main()
{
#if defined(DEBUG) || defined(_DEBUG)
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

  pt::Window window{ 256, 256 };
  pt::PTEngine engine{ window };
  engine.run();
}
