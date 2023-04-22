#include <iostream>
#include <Window.h>

template<typename BaseSystem>
void lux::GraphicsSystem<BaseSystem>::Init()
{
	pbo.Init(Window::width, Window::height);
}

template<typename BaseSystem>
void lux::GraphicsSystem<BaseSystem>::Update()
{
	pbo.Bind();

	for (int j = pbo.imgHeight - 1; j >= 0; --j)
	{
		for (int i{}; i < pbo.imgWidth; ++i)
		{
			double r = (double)i / (pbo.imgWidth - 1);
			double g = (double)j / (pbo.imgHeight - 1);
			double b = 0.25;

			pbo.WritePixel(i, j, math::dvec3(r, g, b));
		}
	}

	pbo.Render();
}

template<typename BaseSystem>
void lux::GraphicsSystem<BaseSystem>::UnInit()
{
	std::cout << "Graphics unInit!\n";
}
