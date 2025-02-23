#include "Stage3Scene.h"
#include "Game.h"
#include "ParticleManager.h"

#include "EnemyMoveState.h"
#include "EnemyStopState.h"

Stage3Scene::Stage3Scene()
{
	Init();
}

Stage3Scene::~Stage3Scene()
{
	Uninit();
}

void Stage3Scene::Init()
{
	std::shared_ptr<Object> Back = std::make_shared<Object>();
	Back->TextureLoad(L"asset/background.png", 1, 1);
	Back->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	Back->SetSize({ SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f });
	Back->SetPos({ 0.0f, 0.0f, 0.0f });

	std::shared_ptr<ParticleManager> particles = std::make_shared<ParticleManager>();
	std::shared_ptr<TileManager> Tile = std::make_shared<TileManager>("asset/Map/Stg3.csv");
	std::shared_ptr<Player> player = std::make_shared<Player>();
	std::shared_ptr<Enemy> enemy1 = std::make_shared<Enemy>();
	std::shared_ptr<Enemy> enemy2 = std::make_shared<Enemy>();
	std::shared_ptr<Enemy> enemy3 = std::make_shared<Enemy>();
	std::shared_ptr<Enemy> enemy4 = std::make_shared<Enemy>();
	std::shared_ptr<Goll> goll = std::make_shared<Goll>();

	player->SetPos({ -SCREEN_WIDTH / 2 + player->GetSize().x / 2,-300.0f,0.0f });

	enemy1->SetPos({ 200.0f, -300.0f, 0.0f });
	enemy1->SetState(EnemyMoveState::GetInstance());
	enemy1->SetFallOnOff(true);

	enemy2->SetPos({ SCREEN_WIDTH / 2 - enemy2->GetSize().x / 2,-300.0f,0.0f });
	enemy2->SetState(EnemyMoveState::GetInstance());
	enemy2->SetFallOnOff(true);

	enemy3->SetPos({ -SCREEN_WIDTH / 2 - enemy2->GetSize().x / 2 + 96 * 5,0.0f,0.0f });
	enemy3->SetState(EnemyMoveState::GetInstance());
	enemy3->SetFallOnOff(false);

	enemy4->SetPos({ -SCREEN_WIDTH / 2 - enemy2->GetSize().x / 2 + 96 * 5,SCREEN_HEIGHT,0.0f });
	enemy4->SetState(EnemyMoveState::GetInstance());
	enemy4->SetFallOnOff(false);

	goll->SetPos({ SCREEN_WIDTH / 2 - (goll->GetPlayerColliderSize().x / 2),-SCREEN_HEIGHT / 2 + (72+ goll->GetPlayerColliderSize().y / 2),0.0f });

	// Gameクラスのコンテナに代入
	Game::GetInstance()->Add_GameObjectVector<Object>(Back);
	Game::GetInstance()->Add_GameObjectVector<ParticleManager>(particles);
	Game::GetInstance()->Add_GameObjectVector<TileManager>(Tile);
	Game::GetInstance()->Add_GameObjectVector<Player>(player);
	Game::GetInstance()->Add_GameObjectVector<Enemy>(enemy1);
	Game::GetInstance()->Add_GameObjectVector<Enemy>(enemy2);
	Game::GetInstance()->Add_GameObjectVector<Enemy>(enemy3);
	Game::GetInstance()->Add_GameObjectVector<Enemy>(enemy4);
	Game::GetInstance()->Add_GameObjectVector<Goll>(goll);

	m_Player = player;
	m_Tiles = Tile;
	m_Enemy.emplace_back(enemy1);
	m_Enemy.emplace_back(enemy2);
	m_Enemy.emplace_back(enemy3);
	m_Enemy.emplace_back(enemy4);
	m_Goll = goll;
}

void Stage3Scene::Update()
{
	// プレイヤーの位置と大きさ取得
	DirectX::XMFLOAT3 PlayerCollider = m_Player->GetPlayerColliderSize();
	DirectX::XMFLOAT3 PlayerPos = m_Player->GetPos();

	// 当たり判定初期化
	m_Player->DeleteHitInformation();
	// 当たり判定処理
	m_Tiles->ColliderTile(m_Player);

	for (int i = 0; m_Enemy.size() > i; i++)
	{
		m_Enemy[i]->DeleteHitInformation();
		m_Tiles->ColliderTile(m_Enemy[i]);

		// エネミーの位置と大きさを取得
		DirectX::XMFLOAT3 EnemyCollider = m_Enemy[i]->GetPlayerColliderSize();
		DirectX::XMFLOAT3 EnemyPos = m_Enemy[i]->GetPos();

		// プレイヤーとエネミーの当たり判定
		if (m_Player->GetAlive() && m_Enemy[i]->GetAlive())
		{
			if (EnemyPos.x + EnemyCollider.x / 2 >= PlayerPos.x - PlayerCollider.x / 2 &&
				EnemyPos.x - EnemyCollider.x / 2 <= PlayerPos.x + PlayerCollider.x / 2 &&
				EnemyPos.y + EnemyCollider.y / 2 >= PlayerPos.y - PlayerCollider.y / 2 &&
				EnemyPos.y - EnemyCollider.y / 2 <= PlayerPos.y + PlayerCollider.y / 2)
			{
				m_Player->SetHitInformation({ ENEMY,EnemyPos,EnemyCollider });
				m_Enemy[i]->SetHitInformation({ PLAYER,PlayerPos,PlayerCollider });
			}
		}
	}
	// めり込まないように補間
	m_Player->Overlap();
	for (int i = 0; m_Enemy.size() > i; i++)
	{
		m_Enemy[i]->Overlap();
	}

	// Sceneチェンジ
	if (m_Player->GameOver())
	{
		Game::GetInstance()->SceneChang(End);
	}
	else if (m_Goll->GetPos().x + m_Goll->GetPlayerColliderSize().x / 2 >= PlayerPos.x - PlayerCollider.x / 2 &&
		m_Goll->GetPos().x - m_Goll->GetPlayerColliderSize().x / 2 <= PlayerPos.x + PlayerCollider.x / 2 &&
		m_Goll->GetPos().y + m_Goll->GetPlayerColliderSize().y / 2 >= PlayerPos.y - PlayerCollider.y / 2 &&
		m_Goll->GetPos().y - m_Goll->GetPlayerColliderSize().y / 2 <= PlayerPos.y + PlayerCollider.y / 2)
	{
		Game::GetInstance()->SceneChang(Clear);
	}
	else if (Input::GetKeyPress(VK_R))
	{
		Game::GetInstance()->SceneChang(Chang);
	}

}

void Stage3Scene::Uninit()
{
	Game::GetInstance()->DeleteAllObj();
}