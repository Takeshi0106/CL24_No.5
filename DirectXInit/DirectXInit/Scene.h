#pragma once
#include"Object.h"
#include <memory>

class Scene
{
public:
	Scene();
	virtual ~Scene();

	//オーバーロード用
	virtual void Update() = 0;
};

