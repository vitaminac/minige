#include "Shader.hpp"

#include <map>
#include <vector>
#include <sstream>
#include <iostream>
#include <GL/glew.h>
#include "platform/FileUtils.hpp"

namespace gengine {
	using namespace math;
	using namespace physics;
	using namespace platform;

	namespace renderer {
		struct Shader::Impl {
			GLuint shaderID;
			const char* vertexPath;
			const char* fragmentPath;
			unsigned int nextTextureId;

			Impl(const char* vertexPath, const char* fragmentPath) : vertexPath(vertexPath), fragmentPath(fragmentPath), nextTextureId(0)
			{
				this->shaderID = this->load();
			}

			~Impl()
			{
				glDeleteProgram(this->shaderID);
			}

			GLuint load() {
				// generate a program object
				auto program = glCreateProgram();

				// generate vertex and fragment shader
				auto vertex = glCreateShader(GL_VERTEX_SHADER);
				auto fragment = glCreateShader(GL_FRAGMENT_SHADER);

				// load and compile shader
				std::string vertSourceString = FileUtils::read_file(this->vertexPath);
				std::string fragSourceString = FileUtils::read_file(this->fragmentPath);

				auto vertexSource = vertSourceString.c_str();
				auto fragmentSource = fragSourceString.c_str();

				GLint result;

				glShaderSource(vertex, 1, &vertexSource, NULL);
				glCompileShader(vertex);

				glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
				if (result == GL_FALSE) {
					GLint length;
					glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
					std::vector<char> error(length);
					glGetShaderInfoLog(vertex, length, &length, &error[0]);
					std::cout << &error[0] << std::endl;
					glDeleteShader(vertex);
					std::stringstream ss;
					ss << "Failed to compile " << this->vertexPath << std::endl;
					throw ss.str();
				}

				glShaderSource(fragment, 1, &fragmentSource, NULL);
				glCompileShader(fragment);

				glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
				if (result == GL_FALSE) {
					GLint length;
					glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
					std::vector<char> error(length);
					glGetShaderInfoLog(fragment, length, &length, &error[0]);
					std::cout << &error[0] << std::endl;
					glDeleteShader(fragment);
					std::stringstream ss;
					ss << "Failed to compile " << this->fragmentPath << std::endl;
					throw ss.str();
				}

				// attach both shaders to program object
				glAttachShader(program, vertex);
				glAttachShader(program, fragment);

				// ¨C link the shaders to the right programmable processor
				glLinkProgram(program);
				glValidateProgram(program);

				glDeleteShader(vertex);
				glDeleteShader(fragment);

				return program;
			}

			std::map<std::string, unsigned int> textureUniformNameToTextureUnitMap;
			GLint getUniformLocation(const std::string& name) const {
				return glGetUniformLocation(this->shaderID, name.c_str());
			}
		};

		Shader::Shader(const char* vertexPath, const char* fragmentPath) : pImpl(std::make_unique<Impl>(vertexPath, fragmentPath)) {
		}

		Shader::~Shader() = default;

		void Shader::enable() const
		{
			glUseProgram(this->pImpl->shaderID);
		}

		void Shader::disable() const
		{
			glUseProgram(0);
		}

		const unsigned int Shader::getId() const
		{
			return this->pImpl->shaderID;
		}

		void Shader::setUniformInteger(const std::string& name, const int value) const
		{
			glUniform1i(this->pImpl->getUniformLocation(name), value);
		}

		void Shader::setUniformFloat(const std::string& name, const float value) const
		{
			glUniform1f(this->pImpl->getUniformLocation(name), value);
		}

		void Shader::setUniformVector2(const std::string& name, const vec2& vector) const
		{
			glUniform2f(this->pImpl->getUniformLocation(name), vector.x, vector.y);
		}

		void Shader::setUniformVector3(const std::string& name, const vec3& vector) const
		{
			glUniform3f(this->pImpl->getUniformLocation(name), vector.x, vector.y, vector.z);
		}

		void Shader::setUniformVector4(const std::string& name, const vec4& vector) const
		{
			glUniform4f(this->pImpl->getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
		}

		void Shader::setUniformMat4(const std::string& name, const mat4& matrix) const
		{
			glUniformMatrix4fv(this->pImpl->getUniformLocation(name), 1, GL_FALSE, matrix.elements);
		}

		void Shader::setLight(const std::string& name, Light light) const
		{
			setUniformVector2((name + ".position").c_str(), light.position);
		}

		void Shader::setTexture(const std::string& name, const Texture& texture)
		{
			auto it = this->pImpl->textureUniformNameToTextureUnitMap.find(name);
			if (it == this->pImpl->textureUniformNameToTextureUnitMap.end()) {
				this->pImpl->textureUniformNameToTextureUnitMap.insert({ name, this->pImpl->nextTextureId });
			}

			const unsigned int textureUnit = (it == this->pImpl->textureUniformNameToTextureUnitMap.end()) ?
				this->pImpl->nextTextureId++ : it->second;
			glActiveTexture(GL_TEXTURE0 + textureUnit);
			texture.bind();
			this->setUniformInteger(name.c_str(), textureUnit);
		}
	}
}