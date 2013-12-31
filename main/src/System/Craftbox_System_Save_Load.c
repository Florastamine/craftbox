/*
--------------------------------------------------
void LoadWorld(STRING *level, int id) 

Desc:

Returns: -
--------------------------------------------------
*/
void LoadWorld(STRING *level, int id) {
	
	if( !str_len(level) || str_cmp(level,undef) ) {
		
		return;
		
	}

	if(id<0) {
		
		return;
		
	}
	
	// LoadWorld's caller has to supply the full path, we don't do the joining stuff :>
	var loadhndl = file_open_read(level);
	
	if(!loadhndl) {
		
		return;
		
	}
	
	STRING *content = "#400";
	
	// Load a blank level first
	level_load("dry_original.wmb");
	while(proc_status(level_load)) wait(1);

	//	GGUIShow();
	//	while(proc_status(GGUIShow)) wait(1);
	file_str_readto(loadhndl,NULL,strseparate_end,100); // Search for the first ']' character (mark the header)
	file_str_readto(loadhndl,NULL,strseparate_end,200); // Serach for the second ']' character
	/*
	file_str_write(filehndl,strseparate_start);
	file_str_write(filehndl,tag_header_warn);
	file_str_write(filehndl,strseparate_end);
	NewLineGeneric(filehndl);
	NewLineGeneric(filehndl);
	
	file_str_write(filehndl,strseparate_start);
	file_str_write(filehndl,tag_system_header);
	file_str_write(filehndl,strseparate_end);
	NewLineGeneric(filehndl);
	
	file_str_write(filehndl,wdstart); // Mark the start point
	file_var_write(filehndl,BBTranslucency); // <- Get last transparency
	
	file_var_write(filehndl,bSize); // <- These are for the terrain editor
	file_var_write(filehndl,tMaxHeight);
	file_var_write(filehndl,sizeh);
	file_var_write(filehndl,brush_speed);
	file_var_write(filehndl,TerrainEditMode);
	file_var_write(filehndl,bType);
	file_var_write(filehndl,bHeight);
	file_var_write(filehndl,bHlimit);
	
	file_var_write(filehndl,StatsIsRunning); // <- Stats panel
	file_var_write(filehndl,CountObjects);
	file_var_write(filehndl,CountParticles);
	file_var_write(filehndl,CountLights);
	file_var_write(filehndl,CountSounds);
	file_var_write(filehndl,CountSprites);
	file_var_write(filehndl,CountTotal);
	
	file_var_write(filehndl,ToggleSnow); // <- Used to determine if weather had been enabled before	
	file_var_write(filehndl,ToggleRain);
	
	file_var_write(filehndl,camera.x); // <- Write camera position
	file_var_write(filehndl,camera.y);
	file_var_write(filehndl,camera.z);
	file_var_write(filehndl,camera.pan);
	file_var_write(filehndl,camera.tilt);
	file_var_write(filehndl,camera.roll);
	file_var_write(filehndl,camera.aspect);
	file_var_write(filehndl,camera.arc);
	file_var_write(filehndl,camera.ambient);
	
	file_var_write(filehndl,cam.x); // <- just to make sure
	file_var_write(filehndl,cam.y);
	file_var_write(filehndl,cam.z);
	file_var_write(filehndl,cam.pan);
	file_var_write(filehndl,cam.tilt);
	file_var_write(filehndl,cam.roll);
	
	file_str_write(filehndl,strseparate_start); // <- Write SKYSTR
	file_str_write(filehndl,SKYSTR);
	file_str_write(filehndl,strseparate_end);
	
	file_str_write(filehndl,strseparate_start); // <- Write GROUNDSTR
	file_str_write(filehndl,GROUNDSTR);
	file_str_write(filehndl,strseparate_end);
	
	file_var_write(filehndl,sun_light);
	file_var_write(filehndl,camera.clip_far);
	file_var_write(filehndl,camera.clip_near);
	
	SaveWorld_system(filehndl); // Stage 1
	while(proc_status(SaveWorld_system)) wait(1);
	
	SaveWorld_geodata(filehndl); // Stage 2
	while(proc_status(SaveWorld_geodata)) wait(1);
	
	SaveWorld_objectdata(filehndl); // Final stage (aka boss)
	while(proc_status(SaveWorld_objectdata)) wait(1);
	
	file_close(filehndl);
	*/
	
}

