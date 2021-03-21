#pragma once

#include <deque>
#include "Renderer2d.h"
#include "../renderable/Renderable2d.h"
#include "../renderable/StaticSprite.h"

namespace gengine {
    namespace graphics {

        class Simple2DRenderer : public Renderer2D
        {
        private:
            std::deque<const StaticSprite*> queue;
        public:
            void submit(const Renderable2D* renderable) override;
            void flush() override;
        };
    }
}