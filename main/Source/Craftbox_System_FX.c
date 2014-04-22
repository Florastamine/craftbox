/*
Craftbox_System_FX.c

A place for (stunning) visual effects.
Mostly they were generated using 3rd party tools.

Written by Nguyen Ngoc Huy
https://github.com/ngochuy2101
http://craftboxdev.blogspot.com/

TODO:
<+++



>+++

NOTES:
<+++

Rainbows are not included.

>+++
--------------------------------------------------
*/

/************************************************************
TUST's implementations
************************************************************/

// ---------------------------------------------------------------------------
// Explosion
// ---------------------------------------------------------------------------
void p_eff_expl_shrapnel_fade(PARTICLE *p) {
	p.alpha += 6 *time_step;
	if(p.alpha > 30) p.lifespan = 0;
}

void p_eff_expl_shrapnel(PARTICLE *p) {
	p.bmap = bmapExplSharpnel;
	p.vel_x = random(32)-16;
	p.vel_y = random(32)-16;
	p.vel_z = random(32)-16;
	p.size = 5;
	p.alpha = 0;
	p.flags |=  MOVE | TRANSLUCENT;
	p.event = p_eff_expl_shrapnel_fade;
}

void p_eff_expl_particle_fade(PARTICLE *p) {
	p.alpha -= random(4) * time_step;
	if(p.alpha < 0) p.lifespan = 0;
	p.vel_x += random(0.6)-0.3;
	p.vel_y += random(0.6)-0.3;
}

void p_eff_expl_particle(PARTICLE *p) {
	p.bmap = bmapExplParticle;
	p.angle = random(360);
	
	vec_for_angle(vecEffectsTemp, vector(p.angle, 0, 0 ));
	vec_rotate(vecEffectsTemp, vector(camera.pan, camera.tilt-90, 0));
	vec_normalize(vecEffectsTemp, 10+random(50));
	vec_add(p.x, vecEffectsTemp);
	if (random(2) > 1) {
		vec_set(vecEffectsTemp, vector( 1, 0, 0 ));
		vec_rotate(vecEffectsTemp, vector(camera.pan, camera.tilt+90, 0));
		vec_normalize(vecEffectsTemp, 10+random(5));
		vec_set(p.vel_x, vecEffectsTemp);
	}
	p.vel_z *= random(1);
	p.size = 5 ;
	p.alpha = 50 ;
	p.flags |= TRANSLUCENT | MOVE;
	p.event = p_eff_expl_particle_fade;
}

void eff_expl_smoke2 () {
	set(me, TRANSLUCENT | ZNEAR | PASSABLE | LIGHT);
	my.roll = random(360);
	my.alpha = 100;
	my.scale_x = 0.2;
	my.scale_y = 0.7;
	my.skill1 = random(3)+2;
	vec_fill(my.blue, 30);
	while(my.alpha > 0) {
		if(my.alpha > 93 ) {
			vec_for_angle(vecEffectsTemp, vector( my.roll,0,0));
			vec_rotate(vecEffectsTemp, vector(camera.pan, camera.tilt+90, 0));
			vec_normalize(vecEffectsTemp, time_step * (my.alpha/my.skill1) * 0.4);
			vec_add(my.x, vecEffectsTemp);
			my.scale_y += vec_length(vecEffectsTemp)/46;
			my.alpha -= time_step * 3;
			} else {
			vec_for_angle(vecEffectsTemp, vector(my.roll, 0, 0));
			vec_rotate(vecEffectsTemp, vector(camera.pan, camera.tilt+90, 0));
			vec_normalize(vecEffectsTemp, time_step * (my.alpha/(my.skill1*2)));
			vec_add(my.x, vecEffectsTemp);
			
			my.scale_y += vec_length(vecEffectsTemp) / 5000;
			
			my.alpha -= time_step * 9;
		}
		wait(1);
	}
	ent_remove(me);
	return;
}

void eff_expl_wave() {
	set(me, TRANSLUCENT | DECAL | PASSABLE);
	my.alpha = 70;
	vec_fill(my.scale_x, 0.1);
	my.tilt = 90;
	my.pan = random(360);
	vec_fill(my.blue, 0);
	while(my.alpha > 0) {
		vec_fill(vecEffectsTemp, time_step * 2);
		vec_add(my.scale_x, vecEffectsTemp);
		my.alpha -= time_step * 7;
		wait (1);
	}
	ent_remove(me);
}

void eff_expl_smoke() {
	set(me, TRANSLUCENT | LIGHT | ZNEAR | PASSABLE);
	vec_set(my.blue, vector(200,255,255));
	my.alpha = 40;
	my.roll = random(360);
	vec_fill(my.scale_x, 0.4);
	while(my.alpha > 0) {
		my.alpha -= time_step * 2;
		my.roll += time_step * sign(ang(my.roll))*1;
		vec_fill(vecEffectsTemp, time_step *0.01);
		vec_add(my.scale_x, vecEffectsTemp);
		wait(1);
	} 
	ent_remove ( me );
}

void eff_expl_flash_2() {
	set(me, BRIGHT | TRANSLUCENT | ZNEAR | PASSABLE);
	my.blue = 150;
	my.green = 235;
	my.red = 255;
	my.alpha = 0;
	my.roll = random(360);
	vec_fill(my.scale_x, 3);
	vec_for_angle(vecEffectsTemp, vector( my.roll, 0, 0));
	vec_rotate(vecEffectsTemp, vector(camera.pan, camera.tilt+90, 0));
	vec_normalize(vecEffectsTemp, 40);
	vec_add(vecEffectsTemp, my.x);
	vec_set(my.x, vecEffectsTemp);
	
	while(my.alpha < 100) {
		if (my.lightrange < 1000 ) my.lightrange += 2000 * time_step;
		my.alpha += time_step * (random(20)+20);
		my.roll += time_step * sign(ang(my.roll));
		vec_normalize ( my.blue, 150 + random(105) );
		wait(1);
	}
	ent_create("explSmoke02.tga", my.x, eff_expl_smoke);
	while(my.alpha > 0) {
		if (my.lightrange > 0) my.lightrange -= 500 * time_step;
		my.alpha -= time_step * 20;
		my.roll += time_step * sign(ang(my.roll))*5;
		wait(1);
	}
	while (my.lightrange > 0) {
		my.lightrange -= 500 * time_step;
		wait(1);
	}
	ent_remove(me);	
}

void eff_expl_flash() {
	int i;
	set(me, BRIGHT | TRANSLUCENT | LIGHT | ZNEAR | PASSABLE);
	my.alpha = 50;
	my.roll = random(360);
	while(my.alpha < 100) {
		my.alpha += time_step * (random(20)+20);
		my.roll += time_step * sign(ang(my.roll));
		vec_fill ( my.scale_x, my.alpha/13 );
		wait(1);		
	}
	for(i=0; i<4; i++) {
		ent_create("explFlash01.tga", my.x, eff_expl_flash_2);
		you = ent_create("explFlash02.tga", my.x, eff_expl_flash_2);		
		if (i == 0) set(you, LIGHT);
	}
	for(i=0; i<5; i++) {
		ent_create ("explSmoke01.tga", my.x, eff_expl_smoke2);
	}
	effect(p_eff_expl_particle, 200, my.x, NULL);
	vec_add(my.scale_x, vector(3,3,3));
	ent_create("explSmoke02.tga", my.x, eff_expl_smoke);
	while(my.alpha > 0) {
		my.alpha -= time_step * 25;
		my.roll += time_step * sign(ang(my.roll));
		wait(1);
	} 
	ent_remove(me);
}

