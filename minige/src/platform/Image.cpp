#include "Image.hpp";

#include <FreeImage.h>

namespace gengine {
	namespace platform {
		struct Image::Impl {
			FIBITMAP* bitmap = nullptr;
		};

		Image::Image(const char* filename) {
			FREE_IMAGE_FORMAT image_format = FIF_UNKNOWN;
			// check the file signature and deduce its format
			image_format = FreeImage_GetFileType(filename, 0);
			if (image_format == FIF_UNKNOWN) {
				// if still unknown, try to guess the file format from the file extension
				image_format = FreeImage_GetFIFFromFilename(filename);
			}
			if (image_format == FIF_UNKNOWN) {
				// if still unkown, return failure
				throw "unknown image format";
			}

			// check that the plugin has reading capabilities and load the file
			if (FreeImage_FIFSupportsReading(image_format)) {
				this->pImpl = std::make_unique<Impl>(FreeImage_Load(image_format, filename));
			}

			// if the image failed to load, return failure
			if (!this->pImpl->bitmap) {
				throw "image load failed";
			}
		}

		Image::~Image() {
			FreeImage_Unload(this->pImpl->bitmap);
		}

		const unsigned char const* Image::getData() const {
			return FreeImage_GetBits(this->pImpl->bitmap);;
		}

		const unsigned int Image::getWidth() const {
			return FreeImage_GetWidth(this->pImpl->bitmap);
		}

		const unsigned int Image::getHeight() const {
			return FreeImage_GetHeight(this->pImpl->bitmap);
		}
	}
}