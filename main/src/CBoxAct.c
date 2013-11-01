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

/*** Third/first person camera ***/
/////////
//cerberi_croman's code (user request topic)
//http://www.coniserver.net/ubb7/ubbthreads.php?ubb=showflat&Number=186382#Post186382
//some changes Xd1Vo :p

// 12.10.2013/13.10.2013 modified by Nguyen Ngoc Huy:
// + some changes were made specifically for craftbox
// + group functions
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

/*****************************/

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

#define HEALTH skill30

function health_indicator()
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

var cam_speed = 1; // initial speed
var dist_to_node;
var current_node = 1;
var angle_difference = 0;
var temp_angle;
var pos_node; // stores the position of the node

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

action act_mystymood_trigg();

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

//title:MystyMood Sky Template
//image:loopix_logo.pcx
//action:act_mystymood_trigg  
//skill1:trigg_range 300.000
//help: sets  range within the mood-trigger is activated
//skill2:trigg_rain_wind_x 2.000
//help: wind strenght on direction x
//skill3:trigg_rain_wind_y 0.000
//help:  wind strenght on direction y
//skill4:trigg_rain_fallspeed 20.000
//help: fallingspeed of the raindrops
// section:
//skill5:trigg_snow_wind_x 4.000
//help: wind strenght on direction x
//skill6:trigg_snow_wind_y 0.000
//help: wind strenght on direction y
//skill7:trigg_snow_fallspeed 5.000
//help: fallingspeed of the snowflakes
// section:
//skill8:trigg_rain_random_move 2.000
//help: random-xy movement of the rain particle
//skill9:trigg_snow_random_move 4.000
//help: random-xy movement of the snow particle
// section:
//skill10:trigg_weather_fade_speed 10.000
//help: speed of fading one weather/mood state into the next
//section:
//skill11:trigg_fog_near 0.000
//help: sets the fog_near distance...use negative values for starting the fog behind the camera
//skill12:trigg_fog_far 0.000
//help: sets the fog_far distance
//skill13: trigg_fog_red 140.000
//help: fog color red
//skill14: trigg_fog_green 170.000
//help: fog color green
//skill15: trigg_fog_blue 160.000
//help: fog color blue
//section:
//text: flag to enable rain
//flag1:trigg_rain 0.000
//text: flag to enable snow
//flag2:trigg_snow 0.000
//text: flag to disable lightning and thunder
//flag3:trigg_disable_lightning_thunder
// section:
//text: flag to enable random-xy movement of the rain particle
//flag4:trigg_rain_random_move_on 1.000
//text: flag to enable random-xy movement of the snow particle
//flag5:trigg_snow_random_move_on 1.000
// section:
//text: flag to enable fog distance/density change
//flag6:trigg_fog_col_dist 1.000
//uses:trigg_range,trigg_rain,trigg_snow,trigg_rain_wind_x,trigg_rain_wind_y,trigg_rain_fallspeed
//uses:trigg_snow_wind_x,trigg_snow_wind_y,trigg_snow_fallspeed
//uses:trigg_rain_random_move_on,trigg_snow_random_move_on,trigg_rain_random_move,trigg_snow_random_move
//uses:trigg_weather_fade_speed,trigg_disable_lightning_thunder
//uses:trigg_fog_col_dist,trigg_fog_near,trigg_fog_far,trigg_fog_red,trigg_fog_green,trigg_fog_blue
action act_mystymood_trigg()
{
	ent_mystymood_trigg = me;

	set(my,PASSABLE);

	//set default skills
	if(!my.trigg_range) my.trigg_range = 300;
	if(!my.trigg_rain_fallspeed) my.trigg_rain_fallspeed = 20;
	if(!my.trigg_snow_fallspeed) my.trigg_snow_fallspeed = 5;
	if(!my.trigg_weather_fade_speed) my.trigg_weather_fade_speed = 10;

	my.trigg_ID = trigg_num_off;
	trigg_num_off += 1;

	my.skill70 = weather_state;	
	my.skill71 = rain_random_move_on;
	my.skill72 = rain_random_move;
	my.skill73 = rain_wind_x;
	my.skill74 = rain_wind_y;
	my.skill75 = rain_fallspeed;
	my.skill76 = disable_lightning_thunder;
	my.skill77 = snow_random_move_on;
	my.skill78 = snow_random_move;
	my.skill79 = snow_wind_x;
	my.skill80 = snow_wind_y;
	my.skill81 = snow_fallspeed;
	my.skill82 = weather_fade_speed;	

	while(1)
	{
		if(vec_dist(my.x,camera.x) < my.trigg_range)
		{
			trigg_active_id = my.trigg_ID;
			
			if(is(my,trigg_rain)) weather_state = 1;
			if(is(my,trigg_snow)) weather_state = 2;
			if(!is(my,trigg_snow) && !is(my,trigg_rain)) weather_state = 0;
			
			weather_fade_speed = my.trigg_weather_fade_speed;
			
			if(weather_state > 0)
			{
				
				rain_random_move_on = is(my,trigg_rain_random_move_on);
				rain_random_move = my.trigg_rain_random_move;
				
				rain_wind_x = my.trigg_rain_wind_x;
				rain_wind_y = my.trigg_rain_wind_y;
				
				rain_fallspeed = my.trigg_rain_fallspeed;
				
				disable_lightning_thunder = is(my,trigg_disable_lightning_thunder);
				
				snow_random_move_on = is(my,trigg_snow_random_move_on);
				snow_random_move = my.trigg_snow_random_move;
				
				snow_wind_x = my.trigg_snow_wind_x;
				snow_wind_y = my.trigg_snow_wind_y;
				
				snow_fallspeed = my.trigg_snow_fallspeed;		
				
			}
			
			if(is(my,trigg_fog_col_dist))
			{
				func_fade_colors(d3d_fogcolor1,current_color,fog_col_trigg);
				
				fog_dist_near_trigg = my.trigg_fog_near;
				fog_dist_far_trigg= my.trigg_fog_far;
				
				if(camera.fog_start>fog_dist_near_trigg) camera.fog_start -= weather_fade_speed*time_step;
				else camera.fog_start += weather_fade_speed*time_step;
				
				if(camera.fog_end>fog_dist_far_trigg) camera.fog_end -= weather_fade_speed*time_step;
				else camera.fog_end += weather_fade_speed*time_step;
				
				fog_col_trigg[2] = my.trigg_fog_red;
				fog_col_trigg[1] = my.trigg_fog_green;
				fog_col_trigg[0] = my.trigg_fog_blue;
				
				
			}
		}
		else
		{
			if(trigg_active_id == my.trigg_ID)
			{
				trigg_active_id = -1;		
				act_mystymood_trigg_label1();	
				break;
			}
		}
		
		wait(1);	
	}
}

