#pragma once
#include "Scene.h"

class ChangScene : public Scene
{
private:

public:
	//�R���X�g���N�^
	ChangScene();
	~ChangScene();

	//�I�[�o�[���[�h
	void Init();
	void Update();
	void Uninit();
};

