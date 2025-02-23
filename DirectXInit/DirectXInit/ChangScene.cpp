#include "ChangScene.h"
#include "Game.h"

ChangScene::ChangScene()
{
	Init();
}

ChangScene::~ChangScene()
{
	Uninit();
}

void ChangScene::Init()
{
	// std::unique_ptrでオブジェクトを管理
	std::shared_ptr<Object> Chang = std::make_shared<Object>();
	Chang->TextureLoad(L"asset/ChangStag.png", 1, 1);
	Chang->SetNum({ 0,0 });
	Chang->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	Chang->SetSize({ SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f });
	Chang->SetPos({ 0.0f, 0.0f, 0.0f });

	// Gameクラスのコンテナに代入
	Game::GetInstance()->Add_GameObjectVector<Object>(Chang);
}

void ChangScene::Update()
{
	if (Input::GetKeyTrigger(VK_1))
	{
		Game::GetInstance()->SceneChang(Stg1);
	}
	else if (Input::GetKeyTrigger(VK_2))
	{
		Game::GetInstance()->SceneChang(Stg2);
	}
	else if (Input::GetKeyTrigger(VK_3))
	{
		Game::GetInstance()->SceneChang(Stg3);
	}
	else if (Input::GetKeyTrigger(VK_BACK))
	{
		Game::GetInstance()->SceneChang(Title);
	}
	/*
	else if (Input::GetKeyTrigger(VK_B))
	{
		Game::GetInstance()->GameStop();
	}
	*/
}

void ChangScene::Uninit()
{
	Game::GetInstance()->DeleteAllObj();
}