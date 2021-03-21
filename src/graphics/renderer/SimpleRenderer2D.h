#pragma once

#include <deque>
#include "Renderer2D.h"
#include "../renderable/Renderable2D.h"
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