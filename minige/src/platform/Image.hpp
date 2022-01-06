#pragma once
#include "so.h"
#include <memory>

namespace gengine {
	namespace platform {
		class SO_API Image
		{
		private:
			// https://en.cppreference.com/w/cpp/language/pimpl
			struct Impl;
			std::unique_ptr <Impl> pImpl;
		public:
			Image(const char* filename);
			~Image();

			// pointer to the image data
			const unsigned char const* getData() const;
			const unsigned int getWidth() const;
			const unsigned int getHeight() const;
		};
	}
}