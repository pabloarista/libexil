#ifndef ExilTimer_h__
#define ExilTimer_h__

#include <Exil.h>
#include <windows.h>

namespace Exil
{
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

		U64 getTimeElapsed()
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