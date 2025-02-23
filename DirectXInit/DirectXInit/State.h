#pragma once

// ===============================
// Playerの状態クラス
// ===============================

class Player;

class PlayerState
{
protected:

public:
	~PlayerState() {};
	// 状態の更新
	virtual void Control(Player* _player) = 0;
	// 状態の開始処理
	virtual void Enter(Player* _player) = 0;
	// 状態中の処理
	virtual void Excute(Player* _player) = 0;
	// 状態の終了処理
	virtual void Exit(Player* _player) = 0;
};

