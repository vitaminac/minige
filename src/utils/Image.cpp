#include "Image.h";

namespace gengine {
    Image::Image(const char* filename) {
        FREE_IMAGE_FORMAT image_format = FIF_UNKNOWN;
        image_format = FreeImage_GetFileType(filename, 0);
        if (image_format == FIF_UNKNOWN)
            image_format = FreeImage_GetFIFFromFilename(filename);
        if (image_format == FIF_UNKNOWN)
            throw "unknown image format";

        if (FreeImage_FIFSupportsReading(image_format))
            this->bitmap = FreeImage_Load(image_format, filename);
        if (!this->bitmap)
            throw "image load failed";
    }

    Image::~Image() {
        FreeImage_Unload(this->bitmap);
    }

    const unsigned char const* Image::getData() const {
        return  FreeImage_GetBits(this->bitmap);;
    }

    const unsigned int Image::getWidth() const {
        return FreeImage_GetWidth(this->bitmap);
    }

    const unsigned int Image::getHeight() const {
        return FreeImage_GetHeight(this->bitmap);
    }
}