//----------------------------------------------------------------------------------------
// Combine pass; part of SSAO v0.6 for Gamestudio A7 & A8
// Copyright (C) 2010, 2011 by Christian Behrenberg
//----------------------------------------------------------------------------------------
// Permission is hereby granted, free of charge, to any person obtaining a copy of this
// software and associated documentation files (the "Software"), to deal in the Software
// without restriction, including without limitation the rights to use, copy, modify,
// merge, publish, distribute, sublicense, and/or sell copies of the Software, and to per-
// mit persons to whom the Software is furnished to do so, subject to the following con-
// ditions:
// 
// The above copyright notice and this permission notice shall be included in all copies
// or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, IN-
// CLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LI-
// ABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
// OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
//----------------------------------------------------------------------------------------

// variables

	float4 vecViewPort; // screen dimensions
	float4 vecSkill1; // z : clip_far

	#ifdef A7
	#ifndef SSAO_NO_FOG
		float4 vecFog;
		float ssaoFogNr_var;
	#endif
	#endif

// textures

	// encoding scheme (tiled 2x2 pattern)
	texture bmapSsaoAoEncode_bmap;
	sampler2D smpEncode = sampler_state {
		Texture = <bmapSsaoAoEncode_bmap>;
		AddressU = Wrap;
		AddressV = Wrap;
		MipFilter = Point;
		MagFilter = Point;
	};

	// diffuse image from camera (hires)
	texture bmapSsaoDiffuseHires_bmap;
	sampler2D smpDiffuse = sampler_state {
		Texture = <bmapSsaoDiffuseHires_bmap>;
		AddressU = clamp;
		AddressV = clamp;
		MipFilter = Point;
		MagFilter = Point;
	};

	// encoded ssao (one lores pixel = 2x2 hires pixels; lores)
	texture mtlSkin1;
	sampler2D smpEncodedAo = sampler_state {
		Texture = <mtlSkin1>;
		AddressU = clamp;
		AddressV = clamp;
		MipFilter = Point;
		MagFilter = Point;
	};

	// softalpha map (hires)
	#ifndef SSAO_NO_SOFTALPHA
	texture bmapSsaoAlphaHires_bmap;
	sampler2D smpAlpha = sampler_state {
		Texture = <bmapSsaoAlphaHires_bmap>;
		AddressU = clamp;
		AddressV = clamp;
		MipFilter = Point;
		MagFilter = Point;
	};
	#endif

	// clipped depth (hires)
	texture bmapSsaoDepthHires_bmap;
	sampler2D smpDepth = sampler_state {
		Texture = <bmapSsaoDepthHires_bmap>;
		AddressU	= clamp;
		AddressV	= clamp;
		MipFilter = Point;
		MagFilter = Point;
	};

// - Pixelshader -------------------------------------------------------------------------

	struct PS_OUT
	{
		float4 screen : COLOR0;
	};

	PS_OUT PS (float2 tex : TEXCOORD0) : COLOR
	{
		PS_OUT Out = (PS_OUT)0;

		// adapt coordinates to half sized source
		float2 coord = tex / 2;

		// fetch 2x2 ao pixle block
		float4 encodedAo = tex2D(smpEncodedAo, coord - vecViewPort.zw);

		// fetch encoding multiplier for current pixel
		float4 encode = tex2D(smpEncode, (coord + vecViewPort.zw) * (vecViewPort.xy / 2));

		// encode ao
		float ao = length(encodedAo * encode);

		#ifndef SSAO_NO_SOFTALPHA
			#if SSAO_SOFTALPHA_QUALITY == SSAO_HD
				ao = lerp(ao, 1.0, tex2D(smpAlpha, coord).x);
			#endif
		#endif

		// diffuse
		float3 diffuse = tex2D(smpDiffuse, coord).rgb;

		// A7 fog
		#ifdef A7
		#ifndef SSAO_NO_FOG

			if (ssaoFogNr_var > 0)
			{
				float depth = tex2D(smpDepth, coord);
				if (depth < vecSkill1.x)
				{
					float  fog      = (1 - saturate((vecFog.y - depth) * vecFog.z));
					float3 fogColor = vecSkill1.gba;
					diffuse = lerp(diffuse, fogColor, fog);
				}
			}

		#endif
		#endif

		Out.screen = float4(diffuse * ao, 1.0);

		return(Out);
	}

// ENTRY POINT

	technique t
	{
		pass p
		{
			VertexShader = null;
			PixelShader  = compile ps_2_0 PS();
		}
	}