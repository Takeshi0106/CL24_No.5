#include "Gravity.h"

DirectX::XMFLOAT3 Gravity::Update(bool Flag)
{
	DirectX::XMFLOAT3 gravity = { 0.0f,0.0f,0.0f };

	if (Flag)
	{
		// 落ちている時の処理
		FallTime++;
	}
	else
	{
		// 着地している時の処理
		FallTime = 0;
	}

	gravity.y = m_GravityPawe * FallTime;
	return gravity;
}
