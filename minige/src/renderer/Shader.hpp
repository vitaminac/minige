#pragma once
#include <string>
#include <GL/glew.h>
#include "math/vec2.hpp"
#include "math/vec3.hpp"
#include "math/mat4.hpp"
#include "physics/light.hpp"

namespace gengine {
	namespace renderer {
		class Shader {
		private:
			GLuint shaderID;
			const char* vertexPath;
			const char* fragmentPath;
			GLuint load();
			GLint getUniformLocation(const GLchar* name) const;
		public:
			Shader(const char* vertexPath, const char* fragmentPath);
			~Shader();

			void enable() const;
			void disable() const;

			inline const GLuint& getId() const {
				return this->shaderID;
			}

			void setUniformInteger(const GLchar* name, const int value) const;
			void setUniformFloat(const GLchar* name, const float value) const;
			void setUniformVector2(const GLchar* name, const math::vec2& vector) const;
			void setUniformVector3(const GLchar* name, const math::vec3& vector) const;
			void setUniformVector4(const GLchar* name, const math::vec4& vector) const;
			void setUniformMat4(const GLchar* name, const math::mat4& matrix) const;
			void setLight(const std::string& name, physics::Light light);
		};
	}
}