#pragma once

// ==============================================================================================
// パーティクルが発生している場所をListに保存しておいてその場所に丸を描画する関数
// ParticleCreate関数()で場所を指定してください
// ==============================================================================================

#include "Object.h"
#include <array>
#include <deque>

struct PARTICLESTATES {
	// 場所
	DirectX::XMFLOAT3 Pos;
	// 描画サイズ
	DirectX::XMFLOAT3 Size;
	// 描画開始時間
	LARGE_INTEGER Time;
	// パーティクルの色
	DirectX::XMFLOAT4 Color;
	// パーティクルが消えるまでの時間
	float DeleteTime;
	// パーティクルの移動量
	DirectX::XMFLOAT3 MovePower;
};

class ParticleManager : public Object
{
private:
	// Circleの半径
	float m_Radius = 0.1f;
	// circleの頂点を入れる
	std::array<Vertex, 40> m_CircleVertex;
	// パーティクルの情報を入れておく
	static std::deque<PARTICLESTATES> m_ParticleData;

public:
	// コンストラクタ・デストラクタ
	ParticleManager();
	~ParticleManager();

	// 
	void Init();
	void Update();
	void Draw();

	// パーティクルの生成(引数で描画する場所を渡す)
	static void ParticleCreate(DirectX::XMFLOAT3 _ParticlePos,DirectX::XMFLOAT3 _ParticleSize, DirectX::XMFLOAT4 _ParticleColor,float _DeleteTime,
		DirectX::XMFLOAT3 _MovePower);

	// 円の頂点を求める（引数で円の半径を渡す。）
	void Circle(float _Radius);
};