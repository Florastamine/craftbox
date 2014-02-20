#ifndef HEADER_H
#define HEADER_H

/*
Craftbox.h

Base declarations.
For example if you want to make fried eggs you need eggs. That's all.

Written by Nguyen Ngoc Huy
https://github.com/ngochuy2101
http://craftboxdev.blogspot.com/

TODO:
<+++



>+++

NOTES:
<+++



>+++
--------------------------------------------------
*/

// I do not write all available paths because of 3D Gamestudio's annoying "bug": Path exceeded.
#define PRAGMA_PATH "./Source"
#define PRAGMA_PATH "./Source/Rendering"

#define PRAGMA_PATH "./Cooked2D"
#define PRAGMA_PATH "./Cooked2D/Skies"

#define PRAGMA_PATH "./CookedSounds"
#define PRAGMA_PATH "./CookedSounds/Music"

#include <acknex.h> // Engine objects
//#include <stdio.h>
#include <strio.c>
#include <d3d9.h>
//#include <particles.c>
#include <level.c>

#define CBOX_DEVELOPMENT
#define USE_TXT_LOG

typedef short bool;

bool cbPlaytesting = false;
bool cbNonWindows = false; // For running craftbox under other environments that is not Windows.
bool cbFlatMenu = false; // Set this prior to executing the menu loader cause craftbox to use flat menu instead of 3D-based menu.
bool cbError_NoGround; // Used for marking error caused by no grounds available
bool cbFinishedLoadKernel; // To indicate the kernel has been successfully loaded.
bool cbKernelRunning = false;
bool cbInBuildment = false;
bool cbUsectraceOptimization = false;
bool cbUseDistanceBasedOptimization = true;
bool cbRandomPlacement = false; // Random placement of objects..useful for generating random scenes
bool cbTerrainEditing = false; // We're in the terrain editing mode
bool PlayerPresent = false;
bool AllowREC = true;
bool AllowCompass = true; // If disabled, compass calculation will still be performed, but the GUI won't display it.

int SessionsCount = 0; // Count how many sessions (worlds) we've played so far
int guiCurrentViewPreset = 1; // Which view to be used at startup?

var LOGFILEHNDL; // Global variable for handling the log file.

var VOL_EFFECTS = 75, VOL_MUSIC = 100; // Alternative vars for sound_vol and midi_vol.

int sResX, sResY, sResMode; // Store screen resolution in X and Y. 

short CameraPosID_temp = 0;  // Temporary variable to store guiCurrentViewPreset at some point
int DialogueSentencesCount = 0; // Count sentences in a dialogue.

short LoadWorldBreak = 0; // Indicate failure when loading a new level.

// Two strings for release number and release mode.
STRING *RELEASE_STR_VER = "0.1";
STRING *RELEASE_STR_INFO = "pre-alpha";
//////////////////////////////////////////////////////////////

// A TEXT struct represents craftbox console.
TEXT* def_ctxt = { font = "Arial#15b"; string("Console","#80"); layer = 999; }

// Some variables and an ANGLE struct represent the debug panel.
var def_dfps,def_dtps,def_dtlv,def_dtcs,def_dtac,def_dtrf,def_dsnd;
ANGLE def_cang;

var def_shot_num = 0;
var def_oldmouse = 0;

var fh_n;
BMAP *canvas;
BMAP *b_render1;
BMAP *b_render2;
BMAP *b_render3;
BMAP *b_render4;
BMAP *b_render5;
BMAP *b_render6;
var cubenumber = 0;
var directions[18] = {180, 0, 0, 90, 0, 0, 0, 0, 0, -90, 0, 0, 90, -90, 0, 90, 90, 0};
STRING *tempstring1 = "#200";
STRING *tempstring2 = "#200";
STRING *_ts_ = "#200";

void write8(var);
void write16(var);
void str_padding(STRING *, var, var);
void write_cubemap();
void capture_cubemap();

void def_box(var, var, var, var, VECTOR *);
void def_debug();
void def_shot();
void def_save();
void def_load();
void def_video();
void def_screen();
void def_console();
void draw_rotated_bbox(ENTITY *);

/*

void def_startup() 
{ 

}

*/

///////////////////////////////////////////////////////////
// This struct is applied to a wide range of objects.
// It can be used to copy normal objects, lights, or particle
// effects
////////////////////////////////////////////////////////////
typedef struct {
	
	////////////////////////////////////////////////////////////
	// General information that is copied regardless
	// which type the object is.
	////////////////////////////////////////////////////////////
	int of_objtype; // The type of object that has been copied.
	
	var _scale_x, _scale_y, _scale_z,
	_pan, _tilt, _roll,
	_alpha, _ambient;
	
	STRING *name;
	
	////////////////////////////////////////////////////////////
	// Unique properties each type of object has.
	////////////////////////////////////////////////////////////
	
	////////////// Normal objects (chair, mouse, salon, book...)
	bool pPhysics, pStatic, _flags[ 8 ];
	
	// Some vars define its physical properties
	// var mass, friction
	
	MATERIAL *m;
	
	////////////// Particle objects
	int _ParticleID;
	
	////////////// Light objects
	var _red, _green, _blue, _range;
	int _LightMode;
	
	////////////// Sound objects
	
	////////////// Node placer
	
	bool AnyData;
	
	var _skill[ 130 ];
	
} ObjectStruct;

///////////////////////////////////////////////////////////
// Graphics struct contains switchers for certain effects, shaders.
// By default a defaultConfig struct (see below) is defined
// for managing graphics settings within craftbox.
////////////////////////////////////////////////////////////
typedef struct {
   
   // Basic graphics settings
   int Brightness;
   int BitDepth;
   int AFLevel;
   int AALevel;
   
   // Shaders and screenspace effects
   int HDR;
   int DOF;
   int _SSAO;
   int Shadows;
   int ObjShaders;
   int PPE;
   
   
} GraphicsSettingsStruct;

ObjectStruct clipboard;
GraphicsSettingsStruct defaultConfig, tempConfig; // tempConfig is used for temporary saving configuration for later comparison
//////////////////////////////////////////////////////////////

// System

char undef = '-';
char endline = '|';
char separate = '_';
char dot = '.';
char strseparate_start = '[';
char strseparate_end = ']';
char wdstart = '+';
char wdend = '+';
char gdundef = '_';
char openent = '(';
char closeent = ')';
char DialogueSentenceDelimiter = ';';
char DialogueFileEnd = '_';

STRING *PARAM_NOLOGFILE = " -dwl";
//STRING *PARAM_DEV = " -dev";
//STRING *PARAM_SUSPENDKERNEL = " -dlk";
STRING *PARAM_USECTRACE = " -com";

//STRING *tag_header = "craftbox World Data File";
//STRING *tag_header_warn = "This file contains (encrypted) world information. Blah, blah, blah...";
//STRING *tag_system_header = "System data";
//STRING *tag_geodata = "Terrain geometry data";
//STRING *tag_objectdata = "Object data";

#define MENU_CAMERA_LAUNCH 1
#define MENU_CAMERA_NEW_GAME 2
#define MENU_CAMERA_LOAD_GAME 3
#define MENU_CAMERA_OPTIONS 4
#define MENU_CAMERA_TROPHIES 5
#define MENU_CAMERA_HELP 6
#define MENU_CAMERA_CREDIT 7
#define MENU_CAMERA_LAUNCH_GAME 8
#define MENU_CAMERA_EXIT 9

// Fixed 
VECTOR *MENU_CAMERA_LAUNCH_pos = { x = -240; y = -300; z = -36; }
VECTOR *MENU_CAMERA_NEW_GAME_pos = { x = 437; y = -215; z = -98; }
//VECTOR *MENU_CAMERA_NEW_GAME_pos = { x = 230; y = -193; z = -45; }
VECTOR *MENU_CAMERA_LOAD_GAME_pos = { x = 213; y = -176; z = -91; }
VECTOR *MENU_CAMERA_HELP_pos = { x = -76; y = 86; z = -33;}
VECTOR *MENU_CAMERA_TROPHIES_pos = { x = -44; y = 126; z = -90; }
//VECTOR *MENU_CAMERA_LAUNCH_GAME_pos = { x = 517; y = -351; z = -88; }
VECTOR *MENU_CAMERA_LAUNCH_GAME_pos = { x = 935; y = -228; z = 164; }
VECTOR *MENU_CAMERA_EXIT_pos = { x = 184; y = 260; z = -92; }

ANGLE *MENU_CAMERA_NEW_GAME_ang = { pan = 329; tilt = 0; roll = 0; }
//ANGLE *MENU_CAMERA_NEW_GAME_ang = { pan = 280; tilt = -58; roll = 0; }
ANGLE *MENU_CAMERA_LOAD_GAME_ang = { pan = 256; tilt = -5; roll = 0; }
ANGLE *MENU_CAMERA_LAUNCH_ang = { pan = 25; tilt = -15; roll = 0; }
ANGLE *MENU_CAMERA_HELP_ang = { pan = 304; tilt = -9; roll = 0; }
ANGLE *MENU_CAMERA_TROPHIES_ang = { pan = 64; tilt = 1; roll = 0; }
//ANGLE *MENU_CAMERA_LAUNCH_GAME_ang = { pan = 332; tilt = -2; roll = 0; }
ANGLE *MENU_CAMERA_LAUNCH_GAME_ang = { pan = 304; tilt = -9; roll = 0; }
ANGLE *MENU_CAMERA_EXIT_ang = { pan = 319; tilt = -6; roll = 0; }

