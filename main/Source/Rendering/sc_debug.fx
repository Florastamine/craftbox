#ifndef _QUAD_FXH
#define _QUAD_FXH

// Numeric types we are likely to encounter....
//	Redefine these before including "Quad.fxh" if you want
//		to use a type other than "half" for these data or just
//		define the symbol QUAD_FLOAT to use "floats"
#ifndef QUAD_REAL
#ifdef QUAD_FLOAT
#define QUAD_REAL float
#define QUAD_REAL2 float2
#define QUAD_REAL3 float3
#define QUAD_REAL4 float4
#define QUAD_REAL3x3 float3x3
#define QUAD_REAL4x3 float4x3
#define QUAD_REAL3x4 float3x4
#define QUAD_REAL4x4 float4x4
#else /* ! QUAD_FLOAT */
#define QUAD_REAL half
#define QUAD_REAL2 half2
#define QUAD_REAL3 half3
#define QUAD_REAL4 half4
#define QUAD_REAL3x3 half3x3
#define QUAD_REAL4x3 half4x3
#define QUAD_REAL3x4 half3x4
#define QUAD_REAL4x4 half4x4
#endif /* ! QUAD_FLOAT */
#endif /* ! QUAD_REAL */

#ifndef NVIDIA_GREEN
#define NVIDIA_GREEN (QUAD_REAL3(0.4627,.7255,0))
#endif /* NVIDIA_GREEN */

///////////////////////////////////////////////////////////////////////
/// Texture-Declaration Macros ////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

//
// Modal 2D File Textures
//
// example usage: FILE_TEXTURE_2D_MODAL(GlowMap,GlowSampler,"myfile.dds",CLAMP)
//
#define FILE_TEXTURE_2D_MODAL(TexName,SampName,Filename,AddrMode) texture TexName < \
	string ResourceName = (Filename); \
    string ResourceType = "2D"; \
>; \
sampler SampName = sampler_state { \
    texture = <TexName>; \
    AddressU  = AddrMode; \
    AddressV = AddrMode; \
    MipFilter = LINEAR; \
    MinFilter = LINEAR; \
    MagFilter = LINEAR; \
};

//
// Simple 2D File Textures
//
// example usage: FILE_TEXTURE_2D(GlowMap,GlowSampler,"myfile.dds")
//
#define FILE_TEXTURE_2D(TextureName,SamplerName,Diskfile) FILE_TEXTURE_2D_MODAL(TextureName,SamplerName,(Diskfile),WRAP)

//
// Use this variation of DECLARE_QUAD_TEX() if you want a *scaled* render target
//
// example usage: DECLARE_SIZED_QUAD_TEX(GlowMap,GlowSampler,"A8R8G8B8",1.0)
#define DECLARE_SIZED_QUAD_TEX(TexName,SampName,PixFmt,Multiple) texture TexName : RENDERCOLORTARGET < \
    float2 ViewPortRatio = {Multiple,Multiple}; \
    int MipLevels = 1; \
    string Format = PixFmt ; \
	string UIWidget = "None"; \
>; \
sampler SampName = sampler_state { \
    texture = <TexName>; \
    AddressU  = CLAMP; \
    AddressV = CLAMP; \
    MipFilter = POINT; \
    MinFilter = LINEAR; \
    MagFilter = LINEAR; \
};

//
// Use this macro to easily declare typical color render targets
//
// example usage: DECLARE_QUAD_TEX(ObjMap,ObjSampler,"A8R8G8B8")
#define DECLARE_QUAD_TEX(TextureName,SamplerName,PixelFormat) DECLARE_SIZED_QUAD_TEX(TextureName,SamplerName,(PixelFormat),1.0)

//
// Use this macro to easily declare variable-sized depth render targets
//
// example usage: DECLARE_SIZED_QUAD_DEPTH_BUFFER(DepthMap,"D24S8",0.5)
#define DECLARE_SIZED_QUAD_DEPTH_BUFFER(TextureName,PixelFormat,Multiple) texture TextureName : RENDERDEPTHSTENCILTARGET < \
    float2 ViewPortRatio = {Multiple,Multiple}; \
    string Format = (PixelFormat); \
	string UIWidget = "None"; \
>; 

//
// Use this macro to easily declare typical depth render targets
//
// example usage: DECLARE_QUAD_DEPTH_BUFFER(DepthMap,"D24S8")
#define DECLARE_QUAD_DEPTH_BUFFER(TexName,PixFmt) DECLARE_SIZED_QUAD_DEPTH_BUFFER(TexName,PixFmt,1.0)

