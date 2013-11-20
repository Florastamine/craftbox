/*
--------------------------------------------------
CBoxAct.c

This is the place where magic happens. Walking people,
flying birds,...anything that will be assigned to non-static
objects in the game.

TODO:
<+++



>+++

NOTES:
<+++



>+++
--------------------------------------------------
*/

#define HEALTH skill30

var cam_speed = 1; // initial speed
var dist_to_node;
var current_node = 1;
var angle_difference = 0;
var temp_angle;
var pos_node; // stores the position of the node

// (entity): grass model to be animated
void act_wgrass(ENTITY *);

//////////////////////////////////////////////////////////////

// (entity): target entity
// (var): u
// (var): v
void act_uvshift(ENTITY *, var, var);

//////////////////////////////////////////////////////////////

// (entity): target entity to be filled with water
void act_water(ENTITY *);

//////////////////////////////////////////////////////////////

// (entity): target entity
// (var): red
// (var): green
// (var): blue
// (var): light range
// (var): mode of rotation (implement later)
// (var): rotation speed

#define PAN 1
#define ROLL 3
#define CRAZY 7

void act_spotlight(ENTITY *, var, var, var, var, var, var);

//////////////////////////////////////////////////////////////

// (entity): give the target entity a shiny look with the fixed function envmap.
// plus translucent and alpha
void act_glass(ENTITY *);

//////////////////////////////////////////////////////////////

// (entity): random scale
void act_randscale(ENTITY *, var);

//////////////////////////////////////////////////////////////

// (entity): this entity will be surrounded by grass (for example the player)
// in that regular case: act_grassgenerator(player).

ENTITY *grass_tempent;

var number_of_bushes = 0; // counts the number of models that are placed in the level at a certain moment

STRING *grass1_mdl = "grass1.mdl";
STRING *grass2_mdl = "grass2.mdl";

#define GRASS_DENSITY 500
#define GRASS_SAMPLE 5 // Number of grass models to be sampled at a time

void place_grass();

void act_grassgenerator(ENTITY *);

//////////////////////////////////////////////////////////////

// (entity): this entity will be surrounded by fog.
// regular examples pointed out before in act_grassgenerator.

ENTITY *fog_tempent;

#define max_alpha skill1
#define max_fog 150

#define FOG_SAMPLE 4 // The same, fog samples

var cam_fog = 500; // needs to be a variable so it can get closer and further away to the camera as needed
VECTOR wind;

void autofog();

void act_foggenerator(ENTITY *);

//////////////////////////////////////////////////////////////

// (entity): entity to follow

ENTITY* target_crumb;

#define WALK_SPEED 15 // Walking speed of the AI
#define DISTANCE_AI_ENTITY 25 // Closest distance between the AI and follow_what (for example the player)
#define NODE_DISTANCE 150 // Distance between created nodes

void crumb_init();

void act_nodegenerator(ENTITY *);
void act_AI_follower(ENTITY *);

//////////////////////////////////////////////////////////////

// (entity): target entity
// (var): max alpha
void act_varalpha(ENTITY *, var);

//////////////////////////////////////////////////////////////

// (entity): target entity
// (var): change time
void act_varcolor(ENTITY *, var);

//////////////////////////////////////////////////////////////

// (entity): target entity
// (var): max
void act_varlight(ENTITY *, var);

//////////////////////////////////////////////////////////////

