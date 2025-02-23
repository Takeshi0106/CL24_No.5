#pragma once
#include "Scene.h"

class ChangScene : public Scene
{
private:

public:
	//コンストラクタ
	ChangScene();
	~ChangScene();

	//オーバーロード
	void Init();
	void Update();
	void Uninit();
};