//
// declare exact-sized arbitrary texture
//
// example usage: DECLARE_SIZED_TEX(BlahMap,BlahSampler,"R32F",128,1)
#define DECLARE_SIZED_TEX(Tex,Samp,Fmt,Wd,Ht) texture Tex : RENDERCOLORTARGET < \
	float2 Dimensions = { Wd, Ht }; \
    string Format = Fmt ; \
	string UIWidget = "None"; \
	int miplevels=1;\
>; \
sampler Samp = sampler_state { \
    texture = <Tex>; \
    AddressU  = CLAMP; \
    AddressV = CLAMP; \
    MipFilter = NONE; \
    MinFilter = LINEAR; \
    MagFilter = LINEAR; \
};

//
// declare exact-sized square texture, as for shadow maps
//
// example usage: DECLARE_SQUARE_QUAD_TEX(ShadMap,ShadObjSampler,"A16R16G16B16F",512)
#define DECLARE_SQUARE_QUAD_TEX(TexName,SampName,PixFmt,Size) DECLARE_SIZED_TEX(TexName,SampName,(PixFmt),Size,Size)

//
// likewise for shadow depth targets
//
// example usage: DECLARE_SQUARE_QUAD_DEPTH_BUFFER(ShadDepth,"D24S8",512)
#define DECLARE_SQUARE_QUAD_DEPTH_BUFFER(TextureName,PixelFormat,Size) texture TextureName : RENDERDEPTHSTENCILTARGET < \
	float2 Dimensions = { Size, Size }; \
    string Format = (PixelFormat) ; \
	string UIWidget = "None"; \
>; 

#ifndef _STRIPE_TEX_FXH_
#define _STRIPE_TEX_FXH_

// caller-override-able

#ifndef STRIPE_TEX_SIZE
#define STRIPE_TEX_SIZE 128
#endif /* STRIPE_TEX_SIZE */

#define DEFAULT_BALANCE (0.5)

/************************************************************/
/*** TWEAKABLES *********************************************/
/************************************************************/

#define DECLARE_BALANCE float Balance < \
    string UIWidget = "slider"; \
    float uimin = 0.01; \
    float uimax = 0.99; \
    float uistep = 0.01; \
    string UIName = "Balance"; \
> = DEFAULT_BALANCE;

/////////////// prodecural texture /////////////

/*********** texture shader ******/

float4 make_stripe_tex(float2 Pos : POSITION,float ps : PSIZE) : COLOR
{
   float v = 0;
   float nx = Pos.x+ps; // keep the last column full-on, always
   v = nx > Pos.y;
   return float4(v.xxxx);
}

// texture declaration

texture _StripeTexture <
    string function = "make_stripe_tex";
    string UIWidget = "None";
    float2 Dimensions = { STRIPE_TEX_SIZE, STRIPE_TEX_SIZE };
>;

sampler2D _StripeSampler = sampler_state
{
    Texture = <_StripeTexture>;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = LINEAR;
    AddressU = WRAP;
    AddressV = CLAMP;
};

////////////////////////////////////////////
// Utility Functions ///////////////////////
////////////////////////////////////////////

// base function: "Balance" is in W term
float stripe(float4 XYZW) { return tex2D(_StripeSampler,XYZW.xw).x; }

float stripe(float4 XYZW,float Balance) {
    return stripe(float4(XYZW.xyz,Balance)); }

float stripe(float3 XYZ,float Balance) {
    return stripe(float4(XYZ.xyz,Balance)); }

float stripe(float2 XY,float Balance) {
    return stripe(float4(XY.xyy,Balance)); }

float stripe(float X,float Balance) {
    return stripe(float4(X.xxx,Balance)); }

// use default balance (can't do float4 version, would interfere): //

float stripe(float3 XYZ) {
    return stripe(float4(XYZ.xyz,DEFAULT_BALANCE)); }

float stripe(float2 XY) {
    return stripe(float4(XY.xyy,DEFAULT_BALANCE)); }

float stripe(float X) {
    return stripe(float4(X.xxx,DEFAULT_BALANCE)); }

///////////////////////////////////
// 2D checker ///////////
///////////////////////////////////

float checker2D(float4 XYZW)
{
    float stripex = tex2D(_StripeSampler,XYZW.xw).x;
    float stripey = tex2D(_StripeSampler,XYZW.yw).x;
    return abs(stripex - stripey);
}

// overloads of the above

float checker2D(float4 XYZW,float Balance) {
    return checker2D(float4(XYZW.xyz,Balance)); }

float checker2D(float3 XYZ,float Balance) {
    return checker2D(float4(XYZ.xyz,Balance)); }

float checker2D(float2 XY,float Balance) {
    return checker2D(float4(XY.xyy,Balance)); }

// use default balance ////////////////////////

float checker2D(float3 XYZ) {
    return checker2D(float4(XYZ.xyz,DEFAULT_BALANCE)); }

