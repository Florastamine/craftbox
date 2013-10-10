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

- I put particle code here because I want to do something that is kernel-independent.
Just plug additional code to CBox.h and CBoxShell.c, modify InsertParticle and 
GSelectParticle a bit, and run - more particle effects.

>+++
--------------------------------------------------
*/


PANEL *ZTool = {
	
	layer = 6;
	
	bmap = "z_tool.bmp";
	
	pos_x = 200;
	pos_y = 10;
	
	vslider(10,10,300,"slider.bmp",-3000,4000,v_objectz);
	
	on_click = GPanelDrag;
	
}

PANEL *LoadGame_Uppart = {
	
	layer = 3;
	
	bmap = "LoadGameUppart.bmp";
	
	button(0,0,"arrow_up.png","arrow_up.png","arrow_up.png",NULL,GLoadGame_Scroll,NULL);
	
}

PANEL *LoadGame_Downpart = {
	
	layer = 3;
	
	bmap = "LoadGameDownpart.bmp";
	
	button(0,0,"arrow_down.png","arrow_down.png","arrow_down.png",NULL,GLoadGame_Scroll,NULL);
	
}

PANEL *LoadGameInside = {
	
	layer = 1;
	
	bmap = "LoadGameInside.bmp";
	
	button(0,0,slot1,slot1,slot1,NULL,LoadGameFromSlot,NULL);
	button(0,50,slot2,slot2,slot2,NULL,LoadGameFromSlot,NULL);
	button(0,100,slot3,slot3,slot3,NULL,LoadGameFromSlot,NULL);
	button(0,150,slot4,slot4,slot4,NULL,LoadGameFromSlot,NULL);
	button(0,200,slot5,slot5,slot5,NULL,LoadGameFromSlot,NULL);
	button(0,250,slot6,slot6,slot6,NULL,LoadGameFromSlot,NULL);
	button(0,300,slot7,slot7,slot7,NULL,LoadGameFromSlot,NULL);
	button(0,350,slot8,slot8,slot8,NULL,LoadGameFromSlot,NULL);
	button(0,400,slot9,slot9,slot9,NULL,LoadGameFromSlot,NULL);
	
}

// C++'s inheritance is needed here DUDE!

PANEL *Options_Graphics = {
	
	layer = 4;
	
	bmap = "Options_Graphics.bmp";
	
	//
	button(155,62,"arrow_left.png","arrow_left.png","arrow_left.png",NULL,GOptionsAdjustSettings,NULL);
	button(275,62,"arrow_right.png","arrow_right.png","arrow_right.png",NULL,GOptionsAdjustSettings,NULL);
	
	button(155,92,"arrow_left.png","arrow_left.png","arrow_left.png",NULL,GOptionsAdjustSettings,NULL);
	button(275,92,"arrow_right.png","arrow_right.png","arrow_right.png",NULL,GOptionsAdjustSettings,NULL);
	
	button(155,122,"arrow_left.png","arrow_left.png","arrow_left.png",NULL,GOptionsAdjustSettings,NULL);
	button(275,122,"arrow_right.png","arrow_right.png","arrow_right.png",NULL,GOptionsAdjustSettings,NULL);
	
	button(155,152,"arrow_left.png","arrow_left.png","arrow_left.png",NULL,GOptionsAdjustSettings,NULL);
	button(275,152,"arrow_right.png","arrow_right.png","arrow_right.png",NULL,GOptionsAdjustSettings,NULL);
	
	button(155,182,"arrow_left.png","arrow_left.png","arrow_left.png",NULL,GOptionsAdjustSettings,NULL);
	button(275,182,"arrow_right.png","arrow_right.png","arrow_right.png",NULL,GOptionsAdjustSettings,NULL);
	
	button(155,212,"arrow_left.png","arrow_left.png","arrow_left.png",GOptionsAdjustSettings,NULL,NULL);
	button(275,212,"arrow_right.png","arrow_right.png","arrow_right.png",GOptionsAdjustSettings,NULL,NULL);
	
	//
	button(320,11,"button_Options_Graphics.png","button_Options_Graphics.png","button_Options_Graphics.png",NULL,GOptions_Graphics,NULL);
	button(320,50,"button_Options_Sound.png","button_Options_Sound.png","button_Options_Sound.png",NULL,GOptions_Sound,NULL);
	button(320,90,"button_Options_Themes.png","button_Options_Themes.png","button_Options_Themes.png",NULL,GOptions_Themes,NULL);
	button(320,130,"button_Options_Maintenance.png","button_Options_Maintenance.png","button_Options_Maintenance.png",NULL,GOptions_Maintenance,NULL);
	
	button(9,349,"button_Options_Back.bmp","button_Options_Back.bmp","button_Options_Back.bmp",NULL,GOptions_SaveSettings,NULL);
	
	flags = TRANSLUCENT;
	
	alpha = 80;
	
	//	on_click = GPanelDrag;
	
}

PANEL *Options_Sound = {
	
	layer = 4;
	
	bmap = "Options_Sound.bmp";
	
	//
	button(155,62,"arrow_left.png","arrow_left.png","arrow_left.png",NULL,GOptionsAdjustSettings,NULL);
	button(275,62,"arrow_right.png","arrow_right.png","arrow_right.png",NULL,GOptionsAdjustSettings,NULL);
	
	button(155,92,"arrow_left.png","arrow_left.png","arrow_left.png",NULL,GOptionsAdjustSettings,NULL);
	button(275,92,"arrow_right.png","arrow_right.png","arrow_right.png",NULL,GOptionsAdjustSettings,NULL);
	
	button(155,122,"arrow_left.png","arrow_left.png","arrow_left.png",NULL,GOptionsAdjustSettings,NULL);
	button(275,122,"arrow_right.png","arrow_right.png","arrow_right.png",NULL,GOptionsAdjustSettings,NULL);
	
	//
	button(320,11,"button_Options_Graphics.png","button_Options_Graphics.png","button_Options_Graphics.png",NULL,GOptions_Graphics,NULL);
	button(320,50,"button_Options_Sound.png","button_Options_Sound.png","button_Options_Sound.png",NULL,GOptions_Sound,NULL);
	button(320,90,"button_Options_Themes.png","button_Options_Themes.png","button_Options_Themes.png",NULL,GOptions_Themes,NULL);
	button(320,130,"button_Options_Maintenance.png","button_Options_Maintenance.png","button_Options_Maintenance.png",NULL,GOptions_Maintenance,NULL);
	
	button(9,349,"button_Options_Back.bmp","button_Options_Back.bmp","button_Options_Back.bmp",NULL,GOptions_SaveSettings,NULL);
	
	flags = TRANSLUCENT;
	
	alpha = 80;
	
}

PANEL *Options_Themes = {
	
	layer = 4;
	
	bmap = "Options_Themes.bmp";
	
	button(320,11,"button_Options_Graphics.png","button_Options_Graphics.png","button_Options_Graphics.png",NULL,GOptions_Graphics,NULL);
	button(320,50,"button_Options_Sound.png","button_Options_Sound.png","button_Options_Sound.png",NULL,GOptions_Sound,NULL);
	button(320,90,"button_Options_Themes.png","button_Options_Themes.png","button_Options_Themes.png",NULL,GOptions_Themes,NULL);
	button(320,130,"button_Options_Maintenance.png","button_Options_Maintenance.png","button_Options_Maintenance.png",NULL,GOptions_Maintenance,NULL);
	
	button(9,349,"button_Options_Back.bmp","button_Options_Back.bmp","button_Options_Back.bmp",NULL,GOptions_SaveSettings,NULL);
	
	flags = TRANSLUCENT;
	
	alpha = 80;
	
}

PANEL *Options_Maintenance = {
	
	layer = 4;
	
	bmap = "Options_Maintenance.bmp";
	
	button(320,11,"button_Options_Graphics.png","button_Options_Graphics.png","button_Options_Graphics.png",NULL,GOptions_Graphics,NULL);
	button(320,50,"button_Options_Sound.png","button_Options_Sound.png","button_Options_Sound.png",NULL,GOptions_Sound,NULL);
	button(320,90,"button_Options_Themes.png","button_Options_Themes.png","button_Options_Themes.png",NULL,GOptions_Themes,NULL);
	button(320,130,"button_Options_Maintenance.png","button_Options_Maintenance.png","button_Options_Maintenance.png",NULL,GOptions_Maintenance,NULL);
	
	button(9,349,"button_Options_Back.bmp","button_Options_Back.bmp","button_Options_Back.bmp",NULL,GOptions_SaveSettings,NULL);
	
	flags = TRANSLUCENT;
	
	alpha = 80;
	
}

PANEL *BackgroundScreen = {
	
	layer = 10;
	
	bmap = BackgroundScreen1;
	
}

PANEL *InsertObject_Inputter = {
	
	/*
	
	EVENT_RELEASE and EVENT_BUTTONUP can be used to distinguish whether functionOff was triggered by leaving the button area 
	or releasing the mouse button. EVENT_CLICK and EVENT_CLICKUP can be used to distinguish whether the mouse click switches the toggle button on or off. 
	
	*/
	
	bmap = "InsertObject_Inputter.bmp";
	
	button(0,0,"InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp",NULL,GSelectObject,NULL);
	button(0,30,"InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp",NULL,GSelectObject,NULL);
	button(0,60,"InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp",NULL,GSelectObject,NULL);
	button(0,90,"InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp",NULL,GSelectObject,NULL);
	button(0,120,"InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp",NULL,GSelectObject,NULL);
	button(0,150,"InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp",NULL,GSelectObject,NULL);
	button(0,180,"InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp",NULL,GSelectObject,NULL);
	button(0,210,"InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp",NULL,GSelectObject,NULL);
	button(0,240,"InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp",NULL,GSelectObject,NULL);
	button(0,270,"InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp",NULL,GSelectObject,NULL);
	button(0,300,"InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp",NULL,GSelectObject,NULL);
	button(0,330,"InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp",NULL,GSelectObject,NULL);
	button(0,360,"InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp",NULL,GSelectObject,NULL);
	button(0,390,"InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp",NULL,GSelectObject,NULL);
	button(0,420,"InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp",NULL,GSelectObject,NULL);
	button(0,450,"InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp",NULL,GSelectObject,NULL);
	button(0,480,"InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp",NULL,GSelectObject,NULL);

	flags = TRANSLUCENT;

	alpha = 50;

}

