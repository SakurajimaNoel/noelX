cbuffer cBuff
{
    float3 lightPosition;
    float3 ambient;
    float3 diffuseColor;
    float diffuseIntensity;
    float attConst;
    float attLin;
    float attQuad;
};

cbuffer oBuff
{
    float3 materialColor;
    float specularIntensity;
    float specularPower;
};

Texture2D tex;
SamplerState smplr;


float4 main(float3 worldPos : POSITION, float3 normal : NORMAL, float2 tc : Texcoord) : SV_Target
{
    const float3 vtol = lightPosition - worldPos;
    const float dtol = length(vtol);
    const float3 dirtol = vtol / dtol;
	
    const float attenuation = 1.0f / (attConst + attLin * dtol + attQuad * (dtol * dtol));
	
    const float3 diffuse = diffuseColor * diffuseIntensity * attenuation * max(0.0f, dot(dirtol, normal));
	
    const float3 w = normal * dot(dirtol, normal);
    const float3 r = w * 2.0f - dirtol;

    const float3 specular = attenuation * (diffuseColor * diffuseIntensity) * specularIntensity * pow(max(0.0f, dot(normalize(r), normalize(worldPos))), specularPower);
    return float4(saturate(diffuse + ambient + specular), 1.0f) * tex.Sample(smplr,tc);

}