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
	button(0,0,"button_back.png","button_back.png","button_back.png",closewindow,NULL,NULL);
	
	flags = OVERLAY;
}

PANEL *buttonlst_submenu_object = {
	layer = 1;
	
	bmap = "button_submenu_black.bmp";
	
	button(0,0,"tree.png","tree.png","tree.png",objadd,NULL,NULL);
	button(0,0,"fireworks256.png","fireworks256.png","fireworks256.png",NULL,NULL,NULL);
	button(0,0,"music.png","music.png","music.png",NULL,NULL,NULL);
	button(0,0,"tips.png","tips.png","tips.png",NULL,NULL,NULL);
	
	button(0,0,"button_back.png","button_back.png","button_back.png",closewindow,NULL,NULL);
	
	flags = OVERLAY;
}

PANEL *buttonlst_submenu_path = {
	layer = 1;
	
	bmap = "button_submenu_black.bmp";
	
	button(0,0,menu3_submenu1,menu3_submenu1_off,menu3_submenu1_over,NULL,NULL,NULL);
	button(0,0,menu3_submenu2,menu3_submenu2_off,menu3_submenu2_over,NULL,NULL,NULL);
	//	button(0,0,menu3_submenu3,menu3_submenu3,menu3_submenu3,NULL,NULL,NULL);
	//	button(0,0,menu3_submenu4,menu3_submenu4,menu3_submenu4,NULL,NULL,NULL);
	
	button(0,0,"button_back.png","button_back.png","button_back.png",closewindow,NULL,NULL);
	
	flags = OVERLAY;
}

PANEL *panHome = {
	layer = 2;
	
	bmap = "panHome.bmp";
	
	button(0,0,"button_close_on.bmp","button_close_off.bmp","button_close_over.bmp",closewindow,NULL,NULL);
	
	button(0,0,button_Home_saveworld,button_Home_saveworld_off,button_Home_saveworld_over,NULL,NULL,NULL);
	button(0,0,button_Home_loadworld,button_Home_loadworld_off,button_Home_loadworld_over,NULL,NULL,NULL);
	button(0,0,button_Home_newworld,button_Home_newworld_off,button_Home_newworld_over,NULL,NULL,NULL);
	button(0,0,button_Home_quitworld,button_Home_quitworld_off,button_Home_quitworld_over,NULL,NULL,NULL);
	button(0,0,button_Home_compileworld,button_Home_compileworld_off,button_Home_compileworld_over,NULL,NULL,NULL);
	button(0,0,button_Home_configworld,button_Home_configworld_off,button_Home_configworld_over,NULL,NULL,NULL);
	
	on_click = dragpanel;
	
	flags = OVERLAY | TRANSLUCENT;
}

PANEL *panProp_1 = { // Properties
	
	layer = 16;
	
	button_toggle(0,0,flag_BIRGHT_on,flag_BIRGHT,flag_BIRGHT_on,flag_BIRGHT_on,NULL,NULL,NULL);
	button_toggle(0,20,flag_INVISIBLE_on,flag_INVISIBLE,flag_INVISIBLE_on,flag_INVISIBLE_on,NULL,NULL,NULL);
	button_toggle(0,40,flag_NOFOG_on,flag_NOFOG,flag_NOFOG_on,flag_NOFOG_on,NULL,NULL,NULL);
	button_toggle(0,60,flag_OVERLAY_on,flag_OVERLAY,flag_OVERLAY_on,flag_OVERLAY_on,NULL,NULL,NULL);
	button_toggle(0,80,flag_PASSABLE_on,flag_PASSABLE,flag_PASSABLE_on,flag_PASSABLE_on,NULL,NULL,NULL);
	button_toggle(0,100,flag_POLYGON_on,flag_POLYGON,flag_POLYGON_on,flag_POLYGON_on,NULL,NULL,NULL);
	button_toggle(0,120,flag_SHADOW_on,flag_SHADOW,flag_SHADOW_on,flag_SHADOW_on,NULL,NULL,NULL);
	button_toggle(0,140,flag_TRANSLUCENT_on,flag_TRANSLUCENT,flag_TRANSLUCENT_on,flag_TRANSLUCENT_on,NULL,NULL,NULL);
	
	button(2,170,"button_default_on.bmp","button_default_off.bmp","button_default_on.bmp",restore,NULL,NULL);
	button(90,170,"button_randomrotate_on.bmp","button_randomrotate_off.bmp","button_randomrotate_on.bmp",random_pan,NULL,NULL);
	
	hslider(0,221,100,slider,0,100,v_alpha);	
	hslider(0,268,100,slider,0,100,v_ambient);
	
	flags = OVERLAY;	
	
}

