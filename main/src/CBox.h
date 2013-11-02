#ifndef HEADER_H
#define HEADER_H

/*
CBox.h

Base declarations.
For example if you want to make fried eggs you need eggs. That's all.

TODO:
<+++



>+++

NOTES:
<+++

Mystymood
The style of organizing scripts that was used in MystyMood was
terrible so I made a .c and put all the definitions and declarations
there. Just like I did with craftbox.

I changed some variables that require only 1 or 0 as acceptable
values to BOOL (not bool you fool) instead of int/var.

readme.txt
MystyMoods C-Script to Lite-C conversion by Alex Rozhkov (Shadow969)
http://www.coniserver.net/ubbthreads/showprofile.php?Cat=0&User=20725

Known issues:
-fps slow down within the particle effects (snow, rain)

Everybody is welcome to help fixing those bugs...THANKS!!!

>+++
--------------------------------------------------
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
	BOOL pPhysics, pStatic, _flags[8];
	
	// Some vars define its physical properties
	var mass, friction;
	
	MATERIAL *m;
	
	////////////// Particle objects
	
	////////////// Light objects
	var _red, _green, _blue, _range;
	int _LightMode;
	
	////////////// Sound objects
	
	////////////// Node placer
	
	BOOL dp;
	
} OBJECTSTRUCT;

OBJECTSTRUCT clipboard;

//////////////////////////////////////////////////////////////

// System
char undef = '-';

#define BORDER 10
#define DEFAULT_ALPHA 50

#define FOG_END_LIM 8000

#define FIXED_CULLING_DISTANCE 1500
#define FOG_CULLING_DISTANCE 200

#define MINIMUM_RESOLUTION_X 1024
#define MINIMUM_RESOLUTION_Y 768

#define MINIMUM_SCALE_CONSTANT .5

#define DYNAMIC_LIGHT_DISCO_SPEED 0.1

#define MAX_rEnts 1000

int rEntCount = -1;

var temp_cam;
int SessionsCount = 0;
var guiViewPresetSpeed = 0.1;
int guiCurrentViewPreset = 1; // Use default view at start

BOOL KERNEL_IS_RUNNING = false,
IN_GAME = false,
C_TRACE_OPTIMIZATION = false,
DISTANCE_OPTIMIZATION = true;

//BOOL SHADE_C_FLAG;

var LOGFILEHNDL;

var VOL_EFFECTS = 75, VOL_MUSIC = 100;

SOUND *__beep = "beep.wav";

STRING *RELEASE_STR_VER = "< release number >";
STRING *RELEASE_STR_INFO = "< release info >";

STRING *VAREXPLORER_EXITSTR = "exit";
STRING *VAREXPLORER_REPORTSTR = "report";
STRING *VAREXPLORER_FACTORYSTR = "default";

STRING *pref_savebmaps = "./src/outside";
STRING *pref_savegames = "./src/outside/cgame";

STRING *FILE_SCREENSHOT = "craftbox";
STRING *FILE_CONFIG = "./src/outside/settings.cfg";
STRING *FILE_CUSTOM_MAT_1 = "./src/outside/mat_custom_1.cfg";
STRING *FILE_CUSTOM_MAT_2 = "./src/outside/mat_custom_2.cfg";
STRING *FILE_CUSTOM_MAT_3 = "./src/outside/mat_custom_3.cfg";
STRING *FILE_CUSTOM_MAT_4 = "./src/outside/mat_custom_4.cfg";
STRING *FILE_CREDITS_0 = "./src/outside/c.t.txt";
STRING *FILE_CREDITS_TEXT = "./src/outside/c.txt";
STRING *FILE_LOG = "./CBox.log";

STRING *FILE_GAME_INTRO_VIDEO = "#300";
STRING *FILE_GAME_OUTRO_VIDEO = "#300";

STRING *GROUNDSTR = "#300"; // Store ground location.
STRING *SKYSTR = "#300"; // Store sky (cube) location.
STRING *TEMPSTR = "#300"; // Store object location
STRING *LOADGAMESTR = "#300";

STRING *EXT_OBJECT = "mdl";
STRING *EXT_SOUND = "wav";
STRING *EXT_TERRAIN = "hmp";
STRING *EXT_SPRITE = "tga";
STRING *EXT_SAVEDGAMES = "s";

STRING *PATH_SOUNDS = "./sounds/";

STRING *PATH_SPRITES = "./objects/sprites/";
STRING *PATH_TERRAINS = "./objects/blands/";
STRING *PATH_OBJECTS_ANMS = "./objects/anms/";
STRING *PATH_OBJECTS_ARCHS = "./objects/archs/";
STRING *PATH_OBJECTS_CHARS = "./objects/chars/";
STRING *PATH_OBJECTS_ETC = "./objects/etc/";
STRING *PATH_OBJECTS_FOOD = "./objects/food/";
STRING *PATH_OBJECTS_MACHS = "./objects/machs/";
STRING *PATH_OBJECTS_PLANTS = "./objects/plants/";
STRING *PATH_OBJECTS_SYS = "./objects/sys/";
STRING *PATH_OBJECTS_TPORTTS = "./objects/tportts/";

STRING *PATH_SKIES = "./2d/skies/";

STRING *PATH_GROUNDS = "./levels/grounds/";

STRING *PATH_SAVEDGAMES = "./levels/";

short TEMP_OBJECT_TYPE;

STRING *LOADCRAFTBOX_1 = "Initializing events and variables...";
STRING *LOADCRAFTBOX_2 = "Initializing saved bitmaps and custom materials...";
STRING *LOADCRAFTBOX_3 = "Initializing GUI...";

TEXT *OptionsGraphicsTxt;
TEXT *OptionsSoundTxt;
TEXT *OptionsThemesTxt;
TEXT *OptionsMaintenanceTxt;
TEXT *ReleaseInfo = {
   
   strings(2);
   
   string(RELEASE_STR_VER,RELEASE_STR_INFO);
   
   font="Arial#20";
   
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

var _moon_scale_fac,
_time_speed_night,
_night_sky_scale_x,
_night_sky_speed_x;

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

new_moon_scale_fac,
new_time_speed_night,
new_night_sky_scale_x,
new_night_sky_speed_x,
new_load_lensflare,
new_use_moon,
new_use_sun,
use_nightstars;

//night sky
// lim(night_sky_scale_x) = 4
// lim(moon_scale_fac) = 5;
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

#define sun_grow_z		 1500//z-height of sun-grow/sun-shrink, adjust according to your horizon view

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

//define here the xyz size of the weatherbox around the camera
#define cx 1000//lenght
#define cy 1000//width
#define cz 600//height

#define rain_part_num 2//defines rain density
#define snow_part_num 1//defines snow density

#define trigg_rain FLAG1
#define trigg_snow FLAG2
#define trigg_disable_lightning_thunder FLAG3//1=disables lightning-thunder
#define trigg_range skill1

#define trigg_rain_wind_x skill2
#define trigg_rain_wind_y skill3
#define trigg_rain_fallspeed skill4

#define trigg_snow_wind_x skill5
#define trigg_snow_wind_y skill6
#define trigg_snow_fallspeed skill7

#define trigg_rain_random_move_on FLAG4//1=let the wind-strenght change randomly, 0=no wind-strenght changes
#define trigg_snow_random_move_on FLAG5
#define trigg_rain_random_move skill8//strength of randomness on the particles x/y movement direction
#define trigg_snow_random_move skill9

#define trigg_weather_fade_speed skill10//fade-speed of weather change

#define trigg_fog_col_dist FLAG6//these are clear...
#define trigg_fog_near skill11
#define trigg_fog_far skill12
#define trigg_fog_red skill13
#define trigg_fog_green skill14
#define trigg_fog_blue skill15
#define trigg_ID skill100

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
#define CameraFP skill7
#define CameraBike skill8
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

TEXT *files_list = {
	
	layer = 15;
	
	strings(800);
	font = "Arial#27b";   
	
}

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

TEXT *music_list = {
   
   layer = 15;
   
   strings(100);
   
   font = "Arial#27b";
   
//   flags = SHOW;
   
}

TEXT* ConsoleText = { font = "Arial#15b"; string("

	< craftbox variable explorer >

","#255","#255","#255","#255","#255"); layer = 999; }

TEXT *PreMainMenuLoading = {
   
   layer = 20;
   
   string("#500","#200","#200");
   
   pos_x = 20;
   pos_y = 20;
   
   font = "Arial#27b";
   
   red = 54;
   green = 117;
   blue = 136;
   
}

TEXT *files_list_SKYSTR_Pool = { strings(800); }
TEXT *files_list_GROUNDSTR_Pool = { strings(800); }
TEXT *files_list_LOADGAMESTR_Pool = { strings(800); }

////////////////////////////////////////////////////////////
// Variables/Booleans will be declared here.
////////////////////////////////////////////////////////////

var WorldType;
var InMenu_NewGame, InMenu_Options;

int SKYSTR_Scaler = 0, GROUNDSTR_Scaler = 0, LOADGAMESTR_Scaler = 0;

BOOL play_as_fp, play_as_bike;

int mat_type, manip_type;
int files_found, list_start;
int shot = 0;

var files_already;

var olrange; // Old light range

var v_alpha, v_ambient,

v_ambient_r, v_ambient_g, v_ambient_b,
v_diffuse_r, v_diffuse_g, v_diffuse_b,
v_specular_r, v_specular_g, v_specular_b,
v_emissive_r, v_emissive_g, v_emissive_b,
v_power, 
v_alpha_m, // Alpha for materials

v_lred, v_lgreen, v_lblue, v_lrange,

v_fogr, v_fogg, v_fogb, v_fogdensity,

v_objectz;

COLOR temp_light;

var ParticleIDNumber;
var _ObjectType;

var page = 1, lfsp = 0; //launched from GpanPropSwitchPage

BOOL from_test_play = 0;

BOOL launch_newgame_from_main;

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

var random_weather_change_frequency = 100;//frequency of weather change...the higher the value the less it changes
var random_weather_state_time = 40;//the higher the value the longer a weather state remains

var weather_state = 0;//start with good weather...1=rain, 2=snow

var rain_wind_x = 2, rain_wind_y = 1;
var rain_fallspeed = 25;

var snow_wind_x = 4, snow_wind_y = 2;
var snow_fallspeed = 4;
var snow_altitude = 160;//world-coord-z that enables snowfall (in quants)

var rain_random_move = 1;//strength of randomness on the particles x/y movement direction
var snow_random_move = 8;

var weather_fade_speed = 10;//fade-speed of weather change
var weather_soundfade_speed = 0.6;//fade-speed of weather-sound on weather changes

var disable_lightning_thunder = 0;//1=disables lightning-thunder
var lightning_frequency = 1.5;//random of 4000/lightning_frequency (wait)time
var lightning = 1;//x200...value to enlighten objects on ligtning strikes...use values 0.1-1

var trigg_num_off = 0;
var trigg_active_id = -1;

var weather_fader = 1;//just an additional fader var
var fog_col_trigg[3];
var fog_dist_near_trigg;
var fog_dist_far_trigg;
var vel_wind_rain_x;
var vel_wind_rain_y;
var vel_wind_snow_x;
var vel_wind_snow_y;

var stroke_area;//area of lightning stroke
var temporary;
var segment_length; // temporary length of the segment line
var stroke_length; // temporary length of the particle line
var current_color[3];
var lightning_on;

// lens_flare.c
var flare_alpha = 70;
var flare_fadespeed = 25;
var lens_active = 0, mystymood_active = 0;

BOOL dynamic_day_night = 1,
use_moon = 1,
use_bg_sounds = 1, //if 1, daytime ambiente background sounds are activated
use_random_weather = 1, //1= weather changes randomly
rain_random_move_on = 1, //1=on,0=off...sets randomness on the particles x/y movement direction
snow_random_move_on = 1,
rain_to_snow_on_altitude = 1;//1=rain morphes to snow when snow_altitude is reached

////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Panels will be declared here.
////////////////////////////////////////////////////////////
PANEL *Statistics,
*buttonlst,
*last_pan,
*panMain_Top,
*panMain_Bottom,
*panMain_Play,
*buttonlst_submenu_terrain,
*buttonlst_submenu_object,
*buttonlst_submenu_path,
*panHome,
*panProp,
*panProp_1,
*panProp_2,
*panProp_3,
*panMat_Sub1,
*panSnd,
*panParticle,
*panLight,
*panRotateHelp,
*panScaleHelp,
*panLightNoti,
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
*BackgroundScreen,
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
*CreateWorldCoffee;

////////////////////////////////////////////////////////////
// Entities will be declared here.
////////////////////////////////////////////////////////////
ENTITY *select, *fpsf_marker, *cam, *flashlight;

ENTITY *my_target_node;

ENTITY *ent_mystymood_trigg,
*sky_horizon,
*sky_cloud1,
*sky_cloud2,
*sky_cloud3,
*sky_day,
*sky_sun,
*sky_suncorona,
*sky_sunshine,
*sky_night,
*sky_moon,
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
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Vectors will be declared here.
////////////////////////////////////////////////////////////
VECTOR cpos1,cpos2,temp_pos;
VECTOR segment_start, segment_end;
VECTOR stroke_start, stroke_end;
VECTOR particle_seedbox;
VECTOR temp2, ctemp;
VECTOR TARGET;

// Vectors for dragging entities & camera movement
VECTOR v1, v2;
VECTOR *camera_force = { z = 0;
}

// Vectors for backup purposes
VECTOR xy_panLight, xy_panProp, xy_panSnd, xy_panParticle;

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
MATERIAL *mat_select, *mat_temp, *pTexColor;

// Predefined materials
MATERIAL *mat_lava, *mat_smaragd, *mat_marble,
*mat_lavenderrose, *mat_bitterlemon, *mat_peachorange,
*mat_purewhite, *mat_black, *mat_palelilac;

// Custom materials
MATERIAL *mat_custom[4];

////////////////////////////////////////////////////////////
// Sounds will be declared here.
////////////////////////////////////////////////////////////

SOUND *rain_wav = "rain.wav";
SOUND *wind_wav = "wind.wav";
SOUND *day_wav = "ambiente_day.wav";
SOUND *night_wav = "ambiente_night.wav";
SOUND *thunder1_wav = "thunder1.wav";
SOUND *thunder2_wav = "thunder2.wav";
SOUND *thunder3_wav = "thunder3.wav";
SOUND *thunder4_wav = "thunder4.wav";
SOUND *thunder5_wav = "thunder5.wav";

////////////////////////////////////////////////////////////
// Bitmap declarations
////////////////////////////////////////////////////////////
BMAP *BackgroundScreen1 = "BackgroundScreen1.jpg";
BMAP *BackgroundScreen2 = "BackgroundScreen2.jpg";
BMAP *BackgroundScreen3 = "BackgroundScreen1.jpg";
BMAP *BackgroundScreen4 = "BackgroundScreen2.jpg";
BMAP *BackgroundScreen5 = "BackgroundScreen1.jpg";
BMAP *BackgroundScreen6 = "BackgroundScreen2.jpg";

BMAP* mouse = "mouse_pointer.png";

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

BMAP *flag_PHY = "flag_PHY.bmp";
BMAP *flag_PHY_on = "flag_PHY_on.bmp";

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

BMAP *menu1_submenu1 = "button_loadfrom.bmp";
BMAP *menu1_submenu1_off = "button_loadfrom_off.bmp";
BMAP *menu1_submenu1_over = "button_loadfrom_over.bmp";

BMAP *menu1_submenu2 = "button_saveto.bmp";
BMAP *menu1_submenu2_off = "button_saveto_off.bmp";
BMAP *menu1_submenu2_over = "button_saveto_over.bmp";

BMAP *menu1_submenu3 = "button_brusht.bmp";
BMAP *menu1_submenu3_off = "button_brusht_off.bmp";
BMAP *menu1_submenu3_over = "button_brusht_over.bmp";

BMAP *menu1_submenu4 = "button_deformt.bmp";
BMAP *menu1_submenu4_off = "button_deformt_off.bmp";
BMAP *menu1_submenu4_over = "button_deformt_over.bmp";

BMAP *menu2_submenu1 = "button_addobject.bmp";
BMAP *menu2_submenu1_off = "button_addobject_off.bmp";
BMAP *menu2_submenu1_over = "button_addobject_over.bmp";

BMAP *menu2_submenu2 = "button_addevent.bmp";
BMAP *menu2_submenu2_off = "button_addevent_off.bmp";
BMAP *menu2_submenu2_over = "button_addevent_over.bmp";

//BMAP *menu2_submenu3 = "button_submenu2_3.bmp";
//BMAP *menu2_submenu4 = "button_submenu2_4.bmp";

BMAP *menu3_submenu1 = "button_addnode.bmp";
BMAP *menu3_submenu1_off = "button_addnode_off.bmp";
BMAP *menu3_submenu1_over = "button_addnode_over.bmp";

BMAP *menu3_submenu2 = "button_nodetype.bmp";
BMAP *menu3_submenu2_off = "button_nodetype_off.bmp";
BMAP *menu3_submenu2_over = "button_nodetype_over.bmp";

//BMAP *menu3_submenu3 = "button_submenu3_3.bmp";
//BMAP *menu3_submenu4 = "button_submenu3_4.bmp";

BMAP *panProp1_IMG = "panProp_1.bmp";
BMAP *panProp2_IMG = "panProp_2.bmp";
BMAP *panProp3_IMG = "panProp_3.bmp";

/*** For particle effects ***/
BMAP *point_blue_map = "point_blue.tga";
BMAP *sparkle1_map = "sparkle1.tga";
BMAP *fire3_map = "fire3.tga";
BMAP *fire1_map = "fire1.tga";
BMAP *blitz1_map = "blitz1.tga";
BMAP *star1_map = "star1.tga";

