#pragma once
#include <GL/glew.h>
#include "utils/Image.h"

namespace gengine {
    namespace graphics {

        class Texture
        {
        private:
            GLuint tid;
            const Image* const image;
        public:
            Texture(const Image* const image);
            ~Texture();
            void bind() const;
            void unbind() const;

            inline const Image* const getImage() const { return image; }
        };
    }
}