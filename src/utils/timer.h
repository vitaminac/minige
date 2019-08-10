#pragma once
#include <Windows.h>

namespace gengine {
    class Timer
    {
    private:
        LARGE_INTEGER m_Start;
        double m_Frequency;
    public:
        Timer()
        {
            LARGE_INTEGER frequency;
            QueryPerformanceFrequency(&frequency);
            m_Frequency = 1.0 / frequency.QuadPart;
            QueryPerformanceCounter(&m_Start);
        }

        void reset()
        {
            QueryPerformanceCounter(&m_Start);
        }

        float elapsed()
        {
            LARGE_INTEGER current;
            QueryPerformanceCounter(&current);
            uint64_t cycles = current.QuadPart - m_Start.QuadPart;
            return (float)(cycles * m_Frequency);
        }
    };
}