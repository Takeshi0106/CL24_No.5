#pragma once

// ==============================================================================================
// �p�[�e�B�N�����������Ă���ꏊ��List�ɕۑ����Ă����Ă��̏ꏊ�Ɋۂ�`�悷��֐�
// ParticleCreate�֐�()�ŏꏊ���w�肵�Ă�������
// ==============================================================================================

#include "Object.h"
#include <array>
#include <deque>

struct PARTICLESTATES {
	// �ꏊ
	DirectX::XMFLOAT3 Pos;
	// �`��T�C�Y
	DirectX::XMFLOAT3 Size;
	// �`��J�n����
	LARGE_INTEGER Time;
	// �p�[�e�B�N���̐F
	DirectX::XMFLOAT4 Color;
	// �p�[�e�B�N����������܂ł̎���
	float DeleteTime;
	// �p�[�e�B�N���̈ړ���
	DirectX::XMFLOAT3 MovePower;
};

class ParticleManager : public Object
{
private:
	// Circle�̔��a
	float m_Radius = 0.1f;
	// circle�̒��_������
	std::array<Vertex, 40> m_CircleVertex;
	// �p�[�e�B�N���̏������Ă���
	static std::deque<PARTICLESTATES> m_ParticleData;

public:
	// �R���X�g���N�^�E�f�X�g���N�^
	ParticleManager();
	~ParticleManager();

	// 
	void Init();
	void Update();
	void Draw();

	// �p�[�e�B�N���̐���(�����ŕ`�悷��ꏊ��n��)
	static void ParticleCreate(DirectX::XMFLOAT3 _ParticlePos,DirectX::XMFLOAT3 _ParticleSize, DirectX::XMFLOAT4 _ParticleColor,float _DeleteTime,
		DirectX::XMFLOAT3 _MovePower);

	// �~�̒��_�����߂�i�����ŉ~�̔��a��n���B�j
	void Circle(float _Radius);
};