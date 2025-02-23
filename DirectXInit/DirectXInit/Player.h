#pragma once

// ============================
// �v���C���[�̃N���X
// ============================

#include "Character.h"
#include "State.h"

#define DELETETIME_SANDSMOKE (0.3f)

class Player : public Character 
{
private:
	// �ړ�������ϐ�
	DirectX::XMFLOAT3 m_Velocity;

	// Player�̏�Ԃ�����
	PlayerState* m_PlayerState;

	// �����x�v�Z�p 
	void Velocity();

public:
	Player();
	~Player();

	void Update();
	void Draw();

	void Overlap();

	// State
	void InputControl();
	void ChangeState(PlayerState* _ChangeState);
	void SetState(PlayerState* _ChangeState);

	// �Z�b�^�[�E�Q�b�^�[
	void SetVelocity(DirectX::XMFLOAT3 _Velocity);
	DirectX::XMFLOAT3 GetVelocity();

	bool GameOver();
};

