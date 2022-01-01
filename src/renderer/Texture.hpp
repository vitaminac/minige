#pragma once
#include <GL/glew.h>
#include "platform/Image.hpp"

namespace gengine {
	namespace renderer {

		class Texture
		{
		private:
			GLuint tid;
			const platform::Image* const image;
		public:
			Texture(const platform::Image* const image);
			~Texture();
			void bind() const;
			void unbind() const;

			inline const platform::Image* const getImage() const { return image; }
		};
	}
}