#ifndef Craftbox_System_Environment

#define Craftbox_System_Environment

/*
--------------------------------------------------
Craftbox_System_Environment.c

Handles environment effects like rain, snow, day/night...

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
void free_camera()

Desc: This is the camera controller I found when I was tweaking Mystymood.
+ 5.7.2013 : This camera is good, but I have to partly rewrite it
because...well, I won't explain, find out for yourself.
This code won't be checked against PLAYTESTING because
it will be killed prior to set PLAYTESTING to 1.
and restored later when PLAYTESTING has been set to 0.
+ 13.10.2013, 22.10.2013 : Modified.

Returns: -
--------------------------------------------------
*/
void free_camera()
{

	WriteLog("[ ] Setting up camera...");
	NewLine();

	var doublefactor;

	set(my, POLYGON | PASSABLE | INVISIBLE);

	while(1)
	{
		
		if(key_shift) doublefactor = 3;
		else doublefactor = 1; // prevent multiplication by 0
		
		//		if(camera.tilt >= 90) camera.tilt = 90;
		//		if(camera.tilt <= -90) camera.tilt = -90;
		
		// 60 = speed
		
		if(! PLAYTESTING ) {
			
			camera_force.x = ( (key_w || key_cuu) - (key_s || key_cud) )*60*doublefactor*time_step;
			camera_force.y = ( (key_a || key_cul) - (key_d || key_cur) )*60*doublefactor*time_step;
			
			c_move(my,camera_force,nullvector,GLIDE+IGNORE_PASSABLE+IGNORE_PASSENTS+IGNORE_PUSH);
			vec_set(camera.x,vector(my.x,my.y,my.z+15));
			
			// 3 = rotation speed
			camera.tilt += 3 * mouse_right*mouse_force.y * time_step;
			camera.pan += 3 * mouse_right*-mouse_force.x * time_step;
			
			vec_set(my.tilt,camera.tilt);
			vec_set(my.pan,camera.pan);
			
		}
		
		wait(1);
	}
	
}

////////////////////////////////////////////////////////////
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

/*
--------------------------------------------------
void flare_init(ENTITY *flare_ent)

Desc:

Returns: - 
--------------------------------------------------
*/

/*
void flare_init(ENTITY *flare_ent)
{
	
	while(!flare_ent) wait(1);

	WriteLog("[ ] Intializing lens flare for ");
	WriteLog( (STRING *) flare_ent->type );
	NewLine();

	my = flare_ent;
	my.flags2 &= ~SHOW;
	my.flags |= (BRIGHT|PASSABLE|TRANSLUCENT);
	
	WriteLog("[X] Task completed.");
	NewLine();
	
}
*/

/*
--------------------------------------------------
void flare_place(ENTITY *flare_ent)

Desc: Places a flare at temp.x/temp.y deviations from screen center

Returns: -
--------------------------------------------------
*/

/*
void flare_place(ENTITY *flare_ent)
{

	// Do not flood the log file

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
*/

/*
--------------------------------------------------
void LoadMystymoodLensflare()

Desc:

Returns: -
--------------------------------------------------
*/

/*
void LoadMystymoodLensflare()
{

	WriteLog("[ ] Activating lens flare");
	NewLine();

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
	
	WriteLog("[X] Task completed for LoadMystymoodLensflare().");
	NewLine();

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

	WriteLog("[X] Deactivated lens flare.");
	NewLine();

}
*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////
////MystyMood sky/sun/weather template...works without shader, uses 3dgs sky entitys!
////
////Note: All sky/weather values must be adjusted in this script...exept from the mysty_mood trigger values 
////that can be adjusted for each trigger dummy via the behaviour panel in WED.
////
////Jun 07 by www.loopix-project.com
////Nov 07 Lite-C conversion by Alexis Rozhkov aka Shadow
//// 22.10.2013: U just tested this with Shade-C 0.91, worked just fine. Shade-C EVO? Maybe later.
/////////////////////////////////////////////////////////////

/*
--------------------------------------------------
void func_fade_colors(var *col_target, var *col1, var *col2)

Desc: 

Returns: -
--------------------------------------------------
*/
void func_fade_colors(var *col_target, var *col1, var *col2)
{
	var i = 0;
	if(i < 100)
	{
		i = minv(i + fog_fade_speed*time_step, 100);
		vec_lerp(col_target, col1, col2, i/100);
	}
}


/*
--------------------------------------------------
void func_particle_seed_infinity(PARTICLE *p)

Desc: 

Returns: -
--------------------------------------------------
*/

/*
void func_particle_seed_infinity(PARTICLE *p)
{

	vec_set(p.x,vector(cycle(p.x,camera.x-particle_seedbox.x,camera.x+particle_seedbox.x),
	cycle(p.y,camera.y-particle_seedbox.y,camera.y+particle_seedbox.y),
	cycle(p.z,camera.z-particle_seedbox.z,camera.z+particle_seedbox.z)));

	if(p.z<camera.z-100) p.lifespan = 0;

}
*/

