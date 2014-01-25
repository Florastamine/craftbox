#ifndef Craftbox_System_Rendering

#define Craftbox_System_Rendering

/*
--------------------------------------------------
Craftbox_System_Rendering.c

Extra rendering stuff for the purpose of boosting craftbox's graphics.

Contains shaders/shader packages and postprocessing effects/
postprocessing effect packages from various sources, for example 
Shade-C (BoH_Havoc), Massive Shader Collection (Slin), mtlFX.c...

However it will not work (mostly, except the fixed function ones) with 
the free edition of 3D Gamestudio/A8. Shader support requires a 
Commercial license which costs $199.

If you find craftbox interested, please support the development 
by sending fixes/patches, request/updates for new features. Or, you 
can donate to help me get a Commercial license, this will greatly expands 
the ability of what craftbox can do, and help boosting its graphics a lot!

See here for license features comparison: 
http://www.conitec.net/english/gstudio/order8.php

Written by Nguyen Ngoc Huy, contains many shaders from various sources.
https://github.com/ngochuy2101
http://craftboxdev.blogspot.com/

TODO:
<+++



>+++

NOTES:
<+++

#include "sc_volumeTexture.h"
http://en.wikipedia.org/wiki/Volume_rendering

#include "sc_deferredLighting.h"
http://en.wikipedia.org/wiki/Deferred_shading

#include "sc_forward.h"
http://gamestart3d.com/wiki/index.php?title=Forward_or_Deferred_rendering%3F

+ Fixed Function Effects List
- [X] Watershader
- [X] Random multitexturing
- [X] Environment Mapping
- [X] Improved Overlay 

+ Shaders List
- [X] Watershader
- Light Shaft
- God Rays
- [X] Specular
- [X] Velvet
- [X] Fur
- (Motion) Blur
- [X] Chrome
- Multitexturing
- [X] Toon
- [X] Grass waving
- Refraction
- [X] Ocean
- Flame
- Soft Particles


>+++
--------------------------------------------------
*/

MATERIAL *FFE_Water;
MATERIAL *FFE_TerrainMultitexturing;
MATERIAL *FFE_Env;
MATERIAL *FFE_ImprovedOverlay;
//MATERIAL *Toon;
//MATERIAL *Chrome;
//MATERIAL *GrassWaving;
//MATERIAL *Fur1;
//MATERIAL *Ocean;
//MATERIAL *Velvety;
//MATERIAL *Specular;
//MATERIAL *Water;

BMAP *waterbump = "waves2.tga";
BMAP *envspec = "sky.tga";
BMAP *sand = "pebbles.tga";
BMAP *grass = "cliff.tga";
BMAP *road = "littlerocks.tga";
BMAP *stone = "longgrass.tga";
BMAP *transenvmap_cube = "envi_snow+6.tga";	// CubicEnvMap
//BMAP *Model_normalizecube_bmap = "tsnormalise.tga";
//BMAP *Model_tone_bmap = "ts2tone.tga";
//BMAP *chrome_lookup = "chrome_lookup.tga";
//BMAP *noise_bmap = "noise.tga";
//BMAP *color_bmap = "noise.tga";
//BMAP *wave_bump_bmap = "waves2.tga";
//BMAP *envcube_bmap = "envi_snow+6.tga";

void mtl_ffpwater_event();
void transenv_event();
void mtl_vegetation_init();

//#include "./Source/Craftbox_System_mtlFX.c"
//#include "./Source/Craftbox_System_mtlView.c"

// Xd1Vo's Projection texture
//#include "pMat.c" // projection materials
//#include "projMain.c" //code for creating matrix
//#include "eRender.c" //render bitmap for projection texture

// BoH_Havoc's Shade-C v 0.91 BETA Snapshot 1
#include "./Source/Rendering/sc_core.c"

// SSAO v0.6 for Gamestudio A7 & A8 by Christian Behrenberg
#include "./Source/Rendering/ppSsao.h"
//#include "./Source/Rendering/dof.c"

