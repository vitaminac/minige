#pragma once
#include "../buffers/VertexBufferObject.h"
#include "../buffers/VertexArrayObject.h"
#include "../buffers/IndexedVertexBufferObject.h"
#include "Sprite.h"
#include "Renderable2d.h"

namespace gengine {
    namespace graphics {

        class StaticSprite : public Sprite
        {
        private:
            VertexArrayObject* vao;
            IndexedVertexBufferObject* ibo;
            VertexBufferObject* vbo_position;
            VertexBufferObject* vbo_color;
            Shader& shader;
        public:
            StaticSprite(float x, float y, float width, float height, const geometry::vec4& color, Shader& shader);
            ~StaticSprite();

            virtual void render(Renderer2D* renderer) const override;
            inline const VertexArrayObject* getVAO() const { return vao; }
            inline const IndexedVertexBufferObject* getIBO() const { return ibo; }

            inline Shader& getShader() const { return shader; }
        };
    }
}