void eff_explosion(VECTOR* _pos) {
	ent_create("explFlash01.tga", _pos, eff_expl_flash);
	ent_create ("explFlash02.tga", _pos, eff_expl_flash);
	ent_create ("explWave01.tga", _pos, eff_expl_wave);
	effect(p_eff_expl_shrapnel, 200, _pos, NULL);
}



// ---------------------------------------------------------------------------
// General functions
// ---------------------------------------------------------------------------

void vec_randomize (VECTOR* _vector, var _range) {
	vec_set(_vector,vector(random(1)-0.5,random(1)-0.5,random(1)-0.5));
	vec_normalize(_vector,random(_range));
}

void pAlphaFade(PARTICLE *p) {
	p.alpha -= p.skill_a*time_step;
	if (p.alpha <= random(10)) {
		p.lifespan = 0;
	}
}

void pAlphaFadeFlame(PARTICLE *p) {
	VECTOR vecTemp;
	vec_lerp(vecTemp, vector(128, 50, 50), vector(200, 180, 100), p.lifespan / 10);
	p.blue = vecTemp.z;
	p.green = vecTemp.y;
	p.blue = vecTemp.x;
	p.alpha = p.lifespan / 10 * 100 * 0.3;
	if (p.alpha <= 0) p.lifespan = 0;
}



// ---------------------------------------------------------------------------
// Further effects
// ---------------------------------------------------------------------------

void pFountain(PARTICLE *p) {
	VECTOR vecTemp;
	vec_randomize(vecTemp, 2);
	vec_add(p.vel_x, vecTemp);
	vec_set(p.blue, vector(random(255), random(255), 255));
	set(p, MOVE | BRIGHT | TRANSLUCENT);
	p.alpha = 100;
	p.size = 2;
	p.gravity = 0.2;
	p.skill_a = 3;
	p.event = pAlphaFade;
}

void pDenseSmoke(PARTICLE *p) {
	VECTOR vecTemp;
	vec_randomize(vecTemp, 2);
	vec_add(p.vel_x, vector(-1+random(2), -1+random(2), 1));
	vec_set(p.blue, vector(140, 140, 140));
	set(p, MOVE | TRANSLUCENT);
	p.alpha = 60 + random(20);
	p.size = 20;
	p.gravity = 0;
	p.skill_a = 1;
	p.event = pAlphaFade;
}

void pStars(PARTICLE *p) {
	VECTOR vecTemp;
	vec_randomize(vecTemp, -1);
	vec_add(p.vel_x, vecTemp);
	vec_set(p.blue, vector(random(255), random(255), 255));
	set(p, MOVE | BRIGHT | TRANSLUCENT);
	p.alpha = 100;
	p.size = 3;
	p.gravity = 1;
	p.skill_a = 3;
	p.bmap = bmapStar;
	p.event = pAlphaFade;
}

void pFlame(PARTICLE *p) {
	VECTOR vecTemp;
	vec_randomize(vecTemp, 2);
	vec_add (p.vel_x, vecTemp);
	p.bmap = bmapFlame;
	set(p, BRIGHT | MOVE | TRANSLUCENT);
	p.lifespan = 10;
	p.size = 10;
	p.event = pAlphaFadeFlame;
}

void pSmokeFlames(PARTICLE *p) {
	VECTOR vecTemp;
	vec_randomize(vecTemp, 2);
	vec_add (p.vel_x, vecTemp);
	p.bmap = bmapSmoke;
	set(p, MOVE | TRANSLUCENT);
	p.lifespan = 10;
	p.size = 10;
	p.event = pAlphaFade;
}


// ---------------------------------------------------------------------------
// Area smoke
// ---------------------------------------------------------------------------
void eff_complexSmokeSprite()
{
	my->flags = TRANSLUCENT;
	my->skill1 = 50;
	wait(1);
	while(my->alpha < my->skill1)
	{
		vec_diff(&my->pan, &my->x, &camera->x);
		vec_to_angle(&my->pan, &my->pan);
		my->roll = total_ticks;
		my->alpha += 0.2 * time_step;
		wait(1);
	}
	while(my->skill2 >= total_ticks || my->skill2 < 0)
	{
		vec_diff(&my->pan, &my->x, &camera->x);
		vec_to_angle(&my->pan, &my->pan);
		my->roll = total_ticks;
		wait(1);
	}
	while(my->alpha > 0)
	{
		vec_diff(&my->pan, &my->x, &camera->x);
		vec_to_angle(&my->pan, &my->pan);
		my->roll = total_ticks;
		my->alpha -= time_step;
		wait(1);
	}
}

void eff_complexSmoke(STRING *smoke, VECTOR* pos, VECTOR* size, var density, var time)
{
	int i;
	var volume = abs(size.x * size.y * size.z);
	for(i = 0; i < 3 * density * (volume / 200000); i++)
	{
		VECTOR spawn;
		spawn.x = random(size.x) - 0.5 * size.x;
		spawn.y = random(size.y) - 0.5 * size.y;
		spawn.z = random(size.z) - 0.5 * size.z;
		vec_add(&spawn, pos);
		
		you = ent_create(smoke, &spawn, eff_complexSmokeSprite);
		you->skill1 = density;
		if(time >= 0)
		you->skill2 = total_ticks + time;
		else
		you->skill2 = -1;
	}
}

/************************************************************
My own implementations (mostly using 3rd party tools,with some tweaks).
************************************************************/

////////////////////////////////////////////////////////////
// Spiral
////////////////////////////////////////////////////////////
void New_Base_Effect_base_event(PARTICLE* p) {
	p.vel_x = sinv(p.skill_d*3.6+180)*p.skill_x;
	p.vel_y = cosv(p.skill_d*3.6)*p.skill_y;
	p.vel_z = p.skill_z;
	p.skill_d = (p.skill_d + time_step*(var)6.000)%100;
}

void New_Base_Effect_base(PARTICLE* p) {
	p.size = 4.000;
	p.alpha = 61.000;
	p.red = 128;
	p.green = 128;
	p.blue = 128;
	p.skill_c = 0.5;
	parted_temp_vec.x = random(6.582)+3.418;
	parted_temp_vec.y = random(7.188)+2.813;
	parted_temp_vec.z = random(6.582)+3.418;
	vec_add(p.x,parted_temp_vec);
	p.vel_x = random(2.598)+(7.402);
	p.vel_y = random(2.793)+(7.207);
	p.vel_z = (3.000);
	p.lifespan = 40.000;
	p.gravity = 0.000;
	p.bmap = point_blue_map;
	p.flags = BRIGHT | BEAM | STREAK | TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = New_Base_Effect_base_event;
}

