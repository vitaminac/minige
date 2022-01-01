#include "Sprite.hpp"

namespace gengine {
	using namespace math;

	namespace renderer {
		Sprite::Sprite(float x, float y, float width, float height, const vec4& color)
			: position(vec3(x, y, 0)), size(vec2(width, height)), color(color)
		{
		}

		void Sprite::render(Renderer2D* renderer) const
		{
			renderer->submit(this);
		}
	}
}