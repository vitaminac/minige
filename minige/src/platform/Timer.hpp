#pragma once
#include "so.h"
#include <cstdint>

namespace gengine {
	namespace platform {
		class SO_API Timer
		{
		private:
			int64_t start;
			double frequency;
		public:
			Timer();

			void reset();

			float elapsed();
		};
	}
}