void emit_spiral() {
	
	my._BEING_MANIPULATED = 0;
	
	my.emask |= ENABLE_CLICK;
	my.event = ObjectManipulationCore;
	
	var eff_frac; eff_frac = 0;
	wait(1);
	while(my) {
		vec_set(parted_temp_vec,nullvector);
		vec_add(parted_temp_vec,my.x);
		eff_frac += 4.000*time_step*6.25;
		if(eff_frac >= 1){
			effect(New_Base_Effect_base,integer(eff_frac),parted_temp_vec,nullvector);
			eff_frac -= integer(eff_frac);
		}
		wait(1);
	}
}

void p_spiral_create(VECTOR *position) {
	if(!position)position = nullvector;
	wait(3);
	you = ent_create(NULL,position,emit_spiral);
	if(you) {
		vec_add(you.x,vector(371.551,349.278,0.000));
		vec_set(you.pan,vector(0.000,0.000,0.000));
		vec_set(you.scale_x,vector(1.000,1.000,1.000));
		set(you,PASSABLE);
		set(you,INVISIBLE);
	}
}

////////////////////////////////////////////////////////////
// Colorful spark
////////////////////////////////////////////////////////////
void Base_Effect_base_event(PARTICLE* p) {
	if(p.lifespan <= 13.000 || (p.skill_a & 1)) {
		p.skill_a |= 1;
		p.alpha = clamp(p.alpha-8.000* time_step,-1,100);
	}
	p.size -= 1.000* time_step;
	if(p.alpha < 0 || p.size < 0) p.lifespan = 0;
	p.vel_x = p.skill_x*p.skill_d/50;
	p.vel_y = p.skill_y*p.skill_d/50;
	p.vel_z = p.skill_z*p.skill_d/50;
	p.skill_d = (p.skill_d + time_step*(var)3.000)%100;
}

void Base_Effect_base(PARTICLE* p) {
	p.size = 29.000;
	p.alpha = 100.000;
	p.red = 128;
	p.green = 128;
	p.blue = 128;
	p.skill_c = 0.5;
	p.vel_x = random(12.000)+(-6.000);
	p.vel_y = random(12.000)+(-6.000);
	p.vel_z = random(12.000)+(-6.000);
	vec_normalize(p.vel_x,10.392);
	p.lifespan = 35.000;
	p.gravity = 0.000;
	p.flags = BRIGHT | BEAM | STREAK | TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = Base_Effect_base_event;
}


void Base_Effect1_base_event(PARTICLE* p) {
	if(p.lifespan <= 13.000 || (p.skill_a & 1)) {
		p.skill_a |= 1;
		p.alpha = clamp(p.alpha-8.000* time_step,-1,100);
	}
	p.size -= 1.000* time_step;
	if(p.alpha < 0 || p.size < 0) p.lifespan = 0;
	p.vel_x = p.skill_x*p.skill_d/50;
	p.vel_y = p.skill_y*p.skill_d/50;
	p.vel_z = p.skill_z*p.skill_d/50;
	p.skill_d = (p.skill_d + time_step*(var)3.000)%100;
}

void Base_Effect1_base(PARTICLE* p) {
	p.size = 29.000;
	p.alpha = 100.000;
	p.red = 228;
	p.green = 62;
	p.blue = 20;
	p.skill_c = 0.5;
	p.vel_x = random(12.000)+(-6.000);
	p.vel_y = random(12.000)+(-6.000);
	p.vel_z = random(12.000)+(-6.000);
	vec_normalize(p.vel_x,10.392);
	p.lifespan = 35.000;
	p.gravity = 0.000;
	p.flags = BRIGHT | BEAM | STREAK | TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = Base_Effect1_base_event;
}

void emit_colorfulspark() {
	
	my._BEING_MANIPULATED = 0;
	
	my.emask |= ENABLE_CLICK;
	my.event = ObjectManipulationCore;
	
	var eff_frac; eff_frac = 0;
	wait(1);
	while(my) {
		parted_temp_vec.x = 0.000;
		parted_temp_vec.y = 0.000;
		parted_temp_vec.z = 0.000;
		vec_add(parted_temp_vec,my.x);
		eff_frac += 5.000*time_step*6.25;
		if(eff_frac >= 1){
			effect(Base_Effect_base,integer(eff_frac),parted_temp_vec,nullvector);
			eff_frac -= integer(eff_frac);
		}
		parted_temp_vec.x = 0.000;
		parted_temp_vec.y = 0.000;
		parted_temp_vec.z = 0.000;
		vec_add(parted_temp_vec,my.x);
		eff_frac += 3.000*time_step*6.25;
		if(eff_frac >= 1){
			effect(Base_Effect1_base,integer(eff_frac),parted_temp_vec,nullvector);
			eff_frac -= integer(eff_frac);
		}
		wait(1);
	}
}

void p_spark_colorful_create(VECTOR *position) {
	if(!position)position = nullvector;
	wait(3);
	you = ent_create(NULL,position,emit_colorfulspark);
	if(you) {
		vec_add(you.x,vector(60.425,91.578,0.000));
		vec_set(you.pan,vector(0.000,0.000,0.000));
		vec_set(you.scale_x,vector(1.000,1.000,1.000));
		set(you,PASSABLE);
		set(you,INVISIBLE);
	}
}

////////////////////////////////////////////////////////////
// Space hole
////////////////////////////////////////////////////////////
void Base_Effect2_base_event(PARTICLE* p) {
	p.alpha = clamp(p.alpha-4.000* time_step,-1,100);
	p.size += 2.000* time_step;
	if(p.lifespan <= 20.000 || (p.skill_a & 4)) {
		p.skill_a |= 4;
		p.vel_x += p.skill_x*2.000* time_step;
		p.vel_y += p.skill_y*2.000* time_step;
		p.vel_z += p.skill_z*2.000* time_step;
	}
	if(p.alpha < 0 || p.size < 0) p.lifespan = 0;
}

void Base_Effect2_base(PARTICLE* p) {
	p.size = 10.000;
	p.alpha = random(27.402)+(33.598);
	p.red = 159;
	p.green = 205;
	p.blue = 227;
	p.skill_c = 0.5;
	p.vel_x = random(4.000)+(-2.000);
	p.vel_y = random(4.000)+(-2.000);
	p.vel_z = random(4.000)+(-2.000);
	p.lifespan = 40.000;
	p.gravity = 0.000;
	p.bmap = sparkle1_map;
	p.flags = BRIGHT | BEAM | TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = Base_Effect2_base_event;
}

void emit_spacehole() {
	
	my._BEING_MANIPULATED = 0;
	
	my.emask |= ENABLE_CLICK;
	my.event = ObjectManipulationCore;
	
	var eff_frac; eff_frac = 0;
	wait(1);
	while(my) {
		parted_temp_vec.x = 0.000;
		parted_temp_vec.y = 0.000;
		parted_temp_vec.z = 0.000;
		vec_add(parted_temp_vec,my.x);
		eff_frac += 6.000*time_step*6.25;
		if(eff_frac >= 1){
			effect(Base_Effect2_base,integer(eff_frac),parted_temp_vec,nullvector);
			eff_frac -= integer(eff_frac);
		}
		wait(1);
	}
}

