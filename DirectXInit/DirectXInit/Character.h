#pragma once
#include "Object.h"
#include "Gravity.h"
#include <deque>

// ==================================
// �G��v���C���[�Ȃǂ̊��N���X
// ==================================

// �I�u�W�F�N�g�̃^�O
enum TAG {
	PLAYER,
	ENEMY,
	TILE
};

// �����������
struct HITINFORMATION {
	TAG ObjectTAG;
	DirectX::XMFLOAT3 Pos;
	DirectX::XMFLOAT3 Size;
};

struct INFORMATION {
	DirectX::XMFLOAT2 Pos;
	DirectX::XMFLOAT2 Size;
};

class Character : public Object 
{
protected:
	bool m_Alive = true;

	// �d�̓N���X
	Gravity m_GravityClass;
	// �d�͂����Ă����ϐ�
	DirectX::XMFLOAT3 m_Gravity = { 0.0f,0.0f,0.0f };

	// �����蔻��̑傫��
	DirectX::XMFLOAT3 m_ColliderSize = { 0.0f,0.0f,0.0f };
	// ���������I�u�W�F�N�g�́u�^�O�E�ʒu�E�T�C�Y�v�����Ă���
	std::deque<HITINFORMATION> m_HitInformation;

	// �n�ʂɒ��n���Ă��邩�̃t���O
	bool FallFlag = false;

public:
	virtual void Update();
	virtual void Draw();

	DirectX::XMFLOAT3 GetPlayerColliderSize();
	// �Ԃ�������������
	void SetHitInformation(HITINFORMATION _HitInformation);
	// �Ԃ����������폜����
	void DeleteHitInformation();
	// �v���C���[�����̃I�u�W�F�N�g�Əd�Ȃ�Ȃ��悤�ɂ���
	virtual void Overlap() = 0;
	// �v���C���[�̗������
	bool GetFallFlag();
	// �����t���O
	bool GetAlive();
};

