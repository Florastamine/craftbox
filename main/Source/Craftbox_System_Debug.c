/*
--------------------------------------------------
Craftbox_System_Debug.c

Provides all the necessary stuff when working with 
craftbox under development mode.

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

FONT *TFont = "Arial#25b";
var first, FPS;

PANEL *Statistics = {
	
	layer = 999;

	digits(0,0,99,TFont,1,manip_type); // v_objectz
	digits(0,20,99,TFont,1,TEMP_OBJECT_TYPE);
	
}

VIEW* viewMap = 
{
	flags = WIREFRAME | NOCULL; 
	layer = 1; 
	roll = 270; 
	tilt = -90; 
	arc = 10; 
}

PANEL* def_debug_pan = 
{
	pos_x = 5; 
	pos_y = 5; 
	layer = 998;

	digits(0,2,"%4.0fx","Arial#14b",1,screen_size.x);
	digits(30,2,"%.0f","Arial#14b",1,screen_size.y);
	digits(0,12,"fps%5.0f","Arial#14b",16,def_dfps);
	digits(0,22,"pps%5.0fk","Arial#14b",0.016,def_dtps);
	digits(0,32,"x%7.0f","Arial#14b",1,camera.x);
	digits(0,42,"y%7.0f","Arial#14b",1,camera.y);
	digits(0,52,"z%7.0f","Arial#14b",1,camera.z);
	digits(0,62,"pan%5.0f","Arial#14b",1,def_cang.pan);
	digits(0,72,"til%5.0f","Arial#14b",1,def_cang.tilt);
	digits(0,82,"rol%5.0f","Arial#14b",1,def_cang.roll);

	digits(65,2,"ms/frame","Arial#14b",0,0);
	digits(65,12,"geo%5.1f","Arial#14b",1,def_dtlv);
	digits(65,22,"ent%5.1f","Arial#14b",1,time_entities);
	digits(65,32,"par%5.1f","Arial#14b",1,time_effects);
	digits(65,42,"drw%5.1f","Arial#14b",1,time_draw);
	digits(65,52,"pan%5.1f","Arial#14b",1,time_panels);
	digits(65,62,"ref%5.1f","Arial#14b",1,def_dtrf);
	digits(65,72,"srv%5.1f","Arial#14b",1,def_dtcs);
	digits(65,82,"fnc%5.1f","Arial#14b",1,def_dtac);

	digits(130,2,"count of","Arial#14b",0,0);
	digits(130,12,"ent%5.0f","Arial#14b",1,num_entities);
	digits(130,22,"vis%5.0f","Arial#14b",1,num_visents);
	digits(130,32,"tri%5.0fk","Arial#14b",0.001,num_vistriangles);
	digits(130,42,"par%5.0f","Arial#14b",1,num_particles);
	digits(130,52,"lit%5.0f","Arial#14b",1,num_lights);
	digits(130,62,"snd%5.0f","Arial#14b",1,def_dsnd);
	digits(130,72,"fnc%5.0f","Arial#14b",1,num_actions);
	digits(130,82,"bdy%5.0f","Arial#14b",1,num_bodies);

	digits(200,2,"memory MB","Arial#14b",0,0);
	digits(200,12,"nex%5.0f","Arial#14b",1,nexus);
	digits(200,22,"mem%5.0f","Arial#14b",1,sys_memory);
	digits(200,32,"geo%5.0f","Arial#14b",1,d3d_texsurfs);
	digits(200,42,"shd%5.0f","Arial#14b",1,d3d_texsmaps);
	digits(200,52,"ent%5.0f","Arial#14b",1,d3d_texskins);
	digits(200,62,"fre%5.0f","Arial#14b",1,d3d_texfree);
}

TEXT* def_dtxt = {
	pos_x = 2; pos_y = 2; layer = 999;
	string = watch_str;
	flags = SHOW;
}

void def_box(var x1,var y1,var x2,var y2,VECTOR* color)
{
	draw_line(vector(x1,y1,0),NULL,100);
	draw_line(vector(x2,y1,0),color,100);
	draw_line(vector(x2,y2,0),color,100);
	draw_line(vector(x1,y2,0),color,100);
	draw_line(vector(x1,y1,0),color,100);
}

void def_debug() 
{
	if(key_alt) 
	{ 
		diag_status(); 
		return; 
	}
	
	if(key_shift) 
	{
		diag_status();
		freeze_mode = !freeze_mode;
		
		if (freeze_mode) {
			
			def_oldmouse = mouse_mode;
			mouse_mode = 4;
			mouse_pointer = 2;
			
		} 
		else mouse_mode = def_oldmouse;
		
		while (freeze_mode) {
			if(mouse_left) watched = mouse_ent;
			wait(1);
		}
		return;
	}

	if (key_ctrl) {
		toggle(viewMap,SHOW);
		while is(viewMap,SHOW) {
			vec_set(&viewMap->x,&camera->x);
			viewMap->z += 10000;
			wait(1);
		}
		return;
	}
	
	if(d3d_lines) {
		reset(def_debug_pan,SHOW);
		d3d_lines = 0;
		diag_mode &= ~1;
		} else {
		if is(def_debug_pan,SHOW) {
			d3d_lines = 3;
			} else {
			set(def_debug_pan,SHOW);
			diag_mode |= 1;
			while is(def_debug_pan,SHOW) {
				def_dfps = 0.9*def_dfps+0.1/time_frame;
				def_dtps = 0.9*def_dtps+0.1*num_vistriangles/time_frame;
				def_dtlv = time_level+time_sky;
				def_dtcs = time_client+time_server;
				def_dtrf = time_update+time_idle;
				def_dtac = time_actions+time_pfuncs;
				def_dsnd = num_mediastreams + num_sounds;
				def_cang.pan = cycle(camera->pan,0,360); 
				def_cang.tilt = cycle(camera->tilt,-180,180); 
				def_cang.roll = cycle(camera->roll,-180,180); 
				def_box(def_debug_pan->pos_x-3,def_debug_pan->pos_y-2,
				def_debug_pan->pos_x+314,def_debug_pan->pos_y+103,
				vector(255,255,255));
				
				wait(1);
			}
		}
	}
}

void def_shot() 
{ 
	file_for_screen("shot_",def_shot_num); 
	def_shot_num++; 
}

void def_save() { game_save(app_name,1,SV_ALL-SV_INFO); }
void def_load() { game_load(app_name,1); }

void def_video() 
{
	var mode = video_mode;
	while(1) 
	{
		if (!key_shift)  mode++; 
		else mode--;
		
		mode = cycle(mode,6,12); 
		GGUIInit();
		
		if (video_switch(mode,0,0)) break;
	}
}

void def_screen() 
{
	if (!key_alt) 
	return;
	var mode = video_screen + 1;
	if (mode > 2) 
	mode = 1;
	if(!video_switch(0,0,mode)) {
		
		printf("This video mode is not supported.");
		
	}
}

void def_console() /* ~ */
{
	def_ctxt->pos_x = 2;
	def_ctxt->pos_y = screen_size.y/4;
	toggle(def_ctxt,SHOW);
	while is(def_ctxt,SHOW) {
		inkey((def_ctxt->pstring)[1]);
		if (13 == result) {
			void* found = var_for_name((def_ctxt->pstring)[1]);
			if (!found) execute((def_ctxt->pstring)[1]);
		} else
		reset(def_ctxt,SHOW);
	}
}

