#pragma once
#include "Scene.h"
#include "Player.h"
#include "Enemy.h"
#include "TileManager.h"
#include "Goll.h"

class Stage3Scene : public Scene
{
private:
	// プレイヤーを入れる
	std::shared_ptr<Player> m_Player;
	// タイルを入れる
	std::shared_ptr<TileManager> m_Tiles;
	// エネミーを入れる
	std::vector<std::shared_ptr<Enemy>> m_Enemy;
	// ゴール
	std::shared_ptr<Goll> m_Goll;

public:
	Stage3Scene();
	~Stage3Scene();

	void Init();
	void Update();
	void Uninit();
};

