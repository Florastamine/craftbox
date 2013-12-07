
/*
--------------------------------------------------
kernel.c

This file contains all the ingredients for making
up the kernel. Actions' functions will also be placed
here. Please note that this file contains ONLY 
kernel-related code, GUI/HUD code is placed separately
in shell.c.

Written by Nguyen Ngoc Huy
https://github.com/ngochuy2101
http://craftboxdev.blogspot.com/

TODO:
<+++



>+++

NOTES:
<+++

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

- Objects
- Sounds
- Particles
- Lights
- Sprites (Decals)
- Terrains
- Nodes

>+++
--------------------------------------------------
*/

/*
--------------------------------------------------
var ent_seed_c(

char* name, // entity filename
ENTITY* terrain, // ground entity
BMAP* mask,	  // color mask
COLOR* color, // target color 
var dist,	// average distance between entities
EVENT act

)

Desc: A custom variation of ent_seed.

Returns: The same as ent_seed.
--------------------------------------------------
*/
var ent_seed_c(

char* name, // entity filename
ENTITY* terrain, // ground entity
BMAP* mask,	  // color mask
COLOR* color, // target color 
var dist,	// average distance between entities
EVENT act

)	// entity action
{
	if(!name || !color) return 0;
	if(!terrain) terrain = level_ent;
	if(!mask) mask = ent_getskin(terrain,1);
	if(!mask) return 0;
	
	var width = bmap_width(mask);
	var height = bmap_height(mask);
	float fdx = PIXEL_DX(terrain,mask);
	float fdy = PIXEL_DY(terrain,mask);

	var i,j,n=0;
	float fnum = 0;
	float fdist = dist;
	var format = bmap_lock(mask,0);
	var pixel = pixel_for_vec(color,NULL,format);
	// check all pixels of the mask, and plant entities on all pixels with the right color
	for(j=0; j<height; j++)
	for(i=0; i<width; i++)
	{
		// right mask color?		
		if(pixel != pixel_for_bmap(mask,i,j)) continue;
		// accumulate the probability for an entity per pixel   	
		fnum += fdx/fdist*fdy/fdist;
		while(fnum > random(1))
		{  	 
			ENTITY* ent = ent_create(name,NULL,act);
			if (!ent) return 0;
			// calculate random position within the size of the terrain pixel
			vec_set(&ent->x,terrain_pixel_to_pos(terrain,i,j,mask) + 50);
			ent->x += random(fdx);
			ent->y += random(fdy) + 50;
			// put it on the terrain height at that place
			ent_place_z(ent,terrain_height(terrain,&ent->x)-2);		
			// reduce the placement probability for the next pixel	  	
			fnum -= random(2);
			n++;
		}
	} 
	bmap_unlock(mask);
	return n;
}

/*
--------------------------------------------------
void PerformSeed()

Desc: Starts the seeding process.

Returns: -
--------------------------------------------------
*/
void PerformSeed() {
	
	if(event_type == EVENT_RELEASE) return;
	
	STRING *tempTERRAINSEEDBMAP = "#400";
	
	str_cpy( tempTERRAINSEEDBMAP, TerrainEnt->type );
	str_cat(tempTERRAINSEEDBMAP,SEEDMASKDATA);
	str_cat( tempTERRAINSEEDBMAP, ".tga");
	
	if( file_exists(tempTERRAINSEEDBMAP) ) {
		
		if(is(canvas_pan,SHOW)) reset(canvas_pan,SHOW);
		if(is(seedPanelCover,SHOW)) reset(seedPanelCover,SHOW);
		
		var def = collision_mode;
		collision_mode = 0; // Entities are created faster this way.
		
		if( str_len(seedEnt) && !str_cmp(seedEnt,undef) && !str_cmp((seedEnt->chars)[0],"") ) ent_seed_c(seedEnt,TerrainEnt,bmap_create(tempTERRAINSEEDBMAP),current_color2,15,SeedEntCore);
		while(proc_status(ent_seed_c)) wait(1);
		
		collision_mode = def;
		
		mark_seedEntstr = 0;
		
	}
	
}

/*
--------------------------------------------------
void SeedEntCore()

Desc: Core function for each seeded entity,

Returns: -
--------------------------------------------------
*/
void SeedEntCore() {
	
	my.flags |= PASSABLE; 
	my.flags &= ~(POLYGON | DYNAMIC);
	my.ObjectType = SeedEnt;
	
	my.pan = random(360);
	Scale(my,5);
	
}

/*
--------------------------------------------------
void RemoveSeedEnts()

Desc: Removes all seeded entities in the entity chain.

Returns: -
--------------------------------------------------
*/
void RemoveSeedEnts() {
	
	proc_mode = PROC_NOFREEZE;
	
	if(event_type == EVENT_RELEASE) return;
	
	freeze_mode = 2;
	
	you = ent_next(NULL);
	while(you != NULL) {
		
		if(you.ObjectType == SeedEnt) ptr_remove(you);
		you = ent_next(you);
		
	}
	
	freeze_mode = 0;

}

/*
--------------------------------------------------
void RecreateSeedMap()

Desc:

Returns: -
--------------------------------------------------
*/
void RecreateSeedMap() {
	
	if(event_type == EVENT_RELEASE) return;
	
	ptr_remove(canvas_paint);
	while( proc_status(ptr_remove) ) wait(1);
	canvas_paint = bmap_create("tskin.tga");
	
}

/*
--------------------------------------------------
void SeedEntSelector()

Desc:

Returns: -
--------------------------------------------------
*/
void SeedEntSelector() {
	
	if(event_type == EVENT_RELEASE) return;
	
	STRING *oldTEMPSTR = str_create(TEMPSTR);
	
	GInsertObjectShow();
	while(proc_status( GInsertObjectShow )) wait(1);
	
	while( ! mark_seedEntstr ) wait(1); // Wait until something is selected
	
	if( !str_cmp(TEMPSTR,undef) ) {
		
		str_cpy(seedEnt,TEMPSTR);
		str_cpy(TEMPSTR,oldTEMPSTR);
		
	}
	
}

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
void NewLineGeneric(var hndl)

Desc:

