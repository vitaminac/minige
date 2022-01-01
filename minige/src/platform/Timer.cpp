#include "Timer.hpp"
#include <Windows.h>

namespace gengine {
	namespace platform {
		Timer::Timer()
		{
			LARGE_INTEGER fq, start;
			QueryPerformanceFrequency(&fq);
			frequency = 1.0 / fq.QuadPart;
			QueryPerformanceCounter(&start);
			this->start = start.QuadPart;
		}

		void Timer::reset()
		{
			LARGE_INTEGER start;
			QueryPerformanceCounter(&start);
			this->start = start.QuadPart;
		}

		float Timer::elapsed()
		{
			LARGE_INTEGER current;
			QueryPerformanceCounter(&current);
			uint64_t cycles = current.QuadPart - this->start;
			return (float)(cycles * frequency);
		}
	};
}