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
	
	bmap = "panHome.bmp"; // 437x431
	
	button(0,0,"button_close_on.bmp","button_close_off.bmp","button_close_over.bmp",closewindow,NULL,NULL);
	
	button(88,35,"button_saveworld_on.png","button_saveworld_off.png","button_saveworld_over.png",NULL,NULL,NULL);
	button(119,80,"button_loadworld_on.png","button_loadworld_off.png","button_loadworld_over.png",NULL,NULL,NULL);
	button(113,123,"button_newworld_on.png","button_newworld_off.png","button_newworld_over.png",NULL,NULL,NULL);
	button(108,166,"button_worldset_on.png","button_worldset_off.png","button_worldset_over.png",NULL,NULL,NULL);
	button(34,212,"button_compileworld_on.png","button_compileworld_off.png","button_compileworld_over.png",NULL,NULL,NULL);
	button(50,255,"button_exitworld_on.png","button_exitworld_off.png","button_exitworld_over.png",NULL,NULL,NULL);
	
	on_click = dragpanel;
	
	flags = TRANSLUCENT;
}

PANEL *panProp_1 = { // Properties
	
	layer = 5;
	
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
	
	layer = 5;
	
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
	
	layer = 5;
	
	button_toggle(0,0,flag_PHY_on,flag_PHY,flag_PHY_on,flag_PHY_on,NULL,NULL,NULL);
	
	hslider(0,39,100,slider,0,100,v_friction);
	hslider(0,60,100,slider,0,100,v_bounciness);
	
	flags = OVERLAY;
	
}

PANEL *panProp = {
	layer = 2;
	
	bmap = "panProp.png";
	
	button(0,0,"button_close_on.bmp","button_close_off.bmp","button_close_over.bmp",closewindow,NULL,NULL);
	
	button_toggle(0,0,"button_generalattrib_on.bmp","button_generalattrib.bmp","button_generalattrib_on.bmp","button_generalattrib_on.bmp",switch_panProp,NULL,NULL);
	button_toggle(0,0,"button_material_on.bmp","button_material.bmp","button_material_on.bmp","button_material_on.bmp",switch_panProp,NULL,NULL);
	button_toggle(0,0,"button_physics_on.bmp","button_physics.bmp","button_physics_on.bmp","button_physics_on.bmp",switch_panProp,NULL,NULL);	
	//	button(0,0,"button_apply_on.bmp","button_apply.bmp","button_apply_on.bmp",NULL,NULL,NULL);
	
	on_click = dragpanel;
	
	flags = TRANSLUCENT;
}

PANEL *panMat_Sub1 = {
	layer = 2;
	
	bmap = "panMatEd.bmp";
	
	button(0,0,"button_close_on.bmp","button_close_off.bmp","button_close_over.bmp",closewindow,NULL,NULL);
	button(4,20,"button_savemat_on.bmp","button_savemat_off.bmp","button_savemat_on.bmp",mat_save,NULL,NULL);
	
	//	button(0,0,button_editmat_def,button_editmat_def,button_editmat_def,NULL,NULL,NULL);
	//	button(0,0,button_editmat_save,button_editmat_save,button_editmat_save,mat_save,NULL,NULL);
	//	
	// we need 14 sliders for ambient x3, specular x3, diffuse x3 and emissive x3
	// +power, +alpha.
	
	hslider(134,41,100,"slider.bmp",0,255,v_emissive_r);
	hslider(134,57,100,"slider.bmp",0,255,v_emissive_g);
	hslider(134,75,100,"slider.bmp",0,255,v_emissive_b);
	
	hslider(134,108,100,"slider.bmp",0,255,v_ambient_r);
	hslider(134,126,100,"slider.bmp",0,255,v_ambient_g);
	hslider(134,143,100,"slider.bmp",0,255,v_ambient_b);
	
	hslider(134,181,100,"slider.bmp",0,255,v_diffuse_r);
	hslider(134,199,100,"slider.bmp",0,255,v_diffuse_g);
	hslider(134,216,100,"slider.bmp",0,255,v_diffuse_b);
	
	hslider(134,251,100,"slider.bmp",0,255,v_specular_r);
	hslider(134,269,100,"slider.bmp",0,255,v_specular_g);
	hslider(134,286,100,"slider.bmp",0,255,v_specular_b);
	
	hslider(327,303,100,"slider.bmp",0,10,v_power);
	//	hslider(0,0,100,"slider.bmp",0,255,v_alpha_m);
	
	on_click = dragpanel;
	
	flags = OVERLAY | TRANSLUCENT;
}

PANEL *panSnd = {
	
	layer = 3;
	
	button(0,0,"button_close_on.bmp","button_close_off.bmp","button_close_over.bmp",closewindow,NULL,NULL);
	
	bmap = "panSnd.bmp";
	
	on_click = dragpanel;
	
	flags = TRANSLUCENT;
	
}

PANEL *panParticle = {
	
	layer = 3;
	
	button(0,0,"button_close_on.bmp","button_close_off.bmp","button_close_over.bmp",closewindow,NULL,NULL);
	
	bmap = "panParticle.bmp";
	
	on_click = dragpanel;
	
	flags = TRANSLUCENT;
	
}


PANEL *panMain_Top = {
	layer = 0;
	
	bmap = "panMain_Top.bmp";
	
	button_toggle(0,0,flag_MOVE_on,flag_MOVE,flag_MOVE_on,flag_MOVE_on,switch_to_move,NULL,NULL);
	button_toggle(0,0,flag_ROTATE_on,flag_ROTATE,flag_ROTATE_on,flag_ROTATE_on,switch_to_rotate,NULL,NULL);
	button_toggle(0,0,flag_SCALE_on,flag_SCALE,flag_SCALE_on,flag_SCALE_on,switch_to_scale,NULL,NULL);
	
	flags = OVERLAY | SHOW;
}

