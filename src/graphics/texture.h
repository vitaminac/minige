#pragma once
#include <string>
#include <GL/glew.h>

namespace gengine {
    namespace graphics {

        class Texture
        {
        private:
            std::string filename;
            GLuint tid;
            GLsizei width, height;
        public:
            Texture(const std::string& filename);
            ~Texture();
            void bind() const;
            void unbind() const;

            inline const unsigned int getWidth() const { return width; }
            inline const unsigned int getHeight() const { return height; }
        };
    }
}