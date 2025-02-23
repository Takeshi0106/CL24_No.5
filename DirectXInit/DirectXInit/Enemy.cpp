#include "Enemy.h"
#include "EnemyStopState.h"
#include "EnemyMoveState.h"

#include <algorithm>
#include<stdio.h>
#include<time.h>

Enemy::Enemy()
{
	// ������
    m_Size = { 100.0f,100.0f,70.0f };

    m_ColliderSize.x = m_Size.x * 0.8f;
    m_ColliderSize.y = m_Size.y;

	m_Gravity = { 0.0f,0.0f,0.0f };
    m_Color = { 1.0f,1.0f,1.0f,1.0f };

    TextureLoad(L"asset/pipo-simpleenemy01j.png", 3, 4);
    SetNum({ 1,1 });

    SetState(EnemyMoveState::GetInstance());
}

Enemy::~Enemy()
{

}

void Enemy::Update()
{
    // Enemy�̏�ԕύX
    m_EnemyState->Control(this);
    // Enemy�̏�ԍX�V
    m_EnemyState->Excute(this);

	// �d�͍X�V
	m_Gravity = m_GravityClass.Update(FallFlag);
	// �ʒu���X�V
	m_Pos = m_Pos + m_Gravity;
}

void Enemy::Draw()
{
	ObjectDraw();
}

void Enemy::InputControl()
{

}

void Enemy::ChangeState(std::shared_ptr<EnemyState> _ChangState)
{
    m_EnemyState->Exit(this);
    m_EnemyState = _ChangState;
    m_EnemyState->Enter(this);
}

void Enemy::SetState(std::shared_ptr<EnemyState> _ChangState)
{
    m_EnemyState = _ChangState;
}

void Enemy::Overlap()
{
    // �d�͍X�V
    FallFlag = true;
    bool hasGround = false; // ���ꂪ���邩�̃t���O

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

        // X�����̕␳
        if (std::abs(diffX) > std::abs(diffY))
        {
            if (diffX > 0)
            {
                if (TileTag == TILE)
                {
                    SetCourse(RIGHT);
                }
                adjustX = std::max<float>(adjustX, tileCenter.x + tileSize.x / 2 + charSize.x / 2 - m_Pos.x);
            }
            else
            {
                if (TileTag == TILE)
                {
                    SetCourse(LEFT);
                }
                adjustX = std::min<float>(adjustX, tileCenter.x - tileSize.x / 2 - charSize.x / 2 - m_Pos.x);
            }
        }
        // Y�����̕␳�i���ꔻ��j
        else
        {
            if (diffY > 0 && TileTag == TILE)
            {
                FallFlag = false; // ���n
                hasGround = true; // ���ꂠ��
                adjustY = std::max<float>(adjustY, tileCenter.y + tileSize.y / 2 + charSize.y / 2 - m_Pos.y);
            }
            else
            {
                if (TileTag == PLAYER)
                {
                    m_Alive = false;
                }
                adjustY = std::min<float>(adjustY, tileCenter.y - tileSize.y / 2 - charSize.y / 2 - m_Pos.y);
            }
        }
    }

    // �ʒu�␳��K�p
    m_Pos.x += adjustX;
    m_Pos.y += adjustY;

    // �i�s�����̉��ɑ��ꂪ���邩�`�F�b�N
    if (!CheckGround() && FallOnOff == true)
    {
        if (GetCourse() == RIGHT)
        {
            SetCourse(LEFT);
        }
        else
        {
            SetCourse(RIGHT);
        }
    }
}

Course Enemy::GetCourse()
{
    return m_Course;
}

void Enemy::SetCourse(Course _SetCourse)
{
    m_Course = _SetCourse;
}

bool Enemy::GameClear()
{
    if (-SCREEN_HEIGHT / 2.0f > m_Pos.y + m_Size.y)
    {
        return true;
    }
    return false;
}

bool Enemy::CheckGround()
{
    float checkX = m_Pos.x + ((GetCourse() == RIGHT) ? m_ColliderSize.x / 2 : -m_ColliderSize.x / 2);
    float checkY = m_Pos.y - m_ColliderSize.y / 2 - 1.0f; // 1�s�N�Z�������`�F�b�N

    for (const auto& hit : m_HitInformation)
    {
        if (hit.ObjectTAG == TILE)
        {
            float tileLeft = hit.Pos.x - hit.Size.x / 2;
            float tileRight = hit.Pos.x + hit.Size.x / 2;
            float tileTop = hit.Pos.y + hit.Size.y / 2;
            float tileBottom = hit.Pos.y - hit.Size.y / 2;

            // �i�s�����̑��ꂪ���邩�`�F�b�N
            if (checkX >= tileLeft && checkX <= tileRight && checkY >= tileBottom && checkY <= tileTop)
            {
                return true; // ���ꂠ��
            }
        }
    }
    return false; // ����Ȃ�
}

void Enemy::SetFallOnOff(bool _FallOnOff)
{
    FallOnOff = _FallOnOff;
}