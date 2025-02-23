#include "EnemyMoveState.h"
#include "Enemy.h"
#include "EnemyDeadState.h"
#include <memory>

// インスタンスを渡すクラス
std::shared_ptr<EnemyMoveState> EnemyMoveState::GetInstance()
{
	std::shared_ptr<EnemyMoveState> Instance = std::make_shared<EnemyMoveState>();
	return Instance;
}

// 状態の更新
void EnemyMoveState::Control(Enemy* _enemy)
{
	if (_enemy->GetAlive() == false)
	{
		_enemy->SetState(EnemyDeadState::GetInstance());
	}
}

// 状態の開始処理
void EnemyMoveState::Enter(Enemy* _enemy)
{

}

// 状態中の処理
void EnemyMoveState::Excute(Enemy* _enemy)
{
	int Flag = 0;

	if (_enemy->GetFallFlag() == false)
	{
		DirectX::XMFLOAT3 enemyPos = _enemy->GetPos();
		DirectX::XMFLOAT3 enemySize = _enemy->GetSize();

		if (_enemy->GetCourse() == RIGHT)
		{
			enemyPos.x += 2.5f;
			Flag++;

			_enemy->SetNum({ _enemy->GetNum().numU,2 });

			if (Cnt > 2)
			{
				Animation(_enemy);
				Cnt = 0;
			}

			if (SCREEN_WIDTH / 2 < enemyPos.x + enemySize.x / 2)
			{
				_enemy->SetCourse(LEFT);
			}
		}
		else if (_enemy->GetCourse() == LEFT)
		{
			enemyPos.x -= 2.5f;
			Flag++;

			_enemy->SetNum({ _enemy->GetNum().numU,1 });

			if (Cnt > 2)
			{
				Animation(_enemy);
				Cnt = 0;
			}

			if (-SCREEN_WIDTH / 2 > enemyPos.x - enemySize.x / 2)
			{
				_enemy->SetCourse(RIGHT);
			}
		}

		_enemy->SetPos(enemyPos);
	}

	if (Flag == 1)
	{
		Cnt++;
	}
	else
	{
		Cnt = 0;
	}
	
}

// 状態の終了処理
void EnemyMoveState::Exit(Enemy* _enemy)
{

}

void EnemyMoveState::Animation(Enemy* _enemy)
{
	NUM num = _enemy->GetNum();

	if (m_AniFlag)
	{
		num.numU++;
		if (num.numU >= 2)
		{
			m_AniFlag = !m_AniFlag;
		}
	}
	else
	{
		num.numU--;
		if (num.numU <= 0)
		{
			m_AniFlag = !m_AniFlag;
		}
	}

	_enemy->SetNum(num);
}