#include "Group.hpp"

namespace gengine {
	using namespace math;

	namespace renderer {
		Group::Group(const mat4& transform) : transform(transform)
		{
		}

		void Group::add(Renderable2D* renderable)
		{
			this->children.push_back(renderable);
		}

		void Group::render(Renderer2D* renderer) const
		{
			renderer->pushTransform(this->transform);

			for (const Renderable2D* renderable : children)
				renderable->render(renderer);

			renderer->popTransform();
		}
	}
}