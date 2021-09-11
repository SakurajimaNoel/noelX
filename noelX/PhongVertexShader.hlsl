cbuffer Cbuff
{
	//matrix model;
	matrix transform;
	
};
static const float4x4 model =
{
1, 0, 0, 0, 
0, 1, 0, 0, 
0, 0, 1, 0,
0, 0, 0, 1
};

struct VSOut
{
	float3 worldPos : Position;
	float3 normal : Normal;
	float4 pos : SV_Position;
};

VSOut main(
	float3 pos : POSITION, float3 n : NORMAL)
{
	VSOut vso;
	vso.worldPos = (float3) mul(float4(pos, 1.0f), model);
	vso.normal = mul(n, (float3x3) model);
	vso.pos = mul(float4(pos, 1.0f), transform);
	return vso;
}