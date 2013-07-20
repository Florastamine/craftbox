ENTITY *e;
SOUND *step = "step.wav";

PANEL *A = {
   
   bmap="A_CROW.bmp";
   flags=OVERLAY | SHOW;
}

PANEL *render={
	bmap="render.bmp";
	flags=OVERLAY | SHOW;
}

function flash()
{
	e = me;
	
	proc_mode = PROC_LATE;
	set(e,PASSABLE | SPOTLIGHT | CAST | LIGHT);
	e.lightrange = 4500;
	vec_set(e.blue,vector(255,100,100));
	
	while(1)
	{
		if(key_t) e.lightrange += 25;
		if(key_y) e.lightrange -= 25;
		
		e.x = player.x + 15 * cos(player.pan) + 20 * sin(player.pan);
		e.y = player.y + 50 * sin(player.pan) - 20 * cos(player.pan);
		e.z = player.z + 10; 
		e.pan = player.pan;
		e.tilt = player.tilt;
		e.roll = player.roll;
		wait(1);
	}
}

action players_code() // attach this action to your player model in all the levels

{

	var movement_speed = 10; // movement speed

	VECTOR temp;

	set (my, INVISIBLE); // 1st person player

	player = my; // I'm the player

	e = 	ent_create("cube.mdl",player.x,flash);

	// end of the section that recreates the flashlight (if needed)
	VECTOR v1,v2;
	var hndl;
	

	while (1)

	{

		my.pan -= 7 * mouse_force.x * time_step;
		my.tilt += 5 * mouse_force.y * time_step;
		
		camera.x = my.x;

		camera.y = my.y;

		camera.z = my.z + 50 + 1.1 * sin(my.skill44); // play with 50 and 1.1

		camera.pan = my.pan;
		camera.tilt = my.tilt;
		camera.roll = my.roll;

		vec_set (temp.x, my.x); // trace 10,000 quants below the player

		temp.z -= 10000;
		temp.z = -c_trace (my.x, temp.x, IGNORE_ME | IGNORE_PASSABLE | USE_BOX) - 2; // play with 2
		temp.x = movement_speed * (key_w - key_s) * time_step;

		temp.y = movement_speed * (key_a - key_d) * 0.6 * time_step;

		c_move (my, temp.x, nullvector, IGNORE_PASSABLE | GLIDE);

		
		v1.x = my.x;
		v1.y = my.y;
		v1.z = my.z;
		
		wait(2);
		
		v2.x = my.x;
		v2.y = my.y;
		v2.z = my.z;
		
		if(v1.x!=v2.x || v1.y!=v2.y||v1.z!=v2.z) {
			
			//			while(snd_playing(hndl)) wait(1);
			printf("gay");
			
		}

		wait (1);

	}

}

void main(void){
	
	level_load("test.wmb");
}