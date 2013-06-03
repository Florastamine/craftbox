PANEL *buttonlst;

TEXT *t_editor_panProp[3];

/*
BMAP *button_New = "button_general.bmp";
BMAP *button_New_Over = "button_general_over.bmp";

BMAP *button_Open = "button_general.bmp";
BMAP *button_Open_Over = "button_general_over.bmp";

BMAP *button_Save = "button_general.bmp";
BMAP *button_Save_Over = "button_general_over.bmp";
*/

BMAP *button_black = "button_black.bmp";

BMAP *button_Copy = "button_general.bmp";
BMAP *button_Copy_Over = "button_general_over.bmp";

BMAP *button_Paste = "button_general.bmp";
BMAP *button_Paste_Over = "button_general_over.bmp";

BMAP *button_Delete = "button_general.bmp";
BMAP *button_Delete_Over = "button_general_over.bmp";

BMAP *button_Move = "button_general.bmp";
BMAP *button_Move_Over = "button_general_over.bmp";

BMAP *button_Rotate = "button_general.bmp";
BMAP *button_Rotate_Over = "button_general_over.bmp";

BMAP *button_Scale = "button_general.bmp";
BMAP *button_Scale_Over = "button_general_over.bmp";

BMAP *button_Prop = "button_general.bmp";
BMAP *button_Prop_Over = "button_general_over.bmp";

BMAP *button_Phy = "button_general.bmp";
BMAP *button_Phy_Over = "button_general_over.bmp";

BMAP *button_Mat = "button_general.bmp";
BMAP *button_Mat_Over = "button_general_over.bmp";

BMAP *button_Home = "button_general.bmp";
BMAP *button_Home_Over = "button_general_over.bmp";

BMAP *button_Cam = "button_general.bmp";
BMAP *button_Cam_Over = "button_general_over.bmp";

BMAP *button_Terrain = "button_general.bmp";
BMAP *button_Terrain_Over = "button_general_over.bmp";

BMAP *button_Objs = "button_general.bmp";
BMAP *button_Objs_Over = "button_general_over.bmp";

BMAP *button_Path = "button_general.bmp";
BMAP *button_Path_Over = "button_general_over.bmp";

BMAP *panHome_EDITOR = "panHome_EDITOR.bmp";
BMAP *panHome_FPS = "panHome_FPS.bmp";
BMAP *panProp_EDITOR = "panProp_EDITOR.bmp";
BMAP *panMat_EDITOR = "panMat_EDITOR.bmp";
BMAP *panPhy_EDITOR = "panPhy_EDITOR.bmp";

BMAP *button_Close = "button_Close.bmp";

BMAP *button_Home_newworld = "button_Home_newworld.bmp";
BMAP *button_Home_loadworld = "button_Home_loadworld.bmp";
BMAP *button_Home_saveworld = "button_Home_saveworld.bmp";
BMAP *button_Home_compileworld = "button_Home_compileworld.bmp";
BMAP *button_Home_configworld = "button_Home_configworld.bmp";
BMAP *button_Home_quitworld = "button_Home_quitworld.bmp";

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

BMAP *slider = "xlider.bmp";

var 
/* buttons which is used for the main HUD. */
button_New_x,
button_Open_x,
button_Save_x,
button_Copy_x,
button_Paste_x,
button_Delete_x,
button_Move_x,
button_Rotate_x,
button_Scale_x,
button_Prop_x,
button_Phy_x,
button_Mat_x,
button_Home_x,			button_Home_y,
button_Cam_x,			button_Cam_y,
button_Terrain_x,		button_Terrain_y,
button_Objs_x,			button_Objs_y,
button_Path_x,			button_Path_y;

