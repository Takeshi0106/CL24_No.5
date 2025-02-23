#include "TileManager.h"
#include "MapFileOperations.h"
#include "direcgt3d.h"
#include "Character.h"

#include <set>

TileManager::TileManager(string _FileName)
{
	Init(_FileName);
}

void TileManager::Init(string _FileName)
{
	MapFileOperations operation;
	m_MapData = operation.GetMapDate(_FileName);

    // �c�Ɖ��̗v�f�����擾
    std::set<int> rowSet, colSet;
    for (const auto& entry : m_MapData) {
        rowSet.insert(entry.first.first);  
        colSet.insert(entry.first.second); 
    }

    m_Row = static_cast<int>(rowSet.size());
    m_Column = static_cast<int>(colSet.size());

    // �T�C�Y���擾����
    m_Size.x = SCREEN_WIDTH / 10;
    m_Size.y = SCREEN_HEIGHT / 10;

    // �^�C���̈ʒu���擾����
    for (int i = 0; i < m_Row; i++) // �c
    {
        for (int j = 0; j < m_Column; j++) // ��
        {
			if (m_MapData[{i, j}] != 0)
			{
				m_TilePosDatas.push_back({ -SCREEN_WIDTH / 2 + m_Size.x * j + m_Size.x / 2,
					SCREEN_HEIGHT / 2 - m_Size.y * i - m_Size.y / 2,
					0.0f });
			}
        }
    }

	// �^�C���̐F��ݒ�
	m_Color = { 0.545f,0.271f,0.075f,1.0f };
}

void TileManager::Update()
{

}

void TileManager::Draw()
{
	if (m_TilePosDatas.empty())
	{
		return;
	}

	// ���ʂ̕`����
	UINT strides = sizeof(Vertex);
	UINT offsets = 0;

	g_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &strides, &offsets);
	g_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	g_pDeviceContext->PSSetShader(g_pPixelShader, NULL, 0);

	for (int i = 0; i < m_TilePosDatas.size(); i++)
	{
		ConstBuffer cb;

		//�v���W�F�N�g�ύX�s����쐬
		cb.matrixProj = DirectX::XMMatrixOrthographicLH(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 3.0f);
		cb.matrixProj = DirectX::XMMatrixTranspose(cb.matrixProj);

		//���[���h�ϊ��s��̐���
		//���I�u�W�F�N�g�̈ʒu�E�傫���E�������w�肷��
		cb.matrixWorld = DirectX::XMMatrixScaling(m_Size.x, m_Size.y, m_Size.z);
		cb.matrixWorld *= DirectX::XMMatrixRotationZ(m_Angle * DirectX::XM_PI / 180);

		cb.matrixWorld *= DirectX::XMMatrixTranslation(m_TilePosDatas[i].x, m_TilePosDatas[i].y, m_TilePosDatas[i].z);
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
		cb.color = m_Color;

		//�s����V�F�[�_�ɓn��
		g_pDeviceContext->UpdateSubresource(g_pConstantBuffer, 0, NULL, &cb, 0, 0);

		//Drwa�͍��Z�b�g����Ă�����̂�`�悷��
		g_pDeviceContext->Draw(6, 0);
	}
}

void TileManager::ColliderTile(std::shared_ptr<Character> _character)
{
	// �L�����N�^�[�̈ʒu�Ƒ傫�����擾
	DirectX::XMFLOAT3 CharacterCollider = _character->GetPlayerColliderSize();
	DirectX::XMFLOAT3 CharacterPos = _character->GetPos();

	// ��������œ������Ă���^�C����T��
	for (int i = 0; i < m_TilePosDatas.size(); i++)
	{
		if (CharacterPos.x + CharacterCollider.x / 2 >= m_TilePosDatas[i].x - m_Size.x / 2 &&
			CharacterPos.x - CharacterCollider.x / 2 <= m_TilePosDatas[i].x + m_Size.x / 2 &&
			CharacterPos.y + CharacterCollider.y / 2 >= m_TilePosDatas[i].y - m_Size.y / 2 &&
			CharacterPos.y - CharacterCollider.y / 2 <= m_TilePosDatas[i].y + m_Size.y / 2)
		{
			_character->SetHitInformation({ TILE,m_TilePosDatas[i],m_Size });
		}
	}
}