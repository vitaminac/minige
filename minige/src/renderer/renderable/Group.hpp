#pragma once
#include "so.h"
#include "Renderable2D.hpp"
#include "../renderer/Renderer2d.hpp"

namespace gengine {
	namespace renderer {

		class SO_API Group : public Renderable2D
		{
		private:
			std::vector<Renderable2D*> children;
			math::mat4 transform;
		public:
			Group(const math::mat4& transform);
			void add(Renderable2D* renderable);
			virtual void render(Renderer2D* renderer) const override;
		};
	}
}