PANEL *panProp_EDITOR_elements = {
	layer = 3;
	
	/* we got 8 buttons ranged from [1..8] */
	button_toggle(0,0,flag_BIRGHT_EDITOR_on,flag_BIRGHT_EDITOR,flag_BIRGHT_EDITOR_on,flag_BIRGHT_EDITOR_on,NULL,NULL,NULL);
	button_toggle(0,0,flag_INVISIBLE_EDITOR_on,flag_INVISIBLE_EDITOR,flag_INVISIBLE_EDITOR_on,flag_INVISIBLE_EDITOR_on,NULL,NULL,NULL);
	button_toggle(0,0,flag_NOFOG_EDITOR_on,flag_NOFOG_EDITOR,flag_NOFOG_EDITOR_on,flag_NOFOG_EDITOR_on,NULL,NULL,NULL);
	button_toggle(0,0,flag_OVERLAY_EDITOR_on,flag_OVERLAY_EDITOR,flag_OVERLAY_EDITOR_on,flag_OVERLAY_EDITOR_on,NULL,NULL,NULL);
	button_toggle(0,0,flag_PASSABLE_EDITOR_on,flag_PASSABLE_EDITOR,flag_PASSABLE_EDITOR_on,flag_PASSABLE_EDITOR_on,NULL,NULL,NULL);
	button_toggle(0,0,flag_POLYGON_EDITOR_on,flag_POLYGON_EDITOR,flag_POLYGON_EDITOR_on,flag_POLYGON_EDITOR_on,NULL,NULL,NULL);
	button_toggle(0,0,flag_SHADOW_EDITOR_on,flag_SHADOW_EDITOR,flag_SHADOW_EDITOR_on,flag_SHADOW_EDITOR_on,NULL,NULL,NULL);
	button_toggle(0,0,flag_TRANSLUCENT_EDITOR_on,flag_TRANSLUCENT_EDITOR,flag_TRANSLUCENT_EDITOR_on,flag_TRANSLUCENT_EDITOR_on,sharedGUI_toggle_translucent,NULL,NULL);
	
	hslider(0,0,100,slider,0,100,fpsf_alpha_control);	
	hslider(0,0,100,slider,0,100,test2);	
	hslider(0,0,100,slider,0,100,test3);	
	
	flags=OVERLAY;
}

PANEL *panHome_EDITOR_closebutton = {
	layer = 3;
	button(0,0,button_Close,button_Close,button_Close,sharedGUI_closewindow,NULL,NULL);
}

PANEL *panProp_EDITOR_closebutton = {
	layer = 3;
	button(0,0,button_Close,button_Close,button_Close,sharedGUI_closewindow,NULL,NULL);	
}

PANEL *panPhy_EDITOR_closebutton = {
	layer = 3;
	button(0,0,button_Close,button_Close,button_Close,sharedGUI_closewindow,NULL,NULL);	
}

PANEL *panMat_EDITOR_closebutton = {
	layer = 3;
	button(0,0,button_Close,button_Close,button_Close,sharedGUI_closewindow,NULL,NULL);	
}

/* fuck this shit. i couldn't use arrays to create these buttons
which will result in shorter and much more readable code.
if you're a better lite-C programmer than me, please fix this.*/

PANEL *panHome_EDITOR_elements_button1 = {
	layer = 3;
	button(0,0,button_Home_saveworld,button_Home_saveworld,button_Home_saveworld,NULL,NULL,NULL);
}

PANEL *panHome_EDITOR_elements_button2 = {
	layer = 3;
	button(0,0,button_Home_loadworld,button_Home_loadworld,button_Home_loadworld,NULL,NULL,NULL);
}

PANEL *panHome_EDITOR_elements_button3 = {
	layer = 3;
	button(0,0,button_Home_newworld,button_Home_newworld,button_Home_newworld,NULL,NULL,NULL);
}

PANEL *panHome_EDITOR_elements_button4 = {
	layer = 3;
	button(0,0,button_Home_quitworld,button_Home_quitworld,button_Home_quitworld,NULL,NULL,NULL);
}

PANEL *panHome_EDITOR_elements_button5 = {
	layer = 3;
	button(0,0,button_Home_compileworld,button_Home_compileworld,button_Home_compileworld,NULL,NULL,NULL);
}

