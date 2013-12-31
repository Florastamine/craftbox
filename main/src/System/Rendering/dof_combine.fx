float dofNearPlane_flt;
float dofFocalBegin_flt;
float dofFocalEnd_flt;
float dofFarPlane_flt;

Texture mtlSkin1;
sampler2D smpSource = sampler_state{texture=<mtlSkin1>;}; // diffuse

Texture mtlSkin2;
sampler2D smpBlur = sampler_state{texture=<mtlSkin2>;}; // blur

Texture mtlSkin3;
sampler2D smpDepth = sampler_state{texture=<mtlSkin3>;}; // depth

	texture bmapSsaoNormalHires_bmap;
	sampler2D smpNormal = sampler_state {
		Texture = <bmapSsaoNormalHires_bmap>;
		AddressU	= clamp;
		AddressV	= clamp;
		MipFilter = Point;
		MagFilter = Point;
	};

float4 PS (float2 Tex: TEXCOORD0) : COLOR0
{
	int HD = 2;
	int LD = 4;

	float depth = tex2D(smpDepth,Tex / HD).r;

	float blend = 0.0;

	if ((depth < dofNearPlane_flt) || (depth > dofFarPlane_flt))
	{
		blend = 1.0;
	}
	else
	{
		if (depth < dofFocalBegin_flt)
		{
			blend = 1 - ((depth - dofNearPlane_flt) / (dofFocalBegin_flt - dofNearPlane_flt));
		}
		else
		{
			if (depth > dofFocalEnd_flt)
			{
				blend = (depth - dofFocalEnd_flt) / (dofFarPlane_flt - dofFocalEnd_flt);
			}
		}
	}

	blend = saturate(blend);

	float3 diffuse = tex2D(smpSource, Tex / HD).rgb;
	float3 blur    = tex2D(smpBlur, Tex / LD).rgb;

	float3 color   = lerp(diffuse, blur, blend);

	return(float4(color, 1.0));
}

technique t
{
	pass p
	{
		PixelShader = compile ps_2_0 PS();
	}
}