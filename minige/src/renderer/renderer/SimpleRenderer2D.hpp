#pragma once

#include <deque>
#include "Renderer2D.hpp"
#include "../renderable/Renderable2D.hpp"
#include "../renderable/StaticSprite.hpp"

namespace gengine {
	namespace renderer {

		class Simple2DRenderer2D : public Renderer2D
		{
		private:
			std::deque<const StaticSprite*> queue;
		public:
			virtual void submit(const Renderable2D* renderable) override;
			virtual void flush() override;
			virtual void begin() override;
			virtual void end() override;
		};
	}
}