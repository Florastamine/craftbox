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
//#include <d3d9.h>
//#include <particles.c>
#include <level.c>

#define A7_DEVELOPMENT
//#define CBOX_DEVELOPMENT
#define CBOX_LOADSCREEN
#define CBOX_SPLASHSCREENS
#define CBOX_SHADERS
#define CBOX_FLATMENU
#define CBOX_USE_TXT_LOG
#define CBOX_RANDOM_EVERYTHING

typedef short bool;

bool cbPlaytesting = false;
bool cbNonWindows = false; // For running craftbox under other environments that is not Windows.
bool cbFlatMenu = false; // Set this prior to executing the menu loader cause craftbox to use flat menu instead of 3D-based menu.
bool cbError_NoGround = false; // Used for marking error caused by no grounds available
bool cbFinishedLoadKernel = false; // To indicate the kernel has been successfully loaded.
bool cbKernelRunning = false;
bool cbInBuildment = false;
bool cbUsectraceOptimization = false;
bool cbUseDistanceBasedOptimization = true;
bool cbRandomPlacement = false; // Random placement of objects..useful for generating random scenes
bool cbTerrainEditing = false; // We're in the terrain editing mode
bool PlayerPresent = false;
bool AllowREC = true;
bool AllowCompass = true; // If disabled, compass calculation will still be performed, but the GUI won't display it.
bool LoadWorldBreak = false; // Indicate failure when loading a new level.

int SessionsCount = 0; // Count how many sessions (worlds) we've played so far
int guiCurrentViewPreset = 1; // Which view to be used at startup?

var LOGFILEHNDL; // Global variable for handling the log file.

var VOL_EFFECTS = 75, VOL_MUSIC = 100; // Alternative vars for sound_vol and midi_vol.

int sResX, sResY, sResMode; // Store screen resolution in X and Y. 

short CameraPosID_temp = 0;  // Temporary variable to store guiCurrentViewPreset at some point
int DialogueSentencesCount = 0; // Count sentences in a dialogue.

// Two strings for release number and release mode.
STRING *RELEASE_STR_VER = "0.21";
STRING *RELEASE_STR_INFO = "publicly available pre-alpha";

STRING *titleWindow = "craftbox Pre-alpha";
//////////////////////////////////////////////////////////////

// A TEXT struct represents craftbox console.
TEXT *def_ctxt = { font = "Arial#15b"; string("Console","#80"); layer = 999; }

// Some variables and an ANGLE struct represent the debug panel.
var def_dfps,def_dtps,def_dtlv,def_dtcs,def_dtac,def_dtrf,def_dsnd;
ANGLE def_cang;

var def_shot_num = 0;
var def_oldmouse = 0;

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
	bool /* pPhysics, pStatic, */ _flags[ 8 ];
	
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
GraphicsSettingsStruct defaultConfig/*, tempConfig*/; // tempConfig is used for temporary saving configuration for later comparison
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

// Fixed camera angles for use in the 3D-based main menu.
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
#define LOADSCREEN_FADE_SPEED 10

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

#define WATER_PLANE_U_SHIFT 10
#define WATER_PLANE_V_SHIFT 10

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
int mpCount = 0, mpRandomize = 1, mpSongs, mpPauseMark; // Vars declared specifically for the music player.
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

STRING *mouse_str = "mouse_pointer.png";
BMAP *mouse_painttex = "pen.png";

STRING *_mpCount = "#5";
STRING *_mpSongTemp = "#100";

SOUND *__beep = "./CookedSounds/beep.wav";
//SOUND *footstep = "./CookedSounds/tap.wav";
//STRING *SE_MM_hover = "./CookedSounds/button-24_MMhover.wav"; // Actually they're sound files but under the STRING form.
//STRING *SE_MM_click = "./CookedSounds/button-30_CMMclickon.wav";

// Background level
STRING *LEVEL_MENU = "./CookedWorlds/background.wmb";
STRING *CAMERA_MODEL = "real_cam.mdl";

STRING *VAREXPLORER_EXITSTR = "exit";
STRING *VAREXPLORER_REPORTSTR = "report";
STRING *VAREXPLORER_FACTORYSTR = "default";
STRING *VAREXPLORER_STARTKERNELSTR = "startkernel";
STRING *VAREXPLORER_BENCHMARK = "benchmark";

STRING *FILE_SCREENSHOT = "craftbox";
STRING *FILE_CONFIG = "./Source/Config.cfg";
STRING *FILE_CREDITS_TEXT = "./Source/Credits.cre";
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
STRING *PATH_MUSIC = "CookedSounds\\Music\\";

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

void PassToSelect1String();

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

int nWaterLevel							=	-160;		// z position of water

// Use to tweak frame rates
#define LAND_FOG_NEAR		200
#define LAND_FOG_FAR			4000

#define AQUA_FOG_NEAR		-300
#define AQUA_FOG_FAR			600

#define WEATHER_FOG_NEAR	100
#define WEATHER_FOG_FAR		1000

// Weather particle box around the camera
#define WEATHER_BOX_X		20000
#define WEATHER_BOX_Y		20000
#define WEATHER_BOX_Z		20000

// Effect density
#define RAIN_DENSITY 1000
#define SNOW_DENSITY 2000

var NightDuration = .5;
var DayDuration = .5;
var MoonScaleFactor = .5;
var NightScaleFactor = .5;
var NightSkySpeed = 20;
var _DayDuration, _NightDuration, _MoonScaleFactor, _NightScaleFactor, _NightSkySpeed;

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

