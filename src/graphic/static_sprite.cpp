#include "static_sprite.h"

namespace gengine {
    namespace graphic {

        StaticSprite::StaticSprite(float x, float y, float width, float height, const vec4& color, Shader& shader)
            : Renderable2D(vec3(x, y, 0), vec2(width, height), color), shader(shader)
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

            this->vao->addBuffer(new VertexBufferObject(vertices, 4 * 3, 3), 0);
            this->vao->addBuffer(new VertexBufferObject(colors, 4 * 4, 4), 1);

            GLushort indices[] = { 0, 1, 2, 2, 3, 0 };
            this->ibo = new IndexedVertexBufferObject(indices, 6);
        }

        StaticSprite::~StaticSprite()
        {
            delete vao;
            delete ibo;
        }
    }
}