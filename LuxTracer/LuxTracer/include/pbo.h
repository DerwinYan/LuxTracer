#pragma once

#include <Math/dvec3.h>

namespace lux
{
	struct Pbo
	{
		union Color4
		{
			unsigned char color[4];
			unsigned int raw;

			Color4() = default;
			Color4(unsigned char r, unsigned char g, unsigned char b, unsigned char a) : color{ r,g,b,a } {}
			Color4(unsigned int val) : raw{ val } {}
		};

		void Init(int const imgWidth, int const imgHeight);
		void WritePixel(int x, int y, math::dvec3 const& color);
		void Bind();
		void Render();
		void Clear(Color4 const clearColor);
		void Resize(int const newWidth, int const newHeight);

		//Texture size
		int imgWidth{};
		int imgHeight{};
		int imgSize{};

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
		Color4* pboPtr{};
	};
}