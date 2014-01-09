/*
--------------------------------------------------
Craftbox_System_BootPoint.c

Provides loops and core functions for powering up craftbox, 
linking modules, setting up events.

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
	
	while( ! PreKernelDone ) wait(1);
	
	WriteLog("[SYS] Loading kernel ");
	NewLine();
	
	if ( DEBUG_MODE ) {
		
		reset(LoadKernelScreen,SHOW);
		vec_set( screen_color, vector(0,0,0) ); // black screen
		
		WriteLog("[ ] Testing various settings...");
		NewLine();
		
		//////////////////////////////////////////////////////////////
		switch( sys_metrics(67) ) { // Value that specifies how the system was started
			
			case 0: // Normal boot
			WriteLog("Normal boot");
			break;
			
			case 1: // Safe boot
			WriteLog("Safe boot");
			break;
			
			case 2: // Safe boot + network
			WriteLog("Safe boot with networking");
			break;
			
			default: break;
			
		}
		NewLine();
		
		if( sys_metrics(19) ) { // detect for the installation of mouse
			
			WriteLog("Mouse installed");
			NewLine();
			
		}
		
		if( sys_metrics(73) ) { // detect for a weak processor (rarely happen)
			
			WriteLog("Weak processor");
			NewLine();
			
		}
		//////////////////////////////////////////////////////////////
		
	}
	
	else {
		
		set(LoadKernelScreen,SHOW);
		
	}

	WriteLog("[ ] Initializing...");
	NewLine();
	
	// Init strings
	str_cpy(seedEnt,undef);
	str_cpy(TEMPSTR,undef);
	str_cpy(FILE_GAME_INTRO_VIDEO,undef);
	str_cpy(FILE_GAME_OUTRO_VIDEO,undef);
	str_cpy(GROUNDSTR,undef);
	str_cpy(SKYSTR,undef);
	str_cpy(PLAYTEST_LOADSCREENSTR,undef);
	clipboard.name = str_create("#300");
	
	// Init custom mouse cursor
	// This allows custom cursors to be created (by copying strings to STRING *mouse)
	BMAP *mouseimg;
	if(str_len(mouse_str) && !str_cmp(mouse_str,undef)) mouseimg = bmap_create(mouse_str);
	else mouseimg = bmap_create("mouse_pointer.png"); // default cursor
	mouse_map = mouseimg;
	
	// Init events
	on_bksp = TakeScreenshot;
	on_exit = ExitEvent;
	on_close = ExitEvent;
	on_level = on_level_event;
	on_esc = Event_key_esc;
	
	// Init shaders
	SetupShader();
	
	// Init music player
	mpLoad(PATH_MUSIC,EXT_MUSIC);
	while(proc_status(mpLoad)) wait(1);
	
	// Init materials
	int i;
	for(i = 0;i < 4;i++) mat_custom[i] = mtl_create();

	ReadMaterialDataFromFile(mat_custom[0],FILE_CUSTOM_MAT_1);
	ReadMaterialDataFromFile(mat_custom[1],FILE_CUSTOM_MAT_2);
	ReadMaterialDataFromFile(mat_custom[2],FILE_CUSTOM_MAT_3);
	ReadMaterialDataFromFile(mat_custom[3],FILE_CUSTOM_MAT_4);
	
	// Copy vars
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
	
	// Fetch pools
	FolderScan(files_list_SKYSTR_Pool, PATH_SKIES , str_create("tga") );
	while(proc_status(FolderScan)) wait(1);
	
	FolderScan(files_list_GROUNDSTR_Pool, PATH_GROUNDS, str_create("wmb") );
	while(proc_status(FolderScan)) wait(1);
	
	FolderScan(files_list_LOADGAMESTR_Pool, PATH_SAVEDGAMES, EXT_SAVEDGAMES);
	while(proc_status(FolderScan)) wait(1);
	
	// at this time the kernel has finished its job
	// gui calculation/initialization are on their own
	KERNEL_IS_RUNNING = 1;
	if( is(LoadKernelScreen,SHOW) ) reset(LoadKernelScreen,SHOW);
	
	WriteLog("[X] Finished initializing the kernel.");
	
	// Things happened after the kernel has been loaded.
	PostLoadKernel();
	
}

// things happen after loaded the kernel
// setup GUI, show splashscreens, etc
// why separate function? you may ask
// well the kernel is supposed to load a bunch of fixed things and should 
// not be combined together with GUI stuff, especially we always change the GUI
// plus, the kernel is supposed to load things that it's supposed to load,
// the most important thing.
// sorry for this commenting style, well, but my time is limited :P
void PostLoadKernel() {
	
	// Init (calculate) gui
	GGUIInit();
	while(proc_status(GGUIInit)) wait(1);
	
	GLoadMainMenu();
	while(proc_status(GLoadMainMenu)) wait(1);
	
	//	PANEL *black_cover = pan_create("pos_x = 0; pos_y = 0;",0);
	//	layer_sort(black_cover,SplashScreen->layer-1 );
	//	black_cover.bmap = bmap_create("./Cooked2D/black_.bmp");
	//	GPanelResize(black_cover,RESIZE_XY);
	//	
	//	set(black_cover,SHOW);
	//	
	//	pan_remove(black_cover);
	
	mouse_mode = 4;
	
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
			
			/*
			
			camera.clip_far = camera.fog_end + FOG_END_CLIP; // Clip far
			camera.clip_near = camera.fog_start - FOG_START_CLIP; // Clip near
			
			*/
			
			wait(1);
			
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
			
			
			if(mouse_right) { 
				
				while(mouse_right) wait(1);
				Event_MouseRight();
				
			}
			
			if(mouse_left) 
			{
				
				while(mouse_left) wait(1);
				Event_MouseLeft();
				
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
		
		if(key_r && str_stri(command_str,PARAM_DEV) ) { // This is only allowed in developer mode
			
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
		
		if(key_i) { // Quickly opens the Insert object panel
			
			while(key_i) wait(1);
			
			if( is(InsertObject,SHOW) ) GInsertObjectHide();
			else GInsertObjectShow();
			
		}
		
		if(key_t) { // Quickly opens the terrain toolbar
			
			while(key_t) wait(1);
			
			GToggleTerrainEditor();   
			
		}
		
		wait(1);
		
	}
	
	WriteLog("[X] Kernel looping code has finished its job.");
	NewLine();

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

	video_window(NULL,NULL,0,"craftbox Pre-alpha");
	
	// Read and setup settings prior to executing other functions.
	ConfigFileRead(FILE_CONFIG);
	while(proc_status(ConfigFileRead)) wait(1);

	// These are fixed variables 
	max_entities = max_particles = 20000;
	mouse_range = 500000;
	random_seed(0); // e.g. random light generators.
	terrain_chunk = 0; //
	fps_max = 75;
	clip_particles = 1; // cut off particles from far
	preload_mode = 3+4; // preload ents & precalculate env lights
	if(edition > 2) max_lights = 100; // still can't afford a comm license
	//	max_paths = max_entities = max_particles = pow(10,5);
	tex_share = 1;
	camera.clip_far = 5000000;
	camera.arc = 75;
	
	// Initialization for loopix-project.com's MystyMood_Lite-C
	sky_curve = 2;
	sky_clip = -10;
	
	if( sys_metrics(0) < MINIMUM_RESOLUTION_X || sys_metrics(1) < MINIMUM_RESOLUTION_Y ) {
		
		// user really has a low-end monitor (i have one, too)
		// actually this is the main monitor I use to develop craftbox.
		
		WriteLog("!! [ERROR] Screen resolution isn't supported (too low).");
		NewLine();
		
		ExitEvent();
		
	}
	
	// good monitor
	
	// execution is a bit slow, will optimize later
	/*
	
	if( !sResX ) video_set( sys_metrics(0), 0, 0, 0 ); else video_set( sResX, 0, 0, 0);
	if( !sResY ) video_set( 0, sys_metrics(1), 0, 0 ); else video_set( 0, sResY, 0, 0);
	video_set( 0, 0, 0, sResMode );
	
	*/
	
	video_set( sResX, sResY, 0, sResMode);
	
	PreKernelDone = 1; // The pre-kernel stage is done, at this time LoadKernel() will also be triggered to load the kernel.

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
				
				draw_rotated_bbox(select);
				
				if(key_del) {
					
					//					RemoveFromTextureProjectionArray(select);
					
					ptr_remove(select);
					
					// After this nothing is selected so we disable the panels.
					GPropertiesWindowHide();
					GSoundWindowHide();
					GLightWindowHide();
					GParticleWindowHide();			
					
					if(is(RightClickMenu,SHOW) ) reset(RightClickMenu,SHOW);
					
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