#define CINPUT_TAB 9
#define CINPUT_ENTER 13
#define CINPUT_ESC 27

#define WORLD_DYNAMIC 1
#define WORLD_STATIC 2

#define RESIZE_X 0
#define RESIZE_Y 1
#define RESIZE_XY 2

#define X 1
#define Y 2
#define Z 3

#define BORDER 10
#define DEFAULT_ALPHA 50

#define FOG_END_LIM 8000

#define FIXED_CULLING_DISTANCE 1500
#define FOG_CULLING_DISTANCE 200
#define FOG_END_CLIP 10000
#define FOG_START_CLIP 100

#define CREDITS_ROLL_MAXSTR 100

#define MINIMUM_RESOLUTION_X 1024
#define MINIMUM_RESOLUTION_Y 768

#define MINIMUM_SCALE_CONSTANT .5
#define SCALE_SPEED .002

#define DYNAMIC_LIGHT_DISCO_SPEED 0.1

#define MAX_PRIVATE_SKILLS 100
#define MAX_PUBLIC_SKILLS 30
#define MAX_PUBLIC_FLAGS 8

#define MAX_rEnts 1000
#define MAX_OBJECTS 10000
#define MAX_PARTICLES 40 // "real" particle objects ( differs from max_particles )
#define MAX_LIGHTS 200
#define MAX_SOUNDS 500
#define MAX_SPRITES 1000
#define MAX_TOTAL MAX_OBJECTS+MAX_PARTICLES+MAX_LIGHTS+MAX_SOUNDS+MAX_SPRITES

#define B_MULT 2			  //Brush Multiple Vertex
#define B_MULT_SMOOT 3	  //Brush Multiple Vertex with Smoot
#define DEF_UPPER	1		  //Deform terrain Height UPPER
#define DEF_LOWER 2		  //Deform terrain Height Down
#define TRUE 1	
#define FALSE 0

#define SCALE_MARKER .75
#define SCALE_MARKER_TERRAIN 0

#define _NODE_STATE skill27
#define _NODE_HEARTBEAT skill28
#define _BEING_MANIPULATED skill29

#define _HEALTH skill30
#define _WALK_SPEED skill31
#define _RUN_SPEED skill32
#define _PERFORM_ANIMATIONS skill33
#define _TEAM skill34
#define _FOLLOW_ANOTHER skill35

// Controls the clock.
long SecondsPassed = 0, MinutesPassed = 0, HoursPassed = 0, DaysPassed = 0, MonthsPassed = 0, SeasonsPassed = 0, YearsPassed = 0;
bool StopClock;

// Controls the music player.
int mpCount = 0, mpRandomize = 0, mpSongs, mpPauseMark; // Vars declared specifically for the music player.
var mpHandle;

// Controls the terrain editor
var total_vertices = 5; // will store the total number of vertices for the current terrain entity
var bSize = 800; // Deform max size
var tMaxHeight = 5000; //Terrain Max Height
var sizeh = 10;
var brush_speed = 5;
int bType = B_MULT; // I don't want to drop support for this, because it can come in handy when implementing 
int bHeight = DEF_UPPER;
int bHlimit = FALSE;

// Controls the statistic panel.
int CountObjects = 0, CountParticles = 0, CountLights = 0, CountSounds = 0, CountSprites = 0, CountTotal = 0;

int rEntCount = -1;

var guiViewPresetSpeed = 0.1;

var BBTranslucency;

bool ToggleSnow = false;
bool ToggleRain = false;

STRING *mouse_str = "mouse_pointer.png";
BMAP *mouse_painttex = "pen.png";

STRING *_mpCount = "#5";
STRING *_mpSongTemp = "#100";

SOUND *__beep = "./CookedSounds/beep.wav";
//SOUND *footstep = "./CookedSounds/tap.wav";
STRING *SE_MM_hover = "./CookedSounds/button-24_MMhover.wav"; // Actually they're sound files but under the STRING form.
STRING *SE_MM_click = "./CookedSounds/button-30_CMMclickon.wav";

// Background level
STRING *LEVEL_MENU = "./CookedWorlds/background.wmb";
STRING *CAMERA_MODEL = "real_cam.mdl";

STRING *VAREXPLORER_EXITSTR = "exit";
STRING *VAREXPLORER_REPORTSTR = "report";
STRING *VAREXPLORER_FACTORYSTR = "default";

STRING *FILE_SCREENSHOT = "craftbox";
STRING *FILE_CONFIG = "./Source/Config.cfg";
STRING *FILE_CREDITS_TEXT = "./Source/_credits.cbt";
STRING *FILE_LOG = "./CBox.html";

STRING *FILE_GAME_INTRO_VIDEO = "#300";
STRING *FILE_GAME_OUTRO_VIDEO = "#300";

STRING *GROUNDSTR = "#300"; // Store ground location.
STRING *SKYSTR = "#300"; // Store sky (cube) location.
STRING *TEMPSTR = "#300"; // Store object location
STRING *LOADGAMESTR = "#300";
STRING *mpSongTemp = "#400";

STRING *EXT_SCREENSHOT = "jpg"; // Change the extension here: jpg, dds (uncompressed), png, bmp
STRING *EXT_OBJECT = "mdl";
STRING *EXT_SOUND = "wav";
STRING *EXT_TERRAIN = "hmp";
STRING *EXT_SPRITE = "tga";
STRING *EXT_SAVEDGAMES = "s";
STRING *EXT_MUSIC = "*.ogg";
STRING *EXT_CBOIF = ".cboif";
STRING *EXT_GEO = "*.ctdd";

STRING *PATH_SOUNDS = "./CookedSounds/";
STRING *PATH_SOUNDS_ = "CookedSounds\\";
STRING *sndConnectorShared = "#400";

STRING *PATH_SPRITES = "./CookedObjects/Decals/";
STRING *PATH_TERRAINS = "./CookedObjects/Lands/";
STRING *PATH_OBJECTS_ANMS = "./CookedObjects/Animals/";
STRING *PATH_OBJECTS_ARCHS = "./CookedObjects/Architecture/";
STRING *PATH_OBJECTS_CHARS = "./CookedObjects/Characters/";
STRING *PATH_OBJECTS_ETC = "./CookedObjects/EverydayObjects/";
STRING *PATH_OBJECTS_FOOD = "./CookedObjects/Food/";
STRING *PATH_OBJECTS_MACHS = "./CookedObjects/Machines/";
STRING *PATH_OBJECTS_PLANTS = "./CookedObjects/Plants/";
STRING *PATH_OBJECTS_SYS = "./CookedObjects/";
STRING *PATH_OBJECTS_TPORTTS = "./CookedObjects/Transports/";

STRING *PATH_SKIES = "./Cooked2D/Skies/";
STRING *PATH_GROUNDS = "./CookedWorlds/CookedGrounds/";
STRING *PATH_SAVEDGAMES = "./CookedWorlds/";
STRING *PATH_MUSIC = "CookedSounds\\Music";

STRING *TERRAINDATA = "_geodata";
STRING *SEEDMASKDATA = "_seed_mask";
STRING *TERRAINSEEDBMAP = "#400";

int TEMP_OBJECT_TYPE;

STRING *PLAYTEST_LOADSCREENSTR = "#400"; // Something will modify this...and we got user-defined loadscreens.

TEXT *OptionsGraphicsTxt;
TEXT *OptionsSoundTxt;
TEXT *OptionsThemesTxt;
TEXT *OptionsMaintenanceTxt;
TEXT *ReleaseInfo = {
	
	strings(2);
	
	string(RELEASE_STR_VER,RELEASE_STR_INFO);
	
	font="Arial#20";
	
}

TEXT *MusicPlayerInfo, *MusicPlayerQuickInfo;

TEXT *StatsPanel = {
	
	layer = 15;
	
	strings(6);
	
	font = "Arial#20b";
	
}

TEXT *DialogueContainer = { strings(1000); /* stores 1000 lines for each dialogue */ }

TEXT *Dialogue = {
	
	strings(1);
	font = "Arial#16b";
	
}

TEXT *ClockText = {
	
	strings(1);
	font = "Arial#25b";
	
	pos_x = 10;
	pos_y = 10;
	
}

////////////////////////////////////////////////////////////
// System definitions for Mystymood.
////////////////////////////////////////////////////////////
/**
 * Sets the daytime to night
 */
void weather_night();

/**
 * Sets the daytime to day
 */
void weather_day();

/**
 * Sets the daytime to evening
 */
void weather_evening();

/**
 * Sets the daytime to morning
 */
void weather_morning();

/**
 * Change time of day dynamically
 */
void weather_daynight_dynamic();

/**
 * Sets a static time of day
 */
void weather_daynight_static();

/**
 * Let the sun shine
 */
void weather_sun();

/**
 * Sets it rain
 */
void weather_rain();

/**
 * Start rain with thunder
 */
void weather_thunder();

/**
 * Let it snow
 */
void weather_snow();

// ----------------------------------------------------------------------
// TWEAK HERE!
// ----------------------------------------------------------------------
int nDynamicDayNight						=	1;
var vSunAzimuth							=	190;	// Fixed position when no dynamic day night
var vSunElevation							=	20;	// Fixed position when no dynamic day night
var vDayTransitionTime					=	30;
var vNightTransitionTime				=	50;
int nAmbientSounds						=	1;
int nUnderwaterSounds					=	1;

int nRandomWeather						=	0;
int nRandomWeatherChangeFrequency	=	100;	// Higher value -> Longer states
int nRandomWeatherStateDuration		=	40;	// Higher values -> Lower change probability