PANEL *panHome_EDITOR_elements_button6 = {
	layer = 3;
	button(0,0,button_Home_configworld,button_Home_configworld,button_Home_configworld,NULL,NULL,NULL);
}

PANEL *panHome = {
	layer = 2;
	pos_x = 0;
	pos_y = 0;
	on_click = sharedGUI_dragpanel;
}

PANEL *panProp = {
	layer = 2;
	pos_x = 0;
	pos_y = 0;
	on_click = sharedGUI_dragpanel;
}

PANEL *panPhy = {
	layer = 2;
	pos_x = 0;
	pos_y = 0;
	on_click = sharedGUI_dragpanel;
}

PANEL *panMat = {
	layer = 2;
	pos_x = 0;
	pos_y = 0;
	on_click = sharedGUI_dragpanel;
}

void sharedGUI_updategui(PANEL *wg) {
	//	Elements that is shared among all frameworks
	// 'cause I'm not that greedy man =)).
	
	if(wg == panHome) {
		panHome_EDITOR_closebutton.pos_x = (panHome.pos_x + bmap_width(panHome.bmap)) - 2 * 8 - BORDER/2;
		panHome_EDITOR_closebutton.pos_y = panHome.pos_y + 8 + BORDER/4;
		
		panHome_EDITOR_elements_button1.pos_x = 
		panHome_EDITOR_elements_button2.pos_x = 
		panHome_EDITOR_elements_button3.pos_x = 
		panHome_EDITOR_elements_button4.pos_x = 
		panHome_EDITOR_elements_button5.pos_x = 
		panHome_EDITOR_elements_button6.pos_x = panHome.pos_x + BORDER;//c=10
		
		panHome_EDITOR_elements_button1.pos_y = panHome_EDITOR_closebutton.pos_y + BORDER/1.25; //jump from panHome_EDITOR_closebutton not from panHome	
		panHome_EDITOR_elements_button2.pos_y = panHome_EDITOR_elements_button1.pos_y + bmap_height(button_Home_newworld) + BORDER/4;
		panHome_EDITOR_elements_button3.pos_y = panHome_EDITOR_elements_button2.pos_y + bmap_height(button_Home_newworld) + BORDER/4;
		panHome_EDITOR_elements_button4.pos_y = panHome_EDITOR_elements_button3.pos_y + bmap_height(button_Home_newworld) + BORDER/4;
		panHome_EDITOR_elements_button5.pos_y = panHome_EDITOR_elements_button4.pos_y + bmap_height(button_Home_newworld) + BORDER/4;
		panHome_EDITOR_elements_button6.pos_y = panHome_EDITOR_elements_button5.pos_y + bmap_height(button_Home_newworld) + BORDER/4;
	}
	
	if(wg == panProp) { 
		panProp_EDITOR_closebutton.pos_x = (panProp.pos_x + bmap_width(panProp.bmap)) - 2 * 8 - BORDER/2;
		panProp_EDITOR_closebutton.pos_y = panProp.pos_y + 8 + BORDER/4;	
		
		panProp_EDITOR_elements.pos_x = panProp.pos_x + BORDER/6;
		panProp_EDITOR_elements.pos_y = panProp.pos_y - (23 * 8); // we got 8 buttons, each has its height of 23, so 23 * 8.
		
		//		
		var i = 20, j = 1;
		while( i < 180 && j < 9 ) {
			pan_setpos(panProp_EDITOR_elements,3,j,vector(panProp.pos_x + BORDER,panProp.pos_y + BORDER + i,0));
			i+=20;j++;
		}
		
		var i = 5, j = 1;
		while( i < 20 && j < 4) {
			pan_setpos(panProp_EDITOR_elements,4,j,vector(panProp.pos_x + 102 + (2 * BORDER),panProp.pos_y + (i * BORDER),0));
			i+=5;j++;
		}	
		
		panProp_EDITOR_elements.size_x = 0; // width
		panProp_EDITOR_elements.size_y = 0;//i don't know but that's height.
		
		int i;
		for(i = 0;i < 3;i++) t_editor_panProp[i].pos_x = panProp.pos_x + 102 + (2 * BORDER);
		
		t_editor_panProp[0].pos_y = (panProp.pos_y + (5 * BORDER)) - 15;
		t_editor_panProp[1].pos_y = (panProp.pos_y + (10 * BORDER)) - 15;
		t_editor_panProp[2].pos_y = (panProp.pos_y + (15 * BORDER)) - 15;
		
	}
	
	if(wg == panMat) {
		panMat_EDITOR_closebutton.pos_x = (panMat.pos_x + bmap_width(panMat.bmap)) - 2 * 8 - BORDER/2;
		panMat_EDITOR_closebutton.pos_y = panMat.pos_y + 8 + BORDER/4;			
	}
	
	if(wg == panPhy) {
		panPhy_EDITOR_closebutton.pos_x = (panPhy.pos_x + bmap_width(panPhy.bmap)) - 2 * 8 - BORDER/2;
		panPhy_EDITOR_closebutton.pos_y = panPhy.pos_y + 8 + BORDER/4;			
	}
	
	
	//bitch take this cause i'm not gonna use external variables anymooooore.
	//	pan_setpos(panHome_EDITOR_closebutton,3,2,vector(panHome.pos_x + panHome_EDITOR_closebutton.pos_x));
	
	/*
	if(GAMEMODE == GAME_EDITOR) {
		wait(1);
	}
	
	if(GAMEMODE == GAME_FPS) {
		wait(1);
	}
	
	if(GAMEMODE == GAME_PLATFORM) {
		wait(1);
	}
	
	if(GAMEMODE == GAME_GENERICSHOOTER) {
		wait(1);
	}
	*/
}

