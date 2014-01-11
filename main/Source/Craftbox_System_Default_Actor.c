/*
--------------------------------------------------
Craftbox_System_Default_Actor.c

Worker code for created entities, partly.
Only for basic entities like light, particles, sprites, and such.

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
	`
	my._BEING_MANIPULATED = 0;
	my._NODE_HEARTBEAT = 0;
	//	
	my.emask |= (ENABLE_SCAN /*| ENABLE_CLICK*/);
	//	my.event = ObjectManipulationCore;
	//	my.skin = random(5);
	//	
	
	/*
	while(my) {
		
		wait(1);
		
	}
	*/
	
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
	
	//	my->SoundFileName = str_create("#300"); // resurrect this string
	//	str_cpy(my->SoundFileName,TEMPSTR); // at this moment TEMPSTR is still valid for this session
	
	ent_playloop(my,snd_create(TEMPSTR),VOL_EFFECTS);
	
	my._BEING_MANIPULATED = 0;
	
	my.emask |= ENABLE_CLICK;
	my.event = ObjectManipulationCore;
	
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
	
	my._BEING_MANIPULATED = 0;
	
	my.emask |= ENABLE_CLICK;
	my.event = ObjectManipulationCore;
	
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

int GenerateWaterPlane() {
	
	
}