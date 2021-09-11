cbuffer cBuff
{
	float3 lightPosition;
};

static const float3 materialColor =
{ 0.7f, 0.7f, 0.9f };

static const float3 ambient =
{ 0.05f, 0.05f, 0.05f };

static const float3 diffuseColor =
{ 1.0f, 1.0f, 1.0f };

static const float diffuseIntensity = 1.0f;

static const float attConst = 1.0f;

static const float attLin = 0.045f;

static const float attQuad = 0.0075f;


float4 main(float3 worldPos : POSITION, float3 normal : NORMAL) : SV_Target
{
	const float3 vtol = lightPosition - worldPos;
	const float dtol = length(vtol);
	const float3 dirtol = vtol / dtol;
	
    const float attenuation = 1.0f / (attConst + attLin * dtol + attQuad * (dtol * dtol));
	
	const float3 diffuse = diffuseColor * diffuseIntensity * attenuation * max(0.0f, dot(dirtol, normal));
		
	return float4(saturate(diffuse + ambient), 1.0f);

}