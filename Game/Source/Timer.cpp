// ----------------------------------------------------
// Fast timer with milisecons precision
// ----------------------------------------------------

#include "Timer.h"
#include "SDL\include\SDL_timer.h"
#include <chrono>
#include <cstdint>
#include <thread>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include "App.h"

	
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

void Timer::displayTime(int timeInSeconds) {
	int minutes = timeInSeconds / 60;
	int seconds = timeInSeconds % 60;
	std::string timeString = std::to_string(minutes) + ":";

	if (seconds < 10) {
		timeString += "0";
	}

	timeString += std::to_string(seconds);

	std::vector<int> time_vector;
	for (char c : timeString) {
		if (isdigit(c)) {
			time_vector.push_back(c - '0');
		}
	}

	int IconPosition = 70;
	for (int i = 0; i < time_vector.size(); i++) {
		int bufferSize = snprintf(nullptr, 0, "%d", time_vector[i]) + 1;
		char* pointStr = new char[bufferSize];
		snprintf(pointStr, bufferSize, "%d", time_vector[i]);
		app->fonts->BlitText(895 - IconPosition, 60, app->numbers, pointStr);
		IconPosition -= 16;
		if (IconPosition == 54) {
			IconPosition -= 16;
		}
	}
}