float checker2D(float2 XY) {
    return checker2D(float4(XY.xyy,DEFAULT_BALANCE)); }

float checker2D(float X) {
    return checker2D(float4(X.xxx,DEFAULT_BALANCE)); }

///////////////////////////////////
// 3D checker /////////////////////
///////////////////////////////////

float checker3D(float4 XYZW)
{
    float stripex = tex2D(_StripeSampler,XYZW.xw).x;
    float stripey = tex2D(_StripeSampler,XYZW.yw).x;
    float stripez = tex2D(_StripeSampler,XYZW.zw).x;
    float check = abs(abs(stripex - stripey) - stripez);
    return check;
}

// overloads of the above

float checker3D(float3 XYZ,float Balance) {
    return checker3D(float4(XYZ.xyz,Balance)); }

float checker3D(float4 XYZW,float Balance) {
    return checker3D(float4(XYZW.xyz,Balance)); }

// use default balance ////////////////////////

float checker3D(float3 XYZ) {
    return checker3D(float4(XYZ.xyz,DEFAULT_BALANCE)); }

float checker3D(float2 XY) {
    return checker3D(float4(XY.xyy,DEFAULT_BALANCE)); }

float checker3D(float X) {
    return checker3D(float4(X.xxx,DEFAULT_BALANCE)); }

/////////////

float3 checker3Drgb(float4 XYZW)
{
	float3 result;
    result.x = tex2D(_StripeSampler,XYZW.xw).x;
    result.y = tex2D(_StripeSampler,XYZW.yw).x;
    result.z = tex2D(_StripeSampler,XYZW.zw).x;
    return result;
}

float3 checker3Drgb(float3 XYZ,float Balance)
{
    return checker3Drgb(float4(XYZ.xyz,Balance)); }

float3 checker3Drgb(float3 XYZ)
{
    return checker3Drgb(float4(XYZ.xyz,DEFAULT_BALANCE)); }

#endif /* _STRIPE_TEX_FXH_ */

/***************************** eof ***/



////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////// Utility Functions ////////
////////////////////////////////////////////////////////////////////////////

//
// Scale inputs for use with texture-based lookup tables. A value ranging from zero to one needs
//   a slight scaling and offset to be sure to point at the centers of the first and last pixels
//	 of that lookup texture. Pass the integer size of the table in TableSize
// For now we'll assume that all tables are 1D, square, or cube-shaped -- all axes of equal size
//
// Cost of this operation for pixel shaders: two const-register
//   entries and a MAD (one cycle)
QUAD_REAL scale_lookup(QUAD_REAL Value,const QUAD_REAL TableSize)
{
	QUAD_REAL scale = ((TableSize - 1.0)/TableSize);
	QUAD_REAL shift = (0.5 / TableSize);
	return (scale*Value + shift);
}

QUAD_REAL2 scale_lookup(QUAD_REAL2 Value,const QUAD_REAL TableSize)
{
	QUAD_REAL scale = ((TableSize - 1.0)/TableSize);
	QUAD_REAL shift = (0.5 / TableSize);
	return (scale.xx*Value + shift.xx);
}

QUAD_REAL3 scale_lookup(QUAD_REAL3 Value,const QUAD_REAL TableSize)
{
	QUAD_REAL scale = ((TableSize - 1.0)/TableSize);
	QUAD_REAL shift = (0.5 / TableSize);
	return (scale.xxx*Value + shift.xxx);
}

// pre-multiply and un-pre-mutliply functions. The precision
//		of thse operatoions is often limited to 8-bit so don't
//		always count on them!
// The macro value of NV_ALPHA_EPSILON, if defined, is used to
//		avoid IEEE "NaN" values that may occur when erroneously
//		dividing by a zero alpha (thanks to Pete Warden @ Apple
//		Computer for the suggestion in GPU GEMS II)

// multiply color by alpha to turn an un-premultipied
//	pixel value into a premultiplied one
QUAD_REAL4 premultiply(QUAD_REAL4 C)
{
	return QUAD_REAL4((C.w*C.xyz),C.w);
}

#define NV_ALPHA_EPSILON 0.0001

// given a premultiplied pixel color, try to undo the premultiplication.
// beware of precision errors
QUAD_REAL4 unpremultiply(QUAD_REAL4 C)
{
#ifdef NV_ALPHA_EPSILON
	QUAD_REAL a = C.w + NV_ALPHA_EPSILON;
	return QUAD_REAL4((C.xyz / a),C.w);
#else /* ! NV_ALPHA_EPSILON */
	return QUAD_REAL4((C.xyz / C.w),C.w);
#endif /* ! NV_ALPHA_EPSILON */
}

