#pragma once

// ==============================
// �d�͂���������N���X
// ==============================

#include <DirectXMath.h>

class Gravity
{
private:
	// �d�̗͂�
	float m_GravityPawe = -0.098f;
	// ��������
	int FallTime = 0;

public:
	// �����Ă��鎞�́utrue�v���n���Ă��鎞�́ufalse�v��n���Ă�������
	DirectX::XMFLOAT3 Update(bool Flag);

};

