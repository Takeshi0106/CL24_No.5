#pragma once

// ===========================================
// Player�̗����Ă��鎞�̏��
// ===========================================

#include "State.h"

class PlayerStandingState :public PlayerState
{
private:
	int ParticleCnt = 0;
	bool m_AniFlag = false;

	void Animation(Player* _player);
public:
	PlayerStandingState();

	// �C���X�^���X��n���N���X
	static PlayerStandingState* GetInstance(); 

	// ��Ԃ̍X�V
	void Control(Player* _player);
	// ��Ԃ̊J�n����
	void Enter(Player* _player);
	// ��Ԓ��̏���
	void Excute(Player* _player);
	// ��Ԃ̏I������
	void Exit(Player* _player);
};

