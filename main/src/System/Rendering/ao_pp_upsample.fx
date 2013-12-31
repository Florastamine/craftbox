//-----------------------------------------------------------------------------
// Encoded bilateral upsampling; part of SSAO v0.6 for Gamestudio A7 & A8
// Copyright 2010, 2011 Christian Behrenberg
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

// VARIABLES

	float4 vecViewPort; // Screen dimensions
	float4 vecSkill1; // x: near clipping, y: far clipping

// INPUT DATA

	// Coarse image and depth
	texture mtlSkin1;
	sampler2D smpCoarseImageX_depthY = sampler_state {
		Texture = <mtlSkin1>;
		AddressU	= clamp;
		AddressV	= clamp;
	};

	// Coarse normals and processing flag
	texture mtlSkin2;
	sampler2D smpCoarseNormalsXYZ_processedW = sampler_state {
		Texture = <mtlSkin2>;
		AddressU	= clamp;
		AddressV	= clamp;
	};

	// HiRes depth
	texture bmapSsaoDepthHires_bmap;
	sampler2D smpHiResDepth = sampler_state {
		Texture = <bmapSsaoDepthHires_bmap>;
		AddressU	= clamp;
		AddressV	= clamp;
		MipFilter = Point;
		MagFilter = Point;
	};

	texture bmapSsaoNormalHires_bmap;
	sampler2D smpNormal = sampler_state {
		Texture = <bmapSsaoNormalHires_bmap>;
		AddressU	= clamp;
		AddressV	= clamp;
		MipFilter = Point;
		MagFilter = Point;
	};

// BILINEAR WEIGHTS
// For each hires texel corner

	static const float4 bilinearWeights [4] =
	{
		float4(0.5625, 0.1875, 0.1875, 0.0625),
		float4(0.1875, 0.5625, 0.0625, 0.1875),
		float4(0.1875, 0.0625, 0.5625, 0.1875),
		float4(0.0625, 0.1875, 0.1875, 0.5625)
	};
	
// PIXELSHADER

	float2 coordForHiResSampling (float2 lowResCoord, int texelCorner, float2 hiResPixelSize)
	{
		float2 offset = float2(sign(texelCorner % 2 - 0.5), sign(texelCorner / 2 - 0.5));
		return(lowResCoord + offset * hiResPixelSize);
	}
	
	float2 coordForNeighbourSampling (float2 lowResCoord, int texelCorner, float2 lowResPixelSize)
	{
		float2 offset = float2(texelCorner % 2, texelCorner / 2);
		return(lowResCoord + offset * lowResPixelSize);
	}
	
	float4 PS_Clear () : COLOR0
	{
		return(float4(1,1,1,1));
	}		

	float4 PS_Upscale (float2 tex : TEXCOORD0) : COLOR0
	{
		float2 lowResCoord = tex + vecViewPort.zw;

 		float4x3 hiResNormals;
		float4 hiResDepth;
		float4x3 lowResNormals;
		float4x2 lowResAoDepth;

		for (int texel = 0; texel < 4; texel++)
		{
			float2 hiResCoord     = coordForHiResSampling(lowResCoord, texel, vecViewPort.zw / 2);
			float2 neighbourCoord = coordForNeighbourSampling(tex, texel, vecViewPort.zw * 2);

			lowResNormals[texel] = tex2D(smpCoarseNormalsXYZ_processedW, neighbourCoord).xyz;
			hiResNormals[texel] = tex2D(smpNormal, hiResCoord).xyz;

			hiResDepth[texel] = tex2D(smpHiResDepth, hiResCoord).r;
			
			#ifndef SSAO_NO_SKY
				clip(vecSkill1.y - hiResDepth[texel]);
			#endif
			
			lowResAoDepth[texel] = tex2D(smpCoarseImageX_depthY, neighbourCoord).xy;
		}
		
		hiResNormals = 2 * hiResNormals - 1;
		lowResNormals = 2 * lowResNormals - 1;

		// Calculate weights

			float4 weightSum = 0;
			float4 pixelSum = 0;

			for (int hiResPixel = 0; hiResPixel < 4; hiResPixel++) // HiRes data
			{
				for (int lowResPixel = 0; lowResPixel < 4; lowResPixel++) // LowRes data
				{
					// Compute normal and depth weights

						// Normal weight
						float angleFac = dot(lowResNormals[lowResPixel], hiResNormals[hiResPixel].xyz);
						float normalWeight = pow(angleFac, SSAO_UPSAMPLE_NORMAL_POW);

						// Depth weight
						float depthWeight = saturate(SSAO_UPSAMPLE_DEPTH_T / distance(hiResDepth[hiResPixel], lowResAoDepth[lowResPixel].y));

					// Compute total sample weight
					float pixelWeight = normalWeight * depthWeight * bilinearWeights[hiResPixel][lowResPixel];

					// Accumulate weight- and sample sum
					weightSum[hiResPixel] += pixelWeight;
					pixelSum[hiResPixel] += lowResAoDepth[lowResPixel].x * pixelWeight;
				}

				pixelSum[hiResPixel] /= weightSum[hiResPixel];
				
				pixelSum[hiResPixel] += step(10000, hiResDepth[hiResPixel]);
			}

			return(pixelSum);
	}
	


// ENTRY POINT

	technique t
	{
		// if no sky is visible, we don't need to clear the encoded image
		#ifndef SSAO_NO_SKY
			pass clear
			{
				VertexShader = null;
				PixelShader  = compile ps_2_0 PS_Clear();
			}
		#endif
		
		pass upscale
		{
			VertexShader = null;
			PixelShader  = compile ps_3_0 PS_Upscale();
		}		
	}