PANEL *panProp_2 = { // Materials
	
	layer = 3;
	
	button_toggle(0,0,"button_Mat1_on.bmp","button_Mat1.bmp","button_Mat1_on.bmp","button_Mat1_on.bmp",_mat_select,NULL,NULL);
	button_toggle(0,30,"button_Mat2_on.bmp","button_Mat2.bmp","button_Mat2_on.bmp","button_Mat2_on.bmp",_mat_select,NULL,NULL);
	button_toggle(0,60,"button_Mat3_on.bmp","button_Mat3.bmp","button_Mat3_on.bmp","button_Mat3_on.bmp",_mat_select,NULL,NULL);
	button_toggle(0,90,"button_Mat4_on.bmp","button_Mat4.bmp","button_Mat4_on.bmp","button_Mat4_on.bmp",_mat_select,NULL,NULL);
	button_toggle(0,120,"button_Mat5_on.bmp","button_Mat5.bmp","button_Mat5_on.bmp","button_Mat5_on.bmp",_mat_select,NULL,NULL);
	button_toggle(0,150,"button_Mat6_on.bmp","button_Mat6.bmp","button_Mat6_on.bmp","button_Mat6_on.bmp",_mat_select,NULL,NULL);
	button_toggle(0,180,"button_Mat7_on.bmp","button_Mat7.bmp","button_Mat7_on.bmp","button_Mat7_on.bmp",_mat_select,NULL,NULL);
	button_toggle(0,210,"button_Mat8_on.bmp","button_Mat8.bmp","button_Mat8_on.bmp","button_Mat8_on.bmp",_mat_select,NULL,NULL);
	button_toggle(0,240,"button_Mat9_on.bmp","button_Mat9.bmp","button_Mat9_on.bmp","button_Mat9_on.bmp",_mat_select,NULL,NULL);
	button_toggle(0,270,"button_Mat10_on.bmp","button_Mat10.bmp","button_Mat10_on.bmp","button_Mat10_on.bmp",_mat_select,NULL,NULL);
	button_toggle(0,300,"button_Mat11_on.bmp","button_Mat11.bmp","button_Mat11_on.bmp","button_Mat11_on.bmp",_mat_select,NULL,NULL);
	button_toggle(0,330,"button_Mat12_on.bmp","button_Mat12.bmp","button_Mat12_on.bmp","button_Mat12_on.bmp",_mat_select,NULL,NULL);
	button_toggle(0,360,"button_Mat13_on.bmp","button_Mat13.bmp","button_Mat13_on.bmp","button_Mat13_on.bmp",_mat_select,NULL,NULL);
	button_toggle(0,390,"button_Mat14_on.bmp","button_Mat14.bmp","button_Mat14_on.bmp","button_Mat14_on.bmp",_mat_select,NULL,NULL);
	button_toggle(0,420,"button_Mat15_on.bmp","button_Mat15.bmp","button_Mat15_on.bmp","button_Mat15_on.bmp",_mat_select,NULL,NULL);
	
	button(160,0,"box_icons_on.png","box_icons.png","box_icons_on.png",editmat,NULL,NULL);
	
	flags = OVERLAY;
	
}

PANEL *panProp_3 = { // Physics
	
	layer = 3;
	
	button_toggle(0,0,flag_PHY_on,flag_PHY,flag_PHY_on,flag_PHY_on,NULL,NULL,NULL);
	
	hslider(0,0,100,slider,0,100,v_friction);
	hslider(0,0,100,slider,0,100,v_bounciness);
	
	flags = OVERLAY;
	
}

PANEL *panProp = {
	layer = 2;
	
	bmap = "panProp.png";
	
	button(0,0,"button_close_on.bmp","button_close_off.bmp","button_close_over.bmp",closewindow,NULL,NULL);
	
	/*
	button_toggle(0,0,flag_BIRGHT_on,flag_BIRGHT,flag_BIRGHT_on,flag_BIRGHT_on,NULL,NULL,NULL);
	button_toggle(0,0,flag_INVISIBLE_on,flag_INVISIBLE,flag_INVISIBLE_on,flag_INVISIBLE_on,NULL,NULL,NULL);
	button_toggle(0,0,flag_NOFOG_on,flag_NOFOG,flag_NOFOG_on,flag_NOFOG_on,NULL,NULL,NULL);
	button_toggle(0,0,flag_OVERLAY_on,flag_OVERLAY,flag_OVERLAY_on,flag_OVERLAY_on,NULL,NULL,NULL);
	button_toggle(0,0,flag_PASSABLE_on,flag_PASSABLE,flag_PASSABLE_on,flag_PASSABLE_on,NULL,NULL,NULL);
	button_toggle(0,0,flag_POLYGON_on,flag_POLYGON,flag_POLYGON_on,flag_POLYGON_on,NULL,NULL,NULL);
	button_toggle(0,0,flag_SHADOW_on,flag_SHADOW,flag_SHADOW_on,flag_SHADOW_on,NULL,NULL,NULL);
	button_toggle(0,0,flag_TRANSLUCENT_on,flag_TRANSLUCENT,flag_TRANSLUCENT_on,flag_TRANSLUCENT_on,NULL,NULL,NULL);
	
	button(0,0,button_default,button_default_off,button_default_over,restore,NULL,NULL);
	button(0,0,button_randompan,button_randompan_off,button_randompan_over,random_pan,NULL,NULL);
	*/
	
	button_toggle(0,0,"button_generalattrib_on.bmp","button_generalattrib.bmp","button_generalattrib_on.bmp","button_generalattrib_on.bmp",switch_propmode,NULL,NULL);
	button_toggle(0,0,"button_material_on.bmp","button_material.bmp","button_material_on.bmp","button_material_on.bmp",switch_propmode,NULL,NULL);
	button_toggle(0,0,"button_physics_on.bmp","button_physics.bmp","button_physics_on.bmp","button_physics_on.bmp",switch_propmode,NULL,NULL);	
	button(0,0,"button_apply_on.bmp","button_apply.bmp","button_apply_on.bmp",NULL,NULL,NULL);
	
	on_click = dragpanel;
	
	flags = TRANSLUCENT;
}

