#include "PlayerJumpState.h"
#include "Player.h"
#include "PlayerStandingState.h"
#include "PlayerDeadState.h"

#include "ParticleManager.h"
#include "input.h"

// �C���X�^���X��n���N���X
PlayerJumpState* PlayerJumpState::GetInstance()
{
	static PlayerJumpState Instance;
	return &Instance;
}

// ��Ԃ̍X�V
void PlayerJumpState::Control(Player* _player)
{
	if (_player->GetAlive() == false)
	{
		_player->ChangeState(PlayerDeadState::GetInstance());
	}
	if (!_player->GetFallFlag())
	{
		_player->ChangeState(PlayerStandingState::GetInstance());
	}
}

// ��Ԃ̊J�n����
void PlayerJumpState::Enter(Player* _player)
{
	if (!_player->GetFallFlag())
	{
		// �W�����v�̃p���[��������
		DirectX::XMFLOAT3 playerVelocity = _player->GetVelocity();
		playerVelocity.y += 12.5f;
		_player->SetVelocity(playerVelocity);

		for (int i = 0; i < 5 + rand() % 5; i++)
		{
			// �p�[�e�B�N������
			ParticleManager::ParticleCreate({ _player->GetPos().x + _player->GetPlayerColliderSize().x / 2,
				_player->GetPos().y - _player->GetPlayerColliderSize().y / 2 + rand() % 5
				,0.0f },
				{ 10.0f,10.0f,10.0f },
				{ 1.0f, 1.0f, 1.0f, 1.0f }, DELETETIME_SANDSMOKE,
				{ 1.0f + rand() % 4,0.0f + rand() % 3,0.0f });
		}
		for (int i = 0; i < 5 + rand() % 5; i++)
		{
			// �p�[�e�B�N������
			ParticleManager::ParticleCreate({ _player->GetPos().x - _player->GetPlayerColliderSize().x / 2,
				_player->GetPos().y - _player->GetPlayerColliderSize().y / 2 + rand() % 5,
				0.0f },
				{ 10.0f,10.0f,10.0f },
				{ 1.0f, 1.0f, 1.0f, 1.0f }, DELETETIME_SANDSMOKE,
				{ -1.0f - rand() % 4,0.0f + rand() % 3,0.0f });
		}
	}
}

// ��Ԓ��̏���
void PlayerJumpState::Excute(Player* _player)
{
	DirectX::XMFLOAT3 PlayerPos = _player->GetPos();
	DirectX::XMFLOAT3 PlayerSize = _player->GetSize();

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
void PlayerJumpState::Exit(Player* _player)
{

}