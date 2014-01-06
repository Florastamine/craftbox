float4 vecViewPort;

float dofTapping_flt;

static const int num_poisson_taps = 12;
static const float2 fTaps_Poisson [num_poisson_taps] =
{
	{-.326,-.406},
	{-.840,-.074},
	{-.696, .457},
	{-.203, .621},
	{ .962,-.195},
	{ .473,-.480},
	{ .519, .767},
	{ .185,-.893},
	{ .507, .064},
	{ .896, .412},
	{-.322,-.933},
	{-.792,-.598}
};

texture mtlSkin1;
sampler smpSource = sampler_state
{
	texture = <mtlSkin1>;
};

float4 PS (float2 Tex: TEXCOORD0) : COLOR0
{
	float factor = 4;

	float3 color = 0;

	for (int i = 0; i < num_poisson_taps; i++)
		color += tex2D(smpSource, factor * (Tex + vecViewPort.zw * dofTapping_flt * fTaps_Poisson[i])).rgb;

	color /= num_poisson_taps;

   return(float4(color, 1.0));
}

technique t
{
	pass p
	{
		PixelShader = compile ps_2_0 PS();
	}
}