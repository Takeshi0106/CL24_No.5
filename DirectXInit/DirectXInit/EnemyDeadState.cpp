#include "EnemyDeadState.h"
#include <memory>

// �C���X�^���X��n���N���X
std::shared_ptr<EnemyDeadState> EnemyDeadState::GetInstance()
{
	std::shared_ptr<EnemyDeadState> Instance = std::make_shared<EnemyDeadState>();
	return Instance;
}

// ��Ԃ̍X�V
void EnemyDeadState::Control(Enemy* _enemy)
{

}

// ��Ԃ̊J�n����
void EnemyDeadState::Enter(Enemy* _enemy)
{

}
// ��Ԓ��̏���
void EnemyDeadState::Excute(Enemy* _enemy)
{

}

// ��Ԃ̏I������
void EnemyDeadState::Exit(Enemy* _enemy)
{

}