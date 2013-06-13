#include <acknex.h>
#include <default.c>

#define PRAGMA_PATH "../shared/sharedData"

#include "../shared/shared.c"
#include "../shared/sharedCustom/sharedCustom.c"

void main(void) {
	
	obj_type = 0;
	
	video_set(800,600,32,1);
	video_window(NULL,NULL,0,"editor 0.2 Milestone 1");
	
	sharedGUI_mouseset(mouse);
	
	sharedGUI_loadbackground("small.hmp");
	
	ent_create("marker.mdl",nullvector,follow_pointer);
	def_move();
	
	while(1) 
	{
		vec_set(mouse_pos,mouse_cursor);
		
		if(key_t) 
		{
			while(key_t) wait(1);
			obj_type++;
		}
		
		pass_to_object();
		
		if(mouse_left) 
		{
			while(mouse_left) wait(1);
			
			if(!mouse_panel)
			{
				
				if(mouse_ent)
				{
					if(select)
					{
						select.material = NULL;
						select = NULL;
						something_is_selected = 0;
					}
					select = mouse_ent;
					select.material = mat_select;
					
					something_is_selected = 1;
					
					pass_to_gui(select);
				}
				else
				{
					if(select)
					{
						select.material = NULL;
						select = NULL;
						something_is_selected = 0;
					}
					select = NULL;	
					something_is_selected = 0;
				}
				
				switch(obj_type) 
				{
					
					case obj_winterbaum :
					place_me(o_winterbaum);
					break;
					
					case obj_snowman :
					place_me(o_snowman);
					break;
					
					case obj_genericwall :
					place_me(o_genericwall);
					break;
					
					case obj_generictree :
					place_me(o_generictree);
					break;
					
					case obj_palmtree :
					place_me(o_palmtree);
					break;
					
					default:
					sys_exit(NULL);
					break;
				}
				
			}
			
		}

		wait(1);
	}
	
	wait(1);
}