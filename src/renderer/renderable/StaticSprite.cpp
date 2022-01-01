#include "StaticSprite.hpp"

namespace gengine {
    using namespace math;

    namespace renderer {

        StaticSprite::StaticSprite(float x, float y, float width, float height, const vec4& color, Shader& shader)
            : Sprite(x, y, width, height, color), shader(shader)
        {
            this->vao = new VertexArrayObject();
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

            this->vbo_position = new VertexBufferObject(vertices, 4 * 3 * sizeof(GLfloat), GL_STATIC_DRAW);
            this->vao->addBuffer(this->vbo_position, 0, 3, GL_FLOAT, GL_FALSE, 0, 0);
            this->vbo_color = new VertexBufferObject(colors, 4 * 4 * sizeof(GLfloat), GL_STATIC_DRAW);
            this->vao->addBuffer(this->vbo_color, 1, 4, GL_FLOAT, GL_FALSE, 0, 0);

            GLuint indices[] = { 0, 1, 2, 2, 3, 0 };
            this->ibo = new IndexedVertexBufferObject(indices, 6);
        }

        StaticSprite::~StaticSprite()
        {
            delete vao;
            delete ibo;
            delete this->vbo_position;
            delete this->vbo_color;
        }

        void StaticSprite::render(Renderer2D* renderer) const
        {
            renderer->submit(this);
        }
    }
}