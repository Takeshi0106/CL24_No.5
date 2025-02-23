#include "PlayerStandingState.h"
#include "Player.h"
#include "PlayerJumpState.h"
#include "PlayerDeadState.h"

#include "ParticleManager.h"
#include "input.h"

#include<stdio.h>
#include<time.h>

// �R���X�g���N�^
PlayerStandingState::PlayerStandingState()
{
	srand((unsigned)time(NULL));
}

// �C���X�^���X��n���N���X
PlayerStandingState* PlayerStandingState::GetInstance()
{
	static PlayerStandingState Instance;
	return &Instance;
}

// ��Ԃ̍X�V
void PlayerStandingState::Control(Player* _player)
{
	if (_player->GetAlive() == false)
	{
		_player->ChangeState(PlayerDeadState::GetInstance());
	}
	if (Input::GetKeyTrigger(VK_SPACE) || _player->GetFallFlag())
	{
		_player->ChangeState(PlayerJumpState::GetInstance());
	}
}

// ��Ԃ̊J�n����
void PlayerStandingState::Enter(Player* _player)
{

}

// ��Ԓ��̏���
void PlayerStandingState::Excute(Player* _player)
{
	int Flag = 0;
	DirectX::XMFLOAT3 PlayerPos = _player->GetPos();
	DirectX::XMFLOAT3 PlayerSize = _player->GetSize();

	// 
	if (Input::GetKeyPress(VK_A) && -SCREEN_WIDTH / 2 < PlayerPos.x - PlayerSize.x / 2)
	{
		Flag++;

		PlayerPos.x -= 5.0f;

		_player->SetNum({ _player->GetNum().numU,1 });
		if (ParticleCnt > 2 && !_player->GetFallFlag())
		{
			// �p�[�e�B�N������
			ParticleManager::ParticleCreate(
				{ _player->GetPos().x + _player->GetPlayerColliderSize().x / 2 - 8.0f + rand() % 5,
				_player->GetPos().y - _player->GetPlayerColliderSize().y / 2 + 3.0f + rand() % 5,
				0.0f },
				{ 10.0f,10.0f,10.0f },
				{ 1.0f, 1.0f, 1.0f, 1.0f },
				DELETETIME_SANDSMOKE,
				{ 0.1f + rand() % 4, 1.0f + rand() % 3, 0.0f });

			// �A�j���[�V����
			Animation(_player);

			ParticleCnt = 0;
		}
	}
	if (Input::GetKeyPress(VK_D))
	{
		Flag++;

		PlayerPos.x += 5.0f;

		_player->SetNum({ _player->GetNum().numU,2 });
		if (ParticleCnt > 2 && !_player->GetFallFlag())
		{
			// �p�[�e�B�N������
			ParticleManager::ParticleCreate(
				{ _player->GetPos().x - _player->GetPlayerColliderSize().x / 2 - 8.0f + rand() % 5,
				_player->GetPos().y - _player->GetPlayerColliderSize().y / 2 + 3.0f + rand() % 5,
				0.0f },
				{ 10.0f,10.0f,10.0f },
				{ 1.0f, 1.0f, 1.0f, 1.0f },
				DELETETIME_SANDSMOKE,
				{ -0.1f - rand() % 4,1.0f + rand() % 3,0.0f });

			// �A�j���[�V����
			Animation(_player);

			ParticleCnt = 0;
		}
	}

	if (Flag == 1)
	{
		ParticleCnt++;
	}
	else
	{
		ParticleCnt = 0;
	}

	// Velocity���X�V
	_player->SetPos(PlayerPos);
}

// ��Ԃ̏I������
void PlayerStandingState::Exit(Player* _player)
{

}

void PlayerStandingState::Animation(Player* _player)
{
	NUM num = _player->GetNum();

	if (m_AniFlag)
	{
		num.numU++;
		if (num.numU >= 2)
		{
			m_AniFlag = !m_AniFlag;
		}
	}
	else
	{
		num.numU--;
		if (num.numU <= 0)
		{
			m_AniFlag = !m_AniFlag;
		}
	}

	_player->SetNum(num);
}
