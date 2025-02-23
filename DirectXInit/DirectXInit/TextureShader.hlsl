//--------------------------------------------------------------------------------------
// テクスチャがあるときのピクセルシェーダー
//--------------------------------------------------------------------------------------
#include "heder.hlsl"

Texture2D myTexture : register(t0); //テクスチャ
SamplerState mySampler : register(s0); //サンプラー

float4 ps_main(PS_IN input) : SV_TARGET
{
    float4 color = myTexture.Sample(mySampler, input.tex);

    color *= input.col;
    return color;
}