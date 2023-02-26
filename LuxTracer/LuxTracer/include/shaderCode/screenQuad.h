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

			uniform sampler2D uTexture2D;

			void main()
			{
				fFragColor = texture(uTexture2D, vUV);
				//fFragColor = vec4(0.2, 0.3, 0.3, 1.0);
			}
		)"
	};
}