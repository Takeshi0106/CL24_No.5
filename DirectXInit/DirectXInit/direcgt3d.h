#pragma once

//��������������������������������������������������
//��direcgt3d.h�ֈړ�

#include <d3d11.h>  // DirectX11���g�����߂̃w�b�_�[�t�@�C��
#include<DirectXMath.h>

#define SCREEN_WIDTH (960)	// �E�C���h�E�̕�
#define SCREEN_HEIGHT (720)	// �E�C���h�E�̍���

// �֐��̃v���g�^�C�v�錾
HRESULT D3D_Create(HWND hwnd);
void    D3D_Release();
void    D3D_StartRender();
void    D3D_FinishRender();


// �s�N�Z���V�F�[�_�[�I�u�W�F�N�g
extern ID3D11PixelShader* g_pPixelShader;
// �e�N�X�`�����g���Ƃ��̃V�F�[�_�I�u�W�F�N�g
extern ID3D11PixelShader* g_pTextureShader;

//��direcgt3d.h�ֈړ�
//��������������������������������������������������

// ���_�f�[�^��\���\����
struct Vertex
{
	// ���_�̈ʒu���W
	float x, y, z;

	//�\���̂ɐF��ǉ�����
	float red, green, blue, alpha;

	//�e�N�X�`�����W�iUV���W�j
	float u, v;
};

struct ConstBuffer {
	//���_����\�s��
	DirectX::XMFLOAT4 color;
	//UV���W�ړ�
	DirectX::XMMATRIX matrixTex;
	DirectX::XMMATRIX matrixProj;
	DirectX::XMMATRIX matrixWorld;
};

extern ID3D11Device* g_pDevice; // �f�o�C�X��DirectX�̊e��@�\�����
extern ID3D11DeviceContext* g_pDeviceContext; // �R���e�L�X�g���`��֘A���i��@�\
extern ID3D11Buffer* g_pConstantBuffer;

// Direct3D����̊ȗ����}�N��
#define SAFE_RELEASE(p) { if( NULL != p ) { p->Release(); p = NULL; } }