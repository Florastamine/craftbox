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

VECTOR dist, absdist, force, camera_center;
var my_height; //
var step_height = 8; //
var overallspeed = 7.9; // Overall player's movement speed
var mouse_spd = 9; // Mouse sensivity
var cam_height = 110; // Camera's Z-height
var temp_cam = 0;

void fpcam_push(var Speed,var Amount)
{
	dist.x = Speed * Amount * time_step;
	force.x = Speed * time_step;
	accelerate(dist.x,force.x,0.7);
}

void fpcam_flashlight() {

	proc_mode = PROC_LATE;

	flashlight = me;
	set(flashlight,PASSABLE | SPOTLIGHT | CAST | LIGHT);
	flashlight.lightrange = 1500;
	vec_set(flashlight.blue,vector(255,100,100));

	while(1)
	{
		if(key_t) flashlight.lightrange += 25;
		if(key_y) flashlight.lightrange -= 25;
		
		flashlight.x = player.x + 15 * cos(player.pan) + 20 * sin(player.pan);
		flashlight.y = player.y + 50 * sin(player.pan) - 20 * cos(player.pan);
		flashlight.z = player.z + 10; 
		flashlight.pan = player.pan;
		flashlight.tilt = player.tilt;
		flashlight.roll = player.roll;
		wait(1);
	}  

}

void fpcam_update()
{
	vec_lerp(camera.x,camera.x,camera_center.x,0.3);
	vec_lerp(camera_center,camera_center,vector(0,0,cam_height),1);
	vec_rotate(camera_center,my.pan);
	vec_add(camera_center,my.x);
	camera.pan -= mouse_spd * mouse_force.x * time_step;
	camera.tilt += mouse_spd * mouse_force.y * time_step;
	camera.z = -25;
	if(camera.tilt > 70) camera.tilt = 70;
	if(camera.tilt < -70) camera.tilt = -70;
}

void fpcam_input()
{
	if(key_z)
	{
		while(camera->arc >= 45)
		{
			camera->arc -= .2 * time_step;
			wait(1);
		}
	}
	else
	{
		while(camera->arc <= 60)
		{
			camera->arc += .2 * time_step;
			wait(1);
		}
	}

	if(my_height <= 10)
	{
		force.x = overallspeed * (key_w - key_s) * time_step;
		
		if(key_shift && (key_w)) accelerate(dist.x,force.x + 3.5,0.5);
		else accelerate(dist.x,force.x,0.7);
		
		force.y = overallspeed * (key_a - key_d) * time_step;
		
		if(key_shift && (key_w)) accelerate(dist.x,force.x + 1.5,0.5);
		else accelerate(dist.y,force.y,0.7);
	}

	if(key_w) {
		
		ent_animate(my,"ComNwForward",my.skill65,ANM_CYCLE);
		my.skill65+=5*time_step;
		
		if(key_shift) {
			
			ent_animate(my,"ComNrForward",my.skill65,ANM_CYCLE);
			my.skill65+=5*time_step;
			
		}
		
	}

	else if(key_s) {
		
		ent_animate(my,"ComNwBackward",my.skill65,ANM_CYCLE);
		my.skill65+=5*time_step;
	}

	else if(key_a) {
		
		ent_animate(my,"ComNwLeft",my.skill65,ANM_CYCLE);
		my.skill65 += 5 * time_step;
		
	}

	else if (key_d) {
		
		ent_animate(my,"ComNwRight",my.skill65,ANM_CYCLE);
		my.skill65 += 5 * time_step;
		
	}

	else {
		
		ent_animate(my,"ComNormalStand",my.skill65,ANM_CYCLE);
		my.skill65 += 5 * time_step;
		
	}

	move_friction = 0.2;
	move_min_z = -1;

}

action APlayerFP()
{
	player = my;
	set(my,POLYGON | SHADOW);
	//	my.scale_x = 4.5;
	//	my.scale_y = my.scale_x;
	//	my.scale_z = my.scale_x;

	my.CameraFP = 1;

	flashlight = ent_create("Torch.mdl",my.x,fpcam_flashlight);

	while(my)
	{
		if(PLAYTESTING && my.CameraFP && !my.CameraBike)
		{
			if(my_height <= 10) my.pan = camera.pan;
			my_height = c_trace(my.x,vector(my.x,my.y,my.z-9999),IGNORE_MODELS|IGNORE_PASSABLE|IGNORE_ME|USE_BOX);
			if(my_height > 10) accelerate(absdist.z,-10 * time_step,-1);    
			
			else
			{
				absdist.z = -(my_height/1.2)+ step_height;
				absdist.z = clamp(absdist.z,-step_height,step_height);
				if((my_height + absdist.z) > 10){ absdist.z = -my_height -10; }
			} 
			
			c_move(my,dist,absdist, IGNORE_PASSABLE|GLIDE);	
			
			fpcam_update();
			fpcam_input();
		}
		wait(1);
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

