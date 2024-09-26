
//Base pixel shader
struct PS_INPUT 
{
	
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
	
};

struct MaterialData
{
    float4 diffuseAlbedo;
};

struct LightData
{
    float3 position;
    float strength;
    float3 direction;
    float padding;
};

struct PassData
{
    float4x4 viewproj;
    LightData light;
};

ConstantBuffer<PassData> gPassData : register(b0);
ConstantBuffer<MaterialData> gMaterialData : register(b2);


float4 main(PS_INPUT input) : SV_TARGET
{
    float intensity = max(0.02f, dot(-(normalize(gPassData.light.direction)), normalize(input.normal)));
   
    return gMaterialData.diffuseAlbedo * intensity;

}