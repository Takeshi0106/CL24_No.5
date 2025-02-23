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

    // 縦と横の要素数を取得
    std::set<int> rowSet, colSet;
    for (const auto& entry : m_MapData) {
        rowSet.insert(entry.first.first);  
        colSet.insert(entry.first.second); 
    }

    m_Row = static_cast<int>(rowSet.size());
    m_Column = static_cast<int>(colSet.size());

    // サイズを取得する
    m_Size.x = SCREEN_WIDTH / 10;
    m_Size.y = SCREEN_HEIGHT / 10;

    // タイルの位置を取得する
    for (int i = 0; i < m_Row; i++) // 縦
    {
        for (int j = 0; j < m_Column; j++) // 横
        {
			if (m_MapData[{i, j}] != 0)
			{
				m_TilePosDatas.push_back({ -SCREEN_WIDTH / 2 + m_Size.x * j + m_Size.x / 2,
					SCREEN_HEIGHT / 2 - m_Size.y * i - m_Size.y / 2,
					0.0f });
			}
        }
    }

	// タイルの色を設定
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

	// 共通の描画情報
	UINT strides = sizeof(Vertex);
	UINT offsets = 0;

	g_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &strides, &offsets);
	g_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	g_pDeviceContext->PSSetShader(g_pPixelShader, NULL, 0);

	for (int i = 0; i < m_TilePosDatas.size(); i++)
	{
		ConstBuffer cb;

		//プロジェクト変更行列を作成
		cb.matrixProj = DirectX::XMMatrixOrthographicLH(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 3.0f);
		cb.matrixProj = DirectX::XMMatrixTranspose(cb.matrixProj);

		//ワールド変換行列の生成
		//→オブジェクトの位置・大きさ・向きを指定する
		cb.matrixWorld = DirectX::XMMatrixScaling(m_Size.x, m_Size.y, m_Size.z);
		cb.matrixWorld *= DirectX::XMMatrixRotationZ(m_Angle * DirectX::XM_PI / 180);

		cb.matrixWorld *= DirectX::XMMatrixTranslation(m_TilePosDatas[i].x, m_TilePosDatas[i].y, m_TilePosDatas[i].z);
		cb.matrixWorld = DirectX::XMMatrixTranspose(cb.matrixWorld);

		// UVアニメーションの行列作成
		float u = (float)m_Num.numU / splitx;
		float v = (float)m_Num.numV / splity;
		float uSize = 1.0f / splitx;
		float vSize = 1.0f / splity;

		// UV座標のオフセットとスケーリングを適用
		cb.matrixTex = DirectX::XMMatrixScaling(uSize, vSize, 1.0f);
		cb.matrixTex *= DirectX::XMMatrixTranslation(u, v, 0.0f);
		cb.matrixTex = DirectX::XMMatrixTranspose(cb.matrixTex);

		//頂点カラーのデータを作成
		cb.color = m_Color;

		//行列をシェーダに渡す
		g_pDeviceContext->UpdateSubresource(g_pConstantBuffer, 0, NULL, &cb, 0, 0);

		//Drwaは今セットされているものを描画する
		g_pDeviceContext->Draw(6, 0);
	}
}

void TileManager::ColliderTile(std::shared_ptr<Character> _character)
{
	// キャラクターの位置と大きさを取得
	DirectX::XMFLOAT3 CharacterCollider = _character->GetPlayerColliderSize();
	DirectX::XMFLOAT3 CharacterPos = _character->GetPos();

	// 総当たりで当たっているタイルを探す
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