#pragma once

#include "layer.h"
#include "../BatchRenderer2D.h"

namespace gengine {
    namespace graphics {

        class TileLayer : public Layer
        {
        public:
            TileLayer(Shader* shader, const int content_width, const int content_height);
            ~TileLayer();
        };
    }
}