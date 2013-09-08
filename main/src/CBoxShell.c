/*
--------------------------------------------------
CBoxShell.c

Contains GUI/HUD code.

TODO:
<+++



>+++

NOTES:
<+++

8.9.2013
- New World (Toolboxes, money, workers,...)
- Load World (A house that is being built)
- Options (Headquarters, for example)
- Credits (Behind the scenes-like stuff)
- Exit (An [X])

>+++
--------------------------------------------------
*/

PANEL *empty = {
	
	layer = 0;
	
}

PANEL *buttonlst_submenu_terrain = {
	layer = 1;
	
	bmap = "button_submenu_black.bmp";
	
	button(0,0,"torreeiffel_up.png","torreeiffel_up.png","torreeiffel_up.png",NULL,NULL,NULL);
	button(0,0,"torreeiffel_down.png","torreeiffel_down.png","torreeiffel_down.png",NULL,NULL,NULL);
	button(0,0,menu1_submenu3,menu1_submenu3_off,menu1_submenu3_over,NULL,NULL,NULL);
	button(0,0,menu1_submenu4,menu1_submenu4_off,menu1_submenu4_over,NULL,NULL,NULL);
	
	// The final button will be the back button.
	button(0,0,"button_back.png","button_back.png","button_back.png",GWindowClose,NULL,NULL);
	
	flags = OVERLAY;
}

PANEL *buttonlst_submenu_object = {
	layer = 1;
	
	bmap = "button_submenu_black.bmp";
	
	button(0,0,"tree.png","tree.png","tree.png",GObjectAddWindowShow,NULL,NULL);
	button(0,0,"fireworks256.png","fireworks256.png","fireworks256.png",GParticleAddWindowShow,NULL,NULL);
	button(0,0,"music.png","music.png","music.png",GSoundAddWindowShow,NULL,NULL);
	button(0,0,"tips.png","tips.png","tips.png",GLightAddWindowShow,NULL,NULL);
	
	button(0,0,"button_back.png","button_back.png","button_back.png",GWindowClose,NULL,NULL);
	
	flags = OVERLAY;
}

PANEL *buttonlst_submenu_path = {
	layer = 1;
	
	bmap = "button_submenu_black.bmp";
	
	button(0,0,menu3_submenu1,menu3_submenu1_off,menu3_submenu1_over,NULL,NULL,NULL);
	button(0,0,menu3_submenu2,menu3_submenu2_off,menu3_submenu2_over,NULL,NULL,NULL);
	//	button(0,0,menu3_submenu3,menu3_submenu3,menu3_submenu3,NULL,NULL,NULL);
	//	button(0,0,menu3_submenu4,menu3_submenu4,menu3_submenu4,NULL,NULL,NULL);
	
	button(0,0,"button_back.png","button_back.png","button_back.png",GWindowClose,NULL,NULL);
	
	flags = OVERLAY;
}

PANEL *panHome = {
	layer = 2;
	
	bmap = "panHome.bmp"; // 437x431
	
	button(0,0,"button_close_on.bmp","button_close_off.bmp","button_close_over.bmp",GWindowClose,NULL,NULL);
	
	button(88,35,"button_saveworld_on.png","button_saveworld_off.png","button_saveworld_over.png",GGameSave,NULL,NULL);
	button(119,80,"button_loadworld_on.png","button_loadworld_off.png","button_loadworld_over.png",GGameLoad,NULL,NULL);
	button(113,123,"button_newworld_on.png","button_newworld_off.png","button_newworld_over.png",GWorldNew,NULL,NULL);
	button(108,166,"button_worldset_on.png","button_worldset_off.png","button_worldset_over.png",NULL,NULL,NULL);
	button(34,212,"button_compileworld_on.png","button_compileworld_off.png","button_compileworld_over.png",NULL,NULL,NULL);
	button(50,255,"button_exitworld_on.png","button_exitworld_off.png","button_exitworld_over.png",NULL,NULL,NULL);
	
	on_click = GPanelDrag;
	
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
	
	button(2,170,"button_default_on.bmp","button_default_off.bmp","button_default_on.bmp",ObjectRestoreDefault,NULL,NULL);
	button(90,170,"button_randomrotate_on.bmp","button_randomrotate_off.bmp","button_randomrotate_on.bmp",ObjectRandomPan,NULL,NULL);
	
	hslider(0,221,100,slider,0,100,v_alpha);	
	hslider(0,268,100,slider,0,100,v_ambient);
	
	flags = OVERLAY;	
	
}

PANEL *panProp_2 = { // Materials
	
	layer = 5;
	
	button_toggle(0,0,"button_Mat1_on.bmp","button_Mat1.bmp","button_Mat1_on.bmp","button_Mat1_on.bmp",MaterialSelect,NULL,NULL);
	button_toggle(0,30,"button_Mat2_on.bmp","button_Mat2.bmp","button_Mat2_on.bmp","button_Mat2_on.bmp",MaterialSelect,NULL,NULL);
	button_toggle(0,60,"button_Mat3_on.bmp","button_Mat3.bmp","button_Mat3_on.bmp","button_Mat3_on.bmp",MaterialSelect,NULL,NULL);
	button_toggle(0,90,"button_Mat4_on.bmp","button_Mat4.bmp","button_Mat4_on.bmp","button_Mat4_on.bmp",MaterialSelect,NULL,NULL);
	button_toggle(0,120,"button_Mat5_on.bmp","button_Mat5.bmp","button_Mat5_on.bmp","button_Mat5_on.bmp",MaterialSelect,NULL,NULL);
	button_toggle(0,150,"button_Mat6_on.bmp","button_Mat6.bmp","button_Mat6_on.bmp","button_Mat6_on.bmp",MaterialSelect,NULL,NULL);
	button_toggle(0,180,"button_Mat7_on.bmp","button_Mat7.bmp","button_Mat7_on.bmp","button_Mat7_on.bmp",MaterialSelect,NULL,NULL);
	button_toggle(0,210,"button_Mat8_on.bmp","button_Mat8.bmp","button_Mat8_on.bmp","button_Mat8_on.bmp",MaterialSelect,NULL,NULL);
	button_toggle(0,240,"button_Mat9_on.bmp","button_Mat9.bmp","button_Mat9_on.bmp","button_Mat9_on.bmp",MaterialSelect,NULL,NULL);
	button_toggle(0,270,"button_Mat10_on.bmp","button_Mat10.bmp","button_Mat10_on.bmp","button_Mat10_on.bmp",MaterialSelect,NULL,NULL);
	button_toggle(0,300,"button_Mat11_on.bmp","button_Mat11.bmp","button_Mat11_on.bmp","button_Mat11_on.bmp",MaterialSelect,NULL,NULL);
	button_toggle(0,330,"button_Mat12_on.bmp","button_Mat12.bmp","button_Mat12_on.bmp","button_Mat12_on.bmp",MaterialSelect,NULL,NULL);
	button_toggle(0,360,"button_Mat13_on.bmp","button_Mat13.bmp","button_Mat13_on.bmp","button_Mat13_on.bmp",MaterialSelect,NULL,NULL);
	button_toggle(0,390,"button_Mat14_on.bmp","button_Mat14.bmp","button_Mat14_on.bmp","button_Mat14_on.bmp",MaterialSelect,NULL,NULL);
	button_toggle(0,420,"button_Mat15_on.bmp","button_Mat15.bmp","button_Mat15_on.bmp","button_Mat15_on.bmp",MaterialSelect,NULL,NULL);
	
	button(160,0,"box_icons_on.png","box_icons.png","box_icons_on.png",GMaterialEditorShow,NULL,NULL);
	
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
	
	button(0,0,"button_close_on.bmp","button_close_off.bmp","button_close_over.bmp",GWindowClose,NULL,NULL);
	
	button_toggle(0,0,"button_generalattrib_on.bmp","button_generalattrib.bmp","button_generalattrib_on.bmp","button_generalattrib_on.bmp",switch_panProp,NULL,NULL);
	button_toggle(0,0,"button_material_on.bmp","button_material.bmp","button_material_on.bmp","button_material_on.bmp",switch_panProp,NULL,NULL);
	button_toggle(0,0,"button_physics_on.bmp","button_physics.bmp","button_physics_on.bmp","button_physics_on.bmp",switch_panProp,NULL,NULL);	
	//	button(0,0,"button_apply_on.bmp","button_apply.bmp","button_apply_on.bmp",NULL,NULL,NULL);
	
	on_click = GPanelDrag;
	
	flags = TRANSLUCENT;
}

PANEL *panMat_Sub1 = {
	layer = 2;
	
	bmap = "panMatEd.bmp";
	
	button(0,0,"button_close_on.bmp","button_close_off.bmp","button_close_over.bmp",GWindowClose,NULL,NULL);
	button(4,20,"button_savemat_on.bmp","button_savemat_off.bmp","button_savemat_on.bmp",MaterialSave,NULL,NULL);
	
	//	button(0,0,button_editmat_def,button_editmat_def,button_editmat_def,NULL,NULL,NULL);
	//	button(0,0,button_editMaterialSave,button_editMaterialSave,button_editMaterialSave,MaterialSave,NULL,NULL);
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
	
	on_click = GPanelDrag;
	
	flags = OVERLAY | TRANSLUCENT;
}

PANEL *panSnd = {
	
	layer = 3;
	
	button(0,0,"button_close_on.bmp","button_close_off.bmp","button_close_over.bmp",GWindowClose,NULL,NULL);
	
	bmap = "panSnd.bmp";
	
	on_click = GPanelDrag;
	
	flags = TRANSLUCENT;
	
}

PANEL *panParticle = {
	
	layer = 3;
	
	button(0,0,"button_close_on.bmp","button_close_off.bmp","button_close_over.bmp",GWindowClose,NULL,NULL);
	
	bmap = "panParticle.bmp";
	
	on_click = GPanelDrag;
	
	flags = TRANSLUCENT;
	
}


PANEL *panMain_Top = {
	layer = 0;
	
	bmap = "panMain_Top.bmp";
	
	button_toggle(0,0,flag_MOVE_on,flag_MOVE,flag_MOVE_on,flag_MOVE_on,GSwitchToMoveMode,NULL,NULL);
	button_toggle(0,0,flag_ROTATE_on,flag_ROTATE,flag_ROTATE_on,flag_ROTATE_on,GSwitchToRotateMode,NULL,NULL);
	button_toggle(0,0,flag_SCALE_on,flag_SCALE,flag_SCALE_on,flag_SCALE_on,GSwitchToScaleMode,NULL,NULL);
	
	flags = OVERLAY | SHOW;
}

PANEL *panMain_Bottom = {
	layer = 0;
	
	bmap = "panMain_Bottom.bmp";
	
	button(0,0,"home.png","home.png","home.png",GHomeShow,NULL,NULL);
	//	button_toggle(0,0,"mouse_pointer_on.png","mouse_pointer.png","mouse_pointer_on.png","mouse_pointer_on.png",controlcam,NULL,NULL);
	button(0,0,"pathing.png","pathing.png","pathing.png",GTerrainSubmenuShow,NULL,NULL);
	button(0,0,"objects.png","objects.png","objects.png",GObjectSubmenuShow,NULL,NULL);
	button(0,0,"path_32.png","path_32.png","path_32.png",GPathSubmenuShow,NULL,NULL);
	
	
	flags = OVERLAY | SHOW;
}

PANEL *panMain_Play = {
	layer = 0;
	
	bmap = "panMain_Play.bmp";
	
	button(0,0,"v.png","button_ok.png","button_ok.png",LoadPlayground,NULL,NULL);
	
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
	
	button_toggle(0,0,flag_ANMS_on,flag_ANMS,flag_ANMS_on,flag_ANMS_on,GObjectTypeSwitcher,NULL,NULL);
	button_toggle(0,0,flag_ARCH_on,flag_ARCH,flag_ARCH_on,flag_ARCH_on,GObjectTypeSwitcher,NULL,NULL);
	button_toggle(0,0,flag_BLANDS_on,flag_BLANDS,flag_BLANDS_on,flag_BLANDS_on,GObjectTypeSwitcher,NULL,NULL);
	button_toggle(0,0,flag_CHARS_on,flag_CHARS,flag_CHARS_on,flag_CHARS_on,GObjectTypeSwitcher,NULL,NULL);
	button_toggle(0,0,flag_ETC_on,flag_ETC,flag_ETC_on,flag_ETC_on,GObjectTypeSwitcher,NULL,NULL);
	button_toggle(0,0,flag_FOOD_on,flag_FOOD,flag_FOOD_on,flag_FOOD_on,GObjectTypeSwitcher,NULL,NULL);
	button_toggle(0,0,flag_MACHS_on,flag_MACHS,flag_MACHS_on,flag_MACHS_on,GObjectTypeSwitcher,NULL,NULL);
	button_toggle(0,0,flag_PLANTS_on,flag_PLANTS,flag_PLANTS_on,flag_PLANTS_on,GObjectTypeSwitcher,NULL,NULL);
	button_toggle(0,0,flag_TPORTTS_on,flag_TPORTTS,flag_TPORTTS_on,flag_TPORTTS_on,GObjectTypeSwitcher,NULL,NULL);
	
	flags = OVERLAY;
	
}

PANEL *panObj_Subbar_slider = {
	
	layer = 5;
	bmap = "big_slider.bmp";
	
	// 800 = default
	hslider(0,0,800,"slider_panobj.bmp",0,100,SliderLimit);
	
}

PANEL *panObj_Main = {
	
	layer = 5;
	
	bmap = panObj_anms;
	
	//	flags = OVERLAY;
	
}