void p_space_hole_create(VECTOR *position) {
	if(!position)position = nullvector;
	wait(3);
	you = ent_create(NULL,position,emit_spacehole);
	if(you) {
		vec_add(you.x,vector(414.936,660.420,69.408));
		vec_set(you.pan,vector(0.000,0.000,0.000));
		vec_set(you.scale_x,vector(1.000,1.000,1.000));
		set(you,PASSABLE);
		set(you,INVISIBLE);
	}
}

////////////////////////////////////////////////////////////
// Fountain #2
////////////////////////////////////////////////////////////
void Base_Effect15_base_event(PARTICLE* p) {
	p.vel_x = p.skill_x;
	p.vel_y = p.skill_y;
	p.vel_z = p.skill_z-p.skill_z*p.skill_d/50;
	p.skill_d = (p.skill_d + time_step*(var)2.500)%100;
}

void Base_Effect15_base(PARTICLE* p) {
	p.size = random(4.793)+(7.207);
	p.alpha = random(25.457)+(12.543);
	p.red = 69;
	p.green = 124;
	p.blue = 180;
	p.skill_c = 0.5;
	parted_temp_vec.x = random(0.000)+0.000;
	parted_temp_vec.y = random(8.000)+-4.000;
	parted_temp_vec.z = 0.000;
	vec_add(p.x,parted_temp_vec);
	p.vel_x = random(0.539)+(2.461);
	p.vel_y = (0.000);
	p.vel_z = random(1.387)+(8.613);
	vec_normalize(p.vel_x,10.439);
	p.lifespan = 40.000;
	p.gravity = random(0.000)+0.000;
	p.flags = BRIGHT | TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = Base_Effect15_base_event;
}

void Base_Effect14_base_event(PARTICLE* p) {
	p.vel_x = p.skill_x;
	p.vel_y = p.skill_y;
	p.vel_z = p.skill_z-p.skill_z*p.skill_d/50;
	p.skill_d = (p.skill_d + time_step*(var)2.500)%100;
}

void Base_Effect14_base(PARTICLE* p) {
	p.size = random(4.793)+(7.207);
	p.alpha = random(25.457)+(12.543);
	p.red = 69;
	p.green = 124;
	p.blue = 180;
	p.skill_c = 0.5;
	p.vel_x = random(0.449)+(2.051);
	p.vel_y = random(0.180)+(0.820);
	p.vel_z = random(1.387)+(8.613);
	vec_normalize(p.vel_x,10.355);
	p.lifespan = 40.000;
	p.gravity = random(0.000)+0.000;
	p.flags = BRIGHT | TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = Base_Effect14_base_event;
}

void Base_Effect13_base_event(PARTICLE* p) {
	p.vel_x = p.skill_x;
	p.vel_y = p.skill_y;
	p.vel_z = p.skill_z-p.skill_z*p.skill_d/50;
	p.skill_d = (p.skill_d + time_step*(var)2.500)%100;
}

void Base_Effect13_base(PARTICLE* p) {
	p.size = random(4.793)+(7.207);
	p.alpha = random(25.457)+(12.543);
	p.red = 69;
	p.green = 124;
	p.blue = 180;
	p.skill_c = 0.5;
	p.vel_x = random(0.359)+(1.641);
	p.vel_y = random(0.359)+(1.641);
	p.vel_z = random(1.387)+(8.613);
	vec_normalize(p.vel_x,10.392);
	p.lifespan = 40.000;
	p.gravity = random(0.000)+0.000;
	p.flags = BRIGHT | TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = Base_Effect13_base_event;
}

void Base_Effect12_base_event(PARTICLE* p) {
	p.vel_x = p.skill_x;
	p.vel_y = p.skill_y;
	p.vel_z = p.skill_z-p.skill_z*p.skill_d/50;
	p.skill_d = (p.skill_d + time_step*(var)2.500)%100;
}

void Base_Effect12_base(PARTICLE* p) {
	p.size = random(4.793)+(7.207);
	p.alpha = random(25.457)+(12.543);
	p.red = 69;
	p.green = 124;
	p.blue = 180;
	p.skill_c = 0.5;
	p.vel_x = random(0.180)+(0.820);
	p.vel_y = random(0.449)+(2.051);
	p.vel_z = random(1.387)+(8.613);
	vec_normalize(p.vel_x,10.355);
	p.lifespan = 40.000;
	p.gravity = random(0.000)+0.000;
	p.flags = BRIGHT | TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = Base_Effect12_base_event;
}

void Base_Effect11_base_event(PARTICLE* p) {
	p.vel_x = p.skill_x;
	p.vel_y = p.skill_y;
	p.vel_z = p.skill_z-p.skill_z*p.skill_d/50;
	p.skill_d = (p.skill_d + time_step*(var)2.500)%100;
}

void Base_Effect11_base(PARTICLE* p) {
	p.size = random(4.793)+(7.207);
	p.alpha = random(25.457)+(12.543);
	p.red = 69;
	p.green = 124;
	p.blue = 180;
	p.skill_c = 0.5;
	p.vel_x = (0.000);
	p.vel_y = random(0.539)+(2.461);
	p.vel_z = random(1.387)+(8.613);
	vec_normalize(p.vel_x,10.439);
	p.lifespan = 40.000;
	p.gravity = random(0.000)+0.000;
	p.flags = BRIGHT | TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = Base_Effect11_base_event;
}

void emit_fountain2() {
	
	my._BEING_MANIPULATED = 0;
	
	my.emask |= ENABLE_CLICK;
	my.event = ObjectManipulationCore;
	
	var eff_frac; eff_frac = 0;
	wait(1);
	while(my) {
		vec_set(parted_temp_vec,nullvector);
		vec_add(parted_temp_vec,my.x);
		if(!(total_frames % 2)) {
			eff_frac += 2.000*time_step*6.25;
			if(eff_frac >= 1){
				effect(Base_Effect15_base,integer(eff_frac),parted_temp_vec,nullvector);
				eff_frac -= integer(eff_frac);
			}
		}
		parted_temp_vec.x = random(2.000)+-1.000;
		parted_temp_vec.y = random(6.000)+-3.000;
		parted_temp_vec.z = random(0.000)+0.000;
		vec_add(parted_temp_vec,my.x);
		if(!(total_frames % 2)) {
			eff_frac += 2.000*time_step*6.25;
			if(eff_frac >= 1){
				effect(Base_Effect14_base,integer(eff_frac),parted_temp_vec,nullvector);
				eff_frac -= integer(eff_frac);
			}
		}
		parted_temp_vec.x = random(4.000)+-2.000;
		parted_temp_vec.y = random(4.000)+-2.000;
		parted_temp_vec.z = random(0.000)+0.000;
		vec_add(parted_temp_vec,my.x);
		if(!(total_frames % 2)) {
			eff_frac += 2.000*time_step*6.25;
			if(eff_frac >= 1){
				effect(Base_Effect13_base,integer(eff_frac),parted_temp_vec,nullvector);
				eff_frac -= integer(eff_frac);
			}
		}
		parted_temp_vec.x = random(6.000)+-3.000;
		parted_temp_vec.y = random(2.000)+-1.000;
		parted_temp_vec.z = random(0.000)+0.000;
		vec_add(parted_temp_vec,my.x);
		if(!(total_frames % 2)) {
			eff_frac += 2.000*time_step*6.25;
			if(eff_frac >= 1){
				effect(Base_Effect12_base,integer(eff_frac),parted_temp_vec,nullvector);
				eff_frac -= integer(eff_frac);
			}
		}
		parted_temp_vec.x = random(8.000)+-4.000;
		parted_temp_vec.y = random(0.000)+0.000;
		parted_temp_vec.z = random(0.000)+0.000;
		vec_add(parted_temp_vec,my.x);
		if(!(total_frames % 2)) {
			eff_frac += 2.000*time_step*6.25;
			if(eff_frac >= 1){
				effect(Base_Effect11_base,integer(eff_frac),parted_temp_vec,nullvector);
				eff_frac -= integer(eff_frac);
			}
		}
		wait(1);
	}
}

