#pragma once

#include "Scene.h"
#include "Player.h"
#include "Enemy.h"
#include "TileManager.h"

class Stage1Scene : public Scene
{
private:
	// プレイヤーを入れる
	std::shared_ptr<Player> m_Player;
	// タイルを入れる
	std::shared_ptr<TileManager> m_Tiles;
	// エネミーを入れる
	std::vector<std::shared_ptr<Enemy>> m_Enemy;
public:
	Stage1Scene();
	~Stage1Scene();

	void Init();
	void Update();
	void Uninit();
};

