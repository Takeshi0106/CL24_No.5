#pragma once
#include "EnemyState.h"

class EnemyStopState: public EnemyState
{
private:

public:
	// インスタンスを渡すクラス
	static std::shared_ptr<EnemyStopState> GetInstance();

	// 状態の更新
	void Control(Enemy* _enemy);
	// 状態の開始処理
	void Enter(Enemy* _enemy);
	// 状態中の処理
	void Excute(Enemy* _enemy);
	// 状態の終了処理
	void Exit(Enemy* _enemy);
};

