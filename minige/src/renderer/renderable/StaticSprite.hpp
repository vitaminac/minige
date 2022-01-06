#pragma once
#include "so.h"
#include "Sprite.hpp"
#include "Renderable2d.hpp"

namespace gengine {
	namespace renderer {
		class SO_API StaticSprite : public Sprite
		{
		private:
			struct Impl;
			std::unique_ptr<Impl> pImpl;
		public:
			StaticSprite(float x, float y, float width, float height, const math::vec4& color, const Shader& shader);
			~StaticSprite();

			// TODO: REMOVE
			virtual void render(Renderer2D* renderer) const override;
			void render() const;
		};
	}
}