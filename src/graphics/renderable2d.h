#pragma once

#include "buffers/vbo.h"
#include "buffers/vao.h"

#include "geometry/geometry.h"
#include "shader.h"
#include "renderer2d.h"

namespace gengine {
    namespace graphics {
        struct VertexData
        {
            vec3 vertex;
            unsigned int color;
        };

        class Renderable2D
        {
        protected:
            vec3 position;
            vec2 size;
            vec4 color;
            Renderable2D() :position(vec3::ZERO), size(vec2::ZERO), color(vec4::ZERO) {
            }
        public:
            Renderable2D(vec3 position, vec2 size, vec4 color)
                : position(position), size(size), color(color)
            {
            }

            virtual ~Renderable2D() {}

            virtual void submit(Renderer2D* renderer) const
            {
                renderer->submit(this);
            }

            inline const vec3& getPosition() const { return position; }
            inline const vec2& getSize() const { return size; }
            inline const vec4& getColor() const { return color; }
        };
    }
}