void act_AI_follower(ENTITY *follow_what) // this character follows the player using the breadcrumbs
{
	
	VECTOR temp;
	
	set (my, PASSABLE); 
	while ( follow_what )
	{
		// don't do anything if the follow_what is very close
		my.skill22 = 0;
		while (vec_dist (follow_what.x, my.x) < DISTANCE_AI_ENTITY)
		{
			my.skill22 += 4 * time_step; // 4 gives the "stand" animation speed
			ent_animate(my, "stand", my.skill22, ANM_CYCLE);
			wait (1);
		}
		// use small vertical angles here (30 degrees or so); don't allow the npc to detect crumbs at a top floor (or so)
		c_scan(my.x, my.pan, vector(360, 30, 1000), SCAN_ENTS | SCAN_LIMIT); // scan for crumbs that are placed up to 1000 quants
		if (you) // a crumb was detected?
		{
			target_crumb = you; // the closest crumb to the npc is set to "you" by c_scan
			// rotate the npc towards the crumb
			vec_set(temp, target_crumb.x);
			vec_sub(temp, my.x);
			vec_to_angle(my.pan, temp);
			// the npc looks at the target crumb now
			while (vec_dist (my.x, target_crumb.x) > 30) // the npc moves until it comes close to target_crumb
			{
				my.skill22 += 10 * time_step; // 5 gives the "walk" animation speed
				c_move(my, vector(WALK_SPEED * time_step, 0, 0), nullvector, IGNORE_PASSABLE | GLIDE);
				ent_animate(my, "walk", my.skill22, ANM_CYCLE);
				wait (1);
			}
			// the npc has come close to target_crumb here
			ent_remove(target_crumb); // so remove the current target_crumb and prepare for the following crumb
			
		}
		
		my.skill2 += WALK_SPEED * time_step;
		ent_animate(my,"stand",my.skill22,ANM_CYCLE);
		
		wait (1);
	}
}

void crumb_init()
{
	my.z += 15;
	set (my, PASSABLE); // player's movement code should ignore passable entities
	my.emask |= ENABLE_SCAN; // the crumb is sensitive to c_scan instructions
}


void act_nodegenerator(ENTITY *entity) {
	
	VECTOR player_pos1, player_pos2;
	
	var step = 1;
	
	while ( entity )
	{
		if( !PLAYTESTING ) wait(1);
		
		if (step == 0)
		{
			step = 1;
			vec_set(player_pos1.x, entity.x); // store the initial entity position
		}
		vec_set(player_pos2.x, entity.x); // store the initial entity position
		if (vec_dist (player_pos2.x, player_pos1.x) > NODE_DISTANCE) // create a breadcrumb every 50 quants
		{
			// allow player_pos1 to be set to a new value (approximately equal with the last player_pos2 value)
			step = 0; 
			ent_create("crumb.mdl", entity.x, crumb_init);
		}
		wait (1);
	}
}

void act_varalpha(ENTITY *entity, var max) {
	
	if(!is(entity,TRANSLUCENT) ) set(entity,TRANSLUCENT);
	
	max = abs(max);
	
	while( entity ) {
		
		entity->alpha = random(max);
		
		wait(1);
		
	}
	
}

void act_varcolor(ENTITY *entity, var time) {
	
	if(!is(entity,LIGHT)) set(entity, LIGHT);
	
	while( entity ) {
		
		entity.red = random(255);
		entity.green = random(255);
		entity.blue = random(255);
		
		wait( - abs(time) );
		
	}
	
}

void act_varlight(ENTITY *entity, var max) {
	
	max = abs(max);
	
	while( entity ) {
		
		entity.ambient = random(max);
		
		wait(1);
		
	}
	
}

void create_fog(int input, VECTOR *pos) {
	
	
	if(!input) return;
	
	switch(input) {
		
		case 0: ent_create("Dust_1.tga", pos, autofog);  break;
		case 1: ent_create("Dust_2.tga",pos,autofog); break;

	}
	
	wait(1); // prevent overhead
	
}

void set_alpha() 
{
	var fade_speed = 0.5;
	// fade model in
	my.alpha=0;
	my.max_alpha = integer(random(30));
	if(my.max_alpha < 10){ my.max_alpha = 15; }
	
	while(my.alpha < my.max_alpha)
	{
		my.alpha += fade_speed*time_step;
		wait(1);
	}
	my.alpha = my.max_alpha;
}

void fog_wind()
{
	while(1)
	{
		// new wind direction...
		vec_set(wind.x, vector((random(1) - .5)*1.5, (random(1) - .5)*1.5, random(1)*.4));
		wait(-5 + random(3));
	}
}

