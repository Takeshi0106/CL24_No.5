#pragma once

// ==============================
// 重力をあたえるクラス
// ==============================

#include <DirectXMath.h>

class Gravity
{
private:
	// 重力の力
	float m_GravityPawe = -0.098f;
	// 落下時間
	int FallTime = 0;

public:
	// 落ちている時は「true」着地している時は「false」を渡してください
	DirectX::XMFLOAT3 Update(bool Flag);

};

