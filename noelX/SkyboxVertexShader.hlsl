cbuffer Cbuff
{
	matrix transform;
};
struct VSOut
{
	float4 pos: SV_POSITION;
	float3 tex: TEXCOORD;
};


VSOut main( float3 pos : POSITION, float2 tex : TEXCOORD ) 
{
	VSOut vso;
	vso.pos = mul(float4(pos, 1.0f), transform).xyww;
	vso.tex = pos;
	return vso;
}