/* id always = 1 cuz we don't have two closebuttons at the same time. 
only one PANEL * parameter isn't enough (and it won't work too) so 
this simple ugly hack should do the trick.
*/
void sharedGUI_closewindow(var id, PANEL *p) {
	id = 1;
	
	if(p == panHome_EDITOR_closebutton) {
		if(GAMEMODE == GAME_EDITOR) {
			reset(panHome_EDITOR_closebutton,SHOW);
			reset(panHome,SHOW);
			
			reset(panHome_EDITOR_elements_button1,SHOW);
			reset(panHome_EDITOR_elements_button2,SHOW);
			reset(panHome_EDITOR_elements_button3,SHOW);
			reset(panHome_EDITOR_elements_button4,SHOW);
			reset(panHome_EDITOR_elements_button5,SHOW);
			reset(panHome_EDITOR_elements_button6,SHOW);
			wait(1);
		}
		
		if(GAMEMODE == GAME_FPS) {
			wait(1);
		}
		
		if(GAMEMODE == GAME_PLATFORM) {
			wait(1);
		}
		
		if(GAMEMODE == GAME_GENERICSHOOTER) {
			wait(1);
		}
	}
	
	if(p == panPhy_EDITOR_closebutton) {
		if(GAMEMODE == GAME_EDITOR) {
			reset(panPhy,SHOW);
			reset(panPhy_EDITOR_closebutton,SHOW);
		}
	}
	
	if(p == panMat_EDITOR_closebutton) {
		if(GAMEMODE == GAME_EDITOR) {
			reset(panMat,SHOW);
			reset(panMat_EDITOR_closebutton,SHOW);
		}
	}
	
	if(p == panProp_EDITOR_closebutton) {
		if(GAMEMODE == GAME_EDITOR) {
			
			int i;
			for(i = 0;i < 3;i++) txt_remove(t_editor_panProp[i]);
			
			reset(panProp,SHOW);
			reset(panProp_EDITOR_closebutton,SHOW);
			reset(panProp_EDITOR_elements,SHOW);
			
			enable_click = 1;
		}
	}
}

