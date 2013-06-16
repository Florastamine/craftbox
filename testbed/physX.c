#include <acknex.h>
#include <ackphysX.h>

#include <default.c>

void pX();

function main()
{
	physX_open();
	level_load("physXTest.wmb");
	def_move();
	
	mouse_mode = 4;
	
	while(1) 
	{
		vec_set(mouse_pos,mouse_cursor);
		if(mouse_left) 
		{
			while(mouse_left) wait(1);
			
			if(mouse_ent) 
			{
				ent_create(CUBE_MDL,vector(0,0,0),pX);
			}
		}
		wait(1);
	}  
}

void pX() {   
	pXent_settype(mouse_ent,PH_RIGID,PH_SPHERE);
	pXent_setfriction(mouse_ent,0);
	pXent_setelasticity(mouse_ent,125);
	pXent_setdamping(mouse_ent,10,10);
	pXent_addtorqueglobal(mouse_ent,vector(0,50,0));
}