#include "Game.h"
#include "Timer.h"

Game* Game::m_Instance;

Game::Game()
{
	m_Input = std::make_unique<Input>(); //入力処理を作成
}

Game::~Game()
{

}

void Game::Init(HWND hwnd)
{
	D3D_Create(hwnd);

	m_Instance = new Game;

	Game::GetInstance()->SceneChang(Title);
	
	// タイマー初期化
	Timer::Init();
}

void Game::Update()
{
	m_Instance->m_Input->Update();

	// m_Instance->m_Scene->Update();

	for (auto& o : m_Instance->m_Objects)
	{
		o->Update();
	}

	m_Instance->m_Scene->Update();
}

void Game::Draw()
{
	D3D_StartRender();

	for (auto& o : m_Instance->m_Objects)
	{
		o->Draw();
	}

	D3D_FinishRender();

}

void Game::Uninit()
{
	for (auto& o : m_Instance->m_Objects)
	{
		o->Uninit();
	}

	delete m_Instance->m_Scene;
	
	D3D_Release();
}

void Game::SceneChang(SceneName NextSeen)
{
	if (m_Instance->m_Scene != nullptr)
	{
		delete m_Instance->m_Scene;
		m_Instance->m_Scene = nullptr;
	}

	switch (NextSeen)
	{
	case Title:
		m_Instance->m_Scene = new TitleScene; // メモリを確保
		break;
	case Stg1:
		m_Instance->m_Scene = new Stage1Scene; // メモリを確保
		break;
	case End:
		m_Instance->m_Scene = new EndScene; // メモリを確保
		break;
	case Clear:
		m_Instance->m_Scene = new ClearScene; // メモリ確保
		break;
	case Chang:
		m_Instance->m_Scene = new ChangScene; // メモリ確保
		break;
	case Stg2:
		m_Instance->m_Scene = new Stage2Scene;
		break;
	case Stg3:
		m_Instance->m_Scene = new Stage3Scene;
		break;
	}
}

Game* Game::GetInstance()
{
	return m_Instance;
}

void Game::DeleteAllObj()
{
	m_Instance->m_Objects.clear(); //全て削除
	m_Instance->m_Objects.shrink_to_fit();
}

void Game::GameStop()
{
	m_Loop = false;
}

bool Game::GameLoop()
{
	return m_Loop;
}