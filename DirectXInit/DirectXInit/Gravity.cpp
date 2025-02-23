#include "Gravity.h"

DirectX::XMFLOAT3 Gravity::Update(bool Flag)
{
	DirectX::XMFLOAT3 gravity = { 0.0f,0.0f,0.0f };

	if (Flag)
	{
		// —‚¿‚Ä‚¢‚é‚Ìˆ—
		FallTime++;
	}
	else
	{
		// ’…’n‚µ‚Ä‚¢‚é‚Ìˆ—
		FallTime = 0;
	}

	gravity.y = m_GravityPawe * FallTime;
	return gravity;
}
