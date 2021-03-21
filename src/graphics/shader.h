#pragma once
#include <GL/glew.h>
#include "../geometry/geometry.h"
#include "../utils/fileutils.h"

namespace gengine {
    namespace graphics {
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
            void setUniformVector2(const GLchar* name, const geometry::vec2& vector) const;
            void setUniformVector3(const GLchar* name, const geometry::vec3& vector) const;
            void setUniformVector4(const GLchar* name, const geometry::vec4& vector) const;
            void setUniformMat4(const GLchar* name, const geometry::mat4& matrix) const;
        };
    }
}