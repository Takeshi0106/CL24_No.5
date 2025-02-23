#include "Character.h"
#include <algorithm>

void Character::Update()
{

}

void Character::Draw()
{
	ObjectDraw();
}


void SetObjects(std::vector<Object*>* _p_Objects)
{
	_p_Objects = _p_Objects;
}

DirectX::XMFLOAT3 Character::GetPlayerColliderSize()
{
	return m_ColliderSize;
}

// ‚Ô‚Â‚©‚Á‚½î•ñ‚ğ“ü‚ê‚é
void Character::SetHitInformation(HITINFORMATION _HitInformation)
{
	m_HitInformation.push_back(_HitInformation);
}

// ‚Ô‚Â‚©‚Á‚½î•ñ‚ğƒNƒŠƒA‚·‚é
void Character::DeleteHitInformation()
{
	m_HitInformation.clear();
}

bool Character::GetFallFlag()
{
    return FallFlag;
}

bool Character::GetAlive()
{
    return m_Alive;
}