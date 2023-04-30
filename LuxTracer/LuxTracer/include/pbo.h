#pragma once

#include <Math/vec3.h>
#include <vector>

namespace lux
{
	struct Pbo
	{
		//union Color4
		//{
		//	unsigned char color[4];
		//	unsigned int raw;

		//	Color4() = default;
		//	Color4(unsigned char r, unsigned char g, unsigned char b, unsigned char a) : color{ r,g,b,a } {}
		//	Color4(unsigned int val) : raw{ val } {}

		//	Color4 operator*(float val)
		//	{
		//		return Color4(
		//			(unsigned char)(std::roundf(color[0]*val)),
		//			(unsigned char)(std::roundf(color[1]*val)), 
		//			(unsigned char)(std::roundf(color[2]*val)), 
		//			255);
		//	}

		//	Color4 operator+(Color4 const rhs)
		//	{
		//		return Color4(
		//			color[0] + rhs.color[0],
		//			color[1] + rhs.color[1],
		//			color[2] + rhs.color[2],
		//			255
		//		);
		//	}
		//};

		void Init(int const imgWidth, int const imgHeight);
		void WritePixel(int x, int y, math::vec3 const& color);
		void Bind();
		void Render();
		void Clear();
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

		void Accumulate();

		unsigned totalFrames{};

		//Model
		unsigned vao{};
		unsigned numIndices{};

		//Render texture
		unsigned pboFrontID{};
		unsigned pboBackID{};
		unsigned texID{};

		//Shader
		unsigned shaderPgm{};
		math::vec3* pboPtr{};

		//for each helper
		std::vector<unsigned> iter;
	};
}