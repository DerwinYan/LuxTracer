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
		void BindPBO();
		void Render();
		void Free();

	private:
		union uColor4
		{
			unsigned char color[4];
			unsigned int raw;

			uColor4() = default;
			uColor4(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
				: color{ r,g,b,a }
			{}
			uColor4(unsigned int val) : raw{ val } {}
		};
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
		uColor4	 clearColor{};
		uColor4* pboPtr{};
	};
}