int nWeatherState							=	0;		// 0 sun, 1 rain, 2 snow

int nWaterLevel							=	-10;		// z position of water

// Use to tweak frame rates
#define LAND_FOG_NEAR		200
#define LAND_FOG_FAR			4000

#define AQUA_FOG_NEAR		-300
#define AQUA_FOG_FAR			600

#define WEATHER_FOG_NEAR	100
#define WEATHER_FOG_FAR		1000

// Weather particle box around the camera
#define WEATHER_BOX_X		1000
#define WEATHER_BOX_Y		1000
#define WEATHER_BOX_Z		600

// Effect density
#define RAIN_DENSITY 10
#define SNOW_DENSITY 20

// ----------------------------------------------------------------------
// WEATHER
// ----------------------------------------------------------------------

BMAP* bmapWeatherParticle	= NULL;
BMAP* bmapRain					= NULL;
BMAP* bmapSnow					= NULL;
BMAP* bmapLightning			= NULL;
var vParticleVelocityX		=	0;
var vParticleVelocityY		=	0;
var vParticleVelocityZ		=	0;
var vParticleSize				=	0;
var vParticleAlpha			=	0;
var vParticleNumber			=	0;
VECTOR* vecRainDirection	= { x = 2; y = 1; z = 25; }
VECTOR* vecSnowDirection	= { x = 4; y = 1; z = 25; }
var vRainRandomMove			= 1;
var vSnowRandomMove			= 8;
var vDisableThunder			= 0;
int nLightning					= 1;

// Skills and flags for triggers
#define TRIGGER_RAIN					FLAG1
#define TRIGGER_SNOW					FLAG2
#define TRIGGER_DISABLE_THUNDER	FLAG3
#define T_FOG_CHANGE					FLAG4

#define TRIGGER_RANGE				skill1
#define TRIGGER_RAIN_WIND_X		skill2
#define TRIGGER_RAIN_WIND_Y		skill3
#define TRIGGER_RAIN_FALLSPEED	skill4
#define TRIGGER_SNOW_WIND_X		skill5
#define TRIGGER_SNOW_WIND_Y		skill6
#define TRIGGER_SNOW_FALL_SPEED	skill7
#define T_RAIN_RANDOM_MOVE			skill8
#define T_SNOW_RANDOM_MOVE			skill9
#define T_FOG_NEAR					skill10
#define T_FOG_FAR						skill11
#define T_FOG_RED						skill12
#define T_FOG_GREEN					skill13
#define T_FOG_BLUE					skill14
#define TRIGGER_ID					skill100

int nTriggerCount		= 0;
var nActiveTriggerId	= -1;
var vWeatherFader		= 1;

VECTOR vecTempColor;
var vFogDistanceNearTemp;
var vFogDistanceFarTemp;

var vLightningTemp;
var vLightningSegmentLength;
VECTOR vecLightningSegmentStart;
VECTOR vecLightningSegmentEnd;
var vLightningStrokeLength;
VECTOR vecLightningStrokeStart;
VECTOR vecLightningStrokeEnd;

VECTOR vecParticleSeedBox;
VECTOR vecCurrentColor;

int nIsUnderWater;
int nLightningIsOn;

SOUND* sndRain				= NULL;
SOUND* sndWind				= NULL;
SOUND* sndDay				= NULL;
SOUND* sndNight			= NULL;
SOUND* sndThunder1		= NULL;
SOUND* sndThunder2		= NULL;
SOUND* sndThunder3		= NULL;
SOUND* sndThunder4		= NULL;
SOUND* sndThunder5		= NULL;
SOUND* sndUnderwater		= NULL;

ENTITY* entHorizon		= NULL;
ENTITY* entCloud1 		= NULL;
ENTITY* entCloud2			= NULL;
ENTITY* entCloud3			= NULL;
ENTITY* entSkyDay			= NULL;
ENTITY* entSkySun			= NULL;
ENTITY* entSkySunCorona	= NULL;
ENTITY* entSkySunshine	= NULL;
ENTITY* entSkyNight		= NULL;
ENTITY* entSkyMoon		= NULL;


#define RAIN_ONLY 0
#define SNOW_ONLY 1
#define RAIN_SNOW 2
#define NO_RAIN_SNOW 3
var _fog_color, _sun_light;
var _d3d_fogcolor1_red, _d3d_fogcolor1_green, _d3d_fogcolor1_blue, _camera_fog_end;

/*
#define snd_vol_rain_max 				50
#define snd_vol_wind_max 				40
#define snd_vol_wind_max_when_rainy 10
#define snd_vol_bg_day_max 80
#define snd_vol_bg_night_max 80

//day sky
#define sky_add_red 		  255//color tint of the day_sky.
#define sky_add_green 	  255
#define sky_add_blue 	  255
#define sky_alpha 		 	10//0-100, decrease this to get more fogcolor1 tint

var _fog_color = 0, _sun_light = 100, _d3d_fogcolor1_red = 128, _d3d_fogcolor1_blue = 128, _d3d_fogcolor1_green = 128, _camera_fog_end = 6000; // Default values

//night sky
var night_sky_scale_x = .5;//affects size of the stars at night
var night_sky_scale_y = .5;
var night_sky_speed_x = 1;//movement speed of the stars
var night_sky_speed_y = 1;
#define night_sky_alpha		 0

//cloud layer 1
#define cloud1_speed_x 	  0.5
#define cloud1_speed_y 	  	 3
#define cloud1_scale_x 	  1.5
#define cloud1_scale_y 	  1.5
#define cloud1_alpha	 	80//alpha changes can cause various sun/clouds effects

//cloud layer 2
#define cloud2_speed_x	  	 1
#define cloud2_speed_y 	  	 5
#define cloud2_scale_x	  2.5
#define cloud2_scale_y 	  2.5
#define cloud2_alpha 	 	60//alpha changes can cause various sun/clouds effects

//bad weather clouds
#define cloud3_speed_x 	  	 1
#define cloud3_speed_y 	  	 5
#define cloud3_scale_x 	  	 2
#define cloud3_scale_y 	    2
#define cloud3_alpha 	 	 0//0 = starts at nice weather!

var sun_grow_z	=	 1500;//z-height of sun-grow/sun-shrink, adjust according to your horizon view

//when your sun elevation is low, big scales (scale_x, scale_y) can look bad (sun-sprites touches the terrain!)
#define sun_scale_x 		    3//7;////size of the sun, changes all other sun entitys (sun_corona, sun_shine) relative to it
#define sun_scale_y 		    3//7;//

#define sun_alpha 		 	65//alpha changes can cause various sun/clouds effects
#define sun_corona_alpha 	40//0;//
#define sun_shine_alpha  	50//0;//

var moon_scale_fac = 1.5;
#define moon_alpha 		  100

#define sun_dist_minus	  1000//evtl. raise this value when you see the sun flickering or disappear, default is 10 (10 quant before land_fog_far/clip_far)

#define land_fog_near	 200//fog above water
#define land_fog_far	  	 4000//lower values increase the framerate

#define weather_fog_near	  100//bad weather fog
#define weather_fog_far	  	  1000

//(screen center where pivot_dist = 0) and the sun (pivot_dist = 1).
#define pivot_dist skill99
*/

////////////////////////////////////////////////////////////

#define move 1
#define rotate 2
#define scale 3

// Re-define (a few) skills
#define ObjectType skill1
#define ObjectDynamic skill2
#define ObjectPhysics skill3
#define ParticleID skill4 // Only particle effects use this.
#define LightMode skill5
#define FlickSpeed skill6
//#define ProjectionID skill9

// Object type
#define Object 1
#define ObjectAnimal 2
#define ObjectArchitecture 3
#define ObjectCharacter 4
#define ObjectEveryday 5
#define ObjectFood 6
#define ObjectMachine 7
#define ObjectPlant 8
#define ObjectTransport 9
#define ObjectNode 10

#define Particle 11
#define Light 12
#define Sound 13
#define Terrain 14
#define Sprite 15
#define Neutral 16
#define Player 17 // Player != player

#define DynamicContent 18 // Entities which are marked with this are deleted when playtesting mode has finished.
#define SeedEnt 19 // Entities crated by the ent_seed function.

#define Trigger_PlayerStandard 20
#define Trigger_PlayerBike 21
#define Trigger_PlayerBulldozer 22
#define Trigger_PlayerHelicopter 23
#define Trigger_ForceFieldHurt 24
#define Trigger_ForceFieldKillInstantly 25
#define Trigger_PlayVideoFile 26
#define Trigger_ChangeLevel 27
#define Trigger_ChangeSkybox 28
#define Trigger_FogAdjustment 29
#define Trigger_MusicPlayerController 30
#define Trigger_TimeFactorController 31
#define Trigger_TerrainModifyvertex 32
#define Trigger_SpawnEntity 33
#define Trigger_SpawnConversation 34
#define Trigger_SpawnMessage 35
#define Trigger_SpawnNotification 36
#define Trigger_WinZone 37
#define Trigger_FailZone 38
#define Trigger_ModifyCameraArc 39
#define Trigger_SpawnParticle 40

// Defines for materials
#define select_mat_null 15

#define select_custom_mat1 11
#define select_custom_mat2 12
#define select_custom_mat3 13
#define select_custom_mat4 14

// Defines for lights
#define Flick 1
#define Disco 2

// Defines for particles
#define part_spiral 1
#define part_colorfulspark 2
#define part_spacehole 3
#define part_fountain2 4
#define part_fountain1 5
#define part_fire2 6
#define part_fire1 7
#define part_doublehelix 8
#define part_composition 9

