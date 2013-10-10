float4x4 matMtl;
float4x4 matEffect1;
float4x4 matWorld;
float4x4 matProj;
float4x4 matWorldViewProj;

float light_angle_atten_begin : lightumbra = 0;
float light_angle_atten_end : lightpenumbra = 0;
float light_atten_begin = 0;
float light_atten_end = 9000.0;
float light_shadow_bias = 0.0025;
float light_vsm_epsilon = 0.0001;
//float light_shadow_bias = 0.0033;
//float light_vsm_epsilon = 0.1;
//float light_shadow_bias = 0.0033;
//float light_vsm_epsilon = 0.00001;

float4 lightPos = {0,0,0,3000};
float blurStr = 15; //shadow blur
float shadowAmbient = 0.5;

float4 vecLightPos[8];
/*
float light_angle_atten_begin = 1.99;//: lightumbra;
float light_angle_atten_end = 550;//: lightpenumbra;
float light_atten_begin = 1.0;
float light_atten_end = 10000.0;
float light_shadow_bias = 0.0033;
float light_vsm_epsilon = 0.000001;
*/
static float2 light_angle_atten =
	float2(light_angle_atten_begin, light_angle_atten_end) * 0.5;
static float2 cos_light_angle_atten = cos(light_angle_atten);
float3 light_color = {1,1,1};
float3 diffuse_color = {1,1,1};

