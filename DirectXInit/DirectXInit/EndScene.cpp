#include "EndScene.h"
#include "Game.h"

EndScene::EndScene()
{
	Init();
}

EndScene::~EndScene()
{
	Uninit();
}

void EndScene::Init()
{
	std::shared_ptr<Object> background = std::make_shared<Object>();
	background->TextureLoad(L"asset/GAME OVER.png", 1, 1);
	background->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	background->SetSize({ SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f });
	background->SetPos({ 0.0f, 0.0f, 0.0f });

	//ƒRƒ“ƒeƒi‚É‘ã“ü
	//Objects.push_back(background.get());
	
	Game::GetInstance()->Add_GameObjectVector<Object>(background);
}

void EndScene::Update()
{
	if (Input::GetKeyTrigger(VK_ENTER))
	{
		Game::GetInstance()->SceneChang(Title);
	}
	else if (Input::GetKeyTrigger(VK_BACK))
	{
		Game::GetInstance()->SceneChang(Chang);
	}
	else if (Input::GetKeyTrigger(VK_B))
	{
		Game::GetInstance()->GameStop();
	}
}

void EndScene::Uninit()
{
	Game::GetInstance()->DeleteAllObj();
}