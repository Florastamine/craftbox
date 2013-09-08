/*
--------------------------------------------------
CBoxCore.c

This file contains all the ingredients for making
up the kernel. Actions' functions will also be placed
here. Please note that this file contains ONLY 
kernel-related code, GUI/HUD code is placed separately
in CBoxShell.c.

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

>+++
--------------------------------------------------
*/

#include "CBoxDDecl.c"
#include "CBoxAct.c"

/*
--------------------------------------------------
void TakeScreenshot()

Desc: Uses file_for_screen to take a JPG screenshot
and names the captured file as pref_shot. This function
is independent and can be used anywhere within the code
or assigned to an input key.

Returns: -
--------------------------------------------------
*/
void TakeScreenshot() {
	
	file_for_screen(FILE_SCREENSHOT,shot);
	shot++;
	
	set(panScreenshot,SHOW);
	
	while(panScreenshot.alpha > 0) {
		
		panScreenshot.alpha -= 10 * time_step;
		wait(1);
		
	}

	reset(panScreenshot,SHOW);
	panScreenshot.alpha = 100;
	
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
	if(!my) return -1;

	my_target_node = me;
	my_target_node.emask |= ENABLE_SCAN;
	
	while(my) {
		
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
	
	if(!my) return -1;
	
	ent_playloop(my,sndobjs[num_sndobjs],100);
	
	while(my) {
		
		wait(1);
		
	}
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
	
	if(!my) return -1;
	
	set(my, BRIGHT | NOFOG | PASSABLE | TRANSLUCENT);
	
	/* Some adjustments for our little jabber.png */
	my.scale_x = my.scale_y = my.scale_z /= 2;
	
	my.alpha = DEFAULT_ALPHA+25;
	my.ambient = 100;
	
	my.lightrange = random(500);
	vec_set(my.red,vector(random(255),random(255),random(255)));
	
	my.z += 100;
	
	if(my.FlickSpeed <= 0) my.FlickSpeed = .5;
	
	// Like men and women, lights should equal to normal entities.
	// They have the rights to be manipulated by the mouse.
	// oooh, wait, isn't the mouse belonged to the government??
	// ...
	// oh no.
	my.emask |= ENABLE_CLICK;
	// my.event = 	
	
	while(my) { // This loop will active as long as its entity is alive.
		
		if(my.LightMode == flick) { // Flickering lights (Flashing lights)
			
			my.lightrange = 0;
			wait(-my.FlickSpeed);
			my.lightrange = olrange;
			wait(-my.FlickSpeed);
			
		}
		
		if(my.LightMode == disco) { // Lights that change its r/g/b values continuously.
			
			random_seed(0);
			
			my.red = random(255);
			my.green = random(255);
			my.blue = random(255);
			
			wait(-.1);
			
		}
		
		wait(1);
	}
}

/*
--------------------------------------------------
void FixObjectScale(ENTITY *e)

Desc: This function will fix incorrect scale ratio on models.
Actually, I borrowed models from various source, and surely,
they don't have the same scale ratio. So this quick fix
will re-scale the models.

Returns: -
--------------------------------------------------
*/
void FixObjectScale(ENTITY *e) {
	
	switch(num_mdlobjs) {
		
		case 52: // church/temple model
		e.scale_x = e.scale_y = e.scale_z *= 3;
		
		break;
		/////////////////////////////////////////////////////////////// 
		case 51: // big building
		e.scale_x = e.scale_y = e.scale_z *= 2;
		
		break;
		///////////////////////////////////////////////////////////////
		case 53: // [big] fence
		e.scale_x = e.scale_y = e.scale_z /= 1.5;
		
		break;
		///////////////////////////////////////////////////////////////		
		case 54: // [big] fence bar
		e.scale_x = e.scale_y = e.scale_z /= 1.5;
		
		break;
		///////////////////////////////////////////////////////////////		
		case 55: // wood entrance
		e.scale_x = e.scale_y = e.scale_z *= 2;
		
		break;
		///////////////////////////////////////////////////////////////
		case 2: // bird
		e.scale_x = e.scale_y = e.scale_z /= 2;
		
		break;
		///////////////////////////////////////////////////////////////
		case 12: // idk what is this
		e.scale_x = e.scale_y = e.scale_z *= 2;
		
		break;
		///////////////////////////////////////////////////////////////
		case 55: // generic wood gate
		e.scale_x = e.scale_y = e.scale_z *= 3;
		
		break;
		
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
- Success: pointer of the newly created object.
- Fail: NULL object.
--------------------------------------------------
*/
ENTITY *CreateObject() { // This inherits a lot from place_me

	// Stupid object couldn't float
	if(!temp_pos.x && !temp_pos.y && !temp_pos.z) return;
	
	ENTITY *tmp;

	switch(_ObjectType) {
		
		////////////////////////////////////////////////////////////
		case NormalObject:
		
		if(str_len(mdlobjs_table_ptr[num_mdlobjs]) == 0) {
			
			printf("Wrong object ID.\nMaybe you're trying to access unallocated space in the object database.");
			return NULL;
			
		}
		
		tmp = ent_create(mdlobjs_table_ptr[num_mdlobjs],temp_pos.x,ObjectManipulationInterface);
		
		while(tmp == NULL) wait(1); // wait for tmp to be completely created.
		
		FixObjectScale(tmp);
		
		set(tmp, POLYGON);
		reset(tmp, NOFOG | INVISIBLE | TRANSLUCENT); // Tha giet nham con hon bo sot
		
		tmp.alpha = 0;
		tmp.ambient = 50;
		tmp.pan = random(360); // Give it a random pan value.
		
		tmp.material = mtl_model;
		
		tmp.ObjectType = NormalObject;
		tmp.ObjectID = num_mdlobjs;
		
		tmp.ObjectDynamic = 0; // This is a static object
		tmp.ObjectPhysics = 0; // And physics aren't enabled by default.		
		
		return tmp;
		
		break;
		////////////////////////////////////////////////////////////
		
		////////////////////////////////////////////////////////////
		// Lights don't have a database. So the "unallocated space"
		// error would never happen.
		
		case Light:
		
		tmp = ent_create("jabber.png",temp_pos.x,GenerateLight);
		
		tmp.ObjectType = Light; // Du sao thi light cung ngan hon _ObjectType
		// Lights don't have IDs so passing them is redundant.
		
		return tmp;
		
		break;
		////////////////////////////////////////////////////////////
		
		////////////////////////////////////////////////////////////
		case Particle :
		
		switch(num_partobjs) {
			
			case part_spiral: tmp = ent_create("desktop_effect.png",temp_pos.x,emit_spiral); break;
			case part_colorfulspark: tmp = ent_create("desktop_effect.png",temp_pos.x,emit_colorfulspark); break;
			case part_spacehole: tmp = ent_create("desktop_effect.png",temp_pos.x,emit_spacehole); break;
			case part_fountain2: tmp = ent_create("desktop_effect.png",temp_pos.x,emit_fountain2); break;
			case part_fountain1: tmp = ent_create("desktop_effect.png",temp_pos.x,emit_fountain1); break;
			case part_fire2: tmp = ent_create("desktop_effect.png",temp_pos.x,emit_fire2); break;
			case part_fire1: tmp = ent_create("desktop_effect.png",temp_pos.x,emit_fire1); break;
			case part_doublehelix: tmp = ent_create("desktop_effect.png",temp_pos.x,emit_doublehelix); break;
			case part_composition: tmp = ent_create("desktop_effect.png",temp_pos.x,emit_composition); break;
			
			default:
			
			printf("num_partobjs outside range.");
			return NULL;
			
			break; // redundant, maybe.
			
		}
		
		set(tmp, BRIGHT | NOFOG | PASSABLE | TRANSLUCENT);
		
		tmp.ObjectType = Particle;
		tmp.ObjectID = num_partobjs;
		
		tmp.scale_x = tmp.scale_y = tmp.scale_z /= 2;
		
		tmp.z += 125;
		tmp.alpha = DEFAULT_ALPHA+25;
		tmp.ambient = 100;
		
		return tmp;
		
		break;	
		////////////////////////////////////////////////////////////
		
		////////////////////////////////////////////////////////////
		case Sound:
		
		if(!sndobjs[num_sndobjs] || num_sndobjs < 0 || num_sndobjs > 50) {
			
			printf("Wrong sound ID or damaged sound file.\nMaybe you're trying to access unallocated space in the sound database.");
			return NULL;
			
		}
		
		tmp = ent_create("sound_32.png",temp_pos.x,GenerateSound);
		
		set(tmp, BRIGHT | NOFOG | PASSABLE | TRANSLUCENT);
		
		// Am thanh nho be cu de cho no an :|
		//		tmp.scale_x = tmp.scale_y = tmp.scale_z /= 2;
		
		tmp.z += 125;
		tmp.alpha = DEFAULT_ALPHA+25;
		tmp.ambient = 100;
		
		tmp.ObjectType = Sound;
		tmp.ObjectID = num_sndobjs;
		
		return tmp;
		
		break;
		////////////////////////////////////////////////////////////
		
		////////////////////////////////////////////////////////////
		case Node:
		tmp = ent_create("ix_waypoint.mdl",temp_pos.x,GenerateWaypoint);
		
		set(tmp, BRIGHT | PASSABLE);
		tmp.ambient = 100;
		
		tmp.scale_x = tmp.scale_y = tmp.scale_z *= 1.5;
		
		tmp.ObjectType = Node;
		
		return tmp;
		
		break;
		////////////////////////////////////////////////////////////
		
		////////////////////////////////////////////////////////////
		case Terrain :
		
		return NULL;
		
		break;
		////////////////////////////////////////////////////////////
		
		default:
		
		printf("_ObjectType outside range.");
		return NULL;
		
		break;
		
		
	}
}

/*
void main(void) {
	//	CreateDirectory("cd",0);
	scan_folder("sharedData","pcx");
}
*/

/*
--------------------------------------------------
void FolderScan(STRING *dir, STRING *ext)


--------------------------------------------------
*/
void FolderScan(STRING *dir, STRING *ext)
{
	TEXT *read_files = txt_create(1000,1);
	
	STRING *search_form = "a";

	str_cpy(current_folder,dir);

	str_cpy(search_form,dir);
	str_cat(search_form,"\\*.");
	str_cat(search_form,ext);
	
	files_found = txt_for_dir(read_files, search_form);
	
	var num = files_already;
	while(num<999)
	{
		str_cpy((files_list.pstring)[num],"");
		num++;
	}
	
	num=0;
	while(num<files_found)
	{
		str_cpy((files_list.pstring)[num+files_already],(read_files.pstring)[num]);
		num++;
	}
	list_start=0;
	
	wait(1);
}

/* 
--------------------------------------------------
int PlayVideo(STRING *what, var vol)

Desc: A media_play wrapper which plays a multimedia file 
and wait until it ends. Combine with wait_for to get the 
desired effect.

Returns: -1 if the file couldn't be opened.
--------------------------------------------------
*/
int PlayVideo(STRING *what, var vol) {
	proc_kill(4);

	var hndl;
	
	if(!media_play(what,NULL,0)) return -1;
	else hndl = media_play(what,NULL,abs(vol));

	while(media_playing(hndl)) wait(1);
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
	proc_mode = PROC_LATE  ; // I'm so stupid...
	
	fpsf_marker = me;
	set(fpsf_marker,PASSABLE);

	while(1) {
		
		cpos1.x = mouse_pos.x;
		cpos1.y = mouse_pos.y;
		cpos1.z = 0;
		vec_for_screen(cpos1,camera);
		cpos2.x = mouse_pos.x;
		cpos2.y = mouse_pos.y;
		cpos2.z = 200000;
		vec_for_screen(cpos2,camera);

		c_trace(cpos1.x,cpos2.x,IGNORE_ME | IGNORE_PASSABLE | IGNORE_MODELS);
		vec_set(fpsf_marker.x,hit.x);
		vec_set(temp_pos.x,hit.x);
		
		wait(1);
		
	}
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
	
	if(!is(panProp,SHOW)) return -1;
	
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
	
	if(select) {
		select.alpha = 0;
		select.ambient = 0;
		reset(select, BRIGHT | INVISIBLE | NOFOG | OVERLAY | PASSABLE | SHADOW | TRANSLUCENT);
		if(!is(select,POLYGON)) set(select,POLYGON);
		
		PassObjectPropertiesToGUI(select); // update the properties panel
	}
	
}

/*
--------------------------------------------------
void ObjectRandomPan()


--------------------------------------------------
*/
void ObjectRandomPan() {

	if(select) select.pan = random(360);

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

	// Clear evidence first
	int i = id;
	while(i > 0) {
		
		button_state(panProp_2,i,0);
		i--;
		
	}

	i = id; // fetch again
	while(i < 16) {
		
		button_state(panProp_2,i,0);
		i++;
		
	}

	button_state(panProp_2,id,1);

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
			
			return -1;
			
			break;
			
		}
		
	}

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
	
	// This is an exception - an unplanned feature.
	if(o.ObjectType == Terrain) return -1;

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

	////////////////////////////////////////////////////////////
	switch(o.ObjectType) {
		
		////////////////////////////////////////////////////////////
		case NormalObject:
		
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
		
		of.oid = o.ObjectID;
		of.of_objtype = o.ObjectType;
		
		of.pStatic = o.ObjectDynamic;
		of.pPhysics = o.ObjectPhysics;
		
		// Flag indicates that the copy progress has done.
		// Also, it can be used to determine if the clipboard has any piece of data or not.
		of.dp = 1;
		
		break;
		////////////////////////////////////////////////////////////
		
		////////////////////////////////////////////////////////////
		case Light:
		
		of._red = o.red;
		of._green = o.green;
		of._blue = o.blue;
		of._range = o.lightrange;
		of._LightMode = o.LightMode;
		
		of.of_objtype = o.ObjectType;
		
		of.dp = 1;
		
		break;
		////////////////////////////////////////////////////////////
		
		////////////////////////////////////////////////////////////
		case Sound:
		
		of.of_objtype = o.ObjectType;
		of.oid = o.ObjectID;
		
		of.dp = 1;
		
		break;
		////////////////////////////////////////////////////////////
		
		////////////////////////////////////////////////////////////
		case Particle:
		
		of.of_objtype = o.ObjectType;
		of.oid = o.ObjectID;
		
		of.dp = 1;
		
		break;
		////////////////////////////////////////////////////////////
		
		////////////////////////////////////////////////////////////
		case Node:
		
		of.of_objtype = o.ObjectType;
		
		of.dp = 1;
		
		break;
		////////////////////////////////////////////////////////////
		
		default:
		
		of.of_objtype = -1; // Neutral object
		return -1;
		
		break;
		
	}

}

/*
--------------------------------------------------
void PassClipboardDataToObject(ENTITY *e)

Desc: Copies general information from the clipboard 
struct to ENTITY *e, and continues to copy the remaining 
unique characteristics information based on clipboard.of_objtype.

Returns: -
--------------------------------------------------
*/
void PassClipboardDataToObject(ENTITY *e) {

	if(e.ObjectType == Terrain) return;

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

	////////////////////////////////////////////////////////////	
	switch(clipboard.of_objtype) {
		
		// Neutral object
		case -1:
		
		// Do nothing
		
		break;
		
		////////////////////////////////////////////////////////////
		case NormalObject:
		
		e.ObjectType = clipboard.of_objtype;
		e.ObjectID = clipboard.oid;
		
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
		
		break;
		////////////////////////////////////////////////////////////
		
		////////////////////////////////////////////////////////////
		case Light:
		
		e.red = clipboard._red;
		e.green = clipboard._green;
		e.blue = clipboard._blue;
		e.lightrange = clipboard._range;
		e.LightMode = clipboard._LightMode;
		
		e.material = mtl_model;
		
		break;
		////////////////////////////////////////////////////////////
		
		////////////////////////////////////////////////////////////
		case Particle:
		
		e.material = mtl_model;
		
		break;
		////////////////////////////////////////////////////////////
		
		////////////////////////////////////////////////////////////
		case Sound:
		
		e.material = mtl_sprite;
		
		break;
		////////////////////////////////////////////////////////////
		
	}

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

	if(select) {
		
		PassObjectDataToClipboard(select,clipboard);
		
		if(select.ObjectType == NormalObject) 
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

	if(select) {
		
		PassObjectDataToClipboard(select,clipboard);
		
		if(select.ObjectType == NormalObject) 
		{
			//		// Perform manual access to clipboard to copy material
			clipboard.m = mat_temp;
		}
	}

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

	if(clipboard.dp) {
		
		int _ObjectType_old = _ObjectType, ObjectID_old;
		
		if(clipboard.of_objtype == Particle) {
			
			ObjectID_old = num_partobjs;
			num_partobjs = clipboard.oid;
			
		}
		if(clipboard.of_objtype == NormalObject) {
			
			ObjectID_old = num_mdlobjs;
			num_mdlobjs = clipboard.oid;
			
		}
		
		if(clipboard.of_objtype == Sound) {
			
			ObjectID_old = num_sndobjs;
			num_sndobjs = clipboard.oid;
			
		}
		
		_ObjectType = clipboard.of_objtype;
		
		PassClipboardDataToObject(CreateObject());
		
		if(clipboard.of_objtype == Particle) num_partobjs = ObjectID_old;
		if(clipboard.of_objtype == NormalObject) num_mdlobjs = ObjectID_old;
		if(clipboard.of_objtype == Sound) num_sndobjs = ObjectID_old;
		
	}

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
	while(m == NULL) wait(1); // wait for m to be completely created

	var vpass = file_open_read(file);
	if(vpass == 0) {
		
		printf("Failed to open %s for passing parameters.",file);
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
	while(m == NULL) wait(1);
	
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

	while(m == NULL) wait(1);

	var vpass = file_open_write(file);
	if(vpass == 0) {
		
		printf("Failed to open %s for writing data.",file);
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
		printf("Material saving is available only to custom materials.");
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
	while(mouse_left && (manip_type > 0 && manip_type < 4))
	{
		
		if(manip_type == scale) 
		{
			GGUIHide();
			
			if(key_alt) {
				
				my.scale_x -= .05;
				my.scale_y -= .05;
				my.scale_z -= .05;
				
			}
			
			else {
				
				my.scale_x += .05;
				my.scale_y += .05;
				my.scale_z += .05;
				
			}
			
		}
		
		if(manip_type == move) {
			
			GGUIHide();
			
			v1.x = mouse_pos.x;
			v1.y = mouse_pos.y;
			v1.z = 0;
			vec_for_screen(v1,camera);
			v2.x = mouse_pos.x;
			v2.y = mouse_pos.y;
			v2.z = 200000;
			vec_for_screen(v2,camera);
			
			c_trace(v1.x,v2.x,IGNORE_ME | IGNORE_PASSABLE | IGNORE_MODELS);
			vec_set(my.x,hit.x);
			
		}
		
		if(manip_type == rotate) {
			
			GGUIHide();
			
			my.pan = -mouse_pos.x;
			//			my.tilt = -mouse_pos.y;
			
		}
		
		

		wait (1);
	}

	GGUIShow();

}

/*
--------------------------------------------------
void ObjectManipulationInterface()

Desc: An ObjectManipulationCore() wrapper. It will
be assigned to newly created objects to enable
manipulating of that object.

Includes two simple scene optimization methods 
(C_TRACE_OPTIMIZATION and DISTANCE_OPTIMIZATION).

Two adjustable constants (CBox.h):

FIXED_CULLING_DISTANCE - Distance (without fog)
FOG_CULLING_DISTANCE - Distance (with fog - should be small)

Returns: -
--------------------------------------------------
*/
void ObjectManipulationInterface()
{
	my.emask |= ENABLE_CLICK;
	my.event = ObjectManipulationCore;
	
	var Dist = 0;
	
	while(my) {
		
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
}

/*
--------------------------------------------------
void ExitEvent()

Desc: Peform various tasks prior to exiting craftbox. 
These include writing configuation files, saving variables...

Returns: -
--------------------------------------------------
*/
void ExitEvent() {
	
	ConfigFileWrite(FILE_CONFIG);
	wait_for(ConfigFileWrite);
	
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
	
	wait(1);
	
}

/*
--------------------------------------------------
int ConfigFileWrite(STRING *cf)

Desc: Writes engine variables to "cf" ( [c]onfig [f]ile ).

Returns: -1 if "cf" couldn't be opened.
--------------------------------------------------
*/
int ConfigFileWrite(STRING *cf) {

	var file = file_open_write(cf);
	
	if(!file) {
		
		printf("Failed to open file handle for writing configuration to %s",cf);
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
	- video_mode
	- video_depth
	- video_screen

	*/
	
	// Graphics + system
	file_var_write(file,d3d_anisotropy);
	file_var_write(file,d3d_antialias);
	file_var_write(file,d3d_mipmapping);
	file_var_write(file,d3d_triplebuffer);
	file_var_write(file,d3d_lightres);
	file_var_write(file,video_aspect);
	file_var_write(file,video_gamma);
	file_var_write(file,video_mode);
	file_var_write(file,video_depth);
	file_var_write(file,video_screen);
	
	file_var_write(file,shot);

	file_close(file);

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

	var file = file_open_read(cf);
	if(!file) { // Fail? Then use default settings.
		
		printf("Failed to open file handle for reading configuration from %s.\nDefault configuration will now be applied.",cf);
		
		/* Default config. goes here. */
		
		return -1;
		
	}
	
	// Graphics + system first
	d3d_anisotropy = file_var_read(file);
	d3d_antialias = file_var_read(file);
	d3d_mipmapping = file_var_read(file);
	d3d_triplebuffer = file_var_read(file);
	d3d_lightres = file_var_read(file);

	video_aspect = file_var_read(file);
	video_gamma = file_var_read(file);
	video_mode = file_var_read(file);
	video_depth = file_var_read(file);
	video_screen = file_var_read(file);
	
	shot = file_var_read(file);

	file_close(file);
}

//void save_level(STRING *filef) {
	//	
	//	STRING *filef_original = str_create("#300");
	//	str_cpy(filef_original,filef);
	//	
	//	var hndl_sys = file_open_write(str_cat(filef,"_sys.txt"));
	//	str_cpy(filef,filef_original);
	//	
	//	var hndl_mdlobjs = file_open_write(str_cat(filef,"_ents.txt"));
	//	str_cpy(filef,filef_original);
	//	
	//	var hndl_lights = file_open_write(str_cat(filef,"_lights.txt"));
	//	str_cpy(filef,filef_original);
	//	
	//	var hndl_parts = file_open_write(str_cat(filef,"_parts.txt"));
	//	str_cpy(filef,filef_original);
	//	
	//	var hndl_snds = file_open_write(str_cat(filef,"_snds.txt"));
	//	str_cpy(filef,filef_original);
	//	
	//	var hndl_terraindata = file_open_write(str_cat(filef,"_tdata.txt"));
	//	str_cpy(filef,filef_original);
	//	
	//	var hndl_nodedata = file_open_write(str_cat(filef,"_ndata.txt"));
	//	str_cpy(filef,filef_original);
	//	
	//	var hndl_garbage = file_open_write(str_cat(filef,"_trash.txt"));
	//	str_cpy(filef,filef_original);
	//	
	//	// Get the first entity in entities list
	//	you = ent_next(NULL);
	//	
	//	// Begin checking and writing entities data into various file handles.
	//	while(you) {
		//		
		//		switch(you.ObjectType) {
			//			
			//			case NormalObject :
			//			/*
			//			x,y,z
			//			scale_x,scale_y,scale_z
			//			pan,tilt,roll
			//			alpha,ambient
			//			8 flags:
			//			- BRIGHT/INVISIBLE/NOFOG/OVERLAY/PASSABLE/POLYGON/SHADOW/TRANSLUCENT
			//			object ID
			//			// material
			//			static/dynamic
			//			physics
			//			object_type
			//			*/
			//			file_var_write(hndl_mdlobjs,you.ObjectID); // Object ID
			//			file_var_write(hndl_mdlobjs,you.ObjectType); // The type of the object
			//			
			//			file_var_write(hndl_mdlobjs,you.x);
			//			file_var_write(hndl_mdlobjs,you.y);
			//			file_var_write(hndl_mdlobjs,you.z);
			//			
			//			file_var_write(hndl_mdlobjs,you.scale_x);
			//			file_var_write(hndl_mdlobjs,you.scale_y);
			//			file_var_write(hndl_mdlobjs,you.scale_z);
			//			
			//			file_var_write(hndl_mdlobjs,you.pan);
			//			file_var_write(hndl_mdlobjs,you.tilt);
			//			file_var_write(hndl_mdlobjs,you.roll);
			//			
			//			file_var_write(hndl_mdlobjs,you.alpha);
			//			file_var_write(hndl_mdlobjs,you.ambient);
			//			
			//			if(is(you,BRIGHT)) file_var_write(hndl_mdlobjs,1);
			//			else file_var_write(hndl_mdlobjs,0);
			//			
			//			if(is(you,INVISIBLE)) file_var_write(hndl_mdlobjs,1);
			//			else file_var_write(hndl_mdlobjs,0);
			//			
			//			if(is(you,NOFOG)) file_var_write(hndl_mdlobjs,1);
			//			else file_var_write(hndl_mdlobjs,0);
			//			
			//			if(is(you,OVERLAY)) file_var_write(hndl_mdlobjs,1);
			//			else file_var_write(hndl_mdlobjs,0);
			//			
			//			if(is(you,PASSABLE)) file_var_write(hndl_mdlobjs,1);
			//			else file_var_write(hndl_mdlobjs,0);
			//			
			//			if(is(you,POLYGON)) file_var_write(hndl_mdlobjs,1);
			//			else file_var_write(hndl_mdlobjs,0);
			//			
			//			if(is(you,SHADOW)) file_var_write(hndl_mdlobjs,1);
			//			else file_var_write(hndl_mdlobjs,0);
			//			
			//			if(is(you,TRANSLUCENT)) file_var_write(hndl_mdlobjs,1);
			//			else file_var_write(hndl_mdlobjs,0);
			//			
			//			file_var_write(hndl_mdlobjs,you.ObjectDynamic); // Object state, dynamic/static
			//			file_var_write(hndl_mdlobjs,you.ObjectPhysics); // Physics flag
			//			
			//			break;
			//			
			//			case Light :
			//			/*
			//			x,y,z,pan,tilt,roll, alpha,ambient
			//			r/g/b
			//			lightrange
			//			mode
			//			*/
			//			
			//			file_var_write(hndl_lights,you.x);
			//			file_var_write(hndl_lights,you.y);
			//			file_var_write(hndl_lights,you.z);
			//			
			//			file_var_write(hndl_lights,you.pan);
			//			file_var_write(hndl_lights,you.tilt);
			//			file_var_write(hndl_lights,you.roll);
			//			
			//			file_var_write(hndl_lights,you.ambient);
			//			file_var_write(hndl_lights,you.alpha);
			//			
			//			file_var_write(hndl_lights,you.red);
			//			file_var_write(hndl_lights,you.green);
			//			file_var_write(hndl_lights,you.blue);
			//			
			//			file_var_write(hndl_lights,you.lightrange);
			//			file_var_write(hndl_lights,you.LightMode);
			//			file_var_write(hndl_lights,you.FlickSpeed);
			//			break;
			//			
			//			case Particle :
			//			
			//			file_var_write(hndl_parts,you.ObjectID);
			//			file_var_write(hndl_parts,you.ObjectType);
			//			
			//			/*x,y,z,pan,tilt,roll,ambient,alpha
			//			ObjectID,ObjectType*/
			//			file_var_write(hndl_parts,you.x);
			//			file_var_write(hndl_parts,you.y);
			//			file_var_write(hndl_parts,you.z);
			//			
			//			file_var_write(hndl_parts,you.pan);
			//			file_var_write(hndl_parts,you.tilt);
			//			file_var_write(hndl_parts,you.roll);
			//			
			//			file_var_write(hndl_parts,you.ambient);
			//			file_var_write(hndl_parts,you.alpha);
			//			
			//			break;
			//			
			//			case Sound :
			//			
			//			file_var_write(hndl_snds,you.ObjectID);
			//			file_var_write(hndl_snds,you.ObjectType);
			//			
			//			/*x,y,z,pan,tilt,roll, ambient, alpha, ObjectID, ObjectType */
			//			file_var_write(hndl_snds,you.x);
			//			file_var_write(hndl_snds,you.y);
			//			file_var_write(hndl_snds,you.z);
			//			
			//			file_var_write(hndl_snds,you.pan);
			//			file_var_write(hndl_snds,you.tilt);
			//			file_var_write(hndl_snds,you.roll);
			//			
			//			file_var_write(hndl_snds,you.ambient);
			//			file_var_write(hndl_snds,you.alpha);
			//			
			//			break;
			//			
			//			case Node :
			//			/*x,y,z*/
			//			file_var_write(hndl_nodedata,you.x);
			//			file_var_write(hndl_nodedata,you.y);
			//			file_var_write(hndl_nodedata,you.z);
			//			break;
			//			
			//			case Terrain :
			//			break;
			//			
			//			default: // garbage entities
			//			/* x,y,z, scale_x/y/z,pan,tilt,roll,
			//			alpha,ambient, +8 flags, */
			//			
			//			//you!=NULL
			//			file_var_write(hndl_garbage,you.x);
			//			file_var_write(hndl_garbage,you.y);
			//			file_var_write(hndl_garbage,you.z);
			//			
			//			file_var_write(hndl_garbage,you.scale_x);
			//			file_var_write(hndl_garbage,you.scale_y);
			//			file_var_write(hndl_garbage,you.scale_z);
			//			
			//			file_var_write(hndl_garbage,you.pan);
			//			file_var_write(hndl_garbage,you.tilt);
			//			file_var_write(hndl_garbage,you.roll);
			//			
			//			file_var_write(hndl_garbage,you.alpha);
			//			file_var_write(hndl_garbage,you.ambient);
			//			
			//			if(is(you,BRIGHT)) file_var_write(hndl_garbage,1);
			//			else file_var_write(hndl_garbage,0);
			//			
			//			if(is(you,INVISIBLE)) file_var_write(hndl_garbage,1);
			//			else file_var_write(hndl_garbage,0);
			//			
			//			if(is(you,NOFOG)) file_var_write(hndl_garbage,1);
			//			else file_var_write(hndl_garbage,0);
			//			
			//			if(is(you,OVERLAY)) file_var_write(hndl_garbage,1);
			//			else file_var_write(hndl_garbage,0);
			//			
			//			if(is(you,PASSABLE)) file_var_write(hndl_garbage,1);
			//			else file_var_write(hndl_garbage,0);
			//			
			//			if(is(you,POLYGON)) file_var_write(hndl_garbage,1);
			//			else file_var_write(hndl_garbage,0);
			//			
			//			if(is(you,SHADOW)) file_var_write(hndl_garbage,1);
			//			else file_var_write(hndl_garbage,0);
			//			
			//			if(is(you,TRANSLUCENT)) file_var_write(hndl_garbage,1);
			//			else file_var_write(hndl_garbage,0);
			//			
			//			break;
			//			
		//		}
		//		
		//		you = ent_next(you);
		//		wait(1);
		//		
	//	}
	//	
	//	file_var_write(hndl_mdlobjs,999999);
	//	
	//	// Write to system.
	//	file_var_write(hndl_sys,camera.x);
	//	file_var_write(hndl_sys,camera.y);
	//	file_var_write(hndl_sys,camera.z);
	//	file_var_write(hndl_sys,camera.pan);
	//	file_var_write(hndl_sys,camera.tilt);
	//	file_var_write(hndl_sys,camera.roll);
	//	file_var_write(hndl_sys,camera.aspect);
	//	file_var_write(hndl_sys,camera.arc);
	//	file_var_write(hndl_sys,camera.ambient);
	//	file_var_write(hndl_sys,sun_light);
	//	file_var_write(hndl_sys,sun_angle.pan);
	//	file_var_write(hndl_sys,sun_angle.tilt);
	//	file_var_write(hndl_sys,sun_color.blue);
	//	file_var_write(hndl_sys,sun_color.green);
	//	file_var_write(hndl_sys,sun_color.red);
	//	file_var_write(hndl_sys,fog_color);
	//	file_var_write(hndl_sys,d3d_fogcolor1.red);
	//	file_var_write(hndl_sys,d3d_fogcolor1.green);
	//	file_var_write(hndl_sys,d3d_fogcolor1.blue);
	//	file_var_write(hndl_sys,d3d_fogcolor2.red);
	//	file_var_write(hndl_sys,d3d_fogcolor2.green);
	//	file_var_write(hndl_sys,d3d_fogcolor2.blue);
	//	file_var_write(hndl_sys,d3d_fogcolor3.red);
	//	file_var_write(hndl_sys,d3d_fogcolor3.green);
	//	file_var_write(hndl_sys,d3d_fogcolor3.blue);
	//	file_var_write(hndl_sys,d3d_fogcolor4.red);
	//	file_var_write(hndl_sys,d3d_fogcolor4.green);
	//	file_var_write(hndl_sys,d3d_fogcolor4.blue);
	//	file_var_write(hndl_sys,camera.fog_start);
	//	file_var_write(hndl_sys,camera.fog_end);
	//	file_var_write(hndl_sys,skCube);
	//	
	//	// Close
	//	file_close(hndl_sys);
	//	file_close(hndl_mdlobjs);
	//	file_close(hndl_lights);
	//	file_close(hndl_parts);
	//	file_close(hndl_snds);
	//	file_close(hndl_terraindata);
	//	file_close(hndl_nodedata);
	//	file_close(hndl_garbage);
//}

/*
--------------------------------------------------
void LoadNewLevel()

Desc: Loads a blank level.

Returns: -
--------------------------------------------------
*/
void LoadNewLevel() {

	level_load("dry.wmb");
	/*
	switch(skCube) {
		
		case 0:
		
		_cube = ent_createlayer("s_shamrock+6.tga",SKY | CUBE | SHOW,5);
		layer_sort(_cube,6);
		
		break;
		
		case 1:
		
		_cube = ent_createlayer("s_ocean_sunset+6.tga",SKY | CUBE | SHOW,5);
		layer_sort(_cube,6);
		
		break;
	}
	*/
	camera.ambient = -75;

	ent_create("marker.mdl",nullvector,FollowPointer); // Create a mouse pointer.
	cam = ent_create("marker.mdl",vector(0,0,0),free_camera);
}

//void load_level(STRING *filef) {
	//	
	//	int i = _ObjectType;
	//	ENTITY *tmp;
	//	
	//	int tmpID, tmpobjtype;
	//	VECTOR tmpVector;
	//	
	//	vec_zero(tmpVector);
	//	
	//	// Use the same stupid core as save_level
	//	STRING *filef_original = str_create("#300");
	//	str_cpy(filef_original,filef);
	//	
	//	var hndl_sys = file_open_read(str_cat(filef,"_sys.txt"));
	//	str_cpy(filef,filef_original);
	//	
	//	var hndl_mdlobjs = file_open_read(str_cat(filef,"_ents.txt"));
	//	str_cpy(filef,filef_original);
	//	
	//	var hndl_lights = file_open_read(str_cat(filef,"_lights.txt"));
	//	str_cpy(filef,filef_original);
	//	
	//	var hndl_parts = file_open_read(str_cat(filef,"_parts.txt"));
	//	str_cpy(filef,filef_original);
	//	
	//	var hndl_snds = file_open_read(str_cat(filef,"_snds.txt"));
	//	str_cpy(filef,filef_original);
	//	
	//	var hndl_terraindata = file_open_read(str_cat(filef,"_tdata.txt"));
	//	str_cpy(filef,filef_original);
	//	
	//	var hndl_nodedata = file_open_read(str_cat(filef,"_ndata.txt"));
	//	str_cpy(filef,filef_original);
	//	
	//	var hndl_garbage = file_open_read(str_cat(filef,"_trash.txt"));
	//	str_cpy(filef,filef_original);
	//	//////////////////////////////////////////////////////////////
	//	
	//	level_load("dry.wmb");
	//	
	//	// System
	//	camera.x = file_var_read(hndl_sys);
	//	camera.y = file_var_read(hndl_sys);
	//	camera.z = file_var_read(hndl_sys);
	//	camera.pan = file_var_read(hndl_sys);
	//	camera.tilt = file_var_read(hndl_sys);
	//	camera.roll = file_var_read(hndl_sys);
	//	camera.aspect = file_var_read(hndl_sys);
	//	camera.arc = file_var_read(hndl_sys);
	//	camera.ambient = file_var_read(hndl_sys);
	//	sun_light = file_var_read(hndl_sys);
	//	sun_angle.pan = file_var_read(hndl_sys);
	//	sun_angle.tilt = file_var_read(hndl_sys);
	//	sun_color.blue = file_var_read(hndl_sys);
	//	sun_color.green = file_var_read(hndl_sys);
	//	sun_color.red = file_var_read(hndl_sys);
	//	fog_color = file_var_read(hndl_sys);
	//	d3d_fogcolor1.red = file_var_read(hndl_sys);
	//	d3d_fogcolor1.green = file_var_read(hndl_sys);
	//	d3d_fogcolor1.blue = file_var_read(hndl_sys);
	//	d3d_fogcolor2.red = file_var_read(hndl_sys);
	//	d3d_fogcolor2.green = file_var_read(hndl_sys);
	//	d3d_fogcolor2.blue = file_var_read(hndl_sys);
	//	d3d_fogcolor3.red = file_var_read(hndl_sys);
	//	d3d_fogcolor3.green = file_var_read(hndl_sys);
	//	d3d_fogcolor3.blue = file_var_read(hndl_sys);
	//	d3d_fogcolor4.red = file_var_read(hndl_sys);
	//	d3d_fogcolor4.green = file_var_read(hndl_sys);
	//	d3d_fogcolor4.blue = file_var_read(hndl_sys);
	//	camera.fog_start = file_var_read(hndl_sys);
	//	camera.fog_end = file_var_read(hndl_sys);
	//	skCube = file_var_read(hndl_sys);
	//	
	//	file_close(hndl_sys);
	//	
	//	// filef_ents.txt
	//	var j = num_mdlobjs;
	//	
	//	tmpID = file_var_read(hndl_mdlobjs);
	//	tmpobjtype = file_var_read(hndl_mdlobjs);
	//	
	//	tmpVector.x = file_var_read(hndl_mdlobjs);
	//	tmpVector.y = file_var_read(hndl_mdlobjs);
	//	tmpVector.z = file_var_read(hndl_mdlobjs);
	//	
	//	tmp = ent_create(_str(mdlobjs_table_ptr[tmpID]),tmpVector,NULL);
	//	
	//	tmp.ObjectID = num_mdlobjs;
	//	tmp.ObjectType = file_var_read(hndl_mdlobjs);
	//	
	//	camera.ambient = 50;
	//	
	//	ent_create("marker.mdl",nullvector,FollowPointer); // Create a mouse pointer.
	//	cam = ent_create("marker.mdl",vector(0,0,0),free_camera);
	//	
//}

/*
--------------------------------------------------
int SaveGameToSlot(var slot)

Desc: Saves the current state of the world. Consists 
of two stages: SV_ALL - SV_INFO - SV_BMAPS and SV_INFO + SV_BMAPS. 
There will be two seperate .sav files, one contains each stage's saved data.
They're loaded separately, too.

Returns: -1 if a stage fails.
--------------------------------------------------
*/
int SaveGameToSlot(var slot) {
	
	var i, j;
	
	BOOL t;
	
	slot-=2;
	
	GGUIHide();
	
	reset(panSaveGame,SHOW);
	
	if(is(panLoadGame,SHOW)) {
		
		t++;
		reset(panLoadGame,SHOW);
		
	}
	else t = 0;
	
	wait(2);
	
	bmap_for_screen(ptr_for_handle(save_array[slot]),1,1);
	
	i = game_save(pref_savebmaps,0,SV_INFO + SV_BMAPS);
	j = game_save(pref_savegames,slot,SV_ALL - SV_INFO - SV_BMAPS);
	
	if(!i || !j) return -1;
	
	GGUIShow();
	set(panSaveGame,SHOW);
	if(t) set(panLoadGame,SHOW);
	
}

/*
--------------------------------------------------
int LoadGameFromSlot(var slot)

Desc: Loads a game from slot.

Returns: -1 if operation fails.
--------------------------------------------------
*/
int LoadGameFromSlot(var slot) {
	
	var i;
	
	slot-=2; // 1 for array (count from 0), 1 for closebutton
	
	i = game_load(pref_savegames,slot);
	
	if(!i) return -1;
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
	
	if(KERNEL_IS_RUNNING) return -1;
	
	ConsoleText->pos_x = 2;
	ConsoleText->pos_y = screen_size.y/4;
	toggle(ConsoleText,SHOW);
	
	while(!KERNEL_IS_RUNNING) {
		
		inkey((ConsoleText->pstring)[1]);
		
		if (result == 13) { // [Enter]
			
			void* found = var_for_name((ConsoleText->pstring)[1]);
			if (!found) execute((ConsoleText->pstring)[1]);
			
		}
		
		if(result == 27 && LOAD_KERNEL) { // [Esc]
			
			str_cpy((ConsoleText->pstring)[1],"Loading kernel...");
			
			LoadKernel();
			wait_for(LoadKernel);
			
			LoopKernel();
			
			str_cpy((ConsoleText->pstring)[1],"Switching off console...");
			
			break;	
			
		}
		
		if(str_cmp((ConsoleText->pstring)[1],"exit")) {
			
			printf("exit triggered");
			
		}
		
		wait(1);
		
	}
	
	reset(ConsoleText,SHOW);
	
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
	
	KERNEL_IS_RUNNING = 0;
	
	// From GShowCredits().
	reset(panMMenu,SHOW);
	reset(panMMenu_exit,SHOW);
	reset(panNewGame,SHOW);
	
	level_load(NULL);
	vec_set(screen_color,vector(255,255,255));
	
	GGUIHide();
	
	Console();
	
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
	
	wait(1);
	
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

	// Initialization for loopix-project.com's MystyMood_Lite-C
	sky_curve = 2;
	sky_clip = -10;

	_ObjectType = 1;

	mouse_map = mouse;

	vec_zero(parted_temp_vec);
	vec_zero(parted_temp2_vec);

	// So that we can get access to the database.
	mdlobjs_table_ptr = mdlobjs_table;

	panHome.alpha = panProp.alpha = DEFAULT_ALPHA;

	// Initialize the databases and load them.
	LoadObjectDatabase();
	LoadSoundDatabase(); // Sound database doesn't require a pointer to access.
	LoadParticleDatabase(); // So does particle database.
	LoadSavedBMAPs();

	// Intialize and read custom materials' properties.
	int i;
	for(i = 0;i < 4;i++) mat_custom[i] = mtl_create();

	ReadMaterialDataFromFile(mat_custom[0],FILE_CUSTOM_MAT_1);
	ReadMaterialDataFromFile(mat_custom[1],FILE_CUSTOM_MAT_2);
	ReadMaterialDataFromFile(mat_custom[2],FILE_CUSTOM_MAT_3);
	ReadMaterialDataFromFile(mat_custom[3],FILE_CUSTOM_MAT_4);
	
	// If we want a video to be played...
	//		PlayVideo(100);
	//		wait_for(PlayVideo);

	// Intialize and load the GUI system.
	GGUIInit();
	wait_for(GGUIInit);
	
	/*
	// Load a blank level.
	LoadNewLevel();
	
	//	LoadMystymood(1,1);

	//	def_move();
	*/
	
	GLoadMainMenu();
	
	mouse_mode = 4;
	
	KERNEL_IS_RUNNING = 1;
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
	
	if(!KERNEL_IS_RUNNING) return;
	
	while(KERNEL_IS_RUNNING) {
		
		if(IN_GAME) 
		{
			
			// Prevent the cursor from going outside the level border
			if(!temp_pos.x) temp_pos.x = level_ent.max_x;
			if(!temp_pos.y) temp_pos.y = level_ent.max_y;
			if(!temp_pos.z) temp_pos.z = level_ent.max_z;
			
			
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
			if(key_esc && !from_test_play) { // If ESC is pressed and we're not pressing ESC while we were in testing mode.
				
				while(key_esc) wait(1);
				GHomeShow();
				
			}
			
			if(key_t) 
			{
				while(key_t) wait(1);
				num_mdlobjs++;
			}
			
			if(key_y) {
				while(key_y) wait(1);
				num_mdlobjs--;
			}
			
			if(key_r) {
				
				while(key_r) wait(1);
				you = ent_next(NULL); // Point to the first entity in the list
				while(you) {
					
					ptr_remove(you);
					you = ent_next(you);
					
				}
				
				ent_create("marker.mdl",nullvector,FollowPointer); // Create a mouse pointer.
				cam = ent_create("marker.mdl",vector(0,0,0),free_camera);
				
			}
			
			if(mouse_left) 
			{
				if(_ObjectType == Terrain) return;
				
				while(mouse_left) wait(1);
				
				if(!mouse_panel)
				{
					
					if(!mouse_ent) CreateObject();
					
					else
					{
						if(select)
						{
							
							if(select.ObjectType == Light) GLightWindowHide();
							if(select.ObjectType == NormalObject) GPropertiesWindowHide();
							if(select.ObjectType == Sound) GSoundWindowHide();
							if(select.ObjectType == Particle) GParticleWindowHide();
							
							select.material = mat_temp;
							select = NULL;
						}
						
						select = mouse_ent;
						
						mat_temp = select.material; // Luc nay select da duoc xac dinh nen ta cu thoai mai
						select.material = mat_select;
						
						if(select.ObjectType == Light) GLightWindowShow();
						else GLightWindowHide();
						
						if(select.ObjectType == NormalObject) GPropertiesWindowShow();
						else GPropertiesWindowHide();
						
						if(select.ObjectType == Sound) GSoundWindowShow();
						else GSoundWindowHide();
						
						if(select.ObjectType == Particle) GParticleWindowShow();
						else GParticleWindowHide();
						
						PassObjectPropertiesToGUI(select);
						
					}
					
					/*
					else
					{
						if(select)
						{
							if(mat_temp) select.material = mat_temp;
							else select.material = NULL;
							
							if(select.ObjectType == Light) GLightWindowHide();						
							if(select.ObjectType == NormalObject) GPropertiesWindowHide();
							if(select.ObjectType == Sound) GSoundWindowHide();
							if(select.ObjectType == Particle) GParticleWindowHide();
							
							select = NULL;
						}
						
						GLightWindowHide();	
						GParticleWindowHide();
						GPropertiesWindowHide();
						GSoundWindowHide();
						
						select = NULL;
					}
					*/
					
					wait(1);
					
				}		
				
			}
			
			if(PLAYTESTING && play_as_fp) {
				
				wait(-1);
				reset(panCAMRecorderREC,SHOW);
				wait(-1);
				set(panCAMRecorderREC,SHOW);
				
			}
			
		}
		wait(1);
	}

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

	// Read and setup video settings prior to executing other functions.
	ConfigFileRead(FILE_CONFIG);
	
	on_bksp = TakeScreenshot;
	on_exit = ExitEvent;

	video_window(NULL,NULL,0,"craftbox 0.8 Pre-Alpha 4.1");
	
	mouse_range = 500000;
	random_seed(0); // e.g. random light generators.
	terrain_chunk = 0;
	fps_max = 70;

	while(1) {
		
		// These keys are combined together with the Alt key.
		if(key_alt) {
			
			if(key_f4) {
				
				while(key_f4) wait(1);
				ExitEvent();
				
			}
			
		}
		
		if(KERNEL_IS_RUNNING) {
			
			if(is(anms,SHOW)) anms.pos_x = panObj_Main.pos_x;
			if(is(arch,SHOW)) arch.pos_x = panObj_Main.pos_x;
			if(is(blands,SHOW)) blands.pos_x = panObj_Main.pos_x;
			if(is(chars,SHOW)) chars.pos_x = panObj_Main.pos_x;
			if(is(etc,SHOW)) etc.pos_x = panObj_Main.pos_x;
			if(is(food,SHOW)) food.pos_x = panObj_Main.pos_x;
			if(is(machs,SHOW)) machs.pos_x = panObj_Main.pos_x;
			if(is(plants,SHOW)) plants.pos_x = panObj_Main.pos_x;
			if(is(tportts,SHOW)) tportts.pos_x = panObj_Main.pos_x;
			
			if(select) {
				
				if(key_del) {
					
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
					select.LightMode = disco;
					
				}
				
				if(button_state(panLight,3,-1)) {
					
					button_state(panLight,2,-1);
					select.LightMode = flick;
					
				}
				
				if(button_state(panLight,2,-1) && button_state(panLight,3,-1)) {
					
					button_state(panLight,2,0);
					button_state(panLight,3,0);
					select.LightMode = 0;
					
				}
				
				// panProp
				// select.material now holds mat_select
				// so we must pass something else
				
			}
			
			else { // If select isn't selected.
				
				GPropertiesWindowHide(); // GPropertiesWindowHide() somehow got stuck
				GSoundWindowHide();
				GLightWindowHide();
				GParticleWindowHide();
				
			}
			
			if(SliderLimit<0) SliderLimit=0; // prevent unexpected situations
			if(SliderLimit>100) SliderLimit=100;
			
			panObj_Main.pos_x = (SliderLimit * (-bmap_width(panObj_Main.bmap) + screen_size.x))/100;
			panObj_Part_Main.pos_x = (SliderLimit * (-bmap_width(panObj_Part_Main.bmap) + screen_size.x))/100;
			panObj_Snd_Main.pos_x = (SliderLimit * (-bmap_width(panObj_Snd_Main.bmap) + screen_size.x))/100;
			
			if(panObj_Main.pos_x > 0) panObj_Main.pos_x = 0;
			if(panObj_Main.pos_x < -bmap_width(panObj_Main.bmap) + screen_size.x) {
				
				panObj_Main.pos_x = -bmap_width(panObj_Main.bmap) + screen_size.x;
				
			}
			
			if(panObj_Part_Main.pos_x > 0) panObj_Part_Main.pos_x = 0;
			if(panObj_Part_Main.pos_x < -bmap_width(panObj_Part_Main.bmap) + screen_size.x) {
				
				panObj_Part_Main.pos_x = -bmap_width(panObj_Part_Main.bmap) + screen_size.x;
				
			}
			
			if(panObj_Snd_Main.pos_x > 0) panObj_Snd_Main.pos_x = 0;
			if(panObj_Snd_Main.pos_x < -bmap_width(panObj_Snd_Main.bmap) + screen_size.x) {
				
				panObj_Snd_Main.pos_x = -bmap_width(panObj_Snd_Main.bmap) + screen_size.x;
				
			}
		}	
		wait(1);
		
	}

}

////////////////////////////////////////////////////////////
// This is the camera controller I found when I was tweaking Mystymood.
// 5.7.2013 : This camera is good, but I have to partly rewrite it
// because...well, I won't explain, find out for yourself.
// This code won't be checked against PLAYTESTING because
// it will be killed prior to set PLAYTESTING to 1.
// and restored later when PLAYTESTING has been set to 0.
////////////////////////////////////////////////////////////
VECTOR *camera_force = { z = 0; }

void free_camera()
{
	var rotatespeed = 5;
	var speed = 40;

	set(my, INVISIBLE | POLYGON);

	vec_set(camera.x,my.x);
	vec_set(camera.pan,my.pan);
	vec_set(camera.tilt,my.tilt);

	while(1)
	{	
		camera_force.x = (key_w - key_s)*speed*time_step;
		camera_force.y = (key_a - key_d)*speed*time_step;
		
		c_move(my,camera_force,nullvector,GLIDE+IGNORE_PASSABLE+IGNORE_PASSENTS+IGNORE_PUSH);
		vec_set(camera.x,vector(my.x,my.y,my.z+15));
		
		camera.tilt += rotatespeed * mouse_right*mouse_force.y * time_step;
		camera.pan += rotatespeed * mouse_right*-mouse_force.x * time_step;
		
		vec_set(my.tilt,camera.tilt);
		vec_set(my.pan,camera.pan);
		
		wait(1);
	}
}
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Debug & statistics
////////////////////////////////////////////////////////////
PANEL *debug = {
	layer = 3;

	digits(0,0,99,"arial#25b",1,num_mdlobjs);

	flags = SHOW;
}

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

void flare_init(ENTITY *flare_ent)
{
	my = flare_ent;
	my.flags2 &= ~SHOW;
	my.flags |= (BRIGHT|PASSABLE|TRANSLUCENT);
}

// Desc: places a flare at temp.x/temp.y deviations from screen center
void flare_place(ENTITY *flare_ent)
{
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

void LoadMystymoodLensflare()
{

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
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
////MystyMood sky/sun/weather template...works without shader, uses 3dgs sky entitys!
////
////Note: All sky/weather values must be adjusted in this script...exept from the mysty_mood trigger values 
////that can be adjusted for each trigger dummy via the behaviour panel in WED.
////
////Jun 07 by www.loopix-project.com
////Nov 07 Lite-C conversion by Alexis Rozhkov aka Shadow
/////////////////////////////////////////////////////////////

void func_fade_colors(var *col_target, var *col1, var *col2)
{
	var i = 0;
	if(i < 100)
	{
		i = minv(i + fog_fade_speed*time_step, 100);
		vec_lerp(col_target, col1, col2, i/100);
	}
}

//start rain/snow particle effects////

void func_particle_seed_infinity(PARTICLE *p)
{

	vec_set(p.x,vector(cycle(p.x,camera.x-particle_seedbox.x,camera.x+particle_seedbox.x),
	cycle(p.y,camera.y-particle_seedbox.y,camera.y+particle_seedbox.y),
	cycle(p.z,camera.z-particle_seedbox.z,camera.z+particle_seedbox.z)));

	if(p.z<camera.z-100) p.lifespan = 0;

}

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
////end rain/snow particle setup////

////start thunder lighning////
void func_fade_lightning(PARTICLE *p)  { p.lifespan = 0; }

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

void func_particle_segment()
{
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
}

void func_particle_segment()
{
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
}

void func_increase_brightness()
{
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
}

////end thunder lightning////

void toggle_weather()//just for testing
{
	weather_state += 1;
	if(weather_state > 2) weather_state = 0;
}

void good_weather()  { weather_state = 0; }

void weather_change() {

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

	while(1)
	{
		
		random_seed(0);
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
				snd_handle_thunder = snd_play(thunder1_wav, 100, 0);
				rand_count_state = 1;
			}
			if(rand_count == 2 && rand_count_state != 2)
			{
				snd_handle_thunder = snd_play(thunder2_wav, 100, 0);
				rand_count_state = 2;
			}
			if(rand_count == 3 && rand_count_state != 3)
			{
				snd_handle_thunder = snd_play(thunder3_wav, 100, 0);
				rand_count_state = 3;	
			}
			if(rand_count == 4 && rand_count_state != 4)
			{
				snd_handle_thunder = snd_play(thunder4_wav, 100, 0);
				rand_count_state = 4;	
			}
			if(rand_count == 5 && rand_count_state != 5)
			{
				snd_handle_thunder = snd_play(thunder5_wav, 100, 0);
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
}

/*** LoadMystymood(BOOL on, BOOL load_lens) 

Set on = 1, load mystymood
Set load_lens = 1, load lens flare

***/
void LoadMystymood(BOOL _on, BOOL load_lens)
{
	
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

	if(step>=2) return;

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
	sky_sun.flags2 |= SHOW;
	sky_suncorona.flags2 |= SHOW;
	sky_sunshine.flags2 |= SHOW;
	sky_night.flags2 |= SHOW;
	sky_moon.flags2 |= SHOW;

	VECTOR temp;

	on_space = toggle_weather;
	on_alt = good_weather;

	weather_change();

	sky_sun.scale_x = sun_scale_x;
	sky_sun.scale_y = sun_scale_y;

	fog_color = 1;

	camera.fog_start = land_fog_near;//-50;
	camera.fog_end = land_fog_far;//300;

	vec_set(d3d_fogcolor1,fog_day);//set the default day fog-color 

	mystymood_active = 1;

	while(mystymood_active) {
		
		vec_set(sun_color.blue,vector(d3d_fogcolor1.blue*sun_col_fac,d3d_fogcolor1.green*sun_col_fac,d3d_fogcolor1.red*sun_col_fac));
		vec_set(sky_color.blue,d3d_fogcolor1.blue);	
		vec_set(sky_horizon.blue,d3d_fogcolor1.blue);
		
		if(weather_state == 0 && trigg_active_id < 0) {
			
			if(!dynamic_day_night) func_fade_colors(d3d_fogcolor1,current_color,fog_dynamic_day_night_off);
			
			if(camera.fog_start>land_fog_near) camera.fog_start -= weather_fade_speed*time_step;
			else camera.fog_start += weather_fade_speed*time_step;
			
			if(camera.fog_end>land_fog_far) camera.fog_end -= weather_fade_speed*time_step;
			else camera.fog_end += weather_fade_speed*time_step;
			
		}	
		
		vec_set(current_color,d3d_fogcolor1);
		
		vec_set(temp,sun_pos); 
		vec_set(sky_sun.x,temp);  // copy the sun_pos location
		vec_sub(temp,camera.x); // direction vector from camera to our sun_pos
		vec_normalize(temp,land_fog_far-sun_dist_minus); // chop our direction vector to a set distance	
		
		vec_set(sky_sun.x,temp);
		
		if(use_moon) {
			
			vec_set(temp,sky_sun.x); 
			vec_inverse(temp);
			vec_set(sky_moon.x,temp);  // copy the sun_pos location
		}
		
		if(dynamic_day_night) {
			
			if(sun_angle.pan > 230 && sun_angle.pan < 360) {sun_angle.pan += 0.01*time_speed_night*time_step;}
			else{sun_angle.pan += 0.01*time_speed*time_step;}
			
			sun_angle.pan %= 360;
			sun_angle.tilt = fsin(sun_angle.pan, max_zenith);
			
			//sun "grows" at low azimut
			if(sky_sun.z<sun_grow_z) {
				
				if(sky_sun.scale_x<sun_scale_x+1 && sky_sun.scale_y<sun_scale_y+1) {
					
					sky_sun.scale_x += 0.01*time_step*time_speed/10;
					sky_sun.scale_y += 0.01*time_step*time_speed/10;
					
				}	
				
			}
			
			else {
				
				if(sky_sun.scale_x>sun_scale_x && sky_sun.scale_y>sun_scale_y) {
					
					sky_sun.scale_x -= 0.01*time_step*time_speed/10;
					sky_sun.scale_y -= 0.01*time_step*time_speed/10;
					
				}
			}
		}
		
		else {
			
			sun_angle.pan = sun_azimuth;
			sun_angle.tilt = sun_elevation;
			
		}
		
		if(sun_angle.pan > 0 && sun_angle.pan < 40) {
			
			if (sky_cloud1.alpha < 80) {sky_cloud1.alpha += sky_fade_speed*time_step*time_speed;} 
			if (sky_cloud2.alpha < 60) {sky_cloud2.alpha += sky_fade_speed*time_step*time_speed;}
			if (sky_day.alpha < 60) {sky_day.alpha += sky_fade_speed*time_step*time_speed;}
			if (sky_night.alpha > 1) {sky_night.alpha -= sky_fade_speed*time_step*time_speed;}	
			
		}
		
		if(sun_angle.pan > 10 && sun_angle.pan < 160) func_fade_colors(d3d_fogcolor1,current_color,fog_day);
		
		if(sun_angle.pan > 40 && sun_angle.pan < 160) {
			
			sky_cloud1.alpha = 80;
			sky_cloud2.alpha = 60;
			sky_day.alpha = 60;
			sky_night.alpha = 1;
			
		}
		
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
			
			if(weather_state>0) func_fade_colors(d3d_fogcolor1,current_color,fog_weather_night);
			
		}
		
		else {
			
			if(weather_state>0) func_fade_colors(d3d_fogcolor1,current_color,fog_weather_day);
			
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
}

void act_mystymood_trigg_label1()
{
	weather_fader = 1;//reset this var

	weather_state = my.skill70;
	rain_random_move_on = my.skill71;
	rain_random_move = my.skill72;
	rain_wind_x = my.skill73;
	rain_wind_y = my.skill74;
	rain_fallspeed = my.skill75;
	disable_lightning_thunder = my.skill76;
	snow_random_move_on = my.skill77;
	snow_random_move = my.skill78;
	snow_wind_x = my.skill79;
	snow_wind_y = my.skill80;
	snow_fallspeed = my.skill81;
	weather_fade_speed = my.skill82;

	act_mystymood_trigg();
}

////////////////////////////////////////////////////////////
// This function will set up and manage the playground.
////////////////////////////////////////////////////////////
void LoadPlayground() {

	if(select) {
		
		// Deselect any selected entity first
		if(select.ObjectType == Light) GLightWindowHide();
		if(select.ObjectType == NormalObject) GPropertiesWindowHide();
		if(select.ObjectType == Sound) GSoundWindowHide();
		if(select.ObjectType == Particle) GParticleWindowHide();
		
		select.material = mat_temp;
		select = NULL;
		
	}

	/***

	This code will scan through all available entities

	***/
	you = ent_next(NULL);
	while(you) {
		
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

	mouse_mode = 0;

	ent_remove(fpsf_marker);
	ent_remove(cam);

	GGUIHide();

	PLAYTESTING = 1;

	if(play_as_fp) {
		
		set(panCAMRecorder,SHOW);
		set(panCAMRecorder_digits,SHOW);
		
	}

	while(PLAYTESTING) {
		
		temp_cam += 3 * time_step;
		camera.z += .5 * sin(temp_cam);
		
		if(key_esc) {
			
			from_test_play = 1;
			
			while(key_esc) wait(1);
			
			PLAYTESTING = 0;
			from_test_play = 0; // reset
			
		}
		
		wait(1);
		
	}

	if(play_as_fp) {
		
		reset(panCAMRecorder,SHOW);
		reset(panCAMRecorder_digits,SHOW);
		
	}
	else { //play_as_bike
		
		wait(1);
		
	}

	mouse_mode = 4;
	ent_create("marker.mdl",nullvector,FollowPointer); // Create a mouse pointer.
	cam = ent_create("marker.mdl",vector(0,0,0),free_camera);

	GGUIShow();
	//	def_move();

	/***

	Scan through all available entities in the level
	and set them to their original state.

	***/
	you = ent_next(NULL);

	while(you) {
		
		if(you.ObjectType == Light || you.ObjectType == Particle || you.ObjectType == Sound)
		reset(you,INVISIBLE);
		
		you = ent_next(you);
		
	}
}

void LoadNewLevelFromWindow() {

	// Redirect to another function because we're in main menu now.
	if(launch_newgame_from_main) {
		
		LoadNewLevelFromMenuWindow();
		return;
		
	}

	ent_remove(cam);

	LoadNewLevel();

	// Left
	if(button_state(panNewGame,2,-1)) {
		
		LoadMystymood(0,0);
		
		if(button_state(panNewGame,4,-1)) {
			
			fog_color = 1;
			d3d_fogcolor1.red = v_fogr;
			d3d_fogcolor1.green = v_fogg;
			d3d_fogcolor1.blue = v_fogb;
			
			camera.fog_start = 10;
			camera.fog_end = (FOG_END_LIM - v_fogdensity) + 2 * camera.fog_start ; 
			
		}
		
		else fog_color = 0;
		
		return ;
		
	}

	// Right
	if(button_state(panNewGame,3,-1)) {
		
		LoadMystymood(0,0);
		
		wait(1.5);
		
		// Mystymood w/ lensflare
		LoadMystymood(1,button_state(panNewGame,5,-1));
		
		// Thunder
		if(button_state(panNewGame,6,-1)) disable_lightning_thunder = 1;
		else disable_lightning_thunder = 0;
		
		// Use moon
		if(button_state(panNewGame,7,-1)) use_moon = 1;
		else use_moon = 0;
		
		moon_scale_fac = _moon_scale_fac;
		time_speed_night = _time_speed_night;
		night_sky_scale_x = _night_sky_scale_x;
		night_sky_speed_x = _night_sky_speed_x;
		
		return;
		
	}

}

void LoadNewLevelFromMenuWindow() {
	
	reset(panMMenu,SHOW);
	reset(panMMenu_exit,SHOW);
	reset(panNewGame,SHOW);
	//	
	//	GGUIInit();
	//	wait_for(GGUIInit);

	GGUIShow();

	LoadNewLevel();

	launch_newgame_from_main = 0;
	
	IN_GAME = 1;

	// Left
	if(button_state(panNewGame,2,-1)) {
		
		LoadMystymood(0,0);
		
		if(button_state(panNewGame,4,-1)) {
			
			fog_color = 1;
			d3d_fogcolor1.red = v_fogr;
			d3d_fogcolor1.green = v_fogg;
			d3d_fogcolor1.blue = v_fogb;
			
			camera.fog_start = 10;
			camera.fog_end = (FOG_END_LIM - v_fogdensity) + 2 * camera.fog_start ; 
			
		}
		
		else fog_color = 0;
		
		return ;
		
	}

	// Right
	if(button_state(panNewGame,3,-1)) {
		
		LoadMystymood(0,0);
		
		wait(1.5);
		
		// Mystymood w/ lensflare
		LoadMystymood(1,button_state(panNewGame,5,-1));
		
		// Thunder
		if(button_state(panNewGame,6,-1)) disable_lightning_thunder = 1;
		else disable_lightning_thunder = 0;
		
		// Use moon
		if(button_state(panNewGame,7,-1)) use_moon = 1;
		else use_moon = 0;
		
		moon_scale_fac = _moon_scale_fac;
		time_speed_night = _time_speed_night;
		night_sky_scale_x = _night_sky_scale_x;
		night_sky_speed_x = _night_sky_speed_x;
		
		return;
		
	}

}

void load_ent_anms(var id) {

	num_mdlobjs=id--;

	reset(panObj_Main,SHOW);
	reset(panObj_Subbar,SHOW);
	reset(panObj_Subbar_slider,SHOW);
	reset(panObj_Main_X,SHOW);

	reset(anms,SHOW);

	GGUIShow();

	SliderLimit = 0;

}

void load_ent_arch(var id) {

	error("load_ent_arch");

}

void load_ent_blands(var id) {

	error("load_ent_blands");

}

void load_ent_chars(var id) {

	error("load_ent_chars");

}

void load_ent_etc(var id) {

	error("load_ent_etc");

}

void load_ent_food(var id) {

	error("load_ent_food");

}

void load_ent_machs(var id) {

	error("load_ent_machs");

}

void load_ent_plants(var id) {

	error("load_ent_plants");

}

void load_ent_tportts(var id) {

	error("load_ent_tportts");

}