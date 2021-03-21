#pragma once
#include "geometry/geometry.h"

namespace gengine {
    namespace graphics {
        typedef struct ScreenPosition {
            double x;
            double y;
        } ScreenPosition;

        typedef struct Light {
            geometry::vec2 position;
        };
    }
}