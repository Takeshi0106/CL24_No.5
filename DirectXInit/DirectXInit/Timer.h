#pragma once
#include <Windows.h>
#include <iostream>

class Timer
{
private:
  static LARGE_INTEGER frequency;
  static LARGE_INTEGER lastTime;
  static LARGE_INTEGER startTime;

public:
  static void Init();
  // ゲーム開始時間を記録
  static void Start();
  // ゲーム開始からの時間
  static float GetElapsedTime();
  static float GetElapsedTime(LARGE_INTEGER _startTime);
  // 1フレームの経過時間を返す
  static float GetDeltaTime();
};