PANEL *panMain_Bottom = {
	layer = 0;
	
	bmap = "panMain_Bottom.bmp";
	
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
	
	layer = 5;
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
	
	layer = 5;
	bmap = "big_slider.bmp";
	
	// 800 = default
	hslider(0,0,800,"slider_panobj.bmp",0,100,ctrl);
	
}

PANEL *panObj_Main = {
	
	layer = 5;
	
	bmap = panObj_anms;
	
	//	flags = OVERLAY;
	
}

PANEL *panObj_Main_X = { // So that it won't get sticked with panObj_Main
	
	layer = 6;
	
	bmap = "button_cover.bmp";
	
	button(0,0,"button_close_on.bmp","button_close_off.bmp","button_close_over.bmp",closewindow,NULL,NULL);
	
	flags = OVERLAY;
	
}

PANEL *panLight = {
	
	layer = 2;
	
	bmap = "panLight.bmp";
	
	button(0,0,"button_close_on.bmp","button_close_off.bmp","button_close_over.bmp",closewindow,NULL,NULL);
	
	hslider(153,65,65,"slider.bmp",0,255,v_lred);
	hslider(153,87,65,"slider.bmp",0,255,v_lgreen);
	hslider(153,110,65,"slider.bmp",0,255,v_lblue);
	hslider(163,196,60,"slider.bmp",0,2000,v_lrange);
	
	button_toggle(105,260,flag_DISCO_on,flag_DISCO,flag_DISCO_on,flag_DISCO_on,NULL,NULL,NULL);
	button_toggle(105,280,flag_FLICK_on,flag_FLICK,flag_FLICK_on,flag_FLICK_on,NULL,NULL,NULL);
	
	on_click = dragpanel;
	
	flags = OVERLAY; // because of the checkboxes...
	
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

////////////////////////////////////////////////////////////
// Spiral
////////////////////////////////////////////////////////////
void New_Base_Effect_base_event(PARTICLE* p) {
	p.vel_x = sinv(p.skill_d*3.6+180)*p.skill_x;
	p.vel_y = cosv(p.skill_d*3.6)*p.skill_y;
	p.vel_z = p.skill_z;
	p.skill_d = (p.skill_d + time_step*(var)6.000)%100;
}

void New_Base_Effect_base(PARTICLE* p) {
	p.size = 4.000;
	p.alpha = 61.000;
	p.red = 128;
	p.green = 128;
	p.blue = 128;
	p.skill_c = 0.5;
	parted_temp_vec.x = random(6.582)+3.418;
	parted_temp_vec.y = random(7.188)+2.813;
	parted_temp_vec.z = random(6.582)+3.418;
	vec_add(p.x,parted_temp_vec);
	p.vel_x = random(2.598)+(7.402);
	p.vel_y = random(2.793)+(7.207);
	p.vel_z = (3.000);
	p.lifespan = 40.000;
	p.gravity = 0.000;
	p.bmap = point_blue_map;
	p.flags = BRIGHT | BEAM | STREAK | TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = New_Base_Effect_base_event;
}

void emit_spark() {
	var eff_frac; eff_frac = 0;
	wait(1);
	while(my) {
		vec_set(parted_temp_vec,nullvector);
		vec_add(parted_temp_vec,my.x);
		eff_frac += 4.000*time_step*6.25;
		if(eff_frac >= 1){
			effect(New_Base_Effect_base,integer(eff_frac),parted_temp_vec,nullvector);
			eff_frac -= integer(eff_frac);
		}
		wait(1);
	}
}

void p_spiral_create(VECTOR *position) {
	if(!position)position = nullvector;
	wait(3);
	you = ent_create(NULL,position,emit_spark);
	if(you) {
		vec_add(you.x,vector(371.551,349.278,0.000));
		vec_set(you.pan,vector(0.000,0.000,0.000));
		vec_set(you.scale_x,vector(1.000,1.000,1.000));
		set(you,PASSABLE);
		set(you,INVISIBLE);
	}
}

////////////////////////////////////////////////////////////
// Colorful spark
////////////////////////////////////////////////////////////
void Base_Effect_base_event(PARTICLE* p) {
	if(p.lifespan <= 13.000 || (p.skill_a & 1)) {
		p.skill_a |= 1;
		p.alpha = clamp(p.alpha-8.000* time_step,-1,100);
	}
	p.size -= 1.000* time_step;
	if(p.alpha < 0 || p.size < 0) p.lifespan = 0;
	p.vel_x = p.skill_x*p.skill_d/50;
	p.vel_y = p.skill_y*p.skill_d/50;
	p.vel_z = p.skill_z*p.skill_d/50;
	p.skill_d = (p.skill_d + time_step*(var)3.000)%100;
}

void Base_Effect_base(PARTICLE* p) {
	p.size = 29.000;
	p.alpha = 100.000;
	p.red = 128;
	p.green = 128;
	p.blue = 128;
	p.skill_c = 0.5;
	p.vel_x = random(12.000)+(-6.000);
	p.vel_y = random(12.000)+(-6.000);
	p.vel_z = random(12.000)+(-6.000);
	vec_normalize(p.vel_x,10.392);
	p.lifespan = 35.000;
	p.gravity = 0.000;
	p.flags = BRIGHT | BEAM | STREAK | TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = Base_Effect_base_event;
}


void Base_Effect1_base_event(PARTICLE* p) {
	if(p.lifespan <= 13.000 || (p.skill_a & 1)) {
		p.skill_a |= 1;
		p.alpha = clamp(p.alpha-8.000* time_step,-1,100);
	}
	p.size -= 1.000* time_step;
	if(p.alpha < 0 || p.size < 0) p.lifespan = 0;
	p.vel_x = p.skill_x*p.skill_d/50;
	p.vel_y = p.skill_y*p.skill_d/50;
	p.vel_z = p.skill_z*p.skill_d/50;
	p.skill_d = (p.skill_d + time_step*(var)3.000)%100;
}

void Base_Effect1_base(PARTICLE* p) {
	p.size = 29.000;
	p.alpha = 100.000;
	p.red = 228;
	p.green = 62;
	p.blue = 20;
	p.skill_c = 0.5;
	p.vel_x = random(12.000)+(-6.000);
	p.vel_y = random(12.000)+(-6.000);
	p.vel_z = random(12.000)+(-6.000);
	vec_normalize(p.vel_x,10.392);
	p.lifespan = 35.000;
	p.gravity = 0.000;
	p.flags = BRIGHT | BEAM | STREAK | TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = Base_Effect1_base_event;
}

void emit_colorfulspark() {
	var eff_frac; eff_frac = 0;
	wait(1);
	while(my) {
		parted_temp_vec.x = 0.000;
		parted_temp_vec.y = 0.000;
		parted_temp_vec.z = 0.000;
		vec_add(parted_temp_vec,my.x);
		eff_frac += 5.000*time_step*6.25;
		if(eff_frac >= 1){
			effect(Base_Effect_base,integer(eff_frac),parted_temp_vec,nullvector);
			eff_frac -= integer(eff_frac);
		}
		parted_temp_vec.x = 0.000;
		parted_temp_vec.y = 0.000;
		parted_temp_vec.z = 0.000;
		vec_add(parted_temp_vec,my.x);
		eff_frac += 3.000*time_step*6.25;
		if(eff_frac >= 1){
			effect(Base_Effect1_base,integer(eff_frac),parted_temp_vec,nullvector);
			eff_frac -= integer(eff_frac);
		}
		wait(1);
	}
}

void p_spark_colorful_create(VECTOR *position) {
	if(!position)position = nullvector;
	wait(3);
	you = ent_create(NULL,position,emit_colorfulspark);
	if(you) {
		vec_add(you.x,vector(60.425,91.578,0.000));
		vec_set(you.pan,vector(0.000,0.000,0.000));
		vec_set(you.scale_x,vector(1.000,1.000,1.000));
		set(you,PASSABLE);
		set(you,INVISIBLE);
	}
}

////////////////////////////////////////////////////////////
// Space hole
////////////////////////////////////////////////////////////
void Base_Effect2_base_event(PARTICLE* p) {
	p.alpha = clamp(p.alpha-4.000* time_step,-1,100);
	p.size += 2.000* time_step;
	if(p.lifespan <= 20.000 || (p.skill_a & 4)) {
		p.skill_a |= 4;
		p.vel_x += p.skill_x*2.000* time_step;
		p.vel_y += p.skill_y*2.000* time_step;
		p.vel_z += p.skill_z*2.000* time_step;
	}
	if(p.alpha < 0 || p.size < 0) p.lifespan = 0;
}

void Base_Effect2_base(PARTICLE* p) {
	p.size = 10.000;
	p.alpha = random(27.402)+(33.598);
	p.red = 159;
	p.green = 205;
	p.blue = 227;
	p.skill_c = 0.5;
	p.vel_x = random(4.000)+(-2.000);
	p.vel_y = random(4.000)+(-2.000);
	p.vel_z = random(4.000)+(-2.000);
	p.lifespan = 40.000;
	p.gravity = 0.000;
	p.bmap = sparkle1_map;
	p.flags = BRIGHT | BEAM | TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = Base_Effect2_base_event;
}

void emit_spacehole() {
	var eff_frac; eff_frac = 0;
	wait(1);
	while(my) {
		parted_temp_vec.x = 0.000;
		parted_temp_vec.y = 0.000;
		parted_temp_vec.z = 0.000;
		vec_add(parted_temp_vec,my.x);
		eff_frac += 6.000*time_step*6.25;
		if(eff_frac >= 1){
			effect(Base_Effect2_base,integer(eff_frac),parted_temp_vec,nullvector);
			eff_frac -= integer(eff_frac);
		}
		wait(1);
	}
}

void p_space_hole_create(VECTOR *position) {
	if(!position)position = nullvector;
	wait(3);
	you = ent_create(NULL,position,emit_spacehole);
	if(you) {
		vec_add(you.x,vector(414.936,660.420,69.408));
		vec_set(you.pan,vector(0.000,0.000,0.000));
		vec_set(you.scale_x,vector(1.000,1.000,1.000));
		set(you,PASSABLE);
		set(you,INVISIBLE);
	}
}

////////////////////////////////////////////////////////////
// Fountain #2
////////////////////////////////////////////////////////////
void Base_Effect15_base_event(PARTICLE* p) {
	p.vel_x = p.skill_x;
	p.vel_y = p.skill_y;
	p.vel_z = p.skill_z-p.skill_z*p.skill_d/50;
	p.skill_d = (p.skill_d + time_step*(var)2.500)%100;
}

void Base_Effect15_base(PARTICLE* p) {
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
	p.event = Base_Effect15_base_event;
}

void Base_Effect14_base_event(PARTICLE* p) {
	p.vel_x = p.skill_x;
	p.vel_y = p.skill_y;
	p.vel_z = p.skill_z-p.skill_z*p.skill_d/50;
	p.skill_d = (p.skill_d + time_step*(var)2.500)%100;
}

void Base_Effect14_base(PARTICLE* p) {
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

void Base_Effect13_base_event(PARTICLE* p) {
	p.vel_x = p.skill_x;
	p.vel_y = p.skill_y;
	p.vel_z = p.skill_z-p.skill_z*p.skill_d/50;
	p.skill_d = (p.skill_d + time_step*(var)2.500)%100;
}

void Base_Effect13_base(PARTICLE* p) {
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

void Base_Effect12_base_event(PARTICLE* p) {
	p.vel_x = p.skill_x;
	p.vel_y = p.skill_y;
	p.vel_z = p.skill_z-p.skill_z*p.skill_d/50;
	p.skill_d = (p.skill_d + time_step*(var)2.500)%100;
}

void Base_Effect12_base(PARTICLE* p) {
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

void Base_Effect11_base_event(PARTICLE* p) {
	p.vel_x = p.skill_x;
	p.vel_y = p.skill_y;
	p.vel_z = p.skill_z-p.skill_z*p.skill_d/50;
	p.skill_d = (p.skill_d + time_step*(var)2.500)%100;
}

void Base_Effect11_base(PARTICLE* p) {
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

void emit_fountain2() {
	var eff_frac; eff_frac = 0;
	wait(1);
	while(my) {
		vec_set(parted_temp_vec,nullvector);
		vec_add(parted_temp_vec,my.x);
		if(!(total_frames % 2)) {
			eff_frac += 2.000*time_step*6.25;
			if(eff_frac >= 1){
				effect(Base_Effect15_base,integer(eff_frac),parted_temp_vec,nullvector);
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

void p_fountain_2_create(VECTOR *position) {
	if(!position)position = nullvector;
	wait(3);
	you = ent_create(NULL,position,emit_fountain2);
	if(you) {
		vec_add(you.x,vector(-20.253,-9.493,0.000));
		vec_set(you.pan,vector(0.000,0.000,0.000));
		vec_set(you.scale_x,vector(1.000,1.000,1.000));
		set(you,PASSABLE);
		set(you,INVISIBLE);
	}
}

////////////////////////////////////////////////////////////
// Fountain #1
////////////////////////////////////////////////////////////
void Base_Effect3_base_event(PARTICLE* p) {
	if (p.lifespan > 20.000) {
		p.skill_a |= 1;
		p.size += 1.000* time_step;
	}
	if((p.lifespan <= 20.000 || (p.skill_a & 2)) && !(p.skill_a & 2)) {
		p.skill_a |= 2;
		p.gravity = 0.399;
	}
	if((p.lifespan <= 30.000 || (p.skill_a & 4)) && p.lifespan > 10.000) {
		p.skill_a |= 4;
		p.vel_x += p.skill_x*1.500* time_step;
	}
	if((p.lifespan <= 30.000 || (p.skill_a & 8)) && p.lifespan > 10.000) {
		p.skill_a |= 8;
		p.vel_y += p.skill_y*1.500* time_step;
	}
	if(p.lifespan <= 20.000 || (p.skill_a & 16)) {
		p.skill_a |= 16;
		p.size -= 1.000* time_step;
	}
	if((p.lifespan <= 6.000 || (p.skill_a & 32)) && !(p.skill_a & 32)) {
		p.skill_a |= 32;
		set(p,STREAK);
	}
	if((p.lifespan <= 6.000 || (p.skill_a & 64)) && !(p.skill_a & 64)) {
		p.skill_a |= 64;
		set(p,BEAM);
	}
	if(p.lifespan <= 10.000 || (p.skill_a & 128)) {
		p.skill_a |= 128;
		p.alpha = clamp(p.alpha-0.500* time_step,-1,100);
	}
	if(p.alpha < 0 || p.size < 0) p.lifespan = 0;
}

void Base_Effect3_base(PARTICLE* p) {
	p.size = 4.000;
	p.alpha = 9.000;
	p.red = 128;
	p.green = 128;
	p.blue = 128;
	p.skill_c = 0.5;
	p.vel_x = random(0.199)+(-0.100);
	p.vel_y = random(0.199)+(-0.100);
	p.vel_z = random(0.875)+(3.125);
	p.lifespan = 40.000;
	p.gravity = 0.000;
	p.bmap = point_blue_map;
	p.flags = BRIGHT | TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = Base_Effect3_base_event;
}


void emit_fountain1() {
	var my_time;my_time = 0;
	var timetable_num;timetable_num = 0;
	var eff_frac; eff_frac = 0;
	wait(1);
	while(my) {
		my_time += time_step/16;
		if(my_time >= 0.000)my_time = 0;
		timetable_num = 1;
		parted_temp_vec.x = 0.000;
		parted_temp_vec.y = 0.000;
		parted_temp_vec.z = 0.000;
		vec_add(parted_temp_vec,my.x);
		eff_frac += 3.000*timetable_num*time_step*6.25;
		if(eff_frac >= 1){
			effect(Base_Effect3_base,integer(eff_frac),parted_temp_vec,nullvector);
			eff_frac -= integer(eff_frac);
		}
		wait(1);
	}
}

void p_fountain_1_create(VECTOR *position) {
	if(!position)position = nullvector;
	wait(3);
	you = ent_create(NULL,position,emit_fountain1);
	if(you) {
		vec_add(you.x,vector(-200.174,290.466,0.000));
		vec_set(you.pan,vector(0.000,0.000,0.000));
		vec_set(you.scale_x,vector(1.000,1.000,1.000));
		set(you,PASSABLE);
		set(you,INVISIBLE);
	}
}

////////////////////////////////////////////////////////////
// Fire #2
////////////////////////////////////////////////////////////
void New_child2_child_event(PARTICLE* p) {
	p.alpha = clamp(p.alpha-5.000* time_step,-1,100);
	p.size -= 1.000* time_step;
	if(p.alpha < 0 || p.size < 0) p.lifespan = 0;
}

void New_child2_child(PARTICLE* p) {
	p.size = 14.000;
	p.alpha = 100.000;
	p.red = 113;
	p.green = 36;
	p.blue = 0;
	p.skill_c = 0.5;
	p.vel_x = random(2.000)+(-1.000);
	p.vel_y = random(2.000)+(-1.000);
	p.vel_z = (3.000);
	p.lifespan = 40.000;
	p.gravity = 0.000;
	p.flags = BRIGHT | TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = New_child2_child_event;
}

void New_child_child_event(PARTICLE* p) {
	p.size += 2.000* time_step;
	p.alpha = clamp(p.alpha-3.000* time_step,-1,100);
	if(p.alpha < 0 || p.size < 0) p.lifespan = 0;
}

void New_child_child(PARTICLE* p) {
	p.size = 20.000;
	p.alpha = random(45.555)+(22.445);
	p.red = 120;
	p.green = 120;
	p.blue = 120;
	p.skill_c = 0.5;
	p.vel_x = random(1.000)+(-0.500);
	p.vel_y = random(1.000)+(-0.500);
	p.vel_z = random(1.117)+(0.883);
	p.lifespan = 40.000;
	p.gravity = 0.000;
	p.flags = TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = New_child_child_event;
}

void Base_Effect4_base_event(PARTICLE* p) {
	if(p.alpha <= 2.000) {
		parted_temp_vec.x = 0.000;
		parted_temp_vec.y = 0.000;
		parted_temp_vec.z = 0.000;
		vec_add(parted_temp_vec,p.x);
		if(!(total_frames % 6)) {
			p.skill_c += 1.000*time_step*6.25;
			if(p.skill_c >= 1){
				effect(New_child2_child,integer(p.skill_c),parted_temp_vec,nullvector);
				p.skill_c -= integer(p.skill_c);
			}
		}
	}
	if(p.alpha <= 2.000) {
		parted_temp_vec.x = 0.000;
		parted_temp_vec.y = 0.000;
		parted_temp_vec.z = 0.000;
		vec_add(parted_temp_vec,p.x);
		if(!(total_frames % 5)) {
			p.skill_c += 1.000*time_step*6.25;
			if(p.skill_c >= 1){
				effect(New_child_child,integer(p.skill_c),parted_temp_vec,nullvector);
				p.skill_c -= integer(p.skill_c);
			}
		}
	}
	p.size += 0.399* time_step;
	if(p.lifespan <= 32.000 || (p.skill_a & 2)) {
		p.skill_a |= 2;
		p.alpha = clamp(p.alpha-4.000* time_step,-1,100);
	}
	if(p.alpha < 0 || p.size < 0) p.lifespan = 0;
}

void Base_Effect4_base(PARTICLE* p) {
	p.size = random(3.146)+(5.854);
	p.alpha = random(27.535)+(25.465);
	p.red = 255;
	p.green = 128;
	p.blue = 64;
	p.skill_c = 0.5;
	p.vel_x = random(0.287)+(0.013);
	p.vel_y = random(0.281)+(0.019);
	p.vel_z = random(1.246)+(1.153);
	p.lifespan = 50.000;
	p.gravity = 0.000;
	p.bmap = fire3_map;
	p.flags = BRIGHT | TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = Base_Effect4_base_event;
}

void New_effect1_base_event(PARTICLE* p) {
	p.size += 2.000* time_step;
	p.alpha = clamp(p.alpha-3.000* time_step,-1,100);
	if(p.alpha < 0 || p.size < 0) p.lifespan = 0;
}

void New_effect1_base(PARTICLE* p) {
	p.size = 8.000;
	p.alpha = 52.000;
	p.red = 77;
	p.green = 136;
	p.blue = 225;
	p.skill_c = 0.5;
	p.vel_x = random(0.199)+(-0.100);
	p.vel_y = random(0.199)+(-0.100);
	p.vel_z = random(0.781)+(0.618);
	p.lifespan = 40.000;
	p.gravity = 0.000;
	p.flags = TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = New_effect1_base_event;
}

void emit_fire2() {
	var my_time;my_time = 0;
	var timetable_num;timetable_num = 0;
	var eff_frac; eff_frac = 0;
	wait(1);
	while(my) {
		my_time += time_step/16;
		if(my_time >= 0.000)my_time = 0;
		timetable_num = 1;
		parted_temp_vec.x = random(10.000)+-5.000;
		parted_temp_vec.y = random(10.000)+-5.000;
		parted_temp_vec.z = random(0.000)+0.000;
		vec_add(parted_temp_vec,my.x);
		if(!(total_frames % 2) && timetable_num) {
			eff_frac += 2.000*timetable_num*time_step*6.25;
			if(eff_frac >= 1){
				effect(Base_Effect4_base,integer(eff_frac),parted_temp_vec,nullvector);
				eff_frac -= integer(eff_frac);
			}
		}
		timetable_num = 1;
		parted_temp_vec.x = random(10.000)+-5.000;
		parted_temp_vec.y = random(10.000)+-5.000;
		parted_temp_vec.z = random(0.000)+0.000;
		vec_add(parted_temp_vec,my.x);
		if(!(total_frames % 8) && timetable_num) {
			eff_frac += 1.000*timetable_num*time_step*6.25;
			if(eff_frac >= 1){
				effect(New_effect1_base,integer(eff_frac),parted_temp_vec,nullvector);
				eff_frac -= integer(eff_frac);
			}
		}
		wait(1);
	}
}

void p_fire_2_create(VECTOR *position) {
	if(!position)position = nullvector;
	wait(3);
	you = ent_create(NULL,position,emit_fire2);
	if(you) {
		vec_add(you.x,vector(-200.174,290.466,0.000));
		vec_set(you.pan,vector(0.000,0.000,0.000));
		vec_set(you.scale_x,vector(1.000,1.000,1.000));
		set(you,PASSABLE);
		set(you,INVISIBLE);
	}
}

////////////////////////////////////////////////////////////
// Fire #1
////////////////////////////////////////////////////////////
void New_child_child_event2(PARTICLE* p) {
	p.size += 1.000* time_step;
	p.alpha = clamp(p.alpha-2.000* time_step,-1,100);
	if(p.alpha < 0 || p.size < 0) p.lifespan = 0;
}

void New_child_child2(PARTICLE* p) {
	p.size = 8.000;
	p.alpha = 51.000;
	p.red = 29;
	p.green = 29;
	p.blue = 29;
	p.skill_c = 0.5;
	p.lifespan = 40.000;
	p.gravity = 0.000;
	p.flags = TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = New_child_child_event2;
}

void Base_Effect_base_event2(PARTICLE* p) {
	if(p.alpha <= 1.000) {
		parted_temp_vec.x = 0.000;
		parted_temp_vec.y = 0.000;
		parted_temp_vec.z = 0.000;
		vec_add(parted_temp_vec,p.x);
		parted_temp2_vec.x = random(2.000)+(-1.000);
		parted_temp2_vec.y = random(2.000)+(-1.000);
		parted_temp2_vec.z = (1.000);
		if(!(total_frames % 25)) {
			p.skill_c += 3.000*time_step*6.25;
			if(p.skill_c >= 1){
				effect(New_child_child2,integer(p.skill_c),parted_temp_vec,parted_temp2_vec);
				p.skill_c -= integer(p.skill_c);
			}
		}
	}
	p.alpha = clamp(p.alpha-3.000* time_step,-1,100);
	if(p.size >= 11.000 || (p.skill_a & 2)) {
		p.skill_a |= 2;
		p.size -= 1.000* time_step;
	}
	if(p.size <= 3.000 || (p.skill_a & 4)) {
		p.skill_a |= 4;
		p.size += 1.000* time_step;
	}
	if(p.alpha < 0 || p.size < 0) p.lifespan = 0;
}

void Base_Effect_base2(PARTICLE* p) {
	p.size = random(3.594)+(4.406);
	p.alpha = random(28.750)+(35.250);
	p.red = 128;
	p.green = 128;
	p.blue = 128;
	p.skill_c = 0.5;
	p.lifespan = 40.000;
	p.gravity = 0.000;
	p.bmap = fire1_map;
	p.flags = BRIGHT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = Base_Effect_base_event2;
}

void emit_fire1() {
	var my_time;my_time = 0;
	var timetable_num;timetable_num = 0;
	var eff_frac; eff_frac = 0;
	wait(1);
	while(my) {
		my_time += time_step/16;
		if(my_time >= 0.000)my_time = 0;
		timetable_num = 1;
		parted_temp_vec.x = random(20.000)+-10.000;
		parted_temp_vec.y = random(20.000)+-10.000;
		parted_temp_vec.z = random(5.098)+-0.098;
		vec_add(parted_temp_vec,my.x);
		parted_temp2_vec.x = random(0.600)+(-0.300);
		parted_temp2_vec.y = random(0.600)+(-0.300);
		parted_temp2_vec.z = random(0.239)+(0.261);
		eff_frac += 2.000*timetable_num*time_step*6.25;
		if(eff_frac >= 1){
			effect(Base_Effect_base2,integer(eff_frac),parted_temp_vec,parted_temp2_vec);
			eff_frac -= integer(eff_frac);
		}
		wait(1);
	}
}

void p_fire_1_create(VECTOR *position) {
	if(!position)position = nullvector;
	wait(3);
	you = ent_create(NULL,position,emit_fire1);
	if(you) {
		vec_add(you.x,vector(-27.054,186.542,14.000));
		vec_set(you.pan,vector(32.498,-25.617,-3.110));
		vec_set(you.scale_x,vector(1.000,1.000,1.000));
		set(you,PASSABLE);
		set(you,INVISIBLE);
	}
}

////////////////////////////////////////////////////////////
// Double Helix
////////////////////////////////////////////////////////////
void Base_Effect_base_event3(PARTICLE* p) {
	if(p.lifespan <= 40.000 || (p.skill_a & 1)) {
		p.skill_a |= 1;
		p.vel_z = -8.000;
		p.skill_z = p.vel_z;
	}
	if(p.alpha < 0 || p.size < 0) p.lifespan = 0;
	p.vel_x = sinv(p.skill_d*3.6+180)*p.skill_x;
	p.vel_y = cosv(p.skill_d*3.6)*p.skill_y;
	p.vel_z = p.skill_z;
	if(p.creator)vec_rotate(p.vel_x,p.creator.pan);
	p.skill_d = (p.skill_d + time_step*(var)11.000)%100;
}

void Base_Effect_base3(PARTICLE* p) {
	p.size = 4.000;
	p.alpha = 64.000;
	p.red = 128;
	p.green = 128;
	p.blue = 128;
	p.skill_c = 0.5;
	p.vel_x = random(2.773)+(17.227);
	p.vel_y = random(3.164)+(16.836);
	p.vel_z = (8.000);
	if(p.creator)vec_rotate(p.vel_x,p.creator.pan);
	p.lifespan = 80.000;
	p.gravity = 0.000;
	p.bmap = blitz1_map;
	p.flags = BRIGHT | STREAK | TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = Base_Effect_base_event3;
}

void Base_Effect1_base_event3(PARTICLE* p) {
	if(p.lifespan <= 40.000 || (p.skill_a & 1)) {
		p.skill_a |= 1;
		p.vel_z = -8.000;
		p.skill_z = p.vel_z;
	}
	if(p.alpha < 0 || p.size < 0) p.lifespan = 0;
	p.vel_x = sinv(p.skill_d*3.6+180)*p.skill_x;
	p.vel_y = cosv(p.skill_d*3.6)*p.skill_y;
	p.vel_z = p.skill_z;
	if(p.creator)vec_rotate(p.vel_x,p.creator.pan);
	p.skill_d = (p.skill_d + time_step*(var)11.000)%100;
}

void Base_Effect1_base3(PARTICLE* p) {
	p.size = 4.000;
	p.alpha = 64.000;
	p.red = 128;
	p.green = 128;
	p.blue = 128;
	p.skill_c = 0.5;
	p.vel_x = random(-2.773)+(-17.227);
	p.vel_y = random(-3.164)+(-16.836);
	p.vel_z = (8.000);
	if(p.creator)vec_rotate(p.vel_x,p.creator.pan);
	p.lifespan = 80.000;
	p.gravity = 0.000;
	p.bmap = blitz1_map;
	p.flags = BRIGHT | STREAK | TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = Base_Effect1_base_event3;
}

void emit_doublehelix() {
	var my_time;my_time = 0;
	var timetable_num;timetable_num = 0;
	var eff_frac; eff_frac = 0;
	wait(1);
	while(my) {
		my_time += time_step/16;
		if(my_time >= 0.000)my_time = 0;
		timetable_num = 1;
		parted_temp_vec.x = 20.000;
		parted_temp_vec.y = -20.000;
		parted_temp_vec.z = 0.000;
		vec_add(parted_temp_vec,my.x);
		if(!(total_frames % 3) && timetable_num) {
			eff_frac += 1.000*timetable_num*time_step*6.25;
			if(eff_frac >= 1){
				effect(Base_Effect_base3,integer(eff_frac),parted_temp_vec,nullvector);
				eff_frac -= integer(eff_frac);
			}
		}
		timetable_num = 1;
		parted_temp_vec.x = -20.000;
		parted_temp_vec.y = 20.000;
		parted_temp_vec.z = 0.000;
		vec_add(parted_temp_vec,my.x);
		if(!(total_frames % 3) && timetable_num) {
			eff_frac += 1.000*timetable_num*time_step*6.25;
			if(eff_frac >= 1){
				effect(Base_Effect1_base3,integer(eff_frac),parted_temp_vec,nullvector);
				eff_frac -= integer(eff_frac);
			}
		}
		wait(1);
	}
}

void p_double_helix_create(VECTOR *position) {
	if(!position)position = nullvector;
	wait(3);
	you = ent_create(NULL,position,emit_doublehelix);
	if(you) {
		vec_add(you.x,vector(-149.688,31.689,0.000));
		vec_set(you.pan,vector(0.000,0.000,0.000));
		vec_set(you.scale_x,vector(1.000,1.000,1.000));
		set(you,PASSABLE);
		set(you,INVISIBLE);
	}
}

////////////////////////////////////////////////////////////
// Composition
////////////////////////////////////////////////////////////
void star1_base(PARTICLE* p) {
	p.size = 6.000;
	p.alpha = 100.000;
	p.red = 128;
	p.green = 128;
	p.blue = 128;
	p.skill_c = 0.5;
	p.vel_x = random(10.000)+(-5.000);
	p.vel_y = random(10.000)+(-5.000);
	p.vel_z = random(10.000)+(-5.000);
	p.lifespan = 40.000;
	p.gravity = 0.000;
	p.bmap = star1_map;
	p.flags = BRIGHT | TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = NULL;
}

void second_base(PARTICLE* p) {
	p.size = 2.000;
	p.alpha = 100.000;
	p.red = 128;
	p.green = 128;
	p.blue = 128;
	p.skill_c = 0.5;
	p.vel_x = random(6.000)+(-3.000);
	p.vel_y = random(6.000)+(-3.000);
	p.vel_z = random(6.000)+(-3.000);
	p.lifespan = 40.000;
	p.gravity = 0.000;
	p.flags = BRIGHT | TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = NULL;
}

void firstb_base_event(PARTICLE* p) {
	p.alpha = clamp(p.alpha-3.000* time_step,-1,100);
	if(p.alpha < 0 || p.size < 0) p.lifespan = 0;
}

void firstb_base(PARTICLE* p) {
	p.size = 2.000;
	p.alpha = 100.000;
	p.red = 128;
	p.green = 128;
	p.blue = 128;
	p.skill_c = 0.5;
	p.vel_x = random(4.000)+(-2.000);
	p.vel_y = random(4.000)+(-2.000);
	p.vel_z = random(4.000)+(-2.000);
	p.lifespan = 40.000;
	p.gravity = 0.000;
	p.flags = BRIGHT | TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = firstb_base_event;
}

void first_base_event(PARTICLE* p) {
	p.alpha = clamp(p.alpha-5.000* time_step,-1,100);
	if(p.alpha < 0 || p.size < 0) p.lifespan = 0;
}

void first_base(PARTICLE* p) {
	p.size = 2.000;
	p.alpha = 100.000;
	p.red = 128;
	p.green = 128;
	p.blue = 128;
	p.skill_c = 0.5;
	p.vel_x = random(2.000)+(-1.000);
	p.vel_y = random(2.000)+(-1.000);
	p.vel_z = random(4.000)+(-2.000);
	p.lifespan = 40.000;
	p.gravity = 0.000;
	p.flags = BRIGHT | TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = first_base_event;
}

void standard_base(PARTICLE* p) {
	p.size = 4.000;
	p.alpha = 100.000;
	p.red = 128;
	p.green = 128;
	p.blue = 128;
	p.skill_c = 0.5;
	p.vel_x = random(6.000)+(-3.000);
	p.vel_y = random(6.000)+(-3.000);
	p.vel_z = random(6.000)+(-3.000);
	p.lifespan = 40.000;
	p.gravity = 0.000;
	p.flags = BRIGHT | TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = NULL;
}

void sparkleblue_base(PARTICLE* p) {
	p.size = 4.000;
	p.alpha = 100.000;
	p.red = 0;
	p.green = 0;
	p.blue = 255;
	p.skill_c = 0.5;
	p.vel_x = random(6.000)+(-3.000);
	p.vel_y = random(6.000)+(-3.000);
	p.vel_z = random(6.000)+(-3.000);
	p.lifespan = 40.000;
	p.gravity = 0.000;
	p.flags = BRIGHT | TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = NULL;
}

void emit_composition() {
	var my_time;my_time = 0;
	var timetable_num;timetable_num = 0;
	var eff_frac; eff_frac = 0;
	wait(1);
	while(my) {
		my_time += time_step/16;
		if(my_time >= 0.000)my_time = 0;
		timetable_num = 1;
		parted_temp_vec.x = 0.000;
		parted_temp_vec.y = 0.000;
		parted_temp_vec.z = 0.000;
		vec_add(parted_temp_vec,my.x);
		eff_frac += 4.000*timetable_num*time_step*6.25;
		if(eff_frac >= 1){
			effect(star1_base,integer(eff_frac),parted_temp_vec,nullvector);
			eff_frac -= integer(eff_frac);
		}
		timetable_num = 1;
		parted_temp_vec.x = 0.000;
		parted_temp_vec.y = 0.000;
		parted_temp_vec.z = 0.000;
		vec_add(parted_temp_vec,my.x);
		eff_frac += 1.000*timetable_num*time_step*6.25;
		if(eff_frac >= 1){
			effect(second_base,integer(eff_frac),parted_temp_vec,nullvector);
			eff_frac -= integer(eff_frac);
		}
		timetable_num = 1;
		parted_temp_vec.x = 0.000;
		parted_temp_vec.y = 0.000;
		parted_temp_vec.z = 0.000;
		vec_add(parted_temp_vec,my.x);
		eff_frac += 1.000*timetable_num*time_step*6.25;
		if(eff_frac >= 1){
			effect(firstb_base,integer(eff_frac),parted_temp_vec,nullvector);
			eff_frac -= integer(eff_frac);
		}
		timetable_num = 1;
		parted_temp_vec.x = 0.000;
		parted_temp_vec.y = 0.000;
		parted_temp_vec.z = 0.000;
		vec_add(parted_temp_vec,my.x);
		eff_frac += 1.000*timetable_num*time_step*6.25;
		if(eff_frac >= 1){
			effect(first_base,integer(eff_frac),parted_temp_vec,nullvector);
			eff_frac -= integer(eff_frac);
		}
		timetable_num = 1;
		parted_temp_vec.x = 0.000;
		parted_temp_vec.y = 0.000;
		parted_temp_vec.z = 0.000;
		vec_add(parted_temp_vec,my.x);
		eff_frac += 1.000*timetable_num*time_step*6.25;
		if(eff_frac >= 1){
			effect(standard_base,integer(eff_frac),parted_temp_vec,nullvector);
			eff_frac -= integer(eff_frac);
		}
		timetable_num = 1;
		parted_temp_vec.x = 0.000;
		parted_temp_vec.y = 0.000;
		parted_temp_vec.z = 0.000;
		vec_add(parted_temp_vec,my.x);
		eff_frac += 1.000*timetable_num*time_step*6.25;
		if(eff_frac >= 1){
			effect(sparkleblue_base,integer(eff_frac),parted_temp_vec,nullvector);
			eff_frac -= integer(eff_frac);
		}
		wait(1);
	}
}

void p_composition_create(VECTOR *position) {
	if(!position)position = nullvector;
	wait(3);
	you = ent_create(NULL,position,emit_composition);
	if(you) {
		vec_add(you.x,vector(-141.194,16.143,0.000));
		vec_set(you.pan,vector(0.000,0.000,0.000));
		vec_set(you.scale_x,vector(1.000,1.000,1.000));
		set(you,PASSABLE);
		set(you,INVISIBLE);
	}
}

////////////////////////////////////////////////////////////
// End of particle definition
////////////////////////////////////////////////////////////