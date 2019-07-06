#pragma once

#include <GL/glew.h>
#include "../geometry/geometry.h"
#include "renderable2d.h"

namespace gengine {
    namespace graphic {

        class Renderer2D
        {
        public:
            virtual void submit(const Renderable2D* renderable) = 0;
            virtual void flush() = 0;
        };
    }
}