void move_fog()
{
	var roll_speed;
	var fade_distance = cam_fog+(cam_fog/6);
	var fog_speed = 20;
	
	roll_speed = random(2)-1; 
	
	while(me)
	{
		my.roll += roll_speed*time_step; //roll this sprite
		
		// update position globally
		c_move(my, nullvector, vector(random(fog_speed)*wind.x*time_step, random(fog_speed)*wind.y*time_step, 0), IGNORE_PASSABLE);
		
		// fade sprite when close to fog_tempent
		if(vec_dist(my.x, fog_tempent.x) < fade_distance) 
		{
			my.alpha = minv(my.max_alpha, vec_dist(fog_tempent.x, my.x) * my.max_alpha / fade_distance);
		}
		
		wait(1);
	}
}

void autofog()
{
	VECTOR cam_pos;
	var randint;
	
	vec_scale(my.scale_x, 0.8);
	set(my, PASSABLE | TRANSLUCENT | BRIGHT); // can add BRIGHT, but slows FPS down
	
	//fade in slowly
	set_alpha();
	move_fog();
	
	while(me)
	{
		if(my.alpha < my.max_alpha) { my.alpha += time_step; }
		
		vec_set(cam_pos, fog_tempent.x);
		cam_pos.z = my.z;
		
		if(vec_dist(my.x, cam_pos) >= cam_fog)
		{
			// fade the fog out
			while(my.alpha > 0) { my.alpha -= time_step; wait(1); }
			
			// set on new position at edge of fog distance
			vec_set(my.x, vector(cycle(my.x, fog_tempent.x - cam_fog, fog_tempent.x + cam_fog), cycle(my.y, fog_tempent.y - cam_fog, fog_tempent.y + cam_fog), fog_tempent.z - random(100) + random (200)));
		}
		
		wait(5);
	}
}

void act_foggenerator(ENTITY *entity)
{
	var fogcount;
	
	VECTOR pos_place;
	
	fog_tempent = entity;
	
	fog_wind(); // sets a random fog position every so often
	
	for(fogcount=0; fogcount<max_fog; fogcount++)
	{
		// set random position around entity
		vec_set(pos_place.x, vector(((entity.x - random(cam_fog)) + (entity.x + random(cam_fog))), ((entity.y - random(cam_fog)) + (entity.y + random(cam_fog))), ((entity.z - random(cam_fog/4)) + random(cam_fog/2))));
		//		vec_set(pos_place.x, nullvector);
		
		int i;
		for( i = 0; i < FOG_SAMPLE ; i++) create_fog(integer(random(FOG_SAMPLE)), pos_place);
		
	}
}

// Create grass based on ID
void create_grass(int input, VECTOR *pos) {
	
	if(!input) return;
	
	switch ( input ) {
		
		case 0:  ent_create (grass1_mdl, pos, place_grass); break;
		case 1: ent_create (grass2_mdl, pos, place_grass); break;
		case 2: ent_create ("grass3.mdl", pos, place_grass); break;
		
	}
	
	wait(1);
	
}

void act_grassgenerator(ENTITY *surround) {
	
	VECTOR surround_position1, surround_position2, temp;
	
	grass_tempent = surround;
	
	while ( surround )
	{
		vec_set (temp.x, surround.x);
		temp.x += 500 - random(1000);
		vec_set (temp.y, surround.y);
		temp.y += 500 - random(1000);
		temp.z = surround.z + 200;
		if ((abs(temp.x - surround.x) > 300) && (abs(temp.x - surround.x) > 300))
		{
			
			if (((surround_position1.x != surround_position2.x) && (number_of_bushes < GRASS_DENSITY)) || (total_frames < 300))
			{
				
				int i, random_sample;
				for(i = 0; i < GRASS_SAMPLE;i++) create_grass( integer(random( GRASS_SAMPLE )) ,temp.x );
				
			}
			
		}
		vec_set (surround_position1.x, surround.x);
		wait (1);
		vec_set (surround_position2.x, surround.x);
	}
	
}

void act_randscale(ENTITY *entity, var max) {
	
	max = abs(max);
	
	while(entity) {
		
		Scale(entity,max);
		
		wait(1);
		
	}
	
}

void act_glass(ENTITY *entity ) {
	
	set(entity,TRANSLUCENT);
	entity->alpha = 50;
	
	MATERIAL *cubemap = mtl_create();
	while(proc_status( mtl_create ) ) wait(1);
	
	cubemap->skin1 = bmap_create(SKYSTR);
	cubemap->event = transenv_event;
	cubemap->flags |= ENABLE_VIEW;
	
	effect_load(cubemap,"./src/fx/Envmapping.fx");
	
	bmap_to_cubemap(bmap_to_mipmap(cubemap.skin1));
	
	entity.material = cubemap;
	
}

