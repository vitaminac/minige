#include "BatchRenderer2D.hpp"

#include "math/vec2.hpp"
#include "../buffers/VertexArrayObject.hpp"
#include "../buffers/VertexBufferObject.hpp"
#include "../buffers/IndexedVertexBufferObject.hpp"

namespace gengine {
	using namespace math;

	namespace renderer {

#define RENDERER_MAX_SPRITES	60000
#define RENDERER_VERTEX_SIZE	sizeof(VertexData)
#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE	RENDERER_MAX_SPRITES * 6

#define SHADER_VERTEX_INDEX 0
#define SHADER_COLOR_INDEX	1

		struct BatchRenderer2D::Impl {
			VertexArrayObject vao;
			VertexBufferObject vbo;
			IndexedVertexBufferObject* ibo;
			GLsizei index_count;
			VertexData* buffer;

			Impl() : vao(VertexArrayObject()), vbo(VertexBufferObject(NULL, RENDERER_BUFFER_SIZE, GL_DYNAMIC_DRAW)) {
				GLuint* indices = new GLuint[RENDERER_INDICES_SIZE];

				int offset = 0;
				for (int i = 0; i < RENDERER_INDICES_SIZE; i += 6)
				{
					indices[i] = offset + 0;
					indices[i + 1] = offset + 1;
					indices[i + 2] = offset + 2;

					indices[i + 3] = offset + 2;
					indices[i + 4] = offset + 3;
					indices[i + 5] = offset + 0;

					offset += 4;
				}

				this->vao.addBuffer(&this->vbo, SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
				this->vao.addBuffer(&this->vbo, SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::color)));

				this->ibo = new IndexedVertexBufferObject(indices, RENDERER_INDICES_SIZE);
			}

			~Impl() {
				delete ibo;
			}
		};

		BatchRenderer2D::BatchRenderer2D() : pImpl(std::make_unique<Impl>())
		{
		}

		BatchRenderer2D::~BatchRenderer2D() = default;

		void BatchRenderer2D::begin()
		{
			this->pImpl->vbo.bind();
			this->pImpl->buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
			this->pImpl->index_count = 0;
		}

		void BatchRenderer2D::submit(const Renderable2D* renderable)
		{
			const vec3& position = renderable->getPosition();
			const vec2& size = renderable->getSize();
			const vec4& color = renderable->getColor();

			int r = color.x * 255.0f;
			int g = color.y * 255.0f;
			int b = color.z * 255.0f;
			int a = color.w * 255.0f;

			unsigned int c = a << 24 | b << 16 | g << 8 | r;

			// TODO: why we do the multiplication here and why not submitting as a model matrix
			this->pImpl->buffer->vertex = getAccumulatedTransformation() * position;
			this->pImpl->buffer->color = c;
			this->pImpl->buffer++;

			this->pImpl->buffer->vertex = getAccumulatedTransformation() * vec3(position.x, position.y + size.y, position.z);
			this->pImpl->buffer->color = c;
			this->pImpl->buffer++;

			this->pImpl->buffer->vertex = getAccumulatedTransformation() * vec3(position.x + size.x, position.y + size.y, position.z);
			this->pImpl->buffer->color = c;
			this->pImpl->buffer++;

			this->pImpl->buffer->vertex = getAccumulatedTransformation() * vec3(position.x + size.x, position.y, position.z);
			this->pImpl->buffer->color = c;
			this->pImpl->buffer++;

			this->pImpl->index_count += 6;
		}

		void BatchRenderer2D::end()
		{
			glUnmapBuffer(GL_ARRAY_BUFFER);
			this->pImpl->vbo.unbind();
		}

		void BatchRenderer2D::flush()
		{
			this->pImpl->vao.bind();
			this->pImpl->ibo->bind();

			glDrawElements(GL_TRIANGLES, this->pImpl->index_count, GL_UNSIGNED_INT, nullptr);

			this->pImpl->ibo->unbind();
			this->pImpl->vao.unbind();
		}
	}
}