/*** For Mystymood ***/
BMAP *part_bmp_weather;
BMAP *bmp_rain = "rain.tga";
BMAP *bmp_snow = "snow.tga";
BMAP *bmp_lightning = "lightning.tga";    // change

////////////////////////////////////////////////////////////
// Function prototypes declarations
////////////////////////////////////////////////////////////
void OpenDebug();
void CloseDebug();
void ExitEvent();
void LoadKernel();
void LoopKernel();
void LoadPlayground();
void _beep();
int UnloadKernel();
int ReloadKernel();
int Console();
int PlayVideo(STRING *, var);
int SetupShader();
void FolderScan(TEXT *,STRING *,STRING *);
void LoadCBOIF(ENTITY *);

int AddToTextureProjectionArray(ENTITY *);
void RemoveFromTextureProjectionArray(ENTITY *);

// Implementation for writing different types of variables for WriteLog
// With somethin like int WriteLog(int); implement them yourself.
// or use somethin like WriteLog follow an empty string and var.
// Mother of function overloading.
int WriteLog(STRING *);
int WriteLog(STRING *, int);
int WriteLog(STRING *, var);
int WriteLog(STRING *, double);
int WriteLog(STRING *, BOOL);
int WriteLog(STRING *, OBJECTSTRUCT *);
int WriteLog(STRING *);
void NewLine();