/////////////////////////////////////////////////////////////////////////////////////
// Structure Declaration ////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

struct QuadVertexOutput {
   	QUAD_REAL4 Position	: POSITION;
    QUAD_REAL2 UV		: TEXCOORD0;
};

/////////////////////////////////////////////////////////////////////////////////////
// Hidden tweakables declared by this .fxh file /////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

QUAD_REAL2 QuadScreenSize : VIEWPORTPIXELSIZE < string UIWidget="None"; >;

#ifndef NO_TEXEL_OFFSET

#ifdef TWEAKABLE_TEXEL_OFFSET
		QUAD_REAL QuadTexOffset = 0.5;
#else /* !TWEAKABLE_TEXEL_OFFSET */
		QUAD_REAL QuadTexOffset < string UIWidget="None"; > = 0.5;
#endif /* !TWEAKABLE_TEXEL_OFFSET */

static QUAD_REAL2 QuadTexelOffsets =
				QUAD_REAL2(QuadTexOffset/(QuadScreenSize.x),QuadTexOffset/(QuadScreenSize.y));

#endif /* NO_TEXEL_OFFSET */

////////////////////////////////////////////////////////////
////////////////////////////////// vertex shaders //////////
////////////////////////////////////////////////////////////

QuadVertexOutput ScreenQuadVS(
		QUAD_REAL3 Position : POSITION, 
		QUAD_REAL3 TexCoord : TEXCOORD0
) {
    QuadVertexOutput OUT;
    OUT.Position = QUAD_REAL4(Position, 1);
#ifdef NO_TEXEL_OFFSET
    OUT.UV = TexCoord.xy;
#else /* NO_TEXEL_OFFSET */
    OUT.UV = QUAD_REAL2(TexCoord.xy+QuadTexelOffsets); 
#endif /* NO_TEXEL_OFFSET */
    return OUT;
}

//////////////////////////////////////////////////////
////////////////////////////////// pixel shaders /////
//////////////////////////////////////////////////////

// add glow on top of model

QUAD_REAL4 TexQuadPS(QuadVertexOutput IN,uniform sampler2D InputSampler) : COLOR
{   
	QUAD_REAL4 texCol = tex2D(InputSampler, IN.UV);
	return texCol;
}  

QUAD_REAL4 TexQuadBiasPS(QuadVertexOutput IN,uniform sampler2D InputSampler,QUAD_REAL TBias) : COLOR
{   
	QUAD_REAL4 texCol = tex2Dbias(InputSampler, QUAD_REAL4(IN.UV,0,TBias));
	return texCol;
}  

//////////////////////////////////////////////////////////////////
/// Macros to define passes within Techniques ////////////////////
//////////////////////////////////////////////////////////////////

// older HLSL syntax
#define TEX_TECH(TechName,SamplerName) technique TechName { \
    pass TexturePass  { \
		VertexShader = compile vs_2_0 ScreenQuadVS(); \
		AlphaBlendEnable = false; ZEnable = false; \
		PixelShader  = compile ps_2_a TexQuadPS(SamplerName); } }

#define TEX_BLEND_TECH(TechName,SamplerName) technique TechName { \
    pass TexturePass { \
		VertexShader = compile vs_2_0 ScreenQuadVS(); \
		ZEnable = false; AlphaBlendEnable = true; \
		SrcBlend = SrcAlpha; DestBlend = InvSrcAlpha; \
		PixelShader  = compile ps_2_a TexQuadPS(SamplerName); } }

// newer HLSL syntax

#define TEX_TECH2(TechName,SamplerName,TargName) technique TechName { \
    pass TexturePass  < \
		string ScriptFunction = "RenderColorTarget0=" (TargName) ";" \
    							"DrawInternal=Buffer;"; \
	> { \
		VertexShader = compile vs_2_0 ScreenQuadVS(); \
		AlphaBlendEnable = false; ZEnable = false; \
		PixelShader  = compile ps_2_a TexQuadPS(SamplerName); } }

#define TEX_BLEND_TECH2(TechName,SamplerName) technique TechName { \
    pass TexturePass < \
		string ScriptFunction = "RenderColorTarget0=" (TargName) ";" \
    							"DrawInternal=Buffer;"; \
	> { \
		VertexShader = compile vs_2_0 ScreenQuadVS(); \
		ZEnable = false; AlphaBlendEnable = true; \
		SrcBlend = SrcAlpha; DestBlend = InvSrcAlpha; \
		PixelShader  = compile ps_2_a TexQuadPS(SamplerName); } }

#endif /* _QUAD_FXH */

////////////// eof ///



/******************************************************************************/

#ifndef _DEBUG_TOOLS_FXH_
#define _DEBUG_TOOLS_FXH_

