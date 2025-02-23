#pragma once

//■■■■■■■■■■■■■■■■■■■■■■■■■
//↓direcgt3d.hへ移動

#include <d3d11.h>  // DirectX11を使うためのヘッダーファイル
#include<DirectXMath.h>

#define SCREEN_WIDTH (960)	// ウインドウの幅
#define SCREEN_HEIGHT (720)	// ウインドウの高さ

// 関数のプロトタイプ宣言
HRESULT D3D_Create(HWND hwnd);
void    D3D_Release();
void    D3D_StartRender();
void    D3D_FinishRender();


// ピクセルシェーダーオブジェクト
extern ID3D11PixelShader* g_pPixelShader;
// テクスチャを使うときのシェーダオブジェクト
extern ID3D11PixelShader* g_pTextureShader;

//↑direcgt3d.hへ移動
//■■■■■■■■■■■■■■■■■■■■■■■■■

// 頂点データを表す構造体
struct Vertex
{
	// 頂点の位置座標
	float x, y, z;

	//構造体に色を追加する
	float red, green, blue, alpha;

	//テクスチャ座標（UV座標）
	float u, v;
};

struct ConstBuffer {
	//頂点から―行列
	DirectX::XMFLOAT4 color;
	//UV座標移動
	DirectX::XMMATRIX matrixTex;
	DirectX::XMMATRIX matrixProj;
	DirectX::XMMATRIX matrixWorld;
};

extern ID3D11Device* g_pDevice; // デバイス＝DirectXの各種機能を作る
extern ID3D11DeviceContext* g_pDeviceContext; // コンテキスト＝描画関連を司る機能
extern ID3D11Buffer* g_pConstantBuffer;

// Direct3D解放の簡略化マクロ
#define SAFE_RELEASE(p) { if( NULL != p ) { p->Release(); p = NULL; } }