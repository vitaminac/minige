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
            virtual void submit(const Renderable2D* renderable) override;
            virtual void flush() override;
            virtual void begin() override;
            virtual void end() override;
        };
    }
}