void place_grass()
{
	VECTOR temp;
	
	number_of_bushes += 1;
	set(my,TRANSLUCENT | PASSABLE);
	my.pan = random(360);
	vec_set (temp, my.x); 
	Scale(my, random(3) );
	temp.z -= 3000;
	my.z -= c_trace (my.x, temp, IGNORE_ME | IGNORE_SPRITES | IGNORE_MODELS | USE_BOX ); // place the grass model on the ground
	
	while (vec_dist(grass_tempent.x, my.x) < 1000)
	{
		my.alpha = minv (100, (10000 / (vec_dist(grass_tempent.x, my.x))));
		wait (1);
	}
	
	ent_remove (my);
	
	number_of_bushes -= 1;
}

void act_spotlight(ENTITY *entity, var r, var g, var b, var lrange, var mode, var speed) {
	
	entity.ambient = 100;
	
	set(entity,SPOTLIGHT);
	
	entity.lightrange = abs(lrange);
	vec_set(entity.red,vector( abs(b), abs(g), abs(r) ));
	
	speed = abs(speed);
	
	while ( entity ) {
		
		//		my.pan += random(speed) * time_step;
		//		my.tilt += random(speed) * time_step;
		//		my.roll += random(speed) * time_step;
		
		wait(1);
		
	}
	
}

void act_water(ENTITY *entity) {
	
	FFE_Water.matrix11 = floatv(10);
	FFE_Water.matrix22 = floatv(5);

	bmap_to_mipmap(FFE_Water.skin1);
	bmap_to_mipmap(FFE_Water.skin2);

	entity.material = FFE_Water;
	
}

void act_uvshift(ENTITY *entity, var _u, var _v) {
	
	_u = abs(_u);
	_v = abs(_v);
	
	while(1) {
		
		entity.u += _u * time_step;
		entity.v += _v * time_step;
		
		wait(1);
		
	}
	
}


void act_wgrass(ENTITY *entity) {
	
	Scale(entity, 0.7 + random(2) / 3);
	var grass_angles;

	while (1)
	{
		grass_angles += random(10) * time_step; // allow the grass to weave
		entity.roll += 0.02 * sin(grass_angles);

		wait (1);

	}
	
}

action general_action() {
	
	set(my,POLYGON  | PASSABLE | LIGHT);
	
	act_AI_follower(player);
	act_spotlight(me,127,127,127,3000,0,5);
	
	//   act_spotlight(me);
	//	act_glass(me);
	//	act_grassgenerator(me);
	//	act_foggenerator(me);
	//	act_randscale(me,5,7);
	
	while(my) {
		
		if(PLAYTESTING) {
			
			my.x += 15 * (key_y-key_u);
			
			wait(1);
			//			act_glass(me);
			
		}
		
		wait(1);
		
	}
	
}

////////////////////////////////////////////////////////////
// A patroller and a node.
////////////////////////////////////////////////////////////
action a_patroller()
{
	while(my == NULL) wait(1);

	VECTOR temp[3];
	set(my,POLYGON | SHADOW);

	while(true)
	{
		c_scan(my.x, my.pan, vector(360, 60, 1000), IGNORE_ME | SCAN_ENTS | SCAN_LIMIT);
		if(you)
		{
			my_target_node = you;
			my_target_node.scale_z = 2;
			vec_set(temp, my_target_node.x);
			vec_sub(temp, my.x);
			vec_to_angle(my.pan, temp);
			my.tilt = 0;
			while (vec_dist (my.x, my_target_node.x) > 50)
			{
				my.skill22 += 5 * time_step;
				c_move(my, vector(5 * time_step, 0, 0), nullvector, IGNORE_PASSABLE | GLIDE); // 5 = movement speed
				ent_animate(my, "walk", my.skill22, ANM_CYCLE);
				wait (1);
			}
			my.skill99 = 0;
			while (my.skill99 < my_target_node.skill1)
			{
				my.skill99 += time_step / 16;
				ent_animate(my, "stand", my.skill22, ANM_CYCLE);
				my.skill22 += 3 * time_step;
				wait (1);
			}
			ent_remove(my_target_node);
		}
		else
		{
			ent_animate(my, "stand", my.skill22, ANM_CYCLE);
			my.skill22 += 3 * time_step;
		}
		wait (1);
	}
}

