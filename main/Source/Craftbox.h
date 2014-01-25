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

The constants have already been optimized for low-end computers.
Increase the limitations if you want but be careful, you may end up killing 
the frame rates very badly. 

Mystymood
The style of organizing scripts that was used in MystyMood was
terrible so I made a .c and put all the definitions and declarations
there. Just like I did with craftbox.

I changed some variables that require only 1 or 0 as acceptable
values to BOOL (not bool) instead of int/var.

readme.txt
MystyMoods C-Script to Lite-C conversion by Alex Rozhkov (Shadow969)
http://www.coniserver.net/ubbthreads/showprofile.php?Cat=0&User=20725

>+++
--------------------------------------------------
*/

#define PRAGMA_PATH "./Source/Rendering"

#define PRAGMA_PATH "./Cooked2D"
#define PRAGMA_PATH "./Cooked2D/Skies"

#define PRAGMA_PATH "./CookedSounds"
#define PRAGMA_PATH "./CookedSounds/Music"

#include <acknex.h> // standard engine objects
//#include <stdio.h> // Screen space ambient occlusion
#include <strio.c>
#include <d3d9.h> // Shade-C
#include <particles.c> // effects such as snow()
#include <level.c>

#define CBOX_DEVELOPMENT
#define USE_TXT_LOG

//////////////////////////////////////////////////////////////

TEXT* def_ctxt = { font = "Arial#15b"; string("Console","#80"); layer = 999; }

var def_dfps,def_dtps,def_dtlv,def_dtcs,def_dtac,def_dtrf,def_dsnd;
ANGLE def_cang;

var def_shot_num = 0;
var def_oldmouse = 0;

BOOL PLAYTESTING = 0;
BOOL UNDER_MAC_OR_LINUX = 0; // Running craftbox under Mac or Linux-based OS.
BOOL UseFlatMenu = 0;
var LoadWorldBreak;
var PreKernelDone;
var sResX, sResY, sResMode;

//script to capture a skycube by pressing x in 3dgs
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
int CameraPosID_temp;

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
	BOOL pPhysics, pStatic, _flags[ 8 ];
	
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
	
	BOOL dp;
	var _skill[ 130 ];
	
} OBJECTSTRUCT;

///////////////////////////////////////////////////////////
// One solid struct is better than thousands of scattered
// variables
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
   
   
} GRAPHICSKONFIG;

OBJECTSTRUCT clipboard;
GRAPHICSKONFIG defaultConfig, tempConfig; /* tempConfig is used for temporary saving configuration for later comparison */
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

var DialogueSentencesCount = 0;

STRING *PARAM_NOLOGFILE = " -dwl";
//STRING *PARAM_DEV = " -dev";
//STRING *PARAM_SUSPENDKERNEL = " -dlk";
STRING *PARAM_USECTRACE = " -com";

STRING *tag_header = "craftbox World Data File";
STRING *tag_header_warn = "This file contains (encrypted) world information. Blah, blah, blah...";
STRING *tag_system_header = "System data";
STRING *tag_geodata = "Terrain geometry data";
STRING *tag_objectdata = "Object data";

BOOL KERNEL_IS_RUNNING = false,
IN_GAME = false,
C_TRACE_OPTIMIZATION = false,
DISTANCE_OPTIMIZATION = true;

#define MENU_CAMERA_LAUNCH 1
#define MENU_CAMERA_NEW_GAME 2
#define MENU_CAMERA_LOAD_GAME 3
#define MENU_CAMERA_OPTIONS 4
#define MENU_CAMERA_TROPHIES 5
#define MENU_CAMERA_HELP 6
#define MENU_CAMERA_CREDIT 7
#define MENU_CAMERA_LAUNCH_GAME 8
#define MENU_CAMERA_EXIT 9

// Fixed values got by capturing
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

int PlayerPresent = 0;
int AllowREC = 1;
int AllowCompass = 1;

var SecondsPassed = 0, MinutesPassed = 0, HoursPassed = 0, DaysPassed = 0, MonthsPassed = 0, SeasonsPassed = 0, YearsPassed = 0;
int StopClock;

var InBackMenu;
var RandomPlacement;

var total_vertices = 5; // will store the total number of vertices for the current terrain entity
var bSize = 800; //Brushe Terrain deform size 
var tMaxHeight = 5000; //Terrain Max Height
var sizeh = 10;
var brush_speed = 5;
var TerrainEditMode = 0;

var bType = B_MULT; //brushe type
var bHeight = DEF_UPPER;
var bHlimit = FALSE;

var StatsIsRunning = 0;
var CountObjects = 0, CountParticles = 0, CountLights = 0, CountSounds = 0, CountSprites = 0, CountTotal = 0;

int rEntCount = -1;

var temp_cam;
int SessionsCount = 0;
var guiViewPresetSpeed = 0.1;
int guiCurrentViewPreset = 1; // Use default view at start

var BBTranslucency;
var ToggleSnow = 0;
var ToggleRain = 0;

//BOOL SHADE_C_FLAG;

var LOGFILEHNDL;

var VOL_EFFECTS = 75, VOL_MUSIC = 100; // Alternative vars for sound_vol, midi_vol and such.
int mpCount = 0, mpRandomize = 0, mpSongs, mpPauseMark; // Vars declared specifically for the music player.
var mpHandle;

STRING *mouse_str = "mouse_pointer.png";
BMAP *mouse_painttex = "pen.png";