/*
--------------------------------------------------
void SaveWorld_system(var hndl) 

Desc:

Returns: -
--------------------------------------------------
*/
void SaveWorld_system(var hndl) {
	
	if(!hndl) {
		
		WriteLog("!! [ERROR] There was an error when trying to write system data. Aborting...");
		
		return;
		
	}
	
	wait(1);
	
	if(WorldType == WORLD_DYNAMIC) {
		
		file_var_write(hndl,lens_active);
		file_var_write(hndl,mystymood_active);
		file_var_write(hndl,dynamic_day_night);
		
		file_var_write(hndl,_use_moon);
		file_var_write(hndl,_use_sun);
		file_var_write(hndl,_use_nightstars);
		file_var_write(hndl,_weather_mode);
		
		file_var_write(hndl,sun_angle.pan);
		file_var_write(hndl,sun_angle.tilt);
		file_var_write(hndl,sun_angle.roll);
		file_var_write(hndl,sun_color.red);
		file_var_write(hndl,sun_color.green);
		file_var_write(hndl,sun_color.blue);
		//		file_var_write(hndl,sun_grow_z);
		//		file_var_write(hndl,sun_azimuth);
		//		file_var_write(hndl,sun_elevation);
		//		file_var_write(hndl,sun_col_fac);
		//		file_var_write(hndl,max_zenith);
		
		file_var_write(hndl,sky_color.red);
		file_var_write(hndl,sky_color.green);
		file_var_write(hndl,sky_color.blue);
		
		file_var_write(hndl,night_sky_scale_x);
		file_var_write(hndl,night_sky_scale_y);
		file_var_write(hndl,night_sky_speed_x);
		file_var_write(hndl,night_sky_speed_y);
		file_var_write(hndl,moon_scale_fac);
		
		file_var_write(hndl,time_speed);
		file_var_write(hndl,time_speed_night);
		//		file_var_write(hndl,fog_fade_speed); // <- Implement these options later
		//		file_var_write(hndl,sky_fade_speed);
		//		file_var_write(hndl,weather_fade_speed);		
		//		file_var_write(hndl,flare_alpha);
		//		file_var_write(hndl,flare_fadespeed);
		
		int i = 0;
		for(;i<3;i++) file_var_write(hndl,fog_mor[i]);
		for(i=0;i<3;i++) file_var_write(hndl,fog_day[i]);
		for(i=0;i<3;i++) file_var_write(hndl,fog_eve[i]);
		for(i=0;i<3;i++) file_var_write(hndl,fog_night[i]);
		for(i=0;i<3;i++) file_var_write(hndl,fog_dynamic_day_night_off[i]);
		for(i=0;i<3;i++) file_var_write(hndl,fog_weather_day[i]);
		for(i=0;i<3;i++) file_var_write(hndl,fog_weather_night[i]);
		for(i=0;i<3;i++) file_var_write(hndl,current_color[i]);
		
		
	}
	else { // Static world
		
		// Static world uses only 1 COLOR struct so save that struct only is enough. 
		file_var_write(hndl,d3d_fogcolor1.red);
		file_var_write(hndl,d3d_fogcolor1.green);
		file_var_write(hndl,d3d_fogcolor1.blue);
		
		file_var_write(hndl,camera.fog_start);
		file_var_write(hndl,camera.fog_end);
		
		file_var_write(hndl,fog_color);
		
	}
	
	file_str_write(hndl,wdend); // Mark the end point
	NewLineGeneric(hndl);
	NewLineGeneric(hndl);
	
}


