/*
--------------------------------------------------
CBox.c

This file is responsible for setting up the environment
and calling the main modules.

TODO:
<+++


>+++

NOTES:
<+++

+ Milestone 5 release
- Integrated BoH_Havoc's shader library
- Integrated Xd1Vo's texture projection
- Separated the debug code (CBoxDebug.c) and shader code (CBoxShader.c).
- New prototype main menu, which will be improved over time.
- Fixed several bugs.
- A new method of accessing data was implemented -> shorter code, faster performance and allows external 3D contents to be plugged easier.
- Added command line parameters support.

List of things to do :
- Fix the bug related to rEntCount and the black bitmap after create_dxmat.
- Write various parameters to settings.cfg: settings for shaders, texture projection and such.
- Replace sound instructions' volumes by VOL_EFFECTS and VOL_MUSIC
- [X] Tweak the new player code.
- Finish the main menu prototype for further implementations.
- Take a look at the maze generation algorithm.
- Fix RemoveFromTextureProjectionArray(ENTITY *).
- Add support so that both mtl_pTex* and the colorful previously-defined materials can live happily together.
- [X] Appending log file instead of overwriting it.
- More detalied logging.
- Integrate the shader library from Slin's collection

Optimizations that need to be performed:
- Shade-C (for performance)
- Mystymood (for performance)
- RemoveFromTextureProjectionArray(ENTITY *) (for performance)
- Functions, variables, #define statements.

>+++
--------------------------------------------------
*/

#include "CBox8.c"

//////////////////////////////////////////////////////////////
#define PRAGMA_PATH "./src"
#define PRAGMA_PATH "./src/outside"
#define PRAGMA_PATH "./src/fx"

#define PRAGMA_PATH "./2d/gui"
#define PRAGMA_PATH "./2d/tex"
#define PRAGMA_PATH "./2d/sprites"

#define PRAGMA_PATH "./objects/sys"
#define PRAGMA_PATH "./objects/anms"
#define PRAGMA_PATH "./objects/arch"
#define PRAGMA_PATH "./objects/blands"
#define PRAGMA_PATH "./objects/chars"
#define PRAGMA_PATH "./objects/etc"
#define PRAGMA_PATH "./objects/food"
#define PRAGMA_PATH "./objects/machs"
#define PRAGMA_PATH "./objects/plants"
#define PRAGMA_PATH "./objects/tportts"

#define PRAGMA_PATH "./sounds"
#define PRAGMA_PATH "./sounds/music"

#define PRAGMA_PATH "./levels"
//////////////////////////////////////////////////////////////

#include "CBox.h"
#include "CBoxShader.c"
#include "CBoxCore.c"
#include "CBoxShell.c"
#include "CBoxDebug.c"

ENTITY *SkyCube = {
	
	type = "./2d/tex/s_s_greenland+6.tga";
	
	flags2 = SKY | CUBE | SHOW;
	
}

int num = 0;
var hndl;

void play() {
	
	if(media_playing(hndl)) {
		
		printf("I'm playing something");
		return;
		
	}
	
	if(!str_cmp((music_list.pstring)[num],"")) {
		
		STRING *parse = str_create("..\\sounds\\music\\");
		
		str_cat(parse,(music_list.pstring)[num]);
		str_cpy((music_list.pstring)[num],parse);
		
		hndl = media_play(parse,NULL,100);
		printf("%i",hndl);
		
		while(media_playing(hndl)) {
			
			if(key_n) {
				
				while(key_n) wait(1);
				num++;
				
				media_playing(hndl);
				
			}
			
			if(key_p) {
				
				while(key_p) wait(1);
				num--;
				
				media_playing(hndl);
				
			}
			
			wait(1);
			
		}
		
	}
	
}

void main(void)  {
	
	if( str_stri(command_str," -com") ) { // C_TRACE_OPTIMIZATION instead of DISTANCE_OPTIMIZATION
		
		C_TRACE_OPTIMIZATION = 1;
		DISTANCE_OPTIMIZATION = 0;
		
	}
	else { // Uses DISTANCE_OPTIMIZATION if -com isn't specified.
		
		DISTANCE_OPTIMIZATION = 1;
		C_TRACE_OPTIMIZATION = 0;
		
	}
	
	if( str_stri(command_str," -dev") ) { // Enable debugging + statistics, not implemented yet.
		
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
		
		//	
		//	on_t = UnloadKernel;
		//	
		//	txt_for_dir(music_list,str_create("./src/*.ogg"));
		//	
		//	set(music_list,SHOW);
		//	
		//	on_m = play;
		

	}
	
}