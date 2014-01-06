
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
void ExitEvent()

Desc: Peform various tasks prior to exiting craftbox. 
These including writing configuation files, saving variables...

Returns: -
--------------------------------------------------
*/
void ExitEvent() {

	WriteLog("!! [SYS] ExitEvent() was triggered.");
	NewLine();

	if( str_stri(command_str,PARAM_DEV) ) {
		
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

void Event_MouseLeft() {
	
	if(is(RightClickMenu,SHOW)) reset(RightClickMenu,SHOW);
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
				
				/*
				
				if(select.ObjectType == Light) GLightWindowShow();
				else GLightWindowHide();
				
				if(select.ObjectType > Object && select.ObjectType <= ObjectNode) GPropertiesWindowShow();
				else GPropertiesWindowHide();
				
				if(select.ObjectType == Sound) GSoundWindowShow();
				else GSoundWindowHide();
				
				if(select.ObjectType == Particle) GParticleWindowShow();
				else GParticleWindowHide();
				
				PassObjectPropertiesToGUI(select);
				
				*/
				
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
		
		
	}
	
}

void OpenRightClickMenu() {
	
	if(is(RightClickMenu,SHOW) ) reset(RightClickMenu,SHOW);
	
	if(mouse_pos.x + bmap_width(RightClickMenu->bmap) > sys_metrics(0)) RightClickMenu.pos_x = sys_metrics(0) - bmap_width(RightClickMenu->bmap);
	else RightClickMenu.pos_x = mouse_pos.x;
	
	if(mouse_pos.y + bmap_height(RightClickMenu->bmap) > sys_metrics(1)) RightClickMenu.pos_y = sys_metrics(1) - bmap_height(RightClickMenu->bmap);
	else RightClickMenu.pos_y = mouse_pos.y;	
	
	set(RightClickMenu,SHOW);
	
}

void Event_MouseRight() {
	
	if(mouse_ent) { // hit something
		
		if(mouse_ent != select) {
			
			if(!temp_pos.x && !temp_pos.y && !temp_pos.z)  wait(1); // couldnt return here
			
			if(!mouse_panel && !TerrainEditMode)
			{
				
				if(mouse_ent.ObjectType != Neutral && mouse_ent.ObjectType != Terrain) {
					
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
					
					OpenRightClickMenu();
					
				}
				
			}
			
		}
		else OpenRightClickMenu();
		
	}
	
	else { // Don't hit anything
		
		if(is(RightClickMenu,SHOW) ) reset(RightClickMenu,SHOW);
		
	}
	
}

/*
--------------------------------------------------
void Event_key_esc()

Desc:

Returns: -
--------------------------------------------------
*/
void Event_key_esc() {
	
	while(key_esc) wait(1);
	
	if(! from_test_play) {
		
		if(!proc_status(LoadPlayground)) {
			
			if(IN_GAME) {
				
				if(is(BackMenu_Background,SHOW) ) GBackMenuHide();
				else GBackMenuShow();
				
			}
			
		}
		
		return;
		
	}
	
	//////////////////////////////////////////////////////////////
	
	if ( is(canvas_pan,SHOW) && canvas_modified) {
		
		from_test_play = 1; // fake this var
		
		str_cpy(TERRAINSEEDBMAP,TerrainEnt->type );
		str_cat(TERRAINSEEDBMAP,SEEDMASKDATA);
		str_cat(TERRAINSEEDBMAP,".tga"); // bmap_savetga
		
		bmap_savetga(canvas, TERRAINSEEDBMAP );
		while(proc_status ( bmap_savetga ) ) wait(1);
		
		return;
		
	}
	
	//////////////////////////////////////////////////////////////
	
	if( !IN_GAME ) {
		
		if( !is(QuitDialog,SHOW) ) {
			
			GMainMenuHide();
			set(QuitDialog,SHOW);
			
			CameraPosID_temp = guiCurrentViewPreset;
			guiCurrentViewPreset = MENU_CAMERA_EXIT;
			
			
			} else {
			
			reset(QuitDialog,SHOW);
			GMainMenuShow(); 
			
			guiCurrentViewPreset = CameraPosID_temp;
			
		}
		
		return;
		
	}
	
	//////////////////////////////////////////////////////////////	
	
	if(PLAYTESTING ) {
		
		PLAYTESTING = 0;
		from_test_play = 0; // reset
		
		return;
		
	}
	
	//////////////////////////////////////////////////////////////
	
	if(is(InsertObject,SHOW)) {
	   
	   GInsertObjectHide();
	   
	   return;
	   
	}
	
}