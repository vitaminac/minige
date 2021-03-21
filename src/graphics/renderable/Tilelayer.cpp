#include "TileLayer.h"

namespace gengine {
    namespace graphics {

        TileLayer::TileLayer(Shader* shader, const int content_width, const int content_height)
            : Layer(new BatchRenderer2D(), shader, geometry::mat4::orthographic(0, content_width, 0, content_height, -1.0f, 1.0f))
        {
        }

        TileLayer::~TileLayer()
        {
        }
    }
}