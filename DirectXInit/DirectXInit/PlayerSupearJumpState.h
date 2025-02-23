#pragma once
#include "State.h"

class PlayerSupearJumpState : public PlayerState
{
private:
	int cnt = 0;

public:
	// インスタンスを渡すクラス
	static PlayerSupearJumpState* GetInstance();

	// 状態の更新
	void Control(Player* _player);
	// 状態の開始処理
	void Enter(Player* _player);
	// 状態中の処理
	void Excute(Player* _player);
	// 状態の終了処理
	void Exit(Player* _player);
};

