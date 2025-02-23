#pragma once

// ==================================
// �I�u�W�F�N�g�̊��N���X
// ==================================

#include"WICTextureLoader.h"
#include"direcgt3d.h"
#include <vector>
#include <DirectXMath.h>

using namespace DirectX;

enum {
	NUMU,
	NUMV
};

struct NUM {
	int numU, numV;
};

inline DirectX::XMFLOAT3 operator+(const DirectX::XMFLOAT3& LeftSide, const DirectX::XMFLOAT3& RightSide)
{
	return DirectX::XMFLOAT3(LeftSide.x + RightSide.x, LeftSide.y + RightSide.y, LeftSide.z + RightSide.z);
}

inline DirectX::XMFLOAT3 operator*(const DirectX::XMFLOAT3& LeftSide, const float& RightSide)
{
	return DirectX::XMFLOAT3(LeftSide.x * RightSide, LeftSide.y * RightSide, LeftSide.z * RightSide);
}

class Object {
protected:

	//���W
	DirectX::XMFLOAT3 m_Pos = { 0.0f,0.0f,0.0f };
	//�傫��
	DirectX::XMFLOAT3 m_Size = { 100.0f,100.0f,0.0f };
	//�F
	DirectX::XMFLOAT4 m_Color = { 1.0f,1.0f,1.0f,1.0f };
	//�p�x
	float m_Angle = 0.0f;

	//�e�N�X�`�������c�ɉ���������Ă��邩
	int splitx = 1;
	int splity = 1;

	//���ォ�牽���ڂ�؂���̂�
	NUM m_Num = { 0,0 };

	// �e�N�X�`���t���O
	bool m_TextureFlag = false;

	ID3D11Buffer* m_pVertexBuffer;              //���_�o�b�t�@�ϐ�
	ID3D11ShaderResourceView* m_pTextureView;   //�e�N�X�`���p�ϐ�

public:
	Object();
	~Object();

	virtual void Init();
	virtual void Update();
	virtual void Draw();
	void Uninit();

	void ObjectDraw();

	void TextureLoad(const wchar_t* imgname, int sx = 1, int sy = 1);


	// �ʒu�̃Z�b�^�[
	void SetPos(XMFLOAT3 _Pos);
	// �ʒu�́[�Q�b�^�[
	DirectX::XMFLOAT3 GetPos(void);
	// �傫���̃Z�b�^�[
	void SetSize(XMFLOAT3 _Size);
	// �傫���̃Q�b�^�[
	DirectX::XMFLOAT3 GetSize(void);
	// �p�x�̃Z�b�^�[
	void SetAngle(float _Angle);
	// �p�x�̃Q�b�^�[
	float GetAngle(void);
	// UV���W�̃Z�b�^�[
	void SetNum(NUM _num);
	// UV���W�̃Q�b�^�[
	NUM GetNum();
	// �F�̃Z�b�^�[
	void SetColor(XMFLOAT4 _Color);
	// �F�̃Q�b�^�[
	DirectX::XMFLOAT4 GetColor(void);//�F���Q�b�g
};