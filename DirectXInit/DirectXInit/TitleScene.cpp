#include "TitleScene.h"
#include "Game.h"

TitleScene::TitleScene()
{
	Init();
}

TitleScene::~TitleScene()
{
	Uninit();
}

void TitleScene::Init()
{
	// std::unique_ptrでオブジェクトを管理
	std::shared_ptr<Object> Title = std::make_shared<Object>();
	int cnt = Title.use_count();
	Title->TextureLoad(L"asset/Title.png", 1, 1);
	Title->SetNum({ 0,0 });
	Title->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	Title->SetSize({ SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f });
	Title->SetPos({ 0.0f, 0.0f, 0.0f });

	// Gameクラスのコンテナに代入
	Game::GetInstance()->Add_GameObjectVector<Object>(Title);
}

void TitleScene::Update()
{
	if (Input::GetKeyTrigger(VK_ENTER))
	{
		Game::GetInstance()->SceneChang(Chang);
	}
	else if (Input::GetKeyTrigger(VK_B))
	{
		Game::GetInstance()->GameStop();
	}
}

void TitleScene::Uninit()
{
	Game::GetInstance()->DeleteAllObj();
}