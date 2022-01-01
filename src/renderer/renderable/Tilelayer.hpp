#pragma once

#include "Layer.hpp"
#include "../renderer/BatchRenderer2D.hpp"

namespace gengine {
	namespace renderer {

		class TileLayer : public Layer
		{
		public:
			TileLayer(Shader* shader, const int content_width, const int content_height);
			~TileLayer();
		};
	}
}