#pragma once
#include "Scene.h"

class ClearScene : public Scene
{
private:

public:
	ClearScene();
	~ClearScene();

	void Init();
	void Update();
	void Uninit();
};

