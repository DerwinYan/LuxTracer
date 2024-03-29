﻿#include <pbo.h>
#include <GL/glew.h>
#include <Logger.h>
#include <ShaderCode/ScreenQuad.h>
#include <array>
#include <Math/mathUtils.h>
#include <algorithm>
#include <execution>

namespace lux
{
	void Pbo::Init(int const _imgWidth, int const _imgHeight)
	{
		imgWidth = _imgWidth;
		imgHeight = _imgHeight;
		imgSize = imgWidth * imgHeight;

		iter.resize(imgSize);
		for (unsigned i{}; i < (unsigned)imgSize; ++i)
			iter[i] = i;

		CreateShaderPgm();
		CreatePBO();
		CreateScreenQuad();
		CreateTexture();
	}

	void Pbo::WritePixel(int x, int y, math::vec3 const& color)
	{
		LogAssert(pboPtr, "PBO ptr bad!");
		pboPtr[imgWidth * y + x] = color;
	}

	void Pbo::Bind()
	{
		pboPtr = static_cast<math::vec3*>(glMapNamedBuffer(pboBackID, GL_WRITE_ONLY));
		LogAssert(pboPtr, "Unsuccessful PBO mapping!");
	}

	void Pbo::Render()
	{
		Accumulate();

		unsigned tempID = pboFrontID;
		pboFrontID = pboBackID;
		pboBackID = tempID;

		glUnmapNamedBuffer(pboFrontID);
		pboPtr = nullptr;

		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pboFrontID);
		glTextureSubImage2D(texID, 0, 0, 0, imgWidth, imgHeight, GL_RGBA, GL_FLOAT, NULL);
		glBindTextureUnit(0, texID);