PANEL *InsertParticle = {
	
	layer = 6;
	
	button(0,0,"Particle1.bmp","Particle1.bmp","Particle1.bmp",NULL,GSelectParticle,NULL);
	button(80,0,"Particle2.bmp","Particle2.bmp","Particle2.bmp",NULL,GSelectParticle,NULL);
	button(160,0,"Particle3.bmp","Particle3.bmp","Particle3.bmp",NULL,GSelectParticle,NULL);
	button(240,0,"Particle4.bmp","Particle4.bmp","Particle4.bmp",NULL,GSelectParticle,NULL);
	
	button(0,40,"Particle5.bmp","Particle5.bmp","Particle5.bmp",NULL,GSelectParticle,NULL);
	button(80,40,"Particle6.bmp","Particle6.bmp","Particle6.bmp",NULL,GSelectParticle,NULL);
	button(160,40,"Particle7.bmp","Particle7.bmp","Particle7.bmp",NULL,GSelectParticle,NULL);
	button(240,40,"Particle8.bmp","Particle8.bmp","Particle8.bmp",NULL,GSelectParticle,NULL);
	
	button(0,80,"Particle9.bmp","Particle9.bmp","Particle9.bmp",NULL,GSelectParticle,NULL);
	button(80,80,"Particle10.bmp","Particle10.bmp","Particle10.bmp",NULL,GSelectParticle,NULL);
	button(160,80,"Particle11.bmp","Particle11.bmp","Particle11.bmp",NULL,GSelectParticle,NULL);
	button(240,80,"Particle12.bmp","Particle12.bmp","Particle12.bmp",NULL,GSelectParticle,NULL);
	
	button(0,80,"Particle13.bmp","Particle13.bmp","Particle13.bmp",NULL,GSelectParticle,NULL);
	button(80,80,"Particle14.bmp","Particle14.bmp","Particle14.bmp",NULL,GSelectParticle,NULL);
	button(160,80,"Particle15.bmp","Particle15.bmp","Particle15.bmp",NULL,GSelectParticle,NULL);
	button(240,80,"Particle16.bmp","Particle16.bmp","Particle16.bmp",NULL,GSelectParticle,NULL);
	
	button(0,80,"Particle17.bmp","Particle17.bmp","Particle17.bmp",NULL,GSelectParticle,NULL);
	button(80,80,"Particle18.bmp","Particle18.bmp","Particle18.bmp",NULL,GSelectParticle,NULL);
	button(160,80,"Particle19.bmp","Particle19.bmp","Particle19.bmp",NULL,GSelectParticle,NULL);
	button(240,80,"Particle20.bmp","Particle20.bmp","Particle20.bmp",NULL,GSelectParticle,NULL);
	
}

PANEL *InsertObject = {
	
	layer = 4;
	
	bmap = "InsertObject.png";
	
	button(0,0,"button_close_on.bmp","button_close_off.bmp","button_close_over.bmp",NULL,GWindowClose,NULL);
	
	// 2 -> 7
	button_toggle(40,50,"IO_ObjectTab_On.png","IO_ObjectTab_Off.png","IO_ObjectTab_Over.png",,"IO_ObjectTab_Over.png",NULL,GObjectTypeTab_Switcher,NULL);
	button_toggle(150,50,"IO_SoundTab_On.png","IO_SoundTab_Off.png","IO_SoundTab_Over.png","IO_SoundTab_Over.png",NULL,GObjectTypeTab_Switcher,NULL);
	button_toggle(260,50,"IO_ParticleTab_On.png","IO_ParticleTab_Off.png","IO_ParticleTab_Over.png","IO_ParticleTab_Over.png",NULL,GObjectTypeTab_Switcher,NULL);
	button_toggle(370,50,"IO_LightTab_On.png","IO_LightTab_Off.png","IO_LightTab_Over.png","IO_LightTab_Over.png",NULL,GObjectTypeTab_Switcher,NULL);
	button_toggle(480,50,"IO_SpriteTab_On.png","IO_SpriteTab_Off.png","IO_SpriteTab_Over.png","IO_SpriteTab_Over.png",NULL,GObjectTypeTab_Switcher,NULL);
	button_toggle(590,50,"IO_TerrainTab_On.png","IO_TerrainTab_Off.png","IO_TerrainTab_Over.png","IO_TerrainTab_Over.png",NULL,GObjectTypeTab_Switcher,NULL);
	button_toggle(40,80,"IO_BlockTab_On.png","IO_BlockTab_Off.png","IO_BlockTab_Over.png","IO_BlockTab_Over.png",NULL,GObjectTypeTab_Switcher,NULL);
	button_toggle(150,80,"IO_SysTab_On.png","IO_SysTab_Off.png","IO_SysTab_On.png","IO_SysTab_On.png",NULL,GObjectTypeTab_Switcher,NULL);
	
	flags = OVERLAY;
	
	on_click = GPanelDrag;
	
}


PANEL *empty = {
	
	layer = 0;
	
}

PANEL *IO_ObjectTab = {
	
	layer = 5;
	
	// 1->8
	button_toggle(0,0,"IO_ObjectTab_anms_on.png","IO_ObjectTab_anms.png","IO_ObjectTab_anms_on.png","IO_ObjectTab_anms_on.png",NULL,GIO_ObjectTab_SwitchTab,NULL);
	button_toggle(0,30,"IO_ObjectTab_archs_on.png","IO_ObjectTab_archs.png","IO_ObjectTab_archs_on.png",,"IO_ObjectTab_archs_on.png",NULL,GIO_ObjectTab_SwitchTab,NULL);
	button_toggle(0,60,"IO_ObjectTab_chars_on.png","IO_ObjectTab_chars.png","IO_ObjectTab_chars_on.png","IO_ObjectTab_chars_on.png",NULL,GIO_ObjectTab_SwitchTab,NULL);
	button_toggle(0,90,"IO_ObjectTab_etc_on.png","IO_ObjectTab_etc.png","IO_ObjectTab_etc_on.png","IO_ObjectTab_etc_on.png",NULL,GIO_ObjectTab_SwitchTab,NULL);
	button_toggle(0,120,"IO_ObjectTab_food_on.png","IO_ObjectTab_food.png","IO_ObjectTab_food_on.png","IO_ObjectTab_food_on.png",NULL,GIO_ObjectTab_SwitchTab,NULL);
	button_toggle(0,150,"IO_ObjectTab_machs_on.png","IO_ObjectTab_machs.png","IO_ObjectTab_machs_on.png","IO_ObjectTab_machs_on.png",NULL,GIO_ObjectTab_SwitchTab,NULL);
	button_toggle(0,180,"IO_ObjectTab_plants_on.png","IO_ObjectTab_plants.png","IO_ObjectTab_plants_on.png","IO_ObjectTab_plants_on.png",NULL,GIO_ObjectTab_SwitchTab,NULL);
	button_toggle(0,210,"IO_ObjectTab_tportts_on.png","IO_ObjectTab_tportts.png","IO_ObjectTab_tportts_on.png","IO_ObjectTab_tportts_on.png",NULL,GIO_ObjectTab_SwitchTab,NULL);
	
}

PANEL *LightPresets = {
	
	layer = 6;
	
	button(0,0,"LightPreset1.bmp","LightPreset1.bmp","LightPreset1.bmp",NULL,GSelectLight,NULL);
	button(80,0,"LightPreset2.bmp","LightPreset2.bmp","LightPreset2.bmp",NULL,GSelectLight,NULL);
	button(160,0,"LightPreset3.bmp","LightPreset3.bmp","LightPreset3.bmp",NULL,GSelectLight,NULL);
	button(240,0,"LightPreset4.bmp","LightPreset4.bmp","LightPreset4.bmp",NULL,GSelectLight,NULL);
	
	button(0,40,"LightPreset5.bmp","LightPreset5.bmp","LightPreset5.bmp",NULL,GSelectLight,NULL);
	button(80,40,"LightPreset6.bmp","LightPreset6.bmp","LightPreset6.bmp",NULL,GSelectLight,NULL);
	button(160,40,"LightPreset7.bmp","LightPreset7.bmp","LightPreset7.bmp",NULL,GSelectLight,NULL);
	button(240,40,"LightPreset8.bmp","LightPreset8.bmp","LightPreset8.bmp",NULL,GSelectLight,NULL);
	
	button(0,80,"LightPreset9.bmp","LightPreset9.bmp","LightPreset9.bmp",NULL,GSelectLight,NULL);
	button(80,80,"LightPreset10.bmp","LightPreset10.bmp","LightPreset10.bmp",NULL,GSelectLight,NULL);
	button(160,80,"LightPreset11.bmp","LightPreset11.bmp","LightPreset11.bmp",NULL,GSelectLight,NULL);
	button(240,80,"LightPreset12.bmp","LightPreset12.bmp","LightPreset12.bmp",NULL,GSelectLight,NULL);
	
}

PANEL *buttonlst_submenu_terrain = {
	layer = 1;
	
	bmap = "button_submenu_black.bmp";
	
	button(0,0,"torreeiffel_up.png","torreeiffel_up.png","torreeiffel_up.png",NULL,NULL,NULL);
	button(0,0,"torreeiffel_down.png","torreeiffel_down.png","torreeiffel_down.png",NULL,NULL,NULL);
	button(0,0,menu1_submenu3,menu1_submenu3_off,menu1_submenu3_over,NULL,NULL,NULL);
	button(0,0,menu1_submenu4,menu1_submenu4_off,menu1_submenu4_over,NULL,NULL,NULL);
	
	// The final button will be the back button.
	button(0,0,"button_back.png","button_back.png","button_back.png",NULL,GWindowClose,NULL);
	
	flags = OVERLAY;
}

