cbuffer cBuff
{
	float4 side_color[6];
};



float4 main(uint tid : SV_PrimitiveID) : SV_TARGET
{
	return side_color[tid/2];
}
