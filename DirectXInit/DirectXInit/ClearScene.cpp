#include "ClearScene.h"
#include "Game.h"

ClearScene::ClearScene()
{
	Init();
}

ClearScene::~ClearScene()
{
	Uninit();
}

void ClearScene::Init()
{
	std::shared_ptr<Object> Clear = std::make_shared<Object>();
	Clear->TextureLoad(L"asset/GAME CLEAR.png", 1, 1);
	Clear->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	Clear->SetSize({ SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f });
	Clear->SetPos({ 0.0f, 0.0f, 0.0f });

	// Gameクラスのコンテナに代入
	Game::GetInstance()->Add_GameObjectVector<Object>(Clear);
}

void ClearScene::Update()
{
	if (Input::GetKeyTrigger(VK_ENTER))
	{
		Game::GetInstance()->SceneChang(Title);
	}
	else if (Input::GetKeyTrigger(VK_B))
	{
		Game::GetInstance()->GameStop();
	}
}

void ClearScene::Uninit()
{
	Game::GetInstance()->DeleteAllObj();
}