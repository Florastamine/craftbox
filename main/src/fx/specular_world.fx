/***********************************************************************************************
/	Copyright 2006	by Taco Cohen. All rights reserved							
/***********************************************************************************************/

/***********************************************************************************************
/	Global Variables:
/***********************************************************************************************/
// Tweakables:
static const float AmbientIntensity	= 1.0f;					// The intensity of the ambient light.
static const float DiffuseIntensity = 1.0f;					// The intensity of the diffuse light.
static const float SpecularIntensity = 3.0f;				// The intensity of the specular light.
static const float SpecularPower = 8.0f;					// The specular power. Used as 'glossyness' factor.
float4 vecSunColor;

// Application fed data:
const float4x4 matWorldViewProj;	// World*view*projection matrix.
const float4x4 matWorld;			// World matrix.
const float4 vecAmbient;			// Ambient color.
const float4 vecSunDir;				// The sun direction vector.
const float4 vecViewPos;			// View position.

texture entSkin1; 							// Color map.
sampler ColorMapSampler = sampler_state		// Color map sampler.
{
	Texture = <entSkin1>;
	AddressU  = Wrap;
	AddressV  = Wrap;
};

/***********************************************************************************************
/	Vertex Shader:
/***********************************************************************************************/
void SpecularVS(in float4 InPos		: POSITION,
				in float3 InNormal	: NORMAL,
				in float2 InTex		: TEXCOORD0,
				
				out float4 OutPos	: POSITION,
				out float2 OutTex	: TEXCOORD0,
				out float3 OutNormal: TEXCOORD1,
				out float3 OutViewDir: TEXCOORD2)
{
	// Transform the vertex from object space to clip space:
	OutPos = mul(InPos, matWorldViewProj);
	
	// Pass the texture coordinate to the pixel shader:
	OutTex = InTex;
	
	// Pass the normal to the pixel shader:
	OutNormal = InNormal;
	
	// Calculate a vector from the vertex to the view:
	OutViewDir = vecViewPos - mul(InPos, matWorld);
}


/***********************************************************************************************
/	Pixel Shader:
/***********************************************************************************************/
float4 SpecularPS(	in float2 InTex		: TEXCOORD0,
					in float3 InNormal	: TEXCOORD1,
					in float4 InViewDir	: TEXCOORD2) : COLOR
{
	// Calculate the ambient term:
	float4 Ambient = AmbientIntensity * vecAmbient;
	
	// Calculate the diffuse term:
	InNormal = normalize(InNormal);
	float4 Diffuse = DiffuseIntensity * saturate(dot(vecSunDir, InNormal));
	Diffuse *= vecSunColor;
	
	// Fetch the pixel color from the color map:
	float4 Color = tex2D(ColorMapSampler, InTex);
	
	// Calculate the reflection vector:
	float3 R = normalize(2 * dot(InNormal, vecSunDir) * InNormal - vecSunDir);
	
	// Calculate the speculate component:
	InViewDir = normalize(InViewDir);
	float Specular = pow(saturate(dot(R, InViewDir)), SpecularPower) * SpecularIntensity;
	
	// Calculate final color:
	return (Ambient + Diffuse + Specular) * Color;
}

/***********************************************************************************************
/	Technique:
/***********************************************************************************************/
technique SpecularTechnique
{
	pass P0
	{
		VertexShader = compile vs_2_0 SpecularVS();
		PixelShader  = compile ps_2_0 SpecularPS();
	}
}