
#include <cassert>
#include <memory>

#include <Core/PTEngine.h>
#include <Windows.h>

int main()
{
#if defined(DEBUG) || defined(_DEBUG)
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

  pt::Window window{ 1920, 1080 };
  pt::PTEngine engine{ window };
  engine.run();

  // open image to preview
  const char* path{ "output.png" };
  HINSTANCE result = ShellExecuteA(nullptr, "open", path, nullptr, nullptr, SW_SHOWNORMAL);
  if ((int)result <= 32) {
    MessageBoxA(nullptr, "Failed to open image file.", "Error", MB_OK | MB_ICONERROR);
  }
}