void health_indicator()
{
	set (my, PASSABLE);
	while (!player) {wait (1);}
	while (you)
	{
		vec_set (my.x, you.x);
		my.z += 60;
		my.scale_x = you.HEALTH * 0.1;
		wait (1);
	}
}

action NeutralEnt() {
	
	my.ObjectType = Neutral;
	
	TerrainEnt = my;	
	set(my,POLYGON);
	total_vertices = ent_status(my,1);
	my.emask |= ENABLE_TOUCH|ENABLE_CLICK|ENABLE_RIGHTCLICK|DYNAMIC;	
	my.event = TDeform_deform_terrain;	
	//	my.material = mtl_pTex1;
	
}

action APlayerBike() {

	var movement_speed = 0; // initial movement speed
	var rotation_speed = 3; // rotation speed

	my.CameraBike = 1;

	VECTOR bike_speed, temp;
	player = my;

	set(my,SHADOW | POLYGON);

	while(my)
	{
		if(PLAYTESTING && my.CameraBike && !my.CameraFP) {
			
			if(key_w || key_s) {
				
				ent_animate(my,"run",my.skill5,ANM_CYCLE);
				my.skill5 += 4 * time_step;
				
			}
			
			my.pan += rotation_speed * (key_a - key_d) * time_step;
			if (key_a)
			{
				if (my.roll > -20) my.roll -= 5 * time_step;
			}
			else
			{
				if (my.roll < 0) my.roll += 5 * time_step;
			}

			if (key_d)
			{
				if (my.roll < 20) my.roll += 5 * time_step;      
			}
			else
			{
				if (my.roll > 0) my.roll -= 5 * time_step;
			}

			// 15 gives the acceleration, 0.1 gives the frictiob
			vec_set(bike_speed.x, accelerate (movement_speed, 15 * (key_w - key_s), 0.1));

			bike_speed.y = 0;

			vec_set (temp.x, my.x);

			temp.z -= 10000;
			bike_speed.z = -c_trace (my.x, temp.x, IGNORE_ME | IGNORE_PASSABLE | USE_BOX) + 5;

			c_move (my, bike_speed.x, nullvector, IGNORE_PASSABLE | GLIDE);                

			camera.x = my.x - 250 * cos(my.pan); // put the camera 250 quants behind the bike
			camera.y = my.y - 250 * sin(my.pan);
			camera.pan = my.pan; // the camera and the bike have the same pan angle
			camera.z = my.z + 140; // place the camera above the bike, play with this value
			camera.tilt = -10; // look downwards   
			
		}             

		wait (1);

	}


}

ENTITY *dummy_ent;

void move_dummy()
{
	set(my,PASSABLE | INVISIBLE);
	while (1)
	{
		vec_set (my.x, you.x);
		wait (1);
	}
}

void move_target()
{
	while(1)

	{ 

		cam_speed = minv(15, cam_speed + 5 * time_step); // 15 gives the movement speed
		c_move(my, vector(cam_speed * time_step, 0, 0), nullvector, IGNORE_PASSABLE | GLIDE);
		vec_to_angle (dummy_ent.pan, vec_diff (temp_angle, pos_node, my.x));
		
		if(my.pan != dummy_ent.pan)
		{
			angle_difference = ang(dummy_ent.pan - my.pan);
			my.pan += angle_difference * 0.2 * time_step;
		}

		vec_set (camera.x, my.x);
		camera.pan = my.pan;
		camera.tilt = my.tilt;

		wait(1);

	}

}

