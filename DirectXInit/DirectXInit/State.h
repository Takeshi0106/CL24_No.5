#pragma once

// ===============================
// Player�̏�ԃN���X
// ===============================

class Player;

class PlayerState
{
protected:

public:
	~PlayerState() {};
	// ��Ԃ̍X�V
	virtual void Control(Player* _player) = 0;
	// ��Ԃ̊J�n����
	virtual void Enter(Player* _player) = 0;
	// ��Ԓ��̏���
	virtual void Excute(Player* _player) = 0;
	// ��Ԃ̏I������
	virtual void Exit(Player* _player) = 0;
};