/*

custom

*/
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
		
		//hack hack hack!!!!
		if(p == panHome) sharedGUI_updategui(panHome);
		if(p == panProp) sharedGUI_updategui(panProp);
		if(p == panPhy) sharedGUI_updategui(panPhy);
		if(p == panMat) sharedGUI_updategui(panMat);
		wait(1);
	}
	
	//hack to prevent shit happens. f.e. after dragged the guis' elements didn't retain their original location.
	if(p == panHome) sharedGUI_updategui(panHome);
	if(p == panProp) sharedGUI_updategui(panProp);
	if(p == panPhy) sharedGUI_updategui(panPhy);
	if(p == panMat) sharedGUI_updategui(panMat);
}

void sharedGUI_centerpanel(PANEL *p) {
	while(p == NULL) wait(1);
	
	p.pos_x = (screen_size.x - bmap_width(p.bmap)) / 2; 
	p.pos_y = (screen_size.y - bmap_height(p.bmap)) / 2;
}

void sharedGUI_loadbuttons() {
	buttonlst.size_x = screen_size.x;
	buttonlst.size_y = screen_size.y;
	
	// Initialize variables use for positioning elements in the panel (X first)
	// Top-left ( left-to-right )
	button_New_x = BORDER;
	button_Open_x = BORDER + SPACE;
	button_Save_x = button_Open_x + SPACE;
	
	// Top-right, ( right-to-left )
	button_Mat_x = screen_size.x - BORDER - (BUTTON_SIZE * 3);
	button_Phy_x = button_Mat_x - (SPACE);
	button_Prop_x = button_Phy_x - (SPACE);
	
	button_Scale_x = button_Prop_x - ((SPACE) * 1.25);
	button_Rotate_x = button_Scale_x - (SPACE);
	button_Move_x = button_Rotate_x - (SPACE);
	
	button_Delete_x = button_Move_x - ((SPACE) * 1.25);
	button_Paste_x = button_Delete_x - (SPACE);
	button_Copy_x = button_Paste_x - (SPACE);
	
	// Down-left ( left-to-right )
	button_Home_x = button_New_x;
	button_Cam_x = button_Open_x;
	button_Terrain_x = button_Save_x;
	button_Objs_x = button_Terrain_x + SPACE;
	button_Path_x = button_Objs_x + SPACE;
	
	// Initialize variables use for positioning elements in the panel (Y)
	// For down-left
	button_Home_y = screen_size.y - BORDER - BUTTON_SIZE;
	
	pan_setpos(buttonlst,3,1,vector(button_New_x,BORDER,0));
	pan_setpos(buttonlst,3,2,vector(button_Open_x,BORDER,0));
	pan_setpos(buttonlst,3,3,vector(button_Save_x,BORDER,0));
	
	pan_setpos(buttonlst,3,12,vector(button_Mat_x,BORDER,0));
	pan_setpos(buttonlst,3,11,vector(button_Phy_x,BORDER,0));
	pan_setpos(buttonlst,3,10,vector(button_Prop_x,BORDER,0));\
	
	pan_setpos(buttonlst,3,9,vector(button_Scale_x,BORDER,0));
	pan_setpos(buttonlst,3,8,vector(button_Rotate_x,BORDER,0));
	pan_setpos(buttonlst,3,7,vector(button_Move_x,BORDER,0));
	
	pan_setpos(buttonlst,3,6,vector(button_Delete_x,BORDER,0));
	pan_setpos(buttonlst,3,5,vector(button_Paste_x,BORDER,0));
	pan_setpos(buttonlst,3,4,vector(button_Copy_x,BORDER,0));
	
	pan_setpos(buttonlst,3,17,vector(button_Home_x,button_Home_y,0));
	pan_setpos(buttonlst,3,16,vector(button_Cam_x,button_Home_y,0));
	pan_setpos(buttonlst,3,15,vector(button_Terrain_x,button_Home_y,0));
	pan_setpos(buttonlst,3,14,vector(button_Objs_x,button_Home_y,0));
	pan_setpos(buttonlst,3,13,vector(button_Path_x,button_Home_y,0));
}