/*
--------------------------------------------------
void SaveWorld_geodata(var hndl)

Desc:

Returns: -
--------------------------------------------------
*/
void SaveWorld_geodata(var hndl) {
	
	if(!hndl) {
		
		return;
		
	}
	
	file_str_write(hndl,strseparate_start);
	file_str_write(hndl,tag_geodata);
	file_str_write(hndl,strseparate_end);
	NewLineGeneric(hndl);
	
	file_str_write(hndl,wdstart); // Mark the start point
	
	if( TerrainEnt) TDeform_saveterrain( TerrainEnt ); // Save 'em directly without using that ent_next
	else file_str_write(hndl,gdundef); // Indicating that there's no terrain entity available
	
	file_str_write(hndl,wdend);
	NewLineGeneric(hndl);
	NewLineGeneric(hndl);
	
}

/*
--------------------------------------------------
void SaveWorld_objectdata(var hndl)

Desc:

Returns: -
--------------------------------------------------
*/
void SaveWorld_objectdata(var hndl) {
	
	if(!hndl) {
		
		return;
		
	}
	
	file_str_write(hndl,strseparate_start);
	file_str_write(hndl,tag_objectdata);
	file_str_write(hndl,strseparate_end);
	NewLineGeneric(hndl);
	
	file_str_write(hndl,wdstart); // Mark start
	
	you = ent_next(NULL);
	
	while(you != NULL) {
		
		file_str_write(hndl,openent);
		
		file_str_write(hndl,strseparate_start);
		file_str_write(hndl, you->type );
		file_str_write(hndl,strseparate_end);
		
		file_var_write(hndl,you.x);
		file_var_write(hndl,you.y);
		file_var_write(hndl,you.z);
		file_var_write(hndl,you.pan);
		file_var_write(hndl,you.tilt);
		file_var_write(hndl,you.roll);
		file_var_write(hndl,you.alpha);
		file_var_write(hndl,you.ambient);
		file_var_write(hndl,you.albedo);
		file_var_write(hndl,you.red);
		file_var_write(hndl,you.green);
		file_var_write(hndl,you.blue);
		
		file_var_write(hndl,is(you,BRIGHT) );
		file_var_write(hndl,is(you,SHOW));
		file_var_write(hndl,is(you,NOFOG)) ;
		file_var_write(hndl,is(you,OVERLAY)) ;
		file_var_write(hndl,is(you,PASSABLE) );
		file_var_write(hndl,is(you,POLYGON));
		file_var_write(hndl,is(you,SHADOW));
		file_var_write(hndl,is(you,TRANSLUCENT) );
		
		int i = 0;
		for(;i<MAX_PUBLIC_SKILLS + MAX_PRIVATE_SKILLS;i++) file_var_write(hndl,you.skill[i]);
		
		file_str_write(hndl,closeent);
		
		you = ent_next(you);
		
	}
	
	file_str_write(hndl,wdend); // Mark end
	
}

