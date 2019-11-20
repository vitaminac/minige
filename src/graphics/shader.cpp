#include "shader.h"
#include <vector>
#include <sstream>
#include <iostream>

namespace gengine {
    namespace graphics {
        GLuint Shader::load()
        {
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

        Shader::Shader(const char* vertexPath, const char* fragmentPath) : vertexPath(vertexPath), fragmentPath(fragmentPath)
        {
            this->shaderID = this->load();
        }

        Shader::~Shader()
        {
            glDeleteProgram(this->shaderID);
        }

        void Shader::enable() const
        {
            glUseProgram(this->shaderID);
        }

        void Shader::disable() const
        {
            glUseProgram(0);
        }

        GLint Shader::getUniformLocation(const GLchar* name) const
        {
            return glGetUniformLocation(this->shaderID, name);
        }

        void Shader::setUniformInteger(const GLchar* name, const int value) const
        {
            glUniform1d(this->getUniformLocation(name), value);
        }

        void Shader::setUniformFloat(const GLchar* name, const float value) const
        {
            glUniform1f(this->getUniformLocation(name), value);
        }

        void Shader::setUniformVector2(const GLchar* name, const vec2& vector) const
        {
            glUniform2f(this->getUniformLocation(name), vector.x, vector.y);
        }

        void Shader::setUniformVector3(const GLchar* name, const vec3& vector) const
        {
            glUniform3f(this->getUniformLocation(name), vector.x, vector.y, vector.z);
        }

        void Shader::setUniformVector4(const GLchar* name, const vec4& vector) const
        {
            glUniform4f(this->getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
        }

        void Shader::setUniformMat4(const GLchar* name, const mat4& matrix) const
        {
            glUniformMatrix4fv(this->getUniformLocation(name), 1, GL_FALSE, matrix.elements);
        }
    }
}