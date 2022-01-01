#pragma once
#include "../buffers/VertexBufferObject.hpp"
#include "../buffers/VertexArrayObject.hpp"
#include "../buffers/IndexedVertexBufferObject.hpp"
#include "Sprite.hpp"
#include "Renderable2d.hpp"

namespace gengine {
	namespace renderer {

		class StaticSprite : public Sprite
		{
		private:
			VertexArrayObject* vao;
			IndexedVertexBufferObject* ibo;
			VertexBufferObject* vbo_position;
			VertexBufferObject* vbo_color;
			Shader& shader;
		public:
			StaticSprite(float x, float y, float width, float height, const math::vec4& color, Shader& shader);
			~StaticSprite();

			virtual void render(Renderer2D* renderer) const override;
			inline const VertexArrayObject* getVAO() const { return vao; }
			inline const IndexedVertexBufferObject* getIBO() const { return ibo; }

			inline Shader& getShader() const { return shader; }
		};
	}
}