#include "PlayerSupearJumpState.h"
#include "Player.h"
#include "PlayerJumpState.h"

#include "input.h"

// インスタンスを渡すクラス
PlayerSupearJumpState* PlayerSupearJumpState::GetInstance()
{
	static PlayerSupearJumpState Instance;
	return &Instance;
}

// 状態の更新
void PlayerSupearJumpState::Control(Player* _player)
{
	if (cnt > 10)
	{
		_player->ChangeState(PlayerJumpState::GetInstance());
	}
}

// 状態の開始処理
void PlayerSupearJumpState::Enter(Player* _player)
{
	cnt = 0;
}

// 状態中の処理
void PlayerSupearJumpState::Excute(Player* _player)
{
	cnt++;
	DirectX::XMFLOAT3 PlayerPos = _player->GetPos();
	DirectX::XMFLOAT3 PlayerSize = _player->GetSize();

	if (Input::GetKeyTrigger(VK_SPACE))
	{
		// ジャンプのパワーを代入する
		DirectX::XMFLOAT3 playerVelocity = _player->GetVelocity();
		playerVelocity.y += 12.5f;
		_player->SetVelocity(playerVelocity);
	}

	if (Input::GetKeyPress(VK_A) && -SCREEN_WIDTH / 2 < PlayerPos.x - PlayerSize.x / 2)
	{
		PlayerPos.x -= 2.5f;
	}
	if (Input::GetKeyPress(VK_D))
	{
		PlayerPos.x += 2.5f;
	}

	_player->SetPos(PlayerPos);
}

// 状態の終了処理
void PlayerSupearJumpState::Exit(Player* _player)
{

}