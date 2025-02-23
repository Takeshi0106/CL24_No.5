#pragma once
#include "Object.h"
#include "MapFileOperations.h"
#include <deque>

// ==================================================
// Exsel�t�@�C����10*10�ň���
// �i���̓J�����������Ȃ����߁j
// ==================================================

class Character;

class TileManager: public Object
{
private:
	// �}�b�v��ǂݍ���
	map<pair<int, int>, int> m_MapData;
	// �c�Ɖ��̗v�f��
	int m_Row, m_Column;
	// �^�C���̏ꏊ��ۑ����Ă���
	std::deque<DirectX::XMFLOAT3> m_TilePosDatas;

public:
	TileManager(string _FileName);

	void Init(string _FileName);
	void Update();
	void Draw();

	// �^�C���ƃL�����N�^�[�̓����蔻��
	void ColliderTile(std::shared_ptr<Character> _character);
};

