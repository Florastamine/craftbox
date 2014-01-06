//----------------------------------------------------------------------------------------
// Unified SSAO object surface shader; part of SSAO v0.6 for Gamestudio A7 & A8
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

// OBJ_ALPHA indicates that we need alpha-values from the texture. This involves texture
// sampling in the pixel shader and texture transform in the vertex shader.

	#ifdef OBJ_SOFTALPHA
		#define OBJ_ALPHA
	#else
		#ifdef OBJ_BINARY
			#define OBJ_ALPHA
		#endif
	#endif
	
	#ifndef OBJ_ALPHA
		bool PASS_SOLID;
	#endif
	
	// use a full target for PS, if full depth and -normals are activated in general or if
	// we are in depth view and full depth is activated or we are in normals+alpha view
	// and full normals are activated
	
	#ifdef SSAO_FULL_MAPS
		#define PS_FULL_TARGET
	#else
		#ifdef SSAO_SRC_DEPTH
			#ifdef SSAO_FULL_DEPTH
				#define PS_FULL_TARGET
			#endif
		#else
			#ifdef SSAO_SRC_NRMALPHA
				#ifdef SSAO_FULL_NORMALS
					#define PS_FULL_TARGET
				#endif
			#endif
		#endif
	#endif

#ifndef OBJ_SKY

	#include <transform>
	#include <texture>
	#include <normal>
	#include <pos>

	#ifdef A8
		#ifdef SSAO_GPU_BONES
			#include <bones>
		#endif
	#endif

#else

	float4x4 matWorldViewProj;
	
	// if SKIP_T has been accidently defined, we enforce it
	#undef SKIP_T
	
#endif

float4 vecSkill1; // x: near clip, y: far clip, z: difference, w: 0=depthx2

// VERTEXSHADER

	struct VS_IN
	{
		float4 Pos : POSITION;
		float4 Tex : TEXCOORD0;

		#ifdef SSAO_SRC_NRMALPHA
			float3 Normal : NORMAL;
		#endif
	};

	struct VS_OUT
	{
		float4 Pos : POSITION;
		float4 Tex : TEXCOORD0;
		
		#ifdef SSAO_SRC_NRMALPHA
			float3 Normal : TEXCOORD1;
		#endif
	};

	// Default
	#ifndef SKIP_T
	
		VS_OUT VS (VS_IN In)
		{
			VS_OUT Out = (VS_OUT)0;
	
			// Transform world position into screen position
			Out.Pos = mul(In.Pos, matWorldViewProj);
			
			#ifndef OBJ_SKY

				// get correct texture coordinates (e.g. animated textures)
				#ifdef OBJ_ALPHA
					Out.Tex.xy = DoTexture(In.Tex.xy);
				#endif
				
				// Z coordinate of screen space position is equivalent to the radial 
				// distance from camera to pixel which is the depth. We abuse the outgoing
				// texture coordinate by saving the pixel depth in the z-component
				Out.Tex.z = Out.Pos.z;
	
				// pass normal
				#ifdef SSAO_SRC_NRMALPHA
					Out.Normal = DoNormal(In.Normal);
				#endif
	
			#endif
	
			return(Out);
		}
		
	#endif
	
	// GPU-bones
	#ifndef OBJ_SKY
	#ifdef A8
	#ifdef SSAO_GPU_BONES
	#ifndef SKIP_BONES
	
		VS_OUT VS_Bones
		(
			in float4 Pos           : POSITION,
			in float4 Tex           : TEXCOORD0,
			in float3 Normal        : NORMAL,
			in int4   inBoneIndices : BLENDINDICES,
			in float4 inBoneWeights : BLENDWEIGHT
		)
		{
			VS_OUT Out = (VS_OUT)0;
	
			// get correct texture coordinates (e.g. animated textures)
			#ifdef OBJ_ALPHA
				Out.Tex.xy = DoTexture(Tex.xy);
			#endif
	
			// gpu-bones transformed position
			Out.Pos = DoTransform(DoBones(Pos, inBoneIndices, inBoneWeights));
	
			// Z coordinate of screen space position is equivalent to the radial
			// distance from camera to pixel which is the depth. We abuse the outgoing
			// texture coordinate by saving the pixel depth in the z-component
			Out.Tex.z = Out.Pos.z;
	
			// gpu-bones transformed normal
			#ifdef SSAO_SRC_NRMALPHA
				Out.Normal = DoNormal(DoBones(Normal, inBoneIndices, inBoneWeights));
			#endif
	
			return(Out);
		}
	
	#endif
	#endif
	#endif
	#endif
	
