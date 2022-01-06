#include "Texture.hpp"
#include <GL/glew.h>

namespace gengine {
	using namespace platform;

	namespace renderer {

		struct Texture::Impl {
			GLuint tid;
			const platform::Image* const image;
		};

		Texture::Texture(const Image* const image)
		{
			GLuint tid;
			glGenTextures(1, &tid);
			this->pImpl = std::make_unique<Impl>(tid, image);
			this->bind();
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexImage2D(GL_TEXTURE_2D, 0,
				// Specifies the number of color components in the texture.
				GL_RGBA,
				image->getWidth(), image->getHeight(), 0,
				// Specifies the format of the pixel data. The following symbolic values are accepted: 
				// GL_RED, GL_RG, GL_RGB, GL_BGR, GL_RGBA, GL_BGRA, GL_RED_INTEGER, GL_RG_INTEGER, GL_RGB_INTEGER, GL_BGR_INTEGER, GL_RGBA_INTEGER, GL_BGRA_INTEGER, GL_STENCIL_INDEX, GL_DEPTH_COMPONENT, GL_DEPTH_STENCIL.
				GL_BGRA,
				GL_UNSIGNED_BYTE, image->getData());
			this->unbind();
		}

		Texture::~Texture() = default;

		// bind texture to current texture unit defined by glActiveTexture(GL_TEXTURE{i}); which i is a integer from 0 to at least 80
		void Texture::bind() const
		{
			glBindTexture(GL_TEXTURE_2D, this->pImpl->tid);
		}

		void Texture::unbind() const
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		const platform::Image& const Texture::getImage() const
		{
			return *this->pImpl->image;
		}
	}
}