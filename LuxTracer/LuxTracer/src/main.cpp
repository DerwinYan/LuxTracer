
#include <Application.h>
#include <cassert>
#include <memory>

int main()
{
#if defined(DEBUG) || defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif


	lux::Application::Init();
	lux::Application::Run();
	lux::Application::UnInit();

}