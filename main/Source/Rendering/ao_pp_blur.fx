//----------------------------------------------------------------------------------------
// Thresholded Blur Shader; part of SSAO v0.6 for Gamestudio A7 & A8
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

// This shader tries to remove SSAO noise by box blurring ao terms of nearby and similar
// aligned surface pixels. This uses a large blur radius; tapping- and parabola parameters
// are handcrafted, so that it looks ok. Uses SSAO_BLUR_SAMPLES (odd) for number of taken
// samples and STEP_X & STEP_Y as step direction (this is an 1D shader, used twice for
// full 2D convolution). See manual for references and related works.

// variables
float4 vecViewPort; // screen dimensions

float4 vecSkill1; // x: near clipping, y: far clipping

// ao + depth
texture mtlSkin1;
sampler2D smpImage = sampler_state { // ao (+ depth)
	Texture = <mtlSkin1>;
	AddressU = clamp;
	AddressV = clamp;
};

// normals
#ifndef SSAO_NO_BLUR_NORMAL_T
texture mtlSkin2;
sampler2D smpNormal = sampler_state {
	Texture = <mtlSkin2>;
	AddressU	= clamp;
	AddressV	= clamp;
};
#endif

// PIXELSHADER
// 

float4 PS (float2 coord : TEXCOORD0) : COLOR
{
	#ifndef SSAO_NO_BLUR_DEPTH_T
		
		float2 imageX_depthY = tex2D(smpImage, coord).xy;
		
		#ifndef SSAO_NO_SKY
			clip(vecSkill1.y - imageX_depthY.y);
		#endif
	
	#else
		float image = tex2D(smpImage, coord).x;
	#endif
	
	#ifndef SSAO_NO_BLUR_NORMAL_T
		float4 normal = tex2D(smpNormal, coord);
		normal.xyz = normal.xyz * 2.0 - 1.0;
	#endif

	float weightSum = 1.0;
	
	#ifndef SSAO_NO_BLUR_DEPTH_T

		// dynamic parabola depth threshold
		#define DEPTH_TRHESHOLD_C 2.5f
		#define DEPTH_TRHESHOLD_LINEAR 0.004f
		#define DEPTH_TRHESHOLD_CUBIC 0.0001f

		float depthThreshold = DEPTH_TRHESHOLD_C + 
		                       DEPTH_TRHESHOLD_LINEAR * imageX_depthY.y + 
							   DEPTH_TRHESHOLD_CUBIC * imageX_depthY.y * imageX_depthY.y;
	#endif

	// tap offset
	float2 tapOffset = float2(STEP_X, STEP_Y) * vecViewPort.zw * 2;

	int offset = SSAO_BLUR_SAMPLES - 1;

	// sampling
	for (int i = 0; i < SSAO_BLUR_SAMPLES; i++)
	{
		// generate coord (x,y) and fetch image value (z) and depth(w)
		float2 sampleCoord = coord + (float)(i - offset / 2) * tapOffset;

		#ifndef SSAO_NO_BLUR_DEPTH_T
			float2 sampleImageX_depthY = tex2D(smpImage, sampleCoord).xy;
		#else
			float sampleImage = tex2D(smpImage, sampleCoord).x;
		#endif

		#ifndef SSAO_NO_BLUR_DEPTH_T
			if (abs(imageX_depthY.y - sampleImageX_depthY.y) < depthThreshold)
			{
		#endif
			#ifndef SSAO_NO_BLUR_NORMAL_T

				float3 sampleNormal = tex2D(smpNormal, sampleCoord).xyz * 2 - 1;

				// use surface normal similarity to weight the gaussian weight
				float normalWeight = saturate(dot(normal.xyz, sampleNormal.xyz));

				weightSum += normalWeight;
				
				#ifndef SSAO_NO_BLUR_DEPTH_T
					imageX_depthY.x += sampleImageX_depthY.x * normalWeight;
				#else
					image += sampleImage * normalWeight;
				#endif
			#else
				weightSum += 1;
				#ifndef SSAO_NO_BLUR_DEPTH_T
					imageX_depthY.x += sampleImageX_depthY.xy;
				#else
					image += sampleImage;
				#endif
			#endif
		#ifndef SSAO_NO_BLUR_DEPTH_T
			}
		#endif
	}

	// normalize
	#ifndef SSAO_NO_BLUR_DEPTH_T
		imageX_depthY.x /= weightSum;
		return(float4(imageX_depthY, 0, 0));
	#else
		image /= weightSum;
		return(float4(image, 0, 0, 0));
	#endif
}

// entry point
technique t
{
	pass p
	{
		VertexShader = null;
		
		#ifdef SSAO_NO_BLUR_T
			PixelShader = compile ps_2_0 PS();
		#else
			PixelShader = compile ps_3_0 PS();
		#endif
	}
}