// data types, screen-spaced values
#include <Quad.fxh>
// stripe texture, functions, checkers
#include <stripe_tex.fxh>

//
//////// instead of typical spherical normalization, project against the boundaries of a cube
//

QUAD_REAL3 cube_normalize(QUAD_REAL3 V)
{
    QUAD_REAL3 Na = abs(V);
    QUAD_REAL r = max(max(Na.x,Na.y),Na.z);
    return (V/r);
}

QUAD_REAL3 cube_normalize(QUAD_REAL4 V) { return cube_normalize(V.xyz); }

/////////// vectors into colors /////////////

// normalized vector (saturated, at least) as a color
QUAD_REAL3 as_rgb(QUAD_REAL3 V) { return (QUAD_REAL3(0.5,0.5,0.5) + 0.5*V); }
QUAD_REAL3 as_rgb(QUAD_REAL4 V) { return as_rgb(V.xyz); }

// un-normalized vector (spherical normalize)
QUAD_REAL3 as_rgb_n(QUAD_REAL3 V) { return (QUAD_REAL3(0.5,0.5,0.5) + 0.5*normalize(V)); }
QUAD_REAL3 as_rgb_n(QUAD_REAL4 V) { return (QUAD_REAL3(0.5,0.5,0.5) + 0.5*normalize(V.xyz)); }

// un-normalized vector (cube normalize)
QUAD_REAL3 as_rgb_cn(QUAD_REAL3 V) { return (QUAD_REAL3(0.5,0.5,0.5) + 0.5*cube_normalize(V)); }
QUAD_REAL3 as_rgb_cn(QUAD_REAL4 V) { return (QUAD_REAL3(0.5,0.5,0.5) + 0.5*cube_normalize(V.xyz)); }

// return RGBA instead of RGB /////////

// normalized vector (saturated, at least) as a color
QUAD_REAL4 as_rgba(QUAD_REAL3 V) { return QUAD_REAL4((QUAD_REAL3(0.5,0.5,0.5) + 0.5*V.xyz),1.0); }
QUAD_REAL4 as_rgba(QUAD_REAL4 V) { return QUAD_REAL4((QUAD_REAL3(0.5,0.5,0.5) + 0.5*V.xyz),V.w); }

// un-normalized vector (spherical normalize)
QUAD_REAL4 as_rgba_n(QUAD_REAL3 V) { return QUAD_REAL4((QUAD_REAL3(0.5,0.5,0.5) + 0.5*normalize(V.xyz)),1.0); }
QUAD_REAL4 as_rgba_n(QUAD_REAL4 V) { return QUAD_REAL4((QUAD_REAL3(0.5,0.5,0.5) + 0.5*normalize(V.xyz)),V.w); }

// un-normalized vector (cube normalize)
QUAD_REAL4 as_rgba_cn(QUAD_REAL3 V) { return QUAD_REAL4((QUAD_REAL3(0.5,0.5,0.5) + 0.5*cube_normalize(V.xyz)),1.0); }
QUAD_REAL4 as_rgba_cn(QUAD_REAL4 V) { return QUAD_REAL4((QUAD_REAL3(0.5,0.5,0.5) + 0.5*cube_normalize(V.xyz)),V.w); }

#endif /* _DEBUG_TOOLS_FXH_ */

/***************************** eof ***/


/*********************************************************************NVMH3****
$Revision: #3 $

Copyright NVIDIA Corporation 2007
TO THE MAXIMUM EXTENT PERMITTED BY APPLICABLE LAW, THIS SOFTWARE IS PROVIDED
*AS IS* AND NVIDIA AND ITS SUPPLIERS DISCLAIM ALL WARRANTIES, EITHER EXPRESS
OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY
AND FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL NVIDIA OR ITS SUPPLIERS
BE LIABLE FOR ANY SPECIAL, INCIDENTAL, INDIRECT, OR CONSEQUENTIAL DAMAGES
WHATSOEVER (INCLUDING, WITHOUT LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS,
BUSINESS INTERRUPTION, LOSS OF BUSINESS INFORMATION, OR ANY OTHER PECUNIARY
LOSS) ARISING OUT OF THE USE OF OR INABILITY TO USE THIS SOFTWARE, EVEN IF
NVIDIA HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.

% This effect file uses colors
% to illustrate a number of shading vectors -- that is, values
% that are typically important in shading. This effect can often
% help find bogus parts of models, or be used to explore the contents
% of a model.

keywords: material debug virtual_machine bumpmap

date: 070403


To learn more about shading, shaders, and to bounce ideas off other shader
    authors and users, visit the NVIDIA Shader Library Forums at:

    http://developer.nvidia.com/forums/

******************************************************************************/



