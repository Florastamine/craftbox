#include <acknex.h>
#include <default.c>

#define BBOX 8

ENTITY *select;
var fpsf_alpha_control;

#define PRAGMA_PATH "../shared/sharedData"

#include "../shared/shared.c"
#include "../shared/sharedGUI.c"
#include "../shared/sharedCustom/sharedCustom.c"

int fpsf_obj_type;
BMAP* mouse = "arrow.pcx";

void _my();
void bitch();
void test();
void manipobj();

ENTITY	*fpsf_marker;
VECTOR 	sharedGUI_cpos1,sharedGUI_cpos2,fpsf_temp_pos;

void draw_bounding_box(ENTITY* ent)
{
	VECTOR bounding_box[BBOX];
	int i;
	for(i = 0;i < BBOX;i++) {
		vec_set(bounding_box[i],vector(ent.min_x,ent.min_y,ent.min_z));
		vec_rotate(bounding_box[i],ent.pan);
		vec_add(bounding_box[i],ent.x);
	}
	
	draw_line3d(bounding_box[0],NULL,100);
	for(i = 0;i < BBOX;i++) draw_line3d(bounding_box[i],vector(0,0,255),100);
	
	draw_line3d(bounding_box[4],vector(0,0,255),100);
	draw_line3d(bounding_box[5],vector(0,0,255),100);
	
	draw_line3d(bounding_box[2],NULL,100);
	draw_line3d(bounding_box[6],vector(0,0,255),100);
	
	draw_line3d(bounding_box[3],NULL,100);
	draw_line3d(bounding_box[7],vector(0,0,255),100);
}


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

MATERIAL* mat_select = 
{
	ambient_red=255;
	ambient_green=255;
	ambient_blue=0;
	diffuse_red=255;
	diffuse_green=255;
	diffuse_blue=0;
}

void main(void) {
	
	enable_click = 1;
	
	video_set(800,600,32,2);
	//	shadow_stencil = 0;
	video_window(NULL,NULL,0,"editor 0.1 Milestone 0");
	
	GAMEMODE = GAME_EDITOR;
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
			
			if(mouse_ent)
			{
				if(select)
				{
					select.material = NULL;
					select = NULL;
				}
				select = mouse_ent;
				select.material = mat_select;
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

/*
void flg() {
	if(button_state(flagtest,1,-1) == ON) {
		printf("on");
	} else printf("off");
}
*/

//implement this shit
void _my() {
	draw_bounding_box(my);
	select = you;
	my.emask |= ENABLE_CLICK;
	my.event = bitch;
}

void bitch() {
	error("bitch. fuck you");
}

void test() 
{
	while(1) 
	{
		while(select) 
		{
			proc_mode = PROC_LATE;
			select.alpha = fpsf_alpha_control;
			if(!mouse_left){draw_bounding_box(select);    }
			
			//			printf("%d",select.alpha);
			
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