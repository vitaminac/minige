#pragma once
#pragma warning(disable : 26812) // disabling a warning when including a header works normally for most warnings.
#include <GL/glew.h>
#include <FreeImage.h>

namespace gengine {
    class Image
    {
    private:
        FIBITMAP* bitmap = nullptr;
    public:
        Image(const char* filename);
        ~Image();

        const unsigned char const* getData() const;
        const unsigned int getWidth() const;
        const unsigned int getHeight() const;
    };
}