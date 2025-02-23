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
	//�L�[�{�[�h���͂��擾����N���X
	//Input input;

	std::unique_ptr<Input> m_Input;  // ���͏���

	static Game *m_Instance;
	//����Seen�̃I�u�W�F�N�g������
	std::vector<std::shared_ptr<Object>> m_Objects; // �I�u�W�F�N�g
	//std::vector<Object*> m_Objects;

	Scene* m_Scene; // �V�[��

	// �Q�[�����[�v
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

	// �I�u�W�F�N�g��ǉ�����(���e���v���[�g�֐��Ȃ̂ł����ɒ��ڋL�q)
	template<class T>
	void Add_GameObjectVector(std::shared_ptr<T> pt)
	{
		m_Instance->m_Objects.emplace_back(pt);
	}
};

