#include "EnemyStopState.h"
#include "Enemy.h"
#include "EnemyDeadState.h"

// �C���X�^���X��n���N���X
std::shared_ptr<EnemyStopState> EnemyStopState::GetInstance()
{
	std::shared_ptr<EnemyStopState> Instance = std::make_shared<EnemyStopState>();
	return Instance;
}

// ��Ԃ̍X�V
void EnemyStopState::Control(Enemy* _enemy)
{
	if (_enemy->GetAlive() == false)
	{
		_enemy->SetState(EnemyDeadState::GetInstance());
	}
}

// ��Ԃ̊J�n����
void EnemyStopState::Enter(Enemy* _enemy)
{

}

// ��Ԓ��̏���
void EnemyStopState::Excute(Enemy* _enemy)
{

}

// ��Ԃ̏I������
void EnemyStopState::Exit(Enemy* _enemy)
{

}