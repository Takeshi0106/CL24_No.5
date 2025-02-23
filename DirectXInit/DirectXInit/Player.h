#pragma once

// ============================
// プレイヤーのクラス
// ============================

#include "Character.h"
#include "State.h"

#define DELETETIME_SANDSMOKE (0.3f)

class Player : public Character 
{
private:
	// 移動を入れる変数
	DirectX::XMFLOAT3 m_Velocity;

	// Playerの状態を入れる
	PlayerState* m_PlayerState;

	// 減速度計算用 
	void Velocity();

public:
	Player();
	~Player();

	void Update();
	void Draw();

	void Overlap();

	// State
	void InputControl();
	void ChangeState(PlayerState* _ChangeState);
	void SetState(PlayerState* _ChangeState);

	// セッター・ゲッター
	void SetVelocity(DirectX::XMFLOAT3 _Velocity);
	DirectX::XMFLOAT3 GetVelocity();

	bool GameOver();
};