var vSndHandleRain			= 0;
var vSndHandleWind			= 0;
var vSndHandleBgDay			= 0;
var vSndHandleBgNight		= 0;
var vSndHandleUnderwater	= 0;
var vSoundHandleThunder    = 0;

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

var _fog_color, _sun_light;
var _d3d_fogcolor1_red, _d3d_fogcolor1_green, _d3d_fogcolor1_blue, _camera_fog_end;

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
#define ObjectSystemType skill7
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
#define ObjectSystem 100

#define Particle 11
#define Light 12
#define Sound 13
#define Terrain 14
#define Sprite 15
#define Neutral 16
#define Player 17 // Player != player

#define DynamicContent 18 // Entities which are marked with this are deleted when playtesting mode has finished.
#define SeedEnt 19 // Entities crated by the ent_seed function.

void SECreate_PlayerNormal ();
void SECreate_PlayerBike ();
void CreateSystemObject ();

int SystemObjectID = -1;
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
	
	red = 255;
	green = 0;
	blue = 0;
	
}

TEXT* ConsoleText = { font = "Arial#15b"; string("

	This is a console, although there's not much to see and interact with.
	
	This is a safe place to view and modify craftbox's variables and/or execute maintenance functions.
	
	Official releases' users shouldn't be here.
	
	Commands are executed in a single or multi line fashion.
	To combine commands, just enter them all in one line.
	
	Variables' names are followed by a \"=\".
	[Enter] to view the variable's current value, or enter a new value 
	and press [Enter] to assign a new value.
	
	A full list of commands (along with their executioners) can be found in the source code.
	Type \"startkernel\" at any time to return to craftbox.

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
_use_nightstars = 1;
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
*panDialogue,
*panNotification;

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
*WaterPlaneMarker, // points to the marker for correctly placing the water plane
*Gun; // 1st person gun
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
Math
************************************************************/

/*

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

*/

/************************************************************
TUST FX
************************************************************/

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
void SetDefaultGraphicsSettings();

void SetReleaseNumber(STRING *); // Sets RELEASE_STR_VER to an arbitrary string (normally RELEASE_STR_VER contains release number in string format)
void SetReleaseInfo(STRING *); // The same, but with RELEASE_STR_INFO which contains release info.
void OpenDebug_startup();
void CloseDebug();
void ExitEvent();
void LoadKernel();
void PostLoadKernel();
void LoopKernel();
void LoadPlayground();
void _beep();
void ApplyGraphicsSettings( GraphicsSettingsStruct * );
int UnloadKernel();
int ReloadKernel();
int Console();
void OpenConsole();
void OpenBenchmark() { wait( 1 ); }
int PlayVideo(STRING *, var);
int SetupShader();
void FolderScan(TEXT *,STRING *,STRING *);
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
var MainMenuMusicHndl;
void mpLoad(STRING *, STRING *);
void mpUnload();
void mpPrev();
void mpNext();
void mpPause();
void mpResume();
void mpPlay(STRING *);
void ToggleMusicPlayer();

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
/*

void SaveWorld(STRING *, int);
void SaveWorld_system(var);
void SaveWorld_geodata(var);
void SaveWorld_objectdata(var);

void LoadWorld(STRING *, int);
void LoadWorld_system(var);
void LoadWorld_geodata(var);
void LoadWorld_objectdata(var);

*/

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

void GameSplash ();
void GBlackboardAlphaFade();
void GBlackboardAlphaRestore();
void GToggleStatistics();
void GInsertObjectShow();
void GInsertObjectHide();
//void GMaterialEditorShow();
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
//void GNewGame_Scrollbar(var, PANEL *);
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
void GTerrainSubmenuShow();
void GQuitCraftbox();
void GUnQuitCraftbox();
void GOpenPropertiesWindow();

// GUI stuff for system objects
void GSpawnNotificationHide ();
void GSpawnNotificationShow ();
void GSpawnDialogueHide ();
void GSpawnDialogueShow ();

// wrappers/controllers for sound instructions

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

//void ReadMaterialDataFromFile(MATERIAL *, STRING *);
//void WriteMaterialDataToFile(STRING *, MATERIAL *);
//void PassMaterialDataToWindow(MATERIAL *);
//void MaterialCopyColor(MATERIAL *, MATERIAL *);

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

//int SaveGameToSlot(var);
//int LoadGameFromSlot(var);

int ConfigFileRead(STRING *);
int ConfigFileWrite(STRING *);

int GenerateLight();
int GenerateSound();
int GenerateWaypoint();
int GenerateTerrain();
int GenerateWaterPlane();

#define GENERATED_REFLECTION skill25
void GenerateReflection(ENTITY *);
void UpdateGeneratedReflections(STRING *);

void func_particle_segment();
void func_lightning_effect();
void func_increase_brightness();
void weather_change();
void sky_day_fade_in();
void sky_day_state();
void sky_night_fade_in();
void sky_night_state();

void LoadNewLevel();
//void LoadNewLevelFromWindow();
//void LoadNewLevelFromMenuWindow();

//void LevelCleaner();
void TakeScreenshot();
//void OptimizeFramerate(var);

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

void SetReleaseNumber(STRING *Num) { str_cpy(RELEASE_STR_VER,Num); }
void SetReleaseInfo(STRING *Inf) { str_cpy(RELEASE_STR_INFO,Inf); }

// compiler missing function fix
void bullet_particles();

void dummy() { wait( 1 ); }
action Player_Normal();
action Player_Bike();
action Spawn_Warning();

#endif HEADER_H
