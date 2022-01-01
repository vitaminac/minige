#pragma once
#include "Renderer2D.hpp"
#include "../buffers/VertexArrayObject.hpp"
#include "../buffers/VertexBufferObject.hpp"
#include "../buffers/IndexedVertexBufferObject.hpp"
#include "../renderable/Renderable2d.hpp"

namespace gengine {
	namespace renderer {

#define RENDERER_MAX_SPRITES	60000
#define RENDERER_VERTEX_SIZE	sizeof(VertexData)
#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE	RENDERER_MAX_SPRITES * 6

#define SHADER_VERTEX_INDEX 0
#define SHADER_COLOR_INDEX	1

		class BatchRenderer2D : public Renderer2D
		{
		private:
			VertexArrayObject vao;
			VertexBufferObject vbo;
			IndexedVertexBufferObject* ibo;
			GLsizei index_count;
			VertexData* buffer;
		public:
			BatchRenderer2D();
			~BatchRenderer2D();
			void begin() override;
			void submit(const Renderable2D* renderable) override;
			void end() override;
			void flush() override;
		};
	}
}