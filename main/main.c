#include <acknex.h>
#include "ka7def2.c"

// General-purpose gamedata
#define PRAGMA_PATH "./shared/sharedData"

// Objects
#define PRAGMA_PATH "./shared/sharedData/sharedModels"

#define PRAGMA_PATH "./shared/sharedData/sharedModels/sys"
#define PRAGMA_PATH "./shared/sharedData/sharedModels/anms"
#define PRAGMA_PATH "./shared/sharedData/sharedModels/arch"
#define PRAGMA_PATH "./shared/sharedData/sharedModels/blands"
#define PRAGMA_PATH "./shared/sharedData/sharedModels/chars"
#define PRAGMA_PATH "./shared/sharedData/sharedModels/etc"
#define PRAGMA_PATH "./shared/sharedData/sharedModels/food"
#define PRAGMA_PATH "./shared/sharedData/sharedModels/machs"
#define PRAGMA_PATH "./shared/sharedData/sharedModels/plants"
#define PRAGMA_PATH "./shared/sharedData/sharedModels/tportts"

// Levels/Playgrounds/Sandboxes
#define PRAGMA_PATH "./shared/sharedData/sharedLevels"

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
	
	while(1) 
	{
		vec_set(mouse_pos,mouse_cursor);
		
		if(key_t) 
		{
			while(key_t) wait(1);
			obj_type++;
		}
		
		if(key_y) {
			while(key_y) wait(1);
			obj_type--;
		}
		
		if(key_r) {
			
			while(key_r) wait(1);
			you = ent_next(NULL); // Point to the first entity in the list
			while(you) {
				
				ptr_remove(you);
				you = ent_next(you);
				
			}
			
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
				
				if(!is_camera) obj_create();
				
				wait(1);
				
			}
			
			
			
		}

		wait(1);
	}
	
	wait(1);
}