/*
--------------------------------------------------
GRAPHICSKONFIG *CreateGraphicsStruct(int..)

Desc: Creates a new GRAPHICSKONFIG struct.
 -1 gives default value based on guessing. (planned)

Returns: A GRAPHICSKONFIG struct
--------------------------------------------------
*/
GRAPHICSKONFIG *CreateGraphicsStruct(

int brightness,
int bitdepth,
int af,
int aa,

int ssao,
int dof,
int hdr,
int shadows,
int objshaders,
int ppe

) {
   
   GRAPHICSKONFIG *newStruct;

   newStruct->Brightness = abs(brightness);
   newStruct->BitDepth = abs(bitdepth);
   newStruct->AFLevel = abs(af);
   newStruct->AALevel = abs(aa);
   newStruct->_SSAO = abs(ssao);
   newStruct->DOF = abs(dof);
   newStruct->HDR = abs(hdr);
   newStruct->Shadows = abs(shadows);
   newStruct->ObjShaders = abs(objshaders);
   newStruct->PPE = abs(ppe);
   
   return newStruct;
   
}


/*
--------------------------------------------------
int CompareGraphicsStruct(GRAPHICSKONFIG *struct1, GRAPHICSKONFIG *struct2)

Desc: Compare two GRAPHICSKONFIG struct.

Returns: > 0 if struct1 differs from struct2.
--------------------------------------------------
*/
int CompareGraphicsStruct(GRAPHICSKONFIG *struct1, GRAPHICSKONFIG *struct2) {
   
   while( !struct1 || !struct2 ) wait(1);
   
   return (
   
   (struct1->Brightness != struct2->Brightness) ||
   (struct1->BitDepth != struct2->BitDepth) ||
   (struct1->AFLevel != struct2->AFLevel) || 
   (struct1->AALevel != struct2->AALevel) ||
   (struct1->_SSAO != struct2->_SSAO) ||
   (struct1->DOF != struct2->DOF) ||
   (struct1->Shadows != struct2->Shadows) ||
   (struct1->ObjShaders != struct2->ObjShaders) ||
   (struct1->PPE != struct2->PPE) ||
   (struct1->HDR != struct2->HDR)
   
   );
   
}

/*
--------------------------------------------------
void ApplyGraphicsSettings( GRAPHICSKONFIG *dConfig )

Desc: Apply advanced graphics settings such as 
SSAO, HDR, Depth of Field, shadows and such
Rendering device will be restarted whenever necessary.

Returns: -
--------------------------------------------------
*/
void ApplyGraphicsSettings( GRAPHICSKONFIG *dConfig ) {
	
	while(!dConfig) wait(1);
	
	video_gamma = dConfig->Brightness;
	video_depth = dConfig->BitDepth;
	d3d_antialias = dConfig->AALevel;
	d3d_anisotropy = dConfig->AFLevel;
	
	/*
	
	if( !dConfig->HDR && !dConfig->DOF && !dConfig->Shadows) {
		
		// switches off HDR views
		reset(sc_view_hdrDownsample,SHOW);
		reset(sc_view_hdrHighpass,SHOW);
		reset(sc_view_hdrBlur,SHOW);
		reset(sc_view_hdrHBlur,SHOW);
		reset(sc_view_hdrVBlur,SHOW);
		
		reset(sc_view_depth,SHOW);
		reset(sc_view_hdrGamma,SHOW);
		reset(sc_view_reflect,SHOW);
		//		reset(shadowView,SHOW); // local
		//		reset(shadowDepthView,SHOW);
		
		wait(1);
		video_set(sys_metrics(0)-1,0,0,0);
		sc_scSetup = 0;
		
		wait(2);

	}
	
	*/
	
	if( dConfig->HDR || dConfig->DOF || dConfig->Shadows ) sc_setup();
	
	// SSAO
	if (dConfig->_SSAO) {
		
		if( !ssaoLoaded ) LoadSSAO(); // If SSAO hasn't yet initialized, initializes and loads SSAO
		else toggleSsaoState();
		
	}
	
}