void free_camera();
void toggle_weather();
void good_weather();

void GGUIInit();
void GGUIHide();
void GGUIShow();
void GGUIUpdate(PANEL *);

void guiViewPreset (int *, int, VECTOR *, VECTOR *);
void GPanelAlignMainMenu(PANEL *);
void GPanelCenterInside(PANEL *, PANEL *);
void GPanelResize(PANEL *, char);
void GPanelRotate(PANEL *,var,var,BOOL);
void GPanelSelect(PANEL *);
void GPanelCenter(PANEL *);
void GPanelDrag(PANEL *);
void GPanelFade(PANEL *, var, var, var);
void GPanelSizeForWH(PANEL *, BMAP *);
void GNotificationCreate(FONT *, STRING *);
void GWindowClose(var, PANEL *);

void GInsertObjectShow();
void GInsertObjectHide();
void GHomeShow();
void GMaterialEditorShow();
void GObjectSubmenuShow();
void GPathSubmenuShow();
void GSwitchToMoveMode();
void GSwitchToRotateMode();
void GSwitchToScaleMode();
void GLoadMainMenu();
void GPreMainMenu();
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
void GpanPropSwitchPage(var);
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

void GIO_ObjectTab_SwitchTab(var);
void GOptions_Graphics();
void GOptions_Sound();
void GOptions_Themes();
void GOptions_Maintenance();

void GSelectObject(var);
void GSelectLight(var);
void GSelectParticle(var);

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

int MaterialSelect(var);
void MaterialSave();

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

void func_particle_segment();
void func_lightning_effect();
void func_increase_brightness();
void weather_change();
void sky_day_fade_in();
void sky_day_state();
void sky_night_fade_in();
void sky_night_state();
void act_mystymood_trigg_label1();
void lensflare_create();
void lensflare_start();
void flare_init(ENTITY *);
void flare_place(ENTITY *);

void LoadNewLevel();
void LoadNewLevelFromWindow();
void LoadNewLevelFromMenuWindow();

//void LevelCleaner();
void TakeScreenshot();
void OptimizeFramerate(var);

void LoadMystymood(BOOL, BOOL); // This will load the Mystymood engine.
void LoadMystymoodLensflare();
void func_fade_colors(var *, var *, var *);
void func_particle_seed_infinity(PARTICLE *);
void func_effect_particle_seed(PARTICLE *);
void func_fade_lightning(PARTICLE *);
void func_particle_lightning(PARTICLE *);
void func_particle_segment();
void func_increase_brightness();
void weather_change();

// These are particle function prototypes, and were generated
// by 3rd party tools. So their names are a bit messed up.
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

#endif HEADER_H