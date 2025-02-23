#pragma once
#include "Scene.h"
#include "Player.h"
#include "Enemy.h"
#include "TileManager.h"
#include "Goll.h"

class Stage3Scene : public Scene
{
private:
	// �v���C���[������
	std::shared_ptr<Player> m_Player;
	// �^�C��������
	std::shared_ptr<TileManager> m_Tiles;
	// �G�l�~�[������
	std::vector<std::shared_ptr<Enemy>> m_Enemy;
	// �S�[��
	std::shared_ptr<Goll> m_Goll;

public:
	Stage3Scene();
	~Stage3Scene();

	void Init();
	void Update();
	void Uninit();
};

