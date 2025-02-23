#pragma once

// ==================================
// オブジェクトの基底クラス
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

	//座標
	DirectX::XMFLOAT3 m_Pos = { 0.0f,0.0f,0.0f };
	//大きさ
	DirectX::XMFLOAT3 m_Size = { 100.0f,100.0f,0.0f };
	//色
	DirectX::XMFLOAT4 m_Color = { 1.0f,1.0f,1.0f,1.0f };
	//角度
	float m_Angle = 0.0f;

	//テクスチャが横縦に何分割されているか
	int splitx = 1;
	int splity = 1;

	//左上から何枚目を切り取るのか
	NUM m_Num = { 0,0 };

	// テクスチャフラグ
	bool m_TextureFlag = false;

	ID3D11Buffer* m_pVertexBuffer;              //頂点バッファ変数
	ID3D11ShaderResourceView* m_pTextureView;   //テクスチャ用変数

public:
	Object();
	~Object();

	virtual void Init();
	virtual void Update();
	virtual void Draw();
	void Uninit();

	void ObjectDraw();

	void TextureLoad(const wchar_t* imgname, int sx = 1, int sy = 1);


	// 位置のセッター
	void SetPos(XMFLOAT3 _Pos);
	// 位置のーゲッター
	DirectX::XMFLOAT3 GetPos(void);
	// 大きさのセッター
	void SetSize(XMFLOAT3 _Size);
	// 大きさのゲッター
	DirectX::XMFLOAT3 GetSize(void);
	// 角度のセッター
	void SetAngle(float _Angle);
	// 角度のゲッター
	float GetAngle(void);
	// UV座標のセッター
	void SetNum(NUM _num);
	// UV座標のゲッター
	NUM GetNum();
	// 色のセッター
	void SetColor(XMFLOAT4 _Color);
	// 色のゲッター
	DirectX::XMFLOAT4 GetColor(void);//色をゲット
};