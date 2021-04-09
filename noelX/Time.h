#pragma once
#include<chrono>

class Time
{
public:
	Time();
	float getTime();
private:
	std::chrono::steady_clock::time_point last;
};