action dummy_target()
{        

	dummy_ent = ent_create ("dummy.mdl", nullvector, move_dummy);

	move_target();

	result = path_scan(me, my.x, my.pan, vector(360, 180, 1000));

	if (!result) return;

	path_getnode (my, 1, pos_node, NULL);

	vec_to_angle (my.pan, vec_diff (temp_angle, pos_node, my.x)); // rotate towards the node

	vec_to_angle (dummy_ent.pan, vec_diff (temp_angle, pos_node, my.x)); // rotate dummy_ent towards the node as well

	while (1)
	{

		dist_to_node = vec_dist(my.x, pos_node);
		if(dist_to_node < 300) // close to the node?
		{
			current_node = path_nextnode(my, current_node, 1);
			if (!current_node) {current_node = 1;} // reached the end of the path? Then start over!
			path_getnode (my, current_node, pos_node, NULL);

		}

		wait(1);

	}
	
}

/////////
//cerberi_croman's code (user request topic)
//http://www.coniserver.net/ubb7/ubbthreads.php?ubb=showflat&Number=186382#Post186382
//some changes Xd1Vo :p

// 12.10.2013/13.10.2013 modified by Nguyen Ngoc Huy:
// + some changes were made specifically for craftbox
// + group voids
// + disable the "running stamina" system

#define gravity skill30
#define zoffset skill31

#define animate skill32
#define animate2 skill33
#define state skill34
#define currentframe skill35
#define blendframe skill36

#define nullframe -2
#define blend -1
#define stand 0
#define run 1
#define walk 2
#define walkSlow 3
#define walkBack 4

#define run_animation_speed 4

VECTOR speed;
var sMove = 1;
var camera_type=0;


