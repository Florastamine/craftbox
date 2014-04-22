/*
--------------------------------------------------
CBox.c

Initializes and loads craftbox.

Written by Nguyen Ngoc Huy
https://github.com/ngochuy2101
http://craftboxdev.blogspot.com/

craftbox was written from scratch (just about 30 lines of code for codebase).
By the way, this was my first game, so I've already prepared to be thrown and kicked out.

TODO:
<+++

+ New features/modifications
- [X] Appending log file instead of overwriting it.
- [X] More detalied logging.
- [X] Default config. in ConfigFileRead().
- [X] Tweak the new player code.
- [X] Finish the main menu prototype for further implementations.
- [X] Fill int WriteLog(STRING *str, OBJECTSTRUCT *objectstruct).
- Add support so that both mtl_pTex* and the colorful previously-defined materials can live happily together.
- Integrate the shader library from Slin's collection
- Write various parameters to FILE_CONFIG: settings for shaders, texture projection and such.
- Replace sound instructions' volumes by VOL_EFFECTS and VOL_MUSIC
- Replace & polish particle effect thumbnails (capture them real-time)
- Add node thumbnail into system objects
- Build a new ground (terrain) that makes use of craftbox's terrain editing feature.
- Re-build dry.wmb with higher tessellation and better lighting
- Object previewing before inserted into the scene (plus an additional panel LoadObjectThumb for handling preview image)
- On/off state for system objects.
- Add support for selectable, custom deformation data (normally from a file - contains terrain geometry data)
- Add a pathfinding system (node-based) for the AI
- Polish the menu background (new sky cube, better camera, terrain, water plane)
- Replace default dialogue image with something else (it's just a dummy image)
- Freeze game when a conversation is being shown.
- ShowMessage() (temporary name) - use DialogueInitialize() as basecode but shows a notification instead
- A generic compass plus AllowCompass var.
- Splash screen
- [X] Options for switching on and off SSAO, HDR, DOF plus options for screenspace effects and such
- Integrate Shade-C EVO v1.1 (heavier but can be switched off at any time)
- Support for Oculus Rift
- Help system
- -1 gives a guess and creates a new GraphicsSettingsStruct struct in GraphicsSettingsStruct *CreateGraphicsStruct(int..)
- Implement SetDefaultGraphicsSettings().

+ Bugs to fix
- Fix the bug related to rEntCount and the black bitmap after create_dxmat.
- Fix RemoveFromTextureProjectsc_view_hdrVBlurionArray(ENTITY *).
- Fix object copying error (passing from and to clipboard), wrong name for example?
- Fix .cboif bug
- Fix and add support for Unicode text encryption and decryption (Craftbox_System_Crypto.c)
- Fix the "invisible light" bug after dragging
- Fix "Trophies" screen

+ Optimizations
- Shade-C (for performance)
- Mystymood (for performance)
- RemoveFromTextureProjectionArray(ENTITY *) (for performance)
- Functions, variables, #define statements. (clear unnecessary vars, there are too many)
- Optimize menu background (default texture for unseen parts; replace textures; more details such as doors, trees, books...)

+ System entities:
- Force field (hurt)
- Force field (kill instantly)
- Cutscene / Play video trigger zone
- Level changing zone plus extra effects (and/or in combination with other trigger zones)
- Skybox changing zone
- Fog adjustment/fade zone
- "Music player controller" trigger
- Slow down/speed up the scene
- Modify terrain geometry trigger
- Spawn conversations/notifications/entities (for x seconds?)

>+++

NOTES:
<+++


>+++
--------------------------------------------------

*/

#include "./Source/Craftbox.h"

//#include "./Source/Craftbox_System_Math.c"
#include "./Source/Craftbox_System_Rendering.c"
#include "./Source/Craftbox_System_Console.c"
#include "./Source/Craftbox_System_Log.c"
//#include "./Source/Craftbox_System_Crypto.c"
#include "./Source/Craftbox_System_Event.c"
#include "./Source/Craftbox_System_Debug.c"
#include "./Source/Craftbox_System_BootPoint.c"
#include "./Source/Craftbox_System_Clipboard.c"
#include "./Source/Craftbox_System_ExternalIO.c"
#include "./Source/Craftbox_System_GameIO.c"
#include "./Source/Craftbox_System_String.c"
//#include "./Source/Craftbox_System_Save_Load.c"
//#include "./Source/Craftbox_System_Scene.c"
#include "./Source/Craftbox_System_Environment.c"
#include "./Source/Craftbox_System_Object.c"
//#include "./Source/Craftbox_System_Material.c"
#include "./Source/Craftbox_System_Default_Actor.c"
#include "./Source/Craftbox_System_Playtest.c"
#include "./Source/Craftbox_System_Interface.c"

#include "./Source/Plugin/Craftbox_Plugin_Blackboard.c"
#include "./Source/Plugin/Craftbox_Plugin_Music_Player.c"
#include "./Source/Plugin/Craftbox_Plugin_Terrain_Deform.c"
#include "./Source/Plugin/Craftbox_Plugin_Terrain_Seed.c"
#include "./Source/Plugin/Craftbox_Plugin_Behaviors.c"
#include "./Source/Plugin/Craftbox_Plugin_Dialogues.c"
#include "./Source/Plugin/Craftbox_Plugin_Clock.c"
#include "./Source/Plugin/Craftbox_Plugin_Slow_Motion.c"

/*--------------------------------------------------
Main function
--------------------------------------------------*/
void main(void)  {
	
	if( !str_stri(command_str,PARAM_NOLOGFILE) ) OpenLog( "log.log" );
	
	#ifdef CBOX_SPLASHSCREENS
		GameSplash ();
		while( proc_status( GameSplash ) ) wait(1);	
	#endif
	
	LoadKernel();
	while(proc_status(LoadKernel)) wait(1);
	
	LoopKernel();
	
}