/*
--------------------------------------------------
void SaveWorld(STRING *name, int slot)

Desc:

Returns: -
--------------------------------------------------
*/
void SaveWorld(STRING *name, int slot) {
	
	if( !str_len(name) || str_cmp(name,undef) ) {
		
		return;
		
	}
	
	if( !IN_GAME || slot<0 ) {
		
		return;
		
	}
	
	STRING *_name = "#500"; // prevent modification
	var stripos;
	
	str_cpy(_name,PATH_SAVEDGAMES);
	str_cat(_name,name);
	
	stripos = str_stri(name,dot);
	if( str_stri(name,dot) && stripos==str_len( name ) ) wait(.1);
	else str_cat(_name,dot);
	
	str_cat(_name,EXT_SAVEDGAMES);
	
	var filehndl = file_open_write(_name);
	if(!filehndl) {
		
		return;
		
	}
	
	// Write global data here ->
	file_str_write(filehndl,strseparate_start);
	file_str_write(filehndl,tag_header);
	file_str_write(filehndl,strseparate_end);
	NewLineGeneric(filehndl); /* write a new line */
	NewLineGeneric(filehndl);
	
	file_str_write(filehndl,strseparate_start);
	file_str_write(filehndl,tag_header_warn);
	file_str_write(filehndl,strseparate_end);
	NewLineGeneric(filehndl);
	NewLineGeneric(filehndl);
	
	file_str_write(filehndl,strseparate_start);
	file_str_write(filehndl,tag_system_header);
	file_str_write(filehndl,strseparate_end);
	NewLineGeneric(filehndl);
	
	file_str_write(filehndl,wdstart); // Mark the start point
	file_var_write(filehndl,BBTranslucency); // <- Get last transparency
	
	file_var_write(filehndl,bSize); // <- These are for the terrain editor
	file_var_write(filehndl,tMaxHeight);
	file_var_write(filehndl,sizeh);
	file_var_write(filehndl,brush_speed);
	file_var_write(filehndl,TerrainEditMode);
	file_var_write(filehndl,bType);
	file_var_write(filehndl,bHeight);
	file_var_write(filehndl,bHlimit);
	
	file_var_write(filehndl,StatsIsRunning); // <- Stats panel
	file_var_write(filehndl,CountObjects);
	file_var_write(filehndl,CountParticles);
	file_var_write(filehndl,CountLights);
	file_var_write(filehndl,CountSounds);
	file_var_write(filehndl,CountSprites);
	file_var_write(filehndl,CountTotal);
	
	file_var_write(filehndl,ToggleSnow); // <- Used to determine if weather had been enabled before	
	file_var_write(filehndl,ToggleRain);
	
	file_var_write(filehndl,camera.x); // <- Write camera position
	file_var_write(filehndl,camera.y);
	file_var_write(filehndl,camera.z);
	file_var_write(filehndl,camera.pan);
	file_var_write(filehndl,camera.tilt);
	file_var_write(filehndl,camera.roll);
	file_var_write(filehndl,camera.aspect);
	file_var_write(filehndl,camera.arc);
	file_var_write(filehndl,camera.ambient);
	
	file_var_write(filehndl,cam.x); // <- just to make sure
	file_var_write(filehndl,cam.y);
	file_var_write(filehndl,cam.z);
	file_var_write(filehndl,cam.pan);
	file_var_write(filehndl,cam.tilt);
	file_var_write(filehndl,cam.roll);
	
	file_str_write(filehndl,strseparate_start); // <- Write SKYSTR
	file_str_write(filehndl,SKYSTR);
	file_str_write(filehndl,strseparate_end);
	
	file_str_write(filehndl,strseparate_start); // <- Write GROUNDSTR
	file_str_write(filehndl,GROUNDSTR);
	file_str_write(filehndl,strseparate_end);
	
	file_var_write(filehndl,sun_light);
	file_var_write(filehndl,camera.clip_far);
	file_var_write(filehndl,camera.clip_near);
	
	SaveWorld_system(filehndl); // Stage 1
	while(proc_status(SaveWorld_system)) wait(1);
	
	SaveWorld_geodata(filehndl); // Stage 2
	while(proc_status(SaveWorld_geodata)) wait(1);
	
	SaveWorld_objectdata(filehndl); // Final stage (aka boss)
	while(proc_status(SaveWorld_objectdata)) wait(1);
	
	file_close(filehndl);
	
}


/*
--------------------------------------------------
int SaveGameToSlot(var slot)

Desc:

Returns: -1 if a stage fails.
--------------------------------------------------
*/
int SaveGameToSlot(var slot) {

	if(event_type == EVENT_RELEASE) return;
	
	/*
	
	...
	
	*/

}

/*
--------------------------------------------------
int LoadGameFromSlot(var slot)

Desc:

Returns: -1 if operation fails.
--------------------------------------------------
*/
int LoadGameFromSlot(var slot) {

	if(event_type == EVENT_RELEASE) return;
	
	/*
	
	...
	
	*/
	
}