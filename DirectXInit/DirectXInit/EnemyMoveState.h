#pragma once
#include "EnemyState.h"

class EnemyMoveState: public EnemyState
{
private:
	int Cnt = 0;
	bool m_AniFlag = false;

	void Animation(Enemy* _enemy);
public:
	// インスタンスを渡すクラス
	static std::shared_ptr<EnemyMoveState> GetInstance();

	// 状態の更新
	void Control(Enemy* _enemy);
	// 状態の開始処理
	void Enter(Enemy* _enemy);
	// 状態中の処理
	void Excute(Enemy* _enemy);
	// 状態の終了処理
	void Exit(Enemy* _enemy);
};

