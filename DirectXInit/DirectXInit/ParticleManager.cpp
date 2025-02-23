#include "ParticleManager.h"
#include "Timer.h"
#include "Game.h"

std::deque<PARTICLESTATES> ParticleManager::m_ParticleData;

ParticleManager::ParticleManager()
{
	Init();
}

ParticleManager::~ParticleManager()
{
	Uninit();
}

void ParticleManager::Init()
{
	Circle(m_Radius);

	// ���_�o�b�t�@�쐬
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = UINT(sizeof(Vertex) * m_CircleVertex.size());// �m�ۂ���o�b�t�@�T�C�Y���w��
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;// ���_�o�b�t�@�쐬���w��
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	// GPU�ɑ�����
	D3D11_SUBRESOURCE_DATA subResourceData;
	subResourceData.pSysMem = m_CircleVertex.data();// VRAM�ɑ���f�[�^���w��
	subResourceData.SysMemPitch = 0;
	subResourceData.SysMemSlicePitch = 0;

	HRESULT hr = g_pDevice->CreateBuffer(&bufferDesc, &subResourceData, &m_pVertexBuffer);
	if (FAILED(hr))
	{
		MessageBoxA(NULL, "Particles�̃o�b�t�@�쐬�G���[", "�m�F", MB_OKCANCEL);
	}
}

void ParticleManager::Update()
{
	for (int i = 0; i < m_ParticleData.size(); i++)
	{
		if (Timer::GetElapsedTime(m_ParticleData[i].Time) > m_ParticleData[i].DeleteTime)
		{
			m_ParticleData.erase(m_ParticleData.begin() + i);
			i--;
		}
		else
		{
			m_ParticleData[i].Pos = m_ParticleData[i].Pos + m_ParticleData[i].MovePower;
		}
	}
}

void ParticleManager::Draw()
{
	// �p�[�e�B�N�����Ȃ���Ε`�悵�Ȃ�
	if (m_ParticleData.empty())
	{
		return;
	}

	// ���ʂ̕`����
	UINT strides = sizeof(Vertex);
	UINT offsets = 0;

	g_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &strides, &offsets);
	g_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	g_pDeviceContext->PSSetShader(g_pPixelShader, NULL, 0);

	for (int i = 0; i < m_ParticleData.size(); i++)
	{
		ConstBuffer cb;

		//�v���W�F�N�g�ύX�s����쐬
		cb.matrixProj = DirectX::XMMatrixOrthographicLH(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 3.0f);
		cb.matrixProj = DirectX::XMMatrixTranspose(cb.matrixProj);

		//���[���h�ϊ��s��̐���
		//���I�u�W�F�N�g�̈ʒu�E�傫���E�������w�肷��
		cb.matrixWorld = DirectX::XMMatrixScaling(m_ParticleData[i].Size.x, m_ParticleData[i].Size.y, m_ParticleData[i].Size.z);
		cb.matrixWorld *= DirectX::XMMatrixRotationZ(m_Angle * DirectX::XM_PI / 180);

		cb.matrixWorld *= DirectX::XMMatrixTranslation(m_ParticleData[i].Pos.x, m_ParticleData[i].Pos.y, m_ParticleData[i].Pos.z);
		cb.matrixWorld = DirectX::XMMatrixTranspose(cb.matrixWorld);

		// UV�A�j���[�V�����̍s��쐬
		float u = (float)m_Num.numU / splitx;
		float v = (float)m_Num.numV / splity;
		float uSize = 1.0f / splitx;
		float vSize = 1.0f / splity;

		// UV���W�̃I�t�Z�b�g�ƃX�P�[�����O��K�p
		cb.matrixTex = DirectX::XMMatrixScaling(uSize, vSize, 1.0f);
		cb.matrixTex *= DirectX::XMMatrixTranslation(u, v, 0.0f);
		cb.matrixTex = DirectX::XMMatrixTranspose(cb.matrixTex);

		//���_�J���[�̃f�[�^���쐬
		cb.color = m_ParticleData[i].Color;

		//�s����V�F�[�_�ɓn��
		g_pDeviceContext->UpdateSubresource(g_pConstantBuffer, 0, NULL, &cb, 0, 0);

		//Drwa�͍��Z�b�g����Ă�����̂�`�悷��
		g_pDeviceContext->Draw(UINT(m_CircleVertex.size()), 0);
	}
}

// ==========================================
// �p�[�e�B�N���̐����֐�
// ==========================================
void ParticleManager::ParticleCreate(DirectX::XMFLOAT3 _ParticlePos, DirectX::XMFLOAT3 _ParticleSize, DirectX::XMFLOAT4 _ParticleColor,float _DeleteTime,
	DirectX::XMFLOAT3 _MovePower)
{
	PARTICLESTATES particle;
	particle.Pos = _ParticlePos;
	particle.Size = _ParticleSize;
	particle.Color = _ParticleColor;
	particle.DeleteTime = _DeleteTime;
	particle.MovePower = _MovePower;
	QueryPerformanceCounter(&particle.Time);
	m_ParticleData.push_back(particle);
}

// ==========================================
// �`�悷��~�̒��_�����߂�
// ==========================================
void ParticleManager::Circle(float _Radius)
{
	// ������
	m_CircleVertex.fill({ 0.0f,  0.0f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f   ,0.0f, 0.0f });
	// �`�悷��~�̔��~�ɂ������_��
	int CircleVertexNumber = 20;
	// ��̒��_�̊p�x�����߂�
	float Angle = 180.0f / CircleVertexNumber;
	
	int j = 0;

	// ���_�̈ʒu�����߂�
	for (int i = 0; i < CircleVertexNumber; i++)
	{
		// ������
		Vertex VertexList = { 0.0f,  0.0f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f   ,0.0f, 0.0f };
		// X�����߂�
		VertexList.x = _Radius * cos((Angle * i) * DirectX::XM_PI / 180.0f);
		// Y�����߂�
		VertexList.y = _Radius * sin((Angle * i) * DirectX::XM_PI / 180.0f);

		// �R���e�i�ɕۑ�����
		m_CircleVertex[j] = VertexList;
		j++;

		// X�������Ƃ��́[Y�����߂�
		VertexList.y = _Radius * sin((-Angle * i) * DirectX::XM_PI / 180.0f);

		// �R���e�i�ɕۑ�����
		m_CircleVertex[j] = VertexList;
		j++;
	}
}