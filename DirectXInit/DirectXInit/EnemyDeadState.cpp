#include "EnemyDeadState.h"
#include <memory>

// インスタンスを渡すクラス
std::shared_ptr<EnemyDeadState> EnemyDeadState::GetInstance()
{
	std::shared_ptr<EnemyDeadState> Instance = std::make_shared<EnemyDeadState>();
	return Instance;
}

// 状態の更新
void EnemyDeadState::Control(Enemy* _enemy)
{

}

// 状態の開始処理
void EnemyDeadState::Enter(Enemy* _enemy)
{

}
// 状態中の処理
void EnemyDeadState::Excute(Enemy* _enemy)
{

}

// 状態の終了処理
void EnemyDeadState::Exit(Enemy* _enemy)
{

}