PANEL *anms = {
	
	layer = 6;
	bmap = "cover.bmp";
	
	pos_x = 0;
	
	button(0,0,"A_BADGER.bmp","A_BADGER.bmp","A_BADGER.bmp",load_ent_anms,NULL,NULL);
	button(0,0,"A_BAT.bmp","A_BAT.bmp","A_BAT.bmp",load_ent_anms,NULL,NULL);
	button(0,0,"A_BLUEBIRD.bmp","A_BLUEBIRD.bmp","A_BLUEBIRD.bmp",load_ent_anms,NULL,NULL);
	button(0,0,"A_BOAR.bmp","A_BOAR.bmp","A_BOAR.bmp",load_ent_anms,NULL,NULL);
	button(0,0,"A_BUG.bmp","A_BUG.bmp","A_BUG.bmp",load_ent_anms,NULL,NULL);
	button(0,0,"A_BURKEL.bmp","A_BURKEL.bmp","A_BURKEL.bmp",load_ent_anms,NULL,NULL);
	button(0,0,"A_BUTTTERFLY.bmp","A_BUTTTERFLY.bmp","A_BUTTTERFLY.bmp",load_ent_anms,NULL,NULL);
	button(0,0,"A_CROW.bmp","A_CROW.bmp","A_CROW.bmp",load_ent_anms,NULL,NULL);
	button(0,0,"A_FISH1.bmp","A_FISH1.bmp","A_FISH1.bmp",load_ent_anms,NULL,NULL);
	button(0,0,"A_FISH2.bmp","A_FISH2.bmp","A_FISH2.bmp",load_ent_anms,NULL,NULL);
	button(0,0,"A_FISH3.bmp","A_FISH3.bmp","A_FISH3.bmp",load_ent_anms,NULL,NULL);
	button(0,0,"A_FISH4.bmp","A_FISH4.bmp","A_FISH4.bmp",load_ent_anms,NULL,NULL);
	button(0,0,"A_FISH5.bmp","A_FISH5.bmp","A_FISH5.bmp",load_ent_anms,NULL,NULL);
	button(0,0,"A_FISH6.bmp","A_FISH6.bmp","A_FISH6.bmp",load_ent_anms,NULL,NULL);	
	button(0,0,"A_FISH7.bmp","A_FISH7.bmp","A_FISH7.bmp",load_ent_anms,NULL,NULL);	
	button(0,0,"A_FISH8.bmp","A_FISH8.bmp","A_FISH8.bmp",load_ent_anms,NULL,NULL);	
	button(0,0,"A_RAT.bmp","A_RAT.bmp","A_RAT.bmp",load_ent_anms,NULL,NULL);	
	button(0,0,"A_SNAKE.bmp","A_SNAKE.bmp","A_SNAKE.bmp",load_ent_anms,NULL,NULL);	
	
	flags = OVERLAY;
	
}

PANEL *arch = {
	
	layer = 6;
	bmap = "cover.bmp";
	
	pos_x = 0;
	
	button(0,0,"A__FRAME.bmp","A__FRAME.bmp","A__FRAME.bmp",load_ent_arch,NULL,NULL);
	button(0,0,"A_BUILDING1.bmp","A_BUILDING1.bmp","A_BUILDING1.bmp",load_ent_arch,NULL,NULL);
	button(0,0,"a_buildingwmb.bmp","a_buildingwmb.bmp","a_buildingwmb.bmp",load_ent_arch,NULL,NULL);
	button(0,0,"a_buildingwmb.bmp","a_buildingwmb.bmp","a_buildingwmb.bmp",load_ent_arch,NULL,NULL);
	button(0,0,"A_CHURCH.bmp","A_CHURCH.bmp","A_CHURCH.bmp",load_ent_arch,NULL,NULL);
	button(0,0,"A_CHURCH.bmp","A_CHURCH.bmp","A_CHURCH.bmp",load_ent_arch,NULL,NULL);
	button(0,0,"A_FENCE.bmp","A_FENCE.bmp","A_FENCE.bmp",load_ent_arch,NULL,NULL);
	button(0,0,"A_FENCE_CYLINDER.bmp","A_FENCE_CYLINDER.bmp","A_FENCE_CYLINDER.bmp",load_ent_arch,NULL,NULL);
	button(0,0,"A_GATE.bmp","A_GATE.bmp","A_GATE.bmp",load_ent_arch,NULL,NULL);
	button(0,0,"A_HOUSE1.bmp","A_HOUSE1.bmp","A_HOUSE1.bmp",load_ent_arch,NULL,NULL);
	button(0,0,"A_HOUSE2.bmp","A_HOUSE2.bmp","A_HOUSE2.bmp",load_ent_arch,NULL,NULL);
	button(0,0,"A_HOUSE3.bmp","A_HOUSE3.bmp","A_HOUSE3.bmp",load_ent_arch,NULL,NULL);
	button(0,0,"A_HUT.bmp","A_HUT.bmp","A_HUT.bmp",load_ent_arch,NULL,NULL);
	button(0,0,"A_TEMPLE_ENTRANCE.bmp","A_TEMPLE_ENTRANCE.bmp","A_TEMPLE_ENTRANCE.bmp",load_ent_arch,NULL,NULL);
	button(0,0,"A_WAREHOUSE.bmp","A_WAREHOUSE.bmp","A_WAREHOUSE.bmp",load_ent_arch,NULL,NULL);
	button(0,0,"A_WAREHOUSE1.bmp","A_WAREHOUSE1.bmp","A_WAREHOUSE1.bmp",load_ent_arch,NULL,NULL);
	button(0,0,"A_WAREHOUSE2.bmp","A_WAREHOUSE2.bmp","A_WAREHOUSE2.bmp",load_ent_arch,NULL,NULL);
	button(0,0,"A_WAREHOUSE3.bmp","A_WAREHOUSE3.bmp","A_WAREHOUSE3.bmp",load_ent_arch,NULL,NULL);
	button(0,0,"A_WAREHOUSE4.bmp","A_WAREHOUSE4.bmp","A_WAREHOUSE4.bmp",load_ent_arch,NULL,NULL);
	
	flags = OVERLAY;
	
}

PANEL *blands = {
	
	layer = 6;
	bmap = "cover.bmp";
	
	pos_x = 0;
	
	button(0,0,"L_DESERTGENERIC.bmp","L_DESERTGENERIC.bmp","L_DESERTGENERIC.bmp",load_ent_blands,NULL,NULL);
	button(0,0,"L_GREENLAND.bmp","L_GREENLAND.bmp","L_GREENLAND.bmp",load_ent_blands,NULL,NULL);
	button(0,0,"L_GREENLAND1.bmp","L_GREENLAND1.bmp","L_GREENLAND1.bmp",load_ent_blands,NULL,NULL);
	button(0,0,"L_GREENLAND_FAT.bmp","L_GREENLAND_FAT.bmp","L_GREENLAND_FAT.bmp",load_ent_blands,NULL,NULL);
	button(0,0,"L_MARSSURFACE.bmp","L_MARSSURFACE.bmp","L_MARSSURFACE.bmp",load_ent_blands,NULL,NULL);
	button(0,0,"L_OCEAN1.bmp","L_OCEAN1.bmp","L_OCEAN1.bmp",load_ent_blands,NULL,NULL);
	button(0,0,"L_OCEAN2.bmp","L_OCEAN2.bmp","L_OCEAN2.bmp",load_ent_blands,NULL,NULL);
	button(0,0,"L_STEPPEGENERIC.bmp","L_STEPPEGENERIC.bmp","L_STEPPEGENERIC.bmp",load_ent_blands,NULL,NULL);
	button(0,0,"L_STONEGENERIC.bmp","L_STONEGENERIC.bmp","L_STONEGENERIC.bmp",load_ent_blands,NULL,NULL);
	button(0,0,"L_WATER1.bmp","L_WATER1.bmp","L_WATER1.bmp",load_ent_blands,NULL,NULL);
	button(0,0,"L_WATER2.bmp","L_WATER2.bmp","L_WATER2.bmp",load_ent_blands,NULL,NULL);
	
	flags = OVERLAY;
	
}

PANEL *chars = {
	
	layer = 6;
	bmap = "cover.bmp";
	
	pos_x = 0;
	
	button(0,0,"C__007.bmp","C__007.bmp","C__007.bmp",load_ent_chars,NULL,NULL);
	button(0,0,"C_BADGUY.bmp","C_BADGUY.bmp","C_BADGUY.bmp",load_ent_chars,NULL,NULL);
	button(0,0,"C_BERZERKA.bmp","C_BERZERKA.bmp","C_BERZERKA.bmp",load_ent_chars,NULL,NULL);
	button(0,0,"C_CGIRL.bmp","C_CGIRL.bmp","C_CGIRL.bmp",load_ent_chars,NULL,NULL);
	button(0,0,"C_GUARD.bmp","C_GUARD.bmp","C_GUARD.bmp",load_ent_chars,NULL,NULL);
	button(0,0,"C_HCS_WARRIOR_C.bmp","C_HCS_WARRIOR_C.bmp","C_HCS_WARRIOR_C.bmp",load_ent_chars,NULL,NULL);
	button(0,0,"C_INMATE.bmp","C_INMATE.bmp","C_INMATE.bmp",load_ent_chars,NULL,NULL);
	button(0,0,"C_NINJA.bmp","C_NINJA.bmp","C_NINJA.bmp",load_ent_chars,NULL,NULL);
	button(0,0,"C_P_KING_OCHAN.bmp","C_P_KING_OCHAN.bmp","C_P_KING_OCHAN.bmp",load_ent_chars,NULL,NULL);
	button(0,0,"C_P_LOBSTER_MUTANT.bmp","C_P_LOBSTER_MUTANT.bmp","C_P_LOBSTER_MUTANT.bmp",load_ent_chars,NULL,NULL);
	button(0,0,"C_P_MARIO_H.bmp","C_P_MARIO_H.bmp","C_P_MARIO_H.bmp",load_ent_chars,NULL,NULL);
	button(0,0,"C_P_PIRATE.bmp","C_P_PIRATE.bmp","C_P_PIRATE.bmp",load_ent_chars,NULL,NULL);
	button(0,0,"C_P_R2_ROBOT.bmp","C_P_R2_ROBOT.bmp","C_P_R2_ROBOT.bmp",load_ent_chars,NULL,NULL);
	button(0,0,"C_P_SAUCER.bmp","C_P_SAUCER.bmp","C_P_SAUCER.bmp",load_ent_chars,NULL,NULL);
	button(0,0,"C_P_SKEL.bmp","C_P_SKEL.bmp","C_P_SKEL.bmp",load_ent_chars,NULL,NULL);
	button(0,0,"C_RABBIT.bmp","C_RABBIT.bmp","C_RABBIT.bmp",load_ent_chars,NULL,NULL);
	button(0,0,"C_SOLDIER.bmp","C_SOLDIER.bmp","C_SOLDIER.bmp",load_ent_chars,NULL,NULL);
	button(0,0,"C_TROOPER.bmp","C_TROOPER.bmp","C_TROOPER.bmp",load_ent_chars,NULL,NULL);
	button(0,0,"C_WARLOCK.bmp","C_WARLOCK.bmp","C_WARLOCK.bmp",load_ent_chars,NULL,NULL);
	button(0,0,"C_WITCH.bmp","C_WITCH.bmp","C_WITCH.bmp",load_ent_chars,NULL,NULL);
	
	flags = OVERLAY;
	
}

