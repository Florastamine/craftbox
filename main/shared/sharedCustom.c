MATERIAL *mat_smaragd = {
	ambient_red = 100;
	ambient_green = 255;
	ambient_blue = 100;
	diffuse_red = 0;
	diffuse_green = 100;
	diffuse_blue = 0;
	specular_red = 255;
	specular_green = 255;
	specular_blue = 255;
	power = 10;
}

MATERIAL *mat_lava = {
	emissive_red = 200;
	emissive_green = 70;
	emissive_blue = 20;
	ambient_red = 255;
	ambient_green = 150;
	ambient_blue = 50;
	diffuse_red = 200;
	diffuse_green = 150;
	diffuse_blue = 50;
	specular_red = 255;
	specular_green = 255;
	specular_blue = 255;
	alpha = 60;
	albedo = 70;
	power = 10;
}

MATERIAL *mat_marble = {
	emissive_red = 30;
	emissive_green = 30;
	emissive_blue = 30;
	ambient_red = 200;
	ambient_green = 225;
	ambient_blue = 200;
	diffuse_red = 255;
	diffuse_green = 255;
	diffuse_blue = 255;
	specular_red = 255;
	specular_green = 255;
	specular_blue = 255;
	power = 10;
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

TEXT* files_list = 
{ 
	strings = 1000; 
	pos_x = 0;
	pos_y = 0;
	font = "Arial#25b";
	flags=SHOW;
}

/*
void main(void) {
	//	CreateDirectory("cd",0);
	scan_folder("sharedData","pcx");
}
*/

void scan_folder(STRING *dir, STRING *ext)
{
	TEXT* read_files = {strings = 1000;}
	
	STRING* search_form = "a";

	str_cpy(current_folder,dir);

	str_cpy(search_form,dir);
	str_cat(search_form,"\\*.");
	str_cat(search_form,ext);
	
	files_found = txt_for_dir(read_files, search_form);
	
	var num = files_already;
	while(num<999)
	{
		str_cpy((files_list.pstring)[num],"");
		num+=1;
	}
	
	num=0;
	while(num<files_found)
	{
		str_cpy((files_list.pstring)[num+files_already],(read_files.pstring)[num]);
		num+=1;
	}
	list_start=0;
	
	wait(1);
}


void draw_bounding_box(ENTITY *ent)
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


PANEL *buttonlst_submenu_terrain = {
	layer = 1;
	
	bmap = "button_submenu_black.bmp";
	
	button(0,0,menu1_submenu1,menu1_submenu1_off,menu1_submenu1_over,NULL,NULL,NULL);
	button(0,0,menu1_submenu2,menu1_submenu2_off,menu1_submenu2_over,NULL,NULL,NULL);
	button(0,0,menu1_submenu3,menu1_submenu3_off,menu1_submenu3_over,NULL,NULL,NULL);
	button(0,0,menu1_submenu4,menu1_submenu4_off,menu1_submenu4_over,NULL,NULL,NULL);
	
	// The final button will be the back button.
	button(0,0,button_back,button_back,button_back_over,sharedGUI_closewindow,NULL,NULL);
	
	flags = OVERLAY;
}

PANEL *buttonlst_submenu_object = {
	layer = 1;
	
	bmap = "button_submenu_black.bmp";
	
	button(0,0,menu2_submenu1,menu2_submenu1_off,menu2_submenu1_over,NULL,NULL,NULL);
	button(0,0,menu2_submenu2,menu2_submenu2_off,menu2_submenu2_over,NULL,NULL,NULL);
	//	button(0,0,menu2_submenu3,menu2_submenu3,menu2_submenu3,NULL,NULL,NULL);
	//	button(0,0,menu2_submenu4,menu2_submenu4,menu2_submenu4,NULL,NULL,NULL);
	
	button(0,0,button_back,button_back,button_back_over,sharedGUI_closewindow,NULL,NULL);
	
	flags = OVERLAY;
}

PANEL *buttonlst_submenu_path = {
	layer = 1;
	
	bmap = "button_submenu_black.bmp";
	
	button(0,0,menu3_submenu1,menu3_submenu1_off,menu3_submenu1_over,NULL,NULL,NULL);
	button(0,0,menu3_submenu2,menu3_submenu2_off,menu3_submenu2_over,NULL,NULL,NULL);
	//	button(0,0,menu3_submenu3,menu3_submenu3,menu3_submenu3,NULL,NULL,NULL);
	//	button(0,0,menu3_submenu4,menu3_submenu4,menu3_submenu4,NULL,NULL,NULL);
	
	button(0,0,button_back,button_back,button_back_over,sharedGUI_closewindow,NULL,NULL);
	
	flags = OVERLAY;
}

PANEL *panHome = {
	layer = 2;
	
	bmap = "panHome.bmp";
	
	button(0,0,button_Close,button_Close_off,button_Close_over,sharedGUI_closewindow,NULL,NULL);
	
	button(0,0,button_Home_saveworld,button_Home_saveworld_off,button_Home_saveworld_over,NULL,NULL,NULL);
	button(0,0,button_Home_loadworld,button_Home_loadworld_off,button_Home_loadworld_over,NULL,NULL,NULL);
	button(0,0,button_Home_newworld,button_Home_newworld_off,button_Home_newworld_over,NULL,NULL,NULL);
	button(0,0,button_Home_quitworld,button_Home_quitworld_off,button_Home_quitworld_over,NULL,NULL,NULL);
	button(0,0,button_Home_compileworld,button_Home_compileworld_off,button_Home_compileworld_over,NULL,NULL,NULL);
	button(0,0,button_Home_configworld,button_Home_configworld_off,button_Home_configworld_over,NULL,NULL,NULL);
	
	on_click = sharedGUI_dragpanel;
	
	flags = OVERLAY | TRANSLUCENT;
}

PANEL *panProp = {
	layer = 2;
	
	bmap = "panProp.bmp";
	
	button(0,0,button_Close,button_Close_off,button_Close_over,sharedGUI_closewindow,NULL,NULL);
	
	button_toggle(0,0,flag_BIRGHT_on,flag_BIRGHT,flag_BIRGHT_on,flag_BIRGHT_on,NULL,NULL,NULL);
	button_toggle(0,0,flag_INVISIBLE_on,flag_INVISIBLE,flag_INVISIBLE_on,flag_INVISIBLE_on,NULL,NULL,NULL);
	button_toggle(0,0,flag_NOFOG_on,flag_NOFOG,flag_NOFOG_on,flag_NOFOG_on,NULL,NULL,NULL);
	button_toggle(0,0,flag_OVERLAY_on,flag_OVERLAY,flag_OVERLAY_on,flag_OVERLAY_on,NULL,NULL,NULL);
	button_toggle(0,0,flag_PASSABLE_on,flag_PASSABLE,flag_PASSABLE_on,flag_PASSABLE_on,NULL,NULL,NULL);
	button_toggle(0,0,flag_POLYGON_on,flag_POLYGON,flag_POLYGON_on,flag_POLYGON_on,NULL,NULL,NULL);
	button_toggle(0,0,flag_SHADOW_on,flag_SHADOW,flag_SHADOW_on,flag_SHADOW_on,NULL,NULL,NULL);
	button_toggle(0,0,flag_TRANSLUCENT_on,flag_TRANSLUCENT,flag_TRANSLUCENT_on,flag_TRANSLUCENT_on,NULL,NULL,NULL);
	
	button(0,0,button_default,button_default_off,button_default_over,restore,NULL,NULL);
	
	hslider(0,0,100,slider,0,100,v_alpha);	
	hslider(0,0,100,slider,0,100,v_ambient);	
	
	on_click = sharedGUI_dragpanel;
	
	flags = TRANSLUCENT | OVERLAY;
}

PANEL *panPhy = {
	layer = 2;
	
	bmap = "panPhy.bmp";
	
	button(0,0,button_Close,button_Close_off,button_Close_over,sharedGUI_closewindow,NULL,NULL);
	
	button_toggle(0,0,flag_PHY_on,flag_PHY,flag_PHY_on,flag_PHY_on,NULL,NULL,NULL);
	
	hslider(0,0,100,slider,0,100,v_friction);
	hslider(0,0,100,slider,0,100,v_bounciness);
	
	on_click = sharedGUI_dragpanel;
	
	flags = OVERLAY | TRANSLUCENT;
}

PANEL *panMat = {
	layer = 2;
	
	bmap = "panMat.bmp";
	
	button(0,0,button_Close,button_Close_off,button_Close_over,sharedGUI_closewindow,NULL,NULL);
	
	button(0,0,button_Mat1,button_Mat1,button_Mat1,mat_select_lava,NULL,NULL);
	button(0,0,button_Mat2,button_Mat2,button_Mat2,mat_select_marble,NULL,NULL);
	button(0,0,button_Mat3,button_Mat3,button_Mat3,mat_select_smaragd,NULL,NULL);
	button(0,0,button_Mat4,button_Mat4,button_Mat4,mat_select_4,NULL,NULL);
	button(0,0,button_Mat5,button_Mat5,button_Mat5,mat_select_5,NULL,NULL);
	button(0,0,button_Mat6,button_Mat6,button_Mat6,mat_select_6,NULL,NULL);
	button(0,0,button_Mat7,button_Mat7,button_Mat7,mat_select_7,NULL,NULL);
	button(0,0,button_Mat8,button_Mat8,button_Mat8,mat_select_8,NULL,NULL);
	button(0,0,button_Mat9,button_Mat9,button_Mat9,mat_select_9,NULL,NULL);
	button(0,0,button_Mat10,button_Mat10,button_Mat10,mat_select_10,NULL,NULL);
	button(0,0,button_Mat11,button_Mat11,button_Mat11,mat_select_11,NULL,NULL);
	button(0,0,button_Mat12,button_Mat12,button_Mat12,mat_select_12,NULL,NULL);
	button(0,0,button_Mat13,button_Mat13,button_Mat13,mat_select_13,NULL,NULL);
	button(0,0,button_Mat14,button_Mat14,button_Mat14,mat_select_14,NULL,NULL);
	button(0,0,button_Mat15,button_Mat15,button_Mat15,mat_select_null,NULL,NULL);
	
	button(0,0,button_editmat,button_editmat,button_editmat,sharedGUI_editmat,NULL,NULL);
	button(0,0,button_matapply,button_matapply_off,button_matapply_over,pass_mat_to_object,NULL,NULL);
	
	on_click = sharedGUI_dragpanel;
	
	flags = OVERLAY | TRANSLUCENT;
}

PANEL *panMat_Sub1 = {
	layer = 2;
	
	bmap = "panMatEd.bmp";
	
	button(0,0,button_Close,button_Close_off,button_Close_over,sharedGUI_closewindow,NULL,NULL);
	
	button(0,0,button_editmat_def,button_editmat_def,button_editmat_def,NULL,NULL,NULL);
	button(0,0,button_editmat_save,button_editmat_save,button_editmat_save,mat_save,NULL,NULL);
	
	// we need 14 sliders for ambient x3, specular x3, diffuse x3 and emissive x3
	// +power, +alpha.
	
	hslider(0,0,50,slider,0,255,v_emissive_r);
	hslider(0,0,50,slider,0,255,v_emissive_g);
	hslider(0,0,50,slider,0,255,v_emissive_b);
	
	hslider(0,0,50,slider,0,255,v_ambient_r);
	hslider(0,0,50,slider,0,255,v_ambient_g);
	hslider(0,0,50,slider,0,255,v_ambient_b);
	
	hslider(0,0,50,slider,0,255,v_diffuse_r);
	hslider(0,0,50,slider,0,255,v_diffuse_g);
	hslider(0,0,50,slider,0,255,v_diffuse_b);
	
	hslider(0,0,50,slider,0,255,v_specular_r);
	hslider(0,0,50,slider,0,255,v_specular_g);
	hslider(0,0,50,slider,0,255,v_specular_b);
	
	hslider(0,0,50,slider,0,10,v_power);
	hslider(0,0,50,slider,0,255,v_alpha_m);
	
	on_click = sharedGUI_dragpanel;
	
	flags = OVERLAY | TRANSLUCENT;
}

void sharedGUI_updategui(PANEL *wg) {
	
	if(wg == panHome) {
		
		button_SaveWorld_y = BORDER;
		button_LoadWorld_y = button_SaveWorld_y + 40 + BORDER/2.5;
		button_NewWorld_y = button_LoadWorld_y + 40 + BORDER/2.5;
		button_QuitWorld_y = button_NewWorld_y + 40 + BORDER/2.5;
		button_CmpWorld_y = button_QuitWorld_y + 40 + BORDER/2.5;
		button_SetWorld_y = button_CmpWorld_y + 40 + BORDER/2.5;
		
		pan_setpos(panHome,3,2,vector(BORDER,button_SaveWorld_y,0));
		pan_setpos(panHome,3,3,vector(BORDER,button_LoadWorld_y,0));	
		pan_setpos(panHome,3,4,vector(BORDER,button_NewWorld_y,0));
		pan_setpos(panHome,3,5,vector(BORDER,button_QuitWorld_y,0));
		pan_setpos(panHome,3,6,vector(BORDER,button_CmpWorld_y,0));
		pan_setpos(panHome,3,7,vector(BORDER,button_SetWorld_y,0));
		
		pan_setpos(panHome,3,1,vector(bmap_width(panHome.bmap) - BORDER * 2,BORDER,0));
		
	}
	
	if(wg == panProp) { 
		
		int i;
		for(i = 2;i < 10;i++) pan_setpos(panProp,3,i,vector(BORDER,BORDER + 23 * (i - 1),0));
		pan_setpos(panProp,3,10,vector(bmap_width(panProp.bmap) - BORDER - 64, bmap_height(panProp.bmap) - BORDER - 32,0));
		
		pan_setpos(panProp,4,1,vector(BORDER + 102,BORDER * 2 + 23,0));
		pan_setpos(panProp,4,2,vector(BORDER + 102,BORDER * 3 + 23 * 2,0));
		pan_setpos(panProp,4,3,vector(BORDER + 102,BORDER * 4 + 23 * 3,0));
		
		pan_setpos(panProp,3,1,vector(bmap_width(panProp.bmap) - BORDER * 2,BORDER,0));
	}
	
	if(wg == panMat) {
		
		var i = 2, j = 0, k;
		k = i;
		while(i < 17) {
			pan_setpos(panMat,3,i,vector( (k-1) * BORDER + (k-2) * 64,BORDER * 2 + 15 + j,0));
			i++; k++;
			
			if(i == 7) {
				j = 74; // 64 + BORDER
				k = 2;
			}
			
			if(i == 12) {
				j = 148; // 128 + 2x BORDER
				k = 2;
			}
			
		}
		
		var cache = bmap_width(panMat.bmap) - BORDER - 100;
		pan_setpos(panMat,3,17,vector(cache, bmap_height(panMat.bmap) - BORDER - 24 ,0));
		pan_setpos(panMat,3,18,vector(cache, bmap_height(panMat.bmap) - BORDER * 2 - 48,0));
		
		pan_setpos(panMat,3,1,vector(bmap_width(panMat.bmap) - BORDER * 2, BORDER,0));
	}
	
	if(wg == panPhy) {
		pan_setpos(panPhy,3,1,vector(bmap_width(panPhy.bmap) - BORDER * 2, BORDER,0));
		
		pan_setpos(panPhy,3,2,vector(BORDER,BORDER*4,0));
		pan_setpos(panPhy,4,1,vector(141,bmap_height(panPhy.bmap) - 109,0)); // Bounciness
		pan_setpos(panPhy,4,2,vector(141,bmap_height(panPhy.bmap) - 135,0)); // Friction
	}
	
	if(wg == panMat_Sub1) { 
		pan_setpos(panMat_Sub1,3,1,vector(bmap_width(panMat_Sub1.bmap) - BORDER * 2,BORDER,0));
		
		var i = 2;
		while(i < 4) {
			pan_setpos(panMat_Sub1,3,i,vector(BORDER, bmap_height(panMat_Sub1.bmap) - BORDER * (i-1) - 24 * (i-1),0));
			i++;
		}
		
		var i = 1, j = 0, k;
		k = i; //lite-C doesn't allow me to initialize continuous variables during declaring them so...
		
		while(i < 15) {
			
			pan_setpos(panMat_Sub1,4,i,vector( BORDER * k + (k-1) * 50, BORDER * 2 + 45 + j,0 ));
			i++; k++;
			
			if(i == 4) {
				j = 23 + BORDER; // 23 = slider height
				k = 1;
			}
			
			if(i == 7) {
				j = (23 + BORDER) * 2;
				k = 1;
			}
			
			if(i ==  10) {
				j = (23 + BORDER) * 3;
				k = 1;
			}
			
			if(i == 13) {
				j = (23 + BORDER) * 4;
				k = 1;
			}
			
		}
	}
}

/* 

id always = 1 cuz we don't have two closebuttons at the same time. 
only one PANEL * parameter isn't enough (and it won't work too) so 
this simple ugly hack should do the trick.

*/
void sharedGUI_closewindow(var id, PANEL *p) {
	id = 1;
	
	if(p == panHome) {
		reset(panHome,SHOW);
	}
	
	if(p == panPhy) {
		reset(panPhy,SHOW);
	}
	
	if(p == panMat) {
		
		if(is(panMat_Sub1,SHOW)) {
			reset(panMat_Sub1,SHOW);
			
			if(is(debug_material,SHOW)) reset(debug_material,SHOW);
			
		}
		
		reset(panMat,SHOW);
	}
	
	if(p == panMat_Sub1) {
		reset(panMat_Sub1,SHOW);
		
		if(is(debug_material,SHOW)) reset(debug_material,SHOW);
	}
	
	if(p == panProp) {		
		
		reset(panProp,SHOW);
	}
	
	if(p == buttonlst_submenu_terrain) {
		wait(1);
		
		reset(buttonlst_submenu_terrain,SHOW);
	}
	
	if(p == buttonlst_submenu_object) {
		wait(1);
		
		reset(buttonlst_submenu_object,SHOW);
	}
	
	if(p == buttonlst_submenu_path) {
		wait(1);
		
		reset(buttonlst_submenu_path,SHOW);
	}
}

void sharedGUI_dragpanel(PANEL *p)
{
	var click_offset[2];
	
	click_offset[0]=p.pos_x - mouse_pos.x;
	click_offset[1]=p.pos_y - mouse_pos.y;
	
	sharedGUI_panelselect(p);
	
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

void sharedGUI_centerfrom(PANEL *p, PANEL *s) {
	while(p == NULL || s == NULL) wait(1);
	
	// peform a S comparison
	if(bmap_width(p.bmap)*bmap_height(p.bmap) > bmap_width(s.bmap)*bmap_height(s.bmap)) return;
	
	if(bmap_width(s.bmap) > bmap_width(p.bmap))
	p.pos_x = (bmap_width(s.bmap) - bmap_width(p.bmap))/2;
	
	if(bmap_height(s.bmap) > bmap_height(p.bmap))
	p.pos_y = (bmap_height(s.bmap) - bmap_height(p.bmap))/2;
}

void sharedGUI_loadbuttons() {
	
	panMain_Top.pos_x = screen_size.x - bmap_width(panMain_Top.bmap) - (BORDER + 3 * BUTTON_SIZE);
	panMain_Top.pos_y = BORDER;
	
	panMain_Bottom.pos_x = BORDER;
	panMain_Bottom.pos_y = screen_size.y - bmap_height(panMain_Bottom.bmap) - BORDER;

	int i = 1;
	while(i < 10) {
		pan_setpos(panMain_Top,3,i,vector((i - 1) * (BORDER + 32),0,0));
		i++;
	}
	
	int i = 1;
	while(i < 6) {
		pan_setpos(panMain_Bottom,3,i,vector((i-1) * (BORDER + 32),0,0));
		
		i++;
	}
	
	/*
	
	setup for submenus
	* buttonlst_submenu_terrain
	* buttonlst_submenu_object
	* buttonlst_submenu_path
	
	*/
	
	panMain_Play.pos_x = screen_size.x - BORDER - bmap_width(panMain_Play.bmap);
	panMain_Play.pos_y = screen_size.y - BORDER - bmap_height(panMain_Play.bmap);
	
	buttonlst_submenu_terrain.pos_x = 
	buttonlst_submenu_object.pos_x = 
	buttonlst_submenu_path.pos_x = BORDER;
	
	buttonlst_submenu_terrain.pos_y = 
	buttonlst_submenu_object.pos_y =
	buttonlst_submenu_path.pos_y = screen_size.y - 2 * BORDER - 64;
	
	int i = 1;
	while(i < 5){
		pan_setpos(buttonlst_submenu_terrain,3,i,vector(BORDER * (i-1) + 32 * (i-1),NULL,NULL));
		pan_setpos(buttonlst_submenu_object,3,i,vector(BORDER * (i-1) + 32 * (i-1),NULL,NULL));
		pan_setpos(buttonlst_submenu_path,3,i,vector(BORDER * (i-1) + 32 * (i-1),NULL,NULL));
		
		i++;
	}
	
	var cache = BORDER * 4 + 32 * 4; // the above formula, i = 5
	pan_setpos(buttonlst_submenu_terrain,3,5,vector(cache,NULL,NULL));
	pan_setpos(buttonlst_submenu_object,3,3,vector(cache,NULL,NULL));
	pan_setpos(buttonlst_submenu_path,3,3,vector(cache,NULL,NULL));
}

void sharedGUI__loadbuttons() {
	
	if(is(panMain_Top,SHOW)) reset(panMain_Top,SHOW);
	if(is(panMain_Bottom,SHOW)) reset(panMain_Bottom,SHOW);
	if(is(panMain_Play,SHOW)) reset(panMain_Play,SHOW);
}

PANEL *panMain_Top = {
	layer = 0;
	
	bmap = "panMain_Top.bmp";
	
	button(0,0,button_Cut,button_Cut_Off,button_Cut_Over,obj_cut,NULL,NULL);
	button(0,0,button_Copy,button_Copy_Off,button_Copy_Over,obj_copy,NULL,NULL);
	button(0,0,button_Paste,button_Paste_Off,button_Paste_Over,obj_paste,NULL,NULL);
	
	button(0,0,button_Move,button_Move_Off,button_Move_Over,switch_to_move,NULL,NULL);
	button(0,0,button_Rotate,button_Rotate_Off,button_Rotate_Over,switch_to_rotate,NULL,NULL);
	button(0,0,button_Scale,button_Scale_Off,button_Scale_Over,switch_to_scale,NULL,NULL);
	
	button(0,0,button_Prop,button_Prop_Off,button_Prop_Over,sharedGUI_prop,NULL,NULL);
	button(0,0,button_Phy,button_Phy_Off,button_Phy_Over,sharedGUI_phy,NULL,NULL);
	button(0,0,button_Mat,button_Mat_Off,button_Mat_Over,sharedGUI_mat,NULL,NULL);
	
	flags = OVERLAY | SHOW;
}

PANEL *panMain_Bottom = {
	layer = 0;
	
	bmap = "panMain_Bottom.bmp";

	button(0,0,button_Home,button_Home_Off,button_Home_Over,sharedGUI_home,NULL,NULL);
	button_toggle(0,0,button_Cam,button_Cam_Off,button_Cam,button_Cam,controlcam,NULL,NULL);
	button(0,0,button_Terrain,button_Terrain_Off,button_Terrain_Over,sharedGUI_launch_terrain,NULL,NULL);
	button(0,0,button_Objs,button_Objs_Off,button_Objs_Over,sharedGUI_launch_object,NULL,NULL);
	button(0,0,button_Path,button_Path_Off,button_Path_Over,sharedGUI_launch_path,NULL,NULL);
	
	flags = OVERLAY | SHOW;
}

PANEL *panMain_Play = {
	layer = 0;
	
	bmap = "panMain_Play.bmp";
	
	button(0,0,button_Play,button_Play_off,button_Play_over,NULL,NULL,NULL);
	
	flags = OVERLAY | SHOW;
}

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

void sharedGUI_loadlogo(BMAP *logo_bmap) {
	while(logo_bmap == NULL) wait(1);
	
	_logo.bmap = logo_bmap;
	
	_logo->pos_x = screen_size.x - bmap_width(_logo.bmap) - 2 * BORDER;
	_logo->pos_y = 20;
	
	set(_logo,SHOW);
}

void sharedGUI__loadlogo() {
	if(is(_logo,SHOW)) reset(_logo,SHOW);
}

void sharedGUI_release(STRING *str) {
	str_cpy(sharedGUI_releaseStr,str);

	sharedGUI_releaseTEXT->pos_x = screen_size.x - str_width(sharedGUI_releaseStr,"Arial#25b");
	sharedGUI_releaseTEXT->pos_y = screen_size.y - str_width(sharedGUI_releaseStr,"Arial#25b");
	
	set(sharedGUI_releaseTEXT,SHOW);
}

void sharedGUI__release() {
	if(is(sharedGUI_releaseTEXT,SHOW)) reset(sharedGUI_releaseTEXT,SHOW);
	str_cpy(sharedGUI_releaseStr,"");
}

void sharedGUI_playintro(STRING *what, var vol) {
	proc_kill(4);
	
	if(vol<0) vol = 100;
	
	var hndl;
	hndl = media_play(what,NULL,vol);

	while(media_playing(hndl)) wait(1);
}

void sharedGUI_loadbackground(STRING *lv_name) {
	//		sharedGUI_playintro(100);
	//		wait_for(sharedGUI_playintro);
	
	sharedGUI_loadscene(lv_name);
	wait_for(sharedGUI_loadscene);
	
	sharedGUI_loadbuttons();
	wait_for(sharedGUI_loadbuttons);
	
	sharedGUI_blackscreen(FADE_OUT,2);
	wait_for(sharedGUI_blackscreen);
	
	sharedGUI_mouse(ON);
}

void sharedGUI_mouse(int mode) {
	if(mode == OFF) mouse_mode = 0;
	if(mode == ON) mouse_mode = 4;
}

void sharedGUI_mouseset(BMAP *b) {
	mouse_map = b;
}

void sharedGUI_home() {
	
	sharedGUI_centerpanel(panHome);
	sharedGUI_updategui(panHome);
	
	set(panHome,SHOW);
}

void sharedGUI_prop() {
	
	if(select) {
		
		panProp.pos_x = BORDER;
		panProp.pos_y = screen_size.y - (2 * BORDER) - 32 - bmap_height(panProp.bmap);
		
		sharedGUI_updategui(panProp);
		
		set(panProp,SHOW);
		
	}
}

void sharedGUI_mat() {
	
	sharedGUI_centerpanel(panMat);
	sharedGUI_updategui(panMat);
	
	set(panMat,SHOW);
}

void sharedGUI_editmat() {
	
	// Precache panMat_Sub1
	sharedGUI_centerfrom(panMat_Sub1,panMat);
	sharedGUI_updategui(panMat_Sub1);
	
	// Material editor is available only to custom materials
	switch(mat_type) {
		
		case select_custom_mat1 :
		
		pass_mat_to_matsub(mat_custom[0]);
		set(panMat_Sub1,SHOW);
		
		// For debug purposes
		reset(debug,SHOW);
		set(debug_material,SHOW);
		
		break;
		//////////////////////////////////////////////////////////////
		
		case select_custom_mat2 :
		
		pass_mat_to_matsub(mat_custom[1]);
		set(panMat_Sub1,SHOW);
		
		reset(debug,SHOW);
		set(debug_material,SHOW);
		
		break;
		//////////////////////////////////////////////////////////////
		
		case select_custom_mat3 :
		
		pass_mat_to_matsub(mat_custom[2]);
		set(panMat_Sub1,SHOW);
		
		reset(debug,SHOW);
		set(debug_material,SHOW);
		
		break;
		//////////////////////////////////////////////////////////////
		
		case select_custom_mat4 :
		
		pass_mat_to_matsub(mat_custom[3]);
		set(panMat_Sub1,SHOW);
		
		reset(debug,SHOW);
		set(debug_material,SHOW);
		
		break;
		//////////////////////////////////////////////////////////////
		
		default:
		printf("Material editor is available only to custom materials.");
		break;
	}	
}

void sharedGUI_phy() {
	
	sharedGUI_centerpanel(panPhy);
	sharedGUI_updategui(panPhy);
	
	set(panPhy,SHOW);
}

void sharedGUI_panelselect(PANEL *p)
{
	if(last_pan) {
		last_pan.alpha = DEFAULT_ALPHA;
		layer_sort(last_pan,2);
		
		last_pan = p;
		layer_sort(last_pan,3);
		last_pan.alpha = 100;
	}
	else {
		last_pan = p;
		layer_sort(last_pan,3);
		last_pan.alpha = 100;
	}
}

void sharedGUI_launch_terrain() {
	reset(buttonlst_submenu_object,SHOW);
	reset(buttonlst_submenu_path,SHOW);
	
	set(buttonlst_submenu_terrain,SHOW);
}

void sharedGUI_launch_object() {
	reset(buttonlst_submenu_terrain,SHOW);
	reset(buttonlst_submenu_path,SHOW);
	
	set(buttonlst_submenu_object,SHOW);
}

void sharedGUI_launch_path() {
	reset(buttonlst_submenu_object,SHOW);
	reset(buttonlst_submenu_terrain,SHOW);
	
	set(buttonlst_submenu_path,SHOW);
}

void pass_to_object()
{
	while(select)
	{
		if(key_del) ptr_remove(select);
		
		select.alpha = v_alpha;
		select.ambient = v_ambient;
		
		if(button_state(panProp,2,-1) == ON) set(select,BRIGHT);
		else reset(select,BRIGHT);
		
		if(button_state(panProp,3,-1) == ON) set(select,INVISIBLE);
		else reset(select,INVISIBLE);
		
		if(button_state(panProp,4,-1) == ON) set(select,NOFOG);
		else reset(select,NOFOG);
		
		if(button_state(panProp,5,-1) == ON) set(select,OVERLAY);
		else reset(select,OVERLAY);
		
		if(button_state(panProp,6,-1) == ON) set(select,PASSABLE);
		else reset(select,PASSABLE);
		
		if(button_state(panProp,7,-1) == ON) set(select,POLYGON);
		else reset(select,POLYGON);
		
		if(button_state(panProp,8,-1) == ON) set(select,SHADOW);
		else reset(select,SHADOW);
		
		if(button_state(panProp,9,-1) == ON) set(select,TRANSLUCENT);
		else reset(select,TRANSLUCENT);
		
		wait(1);
	}
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
		vec_set(temp_pos.x,hit.x);
		wait(1);
	}
}

void place_me(STRING *e, int otype) {
	if(is_camera == 1) return;
	else ENTITY *tmp = ent_create(e,temp_pos.x,obj_manip_setup);
	
	tmp.skill99 = otype; // Pass object type 
	
	while(tmp == NULL) wait(1); // wait for e to be completely created
	
	set(tmp, POLYGON);
	reset(tmp, NOFOG | INVISIBLE | TRANSLUCENT); // Tha giet nham con hon bo sot
	
	tmp.alpha = 0;
	tmp.ambient = 50;
	
	tmp.material = mat_model;
}

void pass_to_gui(ENTITY *e) {
	v_ambient = e.ambient;
	v_alpha = e.alpha;

	////////////////////////////////////////////////////////////
	// For panProp
	////////////////////////////////////////////////////////////
	if(is(e,BRIGHT)) button_state(panProp,2,1);
	else button_state(panProp,2,0);
	
	if(is(e,INVISIBLE)) button_state(panProp,3,1);
	else button_state(panProp,3,0);
	
	if(is(e,NOFOG)) button_state(panProp,4,1);
	else button_state(panProp,4,0);
	
	if(is(e,OVERLAY)) button_state(panProp,5,1);
	else button_state(panProp,5,0);
	
	if(is(e,PASSABLE)) button_state(panProp,6,1);
	else button_state(panProp,6,0);
	
	if(is(e,POLYGON)) button_state(panProp,7,1);
	else button_state(panProp,7,0);
	
	if(is(e,SHADOW)) button_state(panProp,8,1);
	else button_state(panProp,8,0);
	
	if(is(e,TRANSLUCENT)) button_state(panProp,9,1);
	else button_state(panProp,9,0);
	
}

void controlcam() {
	if(button_state(panMain_Bottom,2,-1) == OFF) is_camera = 0;
	else is_camera = 1;
}

void restore() {
	if(select) {
		select.alpha = 0;
		select.ambient = 0;
		reset(select, BRIGHT | INVISIBLE | NOFOG | OVERLAY | PASSABLE | SHADOW | TRANSLUCENT);
		set(select,POLYGON);
		
		pass_to_gui(select); // update the properties panel
	}
}

////////////////////////////////////////////////////////////
// These materials can't be customized. Thus selecting them make panMat_Sub1 disappears.
////////////////////////////////////////////////////////////
void mat_select_null() {
	mat_type = select_mat_null;
	if(is(panMat_Sub1,SHOW)) {
		reset(panMat_Sub1,SHOW);
		
		if(is(debug_material,SHOW)) reset(debug_material,SHOW);
	}
}

void mat_select_lava() {
	mat_type = select_mat_lava;
	if(is(panMat_Sub1,SHOW)) {
		reset(panMat_Sub1,SHOW);
		
		if(is(debug_material,SHOW)) reset(debug_material,SHOW);
	}
}

void mat_select_smaragd() {
	mat_type = select_mat_smaragd;
	if(is(panMat_Sub1,SHOW)) {
		reset(panMat_Sub1,SHOW);
		
		if(is(debug_material,SHOW)) reset(debug_material,SHOW);
	}
}

void mat_select_marble() {
	mat_type = select_mat_marble;
	if(is(panMat_Sub1,SHOW)) {
		reset(panMat_Sub1,SHOW);
		
		if(is(debug_material,SHOW)) reset(debug_material,SHOW);
	}
}

void mat_select_4() {
	mat_type = select_mat_4;
	if(is(panMat_Sub1,SHOW)) {
		reset(panMat_Sub1,SHOW);
		
		if(is(debug_material,SHOW)) reset(debug_material,SHOW);
	}
}

void mat_select_5() {
	mat_type = select_mat_5;
	if(is(panMat_Sub1,SHOW)) {
		reset(panMat_Sub1,SHOW);
		
		if(is(debug_material,SHOW)) reset(debug_material,SHOW);
	}
}

void mat_select_6() {
	mat_type = select_mat_6;
	if(is(panMat_Sub1,SHOW)) {
		reset(panMat_Sub1,SHOW);
		
		if(is(debug_material,SHOW)) reset(debug_material,SHOW);
	}
}

void mat_select_7() {
	mat_type = select_mat_7;
	if(is(panMat_Sub1,SHOW)) {
		reset(panMat_Sub1,SHOW);
		
		if(is(debug_material,SHOW)) reset(debug_material,SHOW);
	}
}

void mat_select_8() {
	mat_type = select_mat_8;
	if(is(panMat_Sub1,SHOW)) {
		reset(panMat_Sub1,SHOW);
		
		if(is(debug_material,SHOW)) reset(debug_material,SHOW);
	}
}

void mat_select_9() {
	mat_type = select_mat_9;
	if(is(panMat_Sub1,SHOW)) {
		reset(panMat_Sub1,SHOW);
		
		if(is(debug_material,SHOW)) reset(debug_material,SHOW);
	}
}

void mat_select_10() {
	mat_type = select_mat_10;
	if(is(panMat_Sub1,SHOW)) {
		reset(panMat_Sub1,SHOW);
		
		if(is(debug_material,SHOW)) reset(debug_material,SHOW);
	}
}

////////////////////////////////////////////////////////////
// These materials are customizable. You know what to do.
// Only customizable materials' properties is passed through
// pass_mat_to_matsub(MATERIAL *).
////////////////////////////////////////////////////////////
void mat_select_11() {
	mat_type = select_custom_mat1;
	
	/*
	a quick terrible ugly hack
	normally panMat_Sub1 will only be updated
	if you click on "Edit Material",
	but this hack allows you to update panMat_Sub1 directly
	without pressing that button.
	
	this can be useful if you've already opened panMat_Sub1
	and select another customizable material, the panel
	will be updated immediately without having to click
	the "Edit Material" button again.
	*/
	if(is(panMat_Sub1,SHOW))
	pass_mat_to_matsub(mat_custom[0]);
}

void mat_select_12() {
	mat_type = select_custom_mat2;
	
	if(is(panMat_Sub1,SHOW))
	pass_mat_to_matsub(mat_custom[1]);
}

void mat_select_13() {
	mat_type = select_custom_mat3;
	
	if(is(panMat_Sub1,SHOW))
	pass_mat_to_matsub(mat_custom[2]);
}

void mat_select_14() {
	mat_type = select_custom_mat4;
	
	if(is(panMat_Sub1,SHOW))
	pass_mat_to_matsub(mat_custom[3]);
}

void pass_mat_to_object() {
	
	if(select) { // make sure something have been saved to mat_temp
		
		switch(mat_type) {
			
			case select_mat_null :
			mat_temp = mat_model;
			break;
			
			case select_mat_lava :
			mat_temp = mat_lava;
			break;
			
			case select_mat_smaragd :
			mat_temp = mat_smaragd;
			break;
			
			case select_mat_marble :
			mat_temp = mat_marble;
			break;
			
			case select_mat_4 :
			mat_temp = mat_marble;
			break;
			
			case select_mat_5 :
			mat_temp = mat_marble;
			break;
			
			case select_mat_6 :
			mat_temp = mat_marble;
			break;
			
			case select_mat_7 :
			mat_temp = mat_marble;
			break;
			
			case select_mat_8 :
			mat_temp = mat_marble;
			break;
			
			case select_mat_9 :
			mat_temp = mat_marble;
			break;
			
			case select_mat_10 :
			mat_temp = mat_marble;
			break;
			
			// Custom materials
			case select_custom_mat1 :
			mat_temp = mat_custom[0];
			break;
			
			case select_custom_mat2 :
			mat_temp = mat_custom[1];
			break;
			
			case select_custom_mat3 :
			mat_temp = mat_custom[2];
			break;
			
			case select_custom_mat4 :
			mat_temp = mat_custom[3];
			break;
			
			default:
			error("mat_type exceeded/wrong.");
			break; 
			
		}
		
	}
	
}

void pass_object_to_clipboard(ENTITY *o, obj_form *of) {
	of._scale_x = o.scale_x;
	of._scale_y = o.scale_y;
	of._scale_z = o.scale_z;
	
	of._pan = o.pan;
	of._tilt = o.tilt;
	of._roll = o.roll;
	
	of._alpha = o.alpha;
	of._ambient = o.ambient;
	
	if(is(o,BRIGHT)) of._flags[0] = ON;
	else of._flags[0] = OFF;
	
	if(is(o,INVISIBLE)) of._flags[1] = ON;
	else of._flags[1] = OFF;
	
	if(is(o,NOFOG)) of._flags[2] = ON;
	else of._flags[2] = OFF;
	
	if(is(o,OVERLAY)) of._flags[3] = ON;
	else of._flags[3] = OFF;
	
	if(is(o,PASSABLE)) of._flags[4] = ON;
	else of._flags[4] = OFF;
	
	if(is(o,POLYGON)) of._flags[5] = ON;
	else of._flags[5] = OFF;
	
	if(is(o,SHADOW)) of._flags[6] = ON;
	else of._flags[6] = OFF;
	
	if(is(o,TRANSLUCENT)) of._flags[7] = ON;
	else of._flags[7] = OFF;
	
	of.oid = o.skill99;
	of.dp = 1;
}

void pass_clipboard_to_object(ENTITY *e) {
	e.material = clipboard.m;
	e.skill99 = clipboard.oid;
	
	e.ambient = clipboard._ambient;
	e.alpha = clipboard._alpha;
	
	e.scale_x = clipboard._scale_x;
	e.scale_y = clipboard._scale_y;
	e.scale_z = clipboard._scale_z;
	
	e.pan = clipboard._pan;
	e.tilt = clipboard._tilt;
	e.roll = clipboard._roll;
	
	if(clipboard._flags[0] == ON) set(e,BRIGHT);
	else reset(e,BRIGHT);
	
	if(clipboard._flags[1] == ON) set(e,INVISIBLE);
	else reset(e,INVISIBLE);
	
	if(clipboard._flags[2] == ON) set(e,NOFOG);
	else reset(e,NOFOG);
	
	if(clipboard._flags[3] == ON) set(e,OVERLAY);
	else reset(e,OVERLAY);
	
	if(clipboard._flags[4] == ON) set(e,PASSABLE);
	else reset(e,PASSABLE);
	
	if(clipboard._flags[5] == ON) set(e,POLYGON);
	else reset(e,POLYGON);
	
	if(clipboard._flags[6] == ON) set(e,SHADOW);
	else reset(e,SHADOW);
	
	if(clipboard._flags[7] == ON) set(e,TRANSLUCENT);
	else reset(e,TRANSLUCENT);
	
}

void obj_cut() {
	
	if(select) {
		
		pass_object_to_clipboard(select,clipboard);
		
		// Perform manual access to clipboard to copy material
		
		/*
		select is selected.
		so something must have been copied into mat_temp.
		so I directly take mat_temp and copy it into the clipboard.
		
		otherwise if we pass select.material to clipboard.m,
		mat_select is passed but not select's material.
		*/
		clipboard.m = mat_temp;
		
		ptr_remove(select);
		select = NULL;
	}
	
}

void obj_copy() {
	
	if(select) {
		
		pass_object_to_clipboard(select,clipboard);
		
		// Perform manual access to clipboard to copy material
		clipboard.m = mat_temp;
	}
	
}

void obj_paste() {

	if(clipboard.dp) {

		ENTITY *tmp;

		switch(clipboard.oid) {
			
			case obj_winterbaum :
			
			tmp = ent_create(o_winterbaum,temp_pos.x,obj_manip_setup);
			// Begin passing clipboard to the newly created object.
			pass_clipboard_to_object(tmp);
			
			break;
			
			case obj_snowman :
			
			tmp = ent_create(o_snowman,temp_pos.x,obj_manip_setup);
			pass_clipboard_to_object(tmp);
			
			break;
			
			case obj_genericwall :
			
			tmp = ent_create(o_genericwall,temp_pos.x,obj_manip_setup);
			pass_clipboard_to_object(tmp);
			
			break;
			
			case obj_generictree :
			
			tmp = ent_create(o_generictree,temp_pos.x,obj_manip_setup);
			pass_clipboard_to_object(tmp);
			
			break;
			
			case obj_palmtree :
			
			tmp = ent_create(o_palmtree,temp_pos.x,obj_manip_setup);
			pass_clipboard_to_object(tmp);
			
			break;
			
			default:
			error("clipboard.oid exceed/wrong.");
			break;
			
		}
		
	}
	
}

// Read material properties from a file and pass it to a
// previously-defined material.
void pass_file_to_material(MATERIAL *m, STRING *file) {
	while(m == NULL) wait(1); // wait for m to be completely created
	
	var vpass = file_open_read(file);
	if(vpass == 0) return;
	// Follow this form :
	/*
	
	ambient_red, ambient_green, ambient_blue
	specular_red, specular_green, specular_blue,
	diffuse_red, diffuse_green, diffuse_blue,
	emissive_red, emissive_green, emissive_blue,
	alpha, power (no need for albedo)
	
	*/
	
	m.ambient_red = file_var_read(vpass);
	m.ambient_green = file_var_read(vpass);
	m.ambient_blue = file_var_read(vpass);
	
	m.specular_red = file_var_read(vpass);
	m.specular_green = file_var_read(vpass);
	m.specular_blue = file_var_read(vpass);
	
	m.diffuse_red = file_var_read(vpass);
	m.diffuse_green = file_var_read(vpass);
	m.diffuse_blue = file_var_read(vpass);
	
	m.emissive_red = file_var_read(vpass);
	m.emissive_green = file_var_read(vpass);
	m.emissive_blue = file_var_read(vpass);
	
	m.alpha = file_var_read(vpass);
	m.power = file_var_read(vpass);
	
	file_close(vpass);
}

void pass_mat_to_matsub(MATERIAL *m) {
	while(m == NULL) wait(1);

	v_ambient_r = m.ambient_red;
	v_ambient_g = m.ambient_green;
	v_ambient_b = m.ambient_blue;

	v_diffuse_r = m.diffuse_red;
	v_diffuse_g = m.diffuse_green;
	v_diffuse_b = m.diffuse_blue;

	v_specular_r = m.specular_red;
	v_specular_g = m.specular_green;
	v_specular_b = m.specular_blue;

	v_emissive_r = m.emissive_red;
	v_emissive_g = m.emissive_green;
	v_emissive_b = m.emissive_blue;

	v_power = m.power;
	v_alpha_m = m.alpha;
}

void pass_material_to_file(STRING *file, MATERIAL *m) {
	
	while(m == NULL) wait(1);
	
	var vpass = file_open_write(file);
	if(vpass == 0) return;
	
	// Copy values from the sliders
	m.ambient_red = v_ambient_r;
	m.ambient_green = v_ambient_g;
	m.ambient_blue = v_ambient_b;
	
	m.specular_red = v_specular_r;
	m.specular_green = v_specular_g;
	m.specular_blue = v_specular_b;
	
	m.diffuse_red = v_diffuse_r;
	m.diffuse_green = v_diffuse_g;
	m.diffuse_blue = v_diffuse_b;
	
	m.emissive_red = v_emissive_r;
	m.emissive_green = v_emissive_g;
	m.emissive_blue = v_emissive_b;
	
	m.alpha = v_alpha_m;
	m.power = v_power;
	
	// Write these copied values to vpass handle
	file_var_write(vpass,m.ambient_red);
	file_var_write(vpass,m.ambient_green);
	file_var_write(vpass,m.ambient_blue);
	
	file_var_write(vpass,m.specular_red);
	file_var_write(vpass,m.specular_green);
	file_var_write(vpass,m.specular_blue);
	
	file_var_write(vpass,m.diffuse_red);
	file_var_write(vpass,m.diffuse_green);
	file_var_write(vpass,m.diffuse_blue);
	
	file_var_write(vpass,m.emissive_red);
	file_var_write(vpass,m.emissive_green);
	file_var_write(vpass,m.emissive_blue);
	
	file_var_write(vpass,m.alpha);
	file_var_write(vpass,m.power);
	
	file_close(vpass);
	
	printf("Saved successfully.");
}

void mat_save() {
	
	// Material saving is available only to custom materials
	switch(mat_type) {
		
		case select_custom_mat1 :
		pass_material_to_file("mat_custom_1.cfg",mat_custom[0]);
		
		break;
		//////////////////////////////////////////////////////////////
		
		case select_custom_mat2 :
		pass_material_to_file("mat_custom_2.cfg",mat_custom[1]);
		
		break;
		//////////////////////////////////////////////////////////////
		
		case select_custom_mat3 :
		pass_material_to_file("mat_custom_3.cfg",mat_custom[2]);
		
		break;
		//////////////////////////////////////////////////////////////
		
		case select_custom_mat4 :
		pass_material_to_file("mat_custom_4.cfg",mat_custom[3]);
		
		break;
		//////////////////////////////////////////////////////////////
		
		default:
		// This line will never be executed.
		printf("Material saving is available only to custom materials.");
		break;
	}
	
}

////////////////////////////////////////////////////////////
// The following function will handle how the object is manipulated: move, rotate, or scale.
// While holding mouse_left, press Ctrl to downscale the object,
// or release it to upscale the object.
// Why do I have to comment the lines above if you've already
// read through the code.
// Actually this is just an extended version of follow_pointer
// because I'm too lazy to code a new one.
////////////////////////////////////////////////////////////
void obj_manip_interface()
{
	while(mouse_left)
	{
		if(manip_type == scale) 
		{
			
			if(key_ctrl) {
				
				my.scale_x -= .05;
				my.scale_y -= .05;
				my.scale_z -= .05;
				
			}
			
			else {
				
				my.scale_x += .05;
				my.scale_y += .05;
				my.scale_z += .05;
				
			}
			
		}
		
		if(manip_type == move) {
			
			v1.x = mouse_pos.x;
			v1.y = mouse_pos.y;
			v1.z = 0;
			vec_for_screen(v1,camera);
			v2.x = mouse_pos.x;
			v2.y = mouse_pos.y;
			v2.z = 200000;
			vec_for_screen(v2,camera);
			
			c_trace(v1.x,v2.x,IGNORE_ME | IGNORE_PASSABLE | IGNORE_MODELS);
			vec_set(my.x,hit.x);
			
		}
		
		if(manip_type == rotate) {
			
			my.pan = mouse_pos.x;
			my.tilt = mouse_pos.y;
			
		}

		wait (1);
	}
	
}

void obj_manip_setup()
{
	my.emask |= ENABLE_CLICK;
	my.event = obj_manip_interface;
}

////////////////////////////////////////////////////////////
// These functions will be assigned to move, rotate, scale button respectively.
////////////////////////////////////////////////////////////

// stupid switchers
// lite-C compiler: stupid programmer
void switch_to_move() {
	manip_type = move;
}

void switch_to_rotate() {
	manip_type = rotate;
}

void switch_to_scale() {
	manip_type = scale;
}

////////////////////////////////////////////////////////////
// Initialization before the game can be launched.
////////////////////////////////////////////////////////////
void init_startup() {
	
	panHome.alpha = panMat.alpha = panPhy.alpha = panProp.alpha = DEFAULT_ALPHA;
	
	int i;
	for(i = 0;i < 4;i++) mat_custom[i] = mtl_create();
	
	pass_file_to_material(mat_custom[0],"mat_custom_1.cfg");
	pass_file_to_material(mat_custom[1],"mat_custom_2.cfg");
	pass_file_to_material(mat_custom[2],"mat_custom_3.cfg");
	pass_file_to_material(mat_custom[3],"mat_custom_4.cfg");
}

//////////////////////////////
// Debug & statistics
//////////////////////////////
PANEL *debug = {
	layer = 3;
	
	digits(0,0,99,"arial#25b",1,obj_type);
	digits(0,20,99,"arial#25b",1,is_camera);
	
	flags = SHOW;
}

PANEL *debug_material = {
	layer = 3;
	
	digits(0,0,"Ambient red: %f","arial#15b",1,v_ambient_r);
	digits(0,10,"Ambient green: %f","arial#15b",1,v_ambient_g);
	digits(0,20,"Ambient blue: %f","arial#15b",1,v_ambient_b);
	
	digits(0,30,"Specular red: %f","arial#15b",1,v_specular_r);
	digits(0,40,"Specular green: %f","arial#15b",1,v_specular_g);
	digits(0,50,"Specular blue: %f","arial#15b",1,v_specular_b);
	
	digits(0,60,"Emissive red: %f","arial#15b",1,v_emissive_r);
	digits(0,70,"Emissive green: %f","arial#15b",1,v_emissive_g);
	digits(0,80,"Emissive blue: %f","arial#15b",1,v_emissive_b);
	
	digits(0,90,"Diffuse red: %f","arial#15b",1,v_diffuse_r);
	digits(0,100,"Diffuse green: %f","arial#15b",1,v_diffuse_g);
	digits(0,110,"Diffuse blue: %f","arial#15b",1,v_diffuse_b);
	
	digits(0,120,"Power: %f","arial#15b",1,v_power);
	digits(0,130,"Alpha: %f","arial#15b",1,v_alpha_m);
}