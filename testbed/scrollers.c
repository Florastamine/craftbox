#include <acknex.h>
#include <default.c>

BMAP *mouse = "../main/shared/sharedData/arrow.pcx";
void sharedGUI_dragpanel(PANEL *);

var test;

PANEL *pmain = {
	
	layer = 1;
	
	bmap = "panAddObject.bmp";
	pos_x = 15;
	pos_y = 15;
	
	flags = SHOW;
	
	//	on_click = sharedGUI_dragpanel;
	
}

PANEL *slider = {
	
	layer = 2;
	bmap = "slider.bmp";
	
	vslider(0,0,503,"sliderk.bmp",0,503,test);
	
	flags=SHOW;
	
}

PANEL *blackup = {
   
   layer = 3;
   bmap = "blackup.bmp";
   flags=SHOW | TRANSLUCENT;
      
}

PANEL *blackdown = {
   
   layer = 3;;
   bmap = "blackup.bmp";
   flags=SHOW;
   
}

PANEL *psub = {
	
	layer = 2;
	
	bmap = "panAddObject_in.bmp";
	pos_x = 0;
	pos_y = 0;
	
	flags = OVERLAY | SHOW;
	
}

void sharedGUI_dragpanel(PANEL *p)
{
	var click_offset[2];
	
	click_offset[0]=p.pos_x - mouse_pos.x;
	click_offset[1]=p.pos_y - mouse_pos.y;
	
	while(mouse_left)
	{
		proc_mode = PROC_EARLY;
		
		p.pos_x = mouse_pos.x+click_offset[0];
		p.pos_y = mouse_pos.y+click_offset[1];
		
		wait(1);
	}
}

void main(void) {
	
	video_set(800,600,32,1);
	mouse_mode = 2;
	mouse_map = mouse;
	
	level_load("");
	
	while(1) {
		
		vec_set(mouse_pos,mouse_cursor);
		
		psub.pos_y = test;
		
		psub.pos_x = pmain.pos_x + 10;
		//		psub.pos_y = pmain.pos_y + 10;		
		slider.pos_x = bmap_width(pmain.bmap) + 30;
		slider.pos_y = pmain.pos_y;
		
		blackup.pos_x = pmain.pos_x;
		blackup.pos_y = pmain.pos_y;
		
		blackdown.pos_x = pmain.pos_y;
		blackdown.pos_y = bmap_height(pmain.bmap);
		
		wait(1);
		
	} 
}