// PIXELSHADER

	// ENTITY SKIN, needed for alpha
	#ifdef OBJ_ALPHA
		
		texture entSkin1;
		sampler2D skin = sampler_state
		{
			texture = <entSkin1>;
		};

	#endif

	struct PS_OUT
	{
		// target 0 is always used for clipped depth and clipped normals + alpha
		float4 clipped : COLOR0;

		// target 1 is reserved for full depth and -normals, if enabled
		#ifdef PS_FULL_TARGET
			float4 full : COLOR1;
		#endif

		// additional target is used in normal+alpha view, if softalpha is sampled. In
		// that case, it is either target 1 or 2, depending on if full maps are being
		// aquired or not

		#ifdef SSAO_SRC_NRMALPHA
			#ifndef SSAO_NO_SOFTALPHA
				#ifdef PS_FULL_TARGET
					float4 softalpha : COLOR2;
				#else
					float4 softalpha : COLOR1;
				#endif
			#endif
		#endif
	};

	PS_OUT PS (VS_OUT In) : COLOR
	{
		PS_OUT Out = (PS_OUT)0;
		
		#ifdef OBJ_SKY
		
			#ifdef SSAO_SRC_DEPTH
			
				Out.clipped = float4(99999, 0, 0, 1);
				
				#ifdef PS_FULL_TARGET
					Out.full = float4(99999, 0, 0, 1);
				#endif
				
			#endif
			
		#else
		
			float a = 1.0; // solid by default
			
			#ifdef OBJ_ALPHA
				a = tex2D(skin, In.Tex.xy).a;
				
				#ifdef OBJ_BINARY // binary alpha test
					clip(a - 0.5);
				#endif				
				
			#endif
			
			// src output
			{
				// depth
				#ifdef SSAO_SRC_DEPTH
					#ifndef OBJ_SOFTALPHA
						Out.clipped = float4(In.Tex.z, In.Tex.z, In.Tex.z, a);
					#endif

					#ifdef PS_FULL_TARGET
						Out.full = float4(In.Tex.z, In.Tex.z, In.Tex.z, a);
					#endif
				#endif

				// XOR

				// normals and alpha
				#ifdef SSAO_SRC_NRMALPHA
					#ifndef OBJ_SOFTALPHA
						Out.clipped = float4((In.Normal + 1) / 2, a);
					#endif

					#ifdef PS_FULL_TARGET
						Out.full = float4((In.Normal + 1) / 2, a);
					#endif

					#ifdef OBJ_SOFTALPHA
						Out.softalpha = float4(1, 1, 1, a); // softalpha
					#else
						#ifndef SSAO_NO_SOFTALPHA
							Out.softalpha.a = 1; // solid or binary
						#endif
					#endif
				#endif
			}
			
		#endif
		
		return(Out);
	}
	
// ENTRY POINT

	#ifndef SKIP_T
	technique t
	{
		pass p
		{
			#ifdef OBJ_SOFTALPHA
				ZWriteEnable = false;
				AlphaBlendEnable = true;
				SrcBlend = SrcAlpha;
				DestBlend = InvSrcAlpha;
			#else
				AlphaBlendEnable = false;
				ZWriteEnable = true;
				CullMode = CCW;
			#endif

			VertexShader = compile vs_2_0 VS();
			PixelShader  = compile ps_2_0 PS();
		}
	}
	#endif

	#ifndef OBJ_SKY
	#ifdef A8
	#ifdef SSAO_GPU_BONES
	#ifndef SKIP_BONES
	technique bones
	{
		pass p
		{
			#ifdef OBJ_SOFTALPHA
				ZWriteEnable = false;
				AlphaBlendEnable = true;
				SrcBlend = SrcAlpha;
				DestBlend = InvSrcAlpha;
			#else
				AlphaBlendEnable = false;
				ZWriteEnable = true;
				CullMode = CCW;
			#endif

			VertexShader = compile vs_2_0 VS_Bones();
			PixelShader  = compile ps_2_0 PS();
		}
	}
	#endif
	#endif
	#endif
	#endif