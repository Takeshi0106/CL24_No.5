#include "StandingState.h"
#include "input.h"

// �C���X�^���X���擾����
StandingState* StandingState::GetInstance()
{
	static StandingState instance;
	return &instance;
}

// ��Ԃ��X�V����
void StandingState::StateUpdate(Character*)
{

}

// ��Ԃ̊J�n����
void StandingState::Enter(Character*)
{

}

// ��Ԓ��̏���
void StandingState::Excute(Character*)
{

}

// ��Ԃ̏I������
void StandingState::Exit(Character*)
{

}