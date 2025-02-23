#pragma once
#include "EnemyState.h"

class EnemyStopState: public EnemyState
{
private:

public:
	// �C���X�^���X��n���N���X
	static std::shared_ptr<EnemyStopState> GetInstance();

	// ��Ԃ̍X�V
	void Control(Enemy* _enemy);
	// ��Ԃ̊J�n����
	void Enter(Enemy* _enemy);
	// ��Ԓ��̏���
	void Excute(Enemy* _enemy);
	// ��Ԃ̏I������
	void Exit(Enemy* _enemy);
};