void sharedGUI__loadbuttons() {
	if(is(buttonlst,SHOW)) reset(buttonlst,SHOW);
}

PANEL *buttonlst = {
	size_x = 800;
	size_y = 600;
	layer = 1;
	
	/*
	button(0,0,button_New,button_New,button_New_Over,NULL,NULL,NULL);
	button(0,0,button_Open,button_Open,button_Open_Over,NULL,NULL,NULL);
	button(0,0,button_Save,button_Save,button_Save_Over,NULL,NULL,NULL);
	*/
	
	button(0,0,button_black,button_black,button_black,NULL,NULL,NULL);
	button(0,0,button_black,button_black,button_black,NULL,NULL,NULL);
	button(0,0,button_black,button_black,button_black,NULL,NULL,NULL);
	
	button(0,0,button_Copy,button_Copy,button_Copy_Over,NULL,NULL,NULL);
	button(0,0,button_Paste,button_Paste,button_Paste_Over,NULL,NULL,NULL);
	button(0,0,button_Delete,button_Delete,button_Delete_Over,NULL,NULL,NULL);
	
	button(0,0,button_Move,button_Move,button_Move_Over,NULL,NULL,NULL);
	button(0,0,button_Rotate,button_Rotate,button_Rotate_Over,NULL,NULL,NULL);
	button(0,0,button_Scale,button_Scale,button_Scale_Over,NULL,NULL,NULL);
	
	button(0,0,button_Prop,button_Prop,button_Prop_Over,sharedGUI_prop,NULL,NULL);
	button(0,0,button_Phy,button_Phy,button_Phy_Over,sharedGUI_phy,NULL,NULL);
	button(0,0,button_Mat,button_Mat,button_Mat_Over,sharedGUI_mat,NULL,NULL);
	
	button(0,0,button_Path,button_Path,button_Path_Over,NULL,NULL,NULL);
	button(0,0,button_Objs,button_Objs,button_Objs_Over,NULL,NULL,NULL);
	button(0,0,button_Terrain,button_Terrain,button_Terrain_Over,NULL,NULL,NULL);
	button(0,0,button_Cam,button_Cam,button_Cam_Over,NULL,NULL,NULL);
	button(0,0,button_Home,button_Home,button_Home_Over,sharedGUI_home,NULL,NULL);
	
	flags = OVERLAY | SHOW;
}

//panel_set
STRING *sharedGUI_releaseStr = "                       ";

TEXT *sharedGUI_releaseTEXT = {
	string(sharedGUI_releaseStr);
	font = "Arial#25b";
}

PANEL *_logo = {
	bmap = "_logo.bmp";
	flags = OVERLAY;	
}

PANEL *blackscreen = {
	bmap = "bitmap.bmp";
}

PANEL *blackpix = {
	bmap = "black.bmp";
}

void sharedGUI_loadscene(STRING *s) {
	level_load(s);
}

void sharedGUI_rescale(PANEL *p) {
	while(p == NULL) wait(1);
	
	p.pos_x = 0;
	p.pos_y = 0;
	
	p.scale_x = screen_size.x/bmap_width(p.bmap);
	p.scale_y = screen_size.y/bmap_height(p.bmap);
}

