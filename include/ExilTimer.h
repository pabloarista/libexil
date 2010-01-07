#ifndef ExilTimer_h__
#define ExilTimer_h__

//#include <Exil.h>
#include <windows.h>

namespace Exil
{
		typedef unsigned long long uint64_t;
	class Timer
	{
	public:
		Timer()
		{
			QueryPerformanceFrequency(&ticksPerSecond);
			reset();
		}

		void reset()
		{
			QueryPerformanceCounter(&startTime);
			endTime = startTime;
		}

		uint64_t getTimeElapsed()
		{
			QueryPerformanceCounter(&endTime);
			return (endTime.QuadPart - startTime.QuadPart) * 1000 / ticksPerSecond.QuadPart;
		}

		LARGE_INTEGER startTime;
		LARGE_INTEGER endTime;
		LARGE_INTEGER ticksPerSecond;
	};
}//namespace Exil

#endif // ExilTimer_h__