PANEL *buttonlst_submenu_object = {
	layer = 1;
	
	bmap = "button_submenu_black.bmp";
	
	button(0,0,"button_back.png","button_back.png","button_back.png",NULL,GWindowClose,NULL);
	
	flags = OVERLAY;
}

PANEL *buttonlst_submenu_path = {
	layer = 1;
	
	bmap = "button_submenu_black.bmp";
	
	button(0,0,menu3_submenu1,menu3_submenu1_off,menu3_submenu1_over,NULL,NULL,NULL);
	button(0,0,menu3_submenu2,menu3_submenu2_off,menu3_submenu2_over,NULL,NULL,NULL);
	//	button(0,0,menu3_submenu3,menu3_submenu3,menu3_submenu3,NULL,NULL,NULL);
	//	button(0,0,menu3_submenu4,menu3_submenu4,menu3_submenu4,NULL,NULL,NULL);
	
	button(0,0,"button_back.png","button_back.png","button_back.png",NULL,GWindowClose,NULL);
	
	flags = OVERLAY;
	
}

PANEL *panHome = {
	layer = 2;
	
	bmap = "panHome.bmp"; // 437x431
	
	button(0,0,"button_close_on.bmp","button_close_off.bmp","button_close_over.bmp",NULL,GWindowClose,NULL);
	
	button(88,35,"button_saveworld_on.png","button_saveworld_off.png","button_saveworld_over.png",NULL,GGameSave,NULL);
	button(119,80,"button_loadworld_on.png","button_loadworld_off.png","button_loadworld_over.png",NULL,GGameLoad,NULL);
	button(113,123,"button_newworld_on.png","button_newworld_off.png","button_newworld_over.png",NULL,GWorldNew,NULL);
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
	
	button(2,170,"button_default_on.bmp","button_default_off.bmp","button_default_on.bmp",NULL,ObjectRestoreDefault,NULL);
	button(90,170,"button_randomrotate_on.bmp","button_randomrotate_off.bmp","button_randomrotate_on.bmp",NULL,ObjectRandomPan,NULL);
	
	hslider(0,221,100,slider,0,100,v_alpha);	
	hslider(0,268,100,slider,0,100,v_ambient);
	
	flags = OVERLAY;	
	
}

PANEL *panProp_2 = { // Materials
	
	layer = 5;
	
	button_toggle(0,0,"button_Mat1_on.bmp","button_Mat1.bmp","button_Mat1_on.bmp","button_Mat1_on.bmp",NULL,MaterialSelect,NULL);
	button_toggle(0,30,"button_Mat2_on.bmp","button_Mat2.bmp","button_Mat2_on.bmp","button_Mat2_on.bmp",NULL,MaterialSelect,NULL);
	button_toggle(0,60,"button_Mat3_on.bmp","button_Mat3.bmp","button_Mat3_on.bmp","button_Mat3_on.bmp",NULL,MaterialSelect,NULL);
	button_toggle(0,90,"button_Mat4_on.bmp","button_Mat4.bmp","button_Mat4_on.bmp","button_Mat4_on.bmp",NULL,MaterialSelect,NULL);
	button_toggle(0,120,"button_Mat5_on.bmp","button_Mat5.bmp","button_Mat5_on.bmp","button_Mat5_on.bmp",NULL,MaterialSelect,NULL);
	button_toggle(0,150,"button_Mat6_on.bmp","button_Mat6.bmp","button_Mat6_on.bmp","button_Mat6_on.bmp",NULL,MaterialSelect,NULL);
	button_toggle(0,180,"button_Mat7_on.bmp","button_Mat7.bmp","button_Mat7_on.bmp","button_Mat7_on.bmp",NULL,MaterialSelect,NULL);
	button_toggle(0,210,"button_Mat8_on.bmp","button_Mat8.bmp","button_Mat8_on.bmp","button_Mat8_on.bmp",NULL,MaterialSelect,NULL);
	button_toggle(0,240,"button_Mat9_on.bmp","button_Mat9.bmp","button_Mat9_on.bmp","button_Mat9_on.bmp",NULL,MaterialSelect,NULL);
	button_toggle(0,270,"button_Mat10_on.bmp","button_Mat10.bmp","button_Mat10_on.bmp","button_Mat10_on.bmp",NULL,MaterialSelect,NULL);
	button_toggle(0,300,"button_Mat11_on.bmp","button_Mat11.bmp","button_Mat11_on.bmp","button_Mat11_on.bmp",NULL,MaterialSelect,NULL);
	button_toggle(0,330,"button_Mat12_on.bmp","button_Mat12.bmp","button_Mat12_on.bmp","button_Mat12_on.bmp",NULL,MaterialSelect,NULL);
	button_toggle(0,360,"button_Mat13_on.bmp","button_Mat13.bmp","button_Mat13_on.bmp","button_Mat13_on.bmp",NULL,MaterialSelect,NULL);
	button_toggle(0,390,"button_Mat14_on.bmp","button_Mat14.bmp","button_Mat14_on.bmp","button_Mat14_on.bmp",NULL,MaterialSelect,NULL);
	button_toggle(0,420,"button_Mat15_on.bmp","button_Mat15.bmp","button_Mat15_on.bmp","button_Mat15_on.bmp",NULL,MaterialSelect,NULL);
	
	button(160,0,"box_icons_on.png","box_icons.png","box_icons_on.png",NULL,GMaterialEditorShow,NULL);
	
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
	
	button(0,0,"button_close_on.bmp","button_close_off.bmp","button_close_over.bmp",NULL,GWindowClose,NULL);
	
	button_toggle(0,0,"button_generalattrib_on.bmp","button_generalattrib.bmp","button_generalattrib_on.bmp","button_generalattrib_on.bmp",NULL,GpanPropSwitchPage,NULL);
	button_toggle(0,0,"button_material_on.bmp","button_material.bmp","button_material_on.bmp","button_material_on.bmp",NULL,GpanPropSwitchPage,NULL);
	button_toggle(0,0,"button_physics_on.bmp","button_physics.bmp","button_physics_on.bmp","button_physics_on.bmp",NULL,GpanPropSwitchPage,NULL);	
	//	button(0,0,"button_apply_on.bmp","button_apply.bmp","button_apply_on.bmp",NULL,NULL,NULL);
	
	on_click = GPanelDrag;
	
	flags = TRANSLUCENT;
}

PANEL *panMat_Sub1 = {
	layer = 2;
	
	bmap = "panMatEd.bmp";
	
	button(0,0,"button_close_on.bmp","button_close_off.bmp","button_close_over.bmp",NULL,GWindowClose,NULL);
	button(4,20,"button_savemat_on.bmp","button_savemat_off.bmp","button_savemat_on.bmp",NULL,MaterialSave,NULL);
	
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
	
	button(0,0,"button_close_on.bmp","button_close_off.bmp","button_close_over.bmp",NULL,GWindowClose,NULL);
	
	bmap = "panSnd.bmp";
	
	on_click = GPanelDrag;
	
	flags = TRANSLUCENT;
	
}

PANEL *panParticle = {
	
	layer = 3;
	
	button(0,0,"button_close_on.bmp","button_close_off.bmp","button_close_over.bmp",NULL,GWindowClose,NULL);
	
	bmap = "panParticle.bmp";
	
	on_click = GPanelDrag;
	
	flags = TRANSLUCENT;
	
}


PANEL *panMain_Top = {
	layer = 0;
	
	bmap = "panMain_Top.bmp";
	
	button_toggle(0,0,flag_MOVE_on,flag_MOVE,flag_MOVE_on,flag_MOVE_on,NULL,GSwitchToMoveMode,NULL);
	button_toggle(0,0,flag_ROTATE_on,flag_ROTATE,flag_ROTATE_on,flag_ROTATE_on,NULL,GSwitchToRotateMode,NULL);
	button_toggle(0,0,flag_SCALE_on,flag_SCALE,flag_SCALE_on,flag_SCALE_on,NULL,GSwitchToScaleMode,NULL);
	
	flags = OVERLAY | SHOW;
}

PANEL *panMain_Bottom = {
	layer = 0;
	
	bmap = "panMain_Bottom.bmp";
	
	button(0,0,"home.png","home.png","home.png",NULL,GHomeShow,NULL);
	button(0,0,"pathing.png","pathing.png","pathing.png",NULL,GTerrainSubmenuShow,NULL);
	button(0,0,"objects.png","objects.png","objects.png",NULL,GInsertObjectShow,NULL);
	button(0,0,"path_32.png","path_32.png","path_32.png",NULL,GPathSubmenuShow,NULL);
	
	
	flags = OVERLAY | SHOW;
}

PANEL *panMain_Play = {
	layer = 0;
	
	bmap = "panMain_Play.bmp";
	
	button(0,0,"v.png","button_ok.png","button_ok.png",NULL,LoadPlayground,NULL);
	
	flags = OVERLAY | SHOW;
}

PANEL *blackscreen = {
	bmap = "bitmap.bmp";
}

PANEL *panLight = {
	
	layer = 2;
	
	bmap = "panLight.bmp";
	
	button(0,0,"button_close_on.bmp","button_close_off.bmp","button_close_over.bmp",NULL,GWindowClose,NULL);
	
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
	button(0,0,"button_close_on.bmp","button_close_off.bmp","button_close_over.bmp",NULL,GWindowClose,NULL);
	
	// 2
	button_toggle(145,60,"flag_new_on.bmp","flag_new_.bmp","flag_new_on.bmp","flag_new_on.bmp",NULL,GToggleLevelCreationMode,NULL);
	
	// 3
	button_toggle(465,60,"flag_new_on.bmp","flag_new_.bmp","flag_new_on.bmp","flag_new_on.bmp",NULL,GToggleLevelCreationMode,NULL);
	
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
	button(605,460,"button_creatworld_on.bmp","button_creatworld_off.bmp","button_creatworld_on.bmp",NULL,LoadNewLevelFromWindow,NULL);
	
	flags = OVERLAY | TRANSLUCENT;
	
	on_click = GPanelDrag;
	
}

