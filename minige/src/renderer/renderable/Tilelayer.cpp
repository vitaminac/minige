#include "TileLayer.hpp"

namespace gengine {
	using namespace math;

	namespace renderer {

		TileLayer::TileLayer(Shader* shader, const int content_width, const int content_height)
			: Layer(new BatchRenderer2D(), shader, mat4::orthographic(0, content_width, 0, content_height, -1.0f, 1.0f))
		{
		}

		TileLayer::~TileLayer()
		{
		}
	}
}