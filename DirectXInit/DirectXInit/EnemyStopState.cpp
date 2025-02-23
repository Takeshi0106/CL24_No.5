#include "EnemyStopState.h"
#include "Enemy.h"
#include "EnemyDeadState.h"

// インスタンスを渡すクラス
std::shared_ptr<EnemyStopState> EnemyStopState::GetInstance()
{
	std::shared_ptr<EnemyStopState> Instance = std::make_shared<EnemyStopState>();
	return Instance;
}

// 状態の更新
void EnemyStopState::Control(Enemy* _enemy)
{
	if (_enemy->GetAlive() == false)
	{
		_enemy->SetState(EnemyDeadState::GetInstance());
	}
}

// 状態の開始処理
void EnemyStopState::Enter(Enemy* _enemy)
{

}

// 状態中の処理
void EnemyStopState::Excute(Enemy* _enemy)
{

}

// 状態の終了処理
void EnemyStopState::Exit(Enemy* _enemy)
{

}