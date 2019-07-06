#pragma once
#pragma once

#include "buffers/vbo.h"
#include "buffers/vao.h"

#include "../geometry/geometry.h"
#include "shader.h"

namespace gengine {
    namespace graphic {

        class Renderable2D
        {
        protected:
            vec3 position;
            vec2 size;
            vec4 color;

            VertexArrayObject* vao;
            IndexedVertexBufferObject* ibo;
            Shader& shader;
        public:
            Renderable2D(vec3 position, vec2 size, vec4 color, Shader& shader)
                : position(position), size(size), color(color), shader(shader)
            {
                this->vao = new VertexArrayObject();
                GLfloat vertices[] =
                {
                    0, 0, 0,
                    0, size.y, 0,
                    size.x, size.y, 0,
                    size.x, 0, 0
                };

                GLfloat colors[] =
                {
                    color.x, color.y, color.z, color.w,
                    color.x, color.y, color.z, color.w,
                    color.x, color.y, color.z, color.w,
                    color.x, color.y, color.z, color.w
                };

                vao->addBuffer(new VertexBufferObject(vertices, 4 * 3, 3), 0);
                vao->addBuffer(new VertexBufferObject(colors, 4 * 4, 4), 1);

                GLushort indices[] = { 0, 1, 2, 2, 3, 0 };
                ibo = new IndexedVertexBufferObject(indices, 6);
            }

            virtual ~Renderable2D()
            {
                delete vao;
                delete ibo;
            }

            inline const VertexArrayObject* getVAO() const { return vao; }
            inline const IndexedVertexBufferObject* getIBO() const { return ibo; }

            inline Shader& getShader() const { return shader; }

            inline const vec3& getPosition() const { return position; }
            inline const vec2& getSize() const { return size; }
            inline const vec4& getColor() const { return color; }
        };
    }
}