#pragma once
#include "so.h"
#include "Renderer2D.hpp"
#include "../renderable/Renderable2D.hpp"

namespace gengine {
	namespace renderer {
		class SO_API BatchRenderer2D : public Renderer2D
		{
		private:
			struct Impl;
			std::unique_ptr<Impl> pImpl;
		public:
			BatchRenderer2D();
			~BatchRenderer2D();
			void begin() override;
			void submit(const Renderable2D* renderable) override;
			void end() override;
			void flush() override;
		};
	}
}