action NeutralEnt() {
	
	set(my, POLYGON);
	my.ObjectType = Neutral;
	
	//	my.material = mtl_pTex1;
	
}

action player1()
{
	
	VECTOR fpos;
	
	flashlight = ent_create ("flashlight1.mdl",nullvector,NULL);
	
	vec_set(flashlight.blue,vector(60,128,120));
	set(flashlight,PASSABLE/* | SPOTLIGHT*/);
	player = me;
	
	set(my,UNLIT | POLYGON | SHADOW);
	my.HEALTH = 100;
	my.gravity = 6; // needed for
	my.zoffset = 2; // gravity handling
	c_setminmax(me);
	
	my.CameraFP = 1;
	//	my.material = mtl_pTex1;
	
	ent_create ("health.pcx", my.x, health_indicator);
	
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

			}
			
			if(sMove == 2){
				speed.x = (key_w - key_s) * 35 * time_step;//11
				speed.y = (key_a - key_d) * 15 * time_step;
			}
			my.pan = camera.pan;
			
			if(key_w && sMove == 1 && my.state != walk) my.blendframe = walk;
			if(key_w && sMove == 2 && my.state != run) my.blendframe = run;
			if(key_s && my.state != walkBack) my.blendframe = walkBack; speed.x += 2 * time_step;
			if(!key_w && !key_s && !key_a && !key_d && my.state != stand) my.blendframe = stand;
			
			c_move(me, speed.x, nullvector, IGNORE_PASSABLE | GLIDE);
			
			/*** Camera ***/
			if(key_1) {
				
				while(key_1) wait(1);
				switch(camera_type) {
					
					case 0: // third person camera
					
					set(panCAMRecorder,SHOW);
					set(panCAMRecorder_digits,SHOW);
					set(panCAMRecorderREC,SHOW);
					
					camera_type = 1;
					
					break;
					
					case 1: // first person camera
					
					reset(panCAMRecorder,SHOW);
					reset(panCAMRecorder_digits,SHOW);
					reset(panCAMRecorderREC,SHOW);
					
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