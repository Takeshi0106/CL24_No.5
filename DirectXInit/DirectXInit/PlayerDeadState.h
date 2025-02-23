#pragma once
#include "State.h"

class PlayerDeadState: public PlayerState
{
private:

public:
	// �C���X�^���X��n���N���X
	static PlayerDeadState* GetInstance();

	// ��Ԃ̍X�V
	void Control(Player* _player);
	// ��Ԃ̊J�n����
	void Enter(Player* _player);
	// ��Ԓ��̏���
	void Excute(Player* _player);
	// ��Ԃ̏I������
	void Exit(Player* _player);
};

