#pragma once

#include "renderable2d.h"

namespace gengine {
    namespace graphic {

        class StaticSprite : public Renderable2D
        {
        private:
            VertexArrayObject* vao;
            IndexedVertexBufferObject* ibo;
            Shader& shader;
        public:
            StaticSprite(float x, float y, float width, float height, const vec4& color, Shader& shader);
            ~StaticSprite();

            inline const VertexArrayObject* getVAO() const { return vao; }
            inline const IndexedVertexBufferObject* getIBO() const { return ibo; }

            inline Shader& getShader() const { return shader; }
        };
    }
}