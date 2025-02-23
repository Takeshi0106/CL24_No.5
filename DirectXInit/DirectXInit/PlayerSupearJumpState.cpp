#include "PlayerSupearJumpState.h"
#include "Player.h"
#include "PlayerJumpState.h"

#include "input.h"

// �C���X�^���X��n���N���X
PlayerSupearJumpState* PlayerSupearJumpState::GetInstance()
{
	static PlayerSupearJumpState Instance;
	return &Instance;
}

// ��Ԃ̍X�V
void PlayerSupearJumpState::Control(Player* _player)
{
	if (cnt > 10)
	{
		_player->ChangeState(PlayerJumpState::GetInstance());
	}
}

// ��Ԃ̊J�n����
void PlayerSupearJumpState::Enter(Player* _player)
{
	cnt = 0;
}

// ��Ԓ��̏���
void PlayerSupearJumpState::Excute(Player* _player)
{
	cnt++;
	DirectX::XMFLOAT3 PlayerPos = _player->GetPos();
	DirectX::XMFLOAT3 PlayerSize = _player->GetSize();

	if (Input::GetKeyTrigger(VK_SPACE))
	{
		// �W�����v�̃p���[��������
		DirectX::XMFLOAT3 playerVelocity = _player->GetVelocity();
		playerVelocity.y += 12.5f;
		_player->SetVelocity(playerVelocity);
	}

	if (Input::GetKeyPress(VK_A) && -SCREEN_WIDTH / 2 < PlayerPos.x - PlayerSize.x / 2)
	{
		PlayerPos.x -= 2.5f;
	}
	if (Input::GetKeyPress(VK_D))
	{
		PlayerPos.x += 2.5f;
	}

	_player->SetPos(PlayerPos);
}

// ��Ԃ̏I������
void PlayerSupearJumpState::Exit(Player* _player)
{

}