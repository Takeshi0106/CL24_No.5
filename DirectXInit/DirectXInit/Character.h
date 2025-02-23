#pragma once
#include "Object.h"
#include "Gravity.h"
#include <deque>

// ==================================
// 敵やプレイヤーなどの基底クラス
// ==================================

// オブジェクトのタグ
enum TAG {
	PLAYER,
	ENEMY,
	TILE
};

// 当たった情報
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

	// 重力クラス
	Gravity m_GravityClass;
	// 重力を入れておく変数
	DirectX::XMFLOAT3 m_Gravity = { 0.0f,0.0f,0.0f };

	// 当たり判定の大きさ
	DirectX::XMFLOAT3 m_ColliderSize = { 0.0f,0.0f,0.0f };
	// 当たったオブジェクトの「タグ・位置・サイズ」を入れておく
	std::deque<HITINFORMATION> m_HitInformation;

	// 地面に着地しているかのフラグ
	bool FallFlag = false;

public:
	virtual void Update();
	virtual void Draw();

	DirectX::XMFLOAT3 GetPlayerColliderSize();
	// ぶつかった情報を入れる
	void SetHitInformation(HITINFORMATION _HitInformation);
	// ぶつかった情報を削除する
	void DeleteHitInformation();
	// プレイヤーが他のオブジェクトと重ならないようにする
	virtual void Overlap() = 0;
	// プレイヤーの落下状態
	bool GetFallFlag();
	// 生存フラグ
	bool GetAlive();
};