Returns: -
--------------------------------------------------
*/
void NewLineGeneric(var hndl) {
	
	if(!hndl) return;
	file_asc_write(hndl,13);
	file_asc_write(hndl,10);
	
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
void place_mesh_on_ground(ENTITY* _ent, int _dist)

Desc:
By PadMalcom (http://www.opserver.de/ubb7/ubbthreads.php?ubb=showflat&Number=425689#Post425689)

Returns: -
--------------------------------------------------
*/
void place_mesh_on_ground(ENTITY* _ent, int _dist) {
	
	var nVertexCount = ent_status(_ent, 0);
	var i;
	VECTOR* vecTemp;
	CONTACT* c;
	for (i=1; i<=nVertexCount; i++) {
		c = ent_getvertex(_ent, NULL, i);
		if (c != NULL) {
			if(c_trace(	vector(c.v.x, c.v.z, c.v.y + 1024),
			vector(c.v.x, c.v.z, c.v.y - 1024),
			IGNORE_MODELS | IGNORE_SPRITES | IGNORE_PASSABLE | IGNORE_PASSENTS | USE_POLYGON))
			{
				c.v.y = target.z+_dist;
			}
			ent_setvertex(_ent, c, i);
		}
	}
}

/*
--------------------------------------------------
int range(x,y,z)

Desc:

Returns: -
--------------------------------------------------
*/
int range(x,y,z) {
	z+=y;
	if(x >= y && x <= z) return 1;
	return 0;
}

/*
--------------------------------------------------
COLOR *CopyColor(var r, var g, var b)

Desc:

Returns: -
--------------------------------------------------
*/
COLOR *CopyColor(var r, var g, var b) {
	
	WriteLog("[ ] Copying COLOR* struct...");
	NewLine();
	
	COLOR *ret;
	ret.red = abs(r);
	ret.green = abs(g);
	ret.blue = abs(b);
	
	WriteLog("[X] Task completed.");
	NewLine();
	
	return ret;
	
}

/*
--------------------------------------------------
void TDeform_changeBrushSingle()

Desc:

Returns: -
--------------------------------------------------
*/
//void TDeform_changeBrushSingle() { bType = B_SIBGLE; }

/*
--------------------------------------------------
void TDeform_changeBrushMultiple()

Desc:

Returns: - 
--------------------------------------------------
*/
//void TDeform_changeBrushMultiple() { bType = B_MULT;	}

/*
--------------------------------------------------
void TDeform_changeBrushMultipleSmooth()

Desc:

Returns: -
--------------------------------------------------
*/
//void TDeform_changeBrushMultipleSmooth() { bType = B_MULT_SMOOT; }

/*
--------------------------------------------------
void TDeform_changeBrushRaise()

Desc:

Returns: -
--------------------------------------------------
*/
void TDeform_changeBrushRaise() {
	
	if(event_type == EVENT_RELEASE) return;
	
	if( button_state(TerrainToolbar,2,-1)) button_state(TerrainToolbar,2,0); // The lower button
	bHeight = DEF_UPPER;
	
}

/*
--------------------------------------------------
void TDeform_changeBrushLower()

Desc:

Returns: -
--------------------------------------------------
*/
void TDeform_changeBrushLower() {
	
	if(event_type == EVENT_RELEASE) return;
	
	if (button_state(TerrainToolbar,1,-1)) button_state(TerrainToolbar,1,0); // The raise button
	bHeight = DEF_LOWER;
	
}

/*
--------------------------------------------------
void on_level_event(percent)

Desc: A modified version of the on_level_event that is shown in the 3D Gamestudio manual.

Returns: -
--------------------------------------------------
*/
void on_level_event(percent)
{
	
	set(pLoadBar,SHOW | LIGHT);   // switch load bar on
	pLoadBar.pos_y = screen_size.y - 40;
	pLoadBar.size_x = GetPercent( percent,100 ) * screen_size.x/100; // because max percent = 100
	pLoadBar.size_y = 30;
	
	if (percent >= 100) reset(pLoadBar,SHOW);
	pLoadBar.size_x = 0;
	
}

/*
--------------------------------------------------
void TDeform_single()

Desc: Deform Single Vertex, no smooth

Returns: -
--------------------------------------------------
*/
void TDeform_single()
{

	proc_kill(4);

	var vertex_number = ent_nextvertex(my,temp_pos);
	CONTACT* c = ent_getvertex(my,NULL,vertex_number);     
	
	if(bHeight == DEF_UPPER)
	{
		c.z += sizeh * brush_speed;  // increase the vertex height
		c.v = NULL;
		if(c.z <= tMaxHeight) ent_setvertex(my,c,vertex_number);     // update the mesh
		
		else if(bHlimit)
		{
			c.z=tMaxHeight;
			ent_setvertex(my,c,vertex_number);     // update the mesh		
		}
	}
	else if(bHeight == DEF_LOWER)
	{
		c.z -= sizeh * brush_speed;  // increase the vertex height
		c.v = NULL; 
		if(c.z >= 0) ent_setvertex(my,c,vertex_number);     // update the mesh
		else if(bHlimit)
		{	
			c.z=0;
			ent_setvertex(my,c,vertex_number);    // update the mesh		
		}
		
	}

}

/*
--------------------------------------------------
void TDeform_multiple()

Desc:Deform Multiple Vertex no smooth

Returns: -
--------------------------------------------------
*/
void TDeform_multiple()
{

	proc_kill(4);
	proc_mode = PROC_EARLY;
	
	VECTOR vertex_pos;
	int ping=1;

	CONTACT* c;    

	while(ping <= ent_status(TerrainEnt,1))
	{	 		
		vec_for_vertex(vertex_pos,TerrainEnt,ping);	
		
		if(vec_dist(vertex_pos,temp_pos)<=bSize)
		{
			c = ent_getvertex(TerrainEnt,NULL,ping);
			
			if(bHeight == DEF_UPPER)
			{
				c.z += sizeh * brush_speed;  // increase the vertex height
				c.v = NULL;
				
				
				
				if(c.z <= tMaxHeight) ent_setvertex(my,c,ping);    			// update the mesh					
				else if(bHlimit)
				{
					c.z = tMaxHeight;
					ent_setvertex(my,c,ping);    			// update the mesh					
					
				}
			}
			else if(bHeight == DEF_LOWER)
			{
				
				c.z -= sizeh * brush_speed;  // increase the vertex height
				c.v = NULL;
				
				if(c.z >= 0) ent_setvertex(my,c,ping);    			// update the mesh					
				else if(bHlimit)
				{
					c.z = 0;
					ent_setvertex(my,c,ping);    			// update the mesh					
					
				}
				
				
				
			}
		}		
		ping +=1;				
	}

}

/*
--------------------------------------------------
void TDeform_multipleSmooth()

Desc: Deform multiple vertices with smooth

Returns: -
--------------------------------------------------
*/
void TDeform_multipleSmooth()
{

	proc_kill(4);
	proc_mode = PROC_EARLY;

	int ping=1;
	VECTOR vertex_pos;
	CONTACT* c;

	while(ping <= ent_status(TerrainEnt,1))
	{	
		vec_for_vertex(vertex_pos,TerrainEnt,ping);			
		
		if(vec_dist(vertex_pos,temp_pos)<=bSize)
		{	
			
			c = ent_getvertex(my,NULL,ping);
			
			if(bHeight == DEF_UPPER)
			{	
				
				c.z += (sizeh/vec_dist(vertex_pos,temp_pos)) * brush_speed;
				c.v = NULL;			
				
				if(c.z <= tMaxHeight) ent_setvertex(my,c,ping);   		 	// update the mesh			
				else if(bHlimit)
				{
					c.z = tMaxHeight;
					c.v = NULL;			
					ent_setvertex(my,c,ping);
				}
			}
			else if(bHeight == DEF_LOWER)
			{
				c.z -= (sizeh/vec_dist(vertex_pos,temp_pos)) * brush_speed;
				c.v = NULL;			
				
				if(c.z >= 0) ent_setvertex(my,c,ping);   		 	// update the mesh			
				else if(bHlimit)
				{
					c.z = 0;
					c.v = NULL;			
					ent_setvertex(my,c,ping);
				}
				
			}
			
			
			
		}			
		ping +=1;		
		
	}	
}

/*
--------------------------------------------------
void TDeform_saveterrain(ENTITY *terrain)

Desc:

Returns: -
--------------------------------------------------
*/
void TDeform_saveterrain(ENTITY *terrain)
{
	
	proc_kill(4);
	
	WriteLog("[ ] Saving terrain data to ");
	
	while(!terrain) wait(1);
	
	STRING *savestr = "#400";
	
	str_cpy(savestr,terrain->type ); // 4 = ".hmp";
	str_cat(savestr,TERRAINDATA);
	str_cat(savestr,".txt");
	
	WriteLog(savestr);
	WriteLog(", please wait.");
	NewLine();
	
	var terrainHandle = file_open_write(savestr);
	if(!terrainHandle) {
		
		WriteLog("!! [ERROR] Cannot open ");
		WriteLog(savestr);
		WriteLog(" for writing terrain geometry data. Operation aborted.");
		NewLine();
		
		return;
		
	}
	
	VECTOR mesh_coords;
	var index = 0;
	while(index <= total_vertices) // go through all the vertices
	{
		vec_for_mesh(mesh_coords.x, terrain, index); // and get their z coordinates		
		file_var_write(terrainHandle,mesh_coords.z);
		
		index++;
	}
	
	var _size = file_length(terrainHandle)*1024; // original in bytes, convert to KBs
	
	file_close(terrainHandle);
	
	WriteLog("[X] Task completed, file size: ");
	WriteLog(_size);
	NewLine();
	
}

/*
--------------------------------------------------
void TDeform_LoadHeightFrom(ENTITY *terrain)

Desc:

Returns: -
--------------------------------------------------
*/
void TDeform_LoadHeightFrom(ENTITY *terrain) {
	
	proc_kill(4);
	
	WriteLog("[ ] Attempting to load terrain data from ");
	
	while(!terrain) wait(1);
	
	STRING *loadstr = "#400";
	
	str_cpy(loadstr,terrain->type);
	str_cat(loadstr,TERRAINDATA);
	str_cat(loadstr,".txt");
	
	WriteLog(loadstr);
	WriteLog(", please wait.");
	NewLine();

	if(file_exists(loadstr))  // previously saved data exists?
	{
		
		var terrainHandle = file_open_read(loadstr);
		
		var index = 0;
		while(index <= total_vertices) // then load the previously stored height values and apply them to the terrain
		{
			// no need to load the x and y coordinates of the terrain - they can't be changed
			vec_to_mesh(vector (0, 0, file_var_read(terrainHandle) ), terrain, index);
			index += 1;
			
		}
		
		file_close(terrainHandle);
		} else {
		
		WriteLog("Failed to open ");
		WriteLog(loadstr);
		WriteLog(" for passing geometry data to terrain. Operation aborted.");
		NewLine();
		
	}
	
	WriteLog("[X] Task completed.");
	NewLine();
	
}

/*
--------------------------------------------------
STRING *StringForBool(var in)

Desc: This was created specifically for WriteLogHeaders()...

Returns: Converted input.
--------------------------------------------------
*/
STRING *StringForBool(var in) {
	
	if(in) return str_create("Yes");
	else return str_create("No");
	
}

/*
--------------------------------------------------
void WriteLogHeaders()

Desc: 

Returns: -
--------------------------------------------------
*/
void WriteLogHeaders() {
	
	// couldn't use plugins here so I just evaluate some 3D Gamestudio's variables.
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
	
	WriteLog("Graphic card shader version (PSVS): ");
	WriteLog( str_for_num(str_create( d3d_shaderversion ), d3d_shaderversion ) );
	
	NewLine();
	
	WriteLog("Graphic card features: ");
	NewLine();
	
	WriteLog("Hardware T&L: "); WriteLog( StringForBool(d3d_caps & 1) ); NewLine();
	WriteLog("Stencil shadows: "); WriteLog( StringForBool(d3d_caps & 4) ); NewLine();
	WriteLog("Compressed textures: "); WriteLog( StringForBool(d3d_caps & 8) ); NewLine();
	
	WriteLog("Higher features: ");
	WriteLog(StringForBool(d3d_caps & 16));
	WriteLog(",");
	WriteLog(StringForBool(d3d_caps & 32));
	
	NewLine();	
}


/*
--------------------------------------------------
int GetPercent(var consumed, var total)

Desc: Calculate the percent (%) based on "consumed" and "total".

Returns: Percent (%).
--------------------------------------------------
*/
int GetPercent(var consumed, var total) {
	
	return (abs(consumed)*100)/abs(total);
	
}

/*
--------------------------------------------------
void ConvertToCTFormat(STRING *dest, var TrackVariable, var TotalVariable )

Desc: Takes TrackVariable and TotalVariable as input, convert them into 
the following format:

"(TrackVariable/TotalVariable) (% used) "

then sends the result back to dest.

Call it once to let dest be static, or place in a loop 
to dynamically update dest based on TrackVariable and TotalVariable's changes.

This is very useful, f.e. you don't have to define several texts for numbers/strings/symbols, and align them manually, which is very ugly and time-consuming.

Returns: -
--------------------------------------------------
*/
void ConvertToCTFormat(STRING *dest, var TrackVariable, var TotalVariable ) {
	
	STRING *s = "#400";
	
	str_for_num(dest,TrackVariable);
	str_cat(dest,"/");
	str_cpy(s,dest);
	
	s = str_for_num(s,TotalVariable);
	str_cat(dest,s);
	str_cat(dest," (");
	
	s = str_for_int(s,GetPercent(TrackVariable,TotalVariable));
	str_cat(dest,s);
	str_cat(dest,"%)");
	
	
}

/*
--------------------------------------------------
void WriteToBlackboard(STRING *str, STRING *str2, var duration) 

Desc:

Returns: -
--------------------------------------------------
*/
void WriteToBlackboard(STRING *str, STRING *str2, var duration) {
	
	if(proc_status(WriteToBlackboard)) return; // avoid proc_kill(4).
	
	WriteLog("[ ] Writing to blackboard -> ");
	
	var dy = BORDER * 2; // adjust the destination y here
	
	if(!str_len (str) && !str_len(str2) ) {
		
		WriteLog("empty");
		NewLine();
		
		return;
		
	}
	
	TEXT *notistr = txt_create(2,1);
	while(proc_status( txt_create )) wait(1);
	
	Blackboard->pos_x = BORDER;
	Blackboard->pos_y = -bmap_height(Blackboard->bmap);
	
	notistr->font = font_create("Arial#23b");
	notistr->pos_x = Blackboard.pos_x + BORDER;
	notistr->pos_y = Blackboard.pos_y + BORDER*2.5;
	layer_sort(notistr,Blackboard->layer+1);
	
	str_cpy( (notistr.pstring) [0], str);
	str_cpy( (notistr.pstring) [1], str2);
	
	set(Blackboard,SHOW);
	set(notistr,SHOW);
	
	Blackboard->alpha = 0;
	
	while(Blackboard->pos_y <= dy ) {
		
		Blackboard->pos_y += 25 * time_step;
		notistr->pos_y = Blackboard->pos_y;
		Blackboard->alpha = GetPercent(Blackboard->pos_y, dy);
		
		wait(1);
		
	}
	
	wait(- abs(duration) );
	
	while(Blackboard->pos_y >= -bmap_height(Blackboard->bmap) ) {
		
		Blackboard->pos_y -= 25 * time_step;
		notistr->pos_y = Blackboard->pos_y;
		
		Blackboard->alpha = 100 - GetPercent(Blackboard->pos_y, -bmap_height(Blackboard->bmap) );
		
		wait(1);
		
	}
	
	reset(Blackboard,SHOW);
	reset(notistr,SHOW);
	
	str_remove( (notistr.pstring) [0] );
	str_remove( (notistr.pstring) [1] );
	txt_remove(notistr);
	
	NewLine();
	WriteLog("[X] Task completed.");
	
}

/*
--------------------------------------------------
void ToggleMusicPlayer()

Desc:

Returns: -
--------------------------------------------------
*/
void ToggleMusicPlayer() {
	
	if(is(MusicPlayer,SHOW)) {
		
		reset(MusicPlayer,SHOW);
		reset(MusicPlayerInfo,SHOW);
		
		return;
		
	}
	
	set(MusicPlayer,SHOW);
	set(MusicPlayerInfo,SHOW);
	
	while(is(MusicPlayer,SHOW)) {
		
		MusicPlayerInfo.pos_x = MusicPlayer.pos_x + 170;
		MusicPlayerInfo.pos_y = MusicPlayer.pos_y + 130;
		
		wait(1);
		
	}	
}

/*
--------------------------------------------------
void mpLoad(STRING *scan_path, STRING *scan_ext)

Desc:

Returns: -
--------------------------------------------------
*/
void mpLoad(STRING *scan_path, STRING *scan_ext) {
	
	WriteLog("[ ] Scanning for external music...");
	
	STRING *_scan_path = str_create(scan_path); // Prevent modification of the original string
	
	mpSongs = txt_for_dir(mpPool, str_cat(_scan_path,scan_ext) );
	while(proc_status(txt_for_dir)) wait(1);
	
	str_remove(_scan_path);
	
	WriteLog(", found " , (var) mpSongs ); // 
	WriteLog(" tracks.");
	NewLine();
	
	WriteLog("[X] Task completed.");
	NewLine();
	
}

/*
--------------------------------------------------
void mpPlay(STRING *songName)

Desc:

Returns: -
--------------------------------------------------
*/
void mpPlay(STRING *songName) {
	
	WriteLog("[ ] Now playing: ");
	
	if(media_playing(mpHandle)) media_stop(mpHandle);
	if(mpCount > mpSongs - 1 || mpCount < 0) return;
	
	str_cpy(_mpSongTemp,songName);
	str_trunc(_mpSongTemp, str_len(EXT_MUSIC)-1 ); // because our four chars are: .ogg
	
	WriteLog(_mpSongTemp);
	NewLine();
	
	str_cpy(mpSongTemp,PATH_MUSIC);
	str_cat(mpSongTemp,songName);
	
	str_for_num(_mpCount, mpCount); // strcpy is unnecessary here
	
	mpHandle = media_play(mpSongTemp,NULL,VOL_MUSIC);
	
	while(media_playing(mpHandle)) wait(1);
	mpNext();
	
}

/*
--------------------------------------------------
void mpNext() 

Desc:

Returns: -
--------------------------------------------------
*/
void mpNext() {
	
	if(event_type == EVENT_RELEASE) return;
	
	if(mpCount < mpSongs) {
		
		if(mpRandomize) mpCount = (int) random(mpSongs);
		else mpCount += 1;
		mpPlay( (mpPool.pstring)[mpCount] );
		
	}
	
}

/*
--------------------------------------------------
void mpPrev()

Desc:

Returns: -
--------------------------------------------------
*/
void mpPrev() {
	
	if(event_type == EVENT_RELEASE) return;
	
	if(mpCount >= 0) {
		
		if(mpRandomize) mpCount = (int) random(mpSongs);
		else mpCount -= 1;
		mpPlay( (mpPool.pstring)[mpCount] );
		
	}
	
}

/*
--------------------------------------------------
void mpPause() 

Desc:

Returns: -
--------------------------------------------------
*/
void mpPause() {
	
	if(event_type == EVENT_RELEASE) return;
	
	if(media_playing(mpHandle)) {
		
		media_pause(mpHandle);
		mpPauseMark = 1;
		
	}
	
}

/*
--------------------------------------------------
void mpResume()

Desc:

Returns: -
--------------------------------------------------
*/
void mpResume() {
	
	if(event_type == EVENT_RELEASE) return;
	
	if(mpPauseMark) media_start(mpHandle);
	
}

/*
--------------------------------------------------
void PassToSKYSTR(var position)

Desc:

Returns: -
--------------------------------------------------
*/
void PassToSKYSTR(var position) {
	
	if(event_type == EVENT_RELEASE) return;
	
	WriteLog("[ ] Passing information from the input box to SKYSTR");
	
	// I don't care 'bout blank spaces 'cause all of them have been flooded
	// with undef.
	int absposition = position - 1;
	if(!str_cmp( (files_list_SKYSTR.pstring) [absposition], undef ) ) {
		
		str_cpy(SKYSTR, PATH_SKIES);
		str_cat(SKYSTR, (files_list_SKYSTR.pstring) [absposition] );
		
		WriteLog("copied "); WriteLog(SKYSTR);
		NewLine();		
		
	}
	
	WriteLog("[X] Task completed.");
	NewLine();
	
}

/*
--------------------------------------------------
void PassToGROUNDSTR(var position)

Desc:

Returns: -
--------------------------------------------------
*/
void PassToGROUNDSTR(var position) {
	
	if(event_type == EVENT_RELEASE) return;
	
	WriteLog("[ ] Passing information from the input box to GROUNDSTR");
	
	int absposition = position - 1;
	if( !str_cmp((files_list_GROUNDSTR.pstring) [absposition], undef) ) {
		
		str_cpy(GROUNDSTR,PATH_GROUNDS);
		str_cat(GROUNDSTR,(files_list_GROUNDSTR.pstring) [absposition]);
		
		WriteLog("copied "); WriteLog(GROUNDSTR);
		NewLine();
		
		
	}
	
	WriteLog("[X] Task completed.");
	NewLine();
	
}

/*
--------------------------------------------------
void PassToLOADGAMESTR(var position)

Desc:

Returns: -
--------------------------------------------------
*/
void PassToLOADGAMESTR(var position) {
	
	if(event_type == EVENT_RELEASE) return;
	
	WriteLog("[ ] Passing information from the input box to LOADGAMESTR");
	
	int absposition = position - 1;
	if( !str_cmp((files_list_LOADGAMESTR.pstring) [absposition], undef) ) {
		
		str_cpy(LOADGAMESTR, PATH_SAVEDGAMES);
		str_cat(LOADGAMESTR,(files_list_LOADGAMESTR.pstring) [absposition]);
		
		WriteLog("copied "); WriteLog(LOADGAMESTR);
		NewLine();
		
	}
	
	WriteLog("[X] Task completed.");
	NewLine();
	
}

/*
--------------------------------------------------
void TakeScreenshot()

Desc: Uses file_for_screen to take a screenshot
and names the captured file as pref_shot. This function
is independent and can be used anywhere within the code
or assigned to an input key.

Returns: -
--------------------------------------------------
*/
void TakeScreenshot() {
	
	WriteLog("[ ] Trying to take a screenshot...");
	NewLine();
	
	STRING *extension = ".jpg"; // Change the extension here: jpg, dds (uncompressed), png, bmp
	STRING *temp_ = "#100";
	
	str_cpy(temp_,FILE_SCREENSHOT);
	str_cat(temp_,extension);
	
	file_for_screen(temp_,shot);
	shot++;
	
	set(panScreenshot,SHOW);
	
	GPanelFade(panScreenshot,100,0,10);

	reset(panScreenshot,SHOW);
	panScreenshot.alpha = 100;
	
	WriteLog("[X] Task completed.");
	NewLine();
	
}

/*
--------------------------------------------------
int GenerateWaypoint()

Desc: Will be assigned to any newly created entity
through ENTITY *ent = ent_create(name,pos,GenerateWaypoint).
Turns the entity into a waypoint, used for navigating through
the world.

Returns: -1 if the object hasn't been created yet.
--------------------------------------------------
*/
int GenerateWaypoint()
{
	
	WriteLog("[ ] Loading waypoint function for ");
	
	while(!my) wait(1);
	STRING *temp_ = my->type;
	
	WriteLog( temp_ );
	NewLine();

	my_target_node = me;
	my_target_node.emask |= ENABLE_SCAN;
	
	while(my) {
		
		wait(1);
		
	}
	
	WriteLog("[X] Task completed for GenerateWaypoint() at");
	WriteLog( temp_ );
	NewLine();
	
}

/*
--------------------------------------------------
int GenerateTerrain()

Desc:

Returns: -
--------------------------------------------------
*/
int GenerateTerrain() {
	
	TerrainEnt = my;	
	total_vertices = ent_status(my,1);
	my.emask |= (ENABLE_TOUCH | ENABLE_CLICK | DYNAMIC);	
	
	while(my) { // Live till I die
		
		if (mouse_left && TerrainEditMode && !mouse_panel)
		{
			
			/*
			
			if(mouse_left) bHeight = DEF_UPPER;				
			else bHeight = DEF_LOWER;
			
			*/
			
			//		if(bType == B_SIBGLE) TDeform_single();
			if(bType == B_MULT) TDeform_multiple();
			if(bType == B_MULT_SMOOT) TDeform_multipleSmooth();
			
			//just_testing = my.skill1;
			wait (1);
		}
		
		wait(1);
		
	}
}

/*
--------------------------------------------------
int GenerateSound()

Desc: Will be assigned to any newly created entity
through ENTITY *ent = ent_create(name,pos,GenerateSound).
Turns the entity into a sound generator.

Returns: -1 if the object hasn't been created yet.
--------------------------------------------------
*/
int GenerateSound() {
	
	WriteLog("[ ] Loading sound function for ");
	
	while(!my) wait(1);
	STRING *temp_ = my->type;
	
	WriteLog( temp_ );
	NewLine();
	
	ent_playloop(my,snd_create(TEMPSTR),VOL_EFFECTS);
	
	while(my) {
		
		wait(1);
		
	}
	
	WriteLog("[X] Task completed for GenerateSound() at ");
	WriteLog( temp_ ); // use (STRING *) my->type outside here isn't right..my doesn't exist anymore..
	NewLine();
	
}

/*
--------------------------------------------------
int GenerateLight()

Desc: Will be assigned to any newly created entity
through ENTITY *ent = ent_create(name,pos,GenerateLight).
Turns the entity into a dynamic light.

Returns: -1 if the object hasn't been created yet.
--------------------------------------------------
*/
int GenerateLight() {
	
	WriteLog("[ ] Loading light function for ");
	
	while(!my) wait(1);
	STRING *temp_ = my->type;
	
	WriteLog( temp_ );
	NewLine();
	
	set(my, BRIGHT | NOFOG | PASSABLE | TRANSLUCENT);
	
	/* Some adjustments for our little jabber.png */
	my.scale_x = my.scale_y = my.scale_z /= 2;
	
	my.alpha = DEFAULT_ALPHA+25;
	my.ambient = 100;
	
	my.lightrange = random(2000);
	
	my.red = temp_light.red;
	my.green = temp_light.green;
	my.blue = temp_light.blue;
	
	my.z += 100;
	
	if(!my.FlickSpeed) my.FlickSpeed = .5;
	
	// Like men and women, lights should equal to normal entities.
	// They have the rights to be manipulated by the mouse.
	// oooh, wait, isn't the mouse belonged to the government??
	// ...
	// oh no.
	my.emask |= ENABLE_CLICK;
	// my.event = 	
	
	while(my) { // This loop will active as long as its entity is alive.
		
		if(my.LightMode == Flick) { // Flickering lights (Flashing lights)
			
			my.lightrange = 0;
			wait(-my.FlickSpeed);
			my.lightrange = olrange;
			wait(-my.FlickSpeed);
			
		}
		
		if(my.LightMode == Disco) { // Lights that change its r/g/b values continuously.
			
			//			random_seed(0);
			
			my.red = random(255);
			my.green = random(255);
			my.blue = random(255);
			
			wait(-DYNAMIC_LIGHT_DISCO_SPEED);
			
		}
		
		wait(1);
	}
	
	WriteLog("[X] Task completed for GenerateLight() at ");
	WriteLog( temp_ );
	NewLine();
	
}

/*
--------------------------------------------------
int AddToTextureProjectionArray(ENTITY *Ent)

Desc:

Returns: -
--------------------------------------------------
*/
int AddToTextureProjectionArray(ENTITY *Ent) {
	
	/*
	
	WriteLog("[ ] Trying to add an entity to the projection array...");
	NewLine();
	
	while(!Ent) wait(1);
	
	if(rEntCount < MAX_rEnts) {
		
		rEntCount += 1;
		rEnt[rEntCount] = Ent;
		
	}
	
	else {
		
		WriteLog("!! [ERROR] The projection array is full. Maximum number of entities allowed is ",MAX_rEnts);
		NewLine();
		WriteLog("!! From the ",MAX_rEnts + 1);
		WriteLog(" entity, shadows will no longer be casted.");
		NewLine();
		
	}
	
	WriteLog("[X] Task completed for AddToTextureProjectionArray(ENTITY *Ent) at ");
	WriteLog( (STRING *) Ent->type );
	NewLine();
	
	*/
	
	wait(1);
	
}

/*
--------------------------------------------------
void RemoveFromTextureProjectionArray(ENTITY *Ent)

Desc:

Returns: -
--------------------------------------------------
*/
void RemoveFromTextureProjectionArray(ENTITY *Ent) {
	
	/*
	
	// Test for deletion of the newest created entity.
	if(rEnt[rEntCount] == Ent) {
		
		rEnt[rEntCount] = NULL;
		rEntCount -= 1;
		
		return;
		
	}

	if(rEntCount == -1) return;

	int temprEntCount = 0;

	// Check if this entity exists in the rEnt array.
	for( ; temprEntCount <= rEntCount; temprEntCount++)
	if(rEnt[temprEntCount] == Ent) break;

	ptr_remove(rEnt[temprEntCount]);

	if(rEnt[temprEntCount+1]) { // Shift 'em
		
		int temprEntCount2 = temprEntCount + 2;
		
		while(rEnt[temprEntCount2]) {
			
			rEnt[temprEntCount2 - 1] = rEnt[temprEntCount2];
			temprEntCount2 -= 1;
			
			wait(1);
			
		}
		
	}
	
	rEntCount -= 1;
	
	*/
	
	wait(1);
	
}

/*
--------------------------------------------------
ENTITY *CreateObject()

Desc: Uses ent_create to create an object based on which value _ObjectType
is holding. Currently, CreateObject() can only creates
normal .mdl/.wmb objects, lights, particle objects,
waypoint and light objects.

Returns:
- Success: pointer of the newly created object.
- Fail: NULL.
--------------------------------------------------
*/
ENTITY *CreateObject() { // This inherits a lot from place_me & the old CreateObject.

	WriteLog("[ ] Trying to create an object through CreateObject()... ");
	NewLine();
	
	if( str_cmp(TEMPSTR,undef) ) {
		
		_beep();
		
		WriteLog("!! [ERROR] Somehow TEMPSTR is empty, cannot create object, returns NULL.");
		NewLine();
		
		return NULL;
		
	}
	
	// Stupid object couldn't float
	if(!temp_pos.x && !temp_pos.y && !temp_pos.z) {
		
		_beep();
		WriteLog("!! [ERROR] The cursor's position is out of range, returns a NULL object.");
		NewLine();
		WriteLog("!! Point the cursor to the correct position and try again. Solid ground, for example.");
		NewLine();
		
		return NULL;
		
	}
	
	ENTITY *tmp;
	
	if(TEMP_OBJECT_TYPE > Object && TEMP_OBJECT_TYPE < ObjectNode) {
		
		tmp = ent_create(TEMPSTR,temp_pos,ObjectManipulationInterface);
		
		while(!tmp) wait(1);
		WriteLog("[ ] Finished creating the temporary neutral object. Passing values...");
		NewLine();
		
		//		AddToTextureProjectionArray(tmp);
		
		tmp.ObjectType = TEMP_OBJECT_TYPE;
		
		// Begin passing values for the neutral object.
		set(tmp, POLYGON);
		reset(tmp, NOFOG | INVISIBLE | TRANSLUCENT); // Tha giet nham con hon bo sot	
		
		tmp.alpha = 0;
		tmp.ambient = 50;
		tmp.pan = random(360); // Give it a random pan value.
		
		tmp.material = mtl_model;
		
		tmp.ObjectDynamic = 0; // This is a static object
		tmp.ObjectPhysics = 0; // And physics aren't enabled by default.		
		
		LoadObjectCustomSettings(tmp);
		
		WriteLog("[X] Task completed for CreateObject() at ");
		WriteLog( (STRING *) tmp->type );
		NewLine();
		
		return tmp;
		
	}
	
	if(TEMP_OBJECT_TYPE == Particle) {
		
		switch(ParticleIDNumber) {
			
			case part_spiral: 
			tmp = ent_create("desktop_effect.png",temp_pos,emit_spiral); break;
			
			case part_colorfulspark: 
			tmp = ent_create("desktop_effect.png",temp_pos,emit_colorfulspark); break;
			
			case part_spacehole: 
			tmp = ent_create("desktop_effect.png",temp_pos,emit_spacehole); break;
			
			case part_fountain2: 
			tmp = ent_create("desktop_effect.png",temp_pos,emit_fountain2); break;
			
			case part_fountain1: 
			tmp = ent_create("desktop_effect.png",temp_pos,emit_fountain1); break;
			
			case part_fire2: 
			tmp = ent_create("desktop_effect.png",temp_pos,emit_fire2); break;
			
			case part_fire1: 
			tmp = ent_create("desktop_effect.png",temp_pos,emit_fire1); break;
			
			case part_doublehelix: 
			tmp = ent_create("desktop_effect.png",temp_pos,emit_doublehelix); break;
			
			case part_composition: 
			tmp = ent_create("desktop_effect.png",temp_pos,emit_composition); break;
			
			return tmp;
			
			default:
			
			_beep();
			WriteLog("!! [ERROR] ParticleIDNumber out of range (");
			WriteLog(ParticleIDNumber);
			WriteLog("), returns NULL.");
			NewLine();
			
			return NULL;
			
			break; // redundant, maybe.
			
		}
		
		while(!tmp) wait(1);
		
		WriteLog("[ ] Finished creating the temporary particle object. Passing values...");
		NewLine();
		
		tmp.ObjectType = TEMP_OBJECT_TYPE;		
		
		set(tmp, BRIGHT | NOFOG | PASSABLE | TRANSLUCENT);
		
		tmp.ParticleID = ParticleIDNumber;
		
		tmp.scale_x = tmp.scale_y = tmp.scale_z /= 2;
		
		tmp.z += 125;
		tmp.alpha = DEFAULT_ALPHA+25;
		tmp.ambient = 100;
		
		WriteLog("[X] Task completed for CreateObject() at ");
		WriteLog( (STRING *) tmp->type );
		NewLine();
		
		return tmp;	
		
	}
	
	if(TEMP_OBJECT_TYPE == Light) {
		
		tmp = ent_create("jabber.png",temp_pos,GenerateLight);
		
		while(tmp == NULL) wait(1);
		WriteLog("[ ] Finished creating the temporary light object. Passing values...");
		NewLine();
		
		tmp.ObjectType = TEMP_OBJECT_TYPE;
		
		// Lights don't have IDs so passing them is redundant.
		WriteLog("[X] Task completed for CreateObject() at ");
		WriteLog( (STRING *) tmp->type );
		NewLine();
		
		return tmp;
		
	}
	
	if(TEMP_OBJECT_TYPE == Sound) {
		
		tmp = ent_create("sound_32.png",temp_pos,GenerateSound);
		
		while(tmp == NULL) wait(1);
		WriteLog("[ ] Finished creating the temporary sound object. Passing values...");
		NewLine();
		
		set(tmp, BRIGHT | NOFOG | PASSABLE | TRANSLUCENT);
		
		// Am thanh nho be cu de cho no an :|
		//		tmp.scale_x = tmp.scale_y = tmp.scale_z /= 2;
		
		tmp.z += 125;
		tmp.alpha = DEFAULT_ALPHA+25;
		tmp.ambient = 100;
		
		tmp.ObjectType = TEMP_OBJECT_TYPE;
		
		LoadObjectCustomSettings(tmp);
		
		WriteLog("[X] Task completed for CreateObject() at ");
		WriteLog( (STRING *) tmp->type );
		NewLine();
		
		return tmp;
		
	}
	
	if(TEMP_OBJECT_TYPE == Sprite) {
		
		tmp = ent_create(TEMPSTR,temp_pos,ObjectManipulationInterface);
		
		while(!tmp) wait(1);
		WriteLog("[ ] Finished creating the temporary sprite object. Passing values...");
		NewLine();
		
		set(tmp,OVERLAY | BRIGHT | PASSABLE | POLYGON);
		
		tmp.ObjectType = TEMP_OBJECT_TYPE;
		
		LoadObjectCustomSettings(tmp);
		
		WriteLog("[X] Task completed for CreateObject() at ");
		WriteLog( (STRING *) tmp->type );
		NewLine();
		
		return tmp;
		
	}
	
	if(TEMP_OBJECT_TYPE == Terrain) {
		
		tmp = ent_create(TEMPSTR,temp_pos,GenerateTerrain);
		
		while(!tmp) wait(1);
		WriteLog("[ ] Finished creating the temporary terrain object. Passing values...");
		NewLine();
		
		//		AddToTextureProjectionArray(tmp);
		
		set(tmp,POLYGON);
		
		tmp.ObjectType = TEMP_OBJECT_TYPE;
		
		LoadObjectCustomSettings(tmp);
		
		WriteLog("[X] Task completed for CreateObject() at ");
		WriteLog( (STRING *) tmp->type );
		NewLine();
		
		return tmp;
		
	}
	
	if(TEMP_OBJECT_TYPE == ObjectNode) {
		
		tmp = ent_create("ix_waypoint.mdl",temp_pos,GenerateWaypoint);
		//		str_cpy(tmp.type,path_name);
		
		while(tmp == NULL) wait(1);
		WriteLog("[ ] Finished creating the temporary waypoint object. Passing values...");
		NewLine();
		
		set(tmp, BRIGHT | PASSABLE);
		tmp.ambient = 100;
		
		tmp.scale_x = tmp.scale_y = tmp.scale_z *= 1.5;
		
		tmp.ObjectType = ObjectNode;
		
		LoadObjectCustomSettings(tmp);
		
		WriteLog("[X] Task completed for CreateObject() at ");
		WriteLog( (STRING *) tmp->type );
		NewLine();
		
		return tmp;
		
	}
	
	return NULL; // For objects those fall out of range.
	
}

/*
--------------------------------------------------
void FolderScan(TEXT *filler, STRING *dir, STRING *ext)

Desc: Did a little optimization here - the string clearing 
is redundant, because str_cpy will automatically overwrites 
string while writing from source.

27.10.2013: Added a simple extension that fills undef char to the text object

Returns: -
--------------------------------------------------
*/
void FolderScan(TEXT *filler, STRING *dir, STRING *ext)
{
	
	WriteLog("[ ] Scanning folder ");
	WriteLog( dir );
	WriteLog(" for all ");
	WriteLog(ext);
	WriteLog(" files.");
	NewLine();
	
	while(!filler) wait(1); // wait for our customer
	
	TEXT *read_files = txt_create(filler.strings,1);
	
	STRING *search_form = "a";

	str_cpy(current_folder,dir);
	str_cpy(search_form,dir);
	str_cat(search_form,"\\*.");
	str_cat(search_form,ext);
	
	files_found = txt_for_dir(read_files, search_form);
	
	var num = 0;
	
	while(num<files_found)
	{
		str_cpy((filler.pstring)[num+files_already],(read_files.pstring)[num]);
		num++;
	}
	list_start=0;
	
	if(files_found < filler.strings) {
		
		while(files_found < filler.strings) {
			
			str_cpy( (filler.pstring) [(int) files_found], undef);
			files_found += 1;
			
		}
		
	}
	
	WriteLog("[X] Task completed for FolderScan(TEXT *filler, STRING *dir, STRING *ext).");
	NewLine();
	
}

/* 
--------------------------------------------------
int PlayVideo(STRING *what, var vol)

Desc: A media_play wrapper which plays a multimedia file 
and wait until it ends. Combine with proc_status to get the 
desired effect.

Returns: -1 if the file couldn't be opened.
--------------------------------------------------
*/
int PlayVideo(STRING *what, var vol) {
	
	proc_kill(4);

	WriteLog("[ ] Trying to play a video file...");
	NewLine();
	
	var hndl;

	if(!media_play(what,NULL,0)) {
		
		_beep();
		WriteLog("!! [ERROR] The file couldn't be opened.");
		NewLine();
		
		return -1;
		
	}
	else hndl = media_play(what,NULL,abs(vol));

	while(media_playing(hndl)) wait(1);
	
	WriteLog("[X] Task completed. ");
	NewLine();

}

/* 
--------------------------------------------------
void FollowPointer()

Desc: Forces the marker to follow the Windows cursor.
Objects will be created at marker's position.
The original code was written by George Dan Pirvu, but
it was partly rewritten and used as the base code for craftbox.

Returns: -
--------------------------------------------------
*/
void FollowPointer() {
	
	proc_mode = PROC_LATE;
	proc_kill(4);
	
	//	if(proc_status(FollowPointer)) return;

	WriteLog("[ ] Setting up the pointer...");
	NewLine();

	if(!KERNEL_IS_RUNNING) {
		
		_beep();
		
		WriteLog("!! [ERROR] You must first start the kernel before FollowPointer() can be executed.");
		NewLine();
		
		return;
		
	}

	marker = me;
	set(marker,POLYGON | PASSABLE | TRANSLUCENT);
	marker.flags2 |= UNTOUCHABLE;
	marker.alpha = 60;
	Scale(marker,SCALE_MARKER);
	
	VECTOR vv0; //Center
	VECTOR vv1; //left
	VECTOR vv2; //right
	VECTOR vv3; //Up
	VECTOR vv4; //Down

	var v0, v1, v2, v3, v4;

	while( 1  ) {
		
		cpos1.x = mouse_pos.x;
		cpos1.y = mouse_pos.y;
		cpos1.z = 0;
		vec_for_screen(cpos1,camera);
		cpos2.x = mouse_pos.x;
		cpos2.y = mouse_pos.y;
		cpos2.z = pow(10,6);
		vec_for_screen(cpos2,camera);
		
		c_trace(cpos1.x,cpos2.x,
		IGNORE_ME | IGNORE_YOU | IGNORE_PASSABLE | IGNORE_SPRITES | IGNORE_PUSH | 
		USE_BOX | USE_POLYGON);
		
		marker.x = hit.x;
		marker.y = hit.y;
		marker.z = hit.z;
		
		temp_pos.x = hit.x;
		temp_pos.y = hit.y;
		temp_pos.z = hit.z;
		
		/*
		
		DEBUG_VAR(temp_pos.x,20);
		DEBUG_VAR(temp_pos.y,40);
		DEBUG_VAR(temp_pos.z,60);
		
		DEBUG_VAR(marker.x,80);
		DEBUG_VAR(marker.y,100);
		DEBUG_VAR(marker.z,120);
		
		*/
		
		//		
		
		//		if( !PLAYTESTING ) { // <- Uncomment this to lock the realtime terrain editing while in Playtest mode
			
			if(TerrainEnt && bSize >=10 && TerrainEditMode)
			{
				
				// put Scale(marker, SCALE_MARKER_TERRAIN); would be rather expensive
				// unnecessary instrunctions are repeated over and over
				// so check GTerrainSubmenuShow() for more detail
				
				v0 = ent_nextvertex(TerrainEnt,_vec(temp_pos.x,temp_pos.y,temp_pos.z)); 
				v1 = ent_nextvertex(TerrainEnt,_vec(temp_pos.x-bSize-10,temp_pos.y,temp_pos.z)); 
				v2 = ent_nextvertex(TerrainEnt,_vec(temp_pos.x+bSize-10,temp_pos.y,temp_pos.z)); 
				v3 = ent_nextvertex(TerrainEnt,_vec(temp_pos.x,temp_pos.y-bSize-10,temp_pos.z)); 
				v4 = ent_nextvertex(TerrainEnt,_vec(temp_pos.x,temp_pos.y+bSize-10,temp_pos.z));
				
				vec_for_vertex(vv0,TerrainEnt,v0);
				vec_for_vertex(vv1,TerrainEnt,v1);
				vec_for_vertex(vv2,TerrainEnt,v2);
				vec_for_vertex(vv3,TerrainEnt,v3);
				vec_for_vertex(vv4,TerrainEnt,v4);		
				
				draw_point3d(_vec(vv0.x,vv0.y,vv0.z-10), _vec(0,0,255), 100,10);
				draw_point3d(_vec(vv1.x,vv1.y,vv1.z-10), _vec(0,255,255), 100,8);
				draw_point3d(_vec(vv2.x,vv2.y,vv2.z-10), _vec(0,255,255), 100,8);
				draw_point3d(_vec(vv3.x,vv3.y,vv3.z-10), _vec(0,255,255), 100,8);
				draw_point3d(_vec(vv4.x,vv4.y,vv4.z-10), _vec(0,255,255), 100,8);	
				draw_line3d(_vec(vv0.x,vv0.y,0), _vec(255,255,255), 100);
				//			draw_line3d(_vec(vv0.x,vv0.y,tMaxHeight), _vec(255,255,255), 100);
				
			}
			
		//		}
		
		wait(1);
		
	}
	
	WriteLog("[X] Task completed for FollowPointer().");
	NewLine();
	
}

/*
--------------------------------------------------
int PassObjectPropertiesToGUI(ENTITY *e)

Desc: Passes object's properties to the GUI.

Returns: -1 if the appropriate GUI panel haven't
yet been opened.
--------------------------------------------------
*/
int PassObjectPropertiesToGUI(ENTITY *e) {

	WriteLog("[ ] Trying to pass object information to the appropriate panel...");
	NewLine();

	if(!is(panProp,SHOW)) return -1; // Not necessary to use WriteLog here.

	v_objectz = 3000 - e.z;
	v_ambient = e.ambient;
	v_alpha = 100 - e.alpha;

	if(is(e,BRIGHT)) button_state(panProp_1,1,1);
	else button_state(panProp_1,1,0);

	if(is(e,INVISIBLE)) button_state(panProp_1,2,1);
	else button_state(panProp_1,2,0);

	if(is(e,NOFOG)) button_state(panProp_1,3,1);
	else button_state(panProp_1,3,0);

	if(is(e,OVERLAY)) button_state(panProp_1,4,1);
	else button_state(panProp_1,4,0);

	if(is(e,PASSABLE)) button_state(panProp_1,5,1);
	else button_state(panProp_1,5,0);

	if(is(e,POLYGON)) button_state(panProp_1,6,1);
	else button_state(panProp_1,6,0);

	if(is(e,SHADOW)) button_state(panProp_1,7,1);
	else button_state(panProp_1,7,0);

	if(is(e,TRANSLUCENT)) button_state(panProp_1,8,1);
	else button_state(panProp_1,8,0);
	
	WriteLog("[X] Task completed.");
	NewLine();

}

/*
--------------------------------------------------
void ObjectRestoreDefault()

Desc: Restores an object to its original state.
Nothing big, it just resets all the flags to zero
and toggle the POLYGON flag to 1.

This was made specifically for the "select" object for 
assigning to the GUI panel.

Returns: - 
--------------------------------------------------
*/
void ObjectRestoreDefault() {

	if(event_type == EVENT_RELEASE) return;
	
	WriteLog("[ ] Trying to reset the object to its original state...");
	NewLine();

	if(select) {
		
		select.alpha = 0;
		select.ambient = 0;
		reset(select, BRIGHT | INVISIBLE | NOFOG | OVERLAY | PASSABLE | SHADOW | TRANSLUCENT);
		if(!is(select,POLYGON)) set(select,POLYGON);
		
		PassObjectPropertiesToGUI(select); // update the properties panel
		
	}
	
	WriteLog("[X] Task completed.");
	NewLine();

}

/*
--------------------------------------------------
void ObjectRandomPan()

Desc:

Returns: -
--------------------------------------------------
*/
void ObjectRandomPan() {

	if(event_type == EVENT_RELEASE) return;
	
	WriteLog("[ ] Setting random pan for object ");
	NewLine();

	if(select) select.pan = random(360);
	
	WriteLog("[X] Task completed.");	
	NewLine();

}

/*
--------------------------------------------------
void MaterialCopyColor(MATERIAL *dest, MATERIAL *source)

Desc:

Returns: -
--------------------------------------------------
*/
void MaterialCopyColor(MATERIAL *dest, MATERIAL *source) {
	
	WriteLog("[ ] Copying material color...");
	NewLine();

	while(!dest || !source) wait(1);

	dest.ambient_red = source.ambient_red;
	dest.ambient_green = source.ambient_green;
	dest.ambient_blue = source.ambient_blue;

	dest.specular_red = source.specular_red;
	dest.specular_blue = source.specular_blue;

	dest.diffuse_red = source.diffuse_red;
	dest.diffuse_green = source.diffuse_green;
	dest.diffuse_blue = source.diffuse_blue;

	dest.emissive_red = source.emissive_red;
	dest.emissive_green = source.emissive_green;
	dest.emissive_blue = source.emissive_blue;
	
	WriteLog("[X] Task completed.");
	NewLine();

}

/*
--------------------------------------------------
int MaterialSelect(var id)

Desc: Selects a material from panMat. Whenever
you choose something from the material selection window,
the appropriate material will be copied to mat_temp that
will be passed later to the "select" object when it has
gone out of scope.

Returns: -1 if id is out of range.
--------------------------------------------------
*/
int MaterialSelect(var id) {

	if(event_type == EVENT_RELEASE) return -1;
	
	WriteLog("[ ] Selecting material from list...");
	NewLine();

	// Clear evidence first
	var i = 0;
	while(i < 16) {
		
		button_state(panProp_2,i,0);
		i++;
		
	}
	
	button_state(panProp_2,(int) id,1);

	if(select) {
		
		switch(id) {
			
			case 1: // Lava
			
			mat_temp = mat_lava;	
			if(is(panMat_Sub1,SHOW)) reset(panMat_Sub1,SHOW);
			
			break;
			
			case 2: // Marble
			
			mat_temp = mat_marble;
			if(is(panMat_Sub1,SHOW)) reset(panMat_Sub1,SHOW);
			
			break;
			
			case 3: // Smaragd
			
			mat_temp = mat_smaragd;
			if(is(panMat_Sub1,SHOW)) reset(panMat_Sub1,SHOW);
			
			break;
			
			case 4: // Lavender rose
			
			mat_temp = mat_lavenderrose;
			if(is(panMat_Sub1,SHOW)) reset(panMat_Sub1,SHOW);
			
			break;
			
			case 5: // Bitter lemon
			
			mat_temp = mat_bitterlemon;
			if(is(panMat_Sub1,SHOW)) reset(panMat_Sub1,SHOW);
			
			break;
			
			case 6: // Peach orange
			
			mat_temp = mat_peachorange;
			if(is(panMat_Sub1,SHOW)) reset(panMat_Sub1,SHOW);
			
			break;
			
			case 7: // Pure white light
			
			mat_temp = mat_purewhite;
			if(is(panMat_Sub1,SHOW)) reset(panMat_Sub1,SHOW);
			
			break;
			
			case 8: // Metallic
			
			mat_temp = mat_metal;
			if(is(panMat_Sub1,SHOW)) reset(panMat_Sub1,SHOW);
			
			break;
			
			case 9: // Pure black
			
			mat_temp = mat_black;
			if(is(panMat_Sub1,SHOW)) reset(panMat_Sub1,SHOW);
			
			break;
			
			case 10: // Soft pale lilac
			
			mat_temp = mat_palelilac;
			if(is(panMat_Sub1,SHOW)) reset(panMat_Sub1,SHOW);
			
			break;
			
			case 11: // Custom material #1
			
			mat_type = select_custom_mat1;
			mat_temp = mat_custom[0];
			
			/*
			a quick terrible ugly hack
			normally panMat_Sub1 will only be updated
			if you click 1 "Edit Material",
			but this hack allows you to update panMat_Sub1 directly
			without pressing that button.
			
			this can be useful if you've already opened panMat_Sub1
			and select another customizable material, the panel
			will be updated immediately without having to click
			the "Edit Material" button again.
			*/
			if(is(panMat_Sub1,SHOW))
			PassMaterialDataToWindow(mat_custom[0]);
			
			break;
			
			case 12: // Custom material #2
			
			mat_type = select_custom_mat2;
			mat_temp = mat_custom[1];
			
			if(is(panMat_Sub1,SHOW))
			PassMaterialDataToWindow(mat_custom[1]);
			
			break;
			
			case 13: // Custom material #3
			
			mat_type = select_custom_mat3;
			mat_temp = mat_custom[2];
			
			if(is(panMat_Sub1,SHOW))
			PassMaterialDataToWindow(mat_custom[2]);
			
			break;
			
			case 14: // Custom material #4
			mat_type = select_custom_mat4;
			mat_temp = mat_custom[3];
			
			if(is(panMat_Sub1,SHOW))
			PassMaterialDataToWindow(mat_custom[3]);
			
			break;
			
			case 15: // Default
			
			mat_type = select_mat_null;
			mat_temp = NULL;
			
			break;		
			
			default:
			
			WriteLog("!! [ERROR] id fell out of range, returns -1.");  
			NewLine();
			
			return -1;
			
			break;
			
		}
		
	}
	
	WriteLog("[X] Task completed.");
	NewLine();

}

/*
--------------------------------------------------
int PassObjectDataToClipboard(ENTITY *o, OBJECTSTRUCT *of)

Desc: Copies both object's general information and
unique characteristics information to the clipboard struct.

Returns: -1 if o.ObjectType falls out of range. of.of_objtype will 
then be assigned to -1, which indicates neutral object.
--------------------------------------------------
*/
int PassObjectDataToClipboard(ENTITY *o, OBJECTSTRUCT *of) {
	
	while(!o || !of) wait(1);
	
	WriteLog("[ ] Copying data (");
	WriteLog ( (STRING *) o->type );
	WriteLog(") to clipboard...");
	NewLine();

	of.name = str_create("#300");

	////////////////////////////////////////////////////////////
	// Pass general information to the clipboard first.
	////////////////////////////////////////////////////////////
	of._scale_x = o.scale_x;
	of._scale_y = o.scale_y;
	of._scale_z = o.scale_z;

	of._pan = o.pan;
	of._tilt = o.tilt;
	of._roll = o.roll;

	of._alpha = o.alpha;
	of._ambient = o.ambient;
	
	int i = 0;
	for(; i < MAX_PUBLIC_SKILLS + MAX_PRIVATE_SKILLS ; i++) of._skill[i] = o.skill[i];

	// TOO LAZY TO USE MULTIPLE CASES IN A SWITCH STATMENT
	// SO I SPLIT THEM INTO DIFFERENT IFs. IF IT SUCCESS,
	// IT WILL RETURN, THUS PREVENTS THE FUNCTION FROM EXECUTING
	// OTHER IFs.

	if(o.ObjectType > Object && o.ObjectType <= ObjectNode) {
		
		WriteLog("[ ] Passing information of a neutral object into clipboard.");
		NewLine();
		
		//		str_cpy(of.name,o.filename);
		
		if(is(o,BRIGHT)) of._flags[0] = 1;
		else of._flags[0] = 0;
		
		if(is(o,INVISIBLE)) of._flags[1] = 1;
		else of._flags[1] = 0;
		
		if(is(o,NOFOG)) of._flags[2] = 1;
		else of._flags[2] = 0;
		
		if(is(o,OVERLAY)) of._flags[3] = 1;
		else of._flags[3] = 0;
		
		if(is(o,PASSABLE)) of._flags[4] = 1;
		else of._flags[4] = 0;
		
		if(is(o,POLYGON)) of._flags[5] = 1;
		else of._flags[5] = 0;
		
		if(is(o,SHADOW)) of._flags[6] = 1;
		else of._flags[6] = 0;
		
		if(is(o,TRANSLUCENT)) of._flags[7] = 1;
		else of._flags[7] = 0;
		
		of.of_objtype = o.ObjectType;
		
		of.pStatic = o.ObjectDynamic;
		of.pPhysics = o.ObjectPhysics;
		
		// Flag indicates that the copy progress has done.
		// Also, it can be used to determine if the clipboard has any piece of data or not.
		of.dp = 1;
		
		WriteLog("[X] Task completed.");
		NewLine();
		
		return 1;
		
	}

	if(o.ObjectType == Light) {
		
		WriteLog("[ ] Passing information of a light object into clipboard.");
		NewLine();
		
		//		str_cpy(of.name,o.filename);
		
		of._red = o.red;
		of._green = o.green;
		of._blue = o.blue;
		of._range = o.lightrange;
		of._LightMode = o.LightMode;
		
		of.of_objtype = o.ObjectType;
		
		of.dp = 1;
		
		WriteLog("[X] Task completed.");
		NewLine();
		
		return 1;
		
	}

	if(o.ObjectType == Sound) {
		
		WriteLog("[ ] Passing information of a sound object into clipboard.");
		NewLine();
		
		//		str_cpy(of.name,o.filename);
		
		of.of_objtype = o.ObjectType;
		
		of.dp = 1;
		
		WriteLog("[X] Task completed.");
		NewLine();
		
		return 1;
		
	}

	if(o.ObjectType == Particle) {
		
		WriteLog("[ ] Passing information of a particle object into clipboard.");
		NewLine();
		
		//		str_cpy(of.name,o.filename);
		
		of.of_objtype = o.ObjectType;
		
		of.dp = 1;
		
		WriteLog("[X] Task completed.");
		NewLine();
		
		return 1;
		
	}

	if(o.ObjectType == ObjectNode) {
		
		WriteLog("[ ] Passing information of a node object into clipboard.");
		NewLine();
		
		//		str_cpy(of.name,o.filename);
		
		WriteLog("[X] Task completed.");
		NewLine();
		return 1;
		
	}

	if(o.ObjectType == Sprite) {
		
		WriteLog("[ ] Passing information of a sprite object into clipboard.");
		NewLine();
		
		//		str_cpy(of.name,o.filename);
		
		WriteLog("[X] Task completed.");
		NewLine();
		return 1;
		
	}

	if(o.ObjectType == Terrain) {
		
		WriteLog("[ ] Passing information of a terrain into clipboard.");
		NewLine();
		
		//		str_cpy(of.name,o.filename);
		
		WriteLog("[X] Task completed.");
		NewLine();
		return 1;
		
	}

	return -1;
	
}

/*
--------------------------------------------------
int PassClipboardDataToObject(ENTITY *e)

Desc: Copies general information from the clipboard 
struct to ENTITY *e, and continues to copy the remaining 
unique characteristics information based on clipboard.of_objtype.

Returns: -1 if e.ObjectType falls out of range (rare) or 
the clipboard is empty. (clipboard.dp = 0)
--------------------------------------------------
*/
int PassClipboardDataToObject(ENTITY *e) {
	
	while(!e) wait(1);
	
	WriteLog("[ ] Copying back data from clipboard to ");
	WriteLog( (STRING *) e->type);
	NewLine();

	// Double check
	if(!clipboard.dp) {
		
		_beep();
		
		WriteLog("!! [ERROR] Clipboard contains no data, returns -1.");
		NewLine();
		
		return -1;
		
	}

	////////////////////////////////////////////////////////////
	// As usual, pass general data first.
	////////////////////////////////////////////////////////////
	e.ambient = clipboard._ambient;
	e.alpha = clipboard._alpha;

	e.scale_x = clipboard._scale_x;
	e.scale_y = clipboard._scale_y;
	e.scale_z = clipboard._scale_z;

	e.pan = clipboard._pan;
	e.tilt = clipboard._tilt;
	e.roll = clipboard._roll;
	
	int i = 0;
	for(; i < MAX_PUBLIC_SKILLS + MAX_PRIVATE_SKILLS;i++) e.skill[i] = clipboard._skill[i];

	if(clipboard.of_objtype > Object && clipboard.of_objtype <= ObjectNode) {
		
		WriteLog("[ ] Clipboard contains information of a neutral object.");
		NewLine();
		
		e.ObjectType = clipboard.of_objtype;
		
		e.skill2 = clipboard.pStatic;
		e.skill3 = clipboard.pPhysics;
		e.material = clipboard.m;
		
		if(clipboard._flags[0]) set(e,BRIGHT);
		else reset(e,BRIGHT);
		
		if(clipboard._flags[1]) set(e,INVISIBLE);
		else reset(e,INVISIBLE);
		
		if(clipboard._flags[2]) set(e,NOFOG);
		else reset(e,NOFOG);
		
		if(clipboard._flags[3]) set(e,OVERLAY);
		else reset(e,OVERLAY);
		
		if(clipboard._flags[4]) set(e,PASSABLE);
		else reset(e,PASSABLE);
		
		if(clipboard._flags[5]) set(e,POLYGON);
		else reset(e,POLYGON);
		
		if(clipboard._flags[6]) set(e,SHADOW);
		else reset(e,SHADOW);
		
		if(clipboard._flags[7]) set(e,TRANSLUCENT);
		else reset(e,TRANSLUCENT);
		
		WriteLog("[X] Task completed.");
		NewLine();
		
		return 1;
		
	}

	if(clipboard.of_objtype == Light) {
		
		WriteLog("[ ] Clipboard contains information of a light object.");
		NewLine();
		
		e.red = clipboard._red;
		e.green = clipboard._green;
		e.blue = clipboard._blue;
		e.lightrange = clipboard._range;
		e.LightMode = clipboard._LightMode;
		
		e.material = mtl_model;
		
		WriteLog("[X] Task completed.");
		NewLine();
		
		return 1;
		
	}

	if(clipboard.of_objtype == Particle) {
		
		WriteLog("[ ] Clipboard contains information of a particle object.");
		NewLine();
		
		e.material = mtl_model;
		
		WriteLog("[X] Task completed.");
		NewLine();
		
		return 1;
		
	}

	if(clipboard.of_objtype == Sound) {
		
		WriteLog("[ ] Clipboard contains information of a sound object.");
		NewLine();
		
		e.material = mtl_sprite;
		
		WriteLog("[X] Task completed.");
		NewLine();
		
		return 1;
		
	}

	if(clipboard.of_objtype == Sprite) {
		
		WriteLog("[ ] Clipboard contains information of a sprite object.");
		NewLine();
		
		WriteLog("[X] Task completed.");
		NewLine();
		
		return 1;
		
	}

	if(clipboard.of_objtype == Terrain) {
		
		WriteLog("[ ] Clipboard contains information of a terrain.");
		NewLine();
		
		WriteLog("[X] Task completed.");
		NewLine();
		
		return 1;
		
	}

	if(clipboard.of_objtype == ObjectNode) {
		
		WriteLog("[ ] Clipboard contains data of a node object.");
		NewLine();
		
		WriteLog("[X] Task completed.");
		NewLine();
		
		return 1;
		
	}
	
	return -1;

}

/*
--------------------------------------------------
void ObjectCut()

Desc: Copies "select"'s information to clipboard 
prior to deleting the object pointed to by "select".

Returns: Nothing. But be careful - PassObjectDataToClipboard(...) 
in this case maybe returns -1, indicating the object pointed to by
"select" is a neutral object, or its ID isn't assigned correctly due to 
programming mistakes.
--------------------------------------------------
*/
void ObjectCut() {
	
	WriteLog("[ ] Cutting an object to clipboard..."); 
	NewLine();

	if(select) {
		
		PassObjectDataToClipboard(select,clipboard);
		
		if(select.ObjectType > Object && select.ObjectType <= ObjectNode) 
		{
			
			// Perform manual access to clipboard to copy material
			
			/*
			select is selected.
			so something must have been copied into mat_temp.
			so I directly take mat_temp and copy it into the clipboard.
			
			otherwise if we pass select.material to clipboard.m,
			mat_select is passed but not select's material.
			*/
			clipboard.m = mat_temp;
		}
		
		ptr_remove(select);
		select = NULL;
	}
	
	WriteLog("[X] Task completed for ObjectCut().");
	NewLine();

}

/*
--------------------------------------------------
void ObjectCopy()

Desc: Copies "select"'s information to clipboard.

Returns: Nothing. But be careful - PassObjectDataToClipboard(...) 
in this case maybe returns -1, indicating the object pointed to by
"select" is a neutral object, or its ID isn't assigned correctly due to 
programming mistakes.
--------------------------------------------------
*/
void ObjectCopy() {
	
	WriteLog("[ ] Copying an object to clipboard.");
	NewLine();

	if(select) {
		
		PassObjectDataToClipboard(select,clipboard);
		
		if(select.ObjectType == Object) 
		{
			//		// Perform manual access to clipboard to copy material
			clipboard.m = mat_temp;
		}
	}
	
	WriteLog("[X] Task completed for ObjectCopy().");
	NewLine();

}

/*
--------------------------------------------------
void ObjectPaste()

Desc: Searches clipboard.of_objtype, creates the appropriate 
object and passes information from the clipboard struct to that 
object.

Returns: -
--------------------------------------------------
*/
void ObjectPaste() {
	
	WriteLog("[ ] Pasting an object from clipboard...");
	NewLine();

	if(clipboard.dp) {
		
		int TEMP_OBJECT_TYPE_old = clipboard.of_objtype;
		STRING *TEMPSTR_old = str_create ( TEMPSTR );
		
		TEMP_OBJECT_TYPE = clipboard.of_objtype;
		str_cpy(TEMPSTR,clipboard.name);
		
		PassClipboardDataToObject(CreateObject());
		while(proc_status(PassClipboardDataToObject)) wait(1);
		
		str_cpy(TEMPSTR,TEMPSTR_old);
		TEMP_OBJECT_TYPE = TEMP_OBJECT_TYPE_old;
		
	}
	
	WriteLog("[X] Task completed for ObjectPaste().");
	NewLine();

}

/*
--------------------------------------------------
void ReadMaterialDataFromFile(MATERIAL *m, STRING *file)

Desc: Read material properties from a file and pass it to a
previously-defined material.

Returns: -
--------------------------------------------------
*/
void ReadMaterialDataFromFile(MATERIAL *m, STRING *file) {
	
	WriteLog("[ ] Reading material data from external file (");
	WriteLog(file);
	WriteLog(")...");
	NewLine();

	while(!m) wait(1); // wait for m to be completely created

	var vpass = file_open_read(file);
	if(!vpass) {
		
		_beep();
		
		WriteLog("!! [ERROR] Failed to open ");
		WriteLog(file);
		WriteLog(" for reading material data, returns.");
		NewLine();
		
		return;
		
	}

	// Follow this form :
	/*

	ambient_red, ambient_green, ambient_blue
	specular_red, specular_green, specular_blue,
	diffuse_red, diffuse_green, diffuse_blue,
	emissive_red, emissive_green, emissive_blue,
	alpha, power (no need for albedo)

	*/

	m.ambient_red = file_var_read(vpass);
	m.ambient_green = file_var_read(vpass);
	m.ambient_blue = file_var_read(vpass);

	m.specular_red = file_var_read(vpass);
	m.specular_green = file_var_read(vpass);
	m.specular_blue = file_var_read(vpass);

	m.diffuse_red = file_var_read(vpass);
	m.diffuse_green = file_var_read(vpass);
	m.diffuse_blue = file_var_read(vpass);

	m.emissive_red = file_var_read(vpass);
	m.emissive_green = file_var_read(vpass);
	m.emissive_blue = file_var_read(vpass);

	m.alpha = file_var_read(vpass);
	m.power = file_var_read(vpass);

	file_close(vpass);
	
	WriteLog("[X] Task completed.");
	NewLine();
}

/*
--------------------------------------------------
void PassMaterialDataToWindow(MATERIAL *m)

Desc: Copies material data from m to the material
properties window.

Returns: - 
--------------------------------------------------
*/
void PassMaterialDataToWindow(MATERIAL *m) {
	
	WriteLog("[ ] Passing material data to the appropriate panel...");
	NewLine();

	while(!m) wait(1);
	if(!is(panMat_Sub1,SHOW)) return;

	v_ambient_r = m.ambient_red;
	v_ambient_g = m.ambient_green;
	v_ambient_b = m.ambient_blue;

	v_diffuse_r = m.diffuse_red;
	v_diffuse_g = m.diffuse_green;
	v_diffuse_b = m.diffuse_blue;

	v_specular_r = m.specular_red;
	v_specular_g = m.specular_green;
	v_specular_b = m.specular_blue;

	v_emissive_r = m.emissive_red;
	v_emissive_g = m.emissive_green;
	v_emissive_b = m.emissive_blue;

	v_power = m.power;
	v_alpha_m = 100 - m.alpha;
	
	WriteLog("[X] Task completed.");
	NewLine();

}

/*
--------------------------------------------------
void WriteMaterialDataToFile(STRING *file, MATERIAL *m)

Desc: Writes material data from m to file, mostly
custom materials. Or you can use this to save a predefined
material to a file and then pass it back to one of the
custom materials.

Returns: -
--------------------------------------------------
*/
void WriteMaterialDataToFile(STRING *file, MATERIAL *m) {
	
	WriteLog("[ ] Writing material data to ");
	WriteLog(file);
	NewLine();
	
	while(!m) wait(1);

	var vpass = file_open_write(file);
	if(!vpass) {
		
		_beep();
		
		WriteLog(" !! [ERROR] Failed to open ");
		WriteLog(file);
		WriteLog("for writing material data to, returns.");
		NewLine();
		
		return;
		
	}

	// Copy values from the sliders
	m.ambient_red = v_ambient_r;
	m.ambient_green = v_ambient_g;
	m.ambient_blue = v_ambient_b;

	m.specular_red = v_specular_r;
	m.specular_green = v_specular_g;
	m.specular_blue = v_specular_b;

	m.diffuse_red = v_diffuse_r;
	m.diffuse_green = v_diffuse_g;
	m.diffuse_blue = v_diffuse_b;

	m.emissive_red = v_emissive_r;
	m.emissive_green = v_emissive_g;
	m.emissive_blue = v_emissive_b;

	m.alpha = 100 - v_alpha_m;
	m.power = v_power;

	// Write these copied values to vpass handle
	file_var_write(vpass,m.ambient_red);
	file_var_write(vpass,m.ambient_green);
	file_var_write(vpass,m.ambient_blue);

	file_var_write(vpass,m.specular_red);
	file_var_write(vpass,m.specular_green);
	file_var_write(vpass,m.specular_blue);

	file_var_write(vpass,m.diffuse_red);
	file_var_write(vpass,m.diffuse_green);
	file_var_write(vpass,m.diffuse_blue);

	file_var_write(vpass,m.emissive_red);
	file_var_write(vpass,m.emissive_green);
	file_var_write(vpass,m.emissive_blue);

	file_var_write(vpass,m.alpha);
	file_var_write(vpass,m.power);

	file_close(vpass);

	// close the panel.
	if(is(panMat_Sub1,SHOW)) reset(panMat_Sub1,SHOW);
	
	WriteLog("[X] Task completed.");
	NewLine();
}

/*
--------------------------------------------------
void MaterialSave()

Desc: Saves custom materials' data to file using
WriteMaterialDataToFile. It's a WriteMaterialDataToFile
wrapper which will be assigned to the GUI buttons.

Returns: -
--------------------------------------------------
*/
void MaterialSave() {

	if(event_type == EVENT_RELEASE) return;
	
	WriteLog("Saving material to file...");
	NewLine();

	// Material saving is available only to custom materials
	switch(mat_type) {
		
		case select_custom_mat1 :
		WriteMaterialDataToFile(FILE_CUSTOM_MAT_1,mat_custom[0]);
		
		break;
		//////////////////////////////////////////////////////////////
		
		case select_custom_mat2 :
		WriteMaterialDataToFile(FILE_CUSTOM_MAT_2,mat_custom[1]);
		
		break;
		//////////////////////////////////////////////////////////////
		
		case select_custom_mat3 :
		WriteMaterialDataToFile(FILE_CUSTOM_MAT_3,mat_custom[2]);
		
		break;
		//////////////////////////////////////////////////////////////
		
		case select_custom_mat4 :
		WriteMaterialDataToFile(FILE_CUSTOM_MAT_4,mat_custom[3]);
		
		break;
		//////////////////////////////////////////////////////////////
		
		default:
		// This line will never be executed.
		//		printf("Material saving is available only to custom materials.");
		break;
	}
	
}

/*
--------------------------------------------------
void ObjectManipulationCore()

Desc: The following function will handle how the object is manipulated: move, rotate, or scale.
While holding mouse_left, press L/R Alt to downscale the object,
or release it to upscale the object.
Why do I have to comment the lines above if you've already
read through the code.
Actually this is just an extended version of FollowPointer
because I'm too lazy to code a new one.

Returns: -
--------------------------------------------------
*/
void ObjectManipulationCore()
{
	
	WriteLog("[ ] We are at the nuclear core! Oh wait...no, not that stupid core again...");
	NewLine();
	

}

/*
--------------------------------------------------
void ObjectManipulationInterface()

Desc: An ObjectManipulationCore() wrapper. It will
be assigned to newly created objects to enable
manipulating of that object. Contains general code 
for every newly born entity.

Includes two simple scene optimization methods 
(C_TRACE_OPTIMIZATION and DISTANCE_OPTIMIZATION).

Two adjustable constants (CBox.h):

FIXED_CULLING_DISTANCE - Distance (without fog)
FOG_CULLING_DISTANCE - Distance (with fog - should be small)

Returns: -
--------------------------------------------------
*/
int ValidHit() {
	
	if(hit->x||hit->y||hit->z) return 1;
	else return 0;
	
}

void ObjectManipulationInterface()
{
	
	WriteLog("[ ] Executing the stupid function that I have forgotten what it does :v");
	NewLine();
	
	while(!my) wait(1);
	
	STRING *temp_ = my->type;

	my.emask |= ENABLE_CLICK;
	//	my.event = ObjectManipulationCore;

	var Dist = 0;
	
	// These are general code that every entity must have 
	// for example in the editor
	while(my) {
		
		if(mouse_left && !TerrainEditMode && select && !mouse_panel /* && manip_type > 0 && manip_type < 4 */)
		{
			
			if(!temp_pos.x && !temp_pos.y && !temp_pos.z) wait(1);
			
			Scale(marker,SCALE_MARKER_TERRAIN);
			
			if(manip_type == scale && button_state(panMain_Top,3,-1) ) 
			{
				//				GGUIHide();
				if(key_alt) { // i don't place the checker here 'cause it can create jerky effect
					
					if(my.scale_x >= MINIMUM_SCALE_CONSTANT) Scale(my, my.scale_x - SCALE_SPEED);
					
				}
				
				else Scale(my, my.scale_x + SCALE_SPEED);
				
			}
			
			if(manip_type == move && button_state(panMain_Top,1,-1)) {
				
				//				GGUIHide();
				
				v1.x = mouse_pos.x;
				v1.y = mouse_pos.y;
				v1.z = 0;
				vec_for_screen(v1,camera);
				v2.x = mouse_pos.x;
				v2.y = mouse_pos.y;
				v2.z = 200000;
				vec_for_screen(v2,camera);
				
				c_trace(v1.x,v2.x,IGNORE_ME | IGNORE_PASSABLE | IGNORE_MODELS);
				
				if( ValidHit() ) {
					
					vec_set(my.x,hit.x);
					vec_set(my.y,hit.y);
					vec_set(my.z,hit.z); 
					
				}
				
				
			}
			
			if(manip_type == rotate && button_state(panMain_Top,2,-1)) {
				
				//				GGUIHide();
				
				my.pan = -mouse_pos.x;
				//			my.tilt = -mouse_pos.y;
				
			}
			

			wait (1);
		} else if(marker.scale_x != SCALE_MARKER )Scale(marker, SCALE_MARKER);

		//		GGUIShow();
		
		if(PLAYTESTING) {
			
			if(DISTANCE_OPTIMIZATION) {
				
				if(!fog_color) Dist = FIXED_CULLING_DISTANCE;
				else { // Fog is active?
					
					Dist = camera.fog_end + FOG_CULLING_DISTANCE;			   
					
				}
				
				if(vec_dist(player->x,my->x) >= Dist)
				{
					set(my,TRANSLUCENT);
					while(my->alpha > 0)
					{
						my->alpha -= 5 * time_step;
						wait(1);
					}
					reset(my,SHOW);
				}
				else
				{
					reset(my,SHOW);
					my->alpha = 0;
					while(my->alpha <= 100)
					{
						my->alpha += 5 * time_step;
						wait(1);
					}
					reset(my,TRANSLUCENT);
				}
				
			}
			
			else { // C_TRACE_OPTIMIZATION
				
				// Cac entity trong tam nhin khong the cull lan nhau
				if(!is(my,FLAG2)) set(my,FLAG2);
				
				wait (random(20)); // spread the cpu load over 20 consecutive frames
				if(!c_trace(my->x,player->x,IGNORE_ME | IGNORE_FLAG2 | IGNORE_CONTENT | IGNORE_PASSENTS))
				{
					reset(my,INVISIBLE); // then show it!
					while (my.alpha < 100) // run this loop until the entity becomes opaque again
					{
						my.alpha += 25 * time_step;
						wait (1);
					}
					reset(my,TRANSLUCENT); // get rid of some nasty artifacts when the entity is completely visible
				}
				else
				{
					
					set(my,TRANSLUCENT);
					while (my.alpha > 0)
					{
						my.alpha -= 25 * time_step;
						wait(1);
					}
					set(my,INVISIBLE);
				}
				
			}
			
		}
		
		wait(1);
		
	}
	
	WriteLog("[X] Task completed for ObjectManipulationInterface() at ");
	WriteLog(temp_);
	NewLine();

}

/*
--------------------------------------------------
void ExitEvent()

Desc: Peform various tasks prior to exiting craftbox. 
These including writing configuation files, saving variables...

Returns: -
--------------------------------------------------
*/
void ExitEvent() {

	WriteLog("!! [SYS] ExitEvent() was triggered.");
	NewLine();

	if( str_stri(command_str," -dev") ) {
		
		WriteLog("!! [SYS] Closing debuggers...");
		NewLine();
		
		CloseDebug();
		
	}

	WriteLog("!! [SYS] Saving configuration...");
	NewLine();

	ConfigFileWrite(FILE_CONFIG);
	while(proc_status(ConfigFileWrite)) wait(1);

	if(LOGFILEHNDL) {
		
		WriteLog("!! [SYS] Closing LOGFILEHNDL and exiting craftbox!");
		NewLine();
		
		file_close(LOGFILEHNDL);
		
	}

	sys_exit(NULL);

}

/*
--------------------------------------------------
void OptimizeFramerate(var dfr)

Desc: Continuously removing entities in the current view 
until the frame rate equals to or larger than dfr (desired frame rate).

This function should be used with caution because we don't want 
a beautiful green forest to be destroyed just to get a playable 60 fps.

Returns: -
--------------------------------------------------
*/
void OptimizeFramerate(var dfr) {
	
	WriteLog("[ ] Optimizing frame rate...");
	NewLine();
	
	WriteLog("[X] Task completed.");
	NewLine();

}

/*
--------------------------------------------------
int ConfigFileWrite(STRING *cf)

Desc: Writes engine variables to "cf" ( [c]onfig [f]ile ).

Returns: -1 if "cf" couldn't be opened.
--------------------------------------------------
*/
int ConfigFileWrite(STRING *cf) {
	
	WriteLog("[ ] Writing current configuration to file (");
	WriteLog(cf);
	WriteLog(")");
	NewLine();

	var file = file_open_write(cf);
	
	if(!file) {
		
		_beep();
		
		WriteLog("!! [ERROR] The file couldn't be opened, returns -1.");
		NewLine();
		
		return -1;
		
	}

	/*

	Follow this form:

	These variables won't be saved and loaded:
	- d3d_alphadepth
	- d3d_shadowdepth
	- d3d_texdepth 
	- d3d_skydepth

	These variables will be saved/loaded from the .cfg file:
	- d3d_anisotropy
	- d3d_antialias
	- d3d_mipmapping
	- d3d_triplebuffer
	- d3d_lightres
	- video_aspect
	- video_gamma
	- sys_metrics(0), sys_metrics(1)
	- video_depth
	- video_screen

	*/

	// -> Graphics + system
	file_var_write(file,d3d_anisotropy);
	file_var_write(file,d3d_antialias);
	file_var_write(file,d3d_mipmapping);
	file_var_write(file,d3d_triplebuffer);
	file_var_write(file,d3d_lightres);
	file_var_write(file,video_aspect);
	file_var_write(file,video_gamma);

	//	file_var_write(file,video_mode);
	file_var_write(file,sys_metrics(0));
	file_var_write(file,sys_metrics(1));

	file_var_write(file,video_screen);

	file_var_write(file,video_depth);

	file_var_write(file,shot);

	// -> Sound effects' volume
	file_var_write(file,VOL_EFFECTS);
	file_var_write(file,VOL_MUSIC);

	// -> Shaders + PPs parameters

	file_close(file);
	
	WriteLog("[X] Task completed.");
	NewLine();

}

/*
--------------------------------------------------
int ConfigFileRead(STRING *cf)

Desc: Reads engine variables from "cf" ( [c]onfig [f]ile ). 
This function must be called prior to loading the kernel.

Returns: -1 if "cf" couldn't be opened - default settings will 
then be used.
--------------------------------------------------
*/
int ConfigFileRead(STRING *cf) {
	
	WriteLog("[ ] Reading configuration from ");
	WriteLog(cf);
	NewLine();

	var file = file_open_read(cf);
	if(!file) { // Fail? Then use default settings.
		
		_beep();
		
		WriteLog("! [ERROR] The file couldn't be opened, returns -1.");
		NewLine();
		WriteLog("! Will now use default configuration.");
		NewLine();
		
		/* Default config. goes here. */
		video_depth = 32;
		video_set(sys_metrics(0),sys_metrics(1),0,1);
		// other settings remain default (in the game engine/library)
		
		return -1;
		
	}

	// -> Graphics + system
	d3d_anisotropy = file_var_read(file);
	d3d_antialias = file_var_read(file);
	d3d_mipmapping = file_var_read(file);
	d3d_triplebuffer = file_var_read(file);
	d3d_lightres = file_var_read(file);

	video_aspect = file_var_read(file);
	video_gamma = file_var_read(file);

	video_set( file_var_read(file), file_var_read(file),
	0 , file_var_read(file));

	video_depth = file_var_read(file);

	shot = file_var_read(file);

	// -> Sound effects' volume
	VOL_EFFECTS = file_var_read(file);
	VOL_MUSIC = file_var_read(file);

	// -> Shaders + PPs parameters

	file_close(file);
	
	WriteLog("[X] Task completed.");
	NewLine();

}

/*
--------------------------------------------------
void LaunchGameSession()

Desc:

Returns: -
--------------------------------------------------
*/
void LaunchGameSession() {

	if(event_type == EVENT_RELEASE) return;
	
	WriteLog("[ ] Creating a game session, please wait.");
	NewLine();
	
	var olmouse = mouse_mode;
	mouse_mode = 0;
	
	dtimer();
	
	double time;

	// Disable all the panels first
	GMainMenuHide();
	GWorldNewHide();
	GLoadGameHide();
	GOptionsHide();
	GTrophiesHide();
	GHelpHide();
	GInDevHide();
	
	guiCurrentViewPreset = MENU_CAMERA_LAUNCH_GAME;
	
	CreateWorld->alpha = 0;
	set(CreateWorld,SHOW);
	while(CreateWorld->alpha <= 100) {
		
		CreateWorld->alpha += 5 * time_step;
		wait(1);
		
	}
	set(CreateWorldCoffee,SHOW);

	// Begin loading the level
	LoadNewLevel();
	while(proc_status(LoadNewLevel)) wait(1);

	GGUIShow();
	while(proc_status(GGUIShow)) wait(1);
	
	mouse_mode = olmouse;
	
	reset(CreateWorldCoffee,SHOW);
	
	while(CreateWorld->alpha > 0) {
		
		CreateWorld->alpha -= 5 * time_step;
		wait(1);
		
	}	
	reset(CreateWorld,SHOW);
	
	time = dtimer();
	
	SessionsCount += 1;
	
	WriteLog("[X] Task completed, launched game session #",SessionsCount);
	WriteLog(" , cost ",time ); // convert to sec: multiply it by pow(10,6) (microsecs)
	WriteLog(" ms");
	NewLine();

}

/*
--------------------------------------------------
void LoadNewLevel()

Desc: Loads a blank level.

Returns: -
--------------------------------------------------
*/
void LoadNewLevel() {
	
	WriteLog("[ ] Loading ground...");
	NewLine();

	level_load("dry_original.wmb");

	WriteLog("[ ] Creating sky cube...");
	NewLine();
	
	/* _cube = */
	if( !str_cmp(SKYSTR,undef) ) {
		
		// This allows different types of skies can be created.
		if( str_stri(SKYSTR,"+6") ) skycube = ent_createlayer(SKYSTR,SKY | CUBE | SHOW, 1); // If you want to hide the sun, moon, everythiing just set layer to 999
		else skycube = ent_createlayer(SKYSTR,SKY | CYLINDER | SHOW,1);
		
	}
	else { // Default sky cube
		
		// the reason why i use SKYSTR here is: SKYSTR can be read later in act_glass.
		str_cpy(SKYSTR,PATH_SKIES);
		str_cat(SKYSTR,"cubemap+6.tga"); // cubemap+6.tga is mandatory
		skycube = ent_createlayer(SKYSTR,SKY | CUBE | SHOW, 1); // again, set layer = 999 or larger to disable moon, sun, etc.
		
	}
	
	WriteLog("[ ] Loading miscellaneous stuff...");
	NewLine();

	//	camera.ambient = -75;
	
	if(marker) ent_remove(marker);
	//	marker = ent_create("target.mdl",vector(0,0,0),FollowPointer); // Create a mouse pointer.
	//	marker = ent_create(CUBE_MDL,nullvector,FollowPointer);
	cam = ent_create("marker.mdl",vector(0,0,0),free_camera);
	
	//	marker.ObjectType = Neutral;

	manip_type = scale + 1;

	IN_GAME = 1;
	
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

/*
--------------------------------------------------
int Console()

Desc: Available only if the kernel isn't running. 
Used for checking variables' values and/or executing 
engine functions. For the convenience, I defined several 
Con*() functions which perform various tasks without the need 
to enter a long list of commands.

To call this function properly, you must first call UnloadKernel(), 
because the console runs only if the kernel isn't running (as stated before).

Returns: -1 if the kernel is currently running.
--------------------------------------------------
*/
int Console() {

	WriteLog("[SYS] Trying to start the console...");
	NewLine();

	if(KERNEL_IS_RUNNING) {
		
		_beep();
		
		WriteLog("! [ERROR] Console couldn't be executed while the kernel is running, returns -1.");
		NewLine();
		
		return -1;
		
	}
	
	WriteLog("[SYS] Setup console...");

	ConsoleText->pos_x = 2;
	ConsoleText->pos_y = screen_size.y/4;
	toggle(ConsoleText,SHOW);

	// Additional WriteLogs here.

	while(!KERNEL_IS_RUNNING) {
		
		inkey((ConsoleText->pstring)[1]);
		
		if (result == CINPUT_ENTER) { // [Enter]
			
			void* found = var_for_name((ConsoleText->pstring)[1]);
			if (!found) execute((ConsoleText->pstring)[1]);
			
		}
		
		if(result == CINPUT_ESC) { // [Esc]
			
			str_cpy((ConsoleText->pstring)[1],"Loading kernel...");
			
			LoadKernel();
			while(proc_status(LoadKernel)) wait(1);
			
			LoopKernel();
			
			str_cpy((ConsoleText->pstring)[1],"Switching off console...");
			
			break;	
			
		}
		
		if(str_cmp( (ConsoleText.pstring)[1],VAREXPLORER_EXITSTR )) {
			
			WriteLog("[SYS] Exit event was triggered from the console.");
			NewLine();
			
			ExitEvent();
			
		}
		
		if(str_cmp( (ConsoleText.pstring)[1],VAREXPLORER_REPORTSTR )) {
			
			WriteLog("[SYS] Preparing to run the report generator, please wait.");
			NewLine();
			
			_beep();
			
		}
		
		if(str_cmp( (ConsoleText.pstring)[1],VAREXPLORER_FACTORYSTR )) {
			
			WriteLog("[SYS] Preparing to reset settings to its original state, please wait.");
			NewLine();
			
			_beep();
			
		}
		
		wait(1);
		
	}

	reset(ConsoleText,SHOW);

	WriteLog("[SYS] The console has been closed. Probably the user has started the kernel again, or craftbox is preparing to shut down itself.");
	NewLine();

}

/*
--------------------------------------------------
void UnloadKernel()

Desc: This will be executed after the kernel has 
finished running, after that it will redirect to the console.

Returns: -
--------------------------------------------------
*/
int UnloadKernel() {

	proc_kill(4);

	WriteLog("[SYS] Unloading the kernel...");
	NewLine();

	KERNEL_IS_RUNNING = 0;

	// From GCreditsShow().
	GMainMenuHide();

	level_load(NULL);
	vec_set(screen_color,vector(255,255,255));

	GGUIHide();

	Console();

	WriteLog("[SYS] Successfully unloaded the kernel. Use the console to continue controlling craftbox.");
	NewLine();

}

/*
--------------------------------------------------
int ReloadKernel()

Desc: Basically this is just the same as a combination
of UnloadKernel() and LoadKernel(). However, it reduces
a few unnecessary calls (for example)

Returns: -
--------------------------------------------------
*/
int ReloadKernel() {

	WriteLog("[SYS] Reloading the kernel");
	NewLine();

	wait(1);

	WriteLog("[SYS] Successfully reloaded the kernel.");
	NewLine();

}

/*
--------------------------------------------------
void _beep()

Desc: A beep() alternative. It does not halt game execution.

Returns: -
--------------------------------------------------
*/
void _beep() {

	if(LOGFILEHNDL) snd_play(__beep,100,0);

}

/*
--------------------------------------------------
void LoadKernel()

Desc: Sets up the environment and calls a list of 
methods that is essential for starting up craftbox.
Sets KERNEL_IS_RUNNING to 1 if it had been fully loaded.

Returns: -
--------------------------------------------------
*/
void LoadKernel() {

	WriteLog("[SYS] Loading kernel");
	NewLine();
	
	// Let's precache some contents first
	//	PrecacheContent();
	//	while(proc_status(PrecacheContent)) wait(1);

	STRING *_s = "#64";

	// If you want, you can call GetSystemMetrics (windows.h) instead of Gamestudio's sys_metrics.	
	str_cpy((PreMainMenuLoading.pstring)[0],"Testing various settings...");
	
	WriteLog("[ ] Testing various settings.");
	NewLine();

	/* Resolution Test */
	float WIDTH = sys_metrics(0), HEIGHT = sys_metrics(1);

	str_for_num(_s,WIDTH);
	str_cat((PreMainMenuLoading.pstring)[0],_s);
	str_cat((PreMainMenuLoading.pstring)[0]," ");

	str_for_num(_s,HEIGHT);
	str_cat((PreMainMenuLoading.pstring)[0],_s);
	str_cat((PreMainMenuLoading.pstring)[0]," ");

	if(WIDTH < MINIMUM_RESOLUTION_X ||
	HEIGHT < MINIMUM_RESOLUTION_Y ) {
		
		UnloadKernel(); // switch off the kernel and enter console mode.
		while(proc_status(UnloadKernel)) wait(1);  // or else some kind of stupid error would pop up.
		
		str_cpy((ConsoleText.pstring)[1],"craftbox requires at least a 1024x768 resolution screen to run properly.");
		str_cpy((ConsoleText.pstring)[2],"Please switch to the resolution that is larger or equal to 1024x768 and start craftbox again.");
		
		return;
		
	}

	/* Boot Mode Test */
	str_for_num(_s,sys_metrics(67));
	str_cat((PreMainMenuLoading.pstring)[0],_s);
	str_cat((PreMainMenuLoading.pstring)[0]," ");

	/* Mouse Test */
	str_for_num(_s,sys_metrics(19));
	str_cat((PreMainMenuLoading.pstring)[0],_s);
	str_cat((PreMainMenuLoading.pstring)[0]," ");

	if(!sys_metrics(19)) {
		
		UnloadKernel(); // switch off the kernel and enter console mode.
		while(proc_status(UnloadKernel)) wait(1);  // or else some kind of stupid error would pop up.
		
		str_cpy((ConsoleText.pstring)[1],"Plug in a mouse and restart craftbox.");
		
		return;
		
	}

	/* Processor Test */
	str_for_num(_s,sys_metrics(73));
	str_cat((PreMainMenuLoading.pstring)[0],_s);
	str_cat((PreMainMenuLoading.pstring)[0]," ");

	str_remove(_s);
	
	WriteLog("[ ] Setting up events, calling main modules.");
	NewLine();
	
	dtimer();
	
	double timer_;
	STRING *timer__ = "#100";
	
	GPreMainMenu();

	str_cpy((PreMainMenuLoading.pstring)[1],LOADCRAFTBOX_1);

	on_bksp = TakeScreenshot;
	on_exit = ExitEvent;
	on_close = ExitEvent;
	on_level = on_level_event;

	// Initialization for loopix-project.com's MystyMood_Lite-C
	sky_curve = 2;
	sky_clip = -10;
	
	// This allows custom cursors to be created (by copying strings to STRING *mouse)
	BMAP *mouseimg;
	if(str_len(mouse_str) && !str_cmp(mouse_str,undef)) mouseimg = bmap_create(mouse_str);
	else mouseimg = bmap_create("mouse_pointer.png"); // default cursor
	mouse_map = mouseimg;

	vec_zero(parted_temp_vec);
	vec_zero(parted_temp2_vec);
	
	str_cpy(seedEnt,undef);
	str_cpy(TEMPSTR,undef);
	str_cpy(FILE_GAME_INTRO_VIDEO,undef);
	str_cpy(FILE_GAME_OUTRO_VIDEO,undef);
	str_cpy(GROUNDSTR,undef);
	str_cpy(SKYSTR,undef);

	//	MaterialCopyColor(pTexColor, mtl_pTex1);

	panHome.alpha = panProp.alpha = DEFAULT_ALPHA;

	timer_ = dtimer()/pow(10,3);
	str_cat((PreMainMenuLoading.pstring)[1],str_for_num(timer__,timer_));
	str_cat((PreMainMenuLoading.pstring)[1],"s");

	str_cpy((PreMainMenuLoading.pstring)[1],LOADCRAFTBOX_2);
	dtimer();

	// Initialize the databases and load them.
	//	LoadSavedBMAPs();

	// Initialize shaders
	//	SetupShader();
	
	// Load ogg music from PATH_MUSIC
	mpLoad(PATH_MUSIC,EXT_MUSIC);
	while(proc_status(mpLoad)) wait(1);
	
	str_cpy(PLAYTEST_LOADSCREENSTR,undef);
	camera.fog_start = 0;

	// Intialize and read custom materials' properties.
	int i;
	for(i = 0;i < 4;i++) mat_custom[i] = mtl_create();

	ReadMaterialDataFromFile(mat_custom[0],FILE_CUSTOM_MAT_1);
	ReadMaterialDataFromFile(mat_custom[1],FILE_CUSTOM_MAT_2);
	ReadMaterialDataFromFile(mat_custom[2],FILE_CUSTOM_MAT_3);
	ReadMaterialDataFromFile(mat_custom[3],FILE_CUSTOM_MAT_4);

	original_moon_scale_fac = moon_scale_fac;
	original_time_speed_night = time_speed_night;
	original_night_sky_scale_x = night_sky_scale_x;
	original_night_sky_speed_x = night_sky_speed_x;
	original_fog_color = fog_color;
	original_camera_fog_start = camera->fog_start;
	original_camera_fog_end = camera->fog_end;
	original_sun_light = sun_light;
	original_d3d_fogcolor1r = d3d_fogcolor1.red;
	original_d3d_fogcolor1g = d3d_fogcolor1.green;
	original_d3d_fogcolor1b = d3d_fogcolor1.blue;

	clipboard.name = str_create("#300");

	timer_ = dtimer()/pow(10,3);
	str_cat((PreMainMenuLoading.pstring)[1],str_for_num(timer__,timer_));
	str_cat((PreMainMenuLoading.pstring)[1],"s");

	// If we want a video to be played... 

	// Intialize and load the GUI system.
	str_cpy((PreMainMenuLoading.pstring)[2],LOADCRAFTBOX_3);
	dtimer();

	GGUIInit();
	while(proc_status(GGUIInit)) wait(1);

	/*
	// Load a blank level.
	LoadNewLevel();

	//	LoadMystymood(1,1);

	//	def_move();
	*/

	timer_ = dtimer()/pow(10,6);
	str_cat((PreMainMenuLoading.pstring)[2],str_for_num(timer__,timer_));
	str_cat((PreMainMenuLoading.pstring)[2],"s");

	reset(BackgroundScreen,SHOW);
	reset(PreMainMenuLoading,SHOW);
	
	WriteLog("[ ] Executing miscellaneous stuff.");
	NewLine();
	
	// Fill the large pools
	FolderScan(files_list_SKYSTR_Pool, PATH_SKIES , str_create("tga") );
	while(proc_status(FolderScan)) wait(1);
	
	FolderScan(files_list_GROUNDSTR_Pool, PATH_GROUNDS, str_create("wmb") );
	while(proc_status(FolderScan)) wait(1);
	
	FolderScan(files_list_LOADGAMESTR_Pool, PATH_SAVEDGAMES, EXT_SAVEDGAMES);
	while(proc_status(FolderScan)) wait(1);

	KERNEL_IS_RUNNING = 1;
	
	WriteLog("[ ] Loading main menu...");
	NewLine();
	
	GLoadMainMenu();
	while(proc_status(GLoadMainMenu)) wait(1);
	
	// This isn't supposed to be in the kernel code...
	// mpPlay("Funny_Death_-_She_Never_Existed.ogg");
	
	mouse_mode = 4;

	WriteLog("[X] Finished loading the kernel.");
	NewLine();

}

/*
--------------------------------------------------
void LoopKernel()

Desc: The code inside this function will always be
executed until craftbox exits. After that, UnloadKernel()
will take care of the rest.

Returns: -
--------------------------------------------------
*/
void LoopKernel() {

	if(!KERNEL_IS_RUNNING) {
		
		_beep();
		
		WriteLog("[SYS] An attempt to launch LoopKernel() but the kernel hasn't been loaded, aborting.");
		NewLine();
		
		return;
		
	}

	while( KERNEL_IS_RUNNING ) {
		
		// This is optional, it's for low-end computers. Comment them
		// all the instructions from '{' to '}' (plus the if) to remove this feature.
		if(fog_color) {
			
			camera.clip_far = camera.fog_end + FOG_END_CLIP; // Clip far
			camera.clip_near = camera.fog_start - FOG_START_CLIP; // Clip near
			
		}
		
		// These key combinations can be pressed even if game isn't running, as long as the kernel is up and running already.
		// for example: the music player
		if(key_m) {
			
			while(key_m) wait(1);
			ToggleMusicPlayer();
			
		}
		
		if(key_t) {
			
			while(key_t) wait(1);
			GToggleStatistics();
			
		}
		
		if(IN_GAME) 
		{
			
			//			// Prevent the cursor from going outside the level border
			if(!temp_pos.x) temp_pos.x = level_ent.max_x;
			if(!temp_pos.y) temp_pos.y = level_ent.max_y;
			if(!temp_pos.z) temp_pos.z = level_ent.max_z;	
			
			if(mouse_left) 
			{
				
				while(mouse_left) wait(1);
				
				if(!temp_pos.x && !temp_pos.y && !temp_pos.z)  wait(1); // couldnt return here
				
				if(!mouse_panel && !TerrainEditMode)
				{
					
					// Something is on top...
					if(mouse_ent) {
						
						//..but it's a neutral or terrain object
						if(mouse_ent.ObjectType == Neutral || mouse_ent.ObjectType == Terrain) {
							
							if(manip_type >= scale + 1) {
								
								CreateObject();
								
							}
							
						}
						
						else {
							
							if(select)
							{
								
								if(select.ObjectType == Light) GLightWindowHide();
								if(select.ObjectType > Object && select.ObjectType <= ObjectNode) GPropertiesWindowHide();
								if(select.ObjectType == Sound) GSoundWindowHide();
								if(select.ObjectType == Particle) GParticleWindowHide();
								//							if(select.ObjectType == Terrain) return;
								
								// TRA HET CHO NGUOI TRA HET CHO NGUOI ~~~ =))
								select.material = mat_temp;
								select = NULL;
							}
							
							select = mouse_ent;
							
							if(select.material) mat_temp = select.material; // Luc nay select da duoc xac dinh nen ta cu thoai mai
							select.material = mat_select;
							
							if(select.ObjectType == Light) GLightWindowShow();
							else GLightWindowHide();
							
							if(select.ObjectType > Object && select.ObjectType <= ObjectNode) GPropertiesWindowShow();
							else GPropertiesWindowHide();
							
							if(select.ObjectType == Sound) GSoundWindowShow();
							else GSoundWindowHide();
							
							if(select.ObjectType == Particle) GParticleWindowShow();
							else GParticleWindowHide();
							
							PassObjectPropertiesToGUI(select);
							
						}
						
					}
					
					else { // Nothing is on top
						
						// Allow placing entities freely only on top 
						// of neutral objects (e.g. terrains) or on solid
						// ground (which means !mouse_ent)
						//						if(!mouse_ent) { // Nothing is on top of the cursor
							
							if(manip_type >= scale + 1) {
								
								CreateObject();
								
							}
							
						//						}
						
					}
					
					/*
					
					// Something is on top but it's a neutral or terrain object
					else if(mouse_ent.ObjectType == Neutral || mouse_ent.ObjectType == Terrain) {
						
						if(manip_type == scale + 1) {
							
							CreateObject();
							
						}
						
					}
					
					// others
					else
					{
						
						if(select)
						{
							
							if(select.ObjectType == Light) GLightWindowHide();
							if(select.ObjectType > Object && select.ObjectType <= ObjectNode) GPropertiesWindowHide();
							if(select.ObjectType == Sound) GSoundWindowHide();
							if(select.ObjectType == Particle) GParticleWindowHide();
							//							if(select.ObjectType == Terrain) return;
							
							select.material = mat_temp;
							select = NULL;
						}
						
						select = mouse_ent;
						
						mat_temp = select.material; // Luc nay select da duoc xac dinh nen ta cu thoai mai
						select.material = mat_select;
						
						if(select.ObjectType == Light) GLightWindowShow();
						else GLightWindowHide();
						
						if(select.ObjectType > Object && select.ObjectType <= ObjectNode) GPropertiesWindowShow();
						else GPropertiesWindowHide();
						
						if(select.ObjectType == Sound) GSoundWindowShow();
						else GSoundWindowHide();
						
						if(select.ObjectType == Particle) GParticleWindowShow();
						else GParticleWindowHide();
						
						PassObjectPropertiesToGUI(select);
						
					}
					
					*/
					
					wait(1);
					
				}		
				
			}
			
			// These keys are combined together with the Ctrl key.
			if(key_ctrl) {
				
				if(key_c) {
					
					while(key_c) wait(1);
					ObjectCopy();
					
				}
				
				if(key_x) {
					
					while(key_x) wait(1);
					ObjectCut();
					
				}
				
				if(key_v) {
					
					while(key_v) wait(1);
					ObjectPaste();
					
				}
				
				if(key_n) {
					
					while(key_n) wait(1);
					LoadNewLevel();
					
				}
				
			}
			
			// These keys are pressed solely.
			
			// I seperately defined key_esc here
			// so I must disable the one that has been defined 
			// in ka7def2.c/default.c
			if(key_esc && !from_test_play && !proc_status(LoadPlayground) ) { // If ESC is pressed and we're not pressing ESC while we were in testing mode.
				// plus don't allow [ESC] to be pressed while preparing playtest.
				
				while(key_esc) wait(1);
				
				//				GHomeShow();
				
				if(is(BackMenu_Background,SHOW) ) GBackMenuHide();
				else GBackMenuShow();
				
				
				
			}
			
			/*
			
			if(key_t) 
			{
				while(key_t) wait(1);
				ObjectIDNumber++;
			}
			
			if(key_y) {
				while(key_y) wait(1);
				ObjectIDNumber--;
			}
			
			*/
			
			if(key_r) {
				
				while(key_r) wait(1);
				you = ent_next(NULL); // Point to the first entity in the list
				while(you != NULL) {
					
					ptr_remove(you);
					you = ent_next(you);
					
				}
				
				marker = ent_create("target.mdl",nullvector,FollowPointer); // Create a mouse pointer.
				cam = ent_create("marker.mdl",vector(0,0,0),free_camera);
				
				marker.ObjectType = Neutral;
				
			}
			/*
			
			if(PLAYTESTING && play_as_fp) {
				
				wait(-1);
				reset(panCAMRecorderREC,SHOW);
				wait(-1);
				set(panCAMRecorderREC,SHOW);
				
			}
			
			*/
			
		}
		wait(1);
	}

	WriteLog("[X] Kernel looping code has finished its job.");
	NewLine();

}

/*
--------------------------------------------------
void NewLine()

Desc: Writes a new line to LOGFILEHNDL.

Returns: -
--------------------------------------------------
*/
void NewLine() {

	// Windows uses CR/LF
	file_asc_write(LOGFILEHNDL,13); // CR
	file_asc_write(LOGFILEHNDL,10); // LF

}

/*
--------------------------------------------------
int WriteLog(STRING *str)


--------------------------------------------------
*/
int WriteLog(STRING *str) {

	if(LOGFILEHNDL) {
		
		file_str_write(LOGFILEHNDL,str);
		//		NewLine();
		
	}

	else return -1;

}

/*
--------------------------------------------------
int WriteLog(STRING * str, int i)


--------------------------------------------------
*/
int WriteLog(STRING * str, int i) {

	if(LOGFILEHNDL) {
		
		file_str_write(LOGFILEHNDL,str);
		file_var_write(LOGFILEHNDL,(int)i);
		//		NewLine();
		
	}

	else return -1;

}

/*
--------------------------------------------------
int WriteLog(STRING *str, var _v)


--------------------------------------------------
*/
int WriteLog(STRING *str, var _v) {

	if(LOGFILEHNDL) {
		
		file_str_write(LOGFILEHNDL,str);
		file_var_write(LOGFILEHNDL,_v);
		//		NewLine();      
		
	}

	else return -1;

}

/*
--------------------------------------------------
int WriteLog(STRING *str, double d)


--------------------------------------------------
*/
int WriteLog(STRING *str, double d) {

	if(LOGFILEHNDL) {
		
		file_str_write(LOGFILEHNDL,str);
		file_var_write(LOGFILEHNDL,(double)d);
		//		NewLine();
		
	}

	else return -1;

}

/*
--------------------------------------------------
int WriteLog(STRING *str, BOOL b)


--------------------------------------------------
*/
int WriteLog(STRING *str, BOOL b) {

	if(LOGFILEHNDL) {
		
		file_str_write(LOGFILEHNDL,str);
		
		if(b) file_str_write(LOGFILEHNDL,"true");
		else file_str_write(LOGFILEHNDL,"false");
		
		//		NewLine();
		
	}

	else return -1;

}

/*
--------------------------------------------------
int WriteLog(STRING *str, OBJECTSTRUCT *objectstruct)


--------------------------------------------------
*/
int WriteLog(STRING *str, OBJECTSTRUCT *objectstruct) {

	if(LOGFILEHNDL) {
		
		while(!objectstruct) wait(1);
		
		WriteLog("Inside ");
		WriteLog( objectstruct->name );
		NewLine();
		
		WriteLog(objectstruct->_scale_x); NewLine();
		WriteLog(objectstruct->_scale_y); NewLine();
		WriteLog(objectstruct->_scale_z); NewLine();
		WriteLog(objectstruct->_pan); NewLine();
		WriteLog(objectstruct->_tilt); NewLine();
		WriteLog(objectstruct->_roll); NewLine();
		WriteLog(objectstruct->_alpha); NewLine();
		WriteLog(objectstruct->_ambient); NewLine();
		WriteLog(objectstruct->name); NewLine();
		WriteLog(objectstruct->pPhysics); NewLine();
		WriteLog(objectstruct->pStatic); NewLine();
		
		int i = 0;
		while(i < MAX_PUBLIC_FLAGS ) {
			
			WriteLog(objectstruct->_flags[i]);
			NewLine();
			
			i++;
			
		}
		
		i = 0;
		while(i < MAX_PUBLIC_SKILLS + MAX_PRIVATE_SKILLS) {
			
			WriteLog(objectstruct->_skill[i]);
			NewLine();
			
			i++;
			
		}
		
		WriteLog(objectstruct->mass); NewLine();
		WriteLog(objectstruct->friction); NewLine();
		WriteLog(objectstruct->_red); NewLine();
		WriteLog(objectstruct->_green); NewLine();
		WriteLog(objectstruct->_blue); NewLine();
		WriteLog(objectstruct->_range); NewLine();
		WriteLog(objectstruct->_LightMode); NewLine();
		WriteLog(objectstruct->dp); NewLine();
		
		WriteLog("Raw data produced. For more information, refer to the OBJECTSTRUCT struct definition on CBox.h");
		NewLine();
		
	}

	else return -1;

}

/*
--------------------------------------------------
void CBox_startup()

Desc: Unlike LoopKernel() which runs only if the kernel has been 
successfully loaded, CBox_startup() runs globally, that is, independent 
from any value tests, and exits only if craftbox exits. This is used
for setting up variables, controlling/executing functions - things 

The _startup prefix is vital.

Returns: -
--------------------------------------------------
*/
void CBox_startup() {

	WriteLog("[SYS] Loading CBox_startup()...");
	NewLine();

	// Read and setup video settings prior to executing other functions.
	ConfigFileRead(FILE_CONFIG);

	video_window(NULL,NULL,0,"craftbox Pre-alpha");
	
	// These are fixed variables 
	mouse_range = 500000;
	random_seed(0); // e.g. random light generators.
	terrain_chunk = 0; //
	fps_max = 75;
	clip_particles = 1; // cut off particles from far
	preload_mode = 3+4; // preload ents & precalculate env lights
	if(edition > 2) max_lights = 100; // still can't afford a comm license
	//	max_paths = max_entities = max_particles = pow(10,5);
	tex_share = 1;

	while(1) {
		
		// These keys are combined together with the Alt key.
		if(key_alt) {
			
			if(key_f4) {
				
				while(key_f4) wait(1);
				ExitEvent();
				
			}
			
		}
		
		if(KERNEL_IS_RUNNING) {
			
			if(select) {
				
				
				
				if(key_del) {
					
					//					RemoveFromTextureProjectionArray(select);
					
					ptr_remove(select);
					
					// After this nothing is selected so we disable the panels.
					GPropertiesWindowHide();
					GSoundWindowHide();
					GLightWindowHide();
					GParticleWindowHide();
					
				}
				
				//////////////////////////////////////////////////////////////
				// panProp
				select.alpha = 100 - v_alpha;
				select.ambient = v_ambient;
				
				if(button_state(panProp_1,1,-1)) set(select,BRIGHT);
				else reset(select,BRIGHT);
				
				if(button_state(panProp_1,2,-1)) set(select,INVISIBLE);
				else reset(select,INVISIBLE);
				
				if(button_state(panProp_1,3,-1)) set(select,NOFOG);
				else reset(select,NOFOG);
				
				if(button_state(panProp_1,4,-1)) set(select,OVERLAY);
				else reset(select,OVERLAY);
				
				if(button_state(panProp_1,5,-1)) set(select,PASSABLE);
				else reset(select,PASSABLE);
				
				if(button_state(panProp_1,6,-1)) set(select,POLYGON);
				else reset(select,POLYGON);
				
				if(button_state(panProp_1,7,-1)) set(select,SHADOW);
				else reset(select,SHADOW);
				
				if(button_state(panProp_1,8,-1)) set(select,TRANSLUCENT);
				else reset(select,TRANSLUCENT);
				//////////////////////////////////////////////////////////////
				
				//////////////////////////////////////////////////////////////
				// panLight
				select.red = v_lred;
				select.blue = v_lblue;
				select.green = v_lgreen;
				select.lightrange = v_lrange;
				
				if(button_state(panLight,2,-1)) {
					
					button_state(panLight,3,-1);
					select.LightMode = Disco;
					
				}
				
				if(button_state(panLight,3,-1)) {
					
					button_state(panLight,2,-1);
					select.LightMode = Flick;
					
				}
				
				if(button_state(panLight,2,-1) && button_state(panLight,3,-1)) {
					
					button_state(panLight,2,0);
					button_state(panLight,3,0);
					select.LightMode = 0;
					
				}
				
				// panProp
				// select.material now holds mat_select
				// so we must pass something else
				
				//				select.z = 3000 - v_objectz;
				
			}
			
			else { // If select isn't selected.
				
				GPropertiesWindowHide(); // GPropertiesWindowHide() somehow got stuck
				GSoundWindowHide();
				GLightWindowHide();
				GParticleWindowHide();
				
			}
			
		}	
		wait(1);
		
	}

	WriteLog("[X] CBox_startup() was terminated.");
	NewLine();

}

/*
--------------------------------------------------
void guiViewPreset (int* ref, int id, VECTOR* _pos, VECTOR* _ang)

Desc:

Returns: -
--------------------------------------------------
*/
void guiViewPreset (int* ref, int id, VECTOR* _pos, VECTOR* _ang)
{
	VECTOR pos, ang;
	vec_set(&pos, _pos);
	vec_set(&ang, _ang);

	while ( ! IN_GAME )
	{  
		if (*ref == id)
		{
			vec_lerp(camera.x, camera.x, pos.x, clamp(guiViewPresetSpeed * time_step, 0, 1));
			vec_lerp(camera.pan, camera.pan, ang.x, clamp(guiViewPresetSpeed * time_step, 0, 1));
		} 
		
		wait(1);
	}
}

/*
--------------------------------------------------
void free_camera()

Desc: This is the camera controller I found when I was tweaking Mystymood.
+ 5.7.2013 : This camera is good, but I have to partly rewrite it
because...well, I won't explain, find out for yourself.
This code won't be checked against PLAYTESTING because
it will be killed prior to set PLAYTESTING to 1.
and restored later when PLAYTESTING has been set to 0.
+ 13.10.2013, 22.10.2013 : Modified.

Returns: -
--------------------------------------------------
*/
void free_camera()
{

	WriteLog("[ ] Setting up camera...");
	NewLine();

	var doublefactor;

	set(my, POLYGON | PASSABLE | INVISIBLE);
	
	/*
	
	vec_set(camera.x,my.x);
	vec_set(camera.pan,my.pan);
	vec_set(camera.tilt,my.tilt);
	
	*/

	while(1)
	{
		
		if( PLAYTESTING ) wait(1);
		
		if(key_shift) doublefactor = 3;
		else doublefactor = 1; // prevent multiplication by 0
		
		//		if(camera.tilt >= 90) camera.tilt = 90;
		//		if(camera.tilt <= -90) camera.tilt = -90;
		
		// 60 = speed
		camera_force.x = ( (key_w || key_cuu) - (key_s || key_cud) )*60*doublefactor*time_step;
		camera_force.y = ( (key_a || key_cul) - (key_d || key_cur) )*60*doublefactor*time_step;
		
		c_move(my,camera_force,nullvector,GLIDE+IGNORE_PASSABLE+IGNORE_PASSENTS+IGNORE_PUSH);
		vec_set(camera.x,vector(my.x,my.y,my.z+15));
		
		// 3 = rotation speed
		camera.tilt += 3 * mouse_right*mouse_force.y * time_step;
		camera.pan += 3 * mouse_right*-mouse_force.x * time_step;
		
		vec_set(my.tilt,camera.tilt);
		vec_set(my.pan,camera.pan);
		
		wait(1);
	}
	
}

////////////////////////////////////////////////////////////
// Mystymood
// Template file v5.202 (02/20/02)
////////////////////////////////////////////////////////////////////////
// File: lflare.wdl
//	WDL code for lens flare and lighting effects
//
// 2007 Modified by David Lancaster and Loopix, based on ideas of HeelX
// Lite-C conversion by Alexis Rozhkov aka Shadow
//
// www.loopix-project.com
////////////////////////////////////////////////////////////////////////

/*
--------------------------------------------------
void flare_init(ENTITY *flare_ent)

Desc:

Returns: - 
--------------------------------------------------
*/
void flare_init(ENTITY *flare_ent)
{
	
	while(!flare_ent) wait(1);

	WriteLog("[ ] Intializing lens flare for ");
	WriteLog( (STRING *) flare_ent->type );
	NewLine();

	my = flare_ent;
	my.flags2 &= ~SHOW;
	my.flags |= (BRIGHT|PASSABLE|TRANSLUCENT);
	
	WriteLog("[X] Task completed.");
	NewLine();
	
}

/*
--------------------------------------------------
void flare_place(ENTITY *flare_ent)

Desc: Places a flare at temp.x/temp.y deviations from screen center

Returns: -
--------------------------------------------------
*/
void flare_place(ENTITY *flare_ent)
{

	// Do not flood the log file

	my = flare_ent;
	my.flags2 |= SHOW;

	camera.pan%=360;//needed to keep the correct sun_angle for lensflare visibility

	// multiply the pixel deviation with the pivot factor,
	// and add the screen center
	my.x = ctemp.x*my.pivot_dist + 0.5*screen_size.x;
	my.y = ctemp.y*my.pivot_dist + 0.5*screen_size.y;
	my.z = 1000;	// screen distance, determines the size of the flare

	if(my == flare1_ent)
	{
		vec_set(temp2,sun_pos);
		you = player;	
		
		c_trace(camera.x,temp2.x,IGNORE_ME | IGNORE_YOU | IGNORE_PASSABLE | IGNORE_SPRITES | SCAN_TEXTURE);
		if(trace_hit)
		{
			
			if(flare1_ent.alpha > 0) flare1_ent.alpha -= flare_fadespeed * time_step;
			else flare1_ent.alpha = 0;
			
		}
		else
		{
			if((camera.pan > sun_angle.pan + 25) || (camera.pan < sun_angle.pan - 25) || (camera.tilt < sun_angle.tilt - 20) || (camera.tilt > sun_angle.tilt + 20))
			{
				
				if(flare1_ent.alpha > 0) flare1_ent.alpha -= flare_fadespeed * time_step;
				else flare1_ent.alpha = 0;
				
			}
			else
			{	
				temp2.x = sqrt(abs(((my.x - (0.5*screen_size.x))*(my.x - (0.5*screen_size.x)))+((my.y - (0.5*screen_size.y))*(my.y - (0.5*screen_size.y)))));
				if(abs(temp2.x) > (0.5*screen_size.x))
				{
					
					flare1_ent.alpha = flare_alpha - (abs(temp2.x) - (0.5*screen_size.x));
					if(flare1_ent.alpha < 0) flare1_ent.alpha = 0;
					
				}
				else
				{
					
					if(flare1_ent.alpha < flare_alpha) flare1_ent.alpha += flare_fadespeed * time_step;
					else flare1_ent.alpha = flare_alpha;
					
				}
			}
		}
		
		if (flare1_ent.alpha < 0) flare1_ent.alpha = 0;
		if (flare1_ent.alpha > flare_alpha) flare1_ent.alpha = flare_alpha;
	}
	rel_for_screen(my.x,camera);
}

/*
--------------------------------------------------
void LoadMystymoodLensflare()

Desc:

Returns: -
--------------------------------------------------
*/
void LoadMystymoodLensflare()
{

	WriteLog("[ ] Activating lens flare");
	NewLine();

	flare_init(flare1_ent);
	flare_init(flare2_ent);
	flare_init(flare4_ent);
	flare_init(flare5_ent);
	flare_init(flare6_ent);
	flare_init(flare7_ent);
	flare_init(flare8_ent);
	flare_init(flare9_ent);
	flare_init(flare10_ent);
	flare_init(flare11_ent);
	flare_init(flare12_ent);
	flare_init(flare13_ent);
	flare_init(flare14_ent);
	flare_init(flare15_ent);
	flare_init(flare16_ent);
	flare_init(flare17_ent);
	flare_init(flare18_ent);
	flare_init(flare19_ent);
	flare_init(flare20_ent);

	wait(1);

	lens_active = 1;
	
	WriteLog("[X] Task completed for LoadMystymoodLensflare().");
	NewLine();

	while(lens_active)
	{
		vec_set(ctemp,sun_pos);
		vec_to_screen(ctemp,camera);
		
		ctemp.x -= 0.5 * screen_size.x;
		ctemp.y -= 0.5 * screen_size.y;
		
		flare_place(flare1_ent);
		flare_place(flare2_ent);	
		flare_place(flare4_ent);
		flare_place(flare5_ent);
		flare_place(flare6_ent);
		flare_place(flare7_ent);
		flare_place(flare8_ent);
		flare_place(flare9_ent);
		flare_place(flare10_ent);
		flare_place(flare11_ent);
		flare_place(flare12_ent);
		flare_place(flare13_ent);
		flare_place(flare14_ent);
		flare_place(flare15_ent);
		flare_place(flare16_ent);
		flare_place(flare17_ent);
		flare_place(flare18_ent);
		flare_place(flare19_ent);
		flare_place(flare20_ent);
		
		flare1_ent.alpha = flare1_ent.alpha - (sky_cloud3.alpha/10);
		flare2_ent.alpha = flare1_ent.alpha;		
		flare4_ent.alpha = flare1_ent.alpha;
		flare5_ent.alpha = flare1_ent.alpha;
		flare6_ent.alpha = flare1_ent.alpha;
		flare7_ent.alpha = flare1_ent.alpha;
		flare8_ent.alpha = flare1_ent.alpha;
		flare9_ent.alpha = flare1_ent.alpha;
		flare10_ent.alpha = flare1_ent.alpha;
		flare11_ent.alpha = flare1_ent.alpha;
		flare12_ent.alpha = flare1_ent.alpha;
		flare13_ent.alpha = flare1_ent.alpha;
		flare14_ent.alpha = flare1_ent.alpha;
		flare15_ent.alpha = flare1_ent.alpha;
		flare16_ent.alpha = flare1_ent.alpha;
		flare17_ent.alpha = flare1_ent.alpha;
		flare18_ent.alpha = flare1_ent.alpha;
		flare19_ent.alpha = flare1_ent.alpha;
		flare20_ent.alpha = flare1_ent.alpha;
		wait(1);
	}

	lens_active = 0;

	WriteLog("[X] Deactivated lens flare.");
	NewLine();

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
////MystyMood sky/sun/weather template...works without shader, uses 3dgs sky entitys!
////
////Note: All sky/weather values must be adjusted in this script...exept from the mysty_mood trigger values 
////that can be adjusted for each trigger dummy via the behaviour panel in WED.
////
////Jun 07 by www.loopix-project.com
////Nov 07 Lite-C conversion by Alexis Rozhkov aka Shadow
//// 22.10.2013: U just tested this with Shade-C 0.91, worked just fine. Shade-C EVO? Maybe later.
/////////////////////////////////////////////////////////////

/*
--------------------------------------------------
void func_fade_colors(var *col_target, var *col1, var *col2)

Desc: 

Returns: -
--------------------------------------------------
*/
void func_fade_colors(var *col_target, var *col1, var *col2)
{
	var i = 0;
	if(i < 100)
	{
		i = minv(i + fog_fade_speed*time_step, 100);
		vec_lerp(col_target, col1, col2, i/100);
	}
}


/*
--------------------------------------------------
void func_particle_seed_infinity(PARTICLE *p)

Desc: 

Returns: -
--------------------------------------------------
*/
void func_particle_seed_infinity(PARTICLE *p)
{

	vec_set(p.x,vector(cycle(p.x,camera.x-particle_seedbox.x,camera.x+particle_seedbox.x),
	cycle(p.y,camera.y-particle_seedbox.y,camera.y+particle_seedbox.y),
	cycle(p.z,camera.z-particle_seedbox.z,camera.z+particle_seedbox.z)));

	if(p.z<camera.z-100) p.lifespan = 0;

}

/*
--------------------------------------------------
void func_effect_particle_seed(PARTICLE *p)

Desc:

Returns: -
--------------------------------------------------
*/
void func_effect_particle_seed(PARTICLE *p) {

	vec_set(p.x,vector(camera.x+random(particle_seedbox.x*2)-particle_seedbox.x,
	camera.y+random(particle_seedbox.y*2)-particle_seedbox.y,
	camera.z+random(particle_seedbox.z*2)-particle_seedbox.z));

	p.flags |= MOVE;

	if(sky_cloud3.alpha > 0) {
		
		p.bmap = part_bmp_weather;	
		p.vel_x = part_vel_x;
		p.vel_y = part_vel_y;
		p.vel_z = part_vel_z;
		p.size = part_size;
		p.alpha = part_alpha;
		
		p.event  = func_particle_seed_infinity;	
	}	
}

/*
--------------------------------------------------
void func_fade_lightning(PARTICLE *p)

Desc:

Returns: -
--------------------------------------------------
*/
void func_fade_lightning(PARTICLE *p)  { p.lifespan = 0; }

/*
--------------------------------------------------
void func_particle_lightning(PARTICLE *p)

Desc: 

Returns: -
--------------------------------------------------
*/
void func_particle_lightning(PARTICLE *p)
{
	VECTOR temp;
	temp.x = random(2) - 1;
	temp.y = random(2) - 1;
	temp.z = random(2) - 1;
	vec_set(p.vel_x, temp);
	p.bmap = bmp_lightning;
	p.size = 3;
	p.flags |= (MOVE|BRIGHT|TRANSLUCENT);
	p.lifespan = 1;
	p.event  = func_fade_lightning;
}

/*
--------------------------------------------------
void func_particle_segment()

Desc:

Returns: -
--------------------------------------------------
*/
void func_particle_segment()
{
	/*
	
	vec_set(temporary, segment_end);
	vec_sub(segment_end, segment_start);
	segment_length = vec_length(segment_end);
	segment_end.x = (segment_end.x * 2) / segment_length; // create particles every 2. quant
	segment_end.y = (segment_end.y * 2) / segment_length;
	segment_end.z = (segment_end.z * 2) / segment_length;
	while(segment_length > 0)
	{
		
		effect(func_particle_lightning, 2, segment_start.x, nullvector);	
		vec_add(segment_start, segment_end);
		segment_length -= 2;
		
	}
	
	*/
	
	wait(1);
}

/*
--------------------------------------------------
void func_particle_segment()

Desc:

Returns: -
--------------------------------------------------
*/
void func_particle_segment()
{
	
	/*
	
	vec_set(temporary, stroke_start);
	vec_sub(stroke_end, stroke_start);
	stroke_length = vec_length(stroke_end);
	stroke_end.x = (stroke_end.x * 100) / stroke_length; // create segments every 200 quants
	stroke_end.y = (stroke_end.y * 100) / stroke_length;
	stroke_end.z = (stroke_end.z * 100) / stroke_length;
	while(stroke_length > 0)
	{
		vec_add(stroke_start, stroke_end);
		vec_set(segment_start, temporary);
		vec_set(segment_end, stroke_start);
		segment_end.x += random(60) - 30; // displace the lightning segments (don't make the lightning look like a straight stroke)
		segment_end.y += random(60) - 30;
		segment_end.z += random(60) - 30;
		func_particle_segment();
		stroke_length -= 100; // keep the same value here
	}
	
	*/
	
	wait(1);
}

/*
--------------------------------------------------
void func_increase_brightness()

Desc:

Returns: -
--------------------------------------------------
*/
void func_increase_brightness()
{
	/*
	
	lightning_on = 1;

	lightning = 255;
	wait(2+random(3));
	lightning = 1;
	wait(2+random(2));
	lightning = 255;
	wait(1+random(2));
	lightning = 1;
	wait(2+random(2));
	lightning = 255;
	wait(2+random(5));
	lightning = 1;

	wait(random(50));	
	lightning_on = 0;
	
	*/
	
	wait(1);
}

/*
--------------------------------------------------
void weather_change()

Desc:Can't be replaced with VOL_EFFECTS (at the momment).

Returns: -
--------------------------------------------------
*/
void weather_change() {
	
	//   Uncomment the following lines to unlock the old effects that was packed with Mystymood.
	//	Replace 'em with newer and Mystymood-independent code.

	/*
	if(!mystymood_active) return; // Activates weather ONLY IF Mystymood is active.

	VECTOR temp;

	// Sound handlers.
	var snd_handle_thunder, snd_handle_rain, snd_handle_wind, snd_handle_bg_day, snd_handle_bg_night;
	var snd_vol_rain = 2, snd_vol_wind = 2, snd_vol_bg_day = 2, snd_vol_bg_night = 2;

	var rand_count, rand_count_state;
	var outer_radius, inner_radius;

	var eff_density = 1;

	snd_handle_wind = snd_loop(wind_wav,snd_vol_wind,0);
	snd_handle_rain = snd_loop(rain_wav,snd_vol_rain,0);

	outer_radius = weather_fog_far;
	inner_radius = weather_fog_far-(weather_fog_far/8);

	if(use_bg_sounds) {
		
		snd_handle_bg_day = snd_loop(day_wav,snd_vol_bg_day,0);
		snd_handle_bg_night = snd_loop(night_wav,snd_vol_bg_night,0);
		
	}

	weather_state = 0;

	while(mystymood_active)
	{
		
		//		random_seed(0);
		rand_count = integer(random(6));//creates a integer random number 0-4		
		
		//////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////
		
		if(use_random_weather) {
			
			var i = random(random_weather_change_frequency);
			
			if(i>(random_weather_change_frequency/1.3)) {
				
				weather_state = 1;
				wait(-(random(random_weather_state_time/2)+random_weather_state_time/2));	
				
			}
			if(i>(random_weather_change_frequency/1.3)) {
				
				weather_state = 2;
				wait(-(random(random_weather_state_time/2)+random_weather_state_time/2));
				
			}	
			
			if(i>(random_weather_change_frequency/6)) {
				
				weather_state = 0;
				wait(-(random(random_weather_state_time/2)+random_weather_state_time/2));
				
			}
		}	
		
		//////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////
		
		if(weather_state == 1) {
			
			part_bmp_weather = bmp_rain;
			
			if(rain_random_move_on) {	
				
				part_vel_x = rain_wind_x + ((rain_random_move/2)-random(rain_random_move));
				part_vel_y = rain_wind_y + ((rain_random_move/2)-random(rain_random_move));	
				
			}
			
			else {
				
				part_vel_x = rain_wind_x;
				part_vel_y = rain_wind_y;
				
			}	
			
			part_vel_z = -rain_fallspeed;
			part_size=random(2)+8;
			part_alpha=random(10)+60;	
			
		}
		
		if(weather_state == 2) {
			
			part_bmp_weather = bmp_snow;
			
			if(snow_random_move_on == 1) {
				
				part_vel_x = snow_wind_x + ((snow_random_move/2)-random(snow_random_move));
				part_vel_y = snow_wind_y + ((snow_random_move/2)-random(snow_random_move));	
				
			}
			
			else {
				
				part_vel_x = snow_wind_x;
				part_vel_y = snow_wind_y;
				
			}	
			
			part_vel_z = -snow_fallspeed;
			part_size=random(1)+2;
			part_alpha=random(50)+40;	
		}
		
		//////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////
		
		if(weather_state == 1 && disable_lightning_thunder == 0)
		{	
			func_increase_brightness();
			
			vec_set(temp,vector(inner_radius+random(outer_radius-inner_radius),0,0));
			vec_rotate(temp,vector(random(360),0,0));
			vec_add(temp,camera.x); //Camera.x is center now. Maybe you want "player.x" here or something different altogether, depending on your game
			//Temp now is a random position somewhere on your "ring"
			//In your case:
			vec_set(stroke_start,temp);
			stroke_start.z += 600;
			vec_set(stroke_end,vector(temp.x+random(100)-200,temp.y+random(100)-200,temp.z));
			stroke_end.z -= 200;
			
			func_lightning_effect();
			while(lightning_on>0) wait(1); //thunder comes after lightning...
			
			if(rand_count == 1 && rand_count_state != 1)
			{
				snd_handle_thunder = snd_play(thunder1_wav, VOL_EFFECTS, 0);
				rand_count_state = 1;
			}
			if(rand_count == 2 && rand_count_state != 2)
			{
				snd_handle_thunder = snd_play(thunder2_wav, VOL_EFFECTS, 0);
				rand_count_state = 2;
			}
			if(rand_count == 3 && rand_count_state != 3)
			{
				snd_handle_thunder = snd_play(thunder3_wav, VOL_EFFECTS, 0);
				rand_count_state = 3;	
			}
			if(rand_count == 4 && rand_count_state != 4)
			{
				snd_handle_thunder = snd_play(thunder4_wav, VOL_EFFECTS, 0);
				rand_count_state = 4;	
			}
			if(rand_count == 5 && rand_count_state != 5)
			{
				snd_handle_thunder = snd_play(thunder5_wav, VOL_EFFECTS, 0);
				rand_count_state = 5;	
			}	
		}
		
		wait(-random(5));
		
		//////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////
		
		particle_seedbox.x=cx/2;
		particle_seedbox.y=cy/2;
		particle_seedbox.z=cz/2;
		
		if(weather_state>0) {
			
			reset(sky_cloud3,SHOW);
			if (sky_cloud3.alpha < 90) sky_cloud3.alpha += weather_fade_speed/20*time_step;
			
			if(sky_cloud3.alpha>40) {
				
				if(weather_fader<100 && weather_state>0)  weather_fader += weather_fade_speed/20*time_step;
				
				if(weather_state == 0) {
					
					if(weather_fader>1) weather_fader -= weather_fade_speed/20*time_step;
					
				}
				
				eff_density = (weather_fader*part_num);
			}
			
			if(weather_state == 1) {
				
				if(rain_to_snow_on_altitude && camera.z>snow_altitude && trigg_active_id == -1)
				weather_state = 2;
				
				part_num = rain_part_num;
				
				if(snd_vol_bg_day>2 || snd_vol_bg_night>2) {

					snd_vol_bg_day -= weather_soundfade_speed*time_step;
					snd_vol_bg_night -= weather_soundfade_speed*time_step;
					
				}	
				
				if(sky_cloud3.alpha>40) {
					
					if(snd_vol_rain<snd_vol_rain_max) snd_vol_rain += weather_soundfade_speed*time_step;
					if(snd_vol_wind<snd_vol_wind_max_when_rainy) snd_vol_wind += weather_soundfade_speed*time_step;
					
					else snd_vol_wind -= weather_soundfade_speed*time_step;
					
					effect(func_effect_particle_seed,eff_density,nullvector,nullvector);
					
				}
			}	
			
			if(weather_state == 2) {
				
				if(rain_to_snow_on_altitude == 1 && camera.z<snow_altitude && trigg_active_id == -1)
				weather_state = 1;
				
				part_num = snow_part_num;
				
				if(sky_cloud3.alpha>40) {
					
					if(snd_vol_rain>2) snd_vol_rain -= weather_soundfade_speed*time_step*2;
					if(snd_vol_wind<snd_vol_wind_max) snd_vol_wind += (eff_density/50)*weather_soundfade_speed*time_step;
					
					if(snd_vol_bg_day>2 || snd_vol_bg_night>2) {
						
						snd_vol_bg_day -= weather_soundfade_speed*time_step;
						snd_vol_bg_night -= weather_soundfade_speed*time_step;
						
					}
					
					effect(func_effect_particle_seed,eff_density,nullvector,nullvector);
				}
			}
			
			if(trigg_active_id < 0) {
				
				if(camera.fog_start>weather_fog_near) camera.fog_start -= weather_fade_speed*time_step;
				else camera.fog_start += weather_fade_speed*time_step;
				
				if(camera.fog_end>weather_fog_far) camera.fog_end -= weather_fade_speed*time_step;
				else camera.fog_end += weather_fade_speed*time_step;
				
			}
			
			
		}
		
		if(weather_state == 0) {
			
			if(sky_cloud3.alpha > 1) sky_cloud3.alpha -= weather_fade_speed/60*time_step;
			if(sky_cloud3.alpha<1) reset(sky_cloud3,SHOW);
			
			if(sky_cloud3.alpha > 40) {
				
				if(snd_vol_rain>2 || snd_vol_wind>2) {
					
					snd_vol_rain -= weather_soundfade_speed*time_step;
					snd_vol_wind -= weather_soundfade_speed*time_step;
					
					effect(func_effect_particle_seed,eff_density/4,nullvector,nullvector);
					
				}		
			}
			
			if(sky_cloud3.alpha < 60) {
				
				if(sun_angle.pan > 160 && sun_angle.pan < 360) {
					
					if(snd_vol_bg_night<snd_vol_bg_night_max) {
						
						snd_vol_bg_night += weather_soundfade_speed*time_step;
						
						if(snd_vol_bg_day > 2) snd_vol_bg_day -= weather_soundfade_speed*time_step;
						
					}			
				}
				
				if(sun_angle.pan>0 && sun_angle.pan<160) {
					
					if(snd_vol_bg_day<snd_vol_bg_day_max) {
						
						snd_vol_bg_day += weather_soundfade_speed*time_step;
						if(snd_vol_bg_night > 2) snd_vol_bg_night -= weather_soundfade_speed*time_step;
						
					}	
				}
			}
			
			if(trigg_active_id < 0) {
				
				if(camera.fog_start>land_fog_near) camera.fog_start -= weather_fade_speed*time_step;
				else camera.fog_start += weather_fade_speed*time_step;
				
				if(camera.fog_end>land_fog_far) camera.fog_end -= weather_fade_speed*time_step;
				else camera.fog_end += weather_fade_speed*time_step;
				
			}	
		}
		
		sky_sun.alpha = clamp((90-sky_cloud3.alpha),2,100);
		
		
		snd_tune(snd_handle_rain,snd_vol_rain,0,0);
		snd_tune(snd_handle_wind,snd_vol_wind,0,0);	
		snd_tune(snd_handle_bg_day,snd_vol_bg_day,0,0);
		snd_tune(snd_handle_bg_night,snd_vol_bg_night,0,0);
		
		wait(1);		
	}	
	
	*/
	
}

/*
--------------------------------------------------
void UnloadMystymood()

Desc:

Returns: -
--------------------------------------------------
*/
void UnloadMystymood() {
	
	LoadMystymood(0,0);
	
	sky_horizon.flags2 &= ~SHOW;
	sky_cloud1.flags2 &= ~SHOW;
	sky_cloud2.flags2 &= ~SHOW;
	sky_cloud3.flags2 &= ~SHOW;
	sky_day.flags2 &= ~SHOW;
	sky_sun.flags2 &= ~SHOW;
	sky_suncorona.flags2 &= ~SHOW;
	sky_sunshine.flags2 &= ~SHOW;
	sky_night.flags2 &= ~SHOW;
	sky_moon.flags2 &= ~SHOW;
	
}

/*
--------------------------------------------------
void LoadMystymood(BOOL _on, BOOL load_lens)

Desc:

Returns: -
--------------------------------------------------
*/
void LoadMystymood(BOOL _on, BOOL load_lens)
{
	
	WriteLog("[ ] Loading Mystymood");
	NewLine();

	int step = 0;

	if(!load_lens) {
		
		flare1_ent.flags2 &= ~SHOW;
		flare2_ent.flags2 &= ~SHOW;
		//			flare3_ent.flags2 &= ~SHOW; <-- You suck, Mr. Sun.
		flare4_ent.flags2 &= ~SHOW;
		flare5_ent.flags2 &= ~SHOW;
		flare6_ent.flags2 &= ~SHOW;
		flare7_ent.flags2 &= ~SHOW;
		flare8_ent.flags2 &= ~SHOW;
		flare9_ent.flags2 &= ~SHOW;
		flare10_ent.flags2 &= ~SHOW;
		flare11_ent.flags2 &= ~SHOW;
		flare12_ent.flags2 &= ~SHOW;
		flare13_ent.flags2 &= ~SHOW;
		flare14_ent.flags2 &= ~SHOW;
		flare15_ent.flags2 &= ~SHOW;
		flare16_ent.flags2 &= ~SHOW;
		flare17_ent.flags2 &= ~SHOW;
		flare18_ent.flags2 &= ~SHOW;
		flare19_ent.flags2 &= ~SHOW;
		flare20_ent.flags2 &= ~SHOW;
		
		lens_active = 0;
		
		step++;
		
	} else LoadMystymoodLensflare();

	if(!_on) { // Unload mystymood & lensflare effect
		
		// macros work only with flag1? :-? (idk)
		// so we use the inverse flag to control flags2.
		sky_horizon.flags2 &= ~SHOW;
		sky_cloud1.flags2 &= ~SHOW;
		sky_cloud2.flags2 &= ~SHOW;
		sky_cloud3.flags2 &= ~SHOW;
		sky_day.flags2 &= ~SHOW;
		sky_sun.flags2 &= ~SHOW;
		sky_suncorona.flags2 &= ~SHOW;
		sky_sunshine.flags2 &= ~SHOW;
		sky_night.flags2 &= ~SHOW;
		sky_moon.flags2 &= ~SHOW;
		
		mystymood_active = 0;
		
		step++;
		
	}

	if(step>=2) {
		
		WriteLog("[X] Task completed, switched off Mystymood because no parameters were on.");
		NewLine();
		
		return;
		
	}
	

	////////////////////////////////////////////////////////////
	// Setup for lensflare
	////////////////////////////////////////////////////////////
	flare1_ent.pivot_dist = 1.278;
	flare2_ent.pivot_dist = 1.200;
	flare4_ent.pivot_dist = 0.522;
	flare5_ent.pivot_dist = 0.434;
	flare6_ent.pivot_dist = 0.348;
	flare7_ent.pivot_dist = 0.306;
	flare8_ent.pivot_dist = 0.262;	
	flare9_ent.pivot_dist = 0.174;
	flare10_ent.pivot_dist = 0.114;
	flare11_ent.pivot_dist = 0.044;
	flare12_ent.pivot_dist = 0.002;
	flare13_ent.pivot_dist = -0.128;
	flare14_ent.pivot_dist = -0.258;
	flare15_ent.pivot_dist = -0.304;
	flare16_ent.pivot_dist = -0.372;
	flare17_ent.pivot_dist = -0.390;
	flare18_ent.pivot_dist = -0.432;
	flare19_ent.pivot_dist = -0.654;
	flare20_ent.pivot_dist = -1.000;
	////////////////////////////////////////////////////////////

	sky_horizon.flags2 |= SHOW;
	sky_cloud1.flags2 |= SHOW;
	sky_cloud2.flags2 |= SHOW;
	sky_cloud3.flags2 |= SHOW;
	sky_day.flags2 |= SHOW;	
	
	if(_use_nightstars) {
		
		sky_night.flags2 |= SHOW;
		
	}
	
	if(_use_moon) {
		
		sky_moon.flags2 |= SHOW;
		
	}
	
	if(_use_sun) {
		
		sky_sun.flags2 |= SHOW;
		sky_suncorona.flags2 |= SHOW;
		sky_sunshine.flags2 |= SHOW;
		
	}

	VECTOR temp;
	
	/*
	
	if( str_stri(command_str," -dev") ) {
		
		on_space = toggle_weather;
		on_alt = good_weather;
		
	}
	
	*/

	sky_sun.scale_x = sun_scale_x;
	sky_sun.scale_y = sun_scale_y;

	fog_color = 1;

	camera.fog_start = land_fog_near;//-50;
	camera.fog_end = land_fog_far;//300;

	vec_set(d3d_fogcolor1,fog_day);//set the default day fog-color 

	mystymood_active = 1;
	
	WriteLog("[X] Task completed, activated Mystymood.");
	NewLine();
	
	//	weather_change();

	while(mystymood_active) {
		
		vec_set(sun_color.blue,vector(d3d_fogcolor1.blue*sun_col_fac,d3d_fogcolor1.green*sun_col_fac,d3d_fogcolor1.red*sun_col_fac));
		vec_set(sky_color.blue,d3d_fogcolor1.blue);	
		vec_set(sky_horizon.blue,d3d_fogcolor1.blue);
		
		//		if( !weather_state && trigg_active_id < 0) {
			
			if(!dynamic_day_night) func_fade_colors(d3d_fogcolor1,current_color,fog_dynamic_day_night_off);
			
			if(camera.fog_start>land_fog_near) camera.fog_start -= weather_fade_speed*time_step;
			else camera.fog_start += weather_fade_speed*time_step;
			
			if(camera.fog_end>land_fog_far) camera.fog_end -= weather_fade_speed*time_step;
			else camera.fog_end += weather_fade_speed*time_step;
			
		//		}
		
		vec_set(current_color,d3d_fogcolor1);
		
		vec_set(temp,sun_pos); 
		vec_set(sky_sun.x,temp);  // copy the sun_pos location
		vec_sub(temp,camera.x); // direction vector from camera to our sun_pos
		vec_normalize(temp,land_fog_far-sun_dist_minus); // chop our direction vector to a set distance	
		
		vec_set(sky_sun.x,temp);
		
		if(_use_moon) {
			
			vec_set(temp,sky_sun.x); 
			vec_inverse(temp);
			vec_set(sky_moon.x,temp);  // copy the sun_pos location
		}
		
		if(dynamic_day_night) {
			
			if(sun_angle.pan > 230 && sun_angle.pan < 360)
			
			sun_angle.pan += .01*time_speed_night*time_step;
			else sun_angle.pan += .01*time_speed*time_step;
			
			sun_angle.pan %= 360;
			sun_angle.tilt = fsin(sun_angle.pan, max_zenith);
			
			//sun "grows" at low azimut
			if(sky_sun.z<sun_grow_z) {
				
				if(sky_sun.scale_x<sun_scale_x+1 && sky_sun.scale_y<sun_scale_y+1) {
					
					sky_sun.scale_x = sky_sun.scale_y += .01 * (time_speed/10) * time_step;
					
					/*
					
					sky_sun.scale_x += 0.01*time_step*time_speed/10;
					sky_sun.scale_y += 0.01*time_step*time_speed/10;
					
					*/
					
				}	
				
			}
			
			else {
				
				if(sky_sun.scale_x>sun_scale_x && sky_sun.scale_y>sun_scale_y) {
					
					sky_sun.scale_x = sky_sun.scale_y -= .01 * (time_speed/10) * time_step;
					
					/*
					
					sky_sun.scale_x -= 0.01*time_step*time_speed/10;
					sky_sun.scale_y -= 0.01*time_step*time_speed/10;
					
					*/
					
				}
			}
		}
		
		else {
			
			sun_angle.pan = sun_azimuth;
			sun_angle.tilt = sun_elevation;
			
		}
		
		if(sun_angle.pan > 0 && sun_angle.pan < 40) {
			
			if (sky_cloud1.alpha < 80) sky_cloud1.alpha += sky_fade_speed*time_step*time_speed;
			if (sky_cloud2.alpha < 60) sky_cloud2.alpha += sky_fade_speed*time_step*time_speed;
			if (sky_day.alpha < 60) sky_day.alpha += sky_fade_speed*time_step*time_speed;
			if (sky_night.alpha > 1) sky_night.alpha -= sky_fade_speed*time_step*time_speed;	
			
		}
		
		if(sun_angle.pan > 10 && sun_angle.pan < 160) func_fade_colors(d3d_fogcolor1,current_color,fog_day);
		
		if(sun_angle.pan > 40 && sun_angle.pan < 160) {
			
			sky_cloud1.alpha = 80;
			sky_cloud2.alpha = 60;
			sky_day.alpha = 60;
			sky_night.alpha = 1;
			
		}
		
		// Fade into the night...
		if(sun_angle.pan > 160 && sun_angle.pan < 190) {
			
			if (sky_cloud1.alpha > 10) {sky_cloud1.alpha -= sky_fade_speed*time_step*time_speed;} 
			if (sky_cloud2.alpha > 10) {sky_cloud2.alpha -= sky_fade_speed*time_step*time_speed;} 
			if (sky_night.alpha < 100) {sky_night.alpha += sky_fade_speed*time_step*time_speed;}
			if (sky_day.alpha > 1) {sky_day.alpha -= sky_fade_speed*time_step*time_speed;}		
			
			func_fade_colors(d3d_fogcolor1,current_color,fog_eve);
			
		}
		
		if(sun_angle.pan > 190 && sun_angle.pan < 340) func_fade_colors(d3d_fogcolor1,current_color,fog_night);
		
		if(sun_angle.pan > 190 && sun_angle.pan < 340) {
			
			sky_cloud1.alpha = 10;
			sky_cloud2.alpha = 10;
			sky_day.alpha = 10;
			sky_night.alpha = 100;
			
		}
		
		if(sun_angle.pan > 340 && sun_angle.pan < 360) func_fade_colors(d3d_fogcolor1,current_color,fog_mor);
		
		if(sun_angle.pan > 190 && sun_angle.pan < 350) {
			
			/* if(weather_state>0) */ func_fade_colors(d3d_fogcolor1,current_color,fog_weather_night);
			
		}
		
		else {
			
			/* if(weather_state>0) */ func_fade_colors(d3d_fogcolor1,current_color,fog_weather_day);
			
		}
		
		vec_set(sky_sunshine.x,sky_sun.x);	
		vec_set(sky_suncorona.x,sky_sun.x);
		
		sky_suncorona.scale_x = sun_scale_x*5;//15;
		sky_suncorona.scale_y = sun_scale_y*4;//7;
		
		sky_sunshine.scale_x = sun_scale_x*10;
		sky_sunshine.scale_y = sun_scale_y*4;
		
		sky_moon.scale_x = sun_scale_x*moon_scale_fac;
		sky_moon.scale_y = sun_scale_y*moon_scale_fac;	 
		
		sky_night.scale_x = night_sky_scale_x;
		sky_night.scale_y = night_sky_scale_x;
		
		sky_night.u = night_sky_speed_x; 
		sky_night.v = night_sky_speed_y;
		
		wait(1);
	}	

	mystymood_active = 0;
	
	WriteLog("[X] Switched off Mystymood.");
	NewLine();
	
}

/*
--------------------------------------------------
void LoadObjectCustomSettings(ENTITY *from)

Desc:

Returns: -
--------------------------------------------------
*/
void LoadObjectCustomSettings(ENTITY *from) {
	
	return;
	
	var temp;
	STRING *CBOIF = "#1000"; // this is the limit
	//   str_cpy(CBOIF, (STRING *) from->type );
	
	// LoadObjectCustomSettings uses TEMPSTR to evaluate the exact path without having to
	// do it again. Because of this: If you use LoadObjectCustomSettings in other places than 
	// CreateObject(), it won't work, because either TEMPSTR is left undefined 
	// or containing wrong data!
	str_cpy(CBOIF,TEMPSTR);
	
	str_cat(CBOIF,EXT_CBOIF);
	
	var CBOIFHNDL = file_open_read(CBOIF);
	
	if(!file_length(CBOIFHNDL) || !CBOIFHNDL) {
		
		// File is empty, no need to pass anything/can't open file
		//		file_close(CBOIFHNDL);
		
		return;
		
	}
	
	// Dirty, ugly code.
	// Don't have time to optimize them though.
	temp = file_var_read(CBOIFHNDL);
	if(temp != -1) from.scale_x = temp;
	
	temp = file_var_read(CBOIFHNDL);
	if(temp != -1) from.scale_y = temp;
	
	temp = file_var_read(CBOIFHNDL);
	if(temp != -1) from.scale_z = temp;
	
	temp = file_var_read(CBOIFHNDL);
	if(temp != -1) from.alpha = temp;
	
	temp = file_var_read(CBOIFHNDL);
	if(temp != -1) from.albedo = temp;
	
	temp = file_var_read(CBOIFHNDL);
	if(temp != -1) from.ambient = temp;
	
	temp = file_var_read(CBOIFHNDL);
	if(temp != -1) from.red = temp;
	
	temp = file_var_read(CBOIFHNDL);
	if(temp != -1) from.green = temp;
	
	temp = file_var_read(CBOIFHNDL);
	if(temp != -1) from.blue = temp;
	
	temp = file_var_read(CBOIFHNDL);
	if(temp != -1) from.pan = temp;
	
	temp = file_var_read(CBOIFHNDL);
	if(temp != -1) from.tilt = temp;
	
	temp = file_var_read(CBOIFHNDL);
	if(temp != -1) from.roll = temp;
	
	// flags after
	// NARROW, FAT, CLIPPED, CAST, SPOTLIGHT
	// OVERLAY, DECAL, NOFILTER, SHOW/INVISIBLE,
	// ANIMATE, DYNAMIC
	
	if(file_var_read(CBOIFHNDL)) set(from,PASSABLE);
	else reset(from,PASSABLE);
	
	if(file_var_read(CBOIFHNDL)) set(from,POLYGON);
	else reset(from,POLYGON);
	
	if(file_var_read(CBOIFHNDL)) set(from,UNTOUCHABLE);
	else reset(from,UNTOUCHABLE);
	
	if(file_var_read(CBOIFHNDL)) set(from,SHADOW);
	else reset(from,SHADOW);
	
	if(file_var_read(CBOIFHNDL)) set(from,TRANSLUCENT);
	else reset(from,TRANSLUCENT);
	
	if(file_var_read(CBOIFHNDL)) set(from,BRIGHT);
	else reset(from,BRIGHT);
	
	if(file_var_read(CBOIFHNDL)) set(from,LIGHT);
	else reset(from,LIGHT);
	
	if(file_var_read(CBOIFHNDL)) set(from,UNLIT);
	else reset(from,UNLIT);
	
	if(file_var_read(CBOIFHNDL)) set(from,NOFOG);
	else reset(from,NOFOG);
	
	if(file_var_read(CBOIFHNDL)) set(from,ZNEAR);
	else reset(from,ZNEAR);
	
	//+flags
	if(file_var_read(CBOIFHNDL)) set(from,FLAG1);
	else reset(from,FLAG1);
	
	if(file_var_read(CBOIFHNDL)) set(from,FLAG2);
	else reset(from,FLAG2);
	
	if(file_var_read(CBOIFHNDL)) set(from,FLAG3);
	else reset(from,FLAG3);
	
	if(file_var_read(CBOIFHNDL)) set(from,FLAG4);
	else reset(from,FLAG4);
	
	if(file_var_read(CBOIFHNDL)) set(from,FLAG5);
	else reset(from,FLAG5);
	
	if(file_var_read(CBOIFHNDL)) set(from,FLAG6);
	else reset(from,FLAG6);
	
	if(file_var_read(CBOIFHNDL)) set(from,FLAG7);
	else reset(from,FLAG7);
	
	if(file_var_read(CBOIFHNDL)) set(from,FLAG8);
	else reset(from,FLAG8);
	
	//+skills
	int i = MAX_PUBLIC_SKILLS; // pass from MAX_PUBLIC_SKILLS and up
	
	while(i < MAX_PUBLIC_SKILLS + MAX_PRIVATE_SKILLS) {
		
		temp = file_var_read(CBOIFHNDL);
		if(temp != -1) from.skill[i] = temp;
		
		i += 1;
		
		wait(1);
		
	}
	
	file_close(CBOIFHNDL);
	
}

/*
--------------------------------------------------
void WriteObjectCustomSettings(ENTITY *ent)

Desc:

Returns: -
--------------------------------------------------
*/
void WriteObjectCustomSettings(ENTITY *ent) {
	
	while(!ent) wait(1);
	
	STRING *tempstr = "#500";
	str_cpy(tempstr,TEMPSTR);
	str_cat(tempstr, str_create( EXT_CBOIF ) );
	
	var hndl = file_open_write(tempstr);
	
	file_var_write(hndl,ent.scale_x);
	file_var_write(hndl,ent.scale_y);
	file_var_write(hndl,ent.scale_z);
	
	file_var_write(hndl,ent.alpha);
	file_var_write(hndl,ent.albedo);
	file_var_write(hndl,ent.ambient);
	
	file_var_write(hndl,ent.red);
	file_var_write(hndl,ent.green);
	file_var_write(hndl,ent.blue);
	
	file_var_write(hndl,ent.pan);
	file_var_write(hndl,ent.tilt);
	file_var_write(hndl,ent.roll);
	
	file_var_write(hndl,is(ent,PASSABLE) );
	file_var_write(hndl,is(ent,POLYGON) );
	file_var_write(hndl,is(ent,UNTOUCHABLE) );
	file_var_write(hndl,is(ent,SHADOW) );
	file_var_write(hndl,is(ent,TRANSLUCENT) );
	file_var_write(hndl,is(ent,BRIGHT));
	file_var_write(hndl,is(ent,LIGHT));
	file_var_write(hndl,is(ent,UNLIT) );
	file_var_write(hndl,is(ent,NOFOG) );
	file_var_write(hndl,is(ent,ZNEAR) );
	
	file_var_write(hndl,is(ent,FLAG1) );
	file_var_write(hndl,is(ent,FLAG2) );
	file_var_write(hndl,is(ent,FLAG3) );
	file_var_write(hndl,is(ent,FLAG4) );
	file_var_write(hndl,is(ent,FLAG5) );
	file_var_write(hndl,is(ent,FLAG6) );
	file_var_write(hndl,is(ent,FLAG7) );
	file_var_write(hndl,is(ent,FLAG8) );
	
	int i = MAX_PUBLIC_SKILLS;
	while(i < MAX_PUBLIC_SKILLS + MAX_PRIVATE_SKILLS) {
		
		file_var_write(hndl,ent.skill[i]);
		i++;	  
		
	}
	
	file_close(hndl);
	
}

/*
--------------------------------------------------
void sndPlay(STRING *str)

Desc:

Returns: -
--------------------------------------------------
*/
void sndPlay(STRING *str) {
	
	if( str_len(str) ) {
		
		var hndl = media_play(str,NULL,VOL_EFFECTS);
		//		var hndl = snd_play(snd_create(str),VOL_EFFECTS,0);
		if(!hndl) return;
		
		//		while(snd_playing(hndl)) wait(1);
		while(media_playing(hndl)) wait(1);
		
		
	} else return;
	
}

/*
--------------------------------------------------
void Scale(ENTITY *ent, var amount)

Desc:

Returns: -
--------------------------------------------------
*/
void Scale(ENTITY *ent, var amount) {
	
	while(!ent) wait(1);
	
	// modify global variables
	ent.scale_x = ent.scale_y = ent.scale_z = amount; // freely, even if it is a negative number
	
}

/*
--------------------------------------------------
void PrecacheContent()

Desc: Precache game data. This increases load time, but prevents a little slow down (jerk)
when the entity is shown for the first time.
This is optional, and by default is included with the kernel loading code.
Uncomment PrecacheContent() in LoadKernel() to turn off content precaching.

Returns: -
--------------------------------------------------
*/
void PrecacheContent() {
	
	WriteLog("[SYS] Precaching  game content...");
	NewLine();
	
	var   old_VOL_EFFECTS = VOL_EFFECTS,
	old_VOL_MUSIC = VOL_MUSIC;
	
	VOL_EFFECTS = VOL_MUSIC = 0;
	
	GSEMenuMouseHover();
	wait_for(GSEMenuMouseHover);
	
	GSEMenuMouseClick();
	wait_for(GSEMenuMouseClick);
	
	VOL_EFFECTS = old_VOL_EFFECTS;
	VOL_MUSIC = old_VOL_MUSIC;
	
	WriteLog("[X] Finished precaching contents.");
	NewLine();
	
}

/*
--------------------------------------------------
void LoadPlayground()

Desc: Sets up and manages the playground.

Returns: -
--------------------------------------------------
*/
void LoadPlayground() {

	if(event_type == EVENT_RELEASE) return;

	WriteLog("[ ] Preparing the playground...");
	NewLine();
	
	var olmouse = mouse_mode;
	mouse_mode = 0;
	
	var tempvol = 0, rainhndl = -1, snowhndl = -1, windhndl = -1;
	
	BMAP *b_load;
	
	if( str_len(PLAYTEST_LOADSCREENSTR) && !str_cmp(PLAYTEST_LOADSCREENSTR, undef ) ) {
		
		b_load = bmap_create(PLAYTEST_LOADSCREENSTR);
		
		/*
		
		Playtest_Loadscreen.bmap = b_load;
		
		GPanelResize(Playtest_Loadscreen,RESIZE_XY);
		
		set(Playtest_Loadscreen,SHOW);
		
		*/
		
	}
	
	else b_load = bmap_create("ima_01_03.png");
	
	while(proc_status(bmap_create)) wait(1);
	Playtest_Loadscreen.bmap = b_load;
	GPanelResize(Playtest_Loadscreen,RESIZE_XY);	
	set(Playtest_Loadscreen,SHOW);
	
	//
	ent_remove(marker);
	ent_remove(cam);

	if(select) {
		
		// Deselect any selected entity first
		if(select.ObjectType == Light) GLightWindowHide();
		if(select.ObjectType == Object) GPropertiesWindowHide();
		if(select.ObjectType == Sound) GSoundWindowHide();
		if(select.ObjectType == Particle) GParticleWindowHide();
		
		select.material = mat_temp;
		select = NULL;
		
	}

	// Scans through all available entities
	you = ent_next(NULL);
	while(you != NULL) {
		
		if(you.CameraFP) {
			
			you.CameraBike = 0;
			
			play_as_bike = 0;
			play_as_fp = 1;
			
		}
		
		if(you.CameraBike) {
			
			you.CameraFP = 0;
			
			play_as_fp = 0;
			play_as_bike = 1;
			
		}
		
		// Scan for any light, particle, or sound entity
		if(you.ObjectType == Light || you.ObjectType == Particle || you.ObjectType == Sound) {
			
			// I wonder how I couldn't just use reset(you,SHOW) or you.flags &= ~SHOW here
			set(you,INVISIBLE); 
			
		}
		
		you = ent_next(you);
		
		wait(1);
		
	}
	
	if( (int) WorldType == WORLD_STATIC) {
		
		sun_light = _sun_light;
		fog_color = _fog_color;
		d3d_fogcolor1.red = _d3d_fogcolor1_red;
		d3d_fogcolor1.green = _d3d_fogcolor1_green;
		d3d_fogcolor1.blue = _d3d_fogcolor1_blue;
		camera.fog_end = _camera_fog_end;
		
	}
	else {  // WORLD_DYNAMIC
		
		LoadMystymood(1,_load_lensflare);		
		
	}
	
	switch( (int) _weather_mode ) {
		
		case RAIN_ONLY: 
		rain(1,8);
		rainhndl = snd_loop(rain_wav,VOL_EFFECTS,0);
		break;
		
		case SNOW_ONLY:
		snow(5000,camera.x,NULL);
		snowhndl = snd_loop(snowstorm_ambient,VOL_EFFECTS,0);
		break;
		
		case RAIN_SNOW: 

		rain(1,8);
		snow(5000,camera.x,NULL);
		
		rainhndl = snd_loop(rain_wav,VOL_EFFECTS,0);
		snowhndl = snd_loop(snowstorm_ambient,VOL_EFFECTS,0);
		
		break;
		
		case NO_RAIN_SNOW: wait(.1); break;
		
		default: wait(.1); break;
		
	}
	

	GGUIHide();

	PLAYTESTING = 1;

	//
	//	if(play_as_fp) {
		//		
		//		set(panCAMRecorder,SHOW);
		//		set(panCAMRecorder_digits,SHOW);
		//		
	//	}

	/*
	// Test if there is any entity in the projection array
	if(rEnt[0]) {
		
		vec_set(pSys.Pos,sun_light);
		str_cpy(rFile,"renderedProjection");//name of saving bmap and projection parametrs
		screen_render_entities (pSys[0].Pos,pSys[0].Ang,pSys[0].Fov,rEntCount);//create projection bmap(render 5 trees)
		while(proc_status(screen_render_entities)) wait(1);// wait until render is finish
		mtl_pTex1.skin1 = rBmap ;// set material skin to shadow bmap
		
		set_material_matrices();// set all mat_effect pointers that uses in shader
		
	}
	*/
	
	/*
	while(tempvol<=VOL_EFFECTS) {
		
		tempvol += 5;
		if(rainhndl) snd_tune(rainhndl,tempvol,0,0);
		if(snowhndl) snd_tune(snowhndl,tempvol,0,0);
		
		wait(1);
		
	}*/
	
	if(is(Playtest_Loadscreen,SHOW)) reset(Playtest_Loadscreen,SHOW);
	
	from_test_play = 1;

	while(PLAYTESTING) {
		
		// Need a little optimization here....
		//		if(rEnt[0]) create_dxmat(mat_effect1,pSys[0].Pos,pSys[0].Ang,pSys[0].Fov,mtl_pTex1.skin1);
		
		temp_cam += 3 * time_step;
		camera.z += .5 * sin(temp_cam);
		
		if(key_space) {
			
			while(key_space) wait(1);
			if(!mouse_mode) mouse_mode = 2;
			else mouse_mode = 0;
			
		}
		
		if(key_esc) {
			
			while(key_esc) wait(1);
			
			PLAYTESTING = 0;
			from_test_play = 0; // reset
			
		}
		
		if(mouse_mode) vec_set(mouse_pos,mouse_cursor);
		
		wait(1);
		
	}
	
	// Destroy weather effects and its sounds
	rain(0,0);
	snow(0,0,NULL);
	
	if(rainhndl != -1) snd_stop(rainhndl);
	if(snowhndl != -1) snd_stop(snowhndl);
	
	if(mystymood_active) {
		
		UnloadMystymood();
		
		fog_color = 0;

		//		camera.fog_start = 0;
		//		camera.fog_end = land_fog_far;//300;
		//
		//		vec_set(d3d_fogcolor1,fog_day);//set the default day fog-color 
		
	}

	if(play_as_fp) {
		
		reset(panCAMRecorder,SHOW);
		reset(panCAMRecorder_digits,SHOW);
		reset(panCAMRecorderREC,SHOW);
		
	}
	else { //play_as_bike
		
		wait(1);
		
	}

	/***

	Scan through all available entities in the level
	and set them to their original state.

	***/
	you = ent_next(NULL);

	while(you != NULL) {
		
		if(you.ObjectType == Light || you.ObjectType == Particle || you.ObjectType == Sound)
		reset(you,INVISIBLE);
		
		if(you.ObjectType == DynamicContent) {
			
			//			printf("Detect you");
			ptr_remove(you);
			
		}
		
		you = ent_next(you);
		
	}
	
	mouse_mode = olmouse;
	
	marker = ent_create("target.mdl",nullvector,FollowPointer); // Create a mouse pointer.
	//	marker = ent_create(CUBE_MDL,nullvector,FollowPointer);
	cam = ent_create("marker.mdl",vector(0,0,0),free_camera);

	GGUIShow();
	//	def_move();

	// Clear the rendered projection bmap.
	//	bmap_purge(rBmap);
	
	WriteLog("[X] Playtesting ended.");
	NewLine();

}

/*
--------------------------------------------------
BOOL bmap_savetga (BMAP* b, char* filename)

Desc: By HeelX (http://www.opserver.de/ubb7/ubbthreads.php?ubb=showflat&Number=421231#Post421231)

Saves a bitmap as tga file.

Some users reported that they can't properly save a bitmap as TGA with bmap_save, because the bitmap gets mirrored. 
This is due the fact that TGA stores a handedness flag that defines if the image origin is in the upper- or lower left corner 
I found out, that if you set the flag in the TGA, that indicates the origin in the lower left corner, and you write the image upside down into the file, the bitmap is saved correctly and is loaded correctly back into the engine.

So I have written the following function "bmap_savetga" a while ago (inspired by ventilator's C-Script in the wiki) in Lite-C for another project to circumvent the upside-down problem; 
it also saves the alpha channel in the TGA, if and only if the passed BMAP* has an alpha channel, too; otherwise the TGA just saves RGB data.

Returns: -
--------------------------------------------------
*/
BOOL bmap_savetga (BMAP* b, char* filename)
{
	BOOL bSuccess = false;

	if (b && filename && strlen(filename) > 0)
	{
		var fh = file_open_write(filename);
		if (fh)
		{
			int height = b->height;
			int width = b->width;

			var format = bmap_lock(b, 0);

			// if the bitmap has an alpha channel
			BOOL bAlpha = (((format == 8888) || (format == 1555) || (format == 4444)) && (b->bytespp == 4));

			// header

			int i;
			for (i = 0; i < 2; i++)
			file_asc_write(fh, 0);

			file_asc_write(fh, 2); // uncompressed

			for (i = 0; i < 7; i++)
			file_asc_write(fh, 0);

			// y origin (lower left corner)
			file_asc_write(fh, height & 255);
			file_asc_write(fh, (height >> 8) & 255);

			file_asc_write(fh, width & 255);
			file_asc_write(fh, (width >> 8) & 255);

			file_asc_write(fh, height & 255);
			file_asc_write(fh, (height >> 8) & 255);
			
			int bypp = 24;
			if (bAlpha)
			bypp = 32;

			file_asc_write(fh, bypp); // bypp
			file_asc_write(fh, 0);

			// pixels

			COLOR bgr;
			var alpha;

			int ix, iy;
			for (iy = 0; iy < height; iy++)
			{
				for (ix = 0; ix < width; ix++)
				{
					// retrieve BGR color and alpha
					pixel_to_vec(&bgr, &alpha, format, pixel_for_bmap(b, ix, height - 1 - iy));

					file_asc_write(fh, bgr.blue); // b
					file_asc_write(fh, bgr.green); // g
					file_asc_write(fh, bgr.red); // r

					if (bAlpha)
					file_asc_write(fh, alpha * 2.55); // a
				}
			}

			// done!
			bmap_unlock(b);
			file_close(fh);

			bSuccess = true;
		}
	}

	return(bSuccess);
}

/*
--------------------------------------------------
void paint_canvas()

Desc:

Returns: -
--------------------------------------------------
*/
void paint_canvas()
{
	
	canvas = canvas_paint; // set the pointer to our canvas
	canvas_modified = 1; // the player has painted something on the canvas, so the file will be saved on exit automatically
	while(mouse_left && !paint_outside) // this look runs for as long as the left mouse button is being pressed
	{
		
		format = bmap_lock(canvas, 0); // lock the canvas bitmap
		pixel = pixel_for_vec(current_color2, 100, format); // convert the color (alpha = 100) to a pixel in the given format
		pixel_to_bmap(canvas, coords_x, coords_y, pixel); // now write the pixel at the coords_x, coords_y position
		
		pixel_to_bmap(canvas,coords_x, coords_y,pixel);
		pixel_to_bmap(canvas,coords_x + 1, coords_y,pixel);
		pixel_to_bmap(canvas,coords_x + 2, coords_y,pixel);
		pixel_to_bmap(canvas,coords_x, coords_y + 1,pixel);
		pixel_to_bmap(canvas,coords_x, coords_y + 2,pixel);
		pixel_to_bmap(canvas,coords_x + 1, coords_y + 1,pixel);
		pixel_to_bmap(canvas,coords_x + 1, coords_y + 2,pixel);
		pixel_to_bmap(canvas,coords_x + 2, coords_y + 1,pixel);
		pixel_to_bmap(canvas,coords_x + 2, coords_y + 2,pixel);
		
		bmap_unlock(canvas); // unlock the bitmap now
		wait(1);
		
	}     
	
}