/*
--------------------------------------------------
int SetupShader()


--------------------------------------------------
*/
int SetupShader() {
	
	WriteLog("[ ] Setting up shaders");
	NewLine();
	
	if(edition < 3) {
		
		WriteLog("!! [ERROR] Still don't have enough money to afford a Commercial license.. :(");
		NewLine();
		
		return -1;
		
	}
	
	ApplyGraphicsSettings( defaultConfig );
	
	/*
	
	// Shade-C
	
	allowHDR = 1;
	allowDOF = 0;
	sc_bRefract = 1;
	sc_bWater = 1;
	sc_bReflect = 1;
	sc_bVolParts = 1;
	
	sc_setup();	
	
	sc_smSunSetup(screen_size.x, 2000, 1500, 0.002, 0);
	
	sc_lightRayStr =5.4;
	sc_lightRayLength = 3.5; //set light ray length
	
	//activate light rays
	sc_lightRays();
	
	//set mat_model to shadow material. Now all models without any material will receive shadows
	mat_model.effect = "sc_obj_doShadow.fx";
	//set mat_flat to shadow material. Now all level blocks with flat shading and without any material will receive shadows
	mat_flat.effect = "sc_level_doShadow.fx";
	mat_shaded.effect = "sc_level_doShadow.fx";
	
	set(sc_pan_sunDummy,SHOW);
	
	*/
	
	/*
	// SSAO
	_SSAO();
	while(proc_status(_SSAO)) wait(1);
	
	// Depth of field
	dof();
	
	// Misc.
	shadow_stencil = 2;
	//	stencil_blur(3);
	*/
	
	WriteLog("[X] Task completed.");
	NewLine();
	
	
}

// Here goes custom shaders...
MATERIAL *FFE_Water =
{
	skin1 = waterbump;
	skin2 = envspec;

	event = mtl_ffpwater_event;
	flags = ENABLE_VIEW;
	
	effect = "water.fx";
}

MATERIAL *FFE_TerrainMultitexturing =
{
	skin1 = sand;
	skin2 = grass;
	skin3 = road;
	skin4 = stone;

	effect = "ffp5tex.fx";
}


MATERIAL* FFE_Env = 
{
	skin1 = transenvmap_cube;
	
	flags = ENABLE_VIEW;
	event = transenv_event;
	effect = "Envmapping.fx";
}

MATERIAL *FFE_ImprovedOverlay = 
{
	event=mtl_vegetation_init;
	effect=
	"
	texture entSkin1;
	dword mtlSkill1;

	technique vegetation
	{
		pass p0
		{
			Texture[0]=<entSkin1>;
			ZWriteEnable=True;
			AlphaBlendEnable=False;
			AlphaTestEnable=True;
			AlphaRef=<mtlSkill1>;
			AlphaFunc=Greater;
			CullMode=CCW; // CCW or None

			ColorArg1[0]=Texture;
			ColorOp[0]=Modulate2X;
			ColorArg2[0]=Diffuse;
		}
	}
technique fallback{pass p0{}}
	";
}

/*

MATERIAL *Ocean = {
	
	skin1 = wave_bump_bmap;
	skin2 = envcube_bmap;
	effect = "ocean.fx";
	
}

MATERIAL *Toon =
{
	skin1 = Model_normalizecube_bmap;
	skin2 = Model_tone_bmap;
	effect = "toon.fx";
}

MATERIAL *Chrome = 
{
	skin1 = chrome_lookup;
	effect="chrome.fx";
}

MATERIAL *GrassWaving = {
	
	effect = "MovingGrass.fx";
	
}

MATERIAL *Fur1 =
{
	skin1 = noise_bmap;
	skin2 = color_bmap;
	
	effect = "Fur.fx";
}

MATERIAL *Velvety = {
	
	effect = "Velvety.fx";
	
	flags = TANGENT;
	
}

MATERIAL *Specular = {
	
	effect = "specular_world.fx";
	
	flags = TANGENT;
	
}

MATERIAL *Water = {
	
	skin1 = waterbump;
	skin2 = transenvmap_cube;
	
	flags = TANGENT;
	effect = "watershader.fx";
	
}

*/

void mtl_ffpwater_event()
{
	//Lets make it scroll in some direction
	mtl.skill1 += 10*time_step;
	mtl.skill2 += 10*time_step;
	mtl.matrix31 = floatd(mtl.skill1,40000);
	mtl.matrix32 = floatd(mtl.skill2,40000);
}

void transenv_event()
{
	mat_set(mtl.matrix,matViewInv);
	mtl.matrix41=0;
	mtl.matrix42=0;
	mtl.matrix43=0;
}

void mtl_vegetation_init()
{
	vec_set(mtl.emissive_blue,mat_model.emissive_blue);
	vec_set(mtl.ambient_blue,mat_model.ambient_blue);
	vec_set(mtl.diffuse_blue,mat_model.diffuse_blue);
	vec_set(mtl.specular_blue,mat_model.specular_blue);
	mtl.power=mat_model.power;
	mtl.albedo=mat_model.albedo;
	mtl.skill1=pixel_for_vec(vector(128,0,0),0,8888); // the first value in the vector is the threshold
}

