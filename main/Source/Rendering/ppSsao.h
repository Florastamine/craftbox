//----------------------------------------------------------------------------------------
// SSAO v0.6 for Gamestudio A7 & A8
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

#ifndef ppSsao_h
#define ppSsao_h

#define SSAO

//- DETERMINE ENGINE VERSION -------------------------------------------------------------
// This is used to automatically disable unavailable or unnecessary features by design.

	#define A7
	
	#ifdef VERSION_830
		#define A8
	#endif

	#ifdef VERSION_820
		#define A8
	#endif

	#ifdef VERSION_810
		#define A8
	#endif

	#ifdef A8
		#undef A7
	#endif
	
	
//- CONFIGURATION ------------------------------------------------------------------------
// You can use this variables to configure the SSAO effect. All available compiler defines
// are listed and explained here as well, but are commented out. If you want to use them,
// you can uncomment them here; or do that _before_ you include ppSsao.h (see demos).



// Occluder ratio
// Determines the neglection of near vs. distant occluders. If you lower this
// value between 0 and 1, surface dependent occlusion will be removed

	float ssaoRatioNearDistantOccluders = 0.5;


// Contrast
// To increase the brightness of highlighted edges (convex areas) or the darkness
// of ambient occlusion (concave areas), you can use the following weights:

	// disables contrasting
	// #define SSAO_NO_CONTRASTING 
	
	// enforces contrasting with the below constants
	// #define SSAO_STATIC_CONTRASTING 
	// #define SSAO_CONVEX_HIGHLIGHT 1.0
	// #define SSAO_CONCAVE_DARKNESS 1.2

	// variables for dynamic contrasting
	#ifndef SSAO_NO_CONTRASTING
	#ifndef SSAO_STATIC_CONTRASTING
		float ssaoConvexHighlight = 1.0; // brightnes of edges
		float ssaoConcaveDarkness = 1.2; // darkness of ambient occlusion
	#endif
	#endif


// Surface types

	// disables soft alpha mapping
	// #define SSAO_NO_SOFTALPHA
	
	// surfaces type UIDs
	
		// solid (default)
		#define SSAO_TYPE_SOLID (1<<0) 
		
		// alphatesting (alpha clipped if < 50%)
		#define SSAO_TYPE_BINARY (1<<1)
		
		// soft alpha mapped, no contribution to SSAO
		#ifndef SSAO_NO_SOFTALPHA
			#define SSAO_TYPE_SOFTALPHA (1<<2)
		#endif
		
		// ignored, receives SSAO from behind surfaces (like decals)
		#define SSAO_TYPE_IGNORE (1<<3)	
	
	// this entity skill is used for storing surface data
	#define SURFACE skill100


// Gpu bone support
// Disabled always for A7 and only useful for A8 pro. If you have a pro-edition and you
// use gpu-bones, activate them for with the following define to gain extra speed:
	
	// enables support for gpu-bones (A8 pro only)
	// #define SSAO_GPU_BONES


// Particles
// Point particles are instantiated into the scene after the whole SSAO process. If
// you don't want this (for whatever reason) or don't use particles, please disable
// the with the following define.
	
	// disables particle instantiation
	// #define SSAO_NO_PARTICLES


// Fog
// Fog requires some overhead in the shaders and even more for A7 than for A8. If you
// don't use fog at all, please disable it with the following define.
	
	// disables fog handling
	// #define SSAO_NO_FOG
	
	
// Sky
// If no sky is ever visible, you can disable sky support to save some extra GPU cycles:

	// disable sky handling
	//#define SSAO_NO_SKY


// G-buffer
// The G-buffer (G for geometry) involves re-rendering the scene. Since some objects
// are clipped away, SSAO creates two depth- and two normalmaps: once with clipped
// objects (clipped map) and once "everything" (full map), so that  you can recycle
// them in additional PP effects, like DOF (see humanoid demo). It is deactivated by
// default, so if you need this use the following defines:

	// enables generation of both full depth- and normal maps
	// #define SSAO_FULL_MAPS
	
	// enables either only generation of a full depth- and/or normal map
	// #define SSAO_FULL_DEPTH
	// #define SSAO_FULL_NORMALS
	
	
// SSAO approximation
	
	// samples taken by the SSAO stage
	#define SSAO_SAMPLES 1
	
	// microsphere scaling per sample
	#define SSAO_SAMPLE_SCALE_STEP 2.4
	
	
// Thresholded blur
	
	// blur samples
	#define SSAO_BLUR_SAMPLES 13
	
	// deactives the use of all used thresholds
	// #define SSAO_NO_BLUR_T
	
	// deactives either the normal- and/or depth thresholding
	// #define SSAO_NO_BLUR_NORMAL_T
	// #define SSAO_NO_BLUR_DEPTH_T 
	
	
