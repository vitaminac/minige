#pragma once
#include "geometry/geometry.h"
#include "../renderer/Renderer2D.h"

namespace gengine {
    namespace graphics {
        class Renderable2D
        {
        public:
            Renderable2D() = default;
            virtual ~Renderable2D() = default;
            virtual void render(Renderer2D* renderer) const = 0;

            // TODO: TO BE REMOVED
            virtual const geometry::vec3& getPosition() const { return geometry::vec3::ZERO; }
            virtual const geometry::vec2& getSize() const { return geometry::vec2::ZERO; }
            virtual const geometry::vec4& getColor() const { return geometry::vec4::ZERO; }
        };
    }
}