PANEL *etc = {
	
	layer = 6;
	bmap = "cover.bmp";
	
	pos_x = 0;
	
	button(0,0,"E_BALL10.bmp","E_BALL10.bmp","E_BALL10.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_BALL20.bmp","E_BALL20.bmp","E_BALL20.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_BALL30.bmp","E_BALL30.bmp","E_BALL30.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_BALL40.bmp","E_BALL40.bmp","E_BALL40.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_BALL50.bmp","E_BALL50.bmp","E_BALL50.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_BALL60.bmp","E_BALL60.bmp","E_BALL60.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_BALL70.bmp","E_BALL70.bmp","E_BALL70.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_BALL80.bmp","E_BALL80.bmp","E_BALL80.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_BALL90.bmp","E_BALL90.bmp","E_BALL90.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_BALL100.bmp","E_BALL100.bmp","E_BALL100.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_BALL110.bmp","E_BALL110.bmp","E_BALL110.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_BALL120.bmp","E_BALL120.bmp","E_BALL120.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_BALL130.bmp","E_BALL130.bmp","E_BALL130.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_BALL140.bmp","E_BALL140.bmp","E_BALL140.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_BALL150.bmp","E_BALL150.bmp","E_BALL150.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_BALL_WHITE0.bmp","E_BALL_WHITE0.bmp","E_BALL_WHITE0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_BALLOON0.bmp","E_BALLOON0.bmp","E_BALLOON0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_BARREL0.bmp","E_BARREL0.bmp","E_BARREL0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_BARREL010.bmp","E_BARREL010.bmp","E_BARREL010.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_BARREL020.bmp","E_BARREL020.bmp","E_BARREL020.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_BARREL030.bmp","E_BARREL030.bmp","E_BARREL030.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_BARREL040.bmp","E_BARREL040.bmp","E_BARREL040.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_BARREL050.bmp","E_BARREL050.bmp","E_BARREL050.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_BARREL060.bmp","E_BARREL060.bmp","E_BARREL060.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_BARREL070.bmp","E_BARREL070.bmp","E_BARREL070.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_BARREL080.bmp","E_BARREL080.bmp","E_BARREL080.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_BARREL90.bmp","E_BARREL90.bmp","E_BARREL90.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_BARRIER0.bmp","E_BARRIER0.bmp","E_BARRIER0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_BASKETBALLBASKET0.bmp","E_BASKETBALLBASKET0.bmp","E_BASKETBALLBASKET0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_BATTERY0.bmp","E_BATTERY0.bmp","E_BATTERY0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_BENCH0.bmp","E_BENCH0.bmp","E_BENCH0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_BENCH10.bmp","E_BENCH10.bmp","E_BENCH10.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_BENCH20.bmp","E_BENCH20.bmp","E_BENCH20.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_BENCH30.bmp","E_BENCH30.bmp","E_BENCH30.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_BENCH40.bmp","E_BENCH40.bmp","E_BENCH40.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_BENCH50.bmp","E_BENCH50.bmp","E_BENCH50.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_BENCH60.bmp","E_BENCH60.bmp","E_BENCH60.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_BENCH70.bmp","E_BENCH70.bmp","E_BENCH70.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_BENCH80.bmp","E_BENCH80.bmp","E_BENCH80.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_BILLARD10.bmp","E_BILLARD10.bmp","E_BILLARD10.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_BILLARDLAMP0.bmp","E_BILLARDLAMP0.bmp","E_BILLARDLAMP0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_BILLIARD0.bmp","E_BILLIARD0.bmp","E_BILLIARD0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_BILLIARD20.bmp","E_BILLIARD20.bmp","E_BILLIARD20.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_BILLIARD30.bmp","E_BILLIARD30.bmp","E_BILLIARD30.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_BILLIARD_QUEUE0.bmp","E_BILLIARD_QUEUE0.bmp","E_BILLIARD_QUEUE0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_BOOK10.bmp","E_BOOK10.bmp","E_BOOK10.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_BOOKS0.bmp","E_BOOKS0.bmp","E_BOOKS0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_BOOKS20.bmp","E_BOOKS20.bmp","E_BOOKS20.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_BOOKS30.bmp","E_BOOKS30.bmp","E_BOOKS30.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_BOOKSHELF0.bmp","E_BOOKSHELF0.bmp","E_BOOKSHELF0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_BOX0.bmp","E_BOX0.bmp","E_BOX0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_BOX10.bmp","E_BOX10.bmp","E_BOX10.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_CABINET0.bmp","E_CABINET0.bmp","E_CABINET0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_CABINET_CORNER0.bmp","E_CABINET_CORNER0.bmp","E_CABINET_CORNER0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_CD0.bmp","E_CD0.bmp","E_CD0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_CEMENT_BAG0.bmp","E_CEMENT_BAG0.bmp","E_CEMENT_BAG0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_CHAIR0.bmp","E_CHAIR0.bmp","E_CHAIR0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_CHAIR10.bmp","E_CHAIR10.bmp","E_CHAIR10.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_CHAIR20.bmp","E_CHAIR20.bmp","E_CHAIR20.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_CIGA0.bmp","E_CIGA0.bmp","E_CIGA0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_CLOCK0.bmp","E_CLOCK0.bmp","E_CLOCK0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_CLOUD0.bmp","E_CLOUD0.bmp","E_CLOUD0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_COIN0.bmp","E_COIN0.bmp","E_COIN0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_COLAMACH0.bmp","E_COLAMACH0.bmp","E_COLAMACH0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_CRATE0.bmp","E_CRATE0.bmp","E_CRATE0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_CRATE10.bmp","E_CRATE10.bmp","E_CRATE10.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_CRATE20.bmp","E_CRATE20.bmp","E_CRATE20.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_CRYSTAL0.bmp","E_CRYSTAL0.bmp","E_CRYSTAL0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_D_BOOTH_010.bmp","E_D_BOOTH_010.bmp","E_D_BOOTH_010.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_DOOR0.bmp","E_DOOR0.bmp","E_DOOR0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_DOOR10.bmp","E_DOOR10.bmp","E_DOOR10.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_DOOR20.bmp","E_DOOR20.bmp","E_DOOR20.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_DOOR30.bmp","E_DOOR30.bmp","E_DOOR30.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_DOOR40.bmp","E_DOOR40.bmp","E_DOOR40.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_DUMPSTER0.bmp","E_DUMPSTER0.bmp","E_DUMPSTER0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_EXTINGUISHER0.bmp","E_EXTINGUISHER0.bmp","E_EXTINGUISHER0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_EXTINGUISHER10.bmp","E_EXTINGUISHER10.bmp","E_EXTINGUISHER10.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_FENCE0.bmp","E_FENCE0.bmp","E_FENCE0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_FIRE0.bmp","E_FIRE0.bmp","E_FIRE0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_FLAG0.bmp","E_FLAG0.bmp","E_FLAG0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_FRIDGE0.bmp","E_FRIDGE0.bmp","E_FRIDGE0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_FRYING_PAN0.bmp","E_FRYING_PAN0.bmp","E_FRYING_PAN0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_GIFT_BOX0.bmp","E_GIFT_BOX0.bmp","E_GIFT_BOX0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_HYDRANT0.bmp","E_HYDRANT0.bmp","E_HYDRANT0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_IPOD0.bmp","E_IPOD0.bmp","E_IPOD0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_LAMP10.bmp","E_LAMP10.bmp","E_LAMP10.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_LAMP20.bmp","E_LAMP20.bmp","E_LAMP20.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_LAMP30.bmp","E_LAMP30.bmp","E_LAMP30.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_LAMP40.bmp","E_LAMP40.bmp","E_LAMP40.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_LEON_ARMOIRE0.bmp","E_LEON_ARMOIRE0.bmp","E_LEON_ARMOIRE0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_LEON_DESK0.bmp","E_LEON_DESK0.bmp","E_LEON_DESK0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_LIGHT0.bmp","E_LIGHT0.bmp","E_LIGHT0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_MIRROR0.bmp","E_MIRROR0.bmp","E_MIRROR0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_MIRROR10.bmp","E_MIRROR10.bmp","E_MIRROR10.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_PALETTE0.bmp","E_PALETTE0.bmp","E_PALETTE0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_PALETTE10.bmp","E_PALETTE10.bmp","E_PALETTE10.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_PARKINGMETER0.bmp","E_PARKINGMETER0.bmp","E_PARKINGMETER0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_PIANO0.bmp","E_PIANO0.bmp","E_PIANO0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_PICTURE0.bmp","E_PICTURE0.bmp","E_PICTURE0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_PICTURE10.bmp","E_PICTURE10.bmp","E_PICTURE10.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_PICTURE20.bmp","E_PICTURE20.bmp","E_PICTURE20.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_PICTURE30.bmp","E_PICTURE30.bmp","E_PICTURE30.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_PICTURE40.bmp","E_PICTURE40.bmp","E_PICTURE40.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_PICTURE50.bmp","E_PICTURE50.bmp","E_PICTURE50.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_PICTURE60.bmp","E_PICTURE60.bmp","E_PICTURE60.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_PICTURE70.bmp","E_PICTURE70.bmp","E_PICTURE70.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_PICTURE80.bmp","E_PICTURE80.bmp","E_PICTURE80.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_PIPE0.bmp","E_PIPE0.bmp","E_PIPE0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_PIPE10.bmp","E_PIPE10.bmp","E_PIPE10.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_PIPE20.bmp","E_PIPE20.bmp","E_PIPE20.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_PLATFORM0.bmp","E_PLATFORM0.bmp","E_PLATFORM0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_RAIL_LORE10.bmp","E_RAIL_LORE10.bmp","E_RAIL_LORE10.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_RAILWAY_45LEFT0.bmp","E_RAILWAY_45LEFT0.bmp","E_RAILWAY_45LEFT0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_RAILWAY_45RIGHT0.bmp","E_RAILWAY_45RIGHT0.bmp","E_RAILWAY_45RIGHT0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_RAILWAY_DOUBLESWITCH0.bmp","E_RAILWAY_DOUBLESWITCH0.bmp","E_RAILWAY_DOUBLESWITCH0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_RAILWAY_DOWN0.bmp","E_RAILWAY_DOWN0.bmp","E_RAILWAY_DOWN0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_RAILWAY_END0.bmp","E_RAILWAY_END0.bmp","E_RAILWAY_END0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_RAILWAY_SINGLESWITCH0.bmp","E_RAILWAY_SINGLESWITCH0.bmp","E_RAILWAY_SINGLESWITCH0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_RAILWAY_STRAIGHT0.bmp","E_RAILWAY_STRAIGHT0.bmp","E_RAILWAY_STRAIGHT0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_RAILWAY_UP0.bmp","E_RAILWAY_UP0.bmp","E_RAILWAY_UP0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_ROPE0.bmp","E_ROPE0.bmp","E_ROPE0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_SALONCH10.bmp","E_SALONCH10.bmp","E_SALONCH10.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_SIGN_300.bmp","E_SIGN_300.bmp","E_SIGN_300.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_SIGN_600.bmp","E_SIGN_600.bmp","E_SIGN_600.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_SIGN_900.bmp","E_SIGN_900.bmp","E_SIGN_900.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_SIGN_BICYCLELANE0.bmp","E_SIGN_BICYCLELANE0.bmp","E_SIGN_BICYCLELANE0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_SIGN_BOULDER0.bmp","E_SIGN_BOULDER0.bmp","E_SIGN_BOULDER0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_SIGN_BUMPY_ROAD0.bmp","E_SIGN_BUMPY_ROAD0.bmp","E_SIGN_BUMPY_ROAD0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_SIGN_CHURCH0.bmp","E_SIGN_CHURCH0.bmp","E_SIGN_CHURCH0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_SIGN_CROSSWINDS0.bmp","E_SIGN_CROSSWINDS0.bmp","E_SIGN_CROSSWINDS0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_SIGN_CURVE_AHEAD0.bmp","E_SIGN_CURVE_AHEAD0.bmp","E_SIGN_CURVE_AHEAD0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_SIGN_ENDMINIMUMSPEED0.bmp","E_SIGN_ENDMINIMUMSPEED0.bmp","E_SIGN_ENDMINIMUMSPEED0.bmp",load_ent_etc,NULL,NULL);
	button(0,0,"E_SIGN_EXIT0.bmp","E_SIGN_EXIT0.bmp","E_SIGN_EXIT0.bmp",load_ent_etc,NULL,NULL);	
	button(0,0,"E_SIGN_FOOTPATH0.bmp","E_SIGN_FOOTPATH0.bmp","E_SIGN_FOOTPATH0.bmp",load_ent_etc,NULL,NULL);	
	button(0,0,"E_SIGN_HOSPITAL0.bmp","E_SIGN_HOSPITAL0.bmp","E_SIGN_HOSPITAL0.bmp",load_ent_etc,NULL,NULL);	
	button(0,0,"E_SIGN_MINIMUMSPEED0.bmp","E_SIGN_MINIMUMSPEED0.bmp","E_SIGN_MINIMUMSPEED0.bmp",load_ent_etc,NULL,NULL);	
	button(0,0,"E_SIGN_NOENTRY0.bmp","E_SIGN_NOENTRY0.bmp","E_SIGN_NOENTRY0.bmp",load_ent_etc,NULL,NULL);	
	button(0,0,"E_SIGN_NOPARKING0.bmp","E_SIGN_NOPARKING0.bmp","E_SIGN_NOPARKING0.bmp",load_ent_etc,NULL,NULL);	
	button(0,0,"E_SIGN_NOPASSING0.bmp","E_SIGN_NOPASSING0.bmp","E_SIGN_NOPASSING0.bmp",load_ent_etc,NULL,NULL);	
	button(0,0,"E_SIGN_NOSTOPPING0.bmp","E_SIGN_NOSTOPPING0.bmp","E_SIGN_NOSTOPPING0.bmp",load_ent_etc,NULL,NULL);	
	button(0,0,"E_SIGN_NOVEHICLES0.bmp","E_SIGN_NOVEHICLES0.bmp","E_SIGN_NOVEHICLES0.bmp",load_ent_etc,NULL,NULL);	
	button(0,0,"E_SIGN_NOVISITOR0.bmp","E_SIGN_NOVISITOR0.bmp","E_SIGN_NOVISITOR0.bmp",load_ent_etc,NULL,NULL);	
	button(0,0,"E_SIGN_ONESIDE_ROAD_NARROW0.bmp","E_SIGN_ONESIDE_ROAD_NARROW0.bmp","E_SIGN_ONESIDE_ROAD_NARROW0.bmp",load_ent_etc,NULL,NULL);	
	button(0,0,"E_SIGN_PARKING0.bmp","E_SIGN_PARKING0.bmp","E_SIGN_PARKING0.bmp",load_ent_etc,NULL,NULL);	
	button(0,0,"E_SIGN_PEDCROSSING0.bmp","E_SIGN_PEDCROSSING0.bmp","E_SIGN_PEDCROSSING0.bmp",load_ent_etc,NULL,NULL);	
	button(0,0,"E_SIGN_PEDESTRIAN0.bmp","E_SIGN_PEDESTRIAN0.bmp","E_SIGN_PEDESTRIAN0.bmp",load_ent_etc,NULL,NULL);	
	button(0,0,"E_SIGN_PHONE0.bmp","E_SIGN_PHONE0.bmp","E_SIGN_PHONE0.bmp",load_ent_etc,NULL,NULL);	
	button(0,0,"E_SIGN_RAILROAD0.bmp","E_SIGN_RAILROAD0.bmp","E_SIGN_RAILROAD0.bmp",load_ent_etc,NULL,NULL);	
	button(0,0,"E_SIGN_ROAD_NARROW0.bmp","E_SIGN_ROAD_NARROW0.bmp","E_SIGN_ROAD_NARROW0.bmp",load_ent_etc,NULL,NULL);	
	button(0,0,"E_SIGN_ROUNDABOUT0.bmp","E_SIGN_ROUNDABOUT0.bmp","E_SIGN_ROUNDABOUT0.bmp",load_ent_etc,NULL,NULL);	
	button(0,0,"E_SIGN_SLIPPERY0.bmp","E_SIGN_SLIPPERY0.bmp","E_SIGN_SLIPPERY0.bmp",load_ent_etc,NULL,NULL);	
	button(0,0,"E_SIGN_TRAFFIC0.bmp","E_SIGN_TRAFFIC0.bmp","E_SIGN_TRAFFIC0.bmp",load_ent_etc,NULL,NULL);	
	button(0,0,"E_SIGN_TRAFFICLIGHTS0.bmp","E_SIGN_TRAFFICLIGHTS0.bmp","E_SIGN_TRAFFICLIGHTS0.bmp",load_ent_etc,NULL,NULL);	
	button(0,0,"E_SIGN_TURNSCROSSING0.bmp","E_SIGN_TURNSCROSSING0.bmp","E_SIGN_TURNSCROSSING0.bmp",load_ent_etc,NULL,NULL);	
	button(0,0,"E_SIGN_YIELD0.bmp","E_SIGN_YIELD0.bmp","E_SIGN_YIELD0.bmp",load_ent_etc,NULL,NULL);	
	button(0,0,"E_SOFA0.bmp","E_SOFA0.bmp","E_SOFA0.bmp",load_ent_etc,NULL,NULL);	
	button(0,0,"E_STREETLIGHT0.bmp","E_STREETLIGHT0.bmp","E_STREETLIGHT0.bmp",load_ent_etc,NULL,NULL);	
	button(0,0,"E_TABLE0.bmp","E_TABLE0.bmp","E_TABLE0.bmp",load_ent_etc,NULL,NULL);	
	button(0,0,"E_TABLE10.bmp","E_TABLE10.bmp","E_TABLE10.bmp",load_ent_etc,NULL,NULL);	
	button(0,0,"E_TABLE_BLOOD0.bmp","E_TABLE_BLOOD0.bmp","E_TABLE_BLOOD0.bmp",load_ent_etc,NULL,NULL);	
	button(0,0,"E_TARGET0.bmp","E_TARGET0.bmp","E_TARGET0.bmp",load_ent_etc,NULL,NULL);	
	button(0,0,"E_TARGET10.bmp","E_TARGET10.bmp","E_TARGET10.bmp",load_ent_etc,NULL,NULL);	
	button(0,0,"E_TORCH0.bmp","E_TORCH0.bmp","E_TORCH0.bmp",load_ent_etc,NULL,NULL);	
	button(0,0,"E_TRASHCAN0.bmp","E_TRASHCAN0.bmp","E_TRASHCAN0.bmp",load_ent_etc,NULL,NULL);	
	button(0,0,"E_TRASHCAN10.bmp","E_TRASHCAN10.bmp","E_TRASHCAN10.bmp",load_ent_etc,NULL,NULL);	
	button(0,0,"E_TRASHCAN20.bmp","E_TRASHCAN20.bmp","E_TRASHCAN20.bmp",load_ent_etc,NULL,NULL);	
	button(0,0,"E_TREASURE_CHEST0.bmp","E_TREASURE_CHEST0.bmp","E_TREASURE_CHEST0.bmp",load_ent_etc,NULL,NULL);	
	button(0,0,"E_WHEATPACK0.bmp","E_WHEATPACK0.bmp","E_WHEATPACK0.bmp",load_ent_etc,NULL,NULL);	
	button(0,0,"E_WOODCHAIR0.bmp","E_WOODCHAIR0.bmp","E_WOODCHAIR0.bmp",load_ent_etc,NULL,NULL);	
	button(0,0,"E_WOODCHAIR20.bmp","E_WOODCHAIR20.bmp","E_WOODCHAIR20.bmp",load_ent_etc,NULL,NULL);	
	
	flags = OVERLAY;
	
}

