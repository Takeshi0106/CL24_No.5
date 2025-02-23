#pragma once

// =============================
// 何も入力されていないときの状態
// =============================

#include "CharacterState.h"

class StandingState : public CharacterState
{
private:

public:
	// 状態を取得する
	static StandingState* GetInstance();
	// 状態を更新する
	void StateUpdate(Character*);
	// 状態の開始処理
	void Enter(Character*);
	// 状態中の処理
	void Excute(Character*);
	// 状態の終了処理
	void Exit(Character*);
};

