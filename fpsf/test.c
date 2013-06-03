#include<acknex.h>
#include<default.c>

#define PRAGMA_PATH "../shared/sharedData"

BMAP *flag_BIRGHT_EDITOR = "flag_BIRGHT_EDITOR.bmp";
BMAP *flag_BIRGHT_EDITOR_on = "flag_BIRGHT_EDITOR_on.bmp";

BMAP *flag_INVISIBLE_EDITOR = "flag_INVISIBLE_EDITOR.bmp";
BMAP *flag_INVISIBLE_EDITOR_on = "flag_INVISIBLE_EDITOR_on.bmp";

BMAP *flag_NOFOG_EDITOR = "flag_NOFOG_EDITOR.bmp";
BMAP *flag_NOFOG_EDITOR_on = "flag_NOFOG_EDITOR_on.bmp";

BMAP *flag_OVERLAY_EDITOR = "flag_OVERLAY_EDITOR.bmp";
BMAP *flag_OVERLAY_EDITOR_on = "flag_OVERLAY_EDITOR_on.bmp";

BMAP *flag_PASSABLE_EDITOR = "flag_PASSABLE_EDITOR.bmp";
BMAP *flag_PASSABLE_EDITOR_on = "flag_PASSABLE_EDITOR_on.bmp";

BMAP *flag_POLYGON_EDITOR = "flag_POLYGON_EDITOR.bmp";
BMAP *flag_POLYGON_EDITOR_on = "flag_POLYGON_on.bmp";

BMAP *flag_SHADOW_EDITOR = "flag_SHADOW_EDITOR.bmp";
BMAP *flag_SHADOW_EDITOR_on = "flag_SHADOW_EDITOR_on.bmp";

BMAP *flag_TRANSLUCENT_EDITOR = "flag_TRANSLUCENT_EDITOR.bmp";
BMAP *flag_TRANSLUCENT_EDITOR_on = "flag_TRANSLUCENT_EDITOR_on.bmp";


PANEL *panProp_EDITOR_elements = {
	layer = 3;
	size_x = 800;
	size_y = 600;
	
	/* we got 8 buttons ranged from [0..7] */
	button_toggle(0,0,flag_BIRGHT_EDITOR_on,flag_BIRGHT_EDITOR,flag_BIRGHT_EDITOR_on,flag_BIRGHT_EDITOR_on,NULL,NULL,NULL);
	button_toggle(0,0,flag_INVISIBLE_EDITOR_on,flag_INVISIBLE_EDITOR,flag_INVISIBLE_EDITOR_on,flag_INVISIBLE_EDITOR_on,NULL,NULL,NULL);
	button_toggle(0,0,flag_NOFOG_EDITOR_on,flag_NOFOG_EDITOR,flag_NOFOG_EDITOR_on,flag_NOFOG_EDITOR_on,NULL,NULL,NULL);
	button_toggle(0,0,flag_OVERLAY_EDITOR_on,flag_OVERLAY_EDITOR,flag_OVERLAY_EDITOR_on,flag_OVERLAY_EDITOR_on,NULL,NULL,NULL);
	button_toggle(0,0,flag_PASSABLE_EDITOR_on,flag_PASSABLE_EDITOR,flag_PASSABLE_EDITOR_on,flag_PASSABLE_EDITOR_on,NULL,NULL,NULL);
	button_toggle(0,0,flag_POLYGON_EDITOR_on,flag_POLYGON_EDITOR,flag_POLYGON_EDITOR_on,flag_POLYGON_EDITOR_on,NULL,NULL,NULL);
	button_toggle(0,0,flag_SHADOW_EDITOR_on,flag_SHADOW_EDITOR,flag_SHADOW_EDITOR_on,flag_SHADOW_EDITOR_on,NULL,NULL,NULL);
	button_toggle(0,0,flag_TRANSLUCENT_EDITOR_on,flag_TRANSLUCENT_EDITOR,flag_TRANSLUCENT_EDITOR_on,flag_TRANSLUCENT_EDITOR_on,NULL,NULL,NULL);
	flags=OVERLAY | SHOW;
}

void main(void) {
	
	mouse_mode = 2;
	pan_setpos(panProp_EDITOR_elements,3,1,vector(20,20,0));
	pan_setpos(panProp_EDITOR_elements,3,2,vector(20,40,0));
	pan_setpos(panProp_EDITOR_elements,3,3,vector(20,60,0));
	pan_setpos(panProp_EDITOR_elements,3,4,vector(20,80,0));
	pan_setpos(panProp_EDITOR_elements,3,5,vector(20,100,0));
	pan_setpos(panProp_EDITOR_elements,3,6,vector(20,120,0));
	pan_setpos(panProp_EDITOR_elements,3,7,vector(20,140,0));
	pan_setpos(panProp_EDITOR_elements,3,8,vector(20,160,0));
	
	level_load("");
	
	while(1) {
		vec_set(mouse_pos,mouse_cursor);
		wait(1);'
	}
}