STRING *_mpCount = "#5";
STRING *_mpSongTemp = "#100";

SOUND *__beep = "./CookedSounds/beep.wav";
//SOUND *footstep = "./CookedSounds/tap.wav";
STRING *SE_MM_hover = "./CookedSounds/button-24_MMhover.wav"; // Actually they're sound files but under the STRING form.
STRING *SE_MM_click = "./CookedSounds/button-30_CMMclickon.wav";

STRING *RELEASE_STR_VER = "0.1";
STRING *RELEASE_STR_INFO = "pre-alpha";

// Background level
STRING *LEVEL_MENU = "./CookedWorlds/background.wmb";
STRING *CAMERA_MODEL = "real_cam.mdl";

STRING *VAREXPLORER_EXITSTR = "exit";
STRING *VAREXPLORER_REPORTSTR = "report";
STRING *VAREXPLORER_FACTORYSTR = "default";

STRING *FILE_SCREENSHOT = "craftbox";
STRING *FILE_CONFIG = "./Source/Config.cfg";
//STRING *FILE_CUSTOM_MAT_1 = "./Source/mat_custom_1.cfg";
//STRING *FILE_CUSTOM_MAT_2 = "./Source/mat_custom_2.cfg";
//STRING *FILE_CUSTOM_MAT_3 = "./Source/mat_custom_3.cfg";
//STRING *FILE_CUSTOM_MAT_4 = "./Source/mat_custom_4.cfg";
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

#define RAIN_ONLY 0
#define SNOW_ONLY 1
#define RAIN_SNOW 2
#define NO_RAIN_SNOW 3

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

BOOL from_test_play = 0;

////////////////////////////////////////////////////////////
// Variables and booleans related to Mystymood.
////////////////////////////////////////////////////////////
var sun_azimuth = 190;//fix sun position when dynamic_day_night is set to "0"
var sun_elevation = 20;//fix sun position when dynamic_day_night is set to "0"

var time_speed = 30;//day-night transition speed
var time_speed_night = 50;//time_Speed during night (you can shorten the night!)

var fog_mor[3] = {111,190,250};//b, g, r
var fog_day[3] = {140,170,160};
var fog_eve[3] = {72,135,240};
var fog_night[3] = {30,20,20};
//applied fogcolor when dynamic_day_night is deactivated
var fog_dynamic_day_night_off[3] = {160,170,160};

//be carefull with these...
var fog_fade_speed = 2, sky_fade_speed = 0.03;

var max_zenith = 50;//sets the max sun height (on it's path...when dynamic day/night cycle is on)
var sun_col_fac = 0.5;//factor of sun_color influence (sun_color is set to fogcolor)

var part_vel_x, part_vel_y, part_vel_z;
var part_size, part_alpha, part_num; 

//bad weather fog colors...night darker than day
var fog_weather_day[3] = {50,50,50};//r, g, b
var fog_weather_night[3] = {15,15,15};

var weather_fade_speed = 10;//fade-speed of weather change
var current_color[3];

// lens_flare.c
//var flare_alpha = 70;
//var flare_fadespeed = 25;
/* var lens_active = 0, */ var mystymood_active = 0;

BOOL dynamic_day_night = 1;

var original_moon_scale_fac,
original_time_speed_night,
original_night_sky_scale_x,
original_night_sky_speed_x,
original_fog_color,
original_camera_fog_start,
original_camera_fog_end,
original_sun_light,
original_d3d_fogcolor1r,
original_d3d_fogcolor1g,
original_d3d_fogcolor1b,

_moon_scale_fac = moon_scale_fac,
_time_speed_night = time_speed_night,
_time_speed = time_speed,
_night_sky_scale_x = night_sky_scale_x,
_night_sky_speed_x = night_sky_speed_x,
_load_lensflare = 1,
_use_moon = 1,
_use_sun = 1,
_use_nightstars = 1,
_weather_mode = NO_RAIN_SNOW; // RAIN_ONLY, SNOW_ONLY, RAIN_SNOW, NO_RAIN_SNOW
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
FONT *f = "Arial#27b";

////////////////////////////////////////////////////////////
// Material declarations
////////////////////////////////////////////////////////////
//MATERIAL *mat_select, *mat_temp, *pTexColor;

// Predefined materials
//MATERIAL *mat_lava, *mat_smaragd, *mat_marble,
//*mat_lavenderrose, *mat_bitterlemon, *mat_peachorange,
//*mat_purewhite, *mat_black, *mat_palelilac;

// Custom materials
//MATERIAL *mat_custom[4];

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
GRAPHICSKONFIG *CreateGraphicsStruct(int, int, int, int, int, int, int ,int ,int, int);
int CompareGraphicsStruct(GRAPHICSKONFIG *, GRAPHICSKONFIG *);

void OpenDebug_startup();
void CloseDebug();
void ExitEvent();
void LoadKernel();
void PostLoadKernel();
void LoopKernel();
void LoadPlayground();
void PrecacheContent();
void _beep();
void ApplyGraphicsSettings( GRAPHICSKONFIG * );
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
void GPanelRotate(PANEL *,var,var,BOOL);
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

int PassObjectDataToClipboard(ENTITY *, OBJECTSTRUCT *);
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

//void LoadMystymood(BOOL, BOOL); // This will load the Mystymood engine.
void LoadMystymood( BOOL );
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
void snow(var, var, VECTOR *);
void rain(var, var);

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

#endif HEADER_H