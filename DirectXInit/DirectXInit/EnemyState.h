#pragma once
#include <memory>

// ===============================
// Enemy�̏�ԃN���X
// ===============================

class Enemy;

class EnemyState
{
protected:

public:
	~EnemyState() {};
	// ��Ԃ̍X�V
	virtual void Control(Enemy* _enemy) = 0;
	// ��Ԃ̊J�n����
	virtual void Enter(Enemy* _enemy) = 0;
	// ��Ԓ��̏���
	virtual void Excute(Enemy* _enemy) = 0;
	// ��Ԃ̏I������
	virtual void Exit(Enemy* _enemy) = 0;
};