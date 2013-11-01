/*
--------------------------------------------------
CBox.c

This file is responsible for setting up the environment
and calling the main modules.

craftbox was written from scratch (just about 30 lines of code for codebase), in five months.

TODO:
<+++

+ Milestone 5.1 release
- Integrated BoH_Havoc's shader library
- Integrated Xd1Vo's texture projection
- Separated the debug code (CBoxDebug.c) and shader code (CBoxShader.c).
- New prototype main menu, which will be improved over time.
- Fixed several bugs.
- A new method of accessing data was implemented -> shorter code, faster performance and allows external 3D contents to be plugged easier.
- Added command line parameters support.
- ...

List of things to do :
- Fix the bug related to rEntCount and the black bitmap after create_dxmat.
- Write various parameters to settings.cfg: settings for shaders, texture projection and such.
- Replace sound instructions' volumes by VOL_EFFECTS and VOL_MUSIC
- [X] Tweak the new player code.
- [X] Finish the main menu prototype for further implementations.
- Take a look at the maze generation algorithm.
- Fix RemoveFromTextureProjectionArray(ENTITY *).
- Add support so that both mtl_pTex* and the colorful previously-defined materials can live happily together.
- [X] Appending log file instead of overwriting it.
- More detalied logging.
- Integrate the shader library from Slin's collection
- Default config. in ConfigFileRead().
- Fill int WriteLog(STRING *str, OBJECTSTRUCT *objectstruct).

Optimizations that need to be performed:
- Shade-C (for performance)
- Mystymood (for performance)
- RemoveFromTextureProjectionArray(ENTITY *) (for performance)
- Functions, variables, #define statements. (clear unnecessary vars, there are too many)

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

#include "CBox8.c"
#include "CBox.h"
#include "CBoxShader.c"
#include "CBoxCore.c"
#include "CBoxShell.c"
#include "CBoxScratch.c"
#include "CBoxDebug.c"

/*
--------------------------------------------------
void main(void)

Desc:

Returns: -
--------------------------------------------------
*/
void main(void)  {
	
	if( str_stri(command_str," -com") ) { // C_TRACE_OPTIMIZATION instead of DISTANCE_OPTIMIZATION
		
		C_TRACE_OPTIMIZATION = 1;
		DISTANCE_OPTIMIZATION = 0;
		
	}
	
	if( str_stri(command_str," -dev") ) { // Enable debugging + statistics, not fully implemented yet
		
		OpenDebug();
		
	}
	
	if( !str_stri(command_str," -dwl") ) { // Do not output logfiles.
		
		LOGFILEHNDL = file_open_append(FILE_LOG);
		
		NewLine();
		
		WriteLog("-- Log file opened at ");
		WriteLog("",sys_hours);
		WriteLog(": ",sys_minutes);
		WriteLog(": ",sys_seconds);
		WriteLog(",",sys_day);
		WriteLog("/ ",sys_month);
		WriteLog("/ ",sys_year);
		NewLine();
		
		switch(sys_winversion) {
			
			/*
			
			Range:
			1 - Windows 98 SE
			2 - Windows ME
			3 - Windows 2000
			4 - Windows 2003
			5 - Windows XP 
			6 - Windows Vista or above 
			
			*/
			
			case 1: WriteLog("Windows 98/98SE detected."); break;
			case 2: WriteLog("Windows ME detected."); break;
			case 3: WriteLog("Windows 2000 detected."); break;
			case 4: WriteLog("Windows 2003 detected."); break;
			case 5: WriteLog("Windows XP detected."); break;
			case 6: WriteLog("Windows Vista/7/8 detected."); break;
			default: WriteLog("Linux or another operating system detected."); break;
			
		}
		
		NewLine();
		
		WriteLog("Allocated memory: ",sys_memory*1024);
		WriteLog("KB");
		NewLine();
		
	}
	
	if( str_stri(command_str," -dlk") ) { // -dlk: Do not load the kernel
		
		Console();
		
	}
	
	else {
		
		LoadKernel();
		while(proc_status(LoadKernel)) wait(1);
			
		LoopKernel();
		
	}
	
}