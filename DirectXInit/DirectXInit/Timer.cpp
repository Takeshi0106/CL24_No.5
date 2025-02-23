#include "Timer.h"

LARGE_INTEGER Timer::frequency;
LARGE_INTEGER Timer::lastTime;
LARGE_INTEGER Timer::startTime;

void Timer::Init()
{
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&lastTime);
}

void Timer::Start()
{
  QueryPerformanceCounter(&startTime);
}

float Timer::GetDeltaTime()
{
  LARGE_INTEGER currentTime;
  QueryPerformanceCounter(&currentTime);
  float deltaTime = static_cast<float>(currentTime.QuadPart - lastTime.QuadPart) / frequency.QuadPart;
  lastTime = currentTime;
  return deltaTime;
}

float Timer::GetElapsedTime()
{
  LARGE_INTEGER currentTime;
  QueryPerformanceCounter(&currentTime);
  return static_cast<float>(currentTime.QuadPart - startTime.QuadPart) / frequency.QuadPart;
}

float Timer::GetElapsedTime(LARGE_INTEGER _startTime)
{
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);
	return static_cast<float>(currentTime.QuadPart - _startTime.QuadPart) / frequency.QuadPart;
}