textureCUBE mtlSkin1;
samplerCUBE cubeShadowMapSampler = sampler_state
{
	Texture = <mtlSkin1>;
    MipFilter = NONE;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

texture entSkin1;
sampler colorSampler = sampler_state
{
	Texture = <entSkin1>;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

struct LightingVSOutput
{
	float4 position_screen : POSITION;
	float3 position_world  : TEXCOORD0;
	float3 normal_world    : TEXCOORD1;
	float3 light_position  : TEXCOORD2;
	float3 light_direction : TEXCOORD3;
	float3 LightDir : TEXCOORD4;
	float2 tex : TEXCOORD5;
};

LightingVSOutput lighting_VS(
		float4 position : POSITION,
		float3 normal   : NORMAL,
		float2 inTex : TEXCOORD0,
		uniform float4x4 shadow)
{      
    LightingVSOutput output = (LightingVSOutput)0;
    output.position_screen  = mul(position, matWorldViewProj);
    output.position_world   = mul(position, matWorld).xyz;
    output.normal_world     = mul(float4(normal, 0), matWorld).xyz;
    
    // Work out the light position and direction in world space
    output.light_position   = float3(vecLightPos[0].x,vecLightPos[0].y,vecLightPos[0].z);//float3(shadow._41, shadow._42, shadow._43);
    output.light_direction  = float3(0,0,0);//float3(shadow._31, shadow._32, shadow._33);
    
    //cube-projection
    output.LightDir = (vecLightPos[0].xyz - output.position_world);// * BIAS;
    
    //texturecoords
    output.tex = inTex;
    
    return output;
}

struct LightingPSOutput
{
	float4 color : COLOR;
};



float2 g_vSampleOffsets[12] = {

   -0.00695914,  0.00457137,
   -0.00203345,  0.00620716,
    0.00962340, -0.00194983,
    0.00473434, -0.00480026,
    0.00519456,  0.00767022,
    0.00185461, -0.00893124,
    0.00507431,  0.00064425,
    0.00896420,  0.00412458,
   -0.00321940, -0.00932615,
   -0.00791559, -0.00597705,
   //
   -0.00326212, -0.00405805,
   -0.00840144, -0.0073580,

};

LightingPSOutput lighting_PS(
	LightingVSOutput input,
	uniform float4x4 shadow_view_projection)
{
	LightingPSOutput output = (LightingPSOutput)0;
	
	//float4 color = 1;
	//color.rgb = input.LightDir;
	//color.rgb = texCUBE(cubeShadowMapSampler, -float4(input.LightDir.xyz, 1.0f));
	
	// Renormalize
    float3 normal_world = normalize(input.normal_world);
    float3 light_direction = normalize(input.light_direction);

    // Sum the contributions from all lights
    float3 lit_color = float3(0, 0, 0);
      
  	// Light Shader:
  	float3 light_contrib;
  	float3 dir_to_light;
  	float  dist_to_light;
  	
  	float  n_dot_l;
  	{  		  	
    	// Unnormalized light vector
    	dir_to_light = input.light_position - input.position_world;
    	dist_to_light = length(dir_to_light);
		
		float atten_amount =
			clamp((dist_to_light   - light_atten_begin) /
        	      (light_atten_end - light_atten_begin),
        	       0.0, 1.0);
		
    	// Radial attenuation
    	dir_to_light = normalize(dir_to_light);
    	float2 cos_angle_atten = cos_light_angle_atten;
    	float  cos_angle = dot(-dir_to_light, light_direction);
    	
    	float angle_atten_amount = 
        	clamp((cos_angle         - cos_angle_atten.x) /
                  (cos_angle_atten.y - cos_angle_atten.x),
            	   0.0, 1.0);
            	   
    	// Compose the light shader outputs
    	light_contrib = (1.0 - atten_amount) * (1.0 - angle_atten_amount) * light_color;
    	n_dot_l       = dot(normal_world, dir_to_light);
  	}




	
	// Variance Shadow Mapping:
  	{
  		// Transform the surface into light space and project
  		// NB: Could be done in the vertex shader, but doing it here keeps the "light
  		// shader" abstraction and doesn't limit # of shadowed lights.
  		//float4 surf_tex = mul(float4(input.position_world, 1.0), shadow_view_projection);
    	//surf_tex = surf_tex / surf_tex.w;
    	
    	// Rescale viewport to be [0,1] (texture coordinate space)
    	//float2 shadow_tex = surf_tex.xy * float2(0.5, -0.5) + 0.5;
	
    	float4 moments;
    	// TODO: Emulate bilinear filtering on unsupporting hardware
      	moments = texCUBE(cubeShadowMapSampler, -float4(input.LightDir.xyz, 1.0f)+float4(0,0,0,0));



      	
      	/*
      	//float depthBck = 1-pow(clamp(moments.x,0,1),0.3);
      	float depthBck = moments.y;
      	    	    	
      	moments += texCUBE(cubeShadowMapSampler, -float4(input.LightDir.xyz, 1.0f)+float4(blurStr,0,0,0)*depthBck);
      	moments += texCUBE(cubeShadowMapSampler, -float4(input.LightDir.xyz, 1.0f)+float4(-blurStr,0,0,0)*depthBck);
      	moments += texCUBE(cubeShadowMapSampler, -float4(input.LightDir.xyz, 1.0f)+float4(0,blurStr,0,0)*depthBck);
      	moments += texCUBE(cubeShadowMapSampler, -float4(input.LightDir.xyz, 1.0f)+float4(0,-blurStr,0,0)*depthBck);
      	moments += texCUBE(cubeShadowMapSampler, -float4(input.LightDir.xyz, 1.0f)+float4(0,0,blurStr,0)*depthBck);
      	moments += texCUBE(cubeShadowMapSampler, -float4(input.LightDir.xyz, 1.0f)+float4(0,0,-blurStr,0)*depthBck);
      	      	
      	moments += texCUBE(cubeShadowMapSampler, -float4(input.LightDir.xyz, 1.0f)+float4(blurStr/2,0,0,0)*depthBck);
      	moments += texCUBE(cubeShadowMapSampler, -float4(input.LightDir.xyz, 1.0f)+float4(-blurStr/2,0,0,0)*depthBck);
      	moments += texCUBE(cubeShadowMapSampler, -float4(input.LightDir.xyz, 1.0f)+float4(0,blurStr/2,0,0)*depthBck);
      	moments += texCUBE(cubeShadowMapSampler, -float4(input.LightDir.xyz, 1.0f)+float4(0,-blurStr/2,0,0)*depthBck);
      	moments += texCUBE(cubeShadowMapSampler, -float4(input.LightDir.xyz, 1.0f)+float4(0,0,blurStr/2,0)*depthBck);
      	moments += texCUBE(cubeShadowMapSampler, -float4(input.LightDir.xyz, 1.0f)+float4(0,0,-blurStr/2,0)*depthBck);
      	      	
      	moments /= 13;
      	*/

      	moments.y = moments.x * moments.x;
      	//moments.y = moments.x * moments.x;
    	// Rescale light distance and check if we're in shadow
    	float rescaled_dist_to_light = dist_to_light / light_atten_end;
    	rescaled_dist_to_light -= light_shadow_bias;
    	float lit_factor = (rescaled_dist_to_light <= moments.x);
    	
    	// Variance shadow mapping
    	float E_x2 = moments.y;
    	float Ex_2 = moments.x * moments.x;
    	float variance = min(max(E_x2 - Ex_2, 0.0) + light_vsm_epsilon, 1.0);
    	float m_d = (moments.x - rescaled_dist_to_light);
    	float p = variance / (variance + m_d * m_d);
    	
    	// Adjust the light color based on the shadow attenuation
    	light_contrib *= max(lit_factor, p);
    	//light_contrib = moments.x;
  	}
	
	float self_shadow = clamp(n_dot_l * 2.0, 0.0, 1.0);
  	float3 direct_contrib = diffuse_color * n_dot_l;
	lit_color += clamp((light_contrib * 1.5)+shadowAmbient,0,1);// * self_shadow * direct_contrib;

    output.color = float4(lit_color, 1.0);
    output.color.a = tex2D(colorSampler,input.tex).a;
    return output;
}


//------------------------------------------------------------------------------
// Techniques
//------------------------------------------------------------------------------
const float4 shadow_clear <string UIWidget = "None";> = {1, 1, 1, 1};
const float4 color_clear  <string UIWidget = "None";> = {0, 0, 0, 0};
const float  depth_clear  <string UIWidget = "None";> = 1.0;

technique Main
{
	pass UseShadowMap
	{
		VertexShader = compile vs_2_0 lighting_VS(matEffect1);
		ZEnable = true;
		ZWriteEnable = true;
		ZFunc = LessEqual;
		//CullMode = None;
		PixelShader = compile ps_2_a lighting_PS(mul(matMtl, matProj));
	}	
}
