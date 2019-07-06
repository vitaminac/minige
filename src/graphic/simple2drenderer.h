#pragma once

#include <deque>
#include "renderer2d.h"

namespace gengine {
    namespace graphic {

        class Simple2DRenderer : public Renderer2D
        {
        private:
            std::deque<const Renderable2D*> queue;
        public:
            void submit(const Renderable2D* renderable) override;
            void flush() override;
        };
    }
}