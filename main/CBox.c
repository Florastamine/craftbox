/*
--------------------------------------------------
CBox.c

This file is responsible for setting up the environment
and calling the main modules.

Written by Nguyen Ngoc Huy
https://github.com/ngochuy2101
http://craftboxdev.blogspot.com/

craftbox was written from scratch (just about 30 lines of code for codebase), in five months.

TODO:
<+++

Milestone 5.1:  C 91.6% | C++ 8.1% | Objective-C 0.3%
Milestone 6: C 95.8% | C++ 0.1% | Objective-C 4.1%

List of things to do :
- Fix the bug related to rEntCount and the black bitmap after create_dxmat.
- Write various parameters to FILE_CONFIG: settings for shaders, texture projection and such.
- Replace sound instructions' volumes by VOL_EFFECTS and VOL_MUSIC
- [X] Tweak the new player code.
- [X] Finish the main menu prototype for further implementations.
- Take a look at the maze generation algorithm.
- Fix RemoveFromTextureProjectionArray(ENTITY *).
- Add support so that both mtl_pTex* and the colorful previously-defined materials can live happily together.
- [X] Appending log file instead of overwriting it.
- [X] More detalied logging.
- Integrate the shader library from Slin's collection
- [X] Default config. in ConfigFileRead().
- [X] Fill int WriteLog(STRING *str, OBJECTSTRUCT *objectstruct).

Optimizations that need to be performed:
- Shade-C (for performance)
- Mystymood (for performance)
- RemoveFromTextureProjectionArray(ENTITY *) (for performance)
- Functions, variables, #define statements. (clear unnecessary vars, there are too many)

Code readibility: SUPER SUPER INCREDIBLY HELL NO I CAN'T READ IT-level

http://mp3.zing.vn/bai-hat/Silent-Hill-Promise-Reprise-Piano-Unknow/IW9OIZD6.html
http://mp3.zing.vn/album/Piano-Spa-In-Love-Mr-Tuk-Bo-Tree/ZWZACZFW.html?st=12
http://www.youtube.com/watch?v=evSwhNl-HhQ
http://mp3.zing.vn/bai-hat/Power-Kanye-West/ZWZA707C.html
http://mp3.zing.vn/bai-hat/Viva-la-Vida-Coldplay/ZW60CI7D.html
http://mp3.zing.vn/bai-hat/I-m-On-One-DJ-Khaled-ft-Drake-Rick-Ross/ZWZCCCU9.html
http://en.wikipedia.org/wiki/MIT_License
http://en.wikipedia.org/wiki/LGPL
http://en.wikipedia.org/wiki/List_of_colors_(compact)
http://www.woim.net/song/9727/trieu-doa-hoa-hong.html
http://www.woim.net/song/6102/late-autumn.html
http://www.woim.net/song/5029/flying-petals.html
http://www.woim.net/song/61506/im-here.html
http://naturesoundsfor.me/Snowstorm

>+++

NOTES:
<+++

1) 

Texture projection for:
- All types of normal entities (>Object && <=Object..)
- Custom terrains

Projection planes
- All types of players (but only one can be activated at a time).
- Neutral objects (ground planes for example), but not for PASSABLE entities. (like glass walls)

Static; can't be affected.
- Sky cube
- Pointer
- Sprite, sound, particle objects
- Nodes

2) ptr_first

>+++
--------------------------------------------------

*/

#include "./src/System/Craftbox.h"
#include "./src/System/Craftbox_System_Rendering.c"
#include "./src/System/Craftbox_System_Console.c"
#include "./src/System/Craftbox_System_Log.c"
#include "./src/System/Craftbox_System_Crypto.c"
#include "./src/System/Craftbox_System_Event.c"
#include "./src/System/Craftbox_System_Debug.c"
#include "./src/System/Craftbox_System_BootPoint.c"
#include "./src/System/Craftbox_System_Clipboard.c"
#include "./src/System/Craftbox_System_ExternalIO.c"
#include "./src/System/Craftbox_System_GameIO.c"
#include "./src/System/Craftbox_System_String.c"
#include "./src/System/Craftbox_System_Save_Load.c"
#include "./src/System/Craftbox_System_Scene.c"
#include "./src/System/Craftbox_System_Environment.c"
#include "./src/System/Craftbox_System_Object.c"
#include "./src/System/Craftbox_System_Material.c"
#include "./src/System/Craftbox_System_Default_Actor.c"
#include "./src/System/Craftbox_System_Playtest.c"
#include "./src/System/Craftbox_System_Interface.c"

#include "./src/Plugin/Craftbox_Plugin_Blackboard.c"
#include "./src/Plugin/Craftbox_Plugin_Music_Player.c"
#include "./src/Plugin/Craftbox_Plugin_Terrain_Deform.c"
#include "./src/Plugin/Craftbox_Plugin_Terrain_Seed.c"
#include "./src/Plugin/Craftbox_Plugin_Behaviors.c"
#include "./src/Plugin/Craftbox_Plugin_Dialogues.c"
#include "./src/Plugin/Craftbox_Plugin_Clock.c"
#include "./src/Plugin/Craftbox_Plugin_Slow_Motion.c"

void LineConnect(ENTITY *connector, ENTITY *connected)
{
	while(connector && connected)
	{
		draw_line3d(vector(connector.x, connector.y, connector.z), NULL, 100);
		draw_line3d(vector(connected.x, connected.y, connected.z), LineConnectColor, 100);
		
		wait (1);
	}

}


void p(){
   
   LineConnect(player, CameraLoc);
   
}

/*
--------------------------------------------------
void main(void)

Desc: Acts like a bootstrapper.

Returns: -
--------------------------------------------------
*/
void SaveMapDemo() {
	
	SaveWorld("test",1);
	
}

void Fill() {
	
	you = ent_next(NULL);
	while(you) {
		
		WriteObjectCustomSettings(you);
		while(proc_status (WriteObjectCustomSettings) ) wait(1);
		
		you = ent_next(you);
		
		wait(1);     
		
	}
	
}


void main(void)  {
	
	if( !str_stri(command_str,PARAM_NOLOGFILE) ) {
		
		LOGFILEHNDL = file_open_append(FILE_LOG);
		
		WriteLogHeaders();
		while(proc_status(WriteLogHeaders)) wait(1);
		
	}
	
	if( str_stri(command_str,PARAM_DEV) ) OpenDebug();
	if( str_stri(command_str,PARAM_SUSPENDKERNEL) ) Console();	
	else {
		
		LoadKernel();
		while(proc_status(LoadKernel)) wait(1);
		
		LoopKernel();
		
		on_p = Fill;
		on_k=p;
		
	}
	
	if( str_stri(command_str,PARAM_USECTRACE) ) {
		
		C_TRACE_OPTIMIZATION = 1;
		DISTANCE_OPTIMIZATION = 0;
		
	}
	
}