		glUseProgram(shaderPgm);
		glBindVertexArray(vao);
		int uniformLocation = glGetUniformLocation(shaderPgm, "uTexture2D");
		glUniform1i(uniformLocation, 0);
		glDrawElements(GL_TRIANGLE_STRIP, numIndices, GL_UNSIGNED_SHORT, NULL);
		glBindVertexArray(0);
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
	}

	void Pbo::Clear()
	{
		math::vec3* tmp;
		tmp = static_cast<math::vec3*>(glMapNamedBuffer(pboBackID, GL_WRITE_ONLY));
		std::memset(tmp, 0, imgSize * sizeof(math::vec3));
		glUnmapNamedBuffer(pboBackID);

		tmp = static_cast<math::vec3*>(glMapNamedBuffer(pboFrontID, GL_WRITE_ONLY));
		std::memset(tmp, 0, imgSize * sizeof(math::vec3));
		glUnmapNamedBuffer(pboFrontID);

		totalFrames = 0;
	}

	void Pbo::Resize(int const newWidth, int const newHeight)
	{
		imgWidth = newWidth;
		imgHeight = newHeight;
		imgSize = imgWidth * imgHeight;

		CreatePBO();
		CreateTexture();
	}

	void Pbo::CreateShaderPgm()
	{
		int compileResult;
		shaderPgm = glCreateProgram();

		//Create vertex shader
		unsigned vertHandle = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertHandle, 1, &screenShdr::vertShader, NULL);
		glCompileShader(vertHandle);
		glGetShaderiv(vertHandle, GL_COMPILE_STATUS, &compileResult);
		if (!compileResult)
		{
			std::string logMsg{ "Vertex shader compilation failed!\n" };
			int logLen;
			glGetShaderiv(vertHandle, GL_INFO_LOG_LENGTH, &logLen);
			if (logLen > 0) {
				GLchar* log = new GLchar[logLen];
				GLsizei written_log_len;
				glGetShaderInfoLog(vertHandle, logLen, &written_log_len, log);
				logMsg += log;
				delete[] log;
			}
			LogError(logMsg);
		}
		else
		{
			glAttachShader(shaderPgm, vertHandle);
		}

		//Create fragment shader
		unsigned fragHandle = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragHandle, 1, &screenShdr::fragShader, NULL);
		glCompileShader(fragHandle);
		glGetShaderiv(fragHandle, GL_COMPILE_STATUS, &compileResult);
		if (!compileResult)
		{
			std::string logMsg{ "Fragment shader compilation failed!\n" };
			int logLen;
			glGetShaderiv(fragHandle, GL_INFO_LOG_LENGTH, &logLen);
			if (logLen > 0) {
				GLchar* log = new GLchar[logLen];
				GLsizei written_log_len;
				glGetShaderInfoLog(fragHandle, logLen, &written_log_len, log);
				logMsg += log;
				delete[] log;
			}
			LogError(logMsg);
		}
		else
		{
			glAttachShader(shaderPgm, fragHandle);
		}

		//Link shader to program
		int linkStatus;
		glLinkProgram(shaderPgm);
		glGetProgramiv(shaderPgm, GL_LINK_STATUS, &linkStatus);
		if (GL_FALSE == linkStatus)
		{
			std::string logMsg = "Failed to link shader program\n";
			GLint log_len;
			glGetProgramiv(shaderPgm, GL_INFO_LOG_LENGTH, &log_len);
			if (log_len > 0) {
				GLchar* log_str = new GLchar[log_len];
				GLsizei written_log_len;
				glGetProgramInfoLog(shaderPgm, log_len, &written_log_len, log_str);
				logMsg += log_str;
				delete[] log_str;
			}
			LogError(logMsg);
		}
	}

	void Pbo::CreateScreenQuad()
	{
		std::array<float, 16> vertData
		{
			//Position				//UV
			-1.0f,  1.0f,			0.0f, 1.0f,
			-1.0f, -1.0f,			0.0f, 0.0f,
			 1.0f,  1.0f,			1.0f, 1.0f,
			 1.0f, -1.0f,			1.0f, 0.0f
		};

		std::array<GLushort, 4> indices{ 0,1,2,3 };

		GLuint vbo;
		glCreateBuffers(1, &vbo);
		glNamedBufferStorage(vbo, sizeof(float) * vertData.size(),
			vertData.data(), GL_DYNAMIC_STORAGE_BIT);

		glCreateVertexArrays(1, &vao);
		glEnableVertexArrayAttrib(vao, 0);
		glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(float) * 4);
		glVertexArrayAttribFormat(vao, 0, 4, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayAttribBinding(vao, 0, 0);

		GLuint ebo;
		glCreateBuffers(1, &ebo);
		glNamedBufferStorage(ebo, sizeof(GLushort) * indices.size(),
			reinterpret_cast<GLvoid*>(indices.data()),
			GL_DYNAMIC_STORAGE_BIT);
		glVertexArrayElementBuffer(vao, ebo);
		glBindVertexArray(0);

		numIndices = static_cast<GLuint>(indices.size());
	}

	void Pbo::CreatePBO()
	{
		//Calculate num pixels
		int bytes = imgSize * sizeof(math::vec3);

		//Init PBO back buffer ID 
		glCreateBuffers(1, &pboBackID);
		glNamedBufferStorage(pboBackID, bytes, nullptr, GL_DYNAMIC_STORAGE_BIT | GL_MAP_WRITE_BIT);
		pboPtr = static_cast<math::vec3*>(glMapNamedBuffer(pboBackID, GL_WRITE_ONLY));
		LogAssert(pboPtr, "Unsuccessful PBO mapping!");
		glUnmapNamedBuffer(pboBackID);

		//Init PBO front buffer ID
		glCreateBuffers(1, &pboFrontID);
		glNamedBufferStorage(pboFrontID, bytes, nullptr, GL_DYNAMIC_STORAGE_BIT | GL_MAP_WRITE_BIT);
		pboPtr = static_cast<math::vec3*>(glMapNamedBuffer(pboFrontID, GL_WRITE_ONLY));
		LogAssert(pboPtr, "Unsuccessful PBO mapping!");
		glUnmapNamedBuffer(pboFrontID);

	}

	void Pbo::CreateTexture()
	{
		//Create screen size texture
		glCreateTextures(GL_TEXTURE_2D, 1, &texID);
		glTextureStorage2D(texID, 1, GL_RGB32F, imgWidth, imgHeight);
	}

	void Pbo::Accumulate()
	{
		math::vec3*pboFrontPtr = static_cast<math::vec3*>(glMapNamedBuffer(pboFrontID, GL_WRITE_ONLY));
		LogAssert(pboFrontPtr, "Unsuccessful PBO mapping!");
		float weight = 1.0f / (++totalFrames);

		std::for_each(std::execution::par, iter.begin(), iter.end(),
			[=](unsigned i)
			{
				pboPtr[i] = pboFrontPtr[i] * (1.0f - weight) + pboPtr[i] * weight;
			});

		glUnmapNamedBuffer(pboFrontID);
	}
}