struct PSin
{
	float4 pos : SV_POSITION;
	float2 tex : TEXCOORD;
};

Texture2D tex;

SamplerState smplr;

float4 main(PSin ps) : SV_TARGET
{
	return tex.Sample(smplr, ps.tex);
}