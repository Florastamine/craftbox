#ifndef Craftbox_System_Object

#define Craftbox_System_Object

/*
--------------------------------------------------
Craftbox_System_Object.c

Provides functions for object placement and manipulation, in general.

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

void CreateSystemObject () {
	
	ENTITY *tmp;
	
	switch( SystemObjectID ) {
		
		case Trigger_PlayerStandard:
		
		if ( !PlayerPresent ) {
			
			tmp = ent_create( "./CookedObjects/player.mdl", temp_pos, Player_Normal );
			tmp->ObjectType = ObjectSystem;
			Scale( tmp, 2 );
			
		}
		else {
			
			WriteToBlackboard( " Chi duoc tao mot nhan vat duy nhat! ", " ", 5 );
			SystemObjectID = -1;
			
			return;
			
		}
		
		break;
		
		case Trigger_PlayerBike:
		
		if( !PlayerPresent ) {
			
			tmp = ent_create( "./CookedObjects/bike7.mdl", temp_pos, Player_Bike );
			tmp->ObjectType = ObjectSystem;
			Scale( tmp, 5 );
			
		}
		
		else {
			
			WriteToBlackboard( " Chi duoc tao mot nhan vat duy nhat! ", " ", 5 );
			SystemObjectID = -1;
			
			return;
			
		}
		
		break;
		
		case Trigger_SpawnNotification:
		
		tmp = ent_create( "./Cooked2D/tree.png", temp_pos, Spawn_Warning );
		tmp->ObjectType = ObjectSystem;
		tmp->ObjectSystemType = Trigger_SpawnNotification;
		
		break;
		
		default: break;
		
	}
	
}

/*
--------------------------------------------------
ENTITY *CreateObject()

Desc: Uses ent_create to create an object based on which value _ObjectType
is holding. Currently, CreateObject() can only creates
normal .mdl/.wmb objects, lights, particle objects,
waypoint and light objects.

Returns:
- Success: pointer to the newly created object.
- Fail: NULL.
--------------------------------------------------
*/
ENTITY *CreateObject() { // This inherits a lot from place_me & the old CreateObject.

	WriteLog("[ ] Trying to create an object through CreateObject()... ");
	NewLine();
	
	//	if( str_cmp(TEMPSTR,undef) ) {
		//		
		//		_beep();
		//		
		//		WriteLog("!! [ERROR] Somehow TEMPSTR is empty, cannot create object, returns NULL.");
		//		NewLine();
		//		
		//		return NULL;
		//		
	//	}
	
	// Stupid object couldn't float
	if(!temp_pos.x && !temp_pos.y && !temp_pos.z) {
		
		_beep();
		WriteLog("!! [ERROR] The cursor's position is out of range, returns a NULL object.");
		NewLine();
		WriteLog("!! Point the cursor to the correct position and try again. Solid ground, for example.");
		NewLine();
		
		return NULL;
		
	}
	
	if( is(InsertObject,SHOW) ) { // If this panel is being shown
		
		return;
		
	}
	
	if( SystemObjectID != -1 ) {
		
		CreateSystemObject ();
		
		return;
		
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
		if( cbRandomPlacement ) tmp.pan = random(360); // Give it a random pan value.
		
		#ifndef A7_DEVELOPMENT
		tmp.material = mtl_model;
		#endif
		
		tmp.ObjectDynamic = 0; // This is a static object
		tmp.ObjectPhysics = 0; // And physics aren't enabled by default.		
		
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
		tmp.z += 50;
		
		tmp.ObjectType = ObjectNode;
		
		WriteLog("[X] Task completed for CreateObject() at ");
		WriteLog( (STRING *) tmp->type );
		NewLine();
		
		return tmp;
		
	}
	
	return NULL; // For objects those fall out of range.
	
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

	if(!cbKernelRunning) {
		
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

	while( cbInBuildment ) {
		
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
		
		//		if( !cbPlaytesting ) { // <- Uncomment this to lock the realtime terrain editing while in Playtest mode
			
			if(TerrainEnt && bSize >=10 && cbTerrainEditing )
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
				
				#ifdef CBOX_DEVELOPMENT
					
					draw_point3d(_vec(vv0.x,vv0.y,vv0.z-10), _vec(0,0,255), 100,10);
					draw_point3d(_vec(vv1.x,vv1.y,vv1.z-10), _vec(0,255,255), 100,8);
					draw_point3d(_vec(vv2.x,vv2.y,vv2.z-10), _vec(0,255,255), 100,8);
					draw_point3d(_vec(vv3.x,vv3.y,vv3.z-10), _vec(0,255,255), 100,8);
					draw_point3d(_vec(vv4.x,vv4.y,vv4.z-10), _vec(0,255,255), 100,8);	
					draw_line3d(_vec(vv0.x,vv0.y,0), _vec(255,255,255), 100);
					//			draw_line3d(_vec(vv0.x,vv0.y,tMaxHeight), _vec(255,255,255), 100);
					
				#endif
				
			}
			
		//		}
		
		wait(1);
		
	}
	
	WriteLog("[X] Task completed for FollowPointer().");
	NewLine();
	
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
		
		/*
		
		if(select.ObjectType > Object && select.ObjectType <= ObjectNode) 
		{
			
			// Perform manual access to clipboard to copy material	
			//			select is selected.
			//			so something must have been copied into mat_temp.
			//			so I directly take mat_temp and copy it into the clipboard.
			//			
			//			otherwise if we pass select.material to clipboard.m,
			//			mat_select is passed but not select's material.
			
			clipboard.m = mat_temp;
		}
		
		*/
		
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
		
		/*
		
		if(select.ObjectType > Object && select.ObjectType <= ObjectNode) 
		{
			//		// Perform manual access to clipboard to copy material
			clipboard.m = mat_temp;
		}
		
		*/
		
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

	if(clipboard.AnyData) {
		
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
void ObjectManipulationCore()

Desc: The following function will handle how the object is manipulated: move, rotate, or scale.
While holding mouse_left, press L/R Alt to downscale the object, or release it to upscale the object.
Why do I have to comment the lines above if you've already read through the code.
Actually this is just an extended version of FollowPointer because I'm too lazy to code a new one.

Returns: -
--------------------------------------------------
*/
int ValidHit() {
	
	if(hit->x||hit->y||hit->z) return 1;
	else return 0;
	
}

void ObjectManipulationCore()
{
	
	WriteLog("[ ] We are at the nuclear core! Oh wait...no, not that stupid core again...");
	NewLine();

	my._BEING_MANIPULATED += 1;

	if((my._BEING_MANIPULATED % 2) == 1) // clicked the object?
	{

		while (mouse_left) wait(1);
		while (!mouse_left) // move the object until the player presses the mouse button again

		{
			
			switch( manip_type ) {
				
				case move:
				
				v1.x = mouse_pos.x;
				v1.y = mouse_pos.y;
				v1.z = 0;
				vec_for_screen(v1,camera);
				v2.x = mouse_pos.x;
				v2.y = mouse_pos.y;
				v2.z = 200000;
				vec_for_screen(v2,camera);
				
				c_trace(v1.x,v2.x,
				
				IGNORE_ME | IGNORE_PASSABLE | IGNORE_MODELS
				
				);
				
				set(my,PASSABLE);
				
				if( ValidHit() ) {
					
					vec_set(my.x,hit.x);
					vec_set(my.y,hit.y);
					vec_set(my.z,hit.z); 
					
				}
				
				break;
				
				case rotate: 
				
				if( button_state(panMain_Top,2,-1) ) {
					
					my.pan = -mouse_pos.x;
					
				}
				
				break;
				
				case scale:
				
				if( button_state(panMain_Top,3,-1) ) {
					
					/*if(my->scale_x >= MINIMUM_SCALE_CONSTANT) */Scale(my, my->scale_z + mickey.z*SCALE_SPEED*.1); // a typical attempt to reduce the scrolling speed
					
					/*
					
					
					if( mickey->z ) {
						
						Scale(my, my.scale_x + SCALE_SPEED);
						
						
						if(key_alt) { // i don't place checker here 'cause it can create jerky effect
							
							if(my.scale_x >= MINIMUM_SCALE_CONSTANT) Scale(my, my.scale_x - SCALE_SPEED);
							
						}
						
					}
					
					*/
					
				}
				
				break;
				
			}
			
			wait(1);

		}
		
		wait(1);

	}

	else
	{
		
		v1.z = 0;
		vec_for_screen(v1,camera);
		v2.z = 200000;
		vec_for_screen(v2,camera);
		c_trace(v1.z,v2.z,IGNORE_ME | IGNORE_PASSABLE | IGNORE_MODELS);
		
		if( ValidHit() ) {
			
			vec_set(my.x,hit.x);
			reset(my,PASSABLE);
			
		}

	}
	
}

/*
--------------------------------------------------
void ObjectManipulationInterface()

Desc: An ObjectManipulationCore() wrapper. It will
be assigned to newly created objects to enable
manipulating of that object. Contains general code 
for every newly born entity.

Includes two simple scene optimization methods 
(cbUsectraceOptimization and cbUseDistanceBasedOptimization).

Two adjustable constants (CBox.h):

FIXED_CULLING_DISTANCE - Distance (without fog)
FOG_CULLING_DISTANCE - Distance (with fog - should be small)

Returns: -
--------------------------------------------------
*/
void ObjectManipulationInterface()
{
	
	WriteLog("[ ] Executing ObjectManipulationInterface()..");
	NewLine();
	
	my._BEING_MANIPULATED = 0;
	
	my.emask |= ENABLE_CLICK;
	my.event = ObjectManipulationCore;
	
	set(my,FLAG2);
	//	while(!my) wait(1);
	
	STRING *temp_ = my->type;

	var Dist = 0;
	
	// These are general code that every entity must have 
	// for example in the editor
	while(my) {
		
		//		if(cbPlaytesting) {
			//			
			//			if(cbUseDistanceBasedOptimization) {
				//				
				//				if(!fog_color) Dist = FIXED_CULLING_DISTANCE;
				//				else { // Fog is active?
					//					
					//					Dist = camera.fog_end + FOG_CULLING_DISTANCE;			   
					//					
				//				}
				//				
				//				if(vec_dist(player->x,my->x) >= Dist)
				//				{
					//					set(my,TRANSLUCENT);
					//					while(my->alpha > 0)
					//					{
						//						my->alpha -= 5 * time_step;
						//						wait(1);
					//					}
					//					reset(my,SHOW);
				//				}
				//				else
				//				{
					//					reset(my,SHOW);
					//					my->alpha = 0;
					//					while(my->alpha <= 100)
					//					{
						//						my->alpha += 5 * time_step;
						//						wait(1);
					//					}
					//					reset(my,TRANSLUCENT);
				//				}
				//				
			//			}
			//			
			//			else { // cbUsectraceOptimization
				//				
				//				 Cac entity trong tam nhin khong the cull lan nhau
				//				if(!is(my,FLAG2)) set(my,FLAG2);
				//				
				//				wait (random(20)); // spread the cpu load over 20 consecutive frames
				//				if(!c_trace(my->x,player->x,IGNORE_ME | IGNORE_FLAG2 | IGNORE_CONTENT | IGNORE_PASSENTS))
				//				{
					//					reset(my,INVISIBLE); // then show it!
					//					while (my.alpha < 100) // run this loop until the entity becomes opaque again
					//					{
						//						my.alpha += 25 * time_step;
						//						wait (1);
					//					}
					//					reset(my,TRANSLUCENT); // get rid of some nasty artifacts when the entity is completely visible
				//				}
				//				else
				//				{
					//					
					//					set(my,TRANSLUCENT);
					//					while (my.alpha > 0)
					//					{
						//						my.alpha -= 25 * time_step;
						//						wait(1);
					//					}
					//					set(my,INVISIBLE);
				//				}
				//				
			//			}
			//			
			//			
		//		}
		//		
		wait(1);
		
	}
	
	WriteLog("[X] Task completed for ObjectManipulationInterface() at ");
	WriteLog(temp_);
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


ENTITY *Gun = {
	
	layer = 1000;
	
	type = "gun.mdl";
	
	x = 23;
	y = -2;
	z = -22;
	
	scale_x = 2;
	scale_y = 2;
	scale_z = 2;
	
	view = camera;
	
}

void Gun_startup() {
	
	VECTOR trace_coords;
	
	while(1) {
		
		#ifdef CBOX_DEVELOPMENT
			
			Gun.x += 5 * (key_y-key_u)*time_step;
			Gun.y += 5 * (key_h-key_j)*time_step;
			Gun.z += 5 * (key_b-key_n)*time_step;
			
		#endif
		
		if( cbPlaytesting ) {
			
			vec_set(trace_coords.x,vector(100000,0,0));
			//			vec_rotate(trace_coords.x,Gun.pan);
			//			vec_add(trace_coords.x,Gun.x);
			c_trace(Gun.x,trace_coords.x,IGNORE_ME|IGNORE_PASSABLE);
			
			if(hit)
			{
				draw_line3d(Gun.x,NULL,100);
				draw_line3d(Gun.x,COLOR_RED,100);
				draw_line3d(target.x,COLOR_RED,100);
				draw_point3d(hit.x,COLOR_RED,100,3);
			}
			else
			{
				draw_line3d(Gun.x,NULL,100);
				draw_line3d(Gun.x,COLOR_RED,100);
				draw_line3d(trace_coords.x,COLOR_RED,100);
				draw_point3d(trace_coords.x,COLOR_RED,100,3);
			}
			
		}

		wait(1);
		
	}
	
}

void draw_rotated_bbox(ENTITY* ent)
{
	VECTOR c1,c2,c3,c4,c5,c6,c7,c8;  
	
	vec_set(c1,vector(ent.min_x,ent.min_y,ent.min_z));    
	vec_rotate(c1,ent.pan);
	vec_add(c1,ent.x);
	
	vec_set(c2,vector(ent.max_x,ent.min_y,ent.min_z));    
	vec_rotate(c2,ent.pan);
	vec_add(c2,ent.x);
	
	vec_set(c3,vector(ent.max_x,ent.max_y,ent.min_z));    
	vec_rotate(c3,ent.pan);
	vec_add(c3,ent.x);
	
	vec_set(c4,vector(ent.min_x,ent.max_y,ent.min_z));    
	vec_rotate(c4,ent.pan);
	vec_add(c4,ent.x);
	
	vec_set(c5,vector(ent.min_x,ent.min_y,ent.max_z));    
	vec_rotate(c5,ent.pan);
	vec_add(c5,ent.x);
	
	vec_set(c6,vector(ent.max_x,ent.min_y,ent.max_z));    
	vec_rotate(c6,ent.pan);
	vec_add(c6,ent.x);
	
	vec_set(c7,vector(ent.max_x,ent.max_y,ent.max_z));    
	vec_rotate(c7,ent.pan);
	vec_add(c7,ent.x);
	
	vec_set(c8,vector(ent.min_x,ent.max_y,ent.max_z));    
	vec_rotate(c8,ent.pan);
	vec_add(c8,ent.x);	
	
	draw_line3d(c1,NULL,100); 
	draw_line3d(c2,vector(0,255,0),100);
	draw_line3d(c3,vector(0,255,0),100);
	draw_line3d(c4,vector(0,255,0),100);
	draw_line3d(c1,vector(0,255,0),100);
	
	draw_line3d(c5,NULL,100);
	draw_line3d(c6,vector(0,255,0),100);
	draw_line3d(c7,vector(0,255,0),100);
	draw_line3d(c8,vector(0,255,0),100);
	draw_line3d(c5,vector(0,255,0),100);

	draw_line3d(c1,NULL,100);
	draw_line3d(c5,vector(0,255,0),100);
	
	draw_line3d(c2,NULL,100);
	draw_line3d(c6,vector(0,255,0),100);
	
	draw_line3d(c3,NULL,100);
	draw_line3d(c7,vector(0,255,0),100);
	
	draw_line3d(c4,NULL,100);
	draw_line3d(c8,vector(0,255,0),100);
}

#endif