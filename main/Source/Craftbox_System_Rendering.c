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

http://en.wikipedia.org/wiki/Volume_rendering
http://en.wikipedia.org/wiki/Deferred_shading
http://gamestart3d.com/wiki/index.php?title=Forward_or_Deferred_rendering%3F

+ Fixed Function Effects List
- [X] Watershader
- [X] Random multitexturing
- [X] Environment Mapping
- [X] Improved Overlay 

+ Shaders List
- [X] Watershader
- [ ] Light Shaft
- [ ] God Rays
- [X] Specular
- [X] Velvet
- [X] Fur
- [ ] (Motion) Blur
- [X] Chrome
- [ ] Multitexturing
- [X] Toon
- [X] Grass waving
- [ ] Refraction
- [X] Ocean
- [ ] Flame
- [ ] Soft Particles


>+++
--------------------------------------------------
*/

//MATERIAL *ffeWater;
//MATERIAL *ffeTerrainMultitexturing;
//MATERIAL *ffeEnv;
//MATERIAL *ffeImprovedOverlay;
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

/*
--------------------------------------------------
GraphicsSettingsStruct *CreateGraphicsStruct(int..)

Desc: Creates a new GraphicsSettingsStruct struct.
 -1 gives default value based on guessing. (planned)

Returns: A GraphicsSettingsStruct struct
--------------------------------------------------
*/
GraphicsSettingsStruct *CreateGraphicsStruct(

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
   
   GraphicsSettingsStruct *newStruct = malloc( sizeof(GraphicsSettingsStruct) );

   newStruct->Brightness = brightness;
   newStruct->BitDepth = bitdepth;
   newStruct->AFLevel = af;
   newStruct->AALevel = aa;
   newStruct->_SSAO = ssao;
   newStruct->DOF = dof;
   newStruct->HDR = hdr;
   newStruct->Shadows = shadows;
   newStruct->ObjShaders = objshaders;
   newStruct->PPE = ppe;
   
   return newStruct;
   
}

/*
--------------------------------------------------
void ApplyGraphicsSettings( GraphicsSettingsStruct *dConfig )

Desc: Apply advanced graphics settings such as 
SSAO, HDR, Depth of Field, shadows and such
Rendering device will be restarted whenever necessary.

Returns: -
--------------------------------------------------
*/
void ApplyGraphicsSettings( GraphicsSettingsStruct *dConfig ) {
	
	while(!dConfig) wait(1);
	
	video_gamma = dConfig->Brightness;
	video_depth = dConfig->BitDepth;
	d3d_antialias = dConfig->AALevel;
	d3d_anisotropy = dConfig->AFLevel;
}

/*
--------------------------------------------------
void SetDefaultGraphicsSettings()

Desc: Sets the pre-defined graphics struct (defaultConfig) to default settings.

Returns: -
--------------------------------------------------
*/
void SetDefaultGraphicsSettings() {
	
	wait(1);
   
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
	
	WriteLog("[X] Task completed.");
	NewLine();
	
}

// Here goes custom shaders...
MATERIAL *ffeWater =
{
	skin1 = waterbump;
	skin2 = envspec;

	event = mtl_ffpwater_event;
	flags = ENABLE_VIEW;
	
	effect = "water.fx";
}

MATERIAL *ffeTerrainMultitexturing =
{
	skin1 = sand;
	skin2 = grass;
	skin3 = road;
	skin4 = stone;

	effect = "ffp5tex.fx";
}


MATERIAL* ffeEnv = 
{
	skin1 = transenvmap_cube;
	
	flags = ENABLE_VIEW;
	event = transenv_event;
	effect = "Envmapping.fx";
}

MATERIAL *ffeImprovedOverlay = 
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

// Public actions for entities
action sffeWater()
{
	ffeWater.matrix11 = floatv(10);
	ffeWater.matrix22 = floatv(5);

	bmap_to_mipmap(ffeWater.skin1);
	bmap_to_mipmap(ffeWater.skin2);

	my.material = ffeWater;
}

action sffeMultiTex()
{
	bmap_to_mipmap(ffeTerrainMultitexturing.skin1);
	bmap_to_mipmap(ffeTerrainMultitexturing.skin2);
	bmap_to_mipmap(ffeTerrainMultitexturing.skin3);
	bmap_to_mipmap(ffeTerrainMultitexturing.skin4);
	
	my.material = ffeTerrainMultitexturing;
}

action sffeEnvMap()
{
	bmap_to_cubemap(bmap_to_mipmap(ffeEnv.skin1));
	
	set(my,TRANSLUCENT);
	my.alpha=50;
	my.material = ffeEnv;
}

action sffeIOverlay() {
	
	my.material = ffeImprovedOverlay;
	
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