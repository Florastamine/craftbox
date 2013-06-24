////////////////////////////////////////////////////////////
// Panels will be defined here.
////////////////////////////////////////////////////////////
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


PANEL *panMain_Top = {
	layer = 0;
	
	bmap = "panMain_Top.bmp";
	
	//	button(0,0,button_Cut,button_Cut_Off,button_Cut_Over,obj_cut,NULL,NULL);
	//	button(0,0,button_Copy,button_Copy_Off,button_Copy_Over,obj_copy,NULL,NULL);
	//	button(0,0,button_Paste,button_Paste_Off,button_Paste_Over,obj_paste,NULL,NULL);
	
	/*
	button_toggle(0,0,flag_MOVE_on,flag_MOVE,flag_MOVE_on,flag_MOVE_on,switch_to_move,NULL,NULL);
	button_toggle(0,0,flag_ROTATE_on,flag_ROTATE,flag_ROTATE_on,flag_ROTATE_on,switch_to_rotate,NULL,NULL);
	button_toggle(0,0,flag_SCALE_on,flag_SCALE,flag_SCALE_on,flag_SCALE_on,switch_to_scale,NULL,NULL);
	
	button(0,0,button_Prop,button_Prop_Off,button_Prop_Over,sharedGUI_prop,NULL,NULL);
	button(0,0,button_Phy,button_Phy_Off,button_Phy_Over,sharedGUI_phy,NULL,NULL);
	button(0,0,button_Mat,button_Mat_Off,button_Mat_Over,sharedGUI_mat,NULL,NULL);
	*/
	
	button_toggle(0,0,flag_MOVE_on,flag_MOVE,flag_MOVE_on,flag_MOVE_on,switch_to_move,NULL,NULL);
	button_toggle(0,0,flag_ROTATE_on,flag_ROTATE,flag_ROTATE_on,flag_ROTATE_on,switch_to_rotate,NULL,NULL);
	button_toggle(0,0,flag_SCALE_on,flag_SCALE,flag_SCALE_on,flag_SCALE_on,switch_to_scale,NULL,NULL);
	
	button(0,0,"properties.png","properties.png","properties.png",sharedGUI_prop,NULL,NULL);
	button(0,0,"emblem_weapon.png","emblem_weapon.png","emblem_weapon.png",sharedGUI_phy,NULL,NULL);
	button(0,0,"pathing.png","pathing.png","pathing.png",sharedGUI_mat,NULL,NULL);
	
	
	flags = OVERLAY | SHOW;
}

PANEL *panMain_Bottom = {
	layer = 0;
	
	bmap = "panMain_Bottom.bmp";

	/*
	button(0,0,button_Home,button_Home_Off,button_Home_Over,sharedGUI_home,NULL,NULL);
	button_toggle(0,0,button_Cam,button_Cam_Off,button_Cam,button_Cam,controlcam,NULL,NULL);
	button(0,0,button_Terrain,button_Terrain_Off,button_Terrain_Over,sharedGUI_launch_terrain,NULL,NULL);
	button(0,0,button_Objs,button_Objs_Off,button_Objs_Over,sharedGUI_launch_object,NULL,NULL);
	button(0,0,button_Path,button_Path_Off,button_Path_Over,sharedGUI_launch_path,NULL,NULL);
	*/
	
	button(0,0,"home.png","home.png","home.png",sharedGUI_home,NULL,NULL);
	button_toggle(0,0,button_Cam,button_Cam_Off,button_Cam,button_Cam,controlcam,NULL,NULL);
	button(0,0,button_Terrain,button_Terrain_Off,button_Terrain_Over,sharedGUI_launch_terrain,NULL,NULL);
	button(0,0,"objects.png","objects.png","objects.png",sharedGUI_launch_object,NULL,NULL);
	button(0,0,"path_32.png","path_32.png","path_32.png",sharedGUI_launch_path,NULL,NULL);
	
	
	flags = OVERLAY | SHOW;
}

PANEL *panMain_Play = {
	layer = 0;
	
	bmap = "panMain_Play.bmp";
	
	// button(0,0,button_Play,button_Play_off,button_Play_over,NULL,NULL,NULL);
	button(0,0,"v.png","button_ok.png","button_ok.png",NULL,NULL,NULL);
	
	flags = OVERLAY | SHOW;
}

PANEL *_logo = {
	bmap = "_logo.bmp";
	flags = OVERLAY;	
}

PANEL *blackscreen = {
	bmap = "bitmap.bmp";
}

////////////////////////////////////////////////////////////
// Materials will be defined here.
////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////
// Texts will be defined here.
////////////////////////////////////////////////////////////
TEXT *files_list = 
{ 
	strings = 1000; 
	pos_x = 0;
	pos_y = 0;
	font = "Arial#25b";
	flags=SHOW;
}