PANEL *panSaveGame = {
	
	layer = 2;
	
	bmap = "panSaveGame.bmp";
	
	button(0,0,"button_close_on.bmp","button_close_off.bmp","button_close_over.bmp",NULL,GWindowClose,NULL);
	
	button(20,25,slot1,slot1,slot1,NULL,SaveGameToSlot,NULL);
	button(126,25,slot2,slot2,slot2,NULL,SaveGameToSlot,NULL);
	button(232,25,slot3,slot3,slot3,NULL,SaveGameToSlot,NULL);
	button(20,131,slot4,slot4,slot4,NULL,SaveGameToSlot,NULL);
	button(126,131,slot5,slot5,slot5,NULL,SaveGameToSlot,NULL);
	button(232,131,slot6,slot6,slot6,NULL,SaveGameToSlot,NULL);
	button(20,237,slot7,slot7,slot7,NULL,SaveGameToSlot,NULL);
	button(126,237,slot8,slot8,slot8,NULL,SaveGameToSlot,NULL);
	button(232,237,slot9,slot9,slot9,NULL,SaveGameToSlot,NULL);
	//	button(0,180,slot10,slot10,slot10,NULL,SaveGameToSlot,NULL);
	//	button(0,200,slot11,slot11,slot11,NULL,SaveGameToSlot,NULL);
	//	button(0,220,slot12,slot12,slot12,NULL,SaveGameToSlot,NULL);
	//	button(0,240,slot13,slot13,slot13,NULL,SaveGameToSlot,NULL);
	//	button(0,260,slot14,slot14,slot14,NULL,SaveGameToSlot,NULL);
	//	button(0,280,slot15,slot15,slot15,NULL,SaveGameToSlot,NULL);
	//	button(0,300,slot16,slot16,slot16,NULL,SaveGameToSlot,NULL);
	//	button(0,320,slot17,slot17,slot17,NULL,SaveGameToSlot,NULL);
	//	button(0,340,slot18,slot18,slot18,NULL,SaveGameToSlot,NULL);
	//	button(0,360,slot19,slot19,slot19,NULL,SaveGameToSlot,NULL);
	//	button(0,380,slot20,slot20,slot20,NULL,SaveGameToSlot,NULL);
	
	flags = TRANSLUCENT;
	
	on_click = GPanelDrag;
	
}

PANEL *panLoadGame = {
	
	layer = 2;
	bmap = "panLoadGame.bmp";
	
	button(0,0,"button_close_on.bmp","button_close_off.bmp","button_close_over.bmp",NULL,GWindowClose,NULL);
	
	button(20,25,slot1,slot1,slot1,NULL,LoadGameFromSlot,NULL);
	button(126,25,slot2,slot2,slot2,NULL,LoadGameFromSlot,NULL);
	button(232,25,slot3,slot3,slot3,NULL,LoadGameFromSlot,NULL);
	button(20,131,slot4,slot4,slot4,NULL,LoadGameFromSlot,NULL);
	button(126,131,slot5,slot5,slot5,NULL,LoadGameFromSlot,NULL);
	button(232,131,slot6,slot6,slot6,NULL,LoadGameFromSlot,NULL);
	button(20,237,slot7,slot7,slot7,NULL,LoadGameFromSlot,NULL);
	button(126,237,slot8,slot8,slot8,NULL,LoadGameFromSlot,NULL);
	button(232,237,slot9,slot9,slot9,NULL,LoadGameFromSlot,NULL);
	//		button(100,180,slot10,slot10,slot10,NULL,LoadGameFromSlot,NULL);
	//		button(100,200,slot11,slot11,slot11,NULL,LoadGameFromSlot,NULL);
	//		button(100,220,slot12,slot12,slot12,NULL,LoadGameFromSlot,NULL);
	//		button(100,240,slot13,slot13,slot13,NULL,LoadGameFromSlot,NULL);
	//		button(100,260,slot14,slot14,slot14,NULL,LoadGameFromSlot,NULL);
	//		button(100,280,slot15,slot15,slot15,NULL,LoadGameFromSlot,NULL);
	//		button(100,300,slot16,slot16,slot16,NULL,LoadGameFromSlot,NULL);
	//		button(100,320,slot17,slot17,slot17,NULL,LoadGameFromSlot,NULL);
	//		button(100,340,slot18,slot18,slot18,NULL,LoadGameFromSlot,NULL);
	//		button(100,360,slot19,slot19,slot19,NULL,LoadGameFromSlot,NULL);
	//		button(100,380,slot20,slot20,slot20,NULL,LoadGameFromSlot,NULL);
	
	flags = TRANSLUCENT;
	
	on_click = GPanelDrag;
	
}

PANEL *panMMenu = {
	
	layer = 1;
	//	bmap = "panMMenu_Main.bmp";
	
	// Old code
	/*
	button(20,25,slot1,slot1,slot1,LoadGameFromSlot,NULL,NULL);
	button(126,25,slot2,slot2,slot2,LoadGamweFromSlot,NULL,NULL);
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
	*/
	
	button(0,0,"button_NewGame_on.bmp","button_NewGame_off.bmp","button_NewGame_on.bmp",NULL,GWorldNew,NULL);
	button(0,25,"button_LoadGame_on.bmp","button_LoadGame_off.bmp","button_LoadGame_on.bmp",NULL,GLoadGameShow,NULL);
	button(0,50,"button_Options_on.bmp","button_Options_off.bmp","button_Options_on.bmp",NULL,GOptionsShow,NULL);
	button(0,75,"button_Achievements_on.bmp","button_Achievements_off.bmp","button_Achievements_on.bmp",NULL,NULL,NULL);
	button(0,100,"button_Credits_on.bmp","button_Credits_off.bmp","button_Credits_on.bmp",NULL,GShowCredits,NULL);
	//	button(0,100,"button_Exit_on.bmp","button_Exit_off.bmp","button_Exit_on.bmp",NULL,NULL,NULL);
	
	flags = OVERLAY | TRANSLUCENT;
	
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
	
	if(event_type == EVENT_RELEASE) return;
	
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
	if(p == panLight) GLightWindowHide();
	if(p == panSnd) GSoundWindowHide();
	if(p == panParticle) GParticleWindowHide();
	if(p == panProp) GPropertiesWindowHide();
	if(p == InsertObject) GInsertObjectHide();
	if(p == Options_Graphics) GOptionsHide();
	
	if(p == panSaveGame) reset(panSaveGame,SHOW);
	if(p == panLoadGame) reset(panLoadGame,SHOW);
	
}

/* 
--------------------------------------------------
void GToggleLevelCreationMode(var ID)


--------------------------------------------------
*/
void GToggleLevelCreationMode(var ID) {
	
	if(event_type == EVENT_RELEASE) return;
	
	if(ID == 2) button_state(panNewGame,3,0);
	else button_state(panNewGame,2,0);
	
}


/* 
--------------------------------------------------
void GGameLoad()


--------------------------------------------------
*/
void GGameLoad() {
	
	if(event_type == EVENT_RELEASE) return;
	
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
	
	if(event_type == EVENT_RELEASE) return;
	
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
		
		case 'x': p.scale_x = sys_metrics(0)/bmap_width(p.bmap);
		break;
		
		case 'y': p.scale_y = sys_metrics(1)/bmap_height(p.bmap);
		break;
		
		default:
		
		p.pos_x = p.pos_y = 0;
		
		p.scale_x = sys_metrics(0)/bmap_width(p.bmap);
		p.scale_y = sys_metrics(1)/bmap_height(p.bmap);
		
		break;
		
	}
	
}

/* 
--------------------------------------------------
void GGUIInit()


--------------------------------------------------
*/
void GGUIInit() {
	
	wait(2);
	
	GPanelResize(panCAMRecorder,'t'); // x+y-scale
	GPanelResize(panScreenshot,'t');
	
	panMMenu.pos_x = 10;
	panMMenu.pos_y = screen_size.y/4;
	
	int i;
	for(i = 3;i > 0;i--) pan_setpos(panCAMRecorder_digits,1,i,vector(screen_size.x - 35 - 30 * i,BORDER,0));
	
	panMain_Top.pos_x = screen_size.x - bmap_width(panMain_Top.bmap) - (BORDER + 3 * 32);
	panMain_Top.pos_y = BORDER;

	panMain_Bottom.pos_x = BORDER;
	panMain_Bottom.pos_y = screen_size.y - bmap_height(panMain_Bottom.bmap) - BORDER;

	panRotateHelp.pos_x = screen_size.x - bmap_width(panRotateHelp.bmap) - BORDER * 2;
	panRotateHelp.pos_y = panMain_Top.pos_y + BORDER * 2;

	panScaleHelp.pos_x = screen_size.x - bmap_width(panScaleHelp.bmap) - BORDER * 2;
	panScaleHelp.pos_y = panRotateHelp.pos_y;

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
	
	Options_Graphics.pos_y =
	Options_Sound.pos_y = 
	Options_Themes.pos_y = 
	Options_Maintenance.pos_y =
	(screen_size.y - bmap_height(Options_Graphics.bmap)) / 2;
	
	Options_Graphics.pos_x =
	Options_Sound.pos_x = 
	Options_Themes.pos_x = 
	Options_Maintenance.pos_x =
	screen_size.x - bmap_width(Options_Graphics.bmap) - BORDER*3;
	
	LoadGame_Uppart.pos_x = screen_size.x - bmap_width(LoadGameInside.bmap);
	LoadGame_Uppart.pos_y = 0;
	
	LoadGame_Downpart.pos_x = screen_size.x - bmap_width(LoadGame_Downpart.bmap);
	LoadGame_Downpart.pos_y = screen_size.y - bmap_height(LoadGame_Downpart.bmap);
	
	LoadGameInside.pos_x = screen_size.x - bmap_width(LoadGameInside.bmap);
	LoadGameInside.pos_y = bmap_height(LoadGame_Uppart.bmap); // so that the buttons won't get stuck
	
	ZTool.pos_x = screen_size.x - bmap_width(ZTool.bmap) - BORDER * 2;
	ZTool.pos_y = (screen_size.y - bmap_height(ZTool.bmap))/2;
	
	
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
	
	OptionsGraphicsTxt = txt_create(10,500);
	OptionsSoundTxt = txt_create(10,500);
	OptionsThemesTxt = txt_create(10,500);
	OptionsMaintenanceTxt = txt_create(10,500);
	
	OptionsGraphicsTxt->font = OptionsSoundTxt->font = OptionsThemesTxt->font = OptionsMaintenanceTxt->font = font_create("Arial#19");
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
	
	if(event_type == EVENT_RELEASE) return;
	
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
	
	if(event_type == EVENT_RELEASE) return;
	
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
		if(select.ObjectType == Object) GPropertiesWindowHide();
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
	reset(ZTool,SHOW);
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
	
	if(event_type == EVENT_RELEASE) return;

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
	
	if(event_type == EVENT_RELEASE) return;

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

// stupid switchers
// lite-C compiler: stupid programmer

/*
--------------------------------------------------
void GSwitchToMoveMode()


--------------------------------------------------
*/
void GSwitchToMoveMode() {
	
	if(event_type == EVENT_RELEASE) return;
	
	if(!is(ZTool,SHOW)) set(ZTool,SHOW);

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
		
		if(is(ZTool,SHOW)) reset(ZTool,SHOW);
		
	}
}