action sFFE_Water()
{
	FFE_Water.matrix11 = floatv(10);
	FFE_Water.matrix22 = floatv(5);

	bmap_to_mipmap(FFE_Water.skin1);
	bmap_to_mipmap(FFE_Water.skin2);

	my.material = FFE_Water;
}

action sFFE_MultiTex()
{
	bmap_to_mipmap(FFE_TerrainMultitexturing.skin1);
	bmap_to_mipmap(FFE_TerrainMultitexturing.skin2);
	bmap_to_mipmap(FFE_TerrainMultitexturing.skin3);
	bmap_to_mipmap(FFE_TerrainMultitexturing.skin4);
	
	my.material = FFE_TerrainMultitexturing;
}

action sFFE_EnvMap()
{
	bmap_to_cubemap(bmap_to_mipmap(FFE_Env.skin1));
	
	set(my,TRANSLUCENT);
	my.alpha=50;
	my.material = FFE_Env;
}

action sFFE_IOverlay() {
	
	my.material = FFE_ImprovedOverlay;
	
}

/*

action sToon()
{
	
	bmap_to_cubemap(Toon.skin1);
	
	my.material = Toon;
}

action sChrome()
{
	my.material = Chrome;
	my.skill41 = floatv(random(2)-1);	//r
	my.skill42 = floatv(random(2)-1);	//g
	my.skill43 = floatv(random(2)-1);	//b
	my.skill44 = floatv(1.5);	//specular power
	Chrome.skill1 = floatv(1);	//reflectmap scale
}

action sGrassWaving() {
	
	my.material = GrassWaving;
	
}

action sFur1() {
	
	my.material = Fur1;
	
}

action sOcean() {
	
	bmap_to_cubemap(Ocean.skin2);
	my.material = Ocean;
	
}

action sVelvety() {
	
	my.material = Velvety;
	
}

action sSpecular() {
	
	my.material = Specular;
	
}

action sWater()
{
	bmap_to_cubemap(bmap_to_mipmap(Water.skin2));
	bmap_to_mipmap(Water.skin1);
	
	my.material = Water;

	set(my,TRANSLUCENT);
	set(my,NOFOG);
}

*/


/*
--------------------------------------------------
int AddToTextureProjectionArray(ENTITY *Ent)

Desc:

Returns: -
--------------------------------------------------
*/
int AddToTextureProjectionArray(ENTITY *Ent) {
	
	/*
	
	WriteLog("[ ] Trying to add an entity to the projection array...");
	NewLine();
	
	while(!Ent) wait(1);
	
	if(rEntCount < MAX_rEnts) {
		
		rEntCount += 1;
		rEnt[rEntCount] = Ent;
		
	}
	
	else {
		
		WriteLog("!! [ERROR] The projection array is full. Maximum number of entities allowed is ",MAX_rEnts);
		NewLine();
		WriteLog("!! From the ",MAX_rEnts + 1);
		WriteLog(" entity, shadows will no longer be casted.");
		NewLine();
		
	}
	
	WriteLog("[X] Task completed for AddToTextureProjectionArray(ENTITY *Ent) at ");
	WriteLog( (STRING *) Ent->type );
	NewLine();
	
	*/
	
	wait(1);
	
}

/*
--------------------------------------------------
void RemoveFromTextureProjectionArray(ENTITY *Ent)

Desc:

Returns: -
--------------------------------------------------
*/
void RemoveFromTextureProjectionArray(ENTITY *Ent) {
	
	/*
	
	// Test for deletion of the newest created entity.
	if(rEnt[rEntCount] == Ent) {
		
		rEnt[rEntCount] = NULL;
		rEntCount -= 1;
		
		return;
		
	}

	if(rEntCount == -1) return;

	int temprEntCount = 0;

	// Check if this entity exists in the rEnt array.
	for( ; temprEntCount <= rEntCount; temprEntCount++)
	if(rEnt[temprEntCount] == Ent) break;

	ptr_remove(rEnt[temprEntCount]);

	if(rEnt[temprEntCount+1]) { // Shift 'em
		
		int temprEntCount2 = temprEntCount + 2;
		
		while(rEnt[temprEntCount2]) {
			
			rEnt[temprEntCount2 - 1] = rEnt[temprEntCount2];
			temprEntCount2 -= 1;
			
			wait(1);
			
		}
		
	}
	
	rEntCount -= 1;
	
	*/
	
	wait(1);
	
}

#endif