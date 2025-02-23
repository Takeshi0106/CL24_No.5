#pragma once

#include "Scene.h"

class EndScene : public Scene
{
private:

public:
	EndScene();
	~EndScene();

	void Init();
	void Update();
	void Uninit();
};

