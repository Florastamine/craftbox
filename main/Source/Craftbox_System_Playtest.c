#ifndef Craftbox_System_Playtest

#define Craftbox_System_Playtest

/*
--------------------------------------------------
Craftbox_System_Playtest.c

Sets up and manages the playground.

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
	
	VECTOR oldcampos;
	ANGLE _oldcampos;
	
	var olmouse = mouse_mode;
	mouse_mode = 0;
	
	var tempvol = 0, rainhndl = -1, snowhndl = -1, windhndl = -1;
	var temp_cam;
	
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
	
	if( !PlayerPresent ) { // There was no player!
		
		error("Insert a player into the scene!");
		
		reset(Playtest_Loadscreen,SHOW);
		mouse_mode = olmouse;
		
		return;
		
	}
	
	
	ent_remove(marker);
	ent_remove(cam);

	if(select) {
		
		// Deselect any selected entity first
		if(select.ObjectType == Light) GLightWindowHide();
		if(select.ObjectType == Object) GPropertiesWindowHide();
		if(select.ObjectType == Sound) GSoundWindowHide();
		if(select.ObjectType == Particle) GParticleWindowHide();
		
		//		select.material = mat_temp;
		select = NULL;
		
	}

	// Scans through all available entities
	you = ent_next(NULL);
	while(you != NULL) {
		
		// Scan for any light, particle, or sound entity
		if(you.ObjectType == Light || you.ObjectType == Particle || you.ObjectType == Sound) {
			
			// I wonder how I couldn't just use reset(you,SHOW) or you.flags &= ~SHOW here
			set(you,INVISIBLE); 
			
		}
		
		you = ent_next(you);
		
		wait(1);
		
	}
	
	if( (int) WorldType == WORLD_STATIC) {
	   
	   wait(1);
		
//		sun_light = _sun_light;
//		fog_color = _fog_color;
//		d3d_fogcolor1.red = _d3d_fogcolor1_red;
//		d3d_fogcolor1.green = _d3d_fogcolor1_green;
//		d3d_fogcolor1.blue = _d3d_fogcolor1_blue;
//		camera.fog_end = _camera_fog_end;
		
	}
	else {  // WORLD_DYNAMIC
		
		//		LoadMystymood(1,_load_lensflare);
		LoadMystymood( true );
		
	}
	

	GGUIHide();
	
	oldcampos.x = camera.x;
	oldcampos.y = camera.y;
	oldcampos.z = camera.z;
	_oldcampos.pan = camera.pan;
	_oldcampos.tilt = camera.tilt;
	_oldcampos.roll = camera.roll;

	cbPlaytesting = true;

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
	
	from_test_play = false;

	while(cbPlaytesting) {
		
		// Need a little optimization here....
		//		if(rEnt[0]) create_dxmat(mat_effect1,pSys[0].Pos,pSys[0].Ang,pSys[0].Fov,mtl_pTex1.skin1);
		
		temp_cam += 3 * time_step;
		camera.z += .5 * sin(temp_cam);
		
		if(key_space) {
			
			while(key_space) wait(1);
			if(!mouse_mode) mouse_mode = 2;
			else mouse_mode = 0;
			
		}
		
		if(mouse_mode) vec_set(mouse_pos,mouse_cursor);
		
		wait(1);
		
	}
	
	// Destroy weather effects and its sounds
	//rain(0,0);
	//snow(0,0,NULL);
	
	if(rainhndl != -1) snd_stop(rainhndl);
	if(snowhndl != -1) snd_stop(snowhndl);
	
	if( mystymoodActive ) {
	   
	   LoadMystymood( false );
		
		fog_color = 0;

		//		camera.fog_start = 0;
		//		camera.fog_end = land_fog_far;//300;
		//
		//		vec_set(d3d_fogcolor1,fog_day);//set the default day fog-color 
		
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
	cam = ent_create(CAMERA_MODEL,oldcampos,free_camera);
	
	cam.pan = _oldcampos.pan;
	cam.tilt = _oldcampos.tilt;
	cam.roll = _oldcampos.roll;
	
	if( is(panCAMRecorder,SHOW) ) {
		
		reset(panCAMRecorder,SHOW);
		reset(panCAMRecorder_digits,SHOW);
		reset(panCAMRecorderREC,SHOW);
		reset(FPCrosshair,SHOW);
		
		Gun.flags2 &= ~SHOW;
		
	}

	GGUIShow();
	//	def_move();

	// Clear the rendered projection bmap.
	//	bmap_purge(rBmap);
	
	WriteLog("[X] Playtesting ended.");
	NewLine();

}

#endif