// Bilateral upsampling
	
	// normal thresholding
	#define SSAO_UPSAMPLE_NORMAL_POW 16
	
	// depth thresholding
	#define SSAO_UPSAMPLE_DEPTH_T 8
	
	
// Combine target
// If a view is staged behind the combine view, SSAO write the combined diffuse * ao
// image into a render target. If you don't want this and you want to process the
// image via TargetMap, use following define:
	
	// supresses render target creation for the combine image
	// #define SSAO_NO_COMBINE_TARGET
	
	
// External events
// The following events are fired in certain situations. You can couple your code to
// these in order to synchronize your PP chain with SSAO, like when the resolution
// changed or when SSAO is activated/deactived or so.

	// targets were recreated (on startup or when resolution has changed)
	EVENT on_ssaoTargetRecreated = NULL;
	
	// when SSAO has been deactivated
	EVENT on_ssaoDeactivated = NULL;
	
	// when SSAO has been activated
	EVENT on_ssaoActivated = NULL;
		
		
		
//- FUNCTIONS ----------------------------------------------------------------------------
// Below you find all functions that can be used to use SSAO in your game. Please the
// manual for a more in-depth description of each of them.
	
	
	
// Initialization
// You can run SSAO in standalone or source mode. The difference is, that when SSAO is de-
// activated, the G-Buffer is still sampled in source mode. If you reuse the G-Buffer data
// in a later PP effect (like DOF; see humanoid demo), you can use this mode of operation,
// in order to recycle the generated depth- and/or normal without the need of sampling it
// on your own.

	// modes of operation
	#define SSAO_MODE_STANDALONE 1 // default, see SSAO_MODE_DEF
	#define SSAO_MODE_SOURCE 2
	#define SSAO_MODE_DEF SSAO_MODE_STANDALONE // default mode

	// Use one of the following functions to run SSAO. Please read the manual to select
	// the one which you need.
	
		// pre: camera, no post view, standalone
		void runSsao ();
		
		// custom mode; pre: camera, no post view
		void runSsao (long mode);
		
		// custom pre view; no post view, standalone
		void runSsao (VIEW* base);
		
		// custom pre view and -mode; no post view
		void runSsao (VIEW* base, long mode);
		
		// custom pre- and post mode; standalone
		void runSsao (VIEW* pre, VIEW* post);
		
		// custom pre-, post view and -mode
		void runSsaoContext (VIEW* pre, VIEW* post, long mode);	

		// NOTE: I would have renamed runSsaoContext to runSsao (or better: "ssao"), but
		// the Lite-C compiler in A8 selects more precisely overloaded functions and since
		// I want compatibility for A7 and this simply doesn't work, I had to do this.


// State
// Use the following functions to get to know the state of SSAO (is it active?) and to set
// or toggle it.

	// set SSAO state with true or false, returns true if it was successful
	BOOL setSsaoState (BOOL active);
	
	// if SSAO is enabled, it gets deactivated and vice versa. The new state is returned.
	BOOL toggleSsaoState ();
	
	// returns the current state
	BOOL getSsaoState ();
	
	
// Render targets
// Use the following functions to get the BMAP*'s of the G-Buffer and other render targets

	// Diffuse
	BMAP* getSsaoDiffuseMap (); // e.g. the camera image

	// G-Buffer
	
		BMAP* getSsaoClippedDepthMap ();
		BMAP* getSsaoClippedNormalMap ();
		BMAP* getSsaoFullDepthMap ();
		BMAP* getSsaoFullNormalMap ();

		#ifndef SSAO_NO_SOFTALPHA
			BMAP* getSsaoSoftAlphaMap ();
		#endif
		
	// Combine
	#ifndef SSAO_NO_COMBINE_TARGET
		BMAP* getSsaoCombineMap ();
	#endif
	
	
// De-initialization
// If you want to remove SSAO completely from your game, use these functions. Not necess-
// ary, if you close the engine.

	// decouples SSAO from your renderchain and frees memory
	void removeSsao ();
	
	
// Renderchain & context
// The following functions can be used to define the pre- and post view of SSAO. In add-
// ition there are functions which you can use to manipulate the exterior render chain,
// in which SSAO is embedded, in order to safely adapt automatically staging and the SSAO
// context.

	// safely inserting or removing a view from the surrounding render chain
	void attachSsaoView (VIEW* predecessor, VIEW* newView);
	void detachSsaoView (VIEW*); 
	
	// context (pre: view before-, post: view directly after the SSAO chain)
	void setSsaoContext (VIEW* pre, VIEW* post);
	void getSsaoContext (VIEW** pre, VIEW** post); 
	
	