void p_fountain_2_create(VECTOR *position) {
	if(!position)position = nullvector;
	wait(3);
	you = ent_create(NULL,position,emit_fountain2);
	if(you) {
		vec_add(you.x,vector(-20.253,-9.493,0.000));
		vec_set(you.pan,vector(0.000,0.000,0.000));
		vec_set(you.scale_x,vector(1.000,1.000,1.000));
		set(you,PASSABLE);
		set(you,INVISIBLE);
	}
}

////////////////////////////////////////////////////////////
// Fountain #1
////////////////////////////////////////////////////////////
void Base_Effect3_base_event(PARTICLE* p) {
	if (p.lifespan > 20.000) {
		p.skill_a |= 1;
		p.size += 1.000* time_step;
	}
	if((p.lifespan <= 20.000 || (p.skill_a & 2)) && !(p.skill_a & 2)) {
		p.skill_a |= 2;
		p.gravity = 0.399;
	}
	if((p.lifespan <= 30.000 || (p.skill_a & 4)) && p.lifespan > 10.000) {
		p.skill_a |= 4;
		p.vel_x += p.skill_x*1.500* time_step;
	}
	if((p.lifespan <= 30.000 || (p.skill_a & 8)) && p.lifespan > 10.000) {
		p.skill_a |= 8;
		p.vel_y += p.skill_y*1.500* time_step;
	}
	if(p.lifespan <= 20.000 || (p.skill_a & 16)) {
		p.skill_a |= 16;
		p.size -= 1.000* time_step;
	}
	if((p.lifespan <= 6.000 || (p.skill_a & 32)) && !(p.skill_a & 32)) {
		p.skill_a |= 32;
		set(p,STREAK);
	}
	if((p.lifespan <= 6.000 || (p.skill_a & 64)) && !(p.skill_a & 64)) {
		p.skill_a |= 64;
		set(p,BEAM);
	}
	if(p.lifespan <= 10.000 || (p.skill_a & 128)) {
		p.skill_a |= 128;
		p.alpha = clamp(p.alpha-0.500* time_step,-1,100);
	}
	if(p.alpha < 0 || p.size < 0) p.lifespan = 0;
}

void Base_Effect3_base(PARTICLE* p) {
	p.size = 4.000;
	p.alpha = 9.000;
	p.red = 128;
	p.green = 128;
	p.blue = 128;
	p.skill_c = 0.5;
	p.vel_x = random(0.199)+(-0.100);
	p.vel_y = random(0.199)+(-0.100);
	p.vel_z = random(0.875)+(3.125);
	p.lifespan = 40.000;
	p.gravity = 0.000;
	p.bmap = point_blue_map;
	p.flags = BRIGHT | TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = Base_Effect3_base_event;
}


void emit_fountain1() {
	
	my._BEING_MANIPULATED = 0;
	
	my.emask |= ENABLE_CLICK;
	my.event = ObjectManipulationCore;
	
	var my_time;my_time = 0;
	var timetable_num;timetable_num = 0;
	var eff_frac; eff_frac = 0;
	wait(1);
	while(my) {
		my_time += time_step/16;
		if(my_time >= 0.000)my_time = 0;
		timetable_num = 1;
		parted_temp_vec.x = 0.000;
		parted_temp_vec.y = 0.000;
		parted_temp_vec.z = 0.000;
		vec_add(parted_temp_vec,my.x);
		eff_frac += 3.000*timetable_num*time_step*6.25;
		if(eff_frac >= 1){
			effect(Base_Effect3_base,integer(eff_frac),parted_temp_vec,nullvector);
			eff_frac -= integer(eff_frac);
		}
		wait(1);
	}
}

void p_fountain_1_create(VECTOR *position) {
	if(!position)position = nullvector;
	wait(3);
	you = ent_create(NULL,position,emit_fountain1);
	if(you) {
		vec_add(you.x,vector(-200.174,290.466,0.000));
		vec_set(you.pan,vector(0.000,0.000,0.000));
		vec_set(you.scale_x,vector(1.000,1.000,1.000));
		set(you,PASSABLE);
		set(you,INVISIBLE);
	}
}

////////////////////////////////////////////////////////////
// Fire #2
////////////////////////////////////////////////////////////
void New_child2_child_event(PARTICLE* p) {
	p.alpha = clamp(p.alpha-5.000* time_step,-1,100);
	p.size -= 1.000* time_step;
	if(p.alpha < 0 || p.size < 0) p.lifespan = 0;
}

void New_child2_child(PARTICLE* p) {
	p.size = 14.000;
	p.alpha = 100.000;
	p.red = 113;
	p.green = 36;
	p.blue = 0;
	p.skill_c = 0.5;
	p.vel_x = random(2.000)+(-1.000);
	p.vel_y = random(2.000)+(-1.000);
	p.vel_z = (3.000);
	p.lifespan = 40.000;
	p.gravity = 0.000;
	p.flags = BRIGHT | TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = New_child2_child_event;
}

void New_child_child_event(PARTICLE* p) {
	p.size += 2.000* time_step;
	p.alpha = clamp(p.alpha-3.000* time_step,-1,100);
	if(p.alpha < 0 || p.size < 0) p.lifespan = 0;
}

void New_child_child(PARTICLE* p) {
	p.size = 20.000;
	p.alpha = random(45.555)+(22.445);
	p.red = 120;
	p.green = 120;
	p.blue = 120;
	p.skill_c = 0.5;
	p.vel_x = random(1.000)+(-0.500);
	p.vel_y = random(1.000)+(-0.500);
	p.vel_z = random(1.117)+(0.883);
	p.lifespan = 40.000;
	p.gravity = 0.000;
	p.flags = TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = New_child_child_event;
}

void Base_Effect4_base_event(PARTICLE* p) {
	if(p.alpha <= 2.000) {
		parted_temp_vec.x = 0.000;
		parted_temp_vec.y = 0.000;
		parted_temp_vec.z = 0.000;
		vec_add(parted_temp_vec,p.x);
		if(!(total_frames % 6)) {
			p.skill_c += 1.000*time_step*6.25;
			if(p.skill_c >= 1){
				effect(New_child2_child,integer(p.skill_c),parted_temp_vec,nullvector);
				p.skill_c -= integer(p.skill_c);
			}
		}
	}
	if(p.alpha <= 2.000) {
		parted_temp_vec.x = 0.000;
		parted_temp_vec.y = 0.000;
		parted_temp_vec.z = 0.000;
		vec_add(parted_temp_vec,p.x);
		if(!(total_frames % 5)) {
			p.skill_c += 1.000*time_step*6.25;
			if(p.skill_c >= 1){
				effect(New_child_child,integer(p.skill_c),parted_temp_vec,nullvector);
				p.skill_c -= integer(p.skill_c);
			}
		}
	}
	p.size += 0.399* time_step;
	if(p.lifespan <= 32.000 || (p.skill_a & 2)) {
		p.skill_a |= 2;
		p.alpha = clamp(p.alpha-4.000* time_step,-1,100);
	}
	if(p.alpha < 0 || p.size < 0) p.lifespan = 0;
}

