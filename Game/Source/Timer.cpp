// ----------------------------------------------------
// Fast timer with milisecons precision
// ----------------------------------------------------

#include "Timer.h"
#include "SDL\include\SDL_timer.h"
#include <chrono>
#include <cstdint>
#include <thread>
	
Timer::Timer()
{
	Start();
}

void Timer::Start()
{
	startTime = SDL_GetTicks();
}

uint32 Timer::ReadSec() const
{
	return (SDL_GetTicks() - startTime) / 1000;
}


uint32 Timer::CountDown(int total) const
{
	if (total == 0) {
		total = 0;
	}

	return total - (SDL_GetTicks() - startTime) / 1000;
}

float Timer::ReadMSec() const
{
	return (float)(SDL_GetTicks() - startTime);
}
