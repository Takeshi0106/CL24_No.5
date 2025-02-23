#include "PlayerDeadState.h"
#include "Player.h"

// インスタンスを渡すクラス
PlayerDeadState* PlayerDeadState::GetInstance()
{
	static PlayerDeadState Instance;
	return &Instance;
}

// 状態の更新
void PlayerDeadState::Control(Player* _player)
{

}

// 状態の開始処理
void PlayerDeadState::Enter(Player* _player)
{
	// ジャンプのパワーを代入する
	DirectX::XMFLOAT3 playerVelocity = _player->GetVelocity();
	playerVelocity.y = 15.0f;

	_player->SetColor({ 0.8627f, 0.0784f, 0.2353f, 1.0f });
	_player->SetVelocity(playerVelocity);
}

// 状態中の処理
void PlayerDeadState::Excute(Player* _player)
{

}

// 状態の終了処理
void PlayerDeadState::Exit(Player* _player)
{

}