#include <acknex.h>
#include "ka7def2.c"

#define PRAGMA_PATH "./shared/sharedData"
#define PRAGMA_PATH "./shared/sharedData/sharedModels"
#define PRAGMA_PATH "./shared/sharedData/sharedLevels"

var current = 0;

#include "./shared/shared.c"
#include "./shared/sharedCustom.c"

void main(void)  {
	
	obj_type = 0;
	
	video_set(800,600,32,2);
	video_window(NULL,NULL,0,"editor 0.8 Milestone 4");
	
	sharedGUI_mouseset(mouse);
	
	sharedGUI_loadbackground("sandbox.wmb");
	
	ent_create("marker.mdl",nullvector,follow_pointer);
	def_move();
	
	of_init(burkel,6,"a_burkel.mdl");
	
	while(1) 
	{
		vec_set(mouse_pos,mouse_cursor);
		
		if(key_t) 
		{
			while(key_t) wait(1);
			current++;
		}
		
		if(key_y) {
		   while(key_y) wait(1);
		   current--;
		}
		
		pass_to_object();
		
		if(mouse_left) 
		{
			while(mouse_left) wait(1);
			of_create(burkel);
			
			if(!mouse_panel)
			{
				if(mouse_ent)
				{
					if(select)
					{
						select.material = mat_temp;
						select = NULL;
					}
					
					select = mouse_ent;
					
					mat_temp = select.material; // Luc nay select da duoc xac dinh nen ta cu thoai mai
					select.material = mat_select;
					
					pass_to_gui(select);
					
				}
				
				else
				{
					if(select)
					{
						if(mat_temp) select.material = mat_temp;
						else select.material = NULL;
						
						select = NULL;
						
						reset(panProp,SHOW);
					}
					
					select = NULL;
					
					if(is(panProp,SHOW)) reset(panProp,SHOW);
					
				}
				
				switch(obj_type) 
				{
					
					case obj_winterbaum :
					place_me(o_winterbaum, obj_winterbaum);
					break;
					
					case obj_snowman :
					place_me(o_snowman, obj_snowman);
					break;
					
					case obj_genericwall :
					place_me(o_genericwall, obj_genericwall);
					break;
					
					case obj_generictree :
					place_me(o_generictree, obj_generictree);
					break;
					
					case obj_palmtree :
					place_me(o_palmtree, obj_palmtree);
					break;
					
					default:
					//					error("obj_type wrong/exceed.");
					break;
				}
				wait(1);
				
			}
			
		}

		wait(1);
	}
	
	wait(1);
}