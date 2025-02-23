#pragma once

// =========================
// �G�̃N���X
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

	// �v���C���[�����̃I�u�W�F�N�g�Əd�Ȃ�Ȃ��悤�ɂ���
	void Overlap();
	Course GetCourse();
	void SetCourse(Course _SetCourse);

	// �N���A�t���O
	bool GameClear();

	// ���Ƃ����ɗ����邩�̃Z�b�^�[
	void SetFallOnOff(bool _FallOnOff);
};

