/*
--------------------------------------------------
CBoxDebug.c

Contains debug & statistics code, which can be toggled using the -dev 
parameter.

TODO:
<+++



>+++

NOTES:
<+++

-

>+++
--------------------------------------------------
*/

FONT *TFont = "Arial#25b";
var first, FPS;

PANEL *Statistics = {
	
	layer = 999;

	digits(0,0,99,TFont,1,manip_type); // v_objectz
	digits(0,20,99,TFont,1,TEMP_OBJECT_TYPE);
	
}

PANEL *Framerate = {

	layer = 999;
	digits(0,0,99,"Arial#25b",1,FPS);

}

void toggle_weather()//just for testing
{
	weather_state += 1;
	if(weather_state > 2) weather_state = 0;
}

void good_weather()  { weather_state = 0; }

/*
--------------------------------------------------
void OpenDebug()


--------------------------------------------------
*/
void OpenDebug() {
	
	if(!is(Statistics,SHOW)) set(Statistics,SHOW);
	
	Framerate.pos_x = screen_size.x - 50;
	Framerate.pos_y = BORDER;
	
	if(!is(Framerate,SHOW)) set(Framerate,SHOW);
	
	if (!on_f2) on_f2 = def_save;
	if (!on_f3) on_f3 = def_load;
	if (!on_f4) on_f4 = def_video;
	if (!on_f5) on_f5 = def_shot;
	if (!on_f6) on_f6 = def_debug;
	if (!on_f7) on_f7 = capture_cubemap; // Not useable yet!
	
	if (!on_enter) on_enter = def_screen;
	if (!on_grave) on_grave = def_console;
	
	//		if (!on_close) on_close = def_exit;
	
	while(1) {
	   
	   first = total_frames;
	   wait(-1);
	   FPS = total_frames - first;
	   
	   wait(1);
	   
	}
	
}

/*
--------------------------------------------------
void CloseDebug()


--------------------------------------------------
*/
void CloseDebug() {
	
	pan_remove(Statistics);
	
	// If CloseDebug() was called somewhere else in the program
	if(on_f2) on_f2 = NULL;
	if(on_f3) on_f3 = NULL;
	if(on_f4) on_f4 = NULL;
	if(on_f5) on_f5 = NULL;
	if(on_f6) on_f6 = NULL;
	if(on_f7) on_f7 = NULL;
	
	if(on_enter) on_enter = NULL;
	if(on_grave) on_grave = NULL;
	
}