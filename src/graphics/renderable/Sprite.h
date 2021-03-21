#pragma once
#include "geometry/geometry.h"
#include "../shader.h"
#include "Renderable2D.h"

namespace gengine {
    namespace graphics {
        class Sprite : public Renderable2D
        {
        protected:
            geometry::vec3 position;
            geometry::vec2 size;
            geometry::vec4 color;
        public:
            Sprite(float x, float y, float width, float height, const geometry::vec4& color);

            virtual void render(Renderer2D* renderer) const override;

            virtual const geometry::vec3& getPosition() const override { return position; }
            virtual const geometry::vec2& getSize() const override { return size; }
            virtual const geometry::vec4& getColor() const override { return color; }
        };
    }
}