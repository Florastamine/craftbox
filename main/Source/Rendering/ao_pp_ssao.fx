//----------------------------------------------------------------------------------------
// Microsphere SSAO approximation; part of SSAO v0.6 for Gamestudio A7 & A8
// Copyright 2010, 2011 Christian Behrenberg, Nils Daumann
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

// CONSTANTS

	static const float SAMPLES_x8_INV = 1.0f / (SSAO_SAMPLES * 8.0f);

	// 4X4 ROTATION VECTORS
	// Whereas: (x,y,z) := vector, (z) := h = 1 / (1 + rotation.z)
	static const float4 rotationVectors [16] = {
		float4(0.491615f, 0.118215f, 0.177246f, 0.849440134f),
		float4(0.739493f, 0.206308f, 0.826172f, 0.547593545f),
		float4(0.048045f, 0.461949f, 0.289551f, 0.775463708f),
		float4(0.95784f, 0.543049f, 0.696289f, 0.589522186f),
		float4(0.310442f, 0.716885f, 0.908691f, 0.523919272f),
		float4(0.678633f, 0.805715f, 0.853027f, 0.539657544f),
		float4(0.398608f, 0.53607f, 0.011719f, 0.988416744f),
		float4(0.82324f, 0.509473f, 0.881348f, 0.531533773f),
		float4(0.432835f, 0.564812f, 0.991211f, 0.502206948f),
		float4(0.049856f, 0.284607f, 0.46875f, 0.680851064f),
		float4(0.117131f, 0.194883f, 0.398438f, 0.715083543f),
		float4(0.306352f, 0.182266f, 0.833984f, 0.545261027f),
		float4(0.202412f, 0.89876f, 0.549316f, 0.645446119f),
		float4(0.31965f, 0.35541f, 0.943359f, 0.514572964f),
		float4(0.633371f, 0.110118f, 0.216797f, 0.821829771f),
		float4(0.340142f, 0.973354f, 0.480469f, 0.675461627f)
	};

// VARIABLES

	float4 vecViewPort;
	float ssaoRatioNearDistantOccluders_flt;
	float ssaoConvexHighlight_flt;
	float ssaoConcaveDarkness_flt;

	#ifndef SSAO_NO_FOG
		float4 vecFog;
	#endif

	float4 vecSkill1; // x: near clipping, y: far clipping, z: fog in use (1,0), w: inverse of z

// INPUT DATA

	texture bmapSsaoDepthHires_bmap;
	sampler2D smpDepth = sampler_state {
		Texture = <bmapSsaoDepthHires_bmap>;
		AddressU	= clamp;
		AddressV	= clamp;
	};

	texture bmapSsaoNormalHires_bmap;
	sampler2D smpNormal = sampler_state {
		Texture = <bmapSsaoNormalHires_bmap>;
		AddressU	= clamp;
		AddressV	= clamp;
	};

   #ifndef SSAO_NO_SOFTALPHA
	texture bmapSsaoAlphaHires_bmap;
	sampler2D smpAlpha = sampler_state {
		Texture = <bmapSsaoAlphaHires_bmap>;
		AddressU	= clamp;
		AddressV	= clamp;
	};
	#endif

// - Pixelshader -------------------------------------------------------------------------

struct PS_IN
{
	float2 coord : TEXCOORD0;
};

struct PS_OUT
{
	float4 aoX_depthY : COLOR0;
	float4 normalXYZ_processedW : COLOR1;
};

