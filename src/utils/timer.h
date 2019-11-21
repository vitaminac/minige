#pragma once
#include <Windows.h>

namespace gengine {
    class Timer
    {
    private:
        LARGE_INTEGER start;
        double frequency;
    public:
        Timer()
        {
            LARGE_INTEGER fq;
            QueryPerformanceFrequency(&fq);
            frequency = 1.0 / fq.QuadPart;
            QueryPerformanceCounter(&start);
        }

        void reset()
        {
            QueryPerformanceCounter(&start);
        }

        float elapsed()
        {
            LARGE_INTEGER current;
            QueryPerformanceCounter(&current);
            uint64_t cycles = current.QuadPart - start.QuadPart;
            return (float)(cycles * frequency);
        }
    };
}