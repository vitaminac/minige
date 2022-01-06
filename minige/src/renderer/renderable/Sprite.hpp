#pragma once
#include "so.h"
#include "math/vec2.hpp"
#include "math/vec3.hpp"
#include "math/vec4.hpp"
#include "../Shader.hpp"
#include "Renderable2D.hpp"

namespace gengine {
	namespace renderer {
		class SO_API Sprite : public Renderable2D
		{
		protected:
			math::vec3 position;
			math::vec2 size;
			math::vec4 color;
		public:
			Sprite(float x, float y, float width, float height, const math::vec4& color);

			virtual void render(Renderer2D* renderer) const override;

			virtual const math::vec3& getPosition() const override { return position; }
			virtual const math::vec2& getSize() const override { return size; }
			virtual const math::vec4& getColor() const override { return color; }
		};
	}
}