PS_OUT PS (PS_IN In) : COLOR
{
	PS_OUT Out = (PS_OUT)0;

	float2 coord = In.coord * 2;
	float depth = tex2D(smpDepth, coord).r;
	
	#ifndef SSAO_NO_SKY
		clip(vecSkill1.y - depth);
	#endif
	
	float3 normal = tex2D(smpNormal, coord).xyz;
	
	#ifndef SSAO_NO_SOFTALPHA
		#if SSAO_SOFTALPHA_QUALITY == SSAO_LD
			float alpha = tex2D(smpAlpha, coord).x;
		#endif
	#endif

	float2 clipping = vecSkill1.xy;

	#ifndef SSAO_NO_FOG
		float2 fogUse = vecSkill1.zw;
		float fog = fogUse[0] * (1 - saturate((vecFog.y - depth) * vecFog.z)) - fogUse[1];
	#endif

	float ao = 1;

	#ifdef SSAO_NO_FOG
	if (depth > clipping.x)
	#else
	if ((depth > clipping.x) && (fog < fogUse[0]))
	#endif
	{
		// Build rotation matrix
		float3x3 rotMat;
		{
			// Fetch rotation vector

				int2 pixel = (int2)(In.coord.xy * vecViewPort.xy) % 4;
				float4 rotation = rotationVectors[pixel.x * 4 + pixel.y];

			// Note: if you use lookups instead of static vectors, calculate the h with
			// the following formula and replace the precalculated h's (stored in
			// rotation.w) through your own h value!
			//
			// float h = 1.0f / (1.0f + rotation.z);

			// Built rotation matrix
			rotMat._m00 =  rotation.w * rotation.y * rotation.y + rotation.z;
			rotMat._m01 = -rotation.w * rotation.y * rotation.x;
			rotMat._m02 = -rotation.x;
			rotMat._m10 =  rotMat._m01;
			rotMat._m11 =  rotation.w * rotation.x * rotation.x + rotation.z;
			rotMat._m12 = -rotation.y;
			rotMat._m20 = rotation.x;
			rotMat._m21 = rotation.y;
			rotMat._m22 = rotation.z;
		}


		float offsetScale = 0.01;
		float offsetScaleStep = 1 + SSAO_SAMPLE_SCALE_STEP * SAMPLES_x8_INV;

		float Accessibility = 0;

		float3 vOffset;
		float3 vRotatedOffset;
		float3 occluderPos;
		float occluderPositionDepth;
		float occluderSurfaceDepth;
		float	rangeIsInvalid;

		for (int i = 0; i < SSAO_SAMPLES; i++)
		{
			for (int x = -1; x <= 1; x += 2)
			{
				for (int y = -1; y <= 1; y += 2)
				{
					for (int z = -1; z <= 1; z += 2)
					{
						#define cubeNrm 0.5773502692f
						vOffset = cubeNrm * float3(x, y, z) * (offsetScale *= offsetScaleStep);
						
						vRotatedOffset = mul(vOffset, rotMat);

						// Calculate possible occluder position in sphere around current pixel
						occluderPos = float3(coord, depth) + // Origin = current pixel
									  float3(vRotatedOffset.xy, vRotatedOffset.z * (depth + depth)); // Offset
	
						// Fetch depth of occluder position and "traced" depth to the geometry (from depth map)
						occluderPositionDepth = occluderPos.z;
						
						occluderSurfaceDepth = abs(tex2D(smpDepth, occluderPos.xy).r);

						// Evaluate occlusion
						rangeIsInvalid = saturate(((depth - occluderSurfaceDepth) / occluderSurfaceDepth));
						Accessibility += lerp(occluderSurfaceDepth > occluderPositionDepth, ssaoRatioNearDistantOccluders_flt, rangeIsInvalid);
					}
				}
			}
			
		}

		Accessibility *= SAMPLES_x8_INV;

		// ANALYSIS

			// Calculate raw ambient occlusion
			ao = (Accessibility * Accessibility + Accessibility);

		
		#ifndef SSAO_NO_CONTRASTING
		
			#ifndef SSAO_STATIC_CONTRASTING
				ao = saturate((ao - 0.5f) * ssaoConvexHighlight_flt + 0.5f);
				ao = pow(ao, ssaoConcaveDarkness_flt);
			#else
				ao = saturate((ao - 0.5f) * SSAO_CONVEX_HIGHLIGHT + 0.5f);
				ao = pow(ao, SSAO_CONCAVE_DARKNESS);
			#endif

		#endif


		#ifndef SSAO_NO_SOFTALPHA
			ao = lerp(ao, 1.0, alpha); // low res soft alpha
		#endif

		#ifndef SSAO_NO_FOG
			ao = lerp(ao, 1.0, max(0, fog));
		#endif
	}

	Out.aoX_depthY = float4(ao, depth, 0, 0);
	Out.normalXYZ_processedW = float4(normal, step(1, ao));

	return(Out);
}

// ENTRY POINT

	technique t
	{
		pass p
		{
			VertexShader = null;
			PixelShader  = compile ps_3_0 PS();
		}
	}