PANEL *panMat_Sub1 = {
	layer = 2;
	
	bmap = "panMatEd.bmp";
	
	button(0,0,"button_close_on.bmp","button_close_off.bmp","button_close_over.bmp",closewindow,NULL,NULL);
	
//	button(0,0,button_editmat_def,button_editmat_def,button_editmat_def,NULL,NULL,NULL);
//	button(0,0,button_editmat_save,button_editmat_save,button_editmat_save,mat_save,NULL,NULL);
//	
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
	
	on_click = dragpanel;
	
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
	
	//	button(0,0,"properties.png","properties.png","properties.png",prop,NULL,NULL);
	//	button(0,0,"emblem_weapon.png","emblem_weapon.png","emblem_weapon.png",phy,NULL,NULL);
	//	button(0,0,"pathing.png","pathing.png","pathing.png",mat,NULL,NULL);
	
	
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
	
	button(0,0,"home.png","home.png","home.png",home,NULL,NULL);
	button_toggle(0,0,"mouse_pointer_on.png","mouse_pointer.png","mouse_pointer_on.png","mouse_pointer_on.png",controlcam,NULL,NULL);
	button(0,0,"pathing.png","pathing.png","pathing.png",sharedGUI_launch_terrain,NULL,NULL);
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

PANEL *panObj_Subbar = {
	
	layer = 2;
	bmap = "panObj_Subbar_cover.bmp";
	
	button_toggle(0,0,flag_ANMS_on,flag_ANMS,flag_ANMS_on,flag_ANMS_on,panObj_Subbar_switcher,NULL,NULL);
	button_toggle(0,0,flag_ARCH_on,flag_ARCH,flag_ARCH_on,flag_ARCH_on,panObj_Subbar_switcher,NULL,NULL);
	button_toggle(0,0,flag_BLANDS_on,flag_BLANDS,flag_BLANDS_on,flag_BLANDS_on,panObj_Subbar_switcher,NULL,NULL);
	button_toggle(0,0,flag_CHARS_on,flag_CHARS,flag_CHARS_on,flag_CHARS_on,panObj_Subbar_switcher,NULL,NULL);
	button_toggle(0,0,flag_ETC_on,flag_ETC,flag_ETC_on,flag_ETC_on,panObj_Subbar_switcher,NULL,NULL);
	button_toggle(0,0,flag_FOOD_on,flag_FOOD,flag_FOOD_on,flag_FOOD_on,panObj_Subbar_switcher,NULL,NULL);
	button_toggle(0,0,flag_MACHS_on,flag_MACHS,flag_MACHS_on,flag_MACHS_on,panObj_Subbar_switcher,NULL,NULL);
	button_toggle(0,0,flag_PLANTS_on,flag_PLANTS,flag_PLANTS_on,flag_PLANTS_on,panObj_Subbar_switcher,NULL,NULL);
	button_toggle(0,0,flag_TPORTTS_on,flag_TPORTTS,flag_TPORTTS_on,flag_TPORTTS_on,panObj_Subbar_switcher,NULL,NULL);
	
	flags = OVERLAY;
	
}

PANEL *panObj_Subbar_slider = {
	
	layer = 2;
	bmap = "big_slider.bmp";
	
	// 800 = default
	hslider(0,0,800,slider,0,100,ctrl);
	
}

PANEL *panObj_Main = {
	
	layer = 2;
	
	bmap = panObj_anms;
	
	//button(0,0,"button_close_on.bmp","button_close_off.bmp","button_close_over.bmp",closewindow,NULL,NULL);
	
	flags = OVERLAY;
	
}

PANEL *panLight = {
	
	layer = 2;
	
	bmap = "panLight.bmp";
	
	button(0,0,"button_close_on.bmp","button_close_off.bmp","button_close_over.bmp",closewindow,NULL,NULL);
	
	hslider(0,0,100,slider,0,255,v_lred);
	hslider(0,0,100,slider,0,255,v_lgreen);
	hslider(0,0,100,slider,0,255,v_lblue);
	hslider(0,0,100,slider,0,2000,v_lrange);
	
	button_toggle(0,0,flag_DISCO_on,flag_DISCO,flag_DISCO_on,flag_DISCO_on,NULL,NULL,NULL);
	button_toggle(0,0,flag_FLICK_on,flag_FLICK,flag_FLICK_on,flag_FLICK_on,NULL,NULL,NULL);
	
	on_click = dragpanel;
	
	flags = OVERLAY; // because of the checkboxes..
	
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

MATERIAL *mat_lavenderrose = {
	
	ambient_red = 251;
	ambient_green = 160;
	ambient_blue = 227;
	
	power = 10;
	
}

MATERIAL *mat_bitterlemon = {
	
	ambient_red = 13;
	ambient_green = 224;
	ambient_blue = 202;
	
	power = 10;
	
}

MATERIAL *mat_peachorange = {
	
	ambient_red = 255;
	ambient_green = 204;
	ambient_blue = 153;
	
	power = 10;
	
}

MATERIAL *mat_purewhite = {
	
	ambient_red = 255;
	ambient_green = 255;
	ambient_blue = 255;
	emissive_red = 255;
	emissive_green = 255;
	emissive_blue = 255;
	diffuse_red = 255;
	diffuse_green = 255;
	diffuse_blue = 255;
	specular_red = 255;
	specular_green = 255;
	specular_blue = 255;
	
	power = 10;
	
}

MATERIAL *mat_black = {
	
	ambient_red = 0;
	ambient_green = 0;
	ambient_blue = 0;
	emissive_red = 0;
	emissive_green = 0;
	emissive_blue = 0;
	diffuse_red = 0;
	diffuse_green = 0;
	diffuse_blue = 0;
	specular_red = 0;
	specular_green = 0;
	specular_blue = 0;
	
	power = 0;
	
}

MATERIAL *mat_palelilac = {
	
	ambient_red = 255;
	ambient_green = 187;
	ambient_blue = 187;
	
	power = 10;
	
}

MATERIAL *mat_select = 
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

////////////////////////////////////////////////////////////
// Particle effects or anything else related will be defined here.
////////////////////////////////////////////////////////////

/* Fountain 1 */
/////////////////////////////////p_fountain.c/////////////////////////////////
//
//Generated by Parted by Martin Coumont (redphoenix)
//
//LiteC Script file from 27.06.2013 ; 11:01:20:
//
//////////////////////////////////////////////////////////////////////////////

/////////////////////////////////header/////////////////////////////////

#ifndef PARTED_VECTOR_DEF
	#define PARTED_VECTOR_DEF
	VECTOR* parted_temp_vec = { x=0;y=0;z=0; }
	VECTOR* parted_temp2_vec = { x=0;y=0;z=0; }
	ANGLE* parted_temp_ang = { pan=0;tilt=0;roll=0; }
#endif

/////////////////////////////////particle code/////////////////////////////////

function Base_Effect_base_event(PARTICLE* p) {
	p.vel_x = p.skill_x;
	p.vel_y = p.skill_y;
	p.vel_z = p.skill_z-p.skill_z*p.skill_d/50;
	p.skill_d = (p.skill_d + time_step*(var)2.500)%100;
}

function Base_Effect_base(PARTICLE* p) {
	p.size = random(4.793)+(7.207);
	p.alpha = random(25.457)+(12.543);
	p.red = 69;
	p.green = 124;
	p.blue = 180;
	p.skill_c = 0.5;
	parted_temp_vec.x = random(0.000)+0.000;
	parted_temp_vec.y = random(8.000)+-4.000;
	parted_temp_vec.z = 0.000;
	vec_add(p.x,parted_temp_vec);
	p.vel_x = random(0.539)+(2.461);
	p.vel_y = (0.000);
	p.vel_z = random(1.387)+(8.613);
	vec_normalize(p.vel_x,10.439);
	p.lifespan = 40.000;
	p.gravity = random(0.000)+0.000;
	p.flags = BRIGHT | TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = Base_Effect_base_event;
}

function Base_Effect14_base_event(PARTICLE* p) {
	p.vel_x = p.skill_x;
	p.vel_y = p.skill_y;
	p.vel_z = p.skill_z-p.skill_z*p.skill_d/50;
	p.skill_d = (p.skill_d + time_step*(var)2.500)%100;
}

function Base_Effect14_base(PARTICLE* p) {
	p.size = random(4.793)+(7.207);
	p.alpha = random(25.457)+(12.543);
	p.red = 69;
	p.green = 124;
	p.blue = 180;
	p.skill_c = 0.5;
	p.vel_x = random(0.449)+(2.051);
	p.vel_y = random(0.180)+(0.820);
	p.vel_z = random(1.387)+(8.613);
	vec_normalize(p.vel_x,10.355);
	p.lifespan = 40.000;
	p.gravity = random(0.000)+0.000;
	p.flags = BRIGHT | TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = Base_Effect14_base_event;
}

function Base_Effect13_base_event(PARTICLE* p) {
	p.vel_x = p.skill_x;
	p.vel_y = p.skill_y;
	p.vel_z = p.skill_z-p.skill_z*p.skill_d/50;
	p.skill_d = (p.skill_d + time_step*(var)2.500)%100;
}

function Base_Effect13_base(PARTICLE* p) {
	p.size = random(4.793)+(7.207);
	p.alpha = random(25.457)+(12.543);
	p.red = 69;
	p.green = 124;
	p.blue = 180;
	p.skill_c = 0.5;
	p.vel_x = random(0.359)+(1.641);
	p.vel_y = random(0.359)+(1.641);
	p.vel_z = random(1.387)+(8.613);
	vec_normalize(p.vel_x,10.392);
	p.lifespan = 40.000;
	p.gravity = random(0.000)+0.000;
	p.flags = BRIGHT | TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = Base_Effect13_base_event;
}

function Base_Effect12_base_event(PARTICLE* p) {
	p.vel_x = p.skill_x;
	p.vel_y = p.skill_y;
	p.vel_z = p.skill_z-p.skill_z*p.skill_d/50;
	p.skill_d = (p.skill_d + time_step*(var)2.500)%100;
}

function Base_Effect12_base(PARTICLE* p) {
	p.size = random(4.793)+(7.207);
	p.alpha = random(25.457)+(12.543);
	p.red = 69;
	p.green = 124;
	p.blue = 180;
	p.skill_c = 0.5;
	p.vel_x = random(0.180)+(0.820);
	p.vel_y = random(0.449)+(2.051);
	p.vel_z = random(1.387)+(8.613);
	vec_normalize(p.vel_x,10.355);
	p.lifespan = 40.000;
	p.gravity = random(0.000)+0.000;
	p.flags = BRIGHT | TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = Base_Effect12_base_event;
}

function Base_Effect11_base_event(PARTICLE* p) {
	p.vel_x = p.skill_x;
	p.vel_y = p.skill_y;
	p.vel_z = p.skill_z-p.skill_z*p.skill_d/50;
	p.skill_d = (p.skill_d + time_step*(var)2.500)%100;
}

function Base_Effect11_base(PARTICLE* p) {
	p.size = random(4.793)+(7.207);
	p.alpha = random(25.457)+(12.543);
	p.red = 69;
	p.green = 124;
	p.blue = 180;
	p.skill_c = 0.5;
	p.vel_x = (0.000);
	p.vel_y = random(0.539)+(2.461);
	p.vel_z = random(1.387)+(8.613);
	vec_normalize(p.vel_x,10.439);
	p.lifespan = 40.000;
	p.gravity = random(0.000)+0.000;
	p.flags = BRIGHT | TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = Base_Effect11_base_event;
}

function Base_Effect10_base_event(PARTICLE* p) {
	p.vel_x = p.skill_x;
	p.vel_y = p.skill_y;
	p.vel_z = p.skill_z-p.skill_z*p.skill_d/50;
	if(p.creator)vec_rotate(p.vel_x,p.creator.pan);
	p.skill_d = (p.skill_d + time_step*(var)2.500)%100;
}

function Base_Effect10_base(PARTICLE* p) {
	p.size = random(4.793)+(7.207);
	p.alpha = random(25.457)+(12.543);
	p.red = 69;
	p.green = 124;
	p.blue = 180;
	p.skill_c = 0.5;
	parted_temp_vec.x = random(0.000)+0.000;
	parted_temp_vec.y = random(8.000)+-4.000;
	parted_temp_vec.z = 0.000;
	if(p.creator)vec_rotate(parted_temp_vec,p.creator.pan);
	vec_add(p.x,parted_temp_vec);
	p.vel_x = random(0.539)+(2.461);
	p.vel_y = (0.000);
	p.vel_z = random(1.387)+(8.613);
	if(p.creator)vec_rotate(p.vel_x,p.creator.pan);
	vec_normalize(p.vel_x,10.439);
	p.lifespan = 40.000;
	p.gravity = random(0.000)+0.000;
	p.flags = BRIGHT | TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = Base_Effect10_base_event;
}

function Base_Effect9_base_event(PARTICLE* p) {
	p.vel_x = p.skill_x;
	p.vel_y = p.skill_y;
	p.vel_z = p.skill_z-p.skill_z*p.skill_d/50;
	if(p.creator)vec_rotate(p.vel_x,p.creator.pan);
	p.skill_d = (p.skill_d + time_step*(var)2.500)%100;
}

function Base_Effect9_base(PARTICLE* p) {
	p.size = random(4.793)+(7.207);
	p.alpha = random(25.457)+(12.543);
	p.red = 69;
	p.green = 124;
	p.blue = 180;
	p.skill_c = 0.5;
	p.vel_x = random(0.449)+(2.051);
	p.vel_y = random(0.180)+(0.820);
	p.vel_z = random(1.387)+(8.613);
	if(p.creator)vec_rotate(p.vel_x,p.creator.pan);
	vec_normalize(p.vel_x,10.355);
	p.lifespan = 40.000;
	p.gravity = random(0.000)+0.000;
	p.flags = BRIGHT | TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = Base_Effect9_base_event;
}

function Base_Effect8_base_event(PARTICLE* p) {
	p.vel_x = p.skill_x;
	p.vel_y = p.skill_y;
	p.vel_z = p.skill_z-p.skill_z*p.skill_d/50;
	if(p.creator)vec_rotate(p.vel_x,p.creator.pan);
	p.skill_d = (p.skill_d + time_step*(var)2.500)%100;
}

function Base_Effect8_base(PARTICLE* p) {
	p.size = random(4.793)+(7.207);
	p.alpha = random(25.457)+(12.543);
	p.red = 69;
	p.green = 124;
	p.blue = 180;
	p.skill_c = 0.5;
	p.vel_x = random(0.359)+(1.641);
	p.vel_y = random(0.359)+(1.641);
	p.vel_z = random(1.387)+(8.613);
	if(p.creator)vec_rotate(p.vel_x,p.creator.pan);
	vec_normalize(p.vel_x,10.392);
	p.lifespan = 40.000;
	p.gravity = random(0.000)+0.000;
	p.flags = BRIGHT | TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = Base_Effect8_base_event;
}

function Base_Effect7_base_event(PARTICLE* p) {
	p.vel_x = p.skill_x;
	p.vel_y = p.skill_y;
	p.vel_z = p.skill_z-p.skill_z*p.skill_d/50;
	if(p.creator)vec_rotate(p.vel_x,p.creator.pan);
	p.skill_d = (p.skill_d + time_step*(var)2.500)%100;
}

function Base_Effect7_base(PARTICLE* p) {
	p.size = random(4.793)+(7.207);
	p.alpha = random(25.457)+(12.543);
	p.red = 69;
	p.green = 124;
	p.blue = 180;
	p.skill_c = 0.5;
	p.vel_x = random(0.180)+(0.820);
	p.vel_y = random(0.449)+(2.051);
	p.vel_z = random(1.387)+(8.613);
	if(p.creator)vec_rotate(p.vel_x,p.creator.pan);
	vec_normalize(p.vel_x,10.355);
	p.lifespan = 40.000;
	p.gravity = random(0.000)+0.000;
	p.flags = BRIGHT | TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = Base_Effect7_base_event;
}

function Base_Effect6_base_event(PARTICLE* p) {
	p.vel_x = p.skill_x;
	p.vel_y = p.skill_y;
	p.vel_z = p.skill_z-p.skill_z*p.skill_d/50;
	if(p.creator)vec_rotate(p.vel_x,p.creator.pan);
	p.skill_d = (p.skill_d + time_step*(var)2.500)%100;
}

function Base_Effect6_base(PARTICLE* p) {
	p.size = random(4.793)+(7.207);
	p.alpha = random(25.457)+(12.543);
	p.red = 69;
	p.green = 124;
	p.blue = 180;
	p.skill_c = 0.5;
	p.vel_x = (0.000);
	p.vel_y = random(0.539)+(2.461);
	p.vel_z = random(1.387)+(8.613);
	if(p.creator)vec_rotate(p.vel_x,p.creator.pan);
	vec_normalize(p.vel_x,10.439);
	p.lifespan = 40.000;
	p.gravity = random(0.000)+0.000;
	p.flags = BRIGHT | TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = Base_Effect6_base_event;
}

function Base_Effect5_base_event(PARTICLE* p) {
	p.vel_x = p.skill_x;
	p.vel_y = p.skill_y;
	p.vel_z = p.skill_z-p.skill_z*p.skill_d/50;
	if(p.creator)vec_rotate(p.vel_x,p.creator.pan);
	p.skill_d = (p.skill_d + time_step*(var)2.500)%100;
}

function Base_Effect5_base(PARTICLE* p) {
	p.size = random(4.793)+(7.207);
	p.alpha = random(25.457)+(12.543);
	p.red = 69;
	p.green = 124;
	p.blue = 180;
	p.skill_c = 0.5;
	parted_temp_vec.x = random(0.000)+0.000;
	parted_temp_vec.y = random(8.000)+-4.000;
	parted_temp_vec.z = 0.000;
	if(p.creator)vec_rotate(parted_temp_vec,p.creator.pan);
	vec_add(p.x,parted_temp_vec);
	p.vel_x = random(0.539)+(2.461);
	p.vel_y = (0.000);
	p.vel_z = random(1.387)+(8.613);
	if(p.creator)vec_rotate(p.vel_x,p.creator.pan);
	vec_normalize(p.vel_x,10.439);
	p.lifespan = 40.000;
	p.gravity = random(0.000)+0.000;
	p.flags = BRIGHT | TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = Base_Effect5_base_event;
}

function Base_Effect4_base_event(PARTICLE* p) {
	p.vel_x = p.skill_x;
	p.vel_y = p.skill_y;
	p.vel_z = p.skill_z-p.skill_z*p.skill_d/50;
	if(p.creator)vec_rotate(p.vel_x,p.creator.pan);
	p.skill_d = (p.skill_d + time_step*(var)2.500)%100;
}

function Base_Effect4_base(PARTICLE* p) {
	p.size = random(4.793)+(7.207);
	p.alpha = random(25.457)+(12.543);
	p.red = 69;
	p.green = 124;
	p.blue = 180;
	p.skill_c = 0.5;
	p.vel_x = random(0.449)+(2.051);
	p.vel_y = random(0.180)+(0.820);
	p.vel_z = random(1.387)+(8.613);
	if(p.creator)vec_rotate(p.vel_x,p.creator.pan);
	vec_normalize(p.vel_x,10.355);
	p.lifespan = 40.000;
	p.gravity = random(0.000)+0.000;
	p.flags = BRIGHT | TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = Base_Effect4_base_event;
}

function Base_Effect3_base_event(PARTICLE* p) {
	p.vel_x = p.skill_x;
	p.vel_y = p.skill_y;
	p.vel_z = p.skill_z-p.skill_z*p.skill_d/50;
	if(p.creator)vec_rotate(p.vel_x,p.creator.pan);
	p.skill_d = (p.skill_d + time_step*(var)2.500)%100;
}

function Base_Effect3_base(PARTICLE* p) {
	p.size = random(4.793)+(7.207);
	p.alpha = random(25.457)+(12.543);
	p.red = 69;
	p.green = 124;
	p.blue = 180;
	p.skill_c = 0.5;
	p.vel_x = random(0.359)+(1.641);
	p.vel_y = random(0.359)+(1.641);
	p.vel_z = random(1.387)+(8.613);
	if(p.creator)vec_rotate(p.vel_x,p.creator.pan);
	vec_normalize(p.vel_x,10.392);
	p.lifespan = 40.000;
	p.gravity = random(0.000)+0.000;
	p.flags = BRIGHT | TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = Base_Effect3_base_event;
}

function Base_Effect2_base_event(PARTICLE* p) {
	p.vel_x = p.skill_x;
	p.vel_y = p.skill_y;
	p.vel_z = p.skill_z-p.skill_z*p.skill_d/50;
	if(p.creator)vec_rotate(p.vel_x,p.creator.pan);
	p.skill_d = (p.skill_d + time_step*(var)2.500)%100;
}

function Base_Effect2_base(PARTICLE* p) {
	p.size = random(4.793)+(7.207);
	p.alpha = random(25.457)+(12.543);
	p.red = 69;
	p.green = 124;
	p.blue = 180;
	p.skill_c = 0.5;
	p.vel_x = random(0.180)+(0.820);
	p.vel_y = random(0.449)+(2.051);
	p.vel_z = random(1.387)+(8.613);
	if(p.creator)vec_rotate(p.vel_x,p.creator.pan);
	vec_normalize(p.vel_x,10.355);
	p.lifespan = 40.000;
	p.gravity = random(0.000)+0.000;
	p.flags = BRIGHT | TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = Base_Effect2_base_event;
}

function Base_Effect1_base_event(PARTICLE* p) {
	p.vel_x = p.skill_x;
	p.vel_y = p.skill_y;
	p.vel_z = p.skill_z-p.skill_z*p.skill_d/50;
	if(p.creator)vec_rotate(p.vel_x,p.creator.pan);
	p.skill_d = (p.skill_d + time_step*(var)2.500)%100;
}

function Base_Effect1_base(PARTICLE* p) {
	p.size = random(4.793)+(7.207);
	p.alpha = random(25.457)+(12.543);
	p.red = 69;
	p.green = 124;
	p.blue = 180;
	p.skill_c = 0.5;
	p.vel_x = (0.000);
	p.vel_y = random(0.539)+(2.461);
	p.vel_z = random(1.387)+(8.613);
	if(p.creator)vec_rotate(p.vel_x,p.creator.pan);
	vec_normalize(p.vel_x,10.439);
	p.lifespan = 40.000;
	p.gravity = random(0.000)+0.000;
	p.flags = BRIGHT | TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = Base_Effect1_base_event;
}

/////////////////////////////////emitter actions/////////////////////////////////

action Base_Effect_emitter() {
	var eff_frac; eff_frac = 0;
	wait(1);
	while(my) {
		vec_set(parted_temp_vec,nullvector);
		vec_add(parted_temp_vec,my.x);
		if(!(total_frames % 2)) {
			eff_frac += 2.000*time_step*6.25;
			if(eff_frac >= 1){
				effect(Base_Effect_base,integer(eff_frac),parted_temp_vec,nullvector);
				eff_frac -= integer(eff_frac);
			}
		}
		parted_temp_vec.x = random(2.000)+-1.000;
		parted_temp_vec.y = random(6.000)+-3.000;
		parted_temp_vec.z = random(0.000)+0.000;
		vec_add(parted_temp_vec,my.x);
		if(!(total_frames % 2)) {
			eff_frac += 2.000*time_step*6.25;
			if(eff_frac >= 1){
				effect(Base_Effect14_base,integer(eff_frac),parted_temp_vec,nullvector);
				eff_frac -= integer(eff_frac);
			}
		}
		parted_temp_vec.x = random(4.000)+-2.000;
		parted_temp_vec.y = random(4.000)+-2.000;
		parted_temp_vec.z = random(0.000)+0.000;
		vec_add(parted_temp_vec,my.x);
		if(!(total_frames % 2)) {
			eff_frac += 2.000*time_step*6.25;
			if(eff_frac >= 1){
				effect(Base_Effect13_base,integer(eff_frac),parted_temp_vec,nullvector);
				eff_frac -= integer(eff_frac);
			}
		}
		parted_temp_vec.x = random(6.000)+-3.000;
		parted_temp_vec.y = random(2.000)+-1.000;
		parted_temp_vec.z = random(0.000)+0.000;
		vec_add(parted_temp_vec,my.x);
		if(!(total_frames % 2)) {
			eff_frac += 2.000*time_step*6.25;
			if(eff_frac >= 1){
				effect(Base_Effect12_base,integer(eff_frac),parted_temp_vec,nullvector);
				eff_frac -= integer(eff_frac);
			}
		}
		parted_temp_vec.x = random(8.000)+-4.000;
		parted_temp_vec.y = random(0.000)+0.000;
		parted_temp_vec.z = random(0.000)+0.000;
		vec_add(parted_temp_vec,my.x);
		if(!(total_frames % 2)) {
			eff_frac += 2.000*time_step*6.25;
			if(eff_frac >= 1){
				effect(Base_Effect11_base,integer(eff_frac),parted_temp_vec,nullvector);
				eff_frac -= integer(eff_frac);
			}
		}
		wait(1);
	}
}
action Base_Effect10_emitter() {
	var eff_frac; eff_frac = 0;
	wait(1);
	while(my) {
		vec_set(parted_temp_vec,nullvector);
		vec_add(parted_temp_vec,my.x);
		if(!(total_frames % 2)) {
			eff_frac += 2.000*time_step*6.25;
			if(eff_frac >= 1){
				effect(Base_Effect10_base,integer(eff_frac),parted_temp_vec,nullvector);
				eff_frac -= integer(eff_frac);
			}
		}
		parted_temp_vec.x = random(2.000)+-1.000;
		parted_temp_vec.y = random(6.000)+-3.000;
		parted_temp_vec.z = random(0.000)+0.000;
		vec_rotate(parted_temp_vec,my.pan);
		vec_add(parted_temp_vec,my.x);
		if(!(total_frames % 2)) {
			eff_frac += 2.000*time_step*6.25;
			if(eff_frac >= 1){
				effect(Base_Effect9_base,integer(eff_frac),parted_temp_vec,nullvector);
				eff_frac -= integer(eff_frac);
			}
		}
		parted_temp_vec.x = random(4.000)+-2.000;
		parted_temp_vec.y = random(4.000)+-2.000;
		parted_temp_vec.z = random(0.000)+0.000;
		vec_rotate(parted_temp_vec,my.pan);
		vec_add(parted_temp_vec,my.x);
		if(!(total_frames % 2)) {
			eff_frac += 2.000*time_step*6.25;
			if(eff_frac >= 1){
				effect(Base_Effect8_base,integer(eff_frac),parted_temp_vec,nullvector);
				eff_frac -= integer(eff_frac);
			}
		}
		parted_temp_vec.x = random(6.000)+-3.000;
		parted_temp_vec.y = random(2.000)+-1.000;
		parted_temp_vec.z = random(0.000)+0.000;
		vec_rotate(parted_temp_vec,my.pan);
		vec_add(parted_temp_vec,my.x);
		if(!(total_frames % 2)) {
			eff_frac += 2.000*time_step*6.25;
			if(eff_frac >= 1){
				effect(Base_Effect7_base,integer(eff_frac),parted_temp_vec,nullvector);
				eff_frac -= integer(eff_frac);
			}
		}
		parted_temp_vec.x = random(8.000)+-4.000;
		parted_temp_vec.y = random(0.000)+0.000;
		parted_temp_vec.z = random(0.000)+0.000;
		vec_rotate(parted_temp_vec,my.pan);
		vec_add(parted_temp_vec,my.x);
		if(!(total_frames % 2)) {
			eff_frac += 2.000*time_step*6.25;
			if(eff_frac >= 1){
				effect(Base_Effect6_base,integer(eff_frac),parted_temp_vec,nullvector);
				eff_frac -= integer(eff_frac);
			}
		}
		wait(1);
	}
}

action Base_Effect5_emitter() {
	var eff_frac; eff_frac = 0;
	wait(1);
	while(my) {
		vec_set(parted_temp_vec,nullvector);
		vec_add(parted_temp_vec,my.x);
		if(!(total_frames % 2)) {
			eff_frac += 2.000*time_step*6.25;
			if(eff_frac >= 1){
				effect(Base_Effect5_base,integer(eff_frac),parted_temp_vec,nullvector);
				eff_frac -= integer(eff_frac);
			}
		}
		parted_temp_vec.x = random(2.000)+-1.000;
		parted_temp_vec.y = random(6.000)+-3.000;
		parted_temp_vec.z = random(0.000)+0.000;
		vec_rotate(parted_temp_vec,my.pan);
		vec_add(parted_temp_vec,my.x);
		if(!(total_frames % 2)) {
			eff_frac += 2.000*time_step*6.25;
			if(eff_frac >= 1){
				effect(Base_Effect4_base,integer(eff_frac),parted_temp_vec,nullvector);
				eff_frac -= integer(eff_frac);
			}
		}
		parted_temp_vec.x = random(4.000)+-2.000;
		parted_temp_vec.y = random(4.000)+-2.000;
		parted_temp_vec.z = random(0.000)+0.000;
		vec_rotate(parted_temp_vec,my.pan);
		vec_add(parted_temp_vec,my.x);
		if(!(total_frames % 2)) {
			eff_frac += 2.000*time_step*6.25;
			if(eff_frac >= 1){
				effect(Base_Effect3_base,integer(eff_frac),parted_temp_vec,nullvector);
				eff_frac -= integer(eff_frac);
			}
		}
		parted_temp_vec.x = random(6.000)+-3.000;
		parted_temp_vec.y = random(2.000)+-1.000;
		parted_temp_vec.z = random(0.000)+0.000;
		vec_rotate(parted_temp_vec,my.pan);
		vec_add(parted_temp_vec,my.x);
		if(!(total_frames % 2)) {
			eff_frac += 2.000*time_step*6.25;
			if(eff_frac >= 1){
				effect(Base_Effect2_base,integer(eff_frac),parted_temp_vec,nullvector);
				eff_frac -= integer(eff_frac);
			}
		}
		parted_temp_vec.x = random(8.000)+-4.000;
		parted_temp_vec.y = random(0.000)+0.000;
		parted_temp_vec.z = random(0.000)+0.000;
		vec_rotate(parted_temp_vec,my.pan);
		vec_add(parted_temp_vec,my.x);
		if(!(total_frames % 2)) {
			eff_frac += 2.000*time_step*6.25;
			if(eff_frac >= 1){
				effect(Base_Effect1_base,integer(eff_frac),parted_temp_vec,nullvector);
				eff_frac -= integer(eff_frac);
			}
		}
		wait(1);
	}
}