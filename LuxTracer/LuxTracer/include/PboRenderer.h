#pragma once
#include <math/vecx.h>

namespace lux
{
	class PboRenderer
	{
	public:
		void Init(int width, int height);
		void SetClearColor(vec3 const& color);
		void WritePixel(int x, int y, vec3 const& color);
		void Render();
		void Free();

	private:
		void CreateShaderPgm();
		void CreateScreenQuad();
		void CreatePBO();
		void CreateTexture();

		//Model
		unsigned vao{};
		unsigned numIndices{};

		//Render texture
		unsigned pboID{};
		unsigned texID{};

		//Shader
		unsigned shaderPgm{};
		vec3		 clearColor{};
	};
}