/*
--------------------------------------------------
void func_effect_particle_seed(PARTICLE *p)

Desc:

Returns: -
--------------------------------------------------
*/

/*
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
*/

/*
--------------------------------------------------
void func_fade_lightning(PARTICLE *p)

Desc:

Returns: -
--------------------------------------------------
*/
//void func_fade_lightning(PARTICLE *p)  { p.lifespan = 0; }

/*
--------------------------------------------------
void func_particle_lightning(PARTICLE *p)

Desc: 

Returns: -
--------------------------------------------------
*/

/*
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
*/

/*
--------------------------------------------------
void func_particle_segment()

Desc:

Returns: -
--------------------------------------------------
*/

/*

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
	
	wait(1);
}

*/

/*
--------------------------------------------------
void func_particle_segment()

Desc:

Returns: -
--------------------------------------------------
*/

/*

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
	
	wait(1);
}

*/

/*
--------------------------------------------------
void func_increase_brightness()

Desc:

Returns: -
--------------------------------------------------
*/

/*

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
	
	wait(1);
}

*/

/*
--------------------------------------------------
void weather_change()

Desc:Can't be replaced with VOL_EFFECTS (at the momment).

Returns: -
--------------------------------------------------
*/
void weather_change() {
	
	//   Uncomment the following lines to unlock the old effects that was packed with Mystymood.
	//	Replace 'em with newer and Mystymood-independent code.

	/*
	if(!mystymood_active) return; // Activates weather ONLY IF Mystymood is active.

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

	while(mystymood_active)
	{
		
		//		random_seed(0);
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
				snd_handle_thunder = snd_play(thunder1_wav, VOL_EFFECTS, 0);
				rand_count_state = 1;
			}
			if(rand_count == 2 && rand_count_state != 2)
			{
				snd_handle_thunder = snd_play(thunder2_wav, VOL_EFFECTS, 0);
				rand_count_state = 2;
			}
			if(rand_count == 3 && rand_count_state != 3)
			{
				snd_handle_thunder = snd_play(thunder3_wav, VOL_EFFECTS, 0);
				rand_count_state = 3;	
			}
			if(rand_count == 4 && rand_count_state != 4)
			{
				snd_handle_thunder = snd_play(thunder4_wav, VOL_EFFECTS, 0);
				rand_count_state = 4;	
			}
			if(rand_count == 5 && rand_count_state != 5)
			{
				snd_handle_thunder = snd_play(thunder5_wav, VOL_EFFECTS, 0);
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
	
	*/
	
}

/*
--------------------------------------------------
void LoadMystymood(BOOL _on, BOOL load_lens)

Desc:

Returns: -
--------------------------------------------------
*/

