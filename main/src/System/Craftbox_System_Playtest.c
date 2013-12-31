
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
		// values recommended by developers
		// over tweak this leads to some random bright rainbow powered by Nguyen Ngoc Huy
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
	
	oldcampos.x = camera.x;
	oldcampos.y = camera.y;
	oldcampos.z = camera.z;
	_oldcampos.pan = camera.pan;
	_oldcampos.tilt = camera.tilt;
	_oldcampos.roll = camera.roll;

	PLAYTESTING = 1;

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
	cam = ent_create("marker.mdl",oldcampos,free_camera);
	
	cam.pan = _oldcampos.pan;
	cam.tilt = _oldcampos.tilt;
	cam.roll = _oldcampos.roll;

	GGUIShow();
	//	def_move();

	// Clear the rendered projection bmap.
	//	bmap_purge(rBmap);
	
	WriteLog("[X] Playtesting ended.");
	NewLine();

}