void write8(var bte) // write char
{ file_asc_write(fh_n, bte); }

void write16(var shrt) // write unsigned short
{
	file_asc_write(fh_n, shrt&255);
	file_asc_write(fh_n, (shrt>>8)&255);
}

void str_padding(STRING *str, var number, var padding)
{
	str_for_num(_ts_, number);
	var i = 0;
	i = padding - str_len(_ts_);
	while(i > 0)
	{
		str_cat(str, "0");
		i-=1;
	}
	str_cat(str, _ts_);
}

void write_cubemap()
{
	var i;
	var xx;
	var yy;
	var format;
	var pixel;
	var pixelalpha;
	VECTOR canvas_size;
	VECTOR temp;

	canvas_size.x = bmap_width(b_render1);
	canvas_size.y = bmap_height(b_render1);
	format = bmap_lock(b_render1, 0);
	bmap_lock(b_render2, 0);
	bmap_lock(b_render3, 0);
	bmap_lock(b_render4, 0);
	bmap_lock(b_render5, 0);
	bmap_lock(b_render6, 0);

	str_cpy(tempstring1,"cubemap");
	str_padding(tempstring1, cubenumber, 4);
	str_cat(tempstring1, "+6.tga");
	fh_n = file_open_write(tempstring1);
	
	cubenumber+=1;
	//--------------------------------------------------------write header
	write8(0);
	write8(0);
	write8(2); // image type
	write16(0);
	write16(0);
	write8(0);
	write16(0);
	write16(0);
	write16(canvas_size.x * 6); // width
	write16(canvas_size.y); // height
	write8(24); // color depth
	write8(0);
	//--------------------------------------------------------write image data
	yy = canvas_size.y - 1;
	while(yy >= 0)
	{
		i = 0;
		while(i < 6)
		{
			if(i==0) canvas=b_render1;
			if(i==1) canvas=b_render2;
			if(i==2) canvas=b_render3;
			if(i==3) canvas=b_render4; 
			if(i==4) canvas=b_render5; 
			if(i==5) canvas=b_render6; 
			xx = 0;
			while(xx < canvas_size.x)
			{
				pixel = pixel_for_bmap(canvas, xx, yy);
				pixel_to_vec(temp, pixelalpha, format, pixel);
				write8(temp.x); // b
				write8(temp.y); // g
				write8(temp.z); // r
				xx+=1;
			}
			i+=1;
		}
		yy-=1;
	}
	file_close(fh_n);
	bmap_unlock(b_render1);
	bmap_unlock(b_render2);
	bmap_unlock(b_render3);
	bmap_unlock(b_render4);
	bmap_unlock(b_render5);
	bmap_unlock(b_render6);
}

