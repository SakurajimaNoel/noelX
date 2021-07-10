struct PSin
{
	float4 pos : SV_POSITION;
	float3 tex : TEXCOORD;
};

TextureCube tex;

SamplerState smplr;

float4 main(PSin ps) : SV_TARGET
{
	return tex.Sample(smplr, ps.tex);
}