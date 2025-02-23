#pragma once

#include "input.h"
#include "TitleScene.h"
#include "Stage1Scene.h"
#include "EndScene.h"
#include "ClearScene.h"
#include "ChangScene.h"
#include "Stage2Scene.h"
#include "Stage3Scene.h"

enum SceneName {
	Title,
	Stg1,
	End,
	Clear,
	Chang,
	Stg2,
	Stg3,
};

class Game
{
private:
	//キーボード入力を取得するクラス
	//Input input;

	std::unique_ptr<Input> m_Input;  // 入力処理

	static Game *m_Instance;
	//今のSeenのオブジェクトを入れる
	std::vector<std::shared_ptr<Object>> m_Objects; // オブジェクト
	//std::vector<Object*> m_Objects;

	Scene* m_Scene; // シーン

	// ゲームループ
	bool m_Loop = true;

public:
	Game();
	~Game();

	static void Init(HWND hwnd);
	static void Update();
	static void Draw();
	static void Uninit();

	void SceneChang(SceneName NextSeen);
	void GameStop();
	bool GameLoop();
	static Game* GetInstance();
	void DeleteAllObj();

	// オブジェクトを追加する(※テンプレート関数なのでここに直接記述)
	template<class T>
	void Add_GameObjectVector(std::shared_ptr<T> pt)
	{
		m_Instance->m_Objects.emplace_back(pt);
	}
};

