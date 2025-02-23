#include "Player.h"
#include "Game.h"
#include "input.h"
#include "ParticleManager.h"
#include "PlayerStandingState.h"

#include "PlayerSupearJumpState.h"

Player::Player()
{
	// ������
	//m_Size = { 100.0f,100.0f,0.0f };
    m_ColliderSize.x = m_Size.x * 0.7f;
    m_ColliderSize.y = m_Size.y;

	m_Gravity = { 0.0f,0.0f,0.0f };
	m_Velocity = { 0.0f,0.0f,0.0f };
	m_Pos = { 0.0f,0.0f,0.0f };

    TextureLoad(L"asset/pipo-halloweenchara2016_08.png", 3, 4);
    SetNum({ 1,2 });

	SetState(PlayerStandingState::GetInstance());
}

Player::~Player()
{
	
}

void Player::Update()
{
	// Player�̏�ԕύX
	m_PlayerState->Control(this);
	// Player�̏�ԍX�V
	m_PlayerState->Excute(this);

	// �d�͍X�V
	m_Gravity = m_GravityClass.Update(FallFlag);
	// Velocity�X�V
	Velocity();

	// �ʒu���X�V
	m_Pos = m_Pos + m_Gravity + m_Velocity ;
}

void Player::Draw()
{
	ObjectDraw();
}

void Player::Velocity()
{
	float decelerationPower = 0.45f;

	// �x�N�g���� XMVECTOR �ɕϊ�
	XMVECTOR vVel = XMLoadFloat3(&m_Velocity);

	// ���x�̑傫���̓����擾
	float speedSq = XMVectorGetX(XMVector3LengthSq(vVel));

	// ���x���\���ɏ������ꍇ�A�[���ɂ���
	if (speedSq < 0.2f)
	{
		m_Velocity = XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
	else
	{
		// �����������v�Z�i���K���j
		XMVECTOR vDeceleration = XMVectorNegate(vVel);
		vDeceleration = XMVector3Normalize(vDeceleration);

		// �����l��K�p
		XMVECTOR vAcceleration = XMVectorScale(vDeceleration, decelerationPower);
		vVel = XMVectorAdd(vVel, vAcceleration);

		// �V�������x�� XMFLOAT3 �ɕϊ�
		XMStoreFloat3(&m_Velocity, vVel);
	}
}

void Player::Overlap()
{
    // �d�͍X�V
    FallFlag = true;

    if (m_HitInformation.empty() || m_Alive == false)
    {
        return;
    }

    // �L�����N�^�[�̒��S���W�ƃT�C�Y
    DirectX::XMFLOAT2 charCenter = { m_Pos.x, m_Pos.y };
    DirectX::XMFLOAT2 charSize = { m_ColliderSize.x, m_ColliderSize.y };

    // X������Y�����̕␳��
    float adjustX = 0.0f;
    float adjustY = 0.0f;

    // Y�����̏Փ˂�D�悷��i�d�͂̉e�����l���j
    for (const auto& hit : m_HitInformation)
    {
        DirectX::XMFLOAT2 tileCenter = { hit.Pos.x, hit.Pos.y };
        DirectX::XMFLOAT2 tileSize = { hit.Size.x, hit.Size.y };
        TAG TileTag = hit.ObjectTAG;

        float diffX = (charCenter.x + charSize.x / 2) - (tileCenter.x + tileSize.x / 2);
        float diffY = (charCenter.y + charSize.y / 2) - (tileCenter.y + tileSize.y / 2);

        float enemyAdjust = (tileSize.x / 2 + charSize.x / 2) / 2;

        // X�����̕␳
        if (std::abs(diffX) > std::abs(diffY))
        {
            if (diffX > 0)
            {
                if (TileTag == ENEMY)
                {
                    m_Alive = false;
                    adjustX = std::max<float>(adjustX, tileCenter.x + enemyAdjust - m_Pos.x);
                }
                else
                {
                    adjustX = std::max<float>(adjustX, tileCenter.x + tileSize.x / 2 + charSize.x / 2 - m_Pos.x);
                }
            }
            else
            {
                if (TileTag == ENEMY)
                {
                    m_Alive = false;
                    adjustX = std::min<float>(adjustX, tileCenter.x - enemyAdjust - m_Pos.x);
                }
                else
                {
                    adjustX = std::min<float>(adjustX, tileCenter.x - tileSize.x / 2 - charSize.x / 2 - m_Pos.x);
                }
            }
        }
        // Y�����̕␳
        else
        {
            if (diffY > 0)
            {
                FallFlag = false; // ���n
                if (TileTag == ENEMY)
                {
                    m_Velocity.y += 6.25;
                    ChangeState(PlayerSupearJumpState::GetInstance());
                    adjustY = std::max<float>(adjustY, tileCenter.y + enemyAdjust - m_Pos.y);
                }
                else
                {
                    adjustY = std::max<float>(adjustY, tileCenter.y + tileSize.y / 2 + charSize.y / 2 - m_Pos.y);
                }
            }
            else
            {
                if (TileTag == ENEMY)
                {
                    m_Alive = false;
                    adjustY = std::min<float>(adjustY, tileCenter.y - enemyAdjust - m_Pos.y);
                }
                else
                {
                    adjustY = std::min<float>(adjustY, tileCenter.y - tileSize.y / 2 - charSize.y / 2 - m_Pos.y);
                }
            }
        }
    }

    // �ʒu�␳��K�p
    m_Pos.x += adjustX;
    m_Pos.y += adjustY;
}

void Player::InputControl()
{

}

void Player::ChangeState(PlayerState* _ChangState)
{
	m_PlayerState->Exit(this);
	m_PlayerState = _ChangState;
	m_PlayerState->Enter(this);
}

void Player::SetState(PlayerState* _ChangState)
{
	m_PlayerState = _ChangState;
}

void Player::SetVelocity(DirectX::XMFLOAT3 _Velocity)
{
	m_Velocity = _Velocity;
}

DirectX::XMFLOAT3 Player::GetVelocity()
{
	return m_Velocity;
}

bool Player::GameOver()
{
	if (-SCREEN_HEIGHT / 2 > m_Pos.y + m_Size.y)
	{
		return true;
	}
	return false;
}