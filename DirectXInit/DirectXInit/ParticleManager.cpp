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

	// 頂点バッファ作成
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = UINT(sizeof(Vertex) * m_CircleVertex.size());// 確保するバッファサイズを指定
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;// 頂点バッファ作成を指定
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	// GPUに送る情報
	D3D11_SUBRESOURCE_DATA subResourceData;
	subResourceData.pSysMem = m_CircleVertex.data();// VRAMに送るデータを指定
	subResourceData.SysMemPitch = 0;
	subResourceData.SysMemSlicePitch = 0;

	HRESULT hr = g_pDevice->CreateBuffer(&bufferDesc, &subResourceData, &m_pVertexBuffer);
	if (FAILED(hr))
	{
		MessageBoxA(NULL, "Particlesのバッファ作成エラー", "確認", MB_OKCANCEL);
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
	// パーティクルがなければ描画しない
	if (m_ParticleData.empty())
	{
		return;
	}

	// 共通の描画情報
	UINT strides = sizeof(Vertex);
	UINT offsets = 0;

	g_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &strides, &offsets);
	g_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	g_pDeviceContext->PSSetShader(g_pPixelShader, NULL, 0);

	for (int i = 0; i < m_ParticleData.size(); i++)
	{
		ConstBuffer cb;

		//プロジェクト変更行列を作成
		cb.matrixProj = DirectX::XMMatrixOrthographicLH(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 3.0f);
		cb.matrixProj = DirectX::XMMatrixTranspose(cb.matrixProj);

		//ワールド変換行列の生成
		//→オブジェクトの位置・大きさ・向きを指定する
		cb.matrixWorld = DirectX::XMMatrixScaling(m_ParticleData[i].Size.x, m_ParticleData[i].Size.y, m_ParticleData[i].Size.z);
		cb.matrixWorld *= DirectX::XMMatrixRotationZ(m_Angle * DirectX::XM_PI / 180);

		cb.matrixWorld *= DirectX::XMMatrixTranslation(m_ParticleData[i].Pos.x, m_ParticleData[i].Pos.y, m_ParticleData[i].Pos.z);
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
		cb.color = m_ParticleData[i].Color;

		//行列をシェーダに渡す
		g_pDeviceContext->UpdateSubresource(g_pConstantBuffer, 0, NULL, &cb, 0, 0);

		//Drwaは今セットされているものを描画する
		g_pDeviceContext->Draw(UINT(m_CircleVertex.size()), 0);
	}
}

// ==========================================
// パーティクルの生成関数
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
// 描画する円の頂点を求める
// ==========================================
void ParticleManager::Circle(float _Radius)
{
	// 初期化
	m_CircleVertex.fill({ 0.0f,  0.0f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f   ,0.0f, 0.0f });
	// 描画する円の半円につかう頂点数
	int CircleVertexNumber = 20;
	// 一つの頂点の角度を求める
	float Angle = 180.0f / CircleVertexNumber;
	
	int j = 0;

	// 頂点の位置を求める
	for (int i = 0; i < CircleVertexNumber; i++)
	{
		// 初期化
		Vertex VertexList = { 0.0f,  0.0f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f   ,0.0f, 0.0f };
		// Xを求める
		VertexList.x = _Radius * cos((Angle * i) * DirectX::XM_PI / 180.0f);
		// Yを求める
		VertexList.y = _Radius * sin((Angle * i) * DirectX::XM_PI / 180.0f);

		// コンテナに保存する
		m_CircleVertex[j] = VertexList;
		j++;

		// Xが同じときのーYを求める
		VertexList.y = _Radius * sin((-Angle * i) * DirectX::XM_PI / 180.0f);

		// コンテナに保存する
		m_CircleVertex[j] = VertexList;
		j++;
	}
}