//////////////////////////////
// Strings and texts will be declared here.
//////////////////////////////

STRING *current_folder = "a",
*file_selected = "a";

TEXT *files_list_SKYSTR = {
	
	layer = 15;
	
	strings(4);
	
	font = "Arial#27b";
	
}

TEXT *files_list_GROUNDSTR =  {
	
	layer = 15;
	
	strings(4);
	
	font = "Arial#27b";
	
}

TEXT *files_list_LOADGAMESTR = {
	
	layer = 15;
	
	strings(8);
	
	font = "Arial#27b";
	
}

TEXT *files_list_TEMPSTR = {
	
	layer = 15;
	
	strings(20);
	
	font = "Arial#27b";
	
	red = 0;
	green = 255;
	blue = 0;
	
}

TEXT* ConsoleText = { font = "Arial#15b"; string("

	< craftbox variable explorer >

","#255","#255","#255","#255","#255"); layer = 999; }

TEXT *files_list_SKYSTR_Pool = { strings( 100 ); }
TEXT *files_list_GROUNDSTR_Pool = { strings( 100 ); }
TEXT *files_list_LOADGAMESTR_Pool = { strings( 100 ); }
TEXT *files_list_TEMPSTR_Pool = { strings( 500 ); } 

TEXT *mpPool = {
	
	//	pos_x = 10;
	//	pos_y = 40;
	
	strings( 100 );
	
	//	font = "Arial#25b";
	
	//	flags = SHOW;
	
}

////////////////////////////////////////////////////////////
// Variables/Booleans will be declared here.
////////////////////////////////////////////////////////////

var WorldType;
var InMenu_NewGame, InMenu_Options;

int SKYSTR_Scaler = 0, GROUNDSTR_Scaler = 0, LOADGAMESTR_Scaler = 0, TEMPSTR_Scaler = 0;

int mat_type, manip_type;
int files_found, list_start;
int shot = 0;

var files_already;

var olrange; // Old light range
var old_ambient;

var v_alpha, v_ambient,

/*

v_ambient_r, v_ambient_g, v_ambient_b,
v_diffuse_r, v_diffuse_g, v_diffuse_b,
v_specular_r, v_specular_g, v_specular_b,
v_emissive_r, v_emissive_g, v_emissive_b,
v_power, 
v_alpha_m, // Alpha for materials

*/

v_lred, v_lgreen, v_lblue, v_lrange,

v_fogr, v_fogg, v_fogb, v_fogdensity,

v_objectz;

COLOR *temp_light = {
	
	red = 0;
	green = 0;
	blue = 0;
	
}

var ParticleIDNumber;
var _ObjectType;

bool from_test_play = 0;

////////////////////////////////////////////////////////////
// Variables and booleans related to Mystymood.
////////////////////////////////////////////////////////////
bool mystymoodActive = false;
var
_load_lensflare = 1,
_use_moon = 1,
_use_sun = 1,
_use_nightstars = 1,
_weather_mode = 1; // RAIN_ONLY, SNOW_ONLY, RAIN_SNOW, NO_RAIN_SNOW
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Panels will be declared here.
////////////////////////////////////////////////////////////
PANEL *InDev,
*buttonlst,
*last_pan,
*panMain_Top,
*panMain_Bottom,
*panMain_Play,
*buttonlst_submenu_terrain,
*panProp,
*panSnd,
*panParticle,
*panLight,
*panRotateHelp,
*panScaleHelp,
*panScreenshot,
*panCAMRecorder,
*panCAMRecorderREC,
*panCAMRecorder_digits,
*empty,
*InsertObject,
*InsertObject_Inputter,
*InputBox_GROUNDSTR,
*InputBox_SKYSTR,
*InputBox_LOADGAMESTR,
*IO_ObjectTab,
*IO_SoundTab,
*IO_ParticleTab,
*IO_LightTab,
*IO_SpriteTab,
*IO_TerrainTab,
*LightPresets,
*InsertParticle,
*InsertSystemObjects,
*Options_Graphics,
*Options_Sound,
*Options_Themes,
*Options_Maintenance,
*LoadGame,
*ZTool,
*MainMenu_Bar,
*MainMenu_Item1,
*MainMenu_Item2,
*MainMenu_Item3,
*MainMenu_Item4,
*MainMenu_Item5,
*MainMenu_Item6,
*NewGame_ScreenLeft,
*NewGame_ScreenRight,
*NewGame_Screen1,
*NewGame_ScreenDyn_Step1,
*NewGame_ScreenStatic_Step1,
*NewGame_Screen3,
*NewGame_PreviewButton,
*CreateWorld,
*CreateWorldCoffee,
*FPCrosshair,
*MusicPlayer,
*MusicPlayerQuick,
*Stats,
*Blackboard,
*Playtest_Loadscreen, // Global
*pLoadBar,
*TerrainToolbar,
*BackMenu_Background,
*BackMenu_Items,
*QuitDialog,
*RightClickMenu,
*PreviewBox,
*SplashScreen,
*LoadKernelScreen;

////////////////////////////////////////////////////////////
// Entities will be declared here.
////////////////////////////////////////////////////////////
ENTITY *select, // points to the being selected entity
*marker, // points to the marker
*cam, // points to the actual camera (not CameraLoc - it's the camera creator)
*flashlight, // points to the flashlight (1st/3rd person mode)
*skycube, // points to the skycube in dynamic menu background
*TerrainEnt, // points to the deformed terrain
*CameraLoc, // points to the camera creator
*GlassLoc, // points to the glass walls
*WaterPlaneLoc, // points to the water plane
*Gun; // 1st person gun

ENTITY *sky_horizon,
*sky_cloud1,
*sky_cloud2,
*sky_cloud3,
*sky_day,
*sky_sun,
*sky_suncorona,
*sky_sunshine,
*sky_night,
*sky_moon;

/*

*flare1_ent,
*flare2_ent,
*flare4_ent,
*flare5_ent,
*flare6_ent,
*flare7_ent,
*flare8_ent,
*flare9_ent,
*flare10_ent,
*flare11_ent,
*flare12_ent,
*flare13_ent,
*flare14_ent,
*flare15_ent,
*flare16_ent,
*flare17_ent,
*flare18_ent,
*flare19_ent,
*flare20_ent;

*/

////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Vectors will be declared here.
////////////////////////////////////////////////////////////
VECTOR cpos1,cpos2,temp_pos;
VECTOR temp2, ctemp;

// Vectors for dragging entities & camera movement
VECTOR v1, v2;
VECTOR *camera_force = { z = 0; }

/*** Vectors & angles for particle effects ***/
VECTOR parted_temp_vec, parted_temp2_vec;

ANGLE *parted_temp_ang = {
	
	pan = 0;
	tilt = 0;
	roll = 0;
	
}

////////////////////////////////////////////////////////////
// Fonts and texts' declarations
////////////////////////////////////////////////////////////
FONT *cbDefaultFont = "Arial#27b";

////////////////////////////////////////////////////////////
// Sounds will be declared here.
////////////////////////////////////////////////////////////
SOUND *snowstorm_ambient = "snowstorm.ogg";
SOUND *rain_wav = "rain.wav";

////////////////////////////////////////////////////////////
// Bitmap declarations
////////////////////////////////////////////////////////////
BMAP *flag_BIRGHT = "flag_BIRGHT.bmp";
BMAP *flag_BIRGHT_on = "flag_BIRGHT_on.bmp";

BMAP *flag_INVISIBLE = "flag_INVISIBLE.bmp";
BMAP *flag_INVISIBLE_on = "flag_INVISIBLE_on.bmp";

BMAP *flag_NOFOG = "flag_NOFOG.bmp";
BMAP *flag_NOFOG_on = "flag_NOFOG_on.bmp";

BMAP *flag_OVERLAY = "flag_OVERLAY.bmp";
BMAP *flag_OVERLAY_on = "flag_OVERLAY_on.bmp";

BMAP *flag_PASSABLE = "flag_PASSABLE.bmp";
BMAP *flag_PASSABLE_on = "flag_PASSABLE_on.bmp";

BMAP *flag_POLYGON = "flag_POLYGON.bmp";
BMAP *flag_POLYGON_on = "flag_POLYGON_on.bmp";

BMAP *flag_SHADOW = "flag_SHADOW.bmp";
BMAP *flag_SHADOW_on = "flag_SHADOW_on.bmp";

BMAP *flag_TRANSLUCENT = "flag_TRANSLUCENT.bmp";
BMAP *flag_TRANSLUCENT_on = "flag_TRANSLUCENT_on.bmp";

BMAP *flag_MOVE = "flag_MOVE.png";
BMAP *flag_MOVE_on = "flag_MOVE_on.png";

BMAP *flag_ROTATE = "flag_ROTATE.png";
BMAP *flag_ROTATE_on = "flag_ROTATE_on.png";

BMAP *flag_SCALE = "flag_SCALE.png";
BMAP *flag_SCALE_on = "flag_SCALE_on.png";

BMAP *flag_DISCO = "flag_DISCO.bmp";
BMAP *flag_DISCO_on = "flag_DISCO_on.bmp";

BMAP *flag_FLICK = "flag_FLICK.bmp";
BMAP *flag_FLICK_on = "flag_FLICK_on.bmp";

BMAP *slider = "slider.bmp";

BMAP *panProp1_IMG = "panProp_1.bmp";
BMAP *panProp2_IMG = "panProp_2.bmp";

/*** For particle effects ***/
BMAP *point_blue_map = "point_blue.tga";
BMAP *sparkle1_map = "sparkle1.tga";
BMAP *fire3_map = "fire3.tga";
BMAP *fire1_map = "fire1.tga";
BMAP *blitz1_map = "blitz1.tga";
BMAP *star1_map = "star1.tga";
BMAP* drop1_map = "rain.tga";

////////////////////////////////////////////////////////////
// Function prototypes declarations
////////////////////////////////////////////////////////////

void path_make_absolute(STRING *path) // Makes a path absolute.
{
	static STRING *tmp = "#1024";
	str_cpy(tmp, work_dir);
	str_cat(tmp, "\\");
	str_cat(tmp, path);
	str_cpy(path, tmp);
}

/************************************************************
a vector() alternative
************************************************************/
int lvectorLastFrame = 0;
int lvectorStoragePointer = 0;
int lvectorStorageSize = 0;
VECTOR *lvectorStorage = NULL;

/**
* Returns a temporary vector that is valid at least one frame.
* param	x	X component
* param	y	Y component
* param	z	Z component
*/
VECTOR *lvector(var x, var y, var z);

/**
* Returns the current memory used by lvector.
*/
int lvector_usage();

/************************************************************
Generic linked list
************************************************************/
/**
* ListData is used instead of void to give a clear difference between a normal pointer and a pointer used in lists.
*/
typedef void ListData;

/**
* A list item. You can use a list item to iterate through a list.
*/
typedef struct ListItem
{
	//private:
	struct ListItem *previous;
	struct ListItem *next;

	//public:	
	/**
	* The data stored in this list item.
	*/
	ListData *data;
} ListItem;

/**
* A generic list which allows you handling a collection of structs.
* The list doesn't have a fixed size, so you can just add or remove items.
*/
typedef struct List
{
	//private:
	int count;
	//public:
	/**
	* The first item of the list.
	*/
	ListItem *first;
	
	/**
	* The last item of the list.
	*/
	ListItem *last;
} List;

/**
* An iterator for a list. You need the iterator to go through all items in a list.
*/
typedef struct ListIterator
{
	//private:
	List *list;
	ListItem *current;
	int valid;
	//public:
	int hasNext;
} ListIterator;

/**
* Creates a new list.
* return				A new list.
*/
List *list_create();

/**
* Deletes a list.
* param	list		The list to delete.
*/
void list_delete(List *list);

/**
* Clones a list with all list items.
* param	list		The list to clone.
* return				A new list with all items which were in the list to clone.
*/
List *list_clone(List *list);

/**
* Adds a new item to the last position of a list
* param	list		The list where the item should be added.
* param	item		The item which should be added to the list.
*/
void list_add(List *list, ListData *item);

/**
* Adds a range of items to the list.
* param	list		The list where the items should be added.
* param	array		The array where the items should be copied from.
* param	count		The number of items which should be copied.
*/
void list_add_range(List *list, ListData **array, int count);

/**
* Adds a new item in the first position of a list.
* param	list		The list where the item should be added.
* param	item		The item which should be added to the list.
*/
void list_add_first ( List *list, ListData *item );

/**
* Adds a new item sorted by a comparision function
* param	list			The list where the item should be added.
* param	item			The item which should be added to the list.
* param	compare		A pointer to a comparision function. The function needs this signature: int compare(ListData *left, ListData *right) and returns 1 if left>right, 0 if left=right and -1 if left<right.
*/
void list_add_sorted ( List *list, ListData *item, void *compare );

/**
* Removes the item from the list.
* param	list		The list where the item should be removed.
* param	item		The item to remove from the list.
*/
void list_remove(List *list, ListData *item);

/**
* Removes all matching item sfrom the list.
* param	list		The list where the items should be removed.
* param	item		The item to remove from the list.
*/
void list_remove_all(List *list, ListData *item);

/**
* Removes the item at a given index from the list.
* param	list		The list where the item should be removed.
* param	index		The index of the item to remove.
*/
void list_remove_at(List *list, int index);

/**
* Checks if a list contains an item.
* param	list		The list which should be checked.
* param	item		The item which should be searched.
* return				0 if the item is not found, else != 0.
*/
int list_contains(List *list, ListData *item);


/**
* Returns the item stored at a given index.
* param	list		The list where the item is.
* param	index		The index of the item.
* return				The item or NULL if index out of range.
*/
ListData *list_item_at(List *list, int index);

/**
* Removes all items from a list.
* param	list		The list which should be cleared.
*/
void list_clear(List *list);

/**
* Clears the listitems and the listitems data of a list
* param	list		The list where the item should be added.
* param	remove_function		A pointer to a remove function. The function needs this signature: void remove_function ( ListData *item )
*/
void list_clear_content ( List *list, void *remove_function );


/**
* Sorts a list.
* param	list		The list which should be sorted.
* param	compare		A pointer to a comparision function. The function needs this signature: int compare(ListData *left, ListData *right) and returns 1 if left>right, 0 if left=right and -1 if left<right.
*/
void list_sort(List *list, void *compare);

/**
* Reverses a list (first item will be last, last will be first, ...).
* param	list		The list to be reversed.
*/
void list_reverse(List *list);

/**
* Gets the count of items in a list.
* param	list		The list to get the count from.
* return				The amount of items in the list.
*/
int list_get_count(List *list);

/**
* Copies a list to an array of items.
* param	list		The list to be reversed.
* param	array		The array where the items should be copied to.
* param	arrayLength	The max. number of items in the array.
* return				The amount of items copied.
*/
int list_copy_to(List *list, ListData **array, int arrayLength);

/**
* Begins a list iteration.
* param	list		The list to iterate through
* return				A new iterator for the given list.
*/
ListIterator *list_begin_iterate(List *list);

/**
* Gets the next value in a list iteration.
* param	iterator	The iterator to be used.
* return				The next value in the iteration.
*/
ListData *list_iterate(ListIterator *iterator);

/**
* Ends an iteration and frees the iterator.
* param	iterator	The iteration to be freed.
*/
void list_end_iterate(ListIterator *iterator);

/************************************************************
Generic state machines manager
************************************************************/
/*
 * A state machine is a code structure that changes the execution flow in reference to the 
 * state of a variable. A function pointer based state machine is the same concept but it 
 * references a function to be executed next frame instead of checking a variable value.
 *
 * This module offers the possibility of running state machines for any kind of data, even
 * without any data. It is conceived to ensure that the actual state of every object is 
 * executed before been changed by another machine. This characteristic avoids the inherent advantage of the
 * execution order. It has also the minor benefit of executing all the machines from a single
 * array pass inside a single while loop. The state machines will be executed in the same order
 * they were created
 *
 * # How to use these state machine
 * 
 * - Include TUST library into your project.
 * - Start the state machines manager.
 *   ~~~
 *   // Funtion to be executed by a state machine
 *   function myState1 ( STMACHINE *stm ) 
 *   {
 *      // Retrieve the object of the machine
 *      MyStruct *myStruct = stm_me ( stm ); 
 *      you = stm_by_index ( stm ); // Retrieve an object by its index
 *      stm_set_state ( stm, stEnt2, 2 );
 *      my->clock += 20+random(30);
 *   }
 *   ...
 *   stm_open ();
 *   ...
 *   ~~~
*/

/**
*     Check for NULL pointers 
*/
// In release mode, these #defines will be disabled
//#define STMC_SAFE_MODE

/**
*     Try to describe the errors ;) 
*/
//#define STMC_ERRORS

/**
*     Show global state machine collections count
*/
#define STMC_COUNT

/**
*     State machines count into each memory allocation step 
*/
#define STMC_MEMSTEP					4

/* ----------------------------------------------------------------------------------------- */
/* STMACHINE DATA STRUCT
/* ----------------------------------------------------------------------------------------- */
typedef struct STMACHINE
{
	var stateNext;
	void *fncNext;
	void *ptrMe;
	void remover ( void *ptr );
	int *index;
	var flags;
	var state;
	void fncPtr ( struct STMACHINE *machine );
} STMACHINE;

/* ----------------------------------------------------------------------------------------- */
/* GENERAL FUNCTIONS
/* ----------------------------------------------------------------------------------------- */

/**
*     Start the state machines automation 
*/
void stm_open ();

/**
*     Finish the state machines automation 
*/
void stm_close ();

/**
*     Add a new state machine
* param    obj        A pointer to an object. It can be NULL too.
* param    remover    A function that removes the object, 
*                      If NULL the object will not be removed when the state machine is removed
* param    fnc        The state machine starting function. It can't be NULL!
* param    state      a number to identify the starting function. Just a helper. Not used.
* param    index      a pointer to an integer that will be filled 
*	                     with the actual index in the global state machines array.
*	                     Since the state machines memory location is dynamic,
*	                     their index into the array and memory address changes with the flow
*                      so this integer is used as a secure and fast reference
*                      to the new state machine.
* returns             A pointer to the object.
*/
void *stm_add ( void *obj, void *remover, void *fnc, var state, int *index );

/* ----------------------------------------------------------------------------------------- */
/* GENERAL FUNCTION HELPER MACROS
/* ----------------------------------------------------------------------------------------- */

/**
*     Create an integer variable and cast its pointer to another type
*
* Use it when you want to use an entity or panel (etc) skill as state machine index allocator
*
* param    i          Fixed variable (var) to use as pointer to an integer			
*/
#define stm_create_index(i)		i=(int*)sys_malloc(sizeof(int))

/**
*     Delete an integer variable created with stm_create_index
*
* It has to be called after using stm_create_index
*
* param    i          Fixed variable (var) used as pointer to an integer			
*/
#define stm_delete_index(i)		sys_free(i)

/**
*     The pointer saved in the variable used as a pointer to an integer
*
* Use it into last parameter of stm_add function when stm_create_index is used
*
* param    i          Fixed variable (var) used as pointer to an integer			
*/
#define stm_index_ptr(i)			(int*)i

/* ----------------------------------------------------------------------------------------- */
/* INSIDE MACHINE FUNCTIONS
/* ----------------------------------------------------------------------------------------- */

/**
*     Change a state of a machine
* param    stm        A pointer to a state machine
* param    fnc        Function to execute in the new state
* param    state      A number to identify the new state
*/
void stm_set_state ( STMACHINE *stm, void *fnc, var state );

/**
*     Change the object of a machine
* param    stm        A pointer to a state machine
* param    obj        A pointer to an object
* param    remover    A function that deletes the object
*/
void stm_set_me ( STMACHINE *stm, void *obj, void *remover );

/**
*     Stop all the state machines that point to a certain object
* param    obj        A pointer to an object
*/
void stm_stop_ptr ( void *obj );

/* ----------------------------------------------------------------------------------------- */
/* INSIDE MACHINE HELPER MACROS
/* ----------------------------------------------------------------------------------------- */

/**
*     A state identify number of a state machine
* param    stmt	      A pointer to a state machine			
*/
#define stm_state(stmt)				stmt->state

/**
*     The pointer to the object of a state machine 
* param    stmt       A pointer to a state machine			
*/
#define stm_me(stmt)					stmt->ptrMe

/**
*     Stop a state machine in the next frame 
* param    stmt       A pointer to a state machine			
*/
#define stm_stop(stmt)				stm_set_state(stmt,stm_stop_machine,NULL)

/**
*     The content of an integer pointed by a pointer casted into another type variable
*
* Use it when you used an entity or panel (etc) skill as state machine index allocator
*
* param    i          Fixed variable (var) to be casted to an integer pointer			
*/
#define stm_index(i)					*((int*)i)

/**
*     The pointer to the nth state machine
* param    i          Index into the state machines array			
*/
#define stm_by_index(i)				(gblMachines->stmFirst+i)

/************************************************************
Node mesh pathfinding
************************************************************/
typedef struct Node
{
	var x;
	var y;
	var z;
	
	int index;
	var weight;
	int includer;
	int *linked;
	int count;
	int capacity;
	struct Node *next;
} Node;

/**
* struct   NodeMesh
* brief    Generic NodeMesh struct
*/
typedef struct NodeMesh
{
	Node *nodes;
	int count;
	int capacity;
} NodeMesh;

/**
* brief    Route is used instead of List to give a clear difference between a normal list and a route of nodes.
*/
typedef List Route;

/**
* brief    A pointer to the nodemesh constructor collision entity
*/
ENTITY *nodemesh_collider = NULL;

/**
* brief    Creates a new nodemesh.
* return   A new nodemesh.
*/
NodeMesh *nodemesh_create ();

/**
* brief Removes a nodemesh.
* param    nodemesh      The nodemesh to delete.
*/
void nodemesh_remove ( NodeMesh *nodemesh );

/**
* brief    Adds a node to the nodemesh and builds it neighborhood with a c_trace.
* param    nodemesh      The nodemesh.
* param    pos           The position of the node to be added.
* return   The node index in the nodemesh list.
*/
int nodemesh_add ( NodeMesh *nodemesh, VECTOR *pos );

/**
* brief    Looks for the nearest node to a certain position.
* param    nodemesh      The nodemesh.
* param    pos           The position .
* return   The index of the node in the nodemesh list.
*/
int nodemesh_nearest ( NodeMesh *nodemesh, VECTOR *pos );

/**
* brief    Checks the visibilty between a node and all the other nodes inside a nodemesh.
*           Connects them if visible
* param    nodemesh      The nodemesh.
* param    nodeindex     The index of the node.
*/
void nodemesh_ctrace_node ( NodeMesh *nodemesh, int nodeindex );

/**
* brief    Looks for a route between two nodes.
* param    nodemesh      The nodemesh.
* param    indexFrom     The index of the starting node
* param    indexTo       The index of the ending node
* return   A new route between nodes. NULL in the case there is no route.
*/
Route *nodemesh_find_route ( NodeMesh *nodemesh, int indexFrom, int indexTo );

/**
* brief    Deletes a route.
* param    route         The route to delete.
*/
void route_delete ( Route *route );

void nodes_connect ( Node *nodeFrom, Node *nodeTo );
int nodes_trace ( Node *nodeFrom, Node *nodeTo, var mode, ENTITY *collider );

/************************************************************
TUST Headers
************************************************************/

// This macro maps a varible from type a into type b without changing the bits.
#define type_convert(variable, T) (*((T*)(&variable)))

/*
 * Move block of memory.
 *
 * Copies the values of num bytes from the location pointed by source to the memory block pointed by destination. Copying takes place as if an intermediate buffer were used, allowing the destination and source to overlap.
 * The underlying type of the objects pointed by both the source and destination pointers are irrelevant for this function; The result is a binary copy of the data.
 * The function does not check for any terminating null character in source - it always copies exactly num bytes.
 * To avoid overflows, the size of the arrays pointed by both the destination and source parameters, shall be at least num bytes.
 * 
 * destination		Pointer to the destination array where the content is to be copied, type-casted to a pointer of type void*.
 * source			Pointer to the source of data to be copied, type-casted to a pointer of type void*.
 * num				Number of bytes to copy.
 * destination is returned.
 * Copied from http://www.cplusplus.com/reference/cstring/memmove/
*/
void *memmove(BYTE *destination, BYTE *source, unsigned int num);

// Sets all values of an angle between 0 and 360
void ang_normalize(ANGLE* _ang);

// Calculates a vertex position of an entity in world space.
VECTOR* vec_for_ent_ext(VECTOR* _target, ENTITY* _ent, int _vertexNumber);

// Writes a string at the given XY screen position in the current frame, using a Gamestudio FONT.
void draw_font(STRING* text, var x, var y, COLOR* color, FONT *font, int flags, var alpha);

/************************************************************
Math
************************************************************/
long sresult = 0;
static double U[50];
int vec_to_bezierBufferSize = 0;
VECTOR *vec_to_bezierBuffer = NULL;

long GCD(long, long);

VECTOR *vec_form(VECTOR *, VECTOR *);
VECTOR *_vec_add(VECTOR *, VECTOR *);
VECTOR *_vec_scale(VECTOR *, float);
VECTOR *_vec_sub(VECTOR *, VECTOR *);
VECTOR *vec_center(VECTOR *, VECTOR *);
VECTOR *vec_centroid(VECTOR *, VECTOR *, VECTOR *);
VECTOR *_vec_cross(VECTOR *, VECTOR *, VECTOR *);
VECTOR *vec_simplify(VECTOR *);

int vec_same_plane(VECTOR *, VECTOR *, VECTOR *, VECTOR *);
float _vec_length(VECTOR *);
float _vec_dot(VECTOR *, VECTOR *);
float vec_ang(VECTOR *, VECTOR *);

/************************************************************
The following functions are from math.h from the TUST library.
************************************************************/
var ang_lerp_single(var a1, var a2, var factor); // Interpolates a single angle.
ANGLE* ang_lerp(ANGLE* a, ANGLE* a1, ANGLE* a2, var f); // Interpolates an euler angle.
void vec_rotateXY ( VECTOR *vec, var angle ); // Rotates a vector about an orthogonal axis
void vec_rotateXZ ( VECTOR *vec, var angle ); // Rotates a vector about an orthogonal axis.
void vec_rotateYZ ( VECTOR *vec, var angle ); // Rotates a vector about an orthogonal axis.
var point_to_line2D_dist ( var px, var py, var l1x, var l1y, var l2x, var l2y ); // Gives the distance from a point to a line described by two other points
var point_to_line2D_escalar ( var px, var py, var l1x, var l1y, var l2x, var l2y ); // Gives the escalar of the orthogonal projection of a point over a vector described by two other points
List* calculate_spline(List* _points,  int _detail); // Calculates a spline
VECTOR* math_get_spline(VECTOR* points, int pointcount, float pos); // Calculates a spline
VECTOR *vec_to_bezier(VECTOR *pos, VECTOR *points, int count, float p); // Calculates a position on a bezier courve
VECTOR *vec_to_catmull(VECTOR *pos, VECTOR *v0, VECTOR *v1, VECTOR *v2, VECTOR *v3, float s); // Calculates a position on a catmull courve
int float_cmp(float _f1, float _f2); // Compares 2 float values with a precision of %.2f
void mat_eye ( float *_matrix, VECTOR *_vecPos, VECTOR *_vecDir ); // Computes the world to custom coordinates tranformation matrix (matView)

/************************************************************
craftbox's implementations of TUST math functions, marked with prefix c_function name
************************************************************/


/************************************************************
INI functions
************************************************************/
char iniBuffer[2048];

/**
 * Writes a string into an ini file.
 * param	filename	The absolute path to the filename of the ini file.
 * param	section		The section to write into.
 * param	entry		The key of the section entry to write.
 * param	value		The value which will be written into the key entry.
 */
void ini_write(STRING *filename, STRING *section, STRING *entry, STRING *value);

/**
 * Writes an integer into an ini file.
 * param	filename	The absolute path to the filename of the ini file.
 * param	section		The section to write into.
 * param	entry		The key of the section entry to write.
 * param	value		The value which will be written into the key entry.
 */
void ini_write_int(STRING *filename, STRING *section, STRING *entry, int value);

/**
 * Writes a var into an ini file.
 * param	filename	The absolute path to the filename of the ini file.
 * param	section		The section to write into.
 * param	entry		The key of the section entry to write.
 * param	value		The value which will be written into the key entry.
 */
void ini_write_var(STRING *filename, STRING *section, STRING *entry, var value);

/**
 * Writes a float into an ini file.
 * param	filename	The absolute path to the filename of the ini file.
 * param	section		The section to write into.
 * param	entry		The key of the section entry to write.
 * param	value		The value which will be written into the key entry.
 */
void ini_write_float(STRING *filename, STRING *section, STRING *entry, float value);

/**
 * Reads all sections from an ini file into a TEXT object.
 * param	txt			The TEXT object where the sections will be stored in.
 * param	filename	The absolute path to the filename of the ini file.
 * return				Number of sections read from the ini file.
 */
int ini_read_sections(TEXT *txt, STRING *filename);

/**
 * Reads a string from an ini file.
 * param	targetValue		The string where the result will be stored in.
 * param	filename		The absolute path to the filename of the ini file.
 * param	section			The section to read from.
 * param	entry			The key of the section entry to read.
 * param	defaultValue	The default value which will be written into the return value if the key doesn't exist.
 * return					Number of characters read into the string.
 */
int ini_read(STRING *targetValue, STRING *filename, STRING *section, STRING *entry, STRING *defaultValue);

/**
 * Reads an integer from an ini file.nichts
 * param	filename		The absolute path to the filename of the ini file.
 * param	section			The section to read from.
 * param	entry			The key of the section entry to read.
 * param	defaultValue	The default value which will be returned if the key doesn't exist.
 * return					The entry value converted to an integer.
 */
int ini_read_int(STRING *filename, STRING *section, STRING *entry, int defaultValue);

/**
 * Reads a float from an ini file.
 * param	filename		The absolute path to the filename of the ini file.
 * param	section			The section to read from.
 * param	entry			The key of the section entry to read.
 * param	defaultValue	The default value which will be returned if the key doesn't exist.
 * return					The entry value converted to an float.
 */
float ini_read_float(STRING *filename, STRING *section, STRING *entry, float defaultValue);

/**
 * Reads a var from an ini file.
 * param	filename		The absolute path to the filename of the ini file.
 * param	section			The section to read from.
 * param	entry			The key of the section entry to read.
 * param	defaultValue	The default value which will be returned if the key doesn't exist.
 * return					The entry value converted to a var.
 */
var ini_read_var(STRING *filename, STRING *section, STRING *entry, var defaultValue);

/************************************************************
TUST FX
************************************************************/

#define FOG_MAX_ALPHA skill1
#define FOG_CAMERA_DISTANCE 300
#define FOG_SPEED 10

List* fogEntities = NULL;

VECTOR vecEffectsTemp;

BMAP* bmapStar = "star.bmp";
BMAP* bmapFlame = "flame.bmp";
BMAP* bmapSmoke = "smoke.tga";

BMAP* bmapExplParticle = "explParticle.tga";
BMAP* bmapExplSharpnel = "explShrapnel.tga";

/**
* Starts a complex explosion effect
* param	VECTOR*	Position of the effect
*/
void eff_explosion(VECTOR* _pos);

/**
* Starts a complex smoke effect on a certain area
* param	STRING*	File to create smoke entities
* param	VECTOR*	Position to place the smoke
* param	VECTOR*	Size of the smoke
* param	var		Smoke density
* param	var		Effect's time to live
*/
void eff_complexSmoke(STRING *smoke, VECTOR* _pos, VECTOR* _size, var density, var time);

/**
* Generate fog or dust that is always placed around the camera
* param	int	Fog density
*/
void eff_generate_fog(int _density);

void pFountain(PARTICLE *p);
void pDenseSmoke(PARTICLE *p);
void pStars(PARTICLE *p);
void pFlame(PARTICLE *p);
void pSmokeFlames(PARTICLE *p);

// Rain and snow effects can be found in weather.h/.c
void pElectro(PARTICLE *p);
void pLeaves(PARTICLE *p);
void pFlies(PARTICLE *p);
void pBubbles(PARTICLE *p);
void pWaterfall(PARTICLE *p);
void pExplosionFire(PARTICLE *p);
void pExplosionDust(PARTICLE *p);
void pExplosionScatter(PARTICLE *p);

// Internal

void pAlphaFade(PARTICLE *p);
void pAlphaFadeFlame(PARTICLE *p);
void vec_randomize(VECTOR* _vector, var _range);

/************************************************************
Graphics struct
************************************************************/
GraphicsSettingsStruct *CreateGraphicsStruct(int, int, int, int, int, int, int ,int ,int, int);
int CompareGraphicsStruct(GraphicsSettingsStruct *, GraphicsSettingsStruct *);

void SetReleaseNumber(STRING *); // Sets RELEASE_STR_VER to an arbitrary string (normally RELEASE_STR_VER contains release number in string format)
void SetReleaseInfo(STRING *); // The same, but with RELEASE_STR_INFO which contains release info.
void OpenDebug_startup();
void CloseDebug();
void ExitEvent();
void LoadKernel();
void PostLoadKernel();
void LoopKernel();
void LoadPlayground();
void PrecacheContent();
void _beep();
void ApplyGraphicsSettings( GraphicsSettingsStruct * );
int UnloadKernel();
int ReloadKernel();
int Console();
int PlayVideo(STRING *, var);
int SetupShader();
void FolderScan(TEXT *,STRING *,STRING *);
void WriteObjectCustomSettings(ENTITY *);
void LoadObjectCustomSettings(ENTITY *);
int GetPercent(var, var);
void on_level_event(var);
//COLOR *CopyColor(var, var, var);
void Scale(ENTITY *, var);
//int range(var, var, var);
//void place_mesh_on_ground(ENTITY *, int);
var ent_seed_c(char *, ENTITY *, BMAP *, COLOR *, var, EVENT);

void DialogueInitialize(STRING *);
void StartDialogue(BMAP *, BMAP *, STRING *);
void StartDiaryPage(STRING *);

// Implementations for key handlings in different situations
// for example key_esc
// because it can trigger itself lots of events when pressed 
// and we have to decide what event to execute
void Event_key_esc();

void Event_MouseLeft();
void Event_MouseRight();

void ClockStart();
void ClockStop();
void ClockUpdateVar();
void ClockUpdateGUI();

int AddToTextureProjectionArray(ENTITY *);
void RemoveFromTextureProjectionArray(ENTITY *);
void ConvertToCTFormat(STRING *, var, var);

void bmap_savetga(BMAP *, char *);

var LOGFILEHNDL;
char compose_target[300];
STRING *holder = "#500";
STRING *holder_num = "#10";

// Logging functions
void NewLine() { return; } // HTML
char *GenerateDateTime();
void OpenLog( STRING * );
void CloseLog();
STRING *StringForBool(var);

void WriteLog(STRING *);
void WriteLog(VECTOR *);
void WriteLog(ANGLE *);
void WriteLog(int);
void WriteLog(var);
void WriteLog(double);
void WriteLog(float);
void WriteLog(STRING *, VECTOR *);
void WriteLog(STRING *, ANGLE *);
void WriteLog(STRING *, var);
void WriteLog(STRING *, int);
void WriteLog(STRING *, double);
void WriteLog(STRING *, float);

void WriteLogHeaders(); // txt
void hVar(STRING *, int); // txt

void free_camera();
//void toggle_weather();
//void good_weather();

// A simple music player, developed in a rush.
void mpLoad(STRING *, STRING *);
void mpUnload();
void mpPrev();
void mpNext();
void mpPause();
void mpResume();
void mpPlay(STRING *);
void ToggleMusicPlayer();
void sndPlay(STRING *);

// Terrain deformation functions
//void TDeform_deform_terrain();
void TDeform_single(); //upper deform
void TDeform_multiple(); //down deform
void TDeform_multipleSmooth(); //Mutiple vertices from size brush
//void TDeform_changeBrushSingle();
//void TDeform_changeBrushMultiple();
//void TDeform_changeBrushMultipleSmooth();
void TDeform_changeBrushRaise();
void TDeform_changeBrushLower();
void TDeform_saveterrain(ENTITY *);
void TDeform_LoadHeightFrom(ENTITY *);

// A bunch of functions for saving and loading levels
void SaveWorld(STRING *, int);
void SaveWorld_system(var);
void SaveWorld_geodata(var);
void SaveWorld_objectdata(var);

void LoadWorld(STRING *, int);
void LoadWorld_system(var);
void LoadWorld_geodata(var);
void LoadWorld_objectdata(var);

// Object seeding
void paint_canvas();
var format; 
var pixel;
var coords_x;
var coords_y;
var alpha_value = 100;
var canvas_modified = 0;
var paint_outside;
COLOR *current_color2 = { red = 0; green = 255; blue = 255; } // Cyan
COLOR *LineConnectColor = { red = 0; blue = 0; green = 255; }
BMAP* canvas;
BMAP* canvas_paint;
var mark_seedEntstr = 0;
STRING *seedEnt = "#400";
void PerformSeed();
void RecreateSeedMap();
void RemoveSeedEnts();
void SeedEntSelector();
void SeedEntCore();
PANEL *seedPanelCover, *canvas_pan;

void GGUIInit();
void GGUIHide();
void GGUIShow();
void GGUIUpdate(PANEL *);

void _GShowSplashScreen_Common(var);
void GShowSplashScreen(STRING *, var);
void GShowSplashScreen(BMAP *, var);
void guiViewPreset (int *, int, VECTOR *, VECTOR *);
void GPanelAlignMainMenu(PANEL *);
void GPanelCenterInside(PANEL *, PANEL *);
void GPanelResize(PANEL *, int);
void GPanelRotate(PANEL *,var,var,bool);
void GPanelSelect(PANEL *);
void GPanelCenter(PANEL *);
void GPanelDrag(PANEL *);
void GPanelFade(PANEL *, var, var, var);
void GPanelSizeForWH(PANEL *, BMAP *);
void GPanelMoveAlpha(PANEL *, var, var, var, var, var, var);
void GPanelMoveAlphaX(PANEL *, var, var, var);
void GPanelMoveAlphaY(PANEL *, var, var, var);
//void GNotificationCreate(FONT *, STRING *);
//void GWindowClose(var, PANEL *);

void GBlackboardAlphaFade();
void GBlackboardAlphaRestore();
void GToggleStatistics();
void GInsertObjectShow();
void GInsertObjectHide();
void GMaterialEditorShow();
void GToggleTerrainEditor();
void GToggleObjectSeeder();
void GSwitchToMoveMode();
void GSwitchToRotateMode();
void GSwitchToScaleMode();
void GLoadMainMenu();
//void GPreMainMenu();
void GOptionsShow();
void GOptionsAdjustSettings(var);
void GOptions_SaveSettings();
void GOptionsHide();
void GCreditsShow();
void GGameLoad();
void GGameSave();
void GLightWindowShow();
void GLightWindowHide();
void GPropertiesWindowShow();
void GPropertiesWindowHide();
void GSoundWindowShow();
void GSoundWindowHide();
void GParticleWindowShow();
void GParticleWindowHide();
void GWorldNewShow();
void GWorldNewHide();
void GLoadGameShow();
void GLoadGameHide();
void GHelpHide();
void GHelpShow();
void GTrophiesHide();
void GTrophiesShow();
void GMainMenuShow();
void GMainMenuHide();
//void GLoadGame_Scroll(var, PANEL *);
void GNewGameResetDynamicSettings();
void GNewGameResetStaticSettings();
void GSwitchNewGameScreen(var);
void GNewGame_ChooseWorld(var);
void GNewGame_Scrollbar(var, PANEL *);
void GNewGame_PreviewScene();
void GNewGame_UnPreviewScene();
void LaunchGameSession();
void GSKYSTR_Up(); // I don't use grouped functions with parameters 'cause I don't want to get stuck
void GSKYSTR_Down(); // with a bunch of if..else statements.
void GGROUNDSTR_Up();
void GGROUNDSTR_Down();
void GLOADGAMESTR_Up();
void GLOADGAMESTR_Down();
void GTEMPSTR_Up();
void GTEMPSTR_Down();
void GTerrainLoadGeoWrapper();
void GTerrainSaveGeoWrapper();
void GInDevShow();
void GInDevHide();
void GWeatherMode_RainOnly();
void GWeatherMode_SnowOnly();
void GWeatherMode_Nothing();
void GWeatherMode_RainSnow();
void GBackMenuShow();
void GBackMenuHide();
void GQuitToMainMenu();
void GTerrainSubmenuHide();
void GTerrainSubmenuShow();
void GQuitCraftbox();
void GUnQuitCraftbox();
void GOpenPropertiesWindow();

// wrappers/controllers for sound instructions
void GSEMenuMouseHover();
void GSEMenuMouseClick();

void GIO_ObjectTab_SwitchTab(var);
void GOptions_Graphics();
void GOptions_Sound();
void GOptions_Themes();
void GOptions_Maintenance();

void GSelectObject(var);
void GSelectLight(var);
void GSelectParticle(var);

void GToggleMusicPlayerRandomize();

//void GToggleLevelCreationMode(var);
void FillFromPool(TEXT *, TEXT *, var, var); // dest, pool, amount, scaler
void PassToSKYSTR(var);
void PassToGROUNDSTR(var);
void PassToLOADGAMESTR(var);

void FollowPointer();

void ObjectRestoreDefault();
void ObjectRandomPan();

int PassObjectPropertiesToGUI(ENTITY *);

void ReadMaterialDataFromFile(MATERIAL *, STRING *);
void WriteMaterialDataToFile(STRING *, MATERIAL *);
void PassMaterialDataToWindow(MATERIAL *);
void MaterialCopyColor(MATERIAL *, MATERIAL *);

int PassObjectDataToClipboard(ENTITY *, ObjectStruct *);
int PassClipboardDataToObject(ENTITY *);

//int MaterialSelect(var);
//void MaterialSave();

void WriteToBlackboard(STRING *, STRING *, var);

void ObjectCut();
void ObjectCopy();
void ObjectPaste();
void ObjectManipulationCore();
void ObjectManipulationInterface();

ENTITY *CreateObject();

//void LoadSavedBMAPs();

int SaveGameToSlot(var);
int LoadGameFromSlot(var);

int ConfigFileRead(STRING *);
int ConfigFileWrite(STRING *);

int GenerateLight();
int GenerateSound();
int GenerateWaypoint();
int GenerateTerrain();

void func_particle_segment();
void func_lightning_effect();
void func_increase_brightness();
void weather_change();
void sky_day_fade_in();
void sky_day_state();
void sky_night_fade_in();
void sky_night_state();
//void act_mystymood_trigg_label1();
//void lensflare_create();
//void lensflare_start();
//void flare_init(ENTITY *);
//void flare_place(ENTITY *);

void LoadNewLevel();
void LoadNewLevelFromWindow();
void LoadNewLevelFromMenuWindow();

//void LevelCleaner();
void TakeScreenshot();
void OptimizeFramerate(var);

void InitMystymood(); // This will load the necessary resources for the Mystymood engine.
void LoadMystymood( bool ); // This will toggle the Mystymood engine on and off. Not to be confused with InitMystymood() which only loads the resources.
//void UnloadMystymood();
//void LoadMystymoodLensflare();
void func_fade_colors(var *, var *, var *);
//void func_particle_seed_infinity(PARTICLE *);
//void func_effect_particle_seed(PARTICLE *);
//void func_fade_lightning(PARTICLE *);
//void func_particle_lightning(PARTICLE *);
//void func_particle_segment();
//void func_increase_brightness();
void weather_change();

// These are particle function prototypes, and were generated
// by 3rd party tools (instead of hard-coded by hand). So their names are a bit messed up.
// For those who want to modify my code: I've tried naming them properly.
// But core functions remain unreadable.
void New_Base_Effect_base_event(PARTICLE *);
void New_Base_Effect_base(PARTICLE *);
void Base_Effect_base_event(PARTICLE *);
void Base_Effect_base(PARTICLE *);
void Base_Effect1_base_event(PARTICLE *);
void Base_Effect1_base(PARTICLE *);
void Base_Effect2_base_event(PARTICLE *);
void Base_Effect2_base(PARTICLE *);
void Base_Effect15_base_event(PARTICLE *);
void Base_Effect15_base(PARTICLE *);
void Base_Effect14_base_event(PARTICLE *);
void Base_Effect14_base(PARTICLE *);
void Base_Effect13_base_event(PARTICLE *);
void Base_Effect13_base(PARTICLE *);
void Base_Effect12_base_event(PARTICLE *);
void Base_Effect12_base(PARTICLE *);
void Base_Effect11_base_event(PARTICLE *);
void Base_Effect11_base(PARTICLE *);
void Base_Effect3_base_event(PARTICLE *);
void Base_Effect3_base(PARTICLE *);
void New_child2_child_event(PARTICLE *);
void New_child2_child(PARTICLE *);
void New_child_child_event(PARTICLE *);
void New_child_child(PARTICLE *);
void Base_Effect4_base_event(PARTICLE *);
void Base_Effect4_base(PARTICLE *);
void New_effect1_base_event(PARTICLE *);
void New_effect1_base(PARTICLE *);
void New_child_child_event2(PARTICLE *);
void New_child_child2(PARTICLE *);
void Base_Effect_base_event2(PARTICLE *);
void Base_Effect_base2(PARTICLE *);
void Base_Effect_base_event3(PARTICLE *);
void Base_Effect_base3(PARTICLE *);
void Base_Effect1_base_event3(PARTICLE *);
void Base_Effect1_base3(PARTICLE *);
void star1_base(PARTICLE *);
void second_base(PARTICLE *);
void firstb_base_event(PARTICLE *);
void firstb_base(PARTICLE *);
void first_base_event(PARTICLE *);
void first_base(PARTICLE *);
void standard_base(PARTICLE *);
void sparkleblue_base(PARTICLE *);

void emit_spiral();
void emit_colorfulspark();
void emit_spacehole();
void emit_fountain2();
void emit_fountain1();
void emit_fire2();
void emit_fire1();
void emit_doublehelix();
void emit_composition();

void p_spiral_create(VECTOR *);
void p_spark_colorful_create(VECTOR *);
void p_space_hole_create(VECTOR *);
void p_fountain_2_create(VECTOR *);
void p_fountain_1_create(VECTOR *);
void p_fire_2_create(VECTOR *);
void p_fire_1_create(VECTOR *);
void p_double_helix_create(VECTOR *);
void p_composition_create(VECTOR *);

void rain_event(PARTICLE *);
void rain_base(PARTICLE *);
void rain(VECTOR *);

void SetReleaseNumber(STRING *Num) { str_cpy(RELEASE_STR_VER,Num); }
void SetReleaseInfo(STRING *Inf) { str_cpy(RELEASE_STR_INFO,Inf); }

#endif HEADER_H