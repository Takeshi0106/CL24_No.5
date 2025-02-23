#include "Goll.h"

Goll::Goll()
{
	TextureLoad(L"asset/pipo-gwspinitem002.png", 5, 4);
	SetNum({ 0,0 });

	m_ColliderSize.x = m_Size.x;
	m_ColliderSize.y = m_Size.y;
}

void Goll::Update()
{
    Animation();
}

void Goll::Draw()
{
	ObjectDraw();
}

void Goll::Overlap()
{

}

void Goll::Animation()
{
    Cnt++;
    if (Cnt > 3)
    {
        // _playerのGetNum()から現在のフレーム情報を取得
        NUM num = GetNum();

        // 横のフレーム数が5（0～4）で、縦のフレーム数が4（0～3）の範囲
        const int maxHorizontal = 5;  // 横のフレーム数
        const int maxVertical = 4;    // 縦のフレーム数

        num.numU++;  // numU（横方向）を進める

        // 横方向が最大に達したら、横を0にリセットし、縦方向を進める
        if (num.numU >= maxHorizontal)
        {
            num.numU = 0;
            num.numV++;  // 縦方向を進める

            // 縦が最大に達したら、縦を0にリセット
            if (num.numV >= maxVertical)
            {
                num.numV = 0;
            }
        }

        // _playerに新しいフレーム番号を設定
        SetNum(num);
        Cnt = 0;
    }
}


bool Goll::Arrival()
{
	for (const auto& hit : m_HitInformation)
	{
		if (hit.ObjectTAG == PLAYER)
		{
			return true;
		}
	}
	return false;
}