void Base_Effect4_base(PARTICLE* p) {
	p.size = random(3.146)+(5.854);
	p.alpha = random(27.535)+(25.465);
	p.red = 255;
	p.green = 128;
	p.blue = 64;
	p.skill_c = 0.5;
	p.vel_x = random(0.287)+(0.013);
	p.vel_y = random(0.281)+(0.019);
	p.vel_z = random(1.246)+(1.153);
	p.lifespan = 50.000;
	p.gravity = 0.000;
	p.bmap = fire3_map;
	p.flags = BRIGHT | TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = Base_Effect4_base_event;
}

void New_effect1_base_event(PARTICLE* p) {
	p.size += 2.000* time_step;
	p.alpha = clamp(p.alpha-3.000* time_step,-1,100);
	if(p.alpha < 0 || p.size < 0) p.lifespan = 0;
}

void New_effect1_base(PARTICLE* p) {
	p.size = 8.000;
	p.alpha = 52.000;
	p.red = 77;
	p.green = 136;
	p.blue = 225;
	p.skill_c = 0.5;
	p.vel_x = random(0.199)+(-0.100);
	p.vel_y = random(0.199)+(-0.100);
	p.vel_z = random(0.781)+(0.618);
	p.lifespan = 40.000;
	p.gravity = 0.000;
	p.flags = TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = New_effect1_base_event;
}

void emit_fire2() {
	
	my._BEING_MANIPULATED = 0;
	
	my.emask |= ENABLE_CLICK;
	my.event = ObjectManipulationCore;
	
	var my_time;my_time = 0;
	var timetable_num;timetable_num = 0;
	var eff_frac; eff_frac = 0;
	wait(1);
	while(my) {
		my_time += time_step/16;
		if(my_time >= 0.000)my_time = 0;
		timetable_num = 1;
		parted_temp_vec.x = random(10.000)+-5.000;
		parted_temp_vec.y = random(10.000)+-5.000;
		parted_temp_vec.z = random(0.000)+0.000;
		vec_add(parted_temp_vec,my.x);
		if(!(total_frames % 2) && timetable_num) {
			eff_frac += 2.000*timetable_num*time_step*6.25;
			if(eff_frac >= 1){
				effect(Base_Effect4_base,integer(eff_frac),parted_temp_vec,nullvector);
				eff_frac -= integer(eff_frac);
			}
		}
		timetable_num = 1;
		parted_temp_vec.x = random(10.000)+-5.000;
		parted_temp_vec.y = random(10.000)+-5.000;
		parted_temp_vec.z = random(0.000)+0.000;
		vec_add(parted_temp_vec,my.x);
		if(!(total_frames % 8) && timetable_num) {
			eff_frac += 1.000*timetable_num*time_step*6.25;
			if(eff_frac >= 1){
				effect(New_effect1_base,integer(eff_frac),parted_temp_vec,nullvector);
				eff_frac -= integer(eff_frac);
			}
		}
		wait(1);
	}
}

void p_fire_2_create(VECTOR *position) {
	if(!position)position = nullvector;
	wait(3);
	you = ent_create(NULL,position,emit_fire2);
	if(you) {
		vec_add(you.x,vector(-200.174,290.466,0.000));
		vec_set(you.pan,vector(0.000,0.000,0.000));
		vec_set(you.scale_x,vector(1.000,1.000,1.000));
		set(you,PASSABLE);
		set(you,INVISIBLE);
	}
}

////////////////////////////////////////////////////////////
// Fire #1
////////////////////////////////////////////////////////////
void New_child_child_event2(PARTICLE* p) {
	p.size += 1.000* time_step;
	p.alpha = clamp(p.alpha-2.000* time_step,-1,100);
	if(p.alpha < 0 || p.size < 0) p.lifespan = 0;
}

void New_child_child2(PARTICLE* p) {
	p.size = 8.000;
	p.alpha = 51.000;
	p.red = 29;
	p.green = 29;
	p.blue = 29;
	p.skill_c = 0.5;
	p.lifespan = 40.000;
	p.gravity = 0.000;
	p.flags = TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = New_child_child_event2;
}

void Base_Effect_base_event2(PARTICLE* p) {
	if(p.alpha <= 1.000) {
		parted_temp_vec.x = 0.000;
		parted_temp_vec.y = 0.000;
		parted_temp_vec.z = 0.000;
		vec_add(parted_temp_vec,p.x);
		parted_temp2_vec.x = random(2.000)+(-1.000);
		parted_temp2_vec.y = random(2.000)+(-1.000);
		parted_temp2_vec.z = (1.000);
		if(!(total_frames % 25)) {
			p.skill_c += 3.000*time_step*6.25;
			if(p.skill_c >= 1){
				effect(New_child_child2,integer(p.skill_c),parted_temp_vec,parted_temp2_vec);
				p.skill_c -= integer(p.skill_c);
			}
		}
	}
	p.alpha = clamp(p.alpha-3.000* time_step,-1,100);
	if(p.size >= 11.000 || (p.skill_a & 2)) {
		p.skill_a |= 2;
		p.size -= 1.000* time_step;
	}
	if(p.size <= 3.000 || (p.skill_a & 4)) {
		p.skill_a |= 4;
		p.size += 1.000* time_step;
	}
	if(p.alpha < 0 || p.size < 0) p.lifespan = 0;
}

void Base_Effect_base2(PARTICLE* p) {
	p.size = random(3.594)+(4.406);
	p.alpha = random(28.750)+(35.250);
	p.red = 128;
	p.green = 128;
	p.blue = 128;
	p.skill_c = 0.5;
	p.lifespan = 40.000;
	p.gravity = 0.000;
	p.bmap = fire1_map;
	p.flags = BRIGHT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = Base_Effect_base_event2;
}

void emit_fire1() {
	
	my._BEING_MANIPULATED = 0;
	
	my.emask |= ENABLE_CLICK;
	my.event = ObjectManipulationCore;
	
	var my_time;my_time = 0;
	var timetable_num;timetable_num = 0;
	var eff_frac; eff_frac = 0;
	wait(1);
	while(my) {
		my_time += time_step/16;
		if(my_time >= 0.000)my_time = 0;
		timetable_num = 1;
		parted_temp_vec.x = random(20.000)+-10.000;
		parted_temp_vec.y = random(20.000)+-10.000;
		parted_temp_vec.z = random(5.098)+-0.098;
		vec_add(parted_temp_vec,my.x);
		parted_temp2_vec.x = random(0.600)+(-0.300);
		parted_temp2_vec.y = random(0.600)+(-0.300);
		parted_temp2_vec.z = random(0.239)+(0.261);
		eff_frac += 2.000*timetable_num*time_step*6.25;
		if(eff_frac >= 1){
			effect(Base_Effect_base2,integer(eff_frac),parted_temp_vec,parted_temp2_vec);
			eff_frac -= integer(eff_frac);
		}
		wait(1);
	}
}

