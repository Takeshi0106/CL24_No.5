#pragma once

// =============================
// �������͂���Ă��Ȃ��Ƃ��̏��
// =============================

#include "CharacterState.h"

class StandingState : public CharacterState
{
private:

public:
	// ��Ԃ��擾����
	static StandingState* GetInstance();
	// ��Ԃ��X�V����
	void StateUpdate(Character*);
	// ��Ԃ̊J�n����
	void Enter(Character*);
	// ��Ԓ��̏���
	void Excute(Character*);
	// ��Ԃ̏I������
	void Exit(Character*);
};

