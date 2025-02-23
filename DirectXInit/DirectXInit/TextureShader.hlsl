//--------------------------------------------------------------------------------------
// �e�N�X�`��������Ƃ��̃s�N�Z���V�F�[�_�[
//--------------------------------------------------------------------------------------
#include "heder.hlsl"

Texture2D myTexture : register(t0); //�e�N�X�`��
SamplerState mySampler : register(s0); //�T���v���[

float4 ps_main(PS_IN input) : SV_TARGET
{
    float4 color = myTexture.Sample(mySampler, input.tex);

    color *= input.col;
    return color;
}