PANEL *food = {
	
	layer = 6;
	bmap = "cover.bmp";
	
	pos_x = 0;
	
	button(0,0,"F_APPLE_GREEN.bmp","F_APPLE_GREEN.bmp","F_APPLE_GREEN.bmp",load_ent_food,NULL,NULL);
	button(0,0,"F_APPLE_RED.bmp","F_APPLE_RED.bmp","F_APPLE_RED.bmp",load_ent_food,NULL,NULL);
	button(0,0,"F_BAGEL.bmp","F_BAGEL.bmp","F_BAGEL.bmp",load_ent_food,NULL,NULL);
	button(0,0,"F_BANANA.bmp","F_BANANA.bmp","F_BANANA.bmp",load_ent_food,NULL,NULL);
	button(0,0,"F_BREAD.bmp","F_BREAD.bmp","F_BREAD.bmp",load_ent_food,NULL,NULL);
	button(0,0,"F_BREAD_LOAF.bmp","F_BREAD_LOAF.bmp","F_BREAD_LOAF.bmp",load_ent_food,NULL,NULL);
	button(0,0,"F_CARROT.bmp","F_CARROT.bmp","F_CARROT.bmp",load_ent_food,NULL,NULL);
	button(0,0,"F_COOKIE.bmp","F_COOKIE.bmp","F_COOKIE.bmp",load_ent_food,NULL,NULL);
	button(0,0,"F_COOKIE1.bmp","F_COOKIE1.bmp","F_COOKIE1.bmp",load_ent_food,NULL,NULL);
	button(0,0,"F_COOKIE2.bmp","F_COOKIE2.bmp","F_COOKIE2.bmp",load_ent_food,NULL,NULL);
	button(0,0,"F_COOKIE3.bmp","F_COOKIE3.bmp","F_COOKIE3.bmp",load_ent_food,NULL,NULL);
	button(0,0,"F_CORN.bmp","F_CORN.bmp","F_CORN.bmp",load_ent_food,NULL,NULL);
	button(0,0,"F_CROISSAINT.bmp","F_CROISSAINT.bmp","F_CROISSAINT.bmp",load_ent_food,NULL,NULL);
	button(0,0,"F_APPLE_GREEN.bmp","F_APPLE_GREEN.bmp","F_APPLE_GREEN.bmp",load_ent_food,NULL,NULL);
	button(0,0,"F_DONUT.bmp","F_DONUT.bmp","F_DONUT.bmp",load_ent_food,NULL,NULL);
	button(0,0,"F_DONUT1.bmp","F_DONUT1.bmp","F_DONUT1.bmp",load_ent_food,NULL,NULL);
	button(0,0,"F_FOODSACK.bmp","F_FOODSACK.bmp","F_FOODSACK.bmp",load_ent_food,NULL,NULL);
	button(0,0,"F_GENERICF.bmp","F_GENERICF.bmp","F_GENERICF.bmp",load_ent_food,NULL,NULL);
	button(0,0,"F_HAMBURGER.bmp","F_HAMBURGER.bmp","F_HAMBURGER.bmp",load_ent_food,NULL,NULL);
	button(0,0,"F_HOTDOG.bmp","F_HOTDOG.bmp","F_HOTDOG.bmp",load_ent_food,NULL,NULL);
	button(0,0,"F_ICECREAM.bmp","F_ICECREAM.bmp","F_ICECREAM.bmp",load_ent_food,NULL,NULL);
	button(0,0,"F_NECTARINE.bmp","F_NECTARINE.bmp","F_NECTARINE.bmp",load_ent_food,NULL,NULL);
	button(0,0,"F_ORANGE.bmp","F_ORANGE.bmp","F_ORANGE.bmp",load_ent_food,NULL,NULL);
	button(0,0,"F_PEAR.bmp","F_PEAR.bmp","F_PEAR.bmp",load_ent_food,NULL,NULL);
	button(0,0,"F_PIZZA.bmp","F_PIZZA.bmp","F_PIZZA.bmp",load_ent_food,NULL,NULL);
	button(0,0,"F_SQUASH.bmp","F_SQUASH.bmp","F_SQUASH.bmp",load_ent_food,NULL,NULL);
	button(0,0,"F_STEAK.bmp","F_STEAK.bmp","F_STEAK.bmp",load_ent_food,NULL,NULL);
	button(0,0,"F_TOMATO.bmp","F_TOMATO.bmp","F_TOMATO.bmp",load_ent_food,NULL,NULL);
	button(0,0,"F_WATERMELON.bmp","F_WATERMELON.bmp","F_WATERMELON.bmp",load_ent_food,NULL,NULL);
	button(0,0,"F_WATERMELON_PIECE.bmp","F_WATERMELON_PIECE.bmp","F_WATERMELON_PIECE.bmp",load_ent_food,NULL,NULL);
	
	flags = OVERLAY;
	
}

PANEL *machs = {
	
	layer = 6;
	bmap = "cover.bmp";
	
	pos_x = 0;
	
	button(0,0,"M_CONSOLE.bmp","M_CONSOLE.bmp","M_CONSOLE.bmp",load_ent_machs,NULL,NULL);
	button(0,0,"M_GENERATOR.bmp","M_GENERATOR.bmp","M_GENERATOR.bmp",load_ent_machs,NULL,NULL);
	button(0,0,"M_GENERATOR1.bmp","M_GENERATOR1.bmp","M_GENERATOR1.bmp",load_ent_machs,NULL,NULL);
	button(0,0,"M_GENERATOR2.bmp","M_GENERATOR2.bmp","M_GENERATOR2.bmp",load_ent_machs,NULL,NULL);
	button(0,0,"M_HATCH.bmp","M_HATCH.bmp","M_HATCH.bmp",load_ent_machs,NULL,NULL);
	button(0,0,"M_POWERPLANT.bmp","M_POWERPLANT.bmp","M_POWERPLANT.bmp",load_ent_machs,NULL,NULL);
	button(0,0,"M_TURRET02.bmp","M_TURRET02.bmp","M_TURRET02.bmp",load_ent_machs,NULL,NULL);
	
	flags = OVERLAY;
	
}