//// UN-TWEAKABLES - AUTOMATICALLY-TRACKED TRANSFORMS ////////////////

//float4x4 WorldITXf : WorldInverseTranspose < string UIWidget="None"; >;
float4x4 matMtl;
//float4x4 WvpXf : WorldViewProjection < string UIWidget="None"; >;
float4x4 matWorldViewProj;
//float4x4 WorldXf : World < string UIWidget="None"; >;
float4x4 matWorld;
//float4x4 ViewIXf : ViewInverse < string UIWidget="None"; >;
float4x4 matViewInv;

float2 ScreenSize = {1024.0f,768.0f};//: VIEWPORTPIXELSIZE < string UIWidget="None"; >;

/************************************************************/
/*** TWEAKABLES *********************************************/
/************************************************************/

float3 Lamp0Pos : Position <
    string Object = "PointLight0";
    string UIName =  "Lamp 0 Position";
    string Space = "World";
> = {0.0f,0.0f,0.0f};

float4 vecViewPos;

float Scale : UNITSSCALE <
    string units = "inches";
    string UIWidget = "slider";
    float UIMin = 0.001;
    float UIMax = 100.0;
    float UIStep = 0.01;
    string UIName = "Derivatives Brightness";
> = 64.0;

float Shading <
    string UIWidget = "slider";
    float uimin = 0.0;
    float uimax = 1.0;
    float uistep = 0.01;
    string UIName = "Flat<->Shaded";
> = 0.0;

float NormalGeom <
    string UIWidget = "slider";
    float uimin = 0.0;
    float uimax = 1.0;
    float uistep = 0.01;
    string UIName = "Normals as Geometry";
> = 0.0;

float UVGeom <
    string UIWidget = "slider";
    float uimin = 0.0;
    float uimax = 1.0;
    float uistep = 0.01;
    string UIName = "UVs as Geometry";
> = 0.0;

float NGRad <
    string UIWidget = "slider";
    float uimin = 1.0;
    float uimax = 10.0;
    float uistep = 0.01;
    string UIName = "Size of ALternate Geometry";
> = 1.0;

// shared shadow mapping supported in Cg version

/************* DATA STRUCTS **************/

/* data from application vertex buffer */
struct appdata {
    float3 Pos    : POSITION;
    float4 UV        : TEXCOORD0;
    float4 Normal    : NORMAL;
    float4 Tangent    : TANGENT0;
    float4 Binormal    : BINORMAL0;
};

/* data passed from vertex shader to pixel shader */
struct dbgVertOut {
    float4 HPosition    : POSITION;
    float2 TexCoord    : TEXCOORD0;
    float3 LightVec    : TEXCOORD1;
    float3 WorldNormal    : TEXCOORD2;
    float3 WorldEyeVec    : TEXCOORD3;
    float3 WorldTangent    : TEXCOORD4;
    float3 WorldBinorm    : TEXCOORD5;
    float3 WorldPos    : TEXCOORD6;
    float4 BaseColor : COLOR0;
};

/*********** vertex shader for all ******/

dbgVertOut debugVS(appdata IN) {
    dbgVertOut OUT;
    float4 Po = float4(IN.Pos,1.0);
    float4 normPo = float4((NGRad*IN.Normal.xyz),1.0);
    Po = lerp(Po,normPo,NormalGeom);
    float4 uvPo = float4((NGRad*IN.UV.xy),0.0,1.0);
    Po = lerp(Po,uvPo,UVGeom);
    OUT.HPosition = mul(Po,matWorldViewProj);
    // OUT.HPosition = mul(WvpXf,Po);
    OUT.WorldNormal = mul(IN.Normal,matMtl).xyz;
    OUT.WorldTangent = mul(IN.Tangent,matMtl).xyz;
    OUT.WorldBinorm = mul(IN.Binormal,matMtl).xyz;
    float4 Pw = mul(Po,matWorld);
    //OUT.LightVec = (Lamp0Pos-Pw.xyz);
    OUT.LightVec = (vecViewPos.xyz-Pw.xyz);
    OUT.TexCoord = IN.UV.xy;
    OUT.WorldPos = Pw.xyz;
    OUT.WorldEyeVec = normalize(matViewInv[3].xyz - Pw.xyz);
    float ldn = dot(normalize(OUT.LightVec),normalize(OUT.WorldNormal));
    ldn = max(0,ldn);
    OUT.BaseColor = lerp(float4(1,1,1,1),ldn.xxxx,Shading);
    return OUT;
}

/********* pixel shaders ********/

float4 debug_rgba(dbgVertOut IN,float3 Vec)
{
    float4 vc = as_rgba(Vec);
    float4 InColor = IN.BaseColor;
    return (InColor * vc);
}

