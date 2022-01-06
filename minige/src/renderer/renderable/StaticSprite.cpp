#include "StaticSprite.hpp"

#include "../buffers/VertexBufferObject.hpp"
#include "../buffers/VertexArrayObject.hpp"
#include "../buffers/IndexedVertexBufferObject.hpp"

namespace gengine {
	using namespace math;

	namespace renderer {
		struct StaticSprite::Impl {
			VertexArrayObject* vao;
			IndexedVertexBufferObject* ibo;
			VertexBufferObject* vbo_position;
			VertexBufferObject* vbo_color;
			const Shader& shader;

			Impl(const Shader& shader) : shader(shader) {
			}

			~Impl() {
				delete vao;
				delete ibo;
				delete this->vbo_position;
				delete this->vbo_color;
			}
		};

		StaticSprite::StaticSprite(float x, float y, float width, float height, const vec4& color, const Shader& shader)
			: Sprite(x, y, width, height, color), pImpl(std::make_unique<Impl>(shader))
		{
			this->pImpl->vao = new VertexArrayObject();
			GLfloat vertices[] =
			{
				0, 0, 0,
				0, height, 0,
				width, height, 0,
				width, 0, 0
			};

			GLfloat colors[] =
			{
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w
			};

			this->pImpl->vbo_position = new VertexBufferObject(vertices, 4 * 3 * sizeof(GLfloat), GL_STATIC_DRAW);
			this->pImpl->vao->addBuffer(this->pImpl->vbo_position, 0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			this->pImpl->vbo_color = new VertexBufferObject(colors, 4 * 4 * sizeof(GLfloat), GL_STATIC_DRAW);
			this->pImpl->vao->addBuffer(this->pImpl->vbo_color, 1, 4, GL_FLOAT, GL_FALSE, 0, 0);

			GLuint indices[] = { 0, 1, 2, 2, 3, 0 };
			this->pImpl->ibo = new IndexedVertexBufferObject(indices, 6);
		}

		StaticSprite::~StaticSprite() = default;

		void StaticSprite::render(Renderer2D* renderer) const
		{
			renderer->submit(this);
		}

		void StaticSprite::render() const
		{
			this->pImpl->vao->bind();
			this->pImpl->ibo->bind();

			this->pImpl->shader.setUniformMat4("model_matrix", mat4::translation(this->getPosition()));
			glDrawElements(GL_TRIANGLES, this->pImpl->ibo->getCount(), GL_UNSIGNED_INT, nullptr);

			this->pImpl->ibo->unbind();
			this->pImpl->vao->unbind();
		}
	}
}