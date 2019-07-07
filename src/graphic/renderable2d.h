#pragma once
#pragma once

#include "buffers/vbo.h"
#include "buffers/vao.h"

#include "../geometry/geometry.h"
#include "shader.h"

namespace gengine {
    namespace graphic {
        struct VertexData
        {
            vec3 vertex;
            vec4 color;
        };

        class Renderable2D
        {
        protected:
            vec3 position;
            vec2 size;
            vec4 color;
        public:
            Renderable2D(vec3 position, vec2 size, vec4 color)
                : position(position), size(size), color(color)
            {
            }

            virtual ~Renderable2D() {}

            inline const vec3& getPosition() const { return position; }
            inline const vec2& getSize() const { return size; }
            inline const vec4& getColor() const { return color; }
        };
    }
}