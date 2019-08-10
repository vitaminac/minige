#include "tilelayer.h"

namespace gengine {
    namespace graphics {

        TileLayer::TileLayer(Shader* shader, const int content_width, const int content_height)
            : Layer(new BatchRenderer2D(), shader, geometry::mat4::orthographic(vec3(0, 0, -1.0f), vec3(content_width, content_height, 1.0f)))
        {
        }

        TileLayer::~TileLayer()
        {
        }
    }
}