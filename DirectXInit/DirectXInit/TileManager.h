#pragma once
#include "Object.h"
#include "MapFileOperations.h"
#include <deque>

// ==================================================
// Exselファイルの10*10で一画面
// （今はカメラが動かないため）
// ==================================================

class Character;

class TileManager: public Object
{
private:
	// マップを読み込む
	map<pair<int, int>, int> m_MapData;
	// 縦と横の要素数
	int m_Row, m_Column;
	// タイルの場所を保存しておく
	std::deque<DirectX::XMFLOAT3> m_TilePosDatas;

public:
	TileManager(string _FileName);

	void Init(string _FileName);
	void Update();
	void Draw();

	// タイルとキャラクターの当たり判定
	void ColliderTile(std::shared_ptr<Character> _character);
};

