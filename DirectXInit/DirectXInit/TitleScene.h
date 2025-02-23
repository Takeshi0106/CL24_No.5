#pragma once

#include "Scene.h"

class TitleScene : public Scene
{
private:

public:
	//コンストラクタ
	TitleScene();
	~TitleScene();

	//オーバーロード
	void Init();
	void Update();
	void Uninit();
};

