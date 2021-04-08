struct vsOut
{
	float4 color : COLOR;
	float4 pos : SV_POSITION;
};

vsOut main( float3 pos : POSITION, float4 color:COLOR )
{
	vsOut vso;
	vso.pos = float4(pos.x, pos.y, pos.z, 1.0f);
	vso.color = color;
	return vso;
}