// Surface types
// In order to overwrite and set surface types or to get to know what surface type an obj-
// ect has, you can use the following functions.

	// registers a surface type for a specific entity
	void setSsaoSurface (ENTITY* e, int type);
	
	// returns, if a specific entity has a specific surface type
	BOOL hasSsaoSurface (ENTITY* e, int type);
	
	// returns the registered surface type of an entity
	int getSsaoSurface (ENTITY* e);
	

// Fog	
// If you use A7, you *have* to use these functions for fog.
#ifdef A7

	// replacement for "fog_color = 3;" -> activateSsaoFog(3);
	void activateSsaoFog (var colorNr);
	
	// replacement for "fog_color = 0;"
	void disableSsaoFog ();
	
	// replacement for "var c = fog_color;"
	var getSsaoFogColor ();

#endif



//- INTERNALS --- don't touch this, seriously! -------------------------------------------


#define SSAO_HD 1 // full size
#define SSAO_LD 2 // half size


// derived compiler defines

	#ifdef A7
		#undef SSAO_GPU_BONES
	#endif
	
	#ifdef SSAO_FULL_MAPS
		#define SSAO_FULL_DEPTH
		#define SSAO_FULL_NORMALS
	#else
		#ifdef SSAO_FULL_DEPTH
			#ifdef SSAO_FULL_NORMALS
				#define SSAO_FULL_MAPS
			#endif
		#endif
	#endif
	
	#ifdef SSAO_NO_BLUR_NORMAL_T
	#ifdef SSAO_NO_BLUR_DEPTH_T
		#define SSAO_NO_BLUR_T
	#endif
	#endif

	#ifdef SSAO_NO_BLUR_T
		#define SSAO_NO_BLUR_NORMAL_T
		#define SSAO_NO_BLUR_DEPTH_T
	#endif
	#endif

	#ifndef SSAO_SAMPLES
		#define SSAO_SAMPLES 1
	#endif

	#ifndef SSAO_BLUR_SAMPLES
		#define SSAO_BLUR_SAMPLES 13
	#endif

	#ifndef SSAO_UPSAMPLE_NORMAL_POW
		#define SSAO_UPSAMPLE_NORMAL_POW 16
	#endif

	#ifndef SSAO_UPSAMPLE_DEPTH_T
		#define SSAO_UPSAMPLE_DEPTH_T 8
	#endif

	#ifndef SSAO_SAMPLE_SCALE_STEP 2.4
		#define SSAO_SAMPLE_SCALE_STEP 2.4
	#endif

	#ifndef SSAO_NO_CONTRASTING
		#ifdef SSAO_STATIC_CONTRASTING
			#ifndef SSAO_CONVEX_HIGHLIGHT
				#define SSAO_CONVEX_HIGHLIGHT 1.0
			#endif
			#ifndef SSAO_CONCAVE_DARKNESS
				#define SSAO_CONCAVE_DARKNESS 1.2
			#endif
		#endif
	#endif


// precalculations

	void loadSsaoShaders ();
	BOOL compileSsaoShader (MATERIAL** mtlRef, char* customPreamble, char* filename);
	STRING* getSsaoShaderPreamble();

	STRING* ssaoShaderPreamble = NULL;


// mode of operation
int ssaoMode = SSAO_MODE_DEF;
BOOL ssaoActive = false;
	
	
// state
void deactivateSsao ();
void activateSsao ();

	
// render targets & -formats
	
	
	// HIGH RES
		
	BMAP* bmapSsaoDiffuseHires = NULL;
	#define SSAO_DIFF_HD 888 // 24bit (RGB)
	
	BMAP* bmapSsaoDepthHires = NULL;
	#define SSAO_DEPTH_HD 12 // 16bit float
	
	#ifdef SSAO_FULL_DEPTH
		BMAP* bmapSsaoDepthFullHires = NULL;
		#define SSAO_DEPTH_FULL_HD 12 // 16bit float
	#endif
  
	BMAP* bmapSsaoNormalHires = NULL;
	#define SSAO_NORMAL_HD 888 // 24bit RGB
	
	#ifdef SSAO_FULL_NORMALS
		BMAP* bmapSsaoNormalFullHires = NULL;
		#define SSAO_NORMAL_FULL_HD 888 // 24bit RGB
	#endif
	
	#ifndef SSAO_NO_SOFTALPHA
		BMAP* bmapSsaoAlphaHires = NULL;
		#define SSAO_ALPHA_HD 888 // 24bit RGB, A is used for blending
	#endif
	
	#ifndef SSAO_NO_COMBINE_TARGET
		// only allocated and filled, if a postprocessing view is defined via
		// ssaoSetContext to be used after the last SSAO stage
		BMAP* bmapSsaoCombineHires = NULL;
		#define SSAO_COMBINE_HD 8888 // 24bit RGB
	#endif


	// LOW RES
		
	#define SSAO_NRMxMASK_LD 8888 // 32bit RGB normal, A mask
	
	#ifndef SSAO_NO_BLUR_DEPTH_T
		#define SSAO_BLUR 122 // 32bit; 2x16bit ao & depth
	#else
		#define SSAO_BLUR 12 // 16bit, ao
	#endif
	
	#define SSAO_UPSAMPLING 8888 // 32bit RGBA, RGBA stores 2x2 hires ao values
		
		
