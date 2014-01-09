/*
--------------------------------------------------
Craftbox_System_Clipboard.c

Functions for working with the clipboard, for example 
passing to/from object/clipboard.

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
	
	int i = 0; for(; i < MAX_PUBLIC_SKILLS + MAX_PRIVATE_SKILLS ; i++) of._skill[i] = o.skill[i];

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
		
		switch ( o.ObjectType ) {
			
			case ObjectAnimal: str_cpy( of.name, PATH_OBJECTS_ANMS ); break;
			case ObjectArchitecture: str_cpy( of.name, PATH_OBJECTS_ARCHS ); break;
			case ObjectCharacter: str_cpy( of.name, PATH_OBJECTS_CHARS ); break;
			case ObjectEveryday: str_cpy( of.name, PATH_OBJECTS_ETC ); break;
			case ObjectFood: str_cpy( of.name, PATH_OBJECTS_FOOD ); break;
			case ObjectMachine: str_cpy( of.name, PATH_OBJECTS_MACHS); break;
			case ObjectPlant: str_cpy(of.name,PATH_OBJECTS_PLANTS); break;
			case ObjectTransport: str_cpy(of.name, PATH_OBJECTS_TPORTTS); break;
			
		}
		
		str_cat( of.name, o->type );		
		
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
		//		str_cpy(of.name, o.SoundFileName );
		
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
		of._ParticleID = o.ParticleID;
		
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
		
		str_cpy(of.name, PATH_SPRITES);
		str_cat(of.name, o->type );
		
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