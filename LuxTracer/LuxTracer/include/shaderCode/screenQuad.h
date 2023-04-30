#pragma once


namespace lux::screenShdr
{
	const char* const vertShader
	{
		R"(
			#version 460 core
			layout (location = 0) in vec4 aPos;
			
			layout (location = 0) out vec2 vUV;

			void main()
			{
				gl_Position = vec4(aPos.xy, 0.0, 1.0);
				vUV = aPos.zw;
			}
		)"
	};

	const char* const fragShader
	{
		R"(
			#version 460 core
			layout (location = 0) in vec2 vUV;

			layout (location = 0) out vec4 fFragColor;

			uniform sampler2D uCurrTex;
			uniform sampler2D uPrevTex;
			uniform int uFrameNum;

			void main()
			{
				vec4 prevCol = vec4(texture(uPrevTex, vUV).rgb, 1.0);
				vec4 currCol = vec4(texture(uCurrTex, vUV).rgb, 1.0);
				float weight = 1.0 / (uFrameNum + 1);

				fFragColor = prevCol * (1.0-weight) + currCol * weight;
			}
		)"
	};
}