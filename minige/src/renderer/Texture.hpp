#pragma once
#include "so.h"
#include <memory>
#include "platform/Image.hpp"

namespace gengine {
	namespace renderer {
		class SO_API Texture
		{
		private:
			struct Impl;
			std::unique_ptr<Impl> pImpl;
		public:
			Texture(const platform::Image* const image);
			~Texture();
			void bind() const;
			void unbind() const;
			const platform::Image& const getImage() const;
		};
	}
}