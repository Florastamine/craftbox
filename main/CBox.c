/*
--------------------------------------------------
CBox.c

This file is responsible for setting up the environment
and calling the main modules.

craftbox was written from scratch (just about 30 lines of code for codebase), in five months.

TODO:
<+++

Milestone 5.1:  C 91.6% | C++ 8.1% | Objective-C 0.3%

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

Desc: Acts like a bootstrapper.

Returns: -
--------------------------------------------------
*/

void slow() {
	
	while(time_factor>0) {
		
		time_factor -= .01;
		
		DEBUG_VAR(time_factor,100);
		
		wait(1);
		
	}
	
}

void main(void)  {
	
	max_particles = 100000;
	
	if( !str_stri(command_str," -dwl") ) { // Do not output logfiles.
		
		LOGFILEHNDL = file_open_append(FILE_LOG);
		
		WriteLogHeaders(); // Write header information
		while(proc_status(WriteLogHeaders)) wait(1);
		
	}
	
	if( str_stri(command_str," -dev") ) { // Enable debugging + statistics, not fully implemented yet
		
		OpenDebug();
		
	}
	
	if( str_stri(command_str," -dlk") ) { // -dlk: Do not load the kernel
		
		Console();
		
	}
	
	else {
		
		LoadKernel();
		while(proc_status(LoadKernel)) wait(1);
		
		LoopKernel();
		
		on_p=slow;
	}
	
	if( str_stri(command_str," -com") ) { // C_TRACE_OPTIMIZATION instead of DISTANCE_OPTIMIZATION
		
		C_TRACE_OPTIMIZATION = 1;
		DISTANCE_OPTIMIZATION = 0;
		
	}
	
}