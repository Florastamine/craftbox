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
- Tweak the new player code.
- Finish the main menu prototype for further implementations.
- Take a look at the maze generation algorithm.
- Fix RemoveFromTextureProjectionArray(ENTITY *).
- Add support so that both mtl_pTex* and the colorful previously-defined materials can live happily together.
- Appending log file instead of overwriting it.
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



var fpsec;
var init_frames;

PANEL* framerate_pan  =//Zeige mir die Entity Anzahl /--\ Framerate/sek /--\ Polycount
{

       pos_x = 100; //820
       pos_y = 0; //740
       layer = 20;
       digits(350, 0,7,"Arial#20",1, fpsec);  //FPS 
       digits(350,30,7,"Arial#20",1,num_visentpolys); //POLYS
       digits(350,60,7,"Arial#20",1,num_visents); //ENTITYS    
       flags = OVERLAY | SHOW;
}

TEXT* info_txt = 
{
		 font = "Arial#20";
       layer = 20; 
       pos_x = 300;
       pos_y = 0;
       string("FPS","Polygone","Entitys");
       flags = SHOW;

}

function set_fpsmax_startup()
{

       while (1)
       {
               
               init_frames = total_frames;
               wait(-1);
               fpsec = total_frames - init_frames;
               
               if(fpsec<=200 && fpsec>=51)
               {
               framerate_pan.red=60;
               framerate_pan.green=200;
               framerate_pan.blue=60;	
					}               
               
               if(fpsec>=31 && fpsec<=50)
               {
               framerate_pan.red=255;
               framerate_pan.green=190;
               framerate_pan.blue=80;	
					}
					
               if(fpsec<30)
               {
               framerate_pan.red=255;
               framerate_pan.green=0;
               framerate_pan.blue=0;	
					}
               
               wait(1);

       }

}


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
		
		file_str_write(LOGFILEHNDL,"-- Log file opened at ");
		file_var_write(LOGFILEHNDL,sys_hours);
		file_str_write(LOGFILEHNDL,":");
		file_var_write(LOGFILEHNDL,sys_minutes);
		file_str_write(LOGFILEHNDL,":");
		file_var_write(LOGFILEHNDL,sys_seconds);
		NewLine();
		NewLine();
		
	}
	
	if( str_stri(command_str," -dlk") ) { // -dlk: Do not load the kernel
		
		Console();
		
	}
	else {
	   
	   SetupShader();
		
		LoadKernel();
		wait_for(LoadKernel);
		
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

action wter(){
   set(my,PASSABLE);
   sc_water(me);
}