PANEL *plants = {
	
	layer = 6;
	bmap = "cover.bmp";
	
	pos_x = 0;
	
	button(0,0,"BIGTREE2.bmp","BIGTREE2.bmp","BIGTREE2.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"BSTONE1.bmp","BSTONE1.bmp","BSTONE1.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"BSTONE2.bmp","BSTONE2.bmp","BSTONE2.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"BUSH1.bmp","BUSH1.bmp","BUSH1.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"BUSH3.bmp","BUSH3.bmp","BUSH3.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"BUSH7.bmp","BUSH7.bmp","BUSH7.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"D_14_LOD0.bmp","D_14_LOD0.bmp","D_14_LOD0.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"D_FANTASY_TREE1.bmp","D_FANTASY_TREE1.bmp","D_FANTASY_TREE1.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"D_FLOWER_10.bmp","D_FLOWER_10.bmp","D_FLOWER_10.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"D_FLOWER_6.bmp","D_FLOWER_6.bmp","D_FLOWER_6.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"D_LITGR.bmp","D_LITGR.bmp","D_LITGR.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"FERN_1.bmp","FERN_1.bmp","FERN_1.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"FLOWER_1.bmp","FLOWER_1.bmp","FLOWER_1.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"GPALM1.bmp","GPALM1.bmp","GPALM1.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"GRASS.bmp","GRASS.bmp","GRASS.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"GRASS1.bmp","GRASS1.bmp","GRASS1.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"GRASS2.bmp","GRASS2.bmp","GRASS2.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"GRASS3.bmp","GRASS3.bmp","GRASS3.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"GRASS_SCATT.bmp","GRASS_SCATT.bmp","GRASS_SCATT.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"INDOORPLANT.bmp","INDOORPLANT.bmp","INDOORPLANT.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"KAVA_PLANT.bmp","KAVA_PLANT.bmp","KAVA_PLANT.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"KAYA2.bmp","KAYA2.bmp","KAYA2.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"KAYA3.bmp","KAYA3.bmp","KAYA3.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"LIGHTRAY1.bmp","LIGHTRAY1.bmp","LIGHTRAY1.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"LP_BIRKE_KR.bmp","LP_BIRKE_KR.bmp","LP_BIRKE_KR.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"LP_BIRKE_ST.bmp","LP_BIRKE_ST.bmp","LP_BIRKE_ST.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"LP_BUSCH1.bmp","LP_BUSCH1.bmp","LP_BUSCH1.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"LP_CHUNK1.bmp","LP_CHUNK1.bmp","LP_CHUNK1.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"LP_FARN.bmp","LP_FARN.bmp","LP_FARN.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"LP_GRASS.bmp","LP_GRASS.bmp","LP_GRASS.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"LP_PINE1_KR.bmp","LP_PINE1_KR.bmp","LP_PINE1_KR.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"LP_PINE1_ST.bmp","LP_PINE1_ST.bmp","LP_PINE1_ST.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"LP_SPRUCE_KR.bmp","LP_SPRUCE_KR.bmp","LP_SPRUCE_KR.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"LP_SPRUCE_ST.bmp","LP_SPRUCE_ST.bmp","LP_SPRUCE_ST.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"LP_STONES.bmp","LP_STONES.bmp","LP_STONES.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"LP_TREE2_KR.bmp","LP_TREE2_KR.bmp","LP_TREE2_KR.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"LP_TREE2_ST.bmp","LP_TREE2_ST.bmp","LP_TREE2_ST.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"LP_TREE_TRCK.bmp","LP_TREE_TRCK.bmp","LP_TREE_TRCK.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"MUSHROOM1.bmp","MUSHROOM1.bmp","MUSHROOM1.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"MUSHROOM2.bmp","MUSHROOM2.bmp","MUSHROOM2.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"MUSHROOM3.bmp","MUSHROOM3.bmp","MUSHROOM3.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"MUSHROOMS1.bmp","MUSHROOMS1.bmp","MUSHROOMS1.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"MUSHROOMS2.bmp","MUSHROOMS2.bmp","MUSHROOMS2.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"PLANT1.bmp","PLANT1.bmp","PLANT1.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"PLATANE.bmp","PLATANE.bmp","PLATANE.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"RAYS1.bmp","RAYS1.bmp","RAYS1.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"RAYS2.bmp","RAYS2.bmp","RAYS2.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"SHRUB.bmp","SHRUB.bmp","SHRUB.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"SSTONE1.bmp","SSTONE1.bmp","SSTONE1.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"STONE_FOUNTAIN.bmp","STONE_FOUNTAIN.bmp","STONE_FOUNTAIN.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"STONE_GROUND_SMALL.bmp","STONE_GROUND_SMALL.bmp","STONE_GROUND_SMALL.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"TREE1.bmp","TREE1.bmp","TREE1.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"TREE2.bmp","TREE2.bmp","TREE2.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"TREE4.bmp","TREE4.bmp","TREE4.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"TREE5.bmp","TREE5.bmp","TREE5.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"TREE5_2.bmp","TREE5_2.bmp","TREE5_2.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"TREE_LO.bmp","TREE_LO.bmp","TREE_LO.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"TREE_LOG1.bmp","TREE_LOG1.bmp","TREE_LOG1.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"WATERFALL.bmp","WATERFALL.bmp","WATERFALL.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"WEED1.bmp","WEED1.bmp","WEED1.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"WEED2.bmp","WEED2.bmp","WEED2.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"WEED3.bmp","WEED3.bmp","WEED3.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"WEED4.bmp","WEED4.bmp","WEED4.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"WEED5.bmp","WEED5.bmp","WEED5.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"WEED6.bmp","WEED6.bmp","WEED6.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"WEED7.bmp","WEED7.bmp","WEED7.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"WEED8.bmp","WEED8.bmp","WEED8.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"WEED9.bmp","WEED9.bmp","WEED9.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"WEED10.bmp","WEED10.bmp","WEED10.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"WEED11.bmp","WEED11.bmp","WEED11.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"WEED12.bmp","WEED12.bmp","WEED12.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"WEED13.bmp","WEED13.bmp","WEED13.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"WEED14.bmp","WEED14.bmp","WEED14.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"WEED15.bmp","WEED15.bmp","WEED15.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"WEED16.bmp","WEED16.bmp","WEED16.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"WEED17.bmp","WEED17.bmp","WEED17.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"WEED18.bmp","WEED18.bmp","WEED18.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"WEED24.bmp","WEED24.bmp","WEED24.bmp",load_ent_plants,NULL,NULL);
	button(0,0,"WEEDM.bmp","WEEDM.bmp","WEEDM.bmp",load_ent_plants,NULL,NULL);
	
	flags = OVERLAY;
	
}

PANEL *tportts = {
	
	layer = 6;
	bmap = "cover.bmp";
	
	pos_x = 0;
	
	button(0,0,"T_BOMBER0.bmp","T_BOMBER0.bmp","T_BOMBER0.bmp",load_ent_tportts,NULL,NULL);
	button(0,0,"T_BOMBER10.bmp","T_BOMBER10.bmp","T_BOMBER10.bmp",load_ent_tportts,NULL,NULL);
	button(0,0,"T_CAR10.bmp","T_CAR10.bmp","T_CAR10.bmp",load_ent_tportts,NULL,NULL);
	button(0,0,"T_CAR20.bmp","T_CAR20.bmp","T_CAR20.bmp",load_ent_tportts,NULL,NULL);
	button(0,0,"T_CAR30.bmp","T_CAR30.bmp","T_CAR30.bmp",load_ent_tportts,NULL,NULL);
	button(0,0,"T_CAR40.bmp","T_CAR40.bmp","T_CAR40.bmp",load_ent_tportts,NULL,NULL);
	button(0,0,"T_CAR_MR20.bmp","T_CAR_MR20.bmp","T_CAR_MR20.bmp",load_ent_tportts,NULL,NULL);
	button(0,0,"T_F105_THUG0.bmp","T_F105_THUG0.bmp","T_F105_THUG0.bmp",load_ent_tportts,NULL,NULL);
	button(0,0,"T_F160.bmp","T_F160.bmp","T_F160.bmp",load_ent_tportts,NULL,NULL);
	button(0,0,"T_HOVER10.bmp","T_HOVER10.bmp","T_HOVER10.bmp",load_ent_tportts,NULL,NULL);
	button(0,0,"T_LANCASTER0.bmp","T_LANCASTER0.bmp","T_LANCASTER0.bmp",load_ent_tportts,NULL,NULL);
	button(0,0,"T_MCDF4_PHANTOM0.bmp","T_MCDF4_PHANTOM0.bmp","T_MCDF4_PHANTOM0.bmp",load_ent_tportts,NULL,NULL);
	button(0,0,"T_SHOPPINGCADDY0.bmp","T_SHOPPINGCADDY0.bmp","T_SHOPPINGCADDY0.bmp",load_ent_tportts,NULL,NULL);
	button(0,0,"T_TANK0.bmp","T_TANK0.bmp","T_TANK0.bmp",load_ent_tportts,NULL,NULL);
	button(0,0,"T_TANK10.bmp","T_TANK10.bmp","T_TANK10.bmp",load_ent_tportts,NULL,NULL);
	button(0,0,"T_TRAINPART0.bmp","T_TRAINPART0.bmp","T_TRAINPART0.bmp",load_ent_tportts,NULL,NULL);
	button(0,0,"T_VIPER0.bmp","T_VIPER0.bmp","T_VIPER0.bmp",load_ent_tportts,NULL,NULL);
	button(0,0,"T_WAGON0.bmp","T_WAGON0.bmp","T_WAGON0.bmp",load_ent_tportts,NULL,NULL);
	
	flags = OVERLAY;
	
}

PANEL *panObj_Main_X = { // So that it won't get sticked with panObj_Main
	
	layer = 6;
	
	bmap = "button_cover.bmp";
	
	button(0,0,"button_close_on.bmp","button_close_off.bmp","button_close_over.bmp",GWindowClose,NULL,NULL);
	
	flags = OVERLAY;
	
}

PANEL *panObj_Part_Main = {
	
	layer = 5;
	bmap = "panObj_parts.png";
	
}

PANEL *panObj_Part_Main_X = {
	
	layer = 6;
	
	bmap = "button_cover.bmp";
	
	button(0,0,"button_close_on.bmp","button_close_off.bmp","button_close_over.bmp",GWindowClose,NULL,NULL);
	
	flags = OVERLAY;
	
}

PANEL *panObj_Part_slider = {
	
	layer = 5;
	bmap = "big_slider.bmp";
	
	// 800 = default
	hslider(0,0,800,"slider_panobj.bmp",0,100,SliderLimit);
	
}

PANEL *panObj_Snd_Main = {
	
	layer = 5;
	bmap = "panObj_snds.png";
	
}

PANEL *panObj_Snd_Main_X = {
	
	layer = 6;
	
	bmap = "button_cover.bmp";
	
	button(0,0,"button_close_on.bmp","button_close_off.bmp","button_close_over.bmp",GWindowClose,NULL,NULL);
	
	flags = OVERLAY;
	
}

PANEL *panObj_Snd_slider = {
	
	layer = 5;
	bmap = "big_slider.bmp";
	
	// 800 = default
	hslider(0,0,800,"slider_panobj.bmp",0,100,SliderLimit);
	
}

PANEL *panLight = {
	
	layer = 2;
	
	bmap = "panLight.bmp";
	
	button(0,0,"button_close_on.bmp","button_close_off.bmp","button_close_over.bmp",GWindowClose,NULL,NULL);
	
	hslider(153,65,65,"slider.bmp",0,255,v_lred);
	hslider(153,87,65,"slider.bmp",0,255,v_lgreen);
	hslider(153,110,65,"slider.bmp",0,255,v_lblue);
	hslider(163,196,60,"slider.bmp",0,2000,v_lrange);
	
	button_toggle(105,260,flag_DISCO_on,flag_DISCO,flag_DISCO_on,flag_DISCO_on,NULL,NULL,NULL);
	button_toggle(105,280,flag_FLICK_on,flag_FLICK,flag_FLICK_on,flag_FLICK_on,NULL,NULL,NULL);
	
	on_click = GPanelDrag;
	
	flags = OVERLAY; // because of the checkboxes...
	
}

PANEL *panLightNoti = {
	
	layer = 5;
	bmap = "noti_light.bmp";
	
	pos_x = 10;
	pos_y = 10;
	
	flags = OVERLAY;
	
}

PANEL *panRotateHelp = {
	
	layer = 5;
	bmap = "panRotateHelp.png";
	
	flags = OVERLAY;
	
}

PANEL *panScaleHelp = {
	
	layer = 5;
	bmap = "panRotateHelp.png";
	
	flags = OVERLAY;
	
}

PANEL *panNewGame = {
	
	layer = 2;
	
	bmap = "panNewGame.bmp";
	
	// 1
	button(0,0,"button_close_on.bmp","button_close_off.bmp","button_close_over.bmp",GWindowClose,NULL,NULL);
	
	// 2
	button_toggle(145,60,"flag_new_on.bmp","flag_new_.bmp","flag_new_on.bmp","flag_new_on.bmp",GToggleLevelCreationMode,NULL,NULL);
	
	// 3
	button_toggle(465,60,"flag_new_on.bmp","flag_new_.bmp","flag_new_on.bmp","flag_new_on.bmp",GToggleLevelCreationMode,NULL,NULL);
	
	// Left
	hslider(66,400,100,"slider.bmp",1,255,v_fogr);
	hslider(66,419,100,"slider.bmp",1,255,v_fogg);
	hslider(66,438,100,"slider.bmp",1,255,v_fogb);
	hslider(138,464,100,"slider.bmp",100,8000,v_fogdensity);
	
	// 4
	button_toggle(150,365,"flag_select_ON.bmp","flag_select.bmp","flag_select_ON.bmp","flag_select_ON.bmp",NULL,NULL,NULL);
	
	// Right
	
	// 5
	button_toggle(546,87,"flag_select_ON.bmp","flag_select.bmp","flag_select_ON.bmp","flag_select_ON.bmp",NULL,NULL,NULL);
	// 6
	button_toggle(546,104,"flag_select_ON.bmp","flag_select.bmp","flag_select_ON.bmp","flag_select_ON.bmp",NULL,NULL,NULL);
	// 7
	button_toggle(546,120,"flag_select_ON.bmp","flag_select.bmp","flag_select_ON.bmp","flag_select_ON.bmp",NULL,NULL,NULL);
	
	hslider(546,173,100,"slider.bmp",.125,5,_moon_scale_fac);
	hslider(546,188,100,"slider.bmp",.1,255,_time_speed_night);
	hslider(546,203,100,"slider.bmp",.5,4,_night_sky_scale_x);
	hslider(546,218,100,"slider.bmp",1,500,_night_sky_speed_x);
	
	// 8
	button(605,460,"button_creatworld_on.bmp","button_creatworld_off.bmp","button_creatworld_on.bmp",LoadNewLevelFromWindow,NULL,NULL);
	
	flags = OVERLAY | TRANSLUCENT;
	
	on_click = GPanelDrag;
	
}

PANEL *panSaveGame = {
	
	layer = 2;
	
	bmap = "panSaveGame.bmp";
	
	button(0,0,"button_close_on.bmp","button_close_off.bmp","button_close_over.bmp",GWindowClose,NULL,NULL);
	
	button(20,25,slot1,slot1,slot1,SaveGameToSlot,NULL,NULL);
	button(126,25,slot2,slot2,slot2,SaveGameToSlot,NULL,NULL);
	button(232,25,slot3,slot3,slot3,SaveGameToSlot,NULL,NULL);
	button(20,131,slot4,slot4,slot4,SaveGameToSlot,NULL,NULL);
	button(126,131,slot5,slot5,slot5,SaveGameToSlot,NULL,NULL);
	button(232,131,slot6,slot6,slot6,SaveGameToSlot,NULL,NULL);
	button(20,237,slot7,slot7,slot7,SaveGameToSlot,NULL,NULL);
	button(126,237,slot8,slot8,slot8,SaveGameToSlot,NULL,NULL);
	button(232,237,slot9,slot9,slot9,SaveGameToSlot,NULL,NULL);
	//	button(0,180,slot10,slot10,slot10,SaveGameToSlot,NULL,NULL);
	//	button(0,200,slot11,slot11,slot11,SaveGameToSlot,NULL,NULL);
	//	button(0,220,slot12,slot12,slot12,SaveGameToSlot,NULL,NULL);
	//	button(0,240,slot13,slot13,slot13,SaveGameToSlot,NULL,NULL);
	//	button(0,260,slot14,slot14,slot14,SaveGameToSlot,NULL,NULL);
	//	button(0,280,slot15,slot15,slot15,SaveGameToSlot,NULL,NULL);
	//	button(0,300,slot16,slot16,slot16,SaveGameToSlot,NULL,NULL);
	//	button(0,320,slot17,slot17,slot17,SaveGameToSlot,NULL,NULL);
	//	button(0,340,slot18,slot18,slot18,SaveGameToSlot,NULL,NULL);
	//	button(0,360,slot19,slot19,slot19,SaveGameToSlot,NULL,NULL);
	//	button(0,380,slot20,slot20,slot20,SaveGameToSlot,NULL,NULL);
	
	flags = TRANSLUCENT;
	
	on_click = GPanelDrag;
	
}

PANEL *panLoadGame = {
	
	layer = 2;
	bmap = "panLoadGame.bmp";
	
	button(0,0,"button_close_on.bmp","button_close_off.bmp","button_close_over.bmp",GWindowClose,NULL,NULL);
	
	button(20,25,slot1,slot1,slot1,LoadGameFromSlot,NULL,NULL);
	button(126,25,slot2,slot2,slot2,LoadGameFromSlot,NULL,NULL);
	button(232,25,slot3,slot3,slot3,LoadGameFromSlot,NULL,NULL);
	button(20,131,slot4,slot4,slot4,LoadGameFromSlot,NULL,NULL);
	button(126,131,slot5,slot5,slot5,LoadGameFromSlot,NULL,NULL);
	button(232,131,slot6,slot6,slot6,LoadGameFromSlot,NULL,NULL);
	button(20,237,slot7,slot7,slot7,LoadGameFromSlot,NULL,NULL);
	button(126,237,slot8,slot8,slot8,LoadGameFromSlot,NULL,NULL);
	button(232,237,slot9,slot9,slot9,LoadGameFromSlot,NULL,NULL);
	//		button(100,180,slot10,slot10,slot10,LoadGameFromSlot,NULL,NULL);
	//		button(100,200,slot11,slot11,slot11,LoadGameFromSlot,NULL,NULL);
	//		button(100,220,slot12,slot12,slot12,LoadGameFromSlot,NULL,NULL);
	//		button(100,240,slot13,slot13,slot13,LoadGameFromSlot,NULL,NULL);
	//		button(100,260,slot14,slot14,slot14,LoadGameFromSlot,NULL,NULL);
	//		button(100,280,slot15,slot15,slot15,LoadGameFromSlot,NULL,NULL);
	//		button(100,300,slot16,slot16,slot16,LoadGameFromSlot,NULL,NULL);
	//		button(100,320,slot17,slot17,slot17,LoadGameFromSlot,NULL,NULL);
	//		button(100,340,slot18,slot18,slot18,LoadGameFromSlot,NULL,NULL);
	//		button(100,360,slot19,slot19,slot19,LoadGameFromSlot,NULL,NULL);
	//		button(100,380,slot20,slot20,slot20,LoadGameFromSlot,NULL,NULL);
	
	flags = TRANSLUCENT;
	
	on_click = GPanelDrag;
	
}

PANEL *panMMenu = {
	
	layer = 1;
	bmap = "panMMenu_Main.bmp";
	
	button(20,25,slot1,slot1,slot1,LoadGameFromSlot,NULL,NULL);
	button(126,25,slot2,slot2,slot2,LoadGameFromSlot,NULL,NULL);
	button(232,25,slot3,slot3,slot3,LoadGameFromSlot,NULL,NULL);
	button(20,131,slot4,slot4,slot4,LoadGameFromSlot,NULL,NULL);
	button(126,131,slot5,slot5,slot5,LoadGameFromSlot,NULL,NULL);
	button(232,131,slot6,slot6,slot6,LoadGameFromSlot,NULL,NULL);
	button(20,237,slot7,slot7,slot7,LoadGameFromSlot,NULL,NULL);
	button(126,237,slot8,slot8,slot8,LoadGameFromSlot,NULL,NULL);
	button(232,237,slot9,slot9,slot9,LoadGameFromSlot,NULL,NULL);
	
	button(5,359,"button_MMenu_New_on.png","button_MMenu_New_off.png","button_MMenu_New_on.png",GWorldNew,NULL,NULL);
	button(165,359,"button_MMenu_opt_on.png","button_MMenu_opt_off.png","button_MMenu_opt_on.png",NULL,NULL,NULL);
	button(5,402,"button_MMenu_cmp_on.png","button_MMenu_cmp_off.png","button_MMenu_cmp_on.png",NULL,NULL,NULL);
	button(165,402,"button_MMenu_dev_on.png","button_MMenu_dev_off.png","button_MMenu_dev_on.png",GShowCredits,NULL,NULL);
	
	flags = TRANSLUCENT;
	
}

PANEL *panMMenu_exit = {
	
	button(0,0,"button_close_on.bmp","button_close_off.bmp","button_close_over.bmp",GWindowClose,NULL,NULL);
	
	flags = TRANSLUCENT;
	
}

PANEL *panCAMRecorder = {
	
	layer = 3;
	bmap = "panCAMRecorder.bmp";
	
	flags = OVERLAY;
	
}

PANEL *panCAMRecorder_digits = {
	
	layer = 4;
	digits(0,0,2,"Arial#25b",1,sys_seconds);
	digits(0,0,2,"Arial#25b",1,sys_minutes);	
	digits(0,0,2,"Arial#25b",1,sys_hours);
	
}

PANEL *panCAMRecorderREC = {
	
	layer = 4;
	bmap = "panCAMRecorderREC.bmp";
	
	flags = OVERLAY;
	
}

PANEL *panScreenshot = {
	
	layer = 999;
	bmap = "panScreenshot.bmp";
	
	flags = TRANSLUCENT;
	alpha = 100;
	
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

void emit_spiral() {
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
	you = ent_create(NULL,position,emit_spiral);
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
// End of particle definition

////////////////////////////////////////////////////////////
// Entities will be defined here.
////////////////////////////////////////////////////////////
ENTITY *sky_horizon =
{ //this is needed to fix the bad 3dgs horizon merging
	type = "horizon.tga";
	layer = 5; 
	scale_x = 0.25;
	scale_y = 0.25;
	tilt = -60;//adjust this when you change sky_curve or sky_clip settings
	alpha = 100; 
	flags2 = SKY|SCENE;
	flags = TRANSLUCENT|PASSABLE;
}

ENTITY *sky_cloud1 =
{ 
	type = "clouds.tga";
	layer = 2;  
	u = cloud1_speed_x; 
	v = cloud1_speed_y; 
	scale_y = cloud1_scale_x; 
	scale_x = cloud1_scale_y; 
	tilt = -12;//-6; 
	flags2 = SKY|DOME; 
	flags = TRANSLUCENT|PASSABLE;
	alpha = cloud1_alpha; 
} 

ENTITY *sky_cloud2 =
{ 
	type = "clouds.tga";
	layer = 3;//4; 
	u = cloud2_speed_x; 
	v = cloud2_speed_y; 
	scale_x = cloud2_scale_x; 
	scale_y = cloud2_scale_y; 
	tilt = -10;//-5;
	flags2 = SKY|DOME; 
	flags = TRANSLUCENT|PASSABLE; 
	alpha = cloud2_alpha; 
}

//bad weather clouds
ENTITY *sky_cloud3 =
{ 
	type = "clouds_bad.tga";
	layer = 4; 
	u = cloud3_speed_x; 
	v = cloud3_speed_y; 
	scale_x = cloud3_scale_x; 
	scale_y = cloud3_scale_y; 
	tilt = -10;//-5;
	flags2 = SKY|DOME;
	flags = TRANSLUCENT|PASSABLE; 
	alpha = 0;//cloud3_alpha; 
}
`

ENTITY *sky_day =
{ 
	type = "sky_day.tga";
	layer = 1; 
	scale_x = 0.25;
	tilt = -20;//-10;
	red = sky_add_red;
	green = sky_add_green;
	blue = sky_add_blue;
	alpha = 60;//sky_alpha; 
	flags2 = SKY|SCENE; 
	flags = TRANSLUCENT|PASSABLE;
}

ENTITY *sky_sun =
{
	type = "sky_sun.tga";
	layer = 6;
	alpha = sun_alpha;
	flags2 = SKY;
	flags = TRANSLUCENT|PASSABLE|BRIGHT;
}

ENTITY *sky_suncorona =
{
	type = "sky_suncorona.tga";
	layer = 3;
	alpha = sun_corona_alpha;
	flags2 = SKY;
	flags = TRANSLUCENT|PASSABLE|BRIGHT;
}

ENTITY *sky_sunshine =
{
	type = "sky_sunshine.tga";
	layer = 7;
	alpha = sun_shine_alpha;
	flags2 = SKY;
	flags = TRANSLUCENT|PASSABLE|BRIGHT;
}

ENTITY *sky_night =
{ 
	type = "sky_night.tga";  
	layer = 1; 
	alpha = 0;//night_sky_alpha; 
	flags2 = SKY|DOME; 
	flags = TRANSLUCENT|PASSABLE; 
} 

ENTITY *sky_moon =
{
	type = "sky_moon.tga";
	layer = 2;
	alpha = moon_alpha;
	flags2 = SKY;
	flags = TRANSLUCENT|PASSABLE;
}

ENTITY *flare1_ent =
{
	type = "lens_01.tga";
	layer = 8;
	view = camera;
	scale_x = 2;
	scale_y = 2;
}

ENTITY *flare2_ent =
{
	type = "lens_02.tga";
	layer = 8;
	view = camera;
	scale_x = 2;
	scale_y = 2;
}

ENTITY *flare4_ent =
{
	type = "lens_04.tga";
	layer = 8;
	view = camera;
	scale_x = 2;
	scale_y = 2;
}

ENTITY *flare5_ent =
{
	type = "lens_05.tga";
	layer = 8;
	view = camera;
	scale_x = 2;
	scale_y = 2;
}

ENTITY *flare6_ent =
{
	type = "lens_06.tga";
	layer = 8;
	view = camera;
	scale_x = 2;
	scale_y = 2;
}

ENTITY *flare7_ent =
{
	type = "lens_07.tga";
	layer = 8;
	view = camera;
	scale_x = 2;
	scale_y = 2;
}

ENTITY *flare8_ent =
{
	type = "lens_08.tga";
	view = camera;
	layer = 8;
	scale_x = 2;
	scale_y = 2;
}

ENTITY *flare9_ent =
{
	type = "lens_09.tga";
	view = camera;
	layer = 8;
	scale_x = 2;
	scale_y = 2;
}
ENTITY *flare10_ent =
{
	type = "lens_10.tga";
	view = camera;
	layer = 8;
	scale_x = 2;
	scale_y = 2;
}

ENTITY *flare11_ent =
{
	type = "lens_11.tga";
	layer = 8;
	view = camera;
	scale_x = 2;
	scale_y = 2;
}

ENTITY *flare12_ent =
{
	type = "lens_12.tga";
	layer = 8;
	view = camera;
	scale_x = 2;
	scale_y = 2;
}

ENTITY *flare13_ent =
{
	type = "lens_13.tga";
	layer = 8;
	view = camera;
	scale_x = 2;
	scale_y = 2;
}

ENTITY *flare14_ent =
{
	type = "lens_14.tga";
	layer = 8;
	view = camera;	
	scale_x = 2.5;
	scale_y = 2.5;
}

ENTITY *flare15_ent =
{
	type = "lens_15.tga";
	layer = 8;
	view = camera;
	scale_x = 2;
	scale_y = 2;
}

ENTITY *flare16_ent =
{
	type = "lens_16.tga";
	layer = 8;
	view = camera;
	scale_x = 2;
	scale_y = 2;
}

ENTITY *flare17_ent =
{
	type = "lens_17.tga";
	layer = 8;
	view = camera;
	scale_x = 2;
	scale_y = 2;
}

ENTITY *flare18_ent =
{
	type = "lens_18.tga";
	layer = 8;
	view = camera;
	scale_x = 2;
	scale_y = 2;
}

ENTITY *flare19_ent =
{
	type = "lens_19.tga";
	layer = 8;
	view = camera;
	scale_x = 2;
	scale_y = 2;
}

ENTITY *flare20_ent =
{
	type = "lens_20.tga";
	layer = 8;
	view = camera;
	scale_x = 2.8;
	scale_y = 2.8;
}

/*
--------------------------------------------------
void GGUIUpdate(PANEL *wg)


--------------------------------------------------
*/
void GGUIUpdate(PANEL *wg) {
	
	if(wg == panHome) {
		
		pan_setpos(panHome,3,1,vector(bmap_width(panHome.bmap) - 38 - 15,0,0));
		
	}
	
	if(wg == panProp) 
	{
		
		int i;
		for(i = 2;i < 6;i++) pan_setpos(panProp,3,i,vector(4, 20 + 35*(i-2),0));

		pan_setpos(panProp,3,1,vector(bmap_width(panProp.bmap) - 38 - 15,0,0));
		
		//////////////////////////////////////////////////////////////
		panProp_1.pos_x = panProp.pos_x + 121;
		panProp_1.pos_y = panProp.pos_y + 75;
		
		panProp_2.pos_x = panProp.pos_x + 121;
		panProp_2.pos_y = panProp.pos_y + 43;
		
		panProp_3.pos_x = panProp.pos_x + 121;
		panProp_3.pos_y = panProp.pos_y + 75;
		//////////////////////////////////////////////////////////////
		
	}

	if(wg == panMat_Sub1) { 
		
		pan_setpos(panMat_Sub1,3,1,vector(bmap_width(panMat_Sub1.bmap) - 38 - 15,0,0));
	}

	if(wg == panLight) {
		
		pan_setpos(panLight,3,1,vector(bmap_width(panLight.bmap) - 38 - 15,0,0));
		
	}
	
	if(wg == panSnd) {
		
		pan_setpos(panSnd,3,1,vector(bmap_width(panSnd.bmap) - 38 - 15,0,0));
		
	}
	
	if(wg == panParticle) {
		
		pan_setpos(panParticle,3,1,vector(bmap_width(panParticle.bmap) - 38 - 15,0,0));
		
	}
	
	if(wg == panNewGame) {
		
		pan_setpos(panNewGame,3,1,vector(bmap_width(panNewGame.bmap) - 38 - 15,0,0));
		
	}
	
	if(wg == panLoadGame) {
		
		pan_setpos(panLoadGame,3,1,vector(bmap_width(panLoadGame.bmap) - 38 - 15,0,0));
		
	}
	
	if(wg == panSaveGame) {
		
		pan_setpos(panSaveGame,3,1,vector(bmap_width(panSaveGame.bmap) - 38 - 15,0,0));
		
	}
}

/* 
--------------------------------------------------
void GWindowClose(var id, PANEL *p)

Desc: id always = 1 cuz we don't have two closebuttons at the same time. 
only one PANEL * parameter isn't enough (and it won't work too) so 
this simple ugly hack should do the trick.
--------------------------------------------------
*/
void GWindowClose(var id, PANEL *p) {
	id = 1;
	
	if(p == panNewGame) reset(panNewGame,SHOW);
	if(p == panHome) reset(panHome,SHOW);

	if(p == panMat_Sub1) {
		reset(panMat_Sub1,SHOW);
		
		/* code to save changes */
		MaterialSave(); // So that I don't have to rewrite the saving code.
		
	}

	if(p == buttonlst_submenu_terrain) reset(buttonlst_submenu_terrain,SHOW);
	if(p == buttonlst_submenu_object) reset(buttonlst_submenu_object,SHOW);
	if(p == buttonlst_submenu_path) reset(buttonlst_submenu_path,SHOW);
	
	if(p == panObj_Main_X) { // This is a bit special, since panObj_Main_X will pop up ONLY if panObj_Main pops.
		
		reset(panObj_Main,SHOW);
		reset(panObj_Subbar,SHOW);
		reset(panObj_Subbar_slider,SHOW);
		reset(panObj_Main_X,SHOW);
		
		GObjectTypeBackgroundSwitcher(empty);
		
		SliderLimit = 0;
		
		GGUIShow();
		
	}
	
	if(p == panObj_Part_Main_X ) {
		
		reset(panObj_Part_Main,SHOW);
		reset(panObj_Part_slider,SHOW);
		reset(panObj_Part_Main_X,SHOW);
		
		SliderLimit = 0;
		
		GGUIShow();
		
	}
	
	if(p == panObj_Snd_Main_X) {
		
		reset(panObj_Snd_Main,SHOW);
		reset(panObj_Snd_slider,SHOW);
		reset(panObj_Snd_Main_X,SHOW);
		
		SliderLimit = 0;
		
		GGUIShow();
		
	}

	if(p == panLight) GLightWindowHide();
	if(p == panSnd) GSoundWindowHide();
	if(p == panParticle) GParticleWindowHide();
	if(p == panProp) GPropertiesWindowHide();
	
	if(p == panSaveGame) reset(panSaveGame,SHOW);
	if(p == panLoadGame) reset(panLoadGame,SHOW);
	
	if(p == panMMenu_exit) {
		
		ConfigFileWrite("./src/cfg/cfg.cfg");
		sys_exit(NULL);
		
	}
}

/* 
--------------------------------------------------
void GToggleLevelCreationMode(var ID)


--------------------------------------------------
*/
void GToggleLevelCreationMode(var ID) {
	
	if(ID == 2) button_state(panNewGame,3,0);
	else button_state(panNewGame,2,0);
	
}


/* 
--------------------------------------------------
void GGameLoad()


--------------------------------------------------
*/
void GGameLoad() {
	
	GPanelCenter(panSaveGame);   
	GGUIUpdate(panLoadGame);
	
	set(panLoadGame,SHOW);
	
	GPanelSelect(panLoadGame);
	
}

/* 
--------------------------------------------------
void GGameSave()


--------------------------------------------------
*/
void GGameSave() {
	
	GPanelCenter(panSaveGame);
	GGUIUpdate(panSaveGame);
	
	set(panSaveGame,SHOW);
	
	GPanelSelect(panSaveGame);
	
}

/* 
--------------------------------------------------
void GGPanelDrag(PANEL *p)


--------------------------------------------------
*/
void GPanelDrag(PANEL *p)
{

	var click_offset[2];

	click_offset[0]=p.pos_x - mouse_pos.x;
	click_offset[1]=p.pos_y - mouse_pos.y;

	GPanelSelect(p);

	while(mouse_left)
	{
		proc_mode = PROC_EARLY;
		
		p.pos_x = mouse_pos.x+click_offset[0];
		p.pos_y = mouse_pos.y+click_offset[1];
		
		//hack hack hack!!!!
		if(p == panHome) GGUIUpdate(panHome);
		if(p == panProp) GGUIUpdate(panProp);
		if(p == panNewGame) GGUIUpdate(panNewGame);
		
		wait(1);
	}

	//hack to prevent shit happens. f.e. after dragged the guis' elements didn't retain their original location.
	if(p == panHome) GGUIUpdate(panHome);
	if(p == panProp) GGUIUpdate(panProp);
	if(p == panNewGame) GGUIUpdate(panNewGame);
}

/* 
--------------------------------------------------
void GPanelCenter(PANEL *p)


--------------------------------------------------
*/
void GPanelCenter(PANEL *p) {
	while(p == NULL) wait(1);

	p.pos_x = (screen_size.x - bmap_width(p.bmap)) / 2; 
	p.pos_y = (screen_size.y - bmap_height(p.bmap)) / 2;
}

/* 
--------------------------------------------------
void GPanelCenterInside(PANEL *p, PANEL *s)


--------------------------------------------------
*/
void GPanelCenterInside(PANEL *p, PANEL *s) {
	while(p == NULL || s == NULL) wait(1);

	// peform a S comparison
	if(bmap_width(p.bmap)*bmap_height(p.bmap) > bmap_width(s.bmap)*bmap_height(s.bmap)) {
		
		printf("The size of the image that needs to be centered is too large.\nTry resizing it.");
		return;
		
	}

	if(bmap_width(s.bmap) > bmap_width(p.bmap))
	p.pos_x = (bmap_width(s.bmap) - bmap_width(p.bmap))/2;

	if(bmap_height(s.bmap) > bmap_height(p.bmap))
	p.pos_y = (bmap_height(s.bmap) - bmap_height(p.bmap))/2;
}

/*
--------------------------------------------------
void GPanelRotate(PANEL *p,var lim,var speed,BOOL rotate_on_center)


--------------------------------------------------
*/
void GPanelRotate(PANEL *p,var lim,var speed,BOOL rotate_on_center)
{
	while(p == NULL && !is(p,SHOW)) wait(1);
	
	if(rotate_on_center)
	{
		p->center_x = p->size_x * 0.5;
		p->center_y = p->size_y * 0.5;
	}
	while(p->angle < lim)
	{
		p->angle += speed * time_step;
		wait(1);
	}
	p->angle = 0; 
}

/*
--------------------------------------------------
void GPanelResize(PANEL *p, char c)


--------------------------------------------------
*/
void GPanelResize(PANEL *p, char c) {
	
	while(p == NULL) wait(1);
	
	switch(c) {
		
		case 'x': p.scale_x = screen_size.x/bmap_width(p.bmap);
		break;
		
		case 'y': p.scale_y = screen_size.y/bmap_height(p.bmap);
		break;
		
		default:
		
		p.pos_x = p.pos_y = 0;
		
		p.scale_x = screen_size.x/bmap_width(p.bmap);
		p.scale_y = screen_size.y/bmap_height(p.bmap);
		
		break;
		
	}
	
}

/* 
--------------------------------------------------
void GGUIInit()


--------------------------------------------------
*/
void GGUIInit() {
	
	wait(-2);
	
	GPanelResize(panCAMRecorder,'t'); // x+y-scale
	GPanelResize(panScreenshot,'t');
	GPanelResize(panObj_Subbar_slider,'x');
	GPanelResize(panObj_Part_slider,'x');
	GPanelResize(panObj_Snd_slider,'x');
	
	int i;
	for(i = 3;i > 0;i--) pan_setpos(panCAMRecorder_digits,1,i,vector(screen_size.x - 35 - 30 * i,BORDER,0));
	
	anms.size_x = bmap_width(panObj_anms);
	arch.size_x = bmap_width(panObj_arch);
	blands.size_x = bmap_width(panObj_blands);
	chars.size_x = bmap_width(panObj_chars);
	etc.size_x = bmap_width(panObj_etc);
	food.size_x = bmap_width(panObj_food);
	machs.size_x = bmap_width(panObj_machs);
	plants.size_x = bmap_width(panObj_plants);
	tportts.size_x = bmap_width(panObj_tportts);
	
	anms.pos_y = arch.pos_y = blands.pos_y = 
	chars.pos_y = etc.pos_y = food.pos_y = 
	machs.pos_y = plants.pos_y = tportts.pos_y = 
	bmap_height(panObj_Main.bmap) - BORDER;
	
	anms.size_y = arch.size_y = blands.size_y = 
	chars.size_y = etc.size_y = food.size_y = 
	machs.size_y = plants.size_y = tportts.size_y = 82;
	
	for(i = 1;i <= 50;i++) pan_setpos(anms,3,i,vector(BORDER*i + 82 * (i-1),0,0));
	for(i = 1;i <= 80;i++) pan_setpos(arch,3,i,vector(BORDER*i + 82 * (i-1),0,0));
	for(i = 1;i <= 50;i++) pan_setpos(blands,3,i,vector(BORDER*i + 82 * (i-1),0,0));
	for(i = 1;i <= 50;i++) pan_setpos(chars,3,i,vector(BORDER*i + 82*(i-1),0,0));
	for(i = 1;i <= 300;i++) pan_setpos(etc,3,i,vector(BORDER*i + 82*(i-1),0,0));
	for(i = 1;i <= 90;i++) pan_setpos(food,3,i,vector(BORDER*i + 82*(i-1),0,0));
	for(i = 1;i <= 50;i++) pan_setpos(machs,3,i,vector(BORDER*i + 82*(i-1),0,0));
	for(i = 1;i <= 160;i++) pan_setpos(plants,3,i,vector(BORDER*i + 82*(i-1),0,0));
	for(i = 1;i <= 50;i++) pan_setpos(tportts,3,i,vector(BORDER*i + 82*(i-1),0,0));
	
	panMain_Top.pos_x = screen_size.x - bmap_width(panMain_Top.bmap) - (BORDER + 3 * 32);
	panMain_Top.pos_y = BORDER;

	panMain_Bottom.pos_x = BORDER;
	panMain_Bottom.pos_y = screen_size.y - bmap_height(panMain_Bottom.bmap) - BORDER;

	panObj_Main.pos_x = 0;
	panObj_Main.pos_y = (screen_size.y - bmap_height(panObj_Main.bmap))/2 - 3 * BORDER;

	panObj_Part_Main.pos_x = 0;
	panObj_Part_Main.pos_y = (screen_size.y - bmap_height(panObj_Main.bmap))/2 - 3 * BORDER;

	panObj_Snd_Main.pos_x = 0;
	panObj_Snd_Main.pos_y = (screen_size.y - bmap_height(panObj_Main.bmap))/2 - 3 * BORDER;

	panObj_Main_X.pos_x = screen_size.x - 40 - BORDER;
	panObj_Main_X.pos_y = panObj_Main.pos_y + 25;

	panObj_Part_Main_X.pos_x = panObj_Main_X.pos_x;
	panObj_Part_Main_X.pos_y = panObj_Main_X.pos_y;

	panObj_Snd_Main_X.pos_x = panObj_Main_X.pos_x;
	panObj_Snd_Main_X.pos_y = panObj_Main_X.pos_y;

	panObj_Subbar.pos_x = panObj_Subbar_slider.pos_x = panObj_Part_slider.pos_x = 0;

	panObj_Subbar.pos_y = panObj_Main.pos_y + bmap_height(panObj_Main.bmap) + BORDER;
	panObj_Subbar_slider.pos_y = panObj_Subbar.pos_y + bmap_height(panObj_Subbar_slider.bmap) + BORDER * 3;

	panObj_Part_slider.pos_y = panObj_Subbar_slider.pos_y;
	panObj_Snd_slider.pos_y = panObj_Subbar_slider.pos_y;

	panRotateHelp.pos_x = screen_size.x - bmap_width(panRotateHelp.bmap) - BORDER * 2;
	panRotateHelp.pos_y = panMain_Top.pos_y + BORDER * 2;

	panScaleHelp.pos_x = screen_size.x - bmap_width(panScaleHelp.bmap) - BORDER * 2;
	panScaleHelp.pos_y = panRotateHelp.pos_y;

	int i;
	for(i = 1; i < 10;i++) {
		
		pan_setpos(panObj_Subbar,3,i,vector(bmap_width(panObj_Subbar.bmap)/9 * (i-1),0,0));
		
	}

	int i = 1;
	while(i < 7) {
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
	while(i < 5) {
		
		pan_setpos(buttonlst_submenu_terrain,3,i,vector(BORDER * (i-1) + 32 * (i-1),NULL,NULL));
		pan_setpos(buttonlst_submenu_object,3,i,vector(BORDER * (i-1) + 32 * (i-1),NULL,NULL));
		pan_setpos(buttonlst_submenu_path,3,i,vector(BORDER * (i-1) + 32 * (i-1),NULL,NULL));
		
		i++;
	}

	var cache = BORDER * 4 + 32 * 4; // the above formula, i = 5
	pan_setpos(buttonlst_submenu_terrain,3,5,vector(cache,NULL,NULL));
	pan_setpos(buttonlst_submenu_object,3,5,vector(cache,NULL,NULL));
	pan_setpos(buttonlst_submenu_path,3,5,vector(cache,NULL,NULL));
}

/* 
--------------------------------------------------
void GPanelSelect(PANEL *p)


--------------------------------------------------
*/
void GPanelSelect(PANEL *p)
{
	
	if(last_pan) {
		last_pan.alpha = DEFAULT_ALPHA;
		layer_sort(last_pan,2);
		
		// Idk why I inserted the fix here but it worked.
		if(last_pan == panProp) {
			
			if(is(panProp_1,SHOW)) layer_sort(panProp_1,panProp.layer+1);
			if(is(panProp_2,SHOW)) layer_sort(panProp_2,panProp.layer+1);
			if(is(panProp_3,SHOW)) layer_sort(panProp_3,panProp.layer+1);
			
		}
		
		last_pan = p;
		layer_sort(last_pan,4);
		last_pan.alpha = 100;
		
		if(p == panProp) {
			
			if(is(panProp_1,SHOW)) layer_sort(panProp_1,panProp.layer+1);
			if(is(panProp_2,SHOW)) layer_sort(panProp_2,panProp.layer+1);
			if(is(panProp_3,SHOW)) layer_sort(panProp_3,panProp.layer+1);
			
		}
		
	}
	
	else {
		last_pan = p;
		layer_sort(last_pan,4);
		last_pan.alpha = 100;
		
		if(p == panProp) {
			
			if(is(panProp_1,SHOW)) layer_sort(panProp_1,panProp.layer+1);
			if(is(panProp_2,SHOW)) layer_sort(panProp_2,panProp.layer+1);
			if(is(panProp_3,SHOW)) layer_sort(panProp_3,panProp.layer+1);
			
		}
		
	}
}

/* 
--------------------------------------------------
void GTerrainSubmenuShow()


--------------------------------------------------
*/
void GTerrainSubmenuShow() {
	reset(buttonlst_submenu_object,SHOW);
	reset(buttonlst_submenu_path,SHOW);

	set(buttonlst_submenu_terrain,SHOW);
}

/* 
--------------------------------------------------
void GObjectSubmenuShow()


--------------------------------------------------
*/
void GObjectSubmenuShow() {
	reset(buttonlst_submenu_terrain,SHOW);
	reset(buttonlst_submenu_path,SHOW);

	set(buttonlst_submenu_object,SHOW);
}

/* 
--------------------------------------------------
void GPathSubmenuShow()


--------------------------------------------------
*/
void GPathSubmenuShow() {
	reset(buttonlst_submenu_object,SHOW);
	reset(buttonlst_submenu_terrain,SHOW);

	set(buttonlst_submenu_path,SHOW);
}

/*
--------------------------------------------------
void GGUIHide()


--------------------------------------------------
*/
void GGUIHide() {

	if(select) {
		
		// Deselect any selected entity first
		if(select.ObjectType == Light) GLightWindowHide();
		if(select.ObjectType == NormalObject) GPropertiesWindowHide();
		if(select.ObjectType == Sound) GSoundWindowHide();
		if(select.ObjectType == Particle) GParticleWindowHide();
		
		select.material = mat_temp;
		select = NULL;
		
	}

	reset(panMain_Top,SHOW);
	reset(panMain_Bottom,SHOW);
	reset(panMain_Play,SHOW);

	// Also disables any remaining active content.
	reset(buttonlst_submenu_object,SHOW);
	reset(buttonlst_submenu_path,SHOW);
	reset(buttonlst_submenu_terrain,SHOW);
	reset(panRotateHelp,SHOW);
	reset(panScaleHelp,SHOW);
}

/*
--------------------------------------------------
void GGUIShow()


--------------------------------------------------
*/
void GGUIShow() {

	set(panMain_Top,SHOW);
	set(panMain_Bottom,SHOW);
	set(panMain_Play,SHOW);

}

/*
--------------------------------------------------
void GHomeShow()


--------------------------------------------------
*/
void GHomeShow() {

	GPanelCenter(panHome);
	GGUIUpdate(panHome);

	set(panHome,SHOW);
	GPanelSelect(panHome);
}

/*
--------------------------------------------------
void GMaterialEditorShow()


--------------------------------------------------
*/
void GMaterialEditorShow() {

	// Precache panMat_Sub1
	GGUIUpdate(panMat_Sub1);

	// Material editor is available only to custom materials
	switch(mat_type) {
		
		case select_custom_mat1 :
		
		PassMaterialDataToWindow(mat_custom[0]);
		set(panMat_Sub1,SHOW);
		
		GPanelSelect(panMat_Sub1);
		
		break;
		//////////////////////////////////////////////////////////////
		
		case select_custom_mat2 :
		
		PassMaterialDataToWindow(mat_custom[1]);
		set(panMat_Sub1,SHOW);
		
		GPanelSelect(panMat_Sub1);
		
		break;
		//////////////////////////////////////////////////////////////
		
		case select_custom_mat3 :
		
		PassMaterialDataToWindow(mat_custom[2]);
		set(panMat_Sub1,SHOW);
		
		GPanelSelect(panMat_Sub1);
		
		break;
		//////////////////////////////////////////////////////////////
		
		case select_custom_mat4 :
		
		PassMaterialDataToWindow(mat_custom[3]);
		set(panMat_Sub1,SHOW);
		
		GPanelSelect(panMat_Sub1);
		
		break;
		//////////////////////////////////////////////////////////////
		
		default:
		printf("Material editor is available only to custom materials.");
		break;
	}	
}

////////////////////////////////////////////////////////////
// These functions will be assigned to move, rotate, scale button respectively.
////////////////////////////////////////////////////////////

// stupid switchers
// lite-C compiler: stupid programmer
void GSwitchToMoveMode() {

	// Check its state first.
	if(button_state(panMain_Top,1,-1)) {
		
		button_state(panMain_Top,2,0);
		button_state(panMain_Top,3,0);
		
		// Switch to ' object move ' state.
		manip_type = move;
		
		reset(panRotateHelp,SHOW);
		reset(panScaleHelp,SHOW);
		
	}

	else {
		
		// The loop can't check this so nothing will be assigned
		// to manip_type.
		manip_type = scale+1;
		
	}
}

void GSwitchToRotateMode() {

	if(button_state(panMain_Top,2,-1)) {
		
		button_state(panMain_Top,1,0);
		button_state(panMain_Top,3,0);
		
		manip_type = rotate;
		
		set(panRotateHelp,SHOW);
		reset(panScaleHelp,SHOW);
		
	}

	else {
		
		manip_type = scale+1;
		reset(panRotateHelp,SHOW);
		
	}
}

void GSwitchToScaleMode() {

	if(button_state(panMain_Top,3,-1)) {
		
		button_state(panMain_Top,1,0);
		button_state(panMain_Top,2,0);
		
		manip_type = scale;
		
		reset(panRotateHelp,SHOW);
		set(panScaleHelp,SHOW);
		
	}

	else {
		
		manip_type=scale+1;
		reset(panScaleHelp,SHOW);
		
	}

}

void GNotificationCreate(FONT *f, STRING *r)
{
	proc_kill(4);

	TEXT *rt = txt_create(1,1);

	rt->font = f;
	str_cpy((rt.pstring)[0],r);

	rt->pos_x = screen_size.x -  str_width((rt.pstring)[0],f) - BORDER - 30; // -30 because I'm using the free edition.
	rt->pos_y = BORDER;

	set(rt,SHOW);

	// It's supposed to be "while(Game Is Running) wait(1);"
	// but I haven't added into the game yet.
	while(1) wait(1);

	txt_remove(rt);
}

void GObjectAddWindowShow() {
	
	GGUIHide();

	set(panObj_Main,SHOW);
	set(panObj_Subbar,SHOW);
	set(panObj_Subbar_slider,SHOW);
	set(panObj_Main_X,SHOW);
	
	button_state(panObj_Subbar,1,1);
	GObjectTypeBackgroundSwitcher(anms);

	SliderLimit = 0;

}

void GParticleAddWindowShow() {

	GGUIHide();
	set(panObj_Part_Main,SHOW);
	set(panObj_Part_Main_X,SHOW);
	set(panObj_Part_slider,SHOW);

	SliderLimit= 0;
}

void GSoundAddWindowShow() {

	GGUIHide();
	set(panObj_Snd_Main,SHOW);
	set(panObj_Snd_Main_X,SHOW);
	set(panObj_Snd_slider,SHOW);

	SliderLimit= 0;

}

void GLightAddWindowShow() {

	set(panLightNoti,SHOW);

	wait(-5);

	reset(panLightNoti,SHOW);

}

void GShowCredits() {
	
	var rollspeed = .5;
	
	reset(panMMenu,SHOW);
	reset(panMMenu_exit,SHOW);
	reset(panNewGame,SHOW);
	
	level_load("_arena1.wmb");
	
	TEXT *import = txt_create(100,1);
	TEXT *end = txt_create(1,1);
	
	import.font = font_create("Arial #25b");
	end.font = import.font;
	
	txt_loadw(import,FILE_CREDITS_TEXT);
	txt_loadw(end,FILE_CREDITS_0);
	
	import.pos_x = 15;
	import.pos_y = 15;
	
	end.pos_x = screen_size.x - str_width((end.pstring)[0],end.font);
	end.pos_y = import.pos_y;
	
	set(import,SHOW);
	set(end,SHOW);
	
	while(!key_esc) {
		
		import.pos_y -= rollspeed * time_step;
		
		//		if(key_cuu) rollspeed = 4; else rollspeed = .5;
		//		if(key_cud) rollspeed = -4; else rollspeed = .5;
		
		wait(1);
		
	}
	
	txt_remove(import);
	txt_remove(end);
	
	GLoadMainMenu();
	
}

// Just a small function for use within GObjectTypeSwitcher(var).
// Updates the size of p according to b's size.
void GPanelSizeForWH(PANEL *p, BMAP *b) {
	while(b == NULL || p == NULL) wait(1);

	p.size_x = bmap_width(b);
	p.size_y = bmap_height(b);

}

void GObjectTypeBackgroundSwitcher(PANEL *p) {
	
	switch(p) {
		
		case anms:
		
		set(anms,SHOW);
		reset(arch,SHOW);
		reset(blands,SHOW);
		reset(chars,SHOW);
		reset(etc,SHOW);
		reset(food,SHOW);
		reset(machs,SHOW);
		reset(plants,SHOW);
		reset(tportts,SHOW);
		
		break;
		
		case arch:
		
		set(arch,SHOW);
		reset(anms,SHOW);
		reset(blands,SHOW);
		reset(chars,SHOW);
		reset(etc,SHOW);
		reset(food,SHOW);
		reset(machs,SHOW);
		reset(plants,SHOW);
		reset(tportts,SHOW);
		
		break;
		
		case blands:
		
		set(blands,SHOW);
		reset(arch,SHOW);
		reset(anms,SHOW);
		reset(chars,SHOW);
		reset(etc,SHOW);
		reset(food,SHOW);
		reset(machs,SHOW);
		reset(plants,SHOW);
		reset(tportts,SHOW);
		
		break;
		
		case chars:
		
		set(chars,SHOW);
		reset(blands,SHOW);
		reset(arch,SHOW);
		reset(anms,SHOW);
		reset(etc,SHOW);
		reset(food,SHOW);
		reset(machs,SHOW);
		reset(plants,SHOW);
		reset(tportts,SHOW);
		
		break;
		
		case etc:
		
		set(etc,SHOW);
		reset(chars,SHOW);
		reset(blands,SHOW);
		reset(arch,SHOW);
		reset(anms,SHOW);
		reset(food,SHOW);
		reset(machs,SHOW);
		reset(plants,SHOW);
		reset(tportts,SHOW);
		
		break;
		
		case food:
		
		set(food,SHOW);
		reset(etc,SHOW);
		reset(chars,SHOW);
		reset(blands,SHOW);
		reset(arch,SHOW);
		reset(anms,SHOW);
		reset(machs,SHOW);
		reset(plants,SHOW);
		reset(tportts,SHOW);
		
		break;
		
		case machs:
		
		set(machs,SHOW);
		reset(food,SHOW);
		reset(etc,SHOW);
		reset(chars,SHOW);
		reset(blands,SHOW);
		reset(arch,SHOW);
		reset(anms,SHOW);
		reset(plants,SHOW);
		reset(tportts,SHOW);
		
		break;
		
		case plants:
		
		set(plants,SHOW);
		reset(machs,SHOW);
		reset(food,SHOW);
		reset(etc,SHOW);
		reset(chars,SHOW);
		reset(blands,SHOW);
		reset(arch,SHOW);
		reset(anms,SHOW);
		reset(tportts,SHOW);
		
		break;
		
		case tportts:
		
		set(tportts,SHOW);
		reset(plants,SHOW);
		reset(machs,SHOW);
		reset(food,SHOW);
		reset(etc,SHOW);
		reset(chars,SHOW);
		reset(blands,SHOW);
		reset(arch,SHOW);
		reset(anms,SHOW);
		
		break;
		
		default:
		
		reset(tportts,SHOW);
		reset(plants,SHOW);
		reset(machs,SHOW);
		reset(food,SHOW);
		reset(etc,SHOW);
		reset(chars,SHOW);
		reset(blands,SHOW);
		reset(arch,SHOW);
		reset(anms,SHOW);
		
		break;
		
	}
	
}

// We met again stupid switcher.
// lite-C compiler: Without me you're nothing bitch.
void GObjectTypeSwitcher(var id) {
	// 10 = upper limit (9 buttons); 0 = lower limit
	// This is more efficient than using a bunch of switch..case.

	int i;

	// Switches off all available buttons after id.
	for(i = id + 1;i < 10;i++) button_state(panObj_Subbar,i,0);
	// Switches off all available buttons before id.
	for(i = id - 1;i > 0;i--) button_state(panObj_Subbar,i,0);

	// Switches on id.
	button_state(panObj_Subbar,id,1);

	// Eeehhh..switch..case..I hate it.

	switch(id) {
		
		case 1: // ANMS
		
		panObj_Main.bmap = panObj_anms;
		GPanelSizeForWH(panObj_Main,panObj_anms);
		
		GObjectTypeBackgroundSwitcher(anms);
		
		SliderLimit= 0;
		
		break;
		
		case 2: // ARCH
		
		panObj_Main.bmap = panObj_arch;
		GPanelSizeForWH(panObj_Main,panObj_arch);
		
		GObjectTypeBackgroundSwitcher(arch);
		
		SliderLimit= 0;
		
		break;
		
		case 3: // BLANDS
		
		panObj_Main.bmap = panObj_blands;
		GPanelSizeForWH(panObj_Main,panObj_blands);
		
		GObjectTypeBackgroundSwitcher(blands);
		
		SliderLimit = 0;
		
		break;
		
		case 4: // CHARS
		
		panObj_Main.bmap = panObj_chars;
		GPanelSizeForWH(panObj_Main,panObj_chars);
		
		GObjectTypeBackgroundSwitcher(chars);
		
		SliderLimit = 0;
		
		break;
		
		case 5: // ETC
		
		panObj_Main.bmap = panObj_etc;
		GPanelSizeForWH(panObj_Main,panObj_etc);
		
		GObjectTypeBackgroundSwitcher(etc);
		
		SliderLimit = 0;
		
		break;
		
		case 6: // FOOD
		
		panObj_Main.bmap = panObj_food;
		GPanelSizeForWH(panObj_Main,panObj_food);
		
		GObjectTypeBackgroundSwitcher(food);
		
		SliderLimit = 0;
		
		break;
		
		case 7: // MACHS
		
		panObj_Main.bmap = panObj_machs;
		GPanelSizeForWH(panObj_Main,panObj_machs);
		
		GObjectTypeBackgroundSwitcher(machs);
		
		SliderLimit = 0;
		
		break; 
		
		case 8: // PLANTS
		
		panObj_Main.bmap = panObj_plants;
		GPanelSizeForWH(panObj_Main,panObj_plants);
		
		GObjectTypeBackgroundSwitcher(plants);
		
		SliderLimit = 0;
		
		break;
		
		case 9: // TPORTTS
		
		panObj_Main.bmap = panObj_tportts;
		GPanelSizeForWH(panObj_Main,panObj_tportts);
		
		GObjectTypeBackgroundSwitcher(tportts);
		
		SliderLimit = 0;
		
		break;
		
		default:
		sys_exit(NULL);
		break;
		
	}

}

void GLoadMainMenu() {
	
	IN_GAME = 0;
	
	panMMenu_exit.pos_x = screen_size.x - 38 - BORDER;
	panMMenu_exit.pos_y = BORDER;
	
	GGUIHide();
	GPanelCenter(panMMenu);
	
	launch_newgame_from_main = 1;
	
	level_load("_tech.wmb");
	game_load(pref_savebmaps,0);
	
	// captured
	camera.x = 886;
	camera.y = 1944;
	camera.z = -28;
	camera.pan = 261;
	camera.tilt = 15;
	camera.roll = 0;
	
	set(panMMenu,SHOW);
	set(panMMenu_exit,SHOW);
	
	GPanelSelect(panMMenu);
	
	layer_sort(panMMenu_exit,panMMenu.layer+1);
	
	panMMenu.alpha = 50;
	
	// dev text goes here
}


void GPropertiesWindowShow() {
	
	if(!lfsp) { // If prop() was launched from switch_panProp, don't re-change window's position.
		
		panProp.pos_x = xy_panProp.x;
		panProp.pos_y = xy_panProp.y;
		
	}
	
	else lfsp = 0;
	
	if(select) {
		
		if(select.ObjectType != Light &&
		select.ObjectType != Sound &&
		select.ObjectType != Particle) {
			
			set(panProp,SHOW);
			GPanelSelect(panProp);
			
			////////////////////////////////////////////////////////////
			// Set rules for opening and closing panProp.
			////////////////////////////////////////////////////////////
			if(page == 1) { // Properties panel
				
				int i = 3;
				while(i<5) {
					
					button_state(panProp,i,0);
					i++;
					
				}
				
				panProp.bmap = panProp1_IMG;
				
				set(panProp_1,SHOW);		
				reset(panProp_2,SHOW);
				reset(panProp_3,SHOW);
				
			}

			if(page == 2) { // Materials panel
				
				button_state(panProp,2,0);
				button_state(panProp,4,0);
				
				panProp.bmap = panProp2_IMG;
				
				reset(panProp_1,SHOW);
				set(panProp_2,SHOW);
				reset(panProp_3,SHOW);
				
			}

			if(page == 3) { // Physics panel
				
				button_state(panProp,3,0);
				button_state(panProp,2,0);
				
				panProp.bmap = panProp3_IMG;
				
				reset(panProp_1,SHOW);
				reset(panProp_2,SHOW);
				set(panProp_3,SHOW);
				
			}
			////////////////////////////////////////////////////////////
			
			GGUIUpdate(panProp);
			
		}
		
	}
	
}

void GPropertiesWindowHide() {
	
	// Object is deactivated/other object has been selected.
	
	// Disable subpanels.
	// Actually we have only one subpanel opened at a time,
	// so only one value is passed to page.
	if(is(panProp_1,SHOW)) { // If something has been opened before.
		
		// save it to page.
		page = 1;
		// close the panel.
		reset(panProp_1,SHOW);
		
	}
	if(is(panProp_2,SHOW)) {
		
		page = 2;
		reset(panProp_2,SHOW);
		
	}
	
	if(is(panProp_3,SHOW)) {
		
		page = 3;
		reset(panProp_3,SHOW);
		
	}
	
	// Save window's location.
	xy_panProp.x = panProp.pos_x;
	xy_panProp.y = panProp.pos_y;	
	
	if(is(panMat_Sub1,SHOW)) reset(panMat_Sub1,SHOW);
	reset(panProp,SHOW);
	
}

void GSoundWindowShow() {
	
	panSnd.pos_x = xy_panSnd.x;
	panSnd.pos_y = xy_panSnd.y;
	
	GGUIUpdate(panSnd);
	set(panSnd,SHOW);
	
	GPanelSelect(panSnd);
	
}

void GSoundWindowHide() {
	
	xy_panSnd.x = panSnd.pos_x;
	xy_panSnd.y = panSnd.pos_y;
	
	reset(panSnd,SHOW);
	
}

/*
--------------------------------------------------
void GParticleWindowShow()

--------------------------------------------------
*/
void GParticleWindowShow() {
	
	panParticle.pos_x = xy_panParticle.x;
	panParticle.pos_y = xy_panParticle.y;
	
	GGUIUpdate(panParticle);
	
	set(panParticle,SHOW);
	
}

/*
--------------------------------------------------
void GParticleWindowHide()

--------------------------------------------------
*/
void GParticleWindowHide() {
	
	xy_panParticle.x = panParticle.pos_y;
	xy_panParticle.y = panParticle.pos_y;
	
	reset(panParticle,SHOW);
	
}

/*
--------------------------------------------------
void GLightWindowShow()

--------------------------------------------------
*/
void GLightWindowShow() {
	
	panLight.pos_x = xy_panLight.x;
	panLight.pos_y = xy_panLight.y;
	
	//		GPanelCenter(panLight);
	GGUIUpdate(panLight);
	
	set(panLight,SHOW);
	
	GPanelSelect(panLight);
	
	// Surely, select has been selected already.
	
	v_lred = select.red;
	v_lgreen = select.green;
	v_lblue = select.blue;
	v_lrange = select.lightrange;
	
	// 'cause no#1 is the close button so we start from 2.
	if(select.LightMode == disco) button_state(panLight,2,1);
	if(select.LightMode == flick) button_state(panLight,3,1);
	
}

/*
--------------------------------------------------
void GLightWindowHide()

--------------------------------------------------
*/
void GLightWindowHide() {
	
	// Backup
	xy_panLight.x = panLight.pos_x;
	xy_panLight.y = panLight.pos_y;
	
	// For passing to loop_kernel without messing up the code 
	// and/or write a new one.
	if(!select) return; 
	
	// Apply new values to the selected object.
	select.red = v_lred;
	select.green = v_lgreen;
	select.blue = v_lblue;
	
	// I grouped.
	// Assignment will happen this way: A <-- B <-- C
	// So we obtain C first, in this case is v_lrange
	olrange = select.lightrange = v_lrange;
	
	if(button_state(panLight,2,-1)) select.LightMode = disco;
	if(button_state(panLight,3,-1)) select.LightMode = flick;
	
	reset(panLight,SHOW);
	
}

/* 
--------------------------------------------------
void GWorldNew()

--------------------------------------------------
*/
void GWorldNew() {
	
	if(!is(panNewGame,SHOW)) {
		
		GGUIUpdate(panNewGame);
		GPanelCenter(panNewGame);
		
		set(panNewGame,SHOW);
		
		GPanelSelect(panNewGame); // Bring me to the TOP ! =))
		
		// Set some default parameters
		
		GToggleLevelCreationMode(2);
		button_state(panNewGame,2,1); // Static sky by default
		
		v_fogdensity = 3000; // Make fog_end a bit larger
		v_fogr = v_fogg = v_fogb = 255/2;
		
		_moon_scale_fac = moon_scale_fac;
		_time_speed_night = time_speed_night;
		_night_sky_scale_x = night_sky_scale_x;
		_night_sky_speed_x = night_sky_speed_x;
		
		//		button_state (panNewGame,5,1); // Lensflare on by default
		//		button_state (panNewGame,7,1); // Moon too
	}
	
}

void switch_panProp(var mode) {

	page=mode--;
	lfsp++;
	GPropertiesWindowShow();

}