/*
--------------------------------------------------
void GSwitchToRotateMode()


--------------------------------------------------
*/
void GSwitchToRotateMode() {
	
	if(event_type == EVENT_RELEASE) return;
	
	if(!is(ZTool,SHOW)) set(ZTool,SHOW);

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
		
		if(is(ZTool,SHOW)) reset(ZTool,SHOW);
		
	}
}

/*
--------------------------------------------------
void GSwitchToScaleMode()


--------------------------------------------------
*/
void GSwitchToScaleMode() {
	
	if(event_type == EVENT_RELEASE) return;
	
	if(!is(ZTool,SHOW)) set(ZTool,SHOW);

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
		
		if(is(ZTool,SHOW)) reset(ZTool,SHOW);
		
	}

}

/*
--------------------------------------------------
void GNotificationCreate(FONT *f, STRING *r)


--------------------------------------------------
*/
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

/*
--------------------------------------------------
void GShowCredits()


--------------------------------------------------
*/
void GShowCredits() {
	
	if(event_type == EVENT_RELEASE) return;
	
	var rollspeed = .5;
	
	reset(panMMenu,SHOW);
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

/*
--------------------------------------------------
void GPanelSizeForWH(PANEL *p, BMAP *b)

Desc: Just a small function for use within GObjectTypeSwitcher(var).
Updates the size of p according to b's size.

Returns: -
--------------------------------------------------
*/
void GPanelSizeForWH(PANEL *p, BMAP *b) {
	while(b == NULL || p == NULL) wait(1);

	p.size_x = bmap_width(b);
	p.size_y = bmap_height(b);

}

/*
--------------------------------------------------
void GLoadMainMenu()


--------------------------------------------------
*/
void GLoadMainMenu() {
	
	IN_GAME = 0;
	
	GGUIHide();
	//	GPanelCenter(panMMenu);
	
	launch_newgame_from_main = 1;
	
	level_load("_tech.wmb");
	game_load(pref_savebmaps,0);
	
	set(panMMenu,SHOW);
	
	GPanelSelect(panMMenu);
	
	panMMenu.alpha = 50;
	
	// dev text goes here
}

/*
--------------------------------------------------
void GOptionsShow()


--------------------------------------------------
*/
void GOptionsShow() {
	
	if(event_type == EVENT_RELEASE) return;
	
	GLoadGameHide();
	
	GOptions_Graphics();
}

/*
--------------------------------------------------
void GOptionsHide()


--------------------------------------------------
*/
void GOptionsHide() {
	
	if(is(Options_Graphics,SHOW)) {
		
		reset(Options_Graphics,SHOW);
		reset(OptionsGraphicsTxt,SHOW);
		
		return;
		
	}
	
	if(is(Options_Sound,SHOW)) {
		
		reset(Options_Sound,SHOW);
		reset(OptionsSoundTxt,SHOW);
		
		return;
		
	}
	
	if(is(Options_Themes,SHOW)) {
		
		reset(Options_Themes,SHOW);
		
		return;
		
	}
	
	if(is(Options_Maintenance,SHOW)) {
		
		reset(Options_Maintenance,SHOW);
		
		return;
		
	}
	
}

/*
--------------------------------------------------
void GPropertiesWindowShow()


--------------------------------------------------
*/
void GPropertiesWindowShow() {
	
	if(!lfsp) { // If prop() was launched from GpanPropSwitchPage, don't re-change window's position.
		
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

/*
--------------------------------------------------
void GPropertiesWindowHide()


--------------------------------------------------
*/
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

/*
--------------------------------------------------
void GSoundWindowShow() 


--------------------------------------------------
*/
void GSoundWindowShow() {
	
	panSnd.pos_x = xy_panSnd.x;
	panSnd.pos_y = xy_panSnd.y;
	
	GGUIUpdate(panSnd);
	set(panSnd,SHOW);
	
	GPanelSelect(panSnd);
	
}

/*
--------------------------------------------------
void GSoundWindowHide()


--------------------------------------------------
*/
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
	
	if(event_type == EVENT_RELEASE) return;
	
	if(!is(panNewGame,SHOW)) {
		
		GGUIUpdate(panNewGame);
		GPanelCenter(panNewGame);
		
		set(panNewGame,SHOW);
		
		GPanelSelect(panNewGame); // Bring me to the TOP ! =))
		
		// Set some default parameters
		
		GToggleLevelCreationMode(2);
		button_state(panNewGame,2,1); // Static sky by default
		
		v_fogdensity = 3000; // Make fog_end a bit larger
		v_fogr = v_fogg = v_fogb = (var)255/2;
		
		_moon_scale_fac = moon_scale_fac;
		_time_speed_night = time_speed_night;
		_night_sky_scale_x = night_sky_scale_x;
		_night_sky_speed_x = night_sky_speed_x;
		
		//		button_state (panNewGame,5,1); // Lensflare on by default
		//		button_state (panNewGame,7,1); // Moon too
	}
	
}

/*
--------------------------------------------------
void GpanPropSwitchPage(var mode)


--------------------------------------------------
*/
void GpanPropSwitchPage(var mode) {
	
	if(event_type == EVENT_RELEASE) return;

	page=mode--;
	lfsp++;
	GPropertiesWindowShow();

}

/*
--------------------------------------------------
void GIO_ObjectTab_SwitchTab(var ID)


--------------------------------------------------
*/
void GIO_ObjectTab_SwitchTab(var ID) {
	
	if(event_type == EVENT_RELEASE) return;
	
	int _ID = ID, i;
	
	if(!button_state(IO_ObjectTab,_ID,-1)) {
		
		reset(files_list,SHOW);
		reset(InsertObject_Inputter,SHOW);
		
		FolderScan(files_list,"./","empty"); // Empty scan
		
		return;
		
	}
	
	else {
		
		if(!is(files_list,SHOW)) set(files_list,SHOW);
		if(!is(InsertObject_Inputter,SHOW)) set(InsertObject_Inputter,SHOW);
		
		switch(_ID) {
			
			// Animals
			case 1:
			
			for(i = 2;i <= 8;i++) button_state(IO_ObjectTab,i,0);
			
			FolderScan(files_list,PATH_OBJECTS_ANMS,EXT_OBJECT);
			
			break;
			
			// Architectures
			case 2:
			
			for(i = _ID-1;i >= 1;i--) button_state(IO_ObjectTab,i,0);
			for(i = _ID+1;i <= 8;i++) button_state(IO_ObjectTab,i,0);
			
			FolderScan(files_list,PATH_OBJECTS_ARCHS,EXT_OBJECT);
			
			break;
			
			// Characters
			case 3:

			for(i = _ID-1;i >= 1;i--) button_state(IO_ObjectTab,i,0);
			for(i = _ID+1;i <= 8;i++) button_state(IO_ObjectTab,i,0);
			
			FolderScan(files_list,PATH_OBJECTS_CHARS,EXT_OBJECT);   
			
			break;
			
			// Everyday objects
			case 4:
			
			for(i = _ID-1;i >= 1;i--) button_state(IO_ObjectTab,i,0);
			for(i = _ID+1;i <= 8;i++) button_state(IO_ObjectTab,i,0);
			
			FolderScan(files_list,PATH_OBJECTS_ETC,EXT_OBJECT);
			
			break;
			
			// Food
			case 5:
			
			for(i = _ID-1;i >= 1;i--) button_state(IO_ObjectTab,i,0);
			for(i = _ID+1;i <= 8;i++) button_state(IO_ObjectTab,i,0);
			
			FolderScan(files_list,PATH_OBJECTS_FOOD,EXT_OBJECT);
			
			break;
			
			// Machines
			case 6:
			
			for(i = _ID-1;i >= 1;i--) button_state(IO_ObjectTab,i,0);
			for(i = _ID+1;i <= 8;i++) button_state(IO_ObjectTab,i,0);
			
			FolderScan(files_list,PATH_OBJECTS_MACHS,EXT_OBJECT); 
			
			break;
			
			// Plants
			case 7:
			
			for(i = ID-1;i >= 1;i--) button_state(IO_ObjectTab,i,0);
			for(i = ID+1;i <= 8;i++) button_state(IO_ObjectTab,i,0);
			
			FolderScan(files_list,PATH_OBJECTS_PLANTS,EXT_OBJECT);
			
			break;
			
			// Transports
			case 8:
			
			for(i = _ID-1;i >= 1;i--) button_state(IO_ObjectTab,i,0);
			
			FolderScan(files_list,PATH_OBJECTS_TPORTTS,EXT_OBJECT); 
			
			break;
			
		}
		
	}
	
}

/*
--------------------------------------------------
void GObjectTypeTab_Switcher(var ID)


--------------------------------------------------
*/
void GObjectTypeTab_Switcher(var ID) {
	
	if(event_type == EVENT_RELEASE) return;
	
	int _ID;
	for(_ID = 2;_ID <= 9;_ID++) button_state(InsertObject,_ID,0);
	
	button_state(InsertObject,(int)ID,1);
	
	switch( (int)ID ) {
		
		case 2: // Object
		
		if(!is(IO_ObjectTab,SHOW)) set(IO_ObjectTab,SHOW);
		if(!is(files_list,SHOW)) set(files_list,SHOW);
		if(!is(InsertObject_Inputter,SHOW)) set(InsertObject_Inputter,SHOW);
		if(!is(IO_ObjectTab,SHOW)) set(IO_ObjectTab,SHOW);
		if(is(LightPresets,SHOW)) reset(LightPresets,SHOW);
		if(is(InsertParticle,SHOW)) reset(InsertParticle,SHOW);
		
		FolderScan(files_list,PATH_OBJECTS_ANMS,EXT_OBJECT);
		
		break;
		
		case 3: // Sound
		
		if(is(IO_ObjectTab,SHOW)) reset(IO_ObjectTab,SHOW);
		if(!is(files_list,SHOW)) set(files_list,SHOW);
		if(!is(InsertObject_Inputter,SHOW)) set(InsertObject_Inputter,SHOW);
		if(is(IO_ObjectTab,SHOW)) set(IO_ObjectTab,SHOW);
		if(is(LightPresets,SHOW)) reset(LightPresets,SHOW);
		if(is(InsertParticle,SHOW)) reset(InsertParticle,SHOW);
		
		FolderScan(files_list,PATH_SOUNDS,EXT_SOUND);
		
		break;
		
		case 4: // Particle
		
		if(is(IO_ObjectTab,SHOW)) reset(IO_ObjectTab,SHOW);
		if(is(files_list,SHOW)) reset(files_list,SHOW);
		if(is(InsertObject_Inputter,SHOW)) reset(InsertObject_Inputter,SHOW);
		if(is(IO_ObjectTab,SHOW)) reset(IO_ObjectTab,SHOW);
		if(is(LightPresets,SHOW)) reset(LightPresets,SHOW);
		if(!is(InsertParticle,SHOW)) set(InsertParticle,SHOW);
		
		break;
		
		case 5: // Light
		
		if(is(IO_ObjectTab,SHOW)) reset(IO_ObjectTab,SHOW);
		if(is(files_list,SHOW)) reset(files_list,SHOW);
		if(is(InsertObject_Inputter,SHOW)) reset(InsertObject_Inputter,SHOW);
		if(is(IO_ObjectTab,SHOW)) reset(IO_ObjectTab,SHOW);
		if(!is(LightPresets,SHOW)) set(LightPresets,SHOW);
		if(is(InsertParticle,SHOW)) reset(InsertParticle,SHOW);
		
		break;
		
		case 6: // Sprite
		
		if(!is(IO_ObjectTab,SHOW)) set(IO_ObjectTab,SHOW);
		if(!is(files_list,SHOW)) set(files_list,SHOW);
		if(!is(InsertObject_Inputter,SHOW)) set(InsertObject_Inputter,SHOW);
		if(is(IO_ObjectTab,SHOW)) reset(IO_ObjectTab,SHOW);
		if(is(LightPresets,SHOW)) reset(LightPresets,SHOW);
		if(is(InsertParticle,SHOW)) reset(InsertParticle,SHOW);
		
		FolderScan(files_list,PATH_SPRITES,EXT_SPRITE);
		
		break;
		
		case 7: // Terrain
		
		if(!is(IO_ObjectTab,SHOW)) set(IO_ObjectTab,SHOW);
		if(!is(files_list,SHOW)) set(files_list,SHOW);
		if(!is(InsertObject_Inputter,SHOW)) set(InsertObject_Inputter,SHOW);
		if(is(IO_ObjectTab,SHOW)) reset(IO_ObjectTab,SHOW);
		if(is(LightPresets,SHOW)) reset(LightPresets,SHOW);
		if(is(InsertParticle,SHOW)) reset(InsertParticle,SHOW);
		
		FolderScan(files_list,PATH_TERRAINS,EXT_TERRAIN);
		
		case 8: // Node
		
		break;
		
		case 9: // Event Trigger + trigger
		
		break;
		
	}
	
}

/*
--------------------------------------------------
void GInsertObjectShow()


--------------------------------------------------
*/
void GInsertObjectShow() {
	
	if(event_type == EVENT_RELEASE) return;
	
	set(InsertObject,SHOW);
	set(IO_ObjectTab,SHOW);
	set(InsertObject_Inputter,SHOW);
	
	int i;
	for(i = 2;i<=8;i++) button_state(IO_ObjectTab,i,0);
	for(i = 3;i<=7;i++) button_state(InsertObject,i,0);
	
	button_state(IO_ObjectTab,1,1);
	button_state(InsertObject,2,1);
	
	set(files_list,SHOW);
	
	layer_sort(files_list,50);
	layer_sort(InsertObject_Inputter,100);
	
	FolderScan(files_list,PATH_OBJECTS_ANMS,EXT_OBJECT);
	
	while(is(InsertObject,SHOW)) {
		
		IO_ObjectTab.pos_x = InsertObject.pos_x + 25;
		IO_ObjectTab.pos_y = InsertObject.pos_y + 250;
		
		files_list.pos_x = InsertObject.pos_x + 200;
		files_list.pos_y = InsertObject.pos_y + 100;
		
		InsertObject_Inputter.pos_x = files_list.pos_x;
		InsertObject_Inputter.pos_y = files_list.pos_y;
		
		LightPresets.pos_x = InsertObject.pos_x + 100;
		LightPresets.pos_y = InsertObject.pos_y + 100;
		
		InsertParticle.pos_x = InsertObject.pos_x + 100;
		InsertParticle.pos_y = InsertObject.pos_y + 100;
		
		wait(1);
		
	}
	
}

/*
--------------------------------------------------
void GInsertObjectHide()


--------------------------------------------------
*/
void GInsertObjectHide() {
	
	
	reset(InsertObject,SHOW);
	reset(IO_ObjectTab,SHOW);
	reset(InsertObject_Inputter,SHOW);
	reset(LightPresets,SHOW);
	reset(InsertParticle,SHOW);
	
	reset(files_list,SHOW);
	
}

/*
--------------------------------------------------
void GSelectObject(var ID)


--------------------------------------------------
*/
void GSelectObject(var ID) {
	
	if(event_type == EVENT_RELEASE) return;
	
	int _ID = ID-1;
	
	if(!str_len( (files_list.pstring)[_ID] ) || str_cmp((files_list.pstring)[_ID]," ") )  {
		
		str_cpy(TEMPSTR," ");
		
		_beep();
		return;
		
	}
	
	if(is(InsertObject,SHOW)) {
		
		if(is(IO_ObjectTab,SHOW) )
		{
			
			while( !is(files_list,SHOW) && !is(InsertObject_Inputter,SHOW) ) wait(1);
			
			/* Can't split them - TEMPSTR will be overwritten. */
			
			if(button_state(IO_ObjectTab,1,-1)) { // anms
				
				str_cpy(TEMPSTR,PATH_OBJECTS_ANMS);
				TEMP_OBJECT_TYPE = ObjectAnimal;
				
			}
			
			if(button_state(IO_ObjectTab,2,-1)) { // archs
				
				str_cpy(TEMPSTR,PATH_OBJECTS_ARCHS);
				TEMP_OBJECT_TYPE = ObjectArchitecture;
				
			}
			
			if(button_state(IO_ObjectTab,3,-1)) { // chars
				
				str_cpy(TEMPSTR,PATH_OBJECTS_CHARS);
				TEMP_OBJECT_TYPE = ObjectCharacter;
				
			}
			
			if(button_state(IO_ObjectTab,4,-1)) { // everyday/etc
				
				str_cpy(TEMPSTR,PATH_OBJECTS_ETC);
				TEMP_OBJECT_TYPE = ObjectEveryday;
				
			}
			
			if(button_state(IO_ObjectTab,5,-1)) { // food
				
				str_cpy(TEMPSTR,PATH_OBJECTS_FOOD);
				TEMP_OBJECT_TYPE = ObjectFood;
				
			}
			
			if(button_state(IO_ObjectTab,6,-1)) { // machs
				
				str_cpy(TEMPSTR,PATH_OBJECTS_MACHS);
				TEMP_OBJECT_TYPE = ObjectMachine;
				
			}
			
			if(button_state(IO_ObjectTab,7,-1)) { // plants
				
				str_cpy(TEMPSTR,PATH_OBJECTS_PLANTS);
				TEMP_OBJECT_TYPE = ObjectPlant;
				
			}
			
			if(button_state(IO_ObjectTab,8,-1)) { // transports
				
				str_cpy(TEMPSTR,PATH_OBJECTS_TPORTTS);
				TEMP_OBJECT_TYPE = ObjectTransport;
				
			}
			
			
			str_cat(TEMPSTR,(files_list.pstring)[_ID]);
			GInsertObjectHide();
			
			return;
			
		} 
		
		if(button_state(InsertObject,3,-1)) { // Sound
			
			str_cpy(TEMPSTR,PATH_SOUNDS);
			str_cat(TEMPSTR,(files_list.pstring)[_ID]);
			TEMP_OBJECT_TYPE = Sound;
			
			GInsertObjectHide();
			
			return;
			
		}
		
		if(button_state(InsertObject,6,-1)) { // Sprite
			
			str_cpy(TEMPSTR,PATH_SPRITES);
			str_cat(TEMPSTR,(files_list.pstring)[_ID]);
			TEMP_OBJECT_TYPE = Sprite;
			
			GInsertObjectHide();
			
			return;
			
		}
		
		if(button_state(InsertObject,7,-1)) { // Terrain
			
			str_cpy(TEMPSTR,PATH_TERRAINS);
			str_cat(TEMPSTR,(files_list.pstring)[_ID]);
			TEMP_OBJECT_TYPE = Terrain;
			
			GInsertObjectHide();
			
			return;
			
		}
		
	}
	
}

/*
--------------------------------------------------
void GSelectParticle(var ID)


--------------------------------------------------
*/
void GSelectParticle(var ID) {
	
	if(event_type == EVENT_RELEASE) return;
	
	switch((int)ID) {
		
		case 1: ParticleIDNumber = part_spiral; break;
		case 2: ParticleIDNumber = part_colorfulspark; break;
		case 3: ParticleIDNumber = part_spacehole; break;
		case 4: ParticleIDNumber = part_fountain2; break;
		case 5: ParticleIDNumber = part_fountain1; break;
		case 6: ParticleIDNumber = part_fire2; break;
		case 7: ParticleIDNumber = part_fire1; break;
		case 8: ParticleIDNumber = part_doublehelix; break;
		case 9: ParticleIDNumber = part_composition; break;
		
	}

	TEMP_OBJECT_TYPE = Particle;
	GInsertObjectHide();
	
}

/*
--------------------------------------------------
void GSelectLight(var ID)


--------------------------------------------------
*/
void GSelectLight(var ID) {
	
	if(event_type == EVENT_RELEASE) return;
	
	switch((int)ID) {
		
		case 1:
		// RGB color code for Pure Red
		temp_light.red = 255;
		temp_light.green = 0;
		temp_light.blue = 0;
		
		break;
		
		case 2:
		// RGB color code for Pure Green
		temp_light.red = 0;
		temp_light.green = 255;
		temp_light.blue = 0;
		
		break;
		
		case 3:
		// RGB color code for Pure Yellow
		/* 
		@en.wikipedia.org
		On a computer display, yellow is created by combining green and red light at the right intensity on a black screen.
		This is called the RGB color model.
		
		So red + green = yellow
		*/
		
		temp_light.red = 255;
		temp_light.green = 255;
		temp_light.blue = 0;
		
		break;
		
		case 4:
		// RGB color code for Teal from http://en.wikipedia.org/wiki/Teal
		temp_light.red = 54;
		temp_light.green = 117;
		temp_light.blue = 136;
		
		break;
		
		case 5:
		// RGB color code for Bud Green from http://en.wikipedia.org/wiki/List_of_colors:_A%E2%80%93F
		// Bonus: May Green, (76, 145, 65).
		temp_light.red = 123;
		temp_light.green = 182;
		temp_light.blue = 97;
		
		break;
		
		case 6:
		// RGB color code for Pure White
		temp_light.red = temp_light.green = temp_light.blue = 255;
		
		break;
		
		case 7:
		// RGB color code for Cyan from http://en.wikipedia.org/wiki/Cyan
		// green + blue = cyan
		temp_light.red = 0;
		temp_light.green = 255;
		temp_light.blue = 255;
		
		break;
		
		case 8:
		// RGB color code for Pure Orange from http://en.wikipedia.org/wiki/Orange_(colour)
		/*
		@en.wikipedia.org
		
		In the RGB colour model, the system used to create colours on a television or computer 
		screen, orange is made by combining high intensity red light 
		with a lower intensity green light, and the blue light turned off.
		
		*/
		temp_light.red = 255;
		temp_light.green = 127;
		temp_light.blue = 0;
		
		break;
		
		case 9:
		// RGB color code for Violet from http://en.wikipedia.org/wiki/Violet_(color)
		/*
		@en.wikipedia.org
		violet is simulated by purple, by combining blue light at high intensity with a less intense red light on a black screen. 
		The range of purples is created by combining blue and red light of any intensities; the chromaticities formed this way line along the "line of purples".
		*/
		
		temp_light.red = 143;
		temp_light.green = 0;
		temp_light.blue = 255;
		
		break;
		
		case 10:
		// RGB color code for Lavender from http://en.wikipedia.org/wiki/Lavender_(color)
		temp_light.red = 230;
		temp_light.green = 230;
		temp_light.blue = 250;
		
		break;
		
		case 11:
		// RGB color code for Brown from http://en.wikipedia.org/wiki/Brown
		temp_light.red = 150;
		temp_light.green = 75;
		temp_light.blue = 0;
		
		break;
		
		case 12:
		// RGB color code for Indigo from http://en.wikipedia.org/wiki/Indigo
		/*
		@en.wikipedia.org
		
		The color electric indigo is a bright and saturated color between the traditional indigo and violet. 
		This is the brightest color indigo that can be approximated on a computer screen[citation needed]—it is a color located between the (primary) blue and the color violet on the RGB color wheel.
		*/
		temp_light.red = 75;
		temp_light.green = 0;
		temp_light.blue = 130;
		
		break;
		
		// Add more color cases here, just make sure you put more buttons.
		
		
	}
	
	TEMP_OBJECT_TYPE = Light;
	GInsertObjectHide();
	
}

/*
--------------------------------------------------
void GPreMainMenu()


--------------------------------------------------
*/
void GPreMainMenu() {
	
	randomize();
	
	// Let's roll a dice
	int i = random(5); // 6 backgrounds
	
	switch(i) {
		
		case 0: BackgroundScreen.bmap = BackgroundScreen1; break;
		case 1: BackgroundScreen.bmap = BackgroundScreen2; break;
		case 2: BackgroundScreen.bmap = BackgroundScreen3; break;
		case 3: BackgroundScreen.bmap = BackgroundScreen4; break;
		case 4: BackgroundScreen.bmap = BackgroundScreen5; break;
		case 5: BackgroundScreen.bmap = BackgroundScreen6; break;
		
	}
	
	GPanelResize(BackgroundScreen,'1');
	
	set(BackgroundScreen,SHOW);
	set(PreMainMenuLoading,SHOW);
	
}

// Sorry for the terrible-lookin' code. I don't have much time.
/*
--------------------------------------------------
void GOptions_Graphics()


--------------------------------------------------
*/
void GOptions_Graphics() {
	
	if(event_type == EVENT_RELEASE) return;
	
	if(is(Options_Sound,SHOW)) {
		
		reset(Options_Sound,SHOW);
		reset(OptionsSoundTxt,SHOW);
		
	}
	if(is(Options_Themes,SHOW)) reset(Options_Themes,SHOW);
	if(is(Options_Maintenance,SHOW)) reset(Options_Maintenance,SHOW);
	
	set(Options_Graphics, SHOW);
	set(OptionsGraphicsTxt,SHOW);
	
	OptionsGraphicsTxt.pos_x = Options_Graphics.pos_x + 190;
	OptionsGraphicsTxt.pos_y = Options_Graphics.pos_y + 67;
	
	//layer_sort(OptionsGraphicsTxt,Options.layer+2);
	
	// Test for fullscreen
	switch(video_screen) {
		
		case 1: // Fullscreen
		str_cpy((OptionsGraphicsTxt.pstring)[0],"Full Screen");
		
		break;
		
		case 2: // Windowed
		str_cpy((OptionsGraphicsTxt.pstring)[0],"Windowed");
		
		break;
		
	}
	
	// Test for widescreen
	
	// Floating values can't be tested using switch..case.
	
	if(video_aspect >= 4/3 && video_aspect < 16/10) str_cpy((OptionsGraphicsTxt.pstring)[1],"4:3");
	else if(video_aspect >= 16/10 && video_aspect < 16/9) str_cpy((OptionsGraphicsTxt.pstring)[1],"16:10");
	else if(video_aspect >= 16/9) str_cpy((OptionsGraphicsTxt.pstring)[1],"16:9");
	else str_cpy((OptionsGraphicsTxt.pstring)[1],"I don't know...");	
	
	// Test for bit depth
	
	switch(video_depth) {
		
		case 16:
		str_cpy((OptionsGraphicsTxt.pstring)[2],"16-bit");
		
		break;
		
		case 32:
		str_cpy((OptionsGraphicsTxt.pstring)[2],"32-bit");
		
		break;
		
	}
	
	// Brightness
	str_cpy((OptionsGraphicsTxt.pstring)[3],str_create(str_for_num((OptionsGraphicsTxt.pstring)[3],video_gamma)));
	
	// FSAA
	str_cpy((OptionsGraphicsTxt.pstring)[4],str_create(str_for_num((OptionsGraphicsTxt.pstring)[4],d3d_antialias)));
	
	// Anisotropic filtering
	str_cpy((OptionsGraphicsTxt.pstring)[5],str_create(str_for_num((OptionsGraphicsTxt.pstring)[5],d3d_anisotropy)));
	
	
}

/*
--------------------------------------------------
void GOptions_Sound()


--------------------------------------------------
*/
void GOptions_Sound() {
	
	if(event_type == EVENT_RELEASE) return;
	
	if(is(Options_Graphics,SHOW)) {
		
		reset(Options_Graphics, SHOW);
		reset(OptionsGraphicsTxt,SHOW);
		
		
	}
	
	if(is(Options_Themes,SHOW)) reset(Options_Themes,SHOW);
	if(is(Options_Maintenance,SHOW)) reset(Options_Maintenance,SHOW);

	set(Options_Sound,SHOW);
	set(OptionsSoundTxt,SHOW);
	
	OptionsSoundTxt.pos_x = Options_Sound.pos_x + 190;
	OptionsSoundTxt.pos_y = Options_Sound.pos_y + 67;
	
	// Music volume
	str_cpy((OptionsSoundTxt.pstring)[0],str_create(str_for_num((OptionsSoundTxt.pstring)[0],VOL_MUSIC)));
	
	// Effects volume
	str_cpy((OptionsSoundTxt.pstring)[1],str_create(str_for_num((OptionsSoundTxt.pstring)[1],VOL_EFFECTS)));
	
	// Doppler effect
	str_cpy((OptionsSoundTxt.pstring)[2],str_create(str_for_num((OptionsSoundTxt.pstring)[2],doppler_factor)));
}

/*
--------------------------------------------------
void GOptions_Themes()


--------------------------------------------------
*/
void GOptions_Themes() {
	
	if(event_type == EVENT_RELEASE) return;
	
	if(is(Options_Graphics,SHOW)) {
		
		reset(Options_Graphics, SHOW);
		reset(OptionsGraphicsTxt,SHOW);
		
	}
	
	if(is(Options_Sound,SHOW)) {
		
		reset(Options_Sound,SHOW);
		reset(OptionsSoundTxt,SHOW);
		
	}
	
	reset(Options_Maintenance,SHOW);
	
	set(Options_Themes,SHOW);
	
	
	
}

/*
--------------------------------------------------
void GOptions_Maintenance()


--------------------------------------------------
*/
void GOptions_Maintenance() {
	
	if(event_type == EVENT_RELEASE) return;
	
	if(is(Options_Graphics,SHOW)) {
		
		reset(Options_Graphics, SHOW);
		reset(OptionsGraphicsTxt,SHOW);
		
	}
	
	if(is(Options_Sound,SHOW)) {
		
		reset(Options_Sound,SHOW);
		reset(OptionsSoundTxt,SHOW);
		
	}
	
	reset(Options_Themes,SHOW);
	
	set(Options_Maintenance,SHOW);
	
	
	
}

/*
--------------------------------------------------
void GOptions_SaveSettings()


--------------------------------------------------
*/
void GOptions_SaveSettings() {
	
	if(event_type == EVENT_RELEASE) return;
	
	//	int temporary_BitDepth;
	
	if(is(Options_Graphics,SHOW)) {
		
		// Compare the third pstring for bit depth
		if(str_cmp((OptionsGraphicsTxt.pstring)[2],"16-bit")) video_set(0,0,16,0);
		else video_set(0,0,32,0);
		
		if( str_cmp((OptionsGraphicsTxt.pstring)[0],"Full Screen") ) {
			
			// 'cause WIDTH and HEIGHT aren't defined globally
			// just for testing when loading the kernel
			// so sys_metrics is directly used here.
			
			// depth always 0  
			video_set(sys_metrics(0),sys_metrics(1),0,1);
			
		}
		else video_set(sys_metrics(0),sys_metrics(1),0,2);
		
		// Check for wide screen, gamma, fsaa, aa and so.
		if( str_cmp((OptionsGraphicsTxt.pstring)[1],"4:3") ) video_aspect = 4/3;
		else if(str_cmp((OptionsGraphicsTxt.pstring)[1],"16:9")) video_aspect = 16/9;
		else video_aspect = 16/10;
		
		video_gamma = str_to_num( (OptionsGraphicsTxt.pstring) [3] );
		d3d_antialias = str_to_num( (OptionsGraphicsTxt.pstring) [4] );
		d3d_anisotropy = str_to_num( (OptionsGraphicsTxt.pstring) [5] );
		
		GOptionsHide();
		
		return;
		
	}

	if(is(Options_Sound,SHOW)) {
		
		VOL_MUSIC = str_to_num( (OptionsSoundTxt.pstring) [0] );
		VOL_EFFECTS = str_to_num( (OptionsSoundTxt.pstring) [1] );
		doppler_factor = str_to_num( (OptionsSoundTxt.pstring) [2] );
		
		GOptionsHide();
		
		return;
		
	}

	if(is(Options_Themes,SHOW)) {
		
		GOptionsHide();
		
		return;
		
	}

	if(is(Options_Maintenance,SHOW)) {
		
		GOptionsHide();
		
		return;
		
	}
	
}

/*
--------------------------------------------------
void GOptionsAdjustSettings(var ID)


--------------------------------------------------
*/
void GOptionsAdjustSettings(var ID) {
	
	if(event_type == EVENT_RELEASE) return;
	
	if(is(Options_Graphics,SHOW)) {
		
		ID = (int)ID; // Well, I have nothing to say...
		
		switch(ID) {
			
			case 1: case 2: // Full screen <-> Windowed
			
			if( str_cmp((OptionsGraphicsTxt.pstring)[0],"Full Screen") ) str_cpy((OptionsGraphicsTxt.pstring)[0],str_create("Windowed"));
			else str_cpy((OptionsGraphicsTxt.pstring)[0],str_create("Full Screen"));
			
			break;
			
			case 3: case 4: // 4:3 <-> 16:10 <-> 16:9
			
			if( str_cmp((OptionsGraphicsTxt.pstring)[1],"4:3") ) str_cpy( (OptionsGraphicsTxt.pstring) [1] , str_create("16:9"));
			else if ( str_cmp((OptionsGraphicsTxt.pstring)[1],"16:9")) str_cpy( (OptionsGraphicsTxt.pstring) [1] , str_create("16:10"));
			else str_cpy( (OptionsGraphicsTxt.pstring) [1] , str_create("4:3"));
			
			break;
			
			case 5: case 6: // 16-bit color depth <-> 32-bit
			
			if( str_cmp((OptionsGraphicsTxt.pstring)[2],"16-bit") ) str_cpy( (OptionsGraphicsTxt.pstring) [2],str_create("32-bit"));
			else str_cpy( (OptionsGraphicsTxt.pstring) [2],str_create("16-bit"));
			
			break;
			
			case 7: // Brightness --
			
			int brightness = str_to_num( (OptionsGraphicsTxt.pstring) [3]);
			
			if(brightness <= 50) break;
			
			brightness-=5;
			
			str_for_num((OptionsGraphicsTxt.pstring)[3],brightness);
			
			break;
			
			case 8: // brightness ++
			
			int brightness = str_to_num( (OptionsGraphicsTxt.pstring) [3]);
			brightness+=5;
			
			if (brightness >= 150) break;
			
			str_for_num((OptionsGraphicsTxt.pstring)[3],brightness);
			
			break;
			
			case 9: // fsaa --
			
			int fsaa = str_to_num( (OptionsGraphicsTxt.pstring) [4]);
			
			if(fsaa <= 0) break;
			
			fsaa--;
			
			str_for_num((OptionsGraphicsTxt.pstring)[4],fsaa);
			
			break;
			
			case 10: // fsaa ++ 
			
			int fsaa = str_to_num( (OptionsGraphicsTxt.pstring) [4]);
			
			if(fsaa >= 9) break;
			fsaa++;
			
			str_for_num((OptionsGraphicsTxt.pstring)[4],fsaa);
			
			break;
			
			case 11: // af --
			
			int af = str_to_num( (OptionsGraphicsTxt.pstring) [5]);
			
			if(af <= 0) break;
			af--;
			
			str_for_num((OptionsGraphicsTxt.pstring)[5],af);
			
			break;
			
			case 12: // af ++ 
			
			int af = str_to_num( (OptionsGraphicsTxt.pstring) [5]);
			
			if(af >= 7) break;
			af++;
			
			str_for_num((OptionsGraphicsTxt.pstring)[5],af);
			
			break;
			
		}	
		
		return ;
		
	}
	
	if(is(Options_Sound,SHOW)) {
		
		switch(ID) {
			
			case 1: // Music volume --
			
			var mv = str_to_num((OptionsSoundTxt.pstring)[0]);
			if(mv <= 0) break;
			mv-=5;
			
			str_for_num((OptionsSoundTxt.pstring)[0],mv);
			
			break;
			
			case 2: // Music volume ++
			
			var mv = str_to_num((OptionsSoundTxt.pstring)[0]);
			if(mv >= 100) break;
			mv+=5;
			
			str_for_num((OptionsSoundTxt.pstring)[0],mv);
			
			break;
			
			case 3: // Sound volume -- 
			
			var sv = str_to_num((OptionsSoundTxt.pstring)[1]);
			if(sv <= 0) break;
			sv-=5;
			
			str_for_num((OptionsSoundTxt.pstring)[1],sv);
			
			break;
			
			case 4: // Sound volume ++ 
			
			var sv = str_to_num((OptionsSoundTxt.pstring)[1]);
			if(sv >= 100) break;
			sv+=5;
			
			str_for_num((OptionsSoundTxt.pstring)[1],sv);
			
			break;
			
			case 5: // Doppler --
			
			int doppler = str_to_num((OptionsSoundTxt.pstring)[2]);
			if(doppler <= 0) break;
			doppler--;
			
			str_for_num((OptionsSoundTxt.pstring)[2],doppler);
			
			break;
			
			case 6: // Doppler ++
			
			int doppler = str_to_num((OptionsSoundTxt.pstring)[2]);
			if(doppler >= 10) break;
			doppler++;
			
			str_for_num((OptionsSoundTxt.pstring)[2],doppler);
			
			break;
			
		}
		
		return;
		
	}
	
}

/*
--------------------------------------------------
void GLoadGame_Scroll(var nothing, PANEL *launcher)


--------------------------------------------------
*/
void GLoadGame_Scroll(var nothing, PANEL *launcher) {
	
	if(event_type == EVENT_RELEASE) return;
	
	if(launcher == LoadGame_Uppart /*&& 
	LoadGameInside.pos_y > bmap_height(LoadGame_Uppart.bmap)*/ ) 
	
	LoadGameInside.pos_y += 50;
	
	else if(launcher == LoadGame_Downpart /*&&
	LoadGameInside.pos_y <= screen_size.y - bmap_height(LoadGameInside.bmap)*/)
	
	LoadGameInside.pos_y -= 50;
	
}

void GLoadGameShow() {
	
	if(event_type == EVENT_RELEASE) return;
	
	GOptionsHide();
	
	set(LoadGame_Uppart,SHOW);
	set(LoadGame_Downpart,SHOW);
	
	set(LoadGameInside,SHOW);
	
	wait(1);
	
}

void GLoadGameHide() {
	
	reset(LoadGame_Uppart,SHOW);
	reset(LoadGame_Downpart,SHOW);
	
	reset(LoadGameInside,SHOW);
	
	wait(1);
	
}
