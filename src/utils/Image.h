#pragma once
#pragma warning(disable : 26812) // disabling a warning when including a header works normally for most warnings.
#include <GL/glew.h>
#include <FreeImage.h>

namespace gengine {
    class Image
    {
    private:
        // pointer to the image, once loaded
        FIBITMAP* bitmap = nullptr;
    public:
        Image(const char* filename);
        ~Image();

        // pointer to the image data
        const unsigned char const* getData() const;
        const unsigned int getWidth() const;
        const unsigned int getHeight() const;
    };
}