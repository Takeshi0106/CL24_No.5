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
        // _player��GetNum()���猻�݂̃t���[�������擾
        NUM num = GetNum();

        // ���̃t���[������5�i0�`4�j�ŁA�c�̃t���[������4�i0�`3�j�͈̔�
        const int maxHorizontal = 5;  // ���̃t���[����
        const int maxVertical = 4;    // �c�̃t���[����

        num.numU++;  // numU�i�������j��i�߂�

        // ���������ő�ɒB������A����0�Ƀ��Z�b�g���A�c������i�߂�
        if (num.numU >= maxHorizontal)
        {
            num.numU = 0;
            num.numV++;  // �c������i�߂�

            // �c���ő�ɒB������A�c��0�Ƀ��Z�b�g
            if (num.numV >= maxVertical)
            {
                num.numV = 0;
            }
        }

        // _player�ɐV�����t���[���ԍ���ݒ�
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