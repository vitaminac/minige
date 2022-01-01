#pragma once
#include <cstdint>

namespace gengine {
	namespace platform {
		class Timer
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