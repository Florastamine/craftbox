#include <acknex.h>
#include "ka7def2.c"

//////////////////////////////////////////////////////////////
#define PRAGMA_PATH "./src"
#define PRAGMA_PATH "./src/cfg"
#define PRAGMA_PATH "./src/txt"

#define PRAGMA_PATH "./2d/gui"
#define PRAGMA_PATH "./2d/tex"

#define PRAGMA_PATH "./objects/sys"
#define PRAGMA_PATH "./objects/anms"
#define PRAGMA_PATH "./objects/arch"
#define PRAGMA_PATH "./objects/blands"
#define PRAGMA_PATH "./objects/chars"
#define PRAGMA_PATH "./objects/etc"
#define PRAGMA_PATH "./objects/food"
#define PRAGMA_PATH "./objects/machs"
#define PRAGMA_PATH "./objects/plants"
#define PRAGMA_PATH "./objects/tportts"

#define PRAGMA_PATH "./sounds"
#define PRAGMA_PATH "./sounds/music"

#define PRAGMA_PATH "./levels"
//////////////////////////////////////////////////////////////

#include "header.h"
#include "data.c"
#include "kernel.c"

void main(void)  {
	
	video_set(800,600,32,2);
	video_window(NULL,NULL,0,"editor 0.8 Milestone 4");
	
	sharedGUI_loadbackground("sandbox.wmb");
	
	ent_create("marker.mdl",nullvector,follow_pointer);
	//	def_move();
	
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
				if(!is_camera) obj_create();
				
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
				
				wait(1);
				
			}
			
			
			
		}

		wait(1);
	}
	
	wait(1);
}