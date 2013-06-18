#include <acknex.h>
#include <default.c>

#define PRAGMA_PATH "./shared/sharedData"
#define PRAGMA_PATH "./shared/sharedData/sharedModels"
#define PRAGMA_PATH "./shared/sharedData/sharedLevels"

#include "./shared/shared.c"
#include "./shared/sharedCustom.c"

void main(void)  {
   	
	obj_type = 0;
	
	video_set(800,600,32,2);
	video_window(NULL,NULL,0,"editor 0.5 Milestone 2");
	
	sharedGUI_mouseset(mouse);
	
	sharedGUI_loadbackground("sandbox.wmb");
	
	ent_create("marker.mdl",nullvector,follow_pointer);
	def_move();
	
	// process all entities within the level
	you = ent_next(NULL);
	int t;
	while(you) {

		t = (int)random(3);
		if(t == 0) you.material = mat_lava;
		if(t == 1) you.material = mat_smaragd;
		if(t == 2) you.material = mat_marble;
		
		you = ent_next(you);
		
		wait(1);
	}
	
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
					error("obj_type wrong/exceed.");
					break;
				}
				wait(1);
				
			}
			
		}

		wait(1);
	}
	
	wait(1);
}