float4 debug_rgba_n(dbgVertOut IN,float3 Vec)
{
    float4 vc = as_rgba_n(Vec);
    float4 InColor = IN.BaseColor;
    return (InColor * vc);
}

////////

float4 normalsRawPS(dbgVertOut IN) : COLOR { return debug_rgba(IN,IN.WorldNormal); }
float4 normalsNPS(dbgVertOut IN)   : COLOR { return debug_rgba_n(IN,IN.WorldNormal); }
float4 tangentRawPS(dbgVertOut IN) : COLOR { return debug_rgba(IN,IN.WorldTangent); }
float4 tangentNPS(dbgVertOut IN)   : COLOR { return debug_rgba_n(IN,IN.WorldTangent); }
float4 binormRawPS(dbgVertOut IN)  : COLOR { return debug_rgba(IN,IN.WorldBinorm); }
float4 binormNPS(dbgVertOut IN)    : COLOR { return debug_rgba_n(IN,IN.WorldBinorm); }
float4 viewNPS(dbgVertOut IN)      : COLOR { return debug_rgba(IN,IN.WorldEyeVec); }
float4 lightNPS(dbgVertOut IN)     : COLOR { return debug_rgba_n(IN,IN.LightVec); }

float4 uvcPS(dbgVertOut IN) : COLOR { return debug_rgba(IN,float3(IN.TexCoord.xy,0)); }

float4 vFacePS(dbgVertOut IN,float Vf : VFACE) : COLOR {
    float d = 0;
    if (Vf>0) d = 1;
    return debug_rgba(IN,d.xxx);
}

float4 vPosPS(dbgVertOut IN,float2 Vpos : VPOS) : COLOR {
    float2 c = Vpos.xy / ScreenSize.xy;
    return debug_rgba(IN,float3(c.xy,0));
}

float4 uvDerivsPS(dbgVertOut IN) : COLOR
{
    float2 dd = Scale * (abs(ddx(IN.TexCoord)) + abs(ddy(IN.TexCoord)));
    return debug_rgba(IN,float3(dd.xy,0));
}

float4 dPduNPS(dbgVertOut IN) : COLOR
{
    float3 dPx = ddx(IN.TexCoord.x) * ddx(IN.WorldPos);
    float3 dPy = ddy(IN.TexCoord.x) * ddy(IN.WorldPos);
    return debug_rgba(IN,(dPx+dPy));
}

float4 dPdvNPS(dbgVertOut IN) : COLOR
{
    float3 dPx = ddx(IN.TexCoord.y) * ddx(IN.WorldPos);
    float3 dPy = ddy(IN.TexCoord.y) * ddy(IN.WorldPos);
    return debug_rgba_n(IN,(dPx+dPy));
}

float4 halfAnglePS(dbgVertOut IN) :COLOR {
    float3 Ln = normalize(IN.LightVec);
    float3 Vn = normalize(IN.WorldEyeVec);
    // float3 Hn = normalize(Vn + Ln);
    return debug_rgba_n(IN,(Vn+Ln));
}

float4 facingPS(dbgVertOut IN) :COLOR {
    float3 Nn = normalize(IN.WorldNormal);
    float3 Vn = normalize(IN.WorldEyeVec);
    return debug_rgba(IN,float3(abs(dot(Nn,Vn)).xxx));
}

/*
float4 dPduNxPS(dbgVertOut IN) : COLOR
{
    float3 dPx = ddx(IN.TexCoord.x) * ddx(IN.WorldPos);
    float3 dPy = ddy(IN.TexCoord.x) * ddy(IN.WorldPos);
    float3 dPdu = normalize(dPx+dPy);
    float3 Nn = normalize(IN.WorldNormal);
    float3 nTan = cross(dPdu,Nn);
    return debug_rgba(IN,nTan);
}
*/

/****************************************************************/
/****************************************************************/
/******* TECHNIQUES *********************************************/
/****************************************************************/
/****************************************************************/

/*
technique uv_Coordinates {
    pass p0 {
	VertexShader = compile vs_2_0 debugVS();
		ZEnable = true;
		ZWriteEnable = true;
		ZFunc = LessEqual;
		AlphaBlendEnable = false;
		CullMode = None;
	PixelShader = compile ps_2_a uvcPS();
    }
}
*/

technique worldNormalVecs_Raw {
    pass p0 {
	VertexShader = compile vs_2_0 debugVS();
		ZEnable = true;
		ZWriteEnable = true;
		ZFunc = LessEqual;
		AlphaBlendEnable = false;
		CullMode = None;
	PixelShader = compile ps_2_a normalsRawPS();
    }
}



