#pragma once

// =========================
// 敵のクラス
// =========================

#include "Character.h"
#include "EnemyState.h"
#include <memory>

enum Course {
	RIGHT,
	LEFT
};

class Enemy : public Character
{
private:

	Course m_Course = LEFT;
	std::shared_ptr<EnemyState> m_EnemyState;

	bool CheckGround();
	bool FallOnOff = false;

public:
	Enemy();
	~Enemy();

	virtual void Update();
	void Draw();

	void InputControl();
	void ChangeState(std::shared_ptr<EnemyState> _ChangeState);
	void SetState(std::shared_ptr<EnemyState> _ChangeState);

	// プレイヤーが他のオブジェクトと重ならないようにする
	void Overlap();
	Course GetCourse();
	void SetCourse(Course _SetCourse);

	// クリアフラグ
	bool GameClear();

	// 落とし穴に落ちるかのセッター
	void SetFallOnOff(bool _FallOnOff);
};

