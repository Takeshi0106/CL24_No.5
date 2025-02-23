#pragma once
#include "State.h"

class PlayerSupearJumpState : public PlayerState
{
private:
	int cnt = 0;

public:
	// �C���X�^���X��n���N���X
	static PlayerSupearJumpState* GetInstance();

	// ��Ԃ̍X�V
	void Control(Player* _player);
	// ��Ԃ̊J�n����
	void Enter(Player* _player);
	// ��Ԓ��̏���
	void Excute(Player* _player);
	// ��Ԃ̏I������
	void Exit(Player* _player);
};