// surface types
	
	// recognizes some surfaces types dependent on an entity's type
	void recognizeSsaoSurface (ENTITY* e);
	
	// if set, surface has been recognized
	#define SSAO_TYPE_RECOGNIZED (1<<8)
	
	// soft alpha quality
	#ifndef SSAO_SOFTALPHA_QUALITY
		#define SSAO_SOFTALPHA_QUALITY SSAO_LD
	#endif


// fog
#ifdef A7
	var ssaoFogNr; // active fog nr (A7 only)
#endif


// utility functions

	void copySsaoClippingParams (MATERIAL* m, VIEW* v);
	
	BOOL hasSsaoChainToBeRecreated ();
	
	// asserts that a target bmap is 1.) allocated and 2.) is as big as the screen
	BOOL hasSsaoBmapToBeRecreated (BMAP* bmap, int lodRatio);
	BMAP* recreateSsaoRenderTarget (BMAP** bmap, int format, int lodRatio);
	
	// asserts a view with flags, a view material and a stage
	void assertSsaoView (VIEW** view, long flags, MATERIAL* mat, VIEW* stage);
	
	// frees a system resource and nullifies the previous pointer (sic!)
	void ssaoFreePtr (void** ptrRef);
	
	// gets the first view who assigned the <successor>-VIEW as stage
	VIEW* ssaoGetViewPredecessor (VIEW* successor);
	
	// syncs a destination view with a source view (pos, angle, arc)
	void ssaoSyncView (VIEW* src, VIEW* dst);
	
	
// (pre-)deferred render event
	
	void mtlSsaoSrc_ev ();
	MATERIAL* mtlSsaoSrc =
	{
		event = mtlSsaoSrc_ev;
		flags = ENABLE_VIEW;
	}
	
	
// object surface materials	

	// gets the appropriate shader for an entity
	BOOL getSsaoObjShader (ENTITY* e, MATERIAL** mat, int src);
	
	// SSAO object material struct
		
		#define SSAO_OBJ_ANIM_CPU 0
		
		#ifdef SSAO_GPU_BONES
			#define SSAO_OBJ_ANIM_GPU 1
			#define SSAO_OBJ_ANIM_CNT 2
		#else
			#define SSAO_OBJ_ANIM_CNT 1
		#endif
		
		char** ssaoObjAnimDefine [SSAO_OBJ_ANIM_CNT];
		
		#define SSAO_SRC_DEPTH 0
		#define SSAO_SRC_NRMALPHA 1
		#define SSAO_SRC_CNT 2
		
		char* ssaoSrcDefine [SSAO_SRC_CNT];
		
		// stores for each src-view a material (incl. shader) for a cpu-anim-
		// ated entity or a gpu-animated entity
		typedef struct SsaoObjMtl
		{
			MATERIAL*** m; //[SSAO_OBJ_ANIM_..][SSAO_SRC_..] -> MATERIAL*
		} SsaoObjMtl;
		
		// loads effect files into the given SSAO object material
		SsaoObjMtl* createSsaoObjMtl (SsaoObjMtl** ref, char* preamble, char* fxFile);
	
	// global object surface materials
		
		SsaoObjMtl* ssaoObjMtlSky    = NULL; // sky
		SsaoObjMtl* ssaoObjMtlSolid  = NULL; // solid (default)
		SsaoObjMtl* ssaoObjMtlBinary = NULL; // binary alpha
		
		#ifndef SSAO_NO_SOFTALPHA
		   SsaoObjMtl* ssaoObjMtlSoftalpha = NULL; // soft alpha (supresses hidden AO by alpha)
		#endif


