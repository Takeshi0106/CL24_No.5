#pragma once

// ===========================================
// Playerの立っている時の状態
// ===========================================

#include "State.h"

class PlayerStandingState :public PlayerState
{
private:
	int ParticleCnt = 0;
	bool m_AniFlag = false;

	void Animation(Player* _player);
public:
	PlayerStandingState();

	// インスタンスを渡すクラス
	static PlayerStandingState* GetInstance(); 

	// 状態の更新
	void Control(Player* _player);
	// 状態の開始処理
	void Enter(Player* _player);
	// 状態中の処理
	void Excute(Player* _player);
	// 状態の終了処理
	void Exit(Player* _player);
};

