#pragma once
#include"Object.h"
#include <memory>

class Scene
{
public:
	Scene();
	virtual ~Scene();

	//�I�[�o�[���[�h�p
	virtual void Update() = 0;
};

