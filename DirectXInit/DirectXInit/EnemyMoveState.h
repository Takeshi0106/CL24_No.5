#pragma once
#include "EnemyState.h"

class EnemyMoveState: public EnemyState
{
private:
	int Cnt = 0;
	bool m_AniFlag = false;

	void Animation(Enemy* _enemy);
public:
	// �C���X�^���X��n���N���X
	static std::shared_ptr<EnemyMoveState> GetInstance();

	// ��Ԃ̍X�V
	void Control(Enemy* _enemy);
	// ��Ԃ̊J�n����
	void Enter(Enemy* _enemy);
	// ��Ԓ��̏���
	void Excute(Enemy* _enemy);
	// ��Ԃ̏I������
	void Exit(Enemy* _enemy);
};