void p_fire_1_create(VECTOR *position) {
	if(!position)position = nullvector;
	wait(3);
	you = ent_create(NULL,position,emit_fire1);
	if(you) {
		vec_add(you.x,vector(-27.054,186.542,14.000));
		vec_set(you.pan,vector(32.498,-25.617,-3.110));
		vec_set(you.scale_x,vector(1.000,1.000,1.000));
		set(you,PASSABLE);
		set(you,INVISIBLE);
	}
}

////////////////////////////////////////////////////////////
// Double Helix
////////////////////////////////////////////////////////////
void Base_Effect_base_event3(PARTICLE* p) {
	if(p.lifespan <= 40.000 || (p.skill_a & 1)) {
		p.skill_a |= 1;
		p.vel_z = -8.000;
		p.skill_z = p.vel_z;
	}
	if(p.alpha < 0 || p.size < 0) p.lifespan = 0;
	p.vel_x = sinv(p.skill_d*3.6+180)*p.skill_x;
	p.vel_y = cosv(p.skill_d*3.6)*p.skill_y;
	p.vel_z = p.skill_z;
	if(p.creator)vec_rotate(p.vel_x,p.creator.pan);
	p.skill_d = (p.skill_d + time_step*(var)11.000)%100;
}

void Base_Effect_base3(PARTICLE* p) {
	p.size = 4.000;
	p.alpha = 64.000;
	p.red = 128;
	p.green = 128;
	p.blue = 128;
	p.skill_c = 0.5;
	p.vel_x = random(2.773)+(17.227);
	p.vel_y = random(3.164)+(16.836);
	p.vel_z = (8.000);
	if(p.creator)vec_rotate(p.vel_x,p.creator.pan);
	p.lifespan = 80.000;
	p.gravity = 0.000;
	p.bmap = blitz1_map;
	p.flags = BRIGHT | STREAK | TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = Base_Effect_base_event3;
}

void Base_Effect1_base_event3(PARTICLE* p) {
	if(p.lifespan <= 40.000 || (p.skill_a & 1)) {
		p.skill_a |= 1;
		p.vel_z = -8.000;
		p.skill_z = p.vel_z;
	}
	if(p.alpha < 0 || p.size < 0) p.lifespan = 0;
	p.vel_x = sinv(p.skill_d*3.6+180)*p.skill_x;
	p.vel_y = cosv(p.skill_d*3.6)*p.skill_y;
	p.vel_z = p.skill_z;
	if(p.creator)vec_rotate(p.vel_x,p.creator.pan);
	p.skill_d = (p.skill_d + time_step*(var)11.000)%100;
}

void Base_Effect1_base3(PARTICLE* p) {
	p.size = 4.000;
	p.alpha = 64.000;
	p.red = 128;
	p.green = 128;
	p.blue = 128;
	p.skill_c = 0.5;
	p.vel_x = random(-2.773)+(-17.227);
	p.vel_y = random(-3.164)+(-16.836);
	p.vel_z = (8.000);
	if(p.creator)vec_rotate(p.vel_x,p.creator.pan);
	p.lifespan = 80.000;
	p.gravity = 0.000;
	p.bmap = blitz1_map;
	p.flags = BRIGHT | STREAK | TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = Base_Effect1_base_event3;
}

void emit_doublehelix() {
	
	my._BEING_MANIPULATED = 0;
	
	my.emask |= ENABLE_CLICK;
	my.event = ObjectManipulationCore;
	
	var my_time;my_time = 0;
	var timetable_num;timetable_num = 0;
	var eff_frac; eff_frac = 0;
	wait(1);
	while(my) {
		my_time += time_step/16;
		if(my_time >= 0.000)my_time = 0;
		timetable_num = 1;
		parted_temp_vec.x = 20.000;
		parted_temp_vec.y = -20.000;
		parted_temp_vec.z = 0.000;
		vec_add(parted_temp_vec,my.x);
		if(!(total_frames % 3) && timetable_num) {
			eff_frac += 1.000*timetable_num*time_step*6.25;
			if(eff_frac >= 1){
				effect(Base_Effect_base3,integer(eff_frac),parted_temp_vec,nullvector);
				eff_frac -= integer(eff_frac);
			}
		}
		timetable_num = 1;
		parted_temp_vec.x = -20.000;
		parted_temp_vec.y = 20.000;
		parted_temp_vec.z = 0.000;
		vec_add(parted_temp_vec,my.x);
		if(!(total_frames % 3) && timetable_num) {
			eff_frac += 1.000*timetable_num*time_step*6.25;
			if(eff_frac >= 1){
				effect(Base_Effect1_base3,integer(eff_frac),parted_temp_vec,nullvector);
				eff_frac -= integer(eff_frac);
			}
		}
		wait(1);
	}
}

void p_double_helix_create(VECTOR *position) {
	if(!position)position = nullvector;
	wait(3);
	you = ent_create(NULL,position,emit_doublehelix);
	if(you) {
		vec_add(you.x,vector(-149.688,31.689,0.000));
		vec_set(you.pan,vector(0.000,0.000,0.000));
		vec_set(you.scale_x,vector(1.000,1.000,1.000));
		set(you,PASSABLE);
		set(you,INVISIBLE);
	}
}

////////////////////////////////////////////////////////////
// Composition
////////////////////////////////////////////////////////////
void star1_base(PARTICLE* p) {
	p.size = 6.000;
	p.alpha = 100.000;
	p.red = 128;
	p.green = 128;
	p.blue = 128;
	p.skill_c = 0.5;
	p.vel_x = random(10.000)+(-5.000);
	p.vel_y = random(10.000)+(-5.000);
	p.vel_z = random(10.000)+(-5.000);
	p.lifespan = 40.000;
	p.gravity = 0.000;
	p.bmap = star1_map;
	p.flags = BRIGHT | TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = NULL;
}

void second_base(PARTICLE* p) {
	p.size = 2.000;
	p.alpha = 100.000;
	p.red = 128;
	p.green = 128;
	p.blue = 128;
	p.skill_c = 0.5;
	p.vel_x = random(6.000)+(-3.000);
	p.vel_y = random(6.000)+(-3.000);
	p.vel_z = random(6.000)+(-3.000);
	p.lifespan = 40.000;
	p.gravity = 0.000;
	p.flags = BRIGHT | TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = NULL;
}

void firstb_base_event(PARTICLE* p) {
	p.alpha = clamp(p.alpha-3.000* time_step,-1,100);
	if(p.alpha < 0 || p.size < 0) p.lifespan = 0;
}

void firstb_base(PARTICLE* p) {
	p.size = 2.000;
	p.alpha = 100.000;
	p.red = 128;
	p.green = 128;
	p.blue = 128;
	p.skill_c = 0.5;
	p.vel_x = random(4.000)+(-2.000);
	p.vel_y = random(4.000)+(-2.000);
	p.vel_z = random(4.000)+(-2.000);
	p.lifespan = 40.000;
	p.gravity = 0.000;
	p.flags = BRIGHT | TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = firstb_base_event;
}

