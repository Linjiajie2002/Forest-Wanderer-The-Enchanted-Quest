#ifndef __TIMER_H__
#define __TIMER_H__

#include "Defs.h"
#include "SDL\include\SDL_timer.h"
#include <chrono>
#include <cstdint>


class Timer
{
public:

	// Constructor
	Timer();

	void Start();
	uint32 ReadSec() const;
	uint32 CountDown(int total) const;
	float ReadMSec() const;


private:
	uint32 startTime;
};

#endif //__TIMER_H__