technique worldNormalVecs_Normalized {
    pass p0 {
	VertexShader = compile vs_2_0 debugVS();
		ZEnable = true;
		ZWriteEnable = true;
		ZFunc = LessEqual;
		AlphaBlendEnable = false;
		CullMode = None;
	PixelShader = compile ps_2_a normalsNPS();
    }
}


technique worldTangentVecs_Raw {
    pass p0 {
	VertexShader = compile vs_2_0 debugVS();
		ZEnable = true;
		ZWriteEnable = true;
		ZFunc = LessEqual;
		AlphaBlendEnable = false;
		CullMode = None;
	PixelShader = compile ps_2_a tangentRawPS();
    }
}


technique worldTangentVecs_Normalized {
    pass p0 {
	VertexShader = compile vs_2_0 debugVS();
		ZEnable = true;
		ZWriteEnable = true;
		ZFunc = LessEqual;
		AlphaBlendEnable = false;
		CullMode = None;
	PixelShader = compile ps_2_a tangentNPS();
    }
}


technique worldBinormalVecs_Raw {
    pass p0 {
	VertexShader = compile vs_2_0 debugVS();
		ZEnable = true;
		ZWriteEnable = true;
		ZFunc = LessEqual;
		AlphaBlendEnable = false;
		CullMode = None;
	PixelShader = compile ps_2_a binormRawPS();
    }
}


technique worldBinormalVecs_Normalized {
    pass p0 {
	VertexShader = compile vs_2_0 debugVS();
		ZEnable = true;
		ZWriteEnable = true;
		ZFunc = LessEqual;
		AlphaBlendEnable = false;
		CullMode = None;
	PixelShader = compile ps_2_a binormNPS();
    }
}

technique worldViewVec_Normalized {
    pass p0 {
	VertexShader = compile vs_2_0 debugVS();
		ZEnable = true;
		ZWriteEnable = true;
		ZFunc = LessEqual;
		AlphaBlendEnable = false;
		CullMode = None;
	PixelShader = compile ps_2_a viewNPS();
    }
}

technique worldLightVec_Normalized {
    pass p0 {
	VertexShader = compile vs_2_0 debugVS();
		ZEnable = true;
		ZWriteEnable = true;
		ZFunc = LessEqual;
		AlphaBlendEnable = false;
		CullMode = None;
	PixelShader = compile ps_2_a lightNPS();
    }
}

technique halfAngles {
    pass p0 {
	VertexShader = compile vs_2_0 debugVS();
		ZEnable = true;
		ZWriteEnable = true;
		ZFunc = LessEqual;
		AlphaBlendEnable = false;
		CullMode = None;
	PixelShader = compile ps_2_a halfAnglePS();
    }
}

technique facingRatio {
    pass p0 {
	VertexShader = compile vs_2_0 debugVS();
		ZEnable = true;
		ZWriteEnable = true;
		ZFunc = LessEqual;
		AlphaBlendEnable = false;
		CullMode = None;
	PixelShader = compile ps_2_a facingPS();
    }
}

technique uv_Derivatives {
    pass p0 {
	VertexShader = compile vs_2_0 debugVS();
		ZEnable = true;
		ZWriteEnable = true;
		ZFunc = LessEqual;
		AlphaBlendEnable = false;
		CullMode = None;
	PixelShader = compile ps_2_a uvDerivsPS();
    }
}


technique dPdu_Normalized {
    pass p0 {
	VertexShader = compile vs_2_0 debugVS();
		ZEnable = true;
		ZWriteEnable = true;
		ZFunc = LessEqual;
		AlphaBlendEnable = false;
		CullMode = None;
	PixelShader = compile ps_2_a dPduNPS();
    }
}


technique dPdv_Normalized {
    pass p0 {
	VertexShader = compile vs_2_0 debugVS();
		ZEnable = true;
		ZWriteEnable = true;
		ZFunc = LessEqual;
		AlphaBlendEnable = false;
		CullMode = None;
	PixelShader = compile ps_2_a dPdvNPS();
    }
}


technique vFace_Register {
    pass p0 {
	VertexShader = compile vs_3_0 debugVS();
		ZEnable = true;
		ZWriteEnable = true;
		ZFunc = LessEqual;
		AlphaBlendEnable = false;
		CullMode = None;
	PixelShader = compile ps_3_0 vFacePS();
    }
}


technique vPos_Register {
    pass p0 {
	VertexShader = compile vs_3_0 debugVS();
		ZEnable = true;
		ZWriteEnable = true;
		ZFunc = LessEqual;
		AlphaBlendEnable = false;
		CullMode = None;
	PixelShader = compile ps_3_0 vPosPS();
    }
}
// # debug_tech(dPduX,debugVS,dPduNxPS)

/***************************** eof ***/