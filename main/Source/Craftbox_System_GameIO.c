
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
void on_level_event(percent)

Desc: A modified version of the on_level_event that is shown in the 3D Gamestudio manual.

Returns: -
--------------------------------------------------
*/
void on_level_event(percent)
{
	
	set(pLoadBar,SHOW | LIGHT);   // switch load bar on
	//pLoadBar.pos_y = screen_size.y - 40;
	pLoadBar.size_x = GetPercent( percent,100 ) * screen_size.x/100; // because max percent = 100
	pLoadBar.size_y = 30;
	
	if (percent >= 100) reset(pLoadBar,SHOW);
	pLoadBar.size_x = 0;
	
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

void SyncPos(VECTOR *v1, VECTOR *v2) {
	
	// Modifies v1
	v1->x = v2->x;
	v1->y = v2->y;
	v1->z = v2->z;
	
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

	level_load("./CookedWorlds/dry_original_weak.wmb");

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

	marker = ent_create("target.mdl",vector(0,0,0),FollowPointer); // Create a mouse pointer.
	
	//	marker.ObjectType = Neutral;
	camera.ambient = -50;

	manip_type = scale + 1;

	IN_GAME = 1;
	
}