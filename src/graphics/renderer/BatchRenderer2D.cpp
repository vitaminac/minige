#include "BatchRenderer2D.h"

namespace gengine {
    namespace graphics {
        BatchRenderer2D::BatchRenderer2D()
        {
            init();
        }

        BatchRenderer2D::~BatchRenderer2D()
        {
            delete ibo;
            glDeleteBuffers(1, &vbo);
            glDeleteVertexArrays(1, &vao);
        }

        void BatchRenderer2D::init()
        {
            glGenVertexArrays(1, &vao);
            glGenBuffers(1, &vbo);

            glBindVertexArray(vao);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
            glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
            glEnableVertexAttribArray(SHADER_COLOR_INDEX);
            glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
            glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::color)));
            glBindBuffer(GL_ARRAY_BUFFER, 0);

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

            ibo = new IndexedVertexBufferObject(indices, RENDERER_INDICES_SIZE);

            glBindVertexArray(0);
        }

        void BatchRenderer2D::begin()
        {
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
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
            buffer->vertex = getAccumulatedTransformation() * position;
            buffer->color = c;
            buffer++;

            buffer->vertex = getAccumulatedTransformation() * vec3(position.x, position.y + size.y, position.z);
            buffer->color = c;
            buffer++;

            buffer->vertex = getAccumulatedTransformation() * vec3(position.x + size.x, position.y + size.y, position.z);
            buffer->color = c;
            buffer++;

            buffer->vertex = getAccumulatedTransformation() * vec3(position.x + size.x, position.y, position.z);
            buffer->color = c;
            buffer++;

            index_count += 6;
        }

        void BatchRenderer2D::end()
        {
            glUnmapBuffer(GL_ARRAY_BUFFER);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        void BatchRenderer2D::flush()
        {
            glBindVertexArray(vao);
            ibo->bind();

            glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, NULL);

            ibo->unbind();
            glBindVertexArray(0);

            index_count = 0;
        }
    }
}