action player1()
{
	
	VECTOR fpos;
	
	flashlight = ent_create ("flashlight1.mdl",nullvector,NULL);
	
	vec_set(flashlight.blue,vector(60,128,120));
	set(flashlight,PASSABLE | SPOTLIGHT);
	player = me;
	
	set(my,UNLIT | POLYGON | SHADOW);
	my.HEALTH = 100;
	my.gravity = 6; // needed for
	my.zoffset = 2; // gravity handling
	c_setminmax(me);
	
	my.CameraFP = 1;
	//	my.material = mtl_pTex1;
	
	ent_create ("health.pcx", my.x, health_indicator);
	
	act_grassgenerator(me);
	act_nodegenerator(me);
	//	act_foggenerator(me);
	
	while(my)
	{
		if(PLAYTESTING && my.CameraFP && !my.CameraBike)
		{
			
			/*** Initial setup ***/
			vec_for_bone(fpos,me,"Bip01 R Finger1");
			vec_set(flashlight.x,fpos);vec_set(flashlight.pan,my.pan);
			
			if(camera.tilt < -90) camera.tilt = -90;
			if(camera.tilt > 45) camera.tilt = 45;
			
			/*** Animation ***/
			if (my.state != blend && my.blendframe != nullframe) 
			{ 
				my.animate2 = 0;
				my.state = blend;
			}
			
			if (my.state == blend)
			{
				if (my.currentframe == stand) ent_animate(my,"patrol_idle",my.animate,ANM_CYCLE);
				if (my.currentframe == run) ent_animate(my,"run",my.animate,ANM_CYCLE);
				if (my.currentframe == walk) ent_animate(my,"patrol_stree",my.animate,ANM_CYCLE);
				if (my.currentframe == walkBack) ent_animate(my,"patrol_stree",my.animate,ANM_CYCLE);
				if (my.currentframe == walkSlow) ent_animate(my,"patrol_stree",my.animate,ANM_CYCLE);
				if (my.blendframe == stand) ent_blend("patrol_idle",0,my.animate2);
				if (my.blendframe == run) ent_blend("run",0,my.animate2);
				if (my.blendframe == walk) ent_blend("patrol_stree",0,my.animate2);
				if (my.blendframe == walkBack) ent_blend("patrol_stree",0,my.animate2);
				if (my.blendframe == walkSlow) ent_blend("patrol_stree",0,my.animate2);

				my.animate2 += 30 * time_step;
				
				if (my.animate2 >= 100) 
				{
					my.animate = 0;
					my.state = my.blendframe;
					my.blendframe = nullframe;
				}
			}
			
			if (my.state == stand) 
			{
				ent_animate(my,"patrol_idle",my.animate,ANM_CYCLE);
				my.animate += 5 * 1 * time_step;
				my.animate %= 100;
				my.currentframe = stand;
			}
			
			if (my.state == run) 
			{
				ent_animate(my,"run",my.animate,ANM_CYCLE);
				my.animate += run_animation_speed * 1 * 3 * time_step;
				my.animate %= 100;
				my.currentframe = run;
			}
			
			if (my.state == walk) 
			{
				ent_animate(my,"patrol_stree",my.animate,ANM_CYCLE);
				my.animate += 7 * 1 * time_step;
				my.animate %= 100;
				my.currentframe = walk;
				wait(1);
				
			}
			
			if (my.state == walkSlow) 
			{
				ent_animate(my,"patrol_stree",my.animate,ANM_CYCLE);
				my.animate += 5 * 1 * time_step;
				my.animate %= 100;
				my.currentframe = walkSlow;
			}
			
			if (my.state == walkBack) 
			{
				ent_animate(my,"patrol_stree",my.animate,ANM_CYCLE);
				my.animate -= 5 * 1 * time_step;
				if(my.animate <= 0){my.animate += 100;}
				my.currentframe = walkBack;
			}
			
			/*** Movement ***/
			if(key_w) {
				
				if(key_shift) sMove = 2;
				else sMove = 1;
				
			}
			
			result = c_trace(my.x, vector(my.x,my.y,my.z-5000), IGNORE_ME|IGNORE_PASSENTS|IGNORE_PASSABLE|IGNORE_SPRITES|USE_BOX); 
			speed.z = -(result - my.zoffset);

			if(sMove == 1) {
				speed.x = (key_w - key_s) * 12 * time_step;//6
				speed.y = (key_a - key_d) * 5 * time_step;
				
				c_move(me, speed.x, nullvector, IGNORE_PASSABLE | GLIDE);
				my.pan = camera.pan;

			}
			
			if(sMove == 2){
				speed.x = (key_w - key_s) * 35 * time_step;//11
				speed.y = (key_a - key_d) * 15 * time_step;
				
				c_move(me, speed.x, nullvector, IGNORE_PASSABLE | GLIDE);
				my.pan = camera.pan;
				
			}
			
			if(key_w && sMove == 1 && my.state != walk) my.blendframe = walk;
			if(key_w && sMove == 2 && my.state != run) my.blendframe = run;
			if(key_s && my.state != walkBack) my.blendframe = walkBack; speed.x += 2 * time_step;
			if(!key_w && !key_s && !key_a && !key_d && my.state != stand) my.blendframe = stand;
			
			/*** Camera ***/
			if(key_1) {
				
				while(key_1) wait(1);
				switch(camera_type) {
					
					case 0: //firstperson
					
					//					set(panCAMRecorder,SHOW);
					//					set(panCAMRecorder_digits,SHOW);
					//					set(panCAMRecorderREC,SHOW);
					//					set(FPCrosshair,SHOW);
					set(flashlight,INVISIBLE);
					
					camera_type = 1;
					
					break;
					
					case 1: //thirdperson
					
					reset(panCAMRecorder,SHOW);
					reset(panCAMRecorder_digits,SHOW);
					reset(panCAMRecorderREC,SHOW);
					reset(FPCrosshair,SHOW);
					reset(flashlight,INVISIBLE);
					
					camera_type = 0;
					
					break;
					
				}
				
			}
			
			if(camera_type == 0) {
				
				camera.genius = NULL;
				camera.pan -= 15 * mouse_force.x * time_step;
				camera.tilt += 15 * mouse_force.y * time_step;

				camera.x = player.x - 100 * cos(camera.pan) * cos(camera.tilt);
				camera.y = player.y - 100 * sin(camera.pan) * cos(camera.tilt);
				camera.z = player.z - 100 * sin(camera.tilt) + 110;
				vec_add(camera.x,vector(20,10,30)); 
				
			}
			
			else { 
				
				camera.genius = me;
				camera.pan -= 15 * mouse_force.x * time_step;
				camera.tilt += 15 * mouse_force.y * time_step;

				camera.x = player.x;
				camera.y = player.y;
				camera.z = player.z + 150;
			}
			
			
			/*** Etc ***/
			
			// 
			
		}
		wait(1);
	} 
	
}