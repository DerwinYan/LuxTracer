
#include <PboRenderer.h>
#include <shaderCode/screenQuad.h>
#include <Logger.h>
#include <string>
#include <GL/glew.h>
#include <array>
#include <Window.h>

namespace lux
{
	void PboRenderer::Init(int width, int height)
	{
		CreateShaderPgm();
		CreatePBO();
		CreateScreenQuad();
		CreateTexture();
	}

	void PboRenderer::SetClearColor(vec3 const& color)
	{

	}

	void PboRenderer::WritePixel(int x, int y, vec3 const& color)
	{

	}

	void PboRenderer::Render()
	{
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pboID);
		glTextureSubImage2D(texID, 0, 0, 0, Window::width, Window::height, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		glBindTextureUnit(0, texID);

		glUseProgram(shaderPgm);
		glBindVertexArray(vao);
		int uniformLocation = glGetUniformLocation(shaderPgm, "uTexture2D");
		glUniform1i(uniformLocation, 0);
		//shaderPgm.SetUniform("uTexture2D", 0);
		glDrawElements(GL_TRIANGLE_STRIP, numIndices, GL_UNSIGNED_SHORT, NULL);
		glBindVertexArray(0);
	}

	void PboRenderer::Free()
	{

	}


	void PboRenderer::CreateShaderPgm()
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

	void PboRenderer::CreateScreenQuad()
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

	void PboRenderer::CreatePBO()
	{
		//Calculate num pixels
		int pixelCount = Window::width * Window::height;
		int bytes = pixelCount * sizeof(unsigned);

		//Init PBO handle ID 
		glCreateBuffers(1, &pboID);
		glNamedBufferStorage(pboID, bytes, nullptr, GL_DYNAMIC_STORAGE_BIT | GL_MAP_WRITE_BIT);
		unsigned* pPbo = static_cast<unsigned*>(glMapNamedBuffer(pboID, GL_WRITE_ONLY));
		LogAssert(pPbo, "Unsuccessful PBO mapping!");

		//test clear color
		std::fill(pPbo, pPbo + pixelCount, 0xFF0000FF);
		glUnmapNamedBuffer(pboID);
	}

	void PboRenderer::CreateTexture()
	{
		//Create screen size texture
		glCreateTextures(GL_TEXTURE_2D, 1, &texID);
		glTextureStorage2D(texID, 1, GL_RGBA8, Window::width, Window::height);
	}



}