#include "Time.h"
using namespace std::chrono;

Time::Time()
{
	last = steady_clock::now();
}

float Time::getTime()
{
	return duration<float>(steady_clock::now() - last).count();
}