void sharedGUI_blackscreen(int mode, int sec) {
	sharedGUI_rescale(blackscreen);
	set(blackscreen,SHOW);
	
	if(mode == FADE_IN) {
		set(blackscreen,TRANSLUCENT);
		blackscreen->alpha = 0;
		
		wait(-sec);
		
		while(blackscreen->alpha <= 100) {
			blackscreen->alpha += 10 * time_step;
			wait(1);
		}
		
		blackscreen->alpha = 100;
		
	}
	
	if(mode == FADE_OUT) {
		if(!is(blackscreen,SHOW)) set(blackscreen,SHOW);
		set(blackscreen,TRANSLUCENT);
		blackscreen->alpha = 100;
		
		wait(-sec);
		
		while(blackscreen->alpha >= 0) {
			blackscreen->alpha -= 10 * time_step;
			wait(1);
		}
		
		blackscreen->alpha = 0;
		reset(blackscreen,SHOW);
		
	}
}

void sharedGUI_loadlogo() {
	// Initial setup	
	_logo->size_x = bmap_width(_logo.bmap);
	_logo->size_y = bmap_height(_logo.bmap);
	
	_logo->pos_x = screen_size.x - bmap_width(_logo.bmap) - 25;
	_logo->pos_y = 25;
	
	if(GAMEMODE == GAME_EDITOR)				set(_logo,SHOW);
	if(GAMEMODE == GAME_FPS)					set(_logo,SHOW);
	if(GAMEMODE == GAME_PLATFORM)				set(_logo,SHOW);
	if(GAMEMODE == GAME_GENERICSHOOTER)		set(_logo,SHOW);
}

void sharedGUI__loadlogo() {
	if(is(_logo,SHOW)) reset(_logo,SHOW);
}

void sharedGUI_release() {
	if(GAMEMODE == GAME_EDITOR)				str_cpy(sharedGUI_releaseStr,"Editor");
	if(GAMEMODE == GAME_FPS)					str_cpy(sharedGUI_releaseStr,"FPS");
	if(GAMEMODE == GAME_PLATFORM)				str_cpy(sharedGUI_releaseStr,"Platform");
	if(GAMEMODE == GAME_GENERICSHOOTER)		str_cpy(sharedGUI_releaseStr,"Generic Shooter");
	
	sharedGUI_releaseTEXT->pos_x = screen_size.x - str_width(sharedGUI_releaseStr,"Arial#25b");
	sharedGUI_releaseTEXT->pos_y = screen_size.y - str_width(sharedGUI_releaseStr,"Arial#25b");
	
	set(sharedGUI_releaseTEXT,SHOW);
}

void sharedGUI__release() {
	if(is(sharedGUI_releaseTEXT,SHOW)) reset(sharedGUI_releaseTEXT,SHOW);
	str_cpy(sharedGUI_releaseStr,"");
}

void sharedGUI_playintro(int vol) {
	proc_kill(4);
	
	var hndl;
	if(GAMEMODE == GAME_EDITOR) hndl = media_play("",NULL,100);
	if(GAMEMODE == GAME_FPS) hndl = media_play("",NULL,vol);
	if(GAMEMODE == GAME_PLATFORM) hndl = media_play("",NULL,vol);
	if(GAMEMODE == GAME_GENERICSHOOTER) hndl = media_play("",NULL,vol);
	
	while(media_playing(hndl)) wait(1);
}

int instance;
PANEL *inst = {
	layer=25;
	digits(0,0,99,"Arial#25b",1,instance);
	flags=SHOW;
}

void sharedGUI_loadbackground() {
	if(GAMEMODE == GAME_EDITOR) {
		
		//		sharedGUI_playintro(100);
		//		wait_for(sharedGUI_playintro);
		
		sharedGUI_loadscene("small.hmp");
		wait_for(sharedGUI_loadscene);
		
		sharedGUI_loadbuttons();
		wait_for(sharedGUI_loadbuttons);
		
		sharedGUI_blackscreen(FADE_OUT,2);
		wait_for(sharedGUI_blackscreen);
		
		sharedGUI_mouse(ON);
	}
}

void sharedGUI_mouse(int mode) {
	if(mode == OFF) mouse_mode = 0;
	if(mode == ON) mouse_mode = 4;
}

void sharedGUI_mouseset(BMAP *b) {
	mouse_map = b;
}

