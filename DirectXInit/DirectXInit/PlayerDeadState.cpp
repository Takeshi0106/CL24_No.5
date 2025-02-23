#include "PlayerDeadState.h"
#include "Player.h"

// �C���X�^���X��n���N���X
PlayerDeadState* PlayerDeadState::GetInstance()
{
	static PlayerDeadState Instance;
	return &Instance;
}

// ��Ԃ̍X�V
void PlayerDeadState::Control(Player* _player)
{

}

// ��Ԃ̊J�n����
void PlayerDeadState::Enter(Player* _player)
{
	// �W�����v�̃p���[��������
	DirectX::XMFLOAT3 playerVelocity = _player->GetVelocity();
	playerVelocity.y = 15.0f;

	_player->SetColor({ 0.8627f, 0.0784f, 0.2353f, 1.0f });
	_player->SetVelocity(playerVelocity);
}

// ��Ԓ��̏���
void PlayerDeadState::Excute(Player* _player)
{

}

// ��Ԃ̏I������
void PlayerDeadState::Exit(Player* _player)
{

}