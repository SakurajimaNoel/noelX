struct vsOut
{
	float4 color : COLOR;
	float4 pos : SV_POSITION;
};

cbuffer cBuff
{
	 matrix transform;
};
vsOut main( float3 pos : POSITION, float4 color:COLOR )
{
	vsOut vso;
	vso.pos = mul(float4(pos, 1.0f), transform);
	vso.color = color;
	return vso;
}