void first_base_event(PARTICLE* p) {
	p.alpha = clamp(p.alpha-5.000* time_step,-1,100);
	if(p.alpha < 0 || p.size < 0) p.lifespan = 0;
}

void first_base(PARTICLE* p) {
	p.size = 2.000;
	p.alpha = 100.000;
	p.red = 128;
	p.green = 128;
	p.blue = 128;
	p.skill_c = 0.5;
	p.vel_x = random(2.000)+(-1.000);
	p.vel_y = random(2.000)+(-1.000);
	p.vel_z = random(4.000)+(-2.000);
	p.lifespan = 40.000;
	p.gravity = 0.000;
	p.flags = BRIGHT | TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = first_base_event;
}

void standard_base(PARTICLE* p) {
	p.size = 4.000;
	p.alpha = 100.000;
	p.red = 128;
	p.green = 128;
	p.blue = 128;
	p.skill_c = 0.5;
	p.vel_x = random(6.000)+(-3.000);
	p.vel_y = random(6.000)+(-3.000);
	p.vel_z = random(6.000)+(-3.000);
	p.lifespan = 40.000;
	p.gravity = 0.000;
	p.flags = BRIGHT | TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = NULL;
}

void sparkleblue_base(PARTICLE* p) {
	p.size = 4.000;
	p.alpha = 100.000;
	p.red = 0;
	p.green = 0;
	p.blue = 255;
	p.skill_c = 0.5;
	p.vel_x = random(6.000)+(-3.000);
	p.vel_y = random(6.000)+(-3.000);
	p.vel_z = random(6.000)+(-3.000);
	p.lifespan = 40.000;
	p.gravity = 0.000;
	p.flags = BRIGHT | TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = NULL;
}

void emit_composition() {
	
	my._BEING_MANIPULATED = 0;
	
	my.emask |= ENABLE_CLICK;
	my.event = ObjectManipulationCore;
	
	var my_time;my_time = 0;
	var timetable_num;timetable_num = 0;
	var eff_frac; eff_frac = 0;
	wait(1);
	while(my) {
		my_time += time_step/16;
		if(my_time >= 0.000)my_time = 0;
		timetable_num = 1;
		parted_temp_vec.x = 0.000;
		parted_temp_vec.y = 0.000;
		parted_temp_vec.z = 0.000;
		vec_add(parted_temp_vec,my.x);
		eff_frac += 4.000*timetable_num*time_step*6.25;
		if(eff_frac >= 1){
			effect(star1_base,integer(eff_frac),parted_temp_vec,nullvector);
			eff_frac -= integer(eff_frac);
		}
		timetable_num = 1;
		parted_temp_vec.x = 0.000;
		parted_temp_vec.y = 0.000;
		parted_temp_vec.z = 0.000;
		vec_add(parted_temp_vec,my.x);
		eff_frac += 1.000*timetable_num*time_step*6.25;
		if(eff_frac >= 1){
			effect(second_base,integer(eff_frac),parted_temp_vec,nullvector);
			eff_frac -= integer(eff_frac);
		}
		timetable_num = 1;
		parted_temp_vec.x = 0.000;
		parted_temp_vec.y = 0.000;
		parted_temp_vec.z = 0.000;
		vec_add(parted_temp_vec,my.x);
		eff_frac += 1.000*timetable_num*time_step*6.25;
		if(eff_frac >= 1){
			effect(firstb_base,integer(eff_frac),parted_temp_vec,nullvector);
			eff_frac -= integer(eff_frac);
		}
		timetable_num = 1;
		parted_temp_vec.x = 0.000;
		parted_temp_vec.y = 0.000;
		parted_temp_vec.z = 0.000;
		vec_add(parted_temp_vec,my.x);
		eff_frac += 1.000*timetable_num*time_step*6.25;
		if(eff_frac >= 1){
			effect(first_base,integer(eff_frac),parted_temp_vec,nullvector);
			eff_frac -= integer(eff_frac);
		}
		timetable_num = 1;
		parted_temp_vec.x = 0.000;
		parted_temp_vec.y = 0.000;
		parted_temp_vec.z = 0.000;
		vec_add(parted_temp_vec,my.x);
		eff_frac += 1.000*timetable_num*time_step*6.25;
		if(eff_frac >= 1){
			effect(standard_base,integer(eff_frac),parted_temp_vec,nullvector);
			eff_frac -= integer(eff_frac);
		}
		timetable_num = 1;
		parted_temp_vec.x = 0.000;
		parted_temp_vec.y = 0.000;
		parted_temp_vec.z = 0.000;
		vec_add(parted_temp_vec,my.x);
		eff_frac += 1.000*timetable_num*time_step*6.25;
		if(eff_frac >= 1){
			effect(sparkleblue_base,integer(eff_frac),parted_temp_vec,nullvector);
			eff_frac -= integer(eff_frac);
		}
		wait(1);
	}
}

void p_composition_create(VECTOR *position) {
	if(!position)position = nullvector;
	wait(3);
	you = ent_create(NULL,position,emit_composition);
	if(you) {
		vec_add(you.x,vector(-141.194,16.143,0.000));
		vec_set(you.pan,vector(0.000,0.000,0.000));
		vec_set(you.scale_x,vector(1.000,1.000,1.000));
		set(you,PASSABLE);
		set(you,INVISIBLE);
	}
}


////////////////////////////////////////////////////////////////////////////

BMAP* particle_tga = "particle.tga";
BMAP* particle2_tga = "particle2.tga";

////////////////////////////////////////////////////////////////////////////

void fade_particle(PARTICLE *p)
{
	p.alpha -= 5 * time_step;
	if (p.alpha < 0) 
	p.lifespan = 0;
}

void particle_void(PARTICLE *p)
{
	vec_add (p.vel_x, vector(1 - random(2), 1 - random(2), 1 + random(1)));
	set(p, MOVE | BRIGHT);
	p.alpha = 30 + random(35);
	p.bmap = particle_tga;
	p.size = 5;
	p.lifespan = 130;
	p.event = fade_particle;
}

void healer_particles()
{
	VECTOR particle_pos[3];
	vec_set (particle_pos.x, my.x);
	particle_pos.z += 70; // place the healing particles above the characters' heads		
	effect(particle_void, 1, particle_pos, nullvector);
}

void player_particles()
{
	VECTOR particle_pos[3];
	vec_set (particle_pos.x, player.x);
	particle_pos.z += 70; // place the healing particles above the characters' heads		
	effect(particle_void, 1, particle_pos, nullvector);
}

void particle_void2(PARTICLE *p)
{
	vec_add (p.vel_x, vector(1 - random(2), 1 - random(2), 0));
	set(p, MOVE | BRIGHT);
	p.alpha = 30 + random(35);
	p.bmap = particle2_tga;
	p.size = 15;
	p.lifespan = 500;
	p.event = fade_particle;
}

void bullet_particles()
{
	VECTOR particle_pos[3];
	vec_set (particle_pos.x, my.x);
	effect(particle_void2, 3, particle_pos, nullvector);
}
// End of particle definition