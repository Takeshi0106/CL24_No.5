#pragma once
#include <memory>

// ===============================
// Enemyの状態クラス
// ===============================

class Enemy;

class EnemyState
{
protected:

public:
	~EnemyState() {};
	// 状態の更新
	virtual void Control(Enemy* _enemy) = 0;
	// 状態の開始処理
	virtual void Enter(Enemy* _enemy) = 0;
	// 状態中の処理
	virtual void Excute(Enemy* _enemy) = 0;
	// 状態の終了処理
	virtual void Exit(Enemy* _enemy) = 0;
};