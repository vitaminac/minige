#pragma once
#include "so.h"
#include "Layer.hpp"
#include "../renderer/BatchRenderer2D.hpp"

namespace gengine {
	namespace renderer {

		class SO_API TileLayer : public Layer
		{
		public:
			TileLayer(const Shader& shader, const int content_width, const int content_height);
			~TileLayer();
		};
	}
}