//----------------------------------------------------------------------------- capture_cubemap
void capture_cubemap()
{
	var old_arc;
	var old_x;
	var old_y;
	var old_screen;

	b_render1 = bmap_create("render.tga"); // use a 256x256 tga for example -> determines cube map size
	b_render2 = bmap_create("render.tga");
	b_render3 = bmap_create("render.tga");
	b_render4 = bmap_create("render.tga");
	b_render5 = bmap_create("render.tga");
	b_render6 = bmap_create("render.tga");

	old_arc = camera.arc;
	old_x = screen_size.x;
	old_y = screen_size.y;
	old_screen = video_screen;

	camera.arc = 90;
	video_set(256, 256, 0, 2); // should be same resolution as render.tga

	freeze_mode = 1;
	
	vec_set(camera.pan, directions[0]); wait(1); bmap_for_screen(b_render1,0,0);
	vec_set(camera.pan, directions[3]); wait(1); bmap_for_screen(b_render2,0,0);
	vec_set(camera.pan, directions[6]); wait(1); bmap_for_screen(b_render3,0,0);
	vec_set(camera.pan, directions[9]); wait(1); bmap_for_screen(b_render4,0,0);
	vec_set(camera.pan, directions[12]); wait(1); bmap_for_screen(b_render5,0,0);
	vec_set(camera.pan, directions[15]); wait(1); bmap_for_screen(b_render6,0,0);
	
	freeze_mode = 0;

	wait(1);
	write_cubemap();

	wait(1);
	camera.arc = old_arc;
	video_set(old_x, old_y, 0, old_screen);
}

/*
--------------------------------------------------
void OpenDebug()


--------------------------------------------------
*/
void OpenDebug() {
	
	if(!is(Statistics,SHOW)) set(Statistics,SHOW);
	
	//	if(run_mode < 8) warn_level = 6;
	
	if (!on_f2) on_f2 = def_save;
	if (!on_f3) on_f3 = def_load;
	if (!on_f4) on_f4 = def_video;
	if (!on_f5) on_f5 = def_shot;
	if (!on_f6) on_f6 = def_debug;
	//	if (!on_f7) on_f7 = capture_cubemap; // Not useable yet!
	//	if (!on_h) on_h = toggleSsaoState;
	
	if (!on_enter) on_enter = def_screen;
	if (!on_grave) on_grave = def_console;
	
	//		if (!on_close) on_close = def_exit;
	
	DEBUG_MODE = 1;
	
	while(1) {
		
		//	   draw_text(")
		
		//		DEBUG_VAR(moon_scale_fac,10);
		//		DEBUG_VAR(time_speed_night,30);
		//		DEBUG_VAR(time_speed,50);
		//		DEBUG_VAR(night_sky_scale_x,70);
		//		DEBUG_VAR(night_sky_speed_x,90);
		//		DEBUG_VAR(sun_grow_z,110);
		//		DEBUG_VAR(TerrainEditMode,50);
		//		
		first = total_frames;
		wait(-1);
		FPS = total_frames - first;
		
		DEBUG_VAR(FPS,20);
		
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
	//	if(on_f7) on_f7 = NULL;
	//	if(on_h) on_h = NULL;
	
	if(on_enter) on_enter = NULL;
	if(on_grave) on_grave = NULL;
	
}