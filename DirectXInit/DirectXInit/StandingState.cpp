#include "StandingState.h"
#include "input.h"

// インスタンスを取得する
StandingState* StandingState::GetInstance()
{
	static StandingState instance;
	return &instance;
}

// 状態を更新する
void StandingState::StateUpdate(Character*)
{

}

// 状態の開始処理
void StandingState::Enter(Character*)
{

}

// 状態中の処理
void StandingState::Excute(Character*)
{

}

// 状態の終了処理
void StandingState::Exit(Character*)
{

}