#include "Gravity.h"

DirectX::XMFLOAT3 Gravity::Update(bool Flag)
{
	DirectX::XMFLOAT3 gravity = { 0.0f,0.0f,0.0f };

	if (Flag)
	{
		// �����Ă��鎞�̏���
		FallTime++;
	}
	else
	{
		// ���n���Ă��鎞�̏���
		FallTime = 0;
	}

	gravity.y = m_GravityPawe * FallTime;
	return gravity;
}
