#include <acknex.h>
#include <default.c>

#define BBOX 8

ENTITY *select;
var fpsf_alpha_control, fpsf_ambient_control, fpsf_albedo_control;

char *ch = '_';

#define PRAGMA_PATH "../shared/sharedData"

#include "../shared/shared.c"
#include "../shared/sharedGUI.c"
#include "../shared/sharedCustom/sharedCustom.c"

int fpsf_obj_type;
BMAP* mouse = "arrow.pcx";

void _my();
void my_event();
void test();
void manipobj();

ENTITY	*fpsf_marker;
VECTOR 	sharedGUI_cpos1,sharedGUI_cpos2,fpsf_temp_pos;

void follow_pointer() {
	fpsf_marker = me;
	set(fpsf_marker,PASSABLE);
	while(1) {
		sharedGUI_cpos1.x = mouse_pos.x;
		sharedGUI_cpos1.y = mouse_pos.y;
		sharedGUI_cpos1.z = 0;
		vec_for_screen(sharedGUI_cpos1,camera);
		sharedGUI_cpos2.x = mouse_pos.x;
		sharedGUI_cpos2.y = mouse_pos.y;
		sharedGUI_cpos2.z = 200000;
		vec_for_screen(sharedGUI_cpos2,camera);
		
		c_trace(sharedGUI_cpos1.x,sharedGUI_cpos2.x,IGNORE_ME | IGNORE_PASSABLE | IGNORE_MODELS);
		vec_set(fpsf_marker.x,hit.x);
		vec_set(fpsf_temp_pos.x,hit.x);
		wait(1);
	}
}

void main(void) {
	
	enable_click = 1;
	
	video_set(800,600,32,2);
	//	shadow_stencil = 0;
	video_window(NULL,NULL,0,"editor 0.1 Milestone 0");
	
	sharedGUI_mouseset(mouse);
	
	sharedGUI_loadbackground();
	
	//	scan_folder("../shared","c");
	//	sharedGUI_release();
	
	ent_create("marker.mdl",nullvector,follow_pointer);
	def_move();
	
	while(1) {
		vec_set(mouse_pos,mouse_cursor);
		manipobj();
		
		if(mouse_left && enable_click != 0) 
		{
			while(mouse_left) wait(1);
			
			if(mouse_ent && enable_click != 0)
			{
				if(select)
				{
					select.material = NULL;
					select = NULL;
				}
				select = mouse_ent;
				select.material = mat_select;
				
				set(select, BRIGHT | TRANSLUCENT);
				
				fpsf_alpha_control = select.alpha;
				fpsf_ambient_control = select.ambient;
				fpsf_albedo_control = select.albedo;
				
				//				if(is(select,BRIGHT)) button_state(panProp_EDITOR_elements,1,1);
				//				if(is(select,INVISIBLE)) button_state(panProp_EDITOR_elements,2,1);
				//				if(is(select,NOFOG)) button_state(panProp_EDITOR_elements,3,1);
				//				if(is(select,OVERLAY)) button_state(panProp_EDITOR_elements,4,1);
				//				if(is(select,PASSABLE)) button_state(panProp_EDITOR_elements,5,1);
				//				if(is(select,POLYGON)) button_state(panProp_EDITOR_elements,6,1);
				//				if(is(select,SHADOW)) button_state(panProp_EDITOR_elements,7,1);
				//				if(is(select,TRANSLUCENT)) button_state(panProp_EDITOR_elements,8,1);
			}
			else
			{
				if(select)
				{
					select.material = NULL;
					select = NULL;
				}
				select = NULL;	
			}
			
			switch(fpsf_obj_type) {
				case 0:
				ent_create("winterbaum.mdl",fpsf_temp_pos.x,NULL);
				break;
				
				case 1:
				ent_create("winterbaum.mdl",fpsf_temp_pos.x,_my);
				break;
				
				default:
				sys_exit(NULL);
				break;
			}
			
			test();
			
		}
		
		/*
		
		if(mouse_right) {
			while(mouse_right) wait(1);
			if(mouse_ent) ent_remove(mouse_ent);
		}
		
		*/
		
		wait(1);
	}
	
	wait(1);
}

void _my() {
	//	draw_bounding_box(my);
	select = you;
	my.emask |= ENABLE_CLICK;
	my.event = my_event;
}

void my_event() {
	error("my_event");
}

void test() 
{
	while(1) 
	{
		while(select) 
		{
			proc_mode = PROC_LATE;
			if(!mouse_left) draw_bounding_box(select);
			
			wait(1);
		}
		wait(1);
	}
}

void manipobj() {
	while(1) {
		
		if(select != NULL) {
			
			if(key_del) {
				while(key_del) wait(1);
				select = NULL;
				select.material = NULL;
				
			}
			
			select.x += .005 * (key_cuu - key_cud) * time_step;
			select.y += .005 * (key_cul - key_cur) * time_step;			
			select.z += .005 * (key_pgup - key_pgdn) * time_step;
			
		}
		
		wait(1);
	}
}