// shaders
	
	// TODO: generate this in Lite-C
	BMAP* bmapSsaoAoEncode = "ao_pp_encode.tga";

	// include <default.fx> for shader code
	#define PRAGMA_PATH "%EXE_DIR%\\code";
	#define PRAGMA_BIND "%EXE_DIR%\\code\\default.fx";
	#define PRAGMA_BIND "d3dcompiler_42.dll";
	
	// G-Buffer
		
		// object material switch
		function objMtlDeferredSwitch_ev ();
		MATERIAL* objMtlDeferredSwitch =
		{
			flags = ENABLE_RENDER;
			event = objMtlDeferredSwitch_ev;
		}
			
	// particle view
	#ifdef A7
	#ifndef SSAO_NO_PARTICLES
		function mtlSsaoParticle_ev ();
		MATERIAL* mtlSsaoParticle = // only for A7
		{
			// dummy shader
			effect = "float4 PS () : COLOR {return(0);} technique t {pass p {pixelShader = compile ps_2_0 PS();}}";
			
			flags = ENABLE_TREE;
			event = mtlSsaoParticle_ev; // clip event
		}
	#endif
	#endif
		
	// postprocessing
		
		// SSAO
		var mtlSsaoApproximation_ev ();
		MATERIAL* mtlSsaoApproximation =
		{
			flags = ENABLE_VIEW;
			event = mtlSsaoApproximation_ev;
		}
		
		// thresholded blur
		
			// horizontal & vertical pass
			MATERIAL* mtlSsaoBlurPassH = {effect = "";}
			MATERIAL* mtlSsaoBlurPassV = {effect = "";}
		
		// reversed bilateral upsampling
		MATERIAL* mtlSsaoUpsampling = {effect = "";}
		
		// combine
		function mtlSsaoCombine_ev ();
		MATERIAL* mtlSsaoCombine =
		{
			event = mtlSsaoCombine_ev;
			flags = ENABLE_VIEW;
		}

	
// postprocessing chain
	
	// context & diffuse
	VIEW *ssaoViewPre = NULL, *ssaoViewPost = NULL;
	VIEW *ssaoDiffuseSrc = NULL;
	
	// particle view
	#ifndef SSAO_NO_PARTICLES
		
		#ifdef A7
			#define SSAO_VIEW_PARTICLE_FLAGS (PROCESS_SCREEN | NOFOG | NOSKY | NOSHADOW | UNTOUCHABLE)
			#define SSAO_VIEW_PARTICLE_USE_DUMMY_MTL
		#endif
		
		#ifdef A8
			#define SSAO_VIEW_PARTICLE_FLAGS (PROCESS_SCREEN | NOFOG | NOSKY | NOWORLD | NOENT | NOSHADOW | UNTOUCHABLE)
		#endif
		
		// SSAO_VIEW_PARTICLE_USE_DUMMY_MTL means using mtlSsaoParticle as dummy
		// shader to prevent rendering; only for A7
		
		VIEW* viewSsaoParticle = NULL;
		
	#endif
	
	// combine
	VIEW* viewSsaoCombine =
	{
		flags = PROCESS_TARGET | CHILD;
		material = mtlSsaoCombine;
	}
	
	// bilateral upsampling
	VIEW* viewSsaoUpsampling =
	{
		flags = PROCESS_TARGET | CHILD;
		material = mtlSsaoUpsampling;
	}
	
	// thresholded blur
			
		// vertical blur pass
		VIEW* viewSsaoBlurPassV =
		{
			flags = PROCESS_TARGET | CHILD;
			material = mtlSsaoBlurPassV;
		}

		// horizontal blur pass
		VIEW* viewSsaoBlurPassH =
		{
			flags = PROCESS_TARGET | CHILD;
			material = mtlSsaoBlurPassH;
		}
		
	// SSAO
	VIEW* viewSsaoApproximation =
	{
		flags = PROCESS_TARGET | CHILD;
		material = mtlSsaoApproximation;
	}
	
	// G-Buffer

		// views
		VIEW* viewSsaoSrcDepth        = NULL;
		VIEW* viewSsaoSrcNormalsAlpha = NULL;

		// flags
		#ifndef SSAO_NO_PARTICLES
			#define SSAO_VIEW_SRC_FLAGS (CHILD | UNTOUCHABLE | NOFOG | NOSHADOW | NOPARTICLE)
		#else
			#define SSAO_VIEW_SRC_FLAGS (CHILD | UNTOUCHABLE | NOFOG | NOSHADOW)
		#endif
		
		
// chain setup
void recreateSsaoChain ();
void updateSsaoChain ();

	
// external events
void fireSsaoEvent (EVENT ev);


#include "./Source/Rendering/ppSsao.c"

#endif /* ppSsao_h */