void LoadMystymood(BOOL _on /* , BOOL load_lens */ )
{
	
	WriteLog("[ ] Loading Mystymood");
	NewLine();

	if( !_on ) { // Unload mystymood & lensflare effect
		
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
		
		WriteLog("[X] Task completed, switched off Mystymood because no parameters were on.");
		NewLine();
		
		return;
		
	}
	
	/*
	
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

	if(step>=2) {
		
		WriteLog("[X] Task completed, switched off Mystymood because no parameters were on.");
		NewLine();
		
		return;
		
	}
	
	*/

	////////////////////////////////////////////////////////////
	// Setup for lensflare
	////////////////////////////////////////////////////////////
	
	/*
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
	*/
	
	////////////////////////////////////////////////////////////

	sky_horizon.flags2 |= SHOW;
	sky_cloud1.flags2 |= SHOW;
	sky_cloud2.flags2 |= SHOW;
	sky_cloud3.flags2 |= SHOW;
	sky_day.flags2 |= SHOW;	
	
	if(_use_nightstars) sky_night.flags2 |= SHOW;
	if(_use_moon) sky_moon.flags2 |= SHOW;
	
	if(_use_sun) {
		
		sky_sun.flags2 |= SHOW;
		sky_suncorona.flags2 |= SHOW;
		sky_sunshine.flags2 |= SHOW;
		
	}

	VECTOR temp;

	sky_sun.scale_x = sun_scale_x;
	sky_sun.scale_y = sun_scale_y;

	fog_color = 1;

	camera.fog_start = land_fog_near;//-50;
	camera.fog_end = land_fog_far;//300;

	vec_set(d3d_fogcolor1,fog_day);//set the default day fog-color 

	mystymood_active = 1;
	
	WriteLog("[X] Task completed, activated Mystymood.");
	NewLine();
	
	//	weather_change();

	while(mystymood_active) {
		
		vec_set(sun_color.blue,vector(d3d_fogcolor1.blue*sun_col_fac,d3d_fogcolor1.green*sun_col_fac,d3d_fogcolor1.red*sun_col_fac));
		vec_set(sky_color.blue,d3d_fogcolor1.blue);	
		vec_set(sky_horizon.blue,d3d_fogcolor1.blue);
		
		//		if( !weather_state && trigg_active_id < 0) {
			
			if(!dynamic_day_night) func_fade_colors(d3d_fogcolor1,current_color,fog_dynamic_day_night_off);
			
			if(camera.fog_start>land_fog_near) camera.fog_start -= weather_fade_speed*time_step;
			else camera.fog_start += weather_fade_speed*time_step;
			
			if(camera.fog_end>land_fog_far) camera.fog_end -= weather_fade_speed*time_step;
			else camera.fog_end += weather_fade_speed*time_step;
			
		//		}
		
		vec_set(current_color,d3d_fogcolor1);
		
		vec_set(temp,sun_pos); 
		vec_set(sky_sun.x,temp);  // copy the sun_pos location
		vec_sub(temp,camera.x); // direction vector from camera to our sun_pos
		vec_normalize(temp,land_fog_far-sun_dist_minus); // chop our direction vector to a set distance	
		
		vec_set(sky_sun.x,temp);
		
		if(_use_moon) {
			
			vec_set(temp,sky_sun.x); 
			vec_inverse(temp);
			vec_set(sky_moon.x,temp);  // copy the sun_pos location
		}
		
		if(dynamic_day_night) {
			
			if(sun_angle.pan > 230 && sun_angle.pan < 360)
			
			sun_angle.pan += .01*time_speed_night*time_step;
			else sun_angle.pan += .01*time_speed*time_step;
			
			sun_angle.pan %= 360;
			sun_angle.tilt = fsin(sun_angle.pan, max_zenith);
			
			//sun "grows" at low azimut
			if(sky_sun.z<sun_grow_z) {
				
				if(sky_sun.scale_x<sun_scale_x+1 && sky_sun.scale_y<sun_scale_y+1) {
					
					sky_sun.scale_x = sky_sun.scale_y += .01 * (time_speed/10) * time_step;
					
				}	
				
			}
			
			else {
				
				if(sky_sun.scale_x>sun_scale_x && sky_sun.scale_y>sun_scale_y) {
					
					sky_sun.scale_x = sky_sun.scale_y -= .01 * (time_speed/10) * time_step;
					
				}
			}
		}
		
		else {
			
			sun_angle.pan = sun_azimuth;
			sun_angle.tilt = sun_elevation;
			
		}
		
		if(sun_angle.pan > 0 && sun_angle.pan < 40) {
			
			if (sky_cloud1.alpha < 80) sky_cloud1.alpha += sky_fade_speed*time_step*time_speed;
			if (sky_cloud2.alpha < 60) sky_cloud2.alpha += sky_fade_speed*time_step*time_speed;
			if (sky_day.alpha < 60) sky_day.alpha += sky_fade_speed*time_step*time_speed;
			if (sky_night.alpha > 1) sky_night.alpha -= sky_fade_speed*time_step*time_speed;	
			
		}
		
		if(sun_angle.pan > 10 && sun_angle.pan < 160) func_fade_colors(d3d_fogcolor1,current_color,fog_day);
		
		if(sun_angle.pan > 40 && sun_angle.pan < 160) {
			
			sky_cloud1.alpha = 80;
			sky_cloud2.alpha = 60;
			sky_day.alpha = 60;
			sky_night.alpha = 1;
			
		}
		
		// Fade into the night...
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
			
			func_fade_colors(d3d_fogcolor1,current_color,fog_weather_night);
			
		}
		
		else {
			
			func_fade_colors(d3d_fogcolor1,current_color,fog_weather_day);
			
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
	
	WriteLog("[X] Switched off Mystymood.");
	NewLine();
	
}


/*
--------------------------------------------------
void sndPlay(STRING *str)

Desc:

Returns: -
--------------------------------------------------
*/
void sndPlay(STRING *str) {
	
	if( str_len(str) ) {
		
		var hndl = media_play(str,NULL,VOL_EFFECTS);
		//		var hndl = snd_play(snd_create(str),VOL_EFFECTS,0);
		if(!hndl) return;
		
		//		while(snd_playing(hndl)) wait(1);
		while(media_playing(hndl)) wait(1);
		
		
	} else return;
	
}

/*
--------------------------------------------------
void Scale(ENTITY *ent, var amount)

Desc:

Returns: -
--------------------------------------------------
*/
void Scale(ENTITY *ent, var amount) {
	
	while(!ent) wait(1);
	
	// modify global variables
	ent.scale_x = ent.scale_y = ent.scale_z = amount; // freely, even if it is a negative number
	
}



ENTITY *SkyCube = {
	
	type = "./Cooked2D/Skies/s_s_greenland+6.tga";
	
	flags2 = SKY | CUBE | SHOW;
	
}

#endif