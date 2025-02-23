#include"Object.h"

Object::Object()
{
	Init();
}

Object::~Object()
{
	Uninit();
}

void Object::Init()
{
	Vertex vertexList[4] =
	{
		//  {    x,     y,    z,    red, green, blue, alpha    U    V}
			{ -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f   ,0.0f, 0.0f},
			{  0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f   ,1.0f, 0.0f },
			{ -0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f   ,0.0f, 1.0f },
			{  0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f   ,1.0f, 1.0f },
	};

	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = sizeof(vertexList);// 確保するバッファサイズを指定
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;// 頂点バッファ作成を指定
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	//vertexList
	D3D11_SUBRESOURCE_DATA subResourceData;
	subResourceData.pSysMem = vertexList;// VRAMに送るデータを指定
	subResourceData.SysMemPitch = 0;
	subResourceData.SysMemSlicePitch = 0;

	HRESULT hr = g_pDevice->CreateBuffer(&bufferDesc, &subResourceData, &m_pVertexBuffer);

	// テクスチャを使うかのフラグ
	m_TextureFlag = false;
}

void Object::Update()
{

}

void Object::Draw()
{
	ObjectDraw();
}

void Object::Uninit()
{
	SAFE_RELEASE(m_pVertexBuffer);
	if (m_TextureFlag == true)
	{
		SAFE_RELEASE(m_pTextureView);
	}
}

void Object::ObjectDraw()
{
	UINT strides = sizeof(Vertex);
	UINT offsets = 0;

	g_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	g_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &strides, &offsets);

	if (m_TextureFlag)
	{
		g_pDeviceContext->PSSetShader(g_pTextureShader, NULL, 0);
		g_pDeviceContext->PSSetShaderResources(0, 1, &m_pTextureView);
	}
	else
	{
		g_pDeviceContext->PSSetShader(g_pPixelShader, NULL, 0);
	}
	ConstBuffer cb;

	//プロジェクト変更行列を作成
	cb.matrixProj = DirectX::XMMatrixOrthographicLH(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 3.0f);
	cb.matrixProj = DirectX::XMMatrixTranspose(cb.matrixProj);

	//ワールド変換行列の生成
	//→オブジェクトの位置・大きさ・向きを指定する
	cb.matrixWorld = DirectX::XMMatrixScaling(m_Size.x, m_Size.y, m_Size.z);
	cb.matrixWorld *= DirectX::XMMatrixRotationZ(m_Angle *  DirectX::XM_PI / 180);

	cb.matrixWorld *= DirectX::XMMatrixTranslation(m_Pos.x, m_Pos.y, m_Pos.z);
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

void Object::TextureLoad(const wchar_t* imgname, int sx, int sy)
{
	splitx = sx;
	splity = sy;

	HRESULT hr = DirectX::CreateWICTextureFromFileEx(g_pDevice, g_pDeviceContext, imgname,
		0, D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		DirectX::WIC_LOADER_IGNORE_SRGB, nullptr, &m_pTextureView);
	if (FAILED(hr)) {
		MessageBoxA(NULL, "テクスチャ読込失敗", "エラー", MB_ICONERROR | MB_OK);
		return;
	}
	m_TextureFlag = true;
}

void Object::SetPos(XMFLOAT3 _Pos)
{
	m_Pos = _Pos;
}

void Object::SetSize(XMFLOAT3 _Size)
{
	m_Size = _Size;
}

void Object::SetAngle(float _Angle)
{
	m_Angle = _Angle;
}

void Object::SetNum(NUM _Num)
{
	m_Num = _Num;
}

void Object::SetColor(XMFLOAT4 _Color)
{
	m_Color = _Color;
}

DirectX::XMFLOAT3 Object::GetPos(void)
{
	return m_Pos;
}

DirectX::XMFLOAT3 Object::GetSize(void)
{
	return m_Size;
}

float Object::GetAngle(void)
{
	return m_Angle;
}

DirectX::XMFLOAT4 Object::GetColor(void)
{
	return m_Color;
}

NUM Object::GetNum()
{
	return m_Num;
}