void sharedGUI_home() {
	if(GAMEMODE == GAME_EDITOR) {
		panHome.bmap = panHome_EDITOR;
		
		sharedGUI_centerpanel(panHome);
		sharedGUI_updategui(panHome);
		
		set(panHome,SHOW);
		set(panHome_EDITOR_closebutton,SHOW);
		set(panHome_EDITOR_elements_button1,SHOW);
		set(panHome_EDITOR_elements_button2,SHOW);
		set(panHome_EDITOR_elements_button3,SHOW);
		set(panHome_EDITOR_elements_button4,SHOW);
		set(panHome_EDITOR_elements_button5,SHOW);
		set(panHome_EDITOR_elements_button6,SHOW);
	}
	
	if(GAMEMODE == GAME_FPS) {
		panHome.bmap = panHome_FPS;
		set(panHome,SHOW);
	}
	
	if(GAMEMODE == GAME_PLATFORM) {
		wait(1);
	}
	
	if(GAMEMODE == GAME_GENERICSHOOTER) {
		wait(1);
	}
}

void sharedGUI_prop() {
	if(GAMEMODE == GAME_EDITOR) {
		enable_click = 0;
		
		int i;
		for(i = 0;i < 3;i++) {
			t_editor_panProp[i] = txt_create(1,3);
			t_editor_panProp[i].font = f;
		}
		
		str_cpy((t_editor_panProp[0].pstring)[0],"Alpha");
		str_cpy((t_editor_panProp[1].pstring)[0],"Ambient");
		str_cpy((t_editor_panProp[2].pstring)[0],"Albedo");
		
		panProp.bmap = panProp_EDITOR;
		
		panProp.pos_x = BORDER;
		panProp.pos_y = screen_size.y - (2 * BORDER) - 32 - bmap_height(panProp.bmap);
		
		sharedGUI_updategui(panProp);
		
		set(panProp,SHOW);
		set(panProp_EDITOR_closebutton,SHOW);
		set(panProp_EDITOR_elements,SHOW);
		
		int i; for(i = 0;i < 3;i++) set(t_editor_panProp[i],SHOW);
	}
	
	if(GAMEMODE == GAME_FPS) {
		wait(1);
	}
	
	if(GAMEMODE == GAME_PLATFORM) {
		wait(1);
	}
	
	if(GAMEMODE == GAME_GENERICSHOOTER) {
		wait(1);
	}
}

void sharedGUI_mat() {
	if(GAMEMODE == GAME_EDITOR) {
		panMat.bmap = panMat_EDITOR;
		
		sharedGUI_centerpanel(panMat);
		sharedGUI_updategui(panMat);
		
		set(panMat,SHOW);
		set(panMat_EDITOR_closebutton,SHOW);
	}
	
	if(GAMEMODE == GAME_FPS) {
		wait(1);
	}
	
	if(GAMEMODE == GAME_PLATFORM) {
		wait(1);
	}
	
	if(GAMEMODE == GAME_GENERICSHOOTER) {
		wait(1);
	}
}

void sharedGUI_phy() {
	if(GAMEMODE == GAME_EDITOR) {
		panPhy.bmap = panPhy_EDITOR;
		
		sharedGUI_centerpanel(panPhy);
		sharedGUI_updategui(panPhy);
		
		set(panPhy,SHOW);
		set(panPhy_EDITOR_closebutton,SHOW);
		
	}
	
	if(GAMEMODE == GAME_FPS) {
		wait(1);
	}
	
	if(GAMEMODE == GAME_PLATFORM) {
		wait(1);
	}
	
	if(GAMEMODE == GAME_GENERICSHOOTER) {
		wait(1);
	}
}

void sharedGUI_toggle_translucent() {
	if(button_state(panProp_EDITOR_elements,8,-1) == ON)
	{
		if(!select) {
			set(select,TRANSLUCENT);
			button_state(panProp_EDITOR_elements,8,1);
		}
	}
}