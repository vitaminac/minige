#pragma once
#include "math/vec2.hpp"
#include "math/vec3.hpp"
#include "math/vec4.hpp"
#include "../renderer/Renderer2D.hpp"

namespace gengine {
	namespace renderer {
		class Renderable2D
		{
		public:
			Renderable2D() = default;
			virtual ~Renderable2D() = default;
			virtual void render(Renderer2D* renderer) const = 0;

			// TODO: TO BE REMOVED
			virtual const math::vec3& getPosition() const { return math::vec3::ZERO; }
			virtual const math::vec2& getSize() const { return math::vec2::ZERO; }
			virtual const math::vec4& getColor() const { return math::vec4::ZERO; }
		};
	}
}