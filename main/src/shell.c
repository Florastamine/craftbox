/*
--------------------------------------------------
shell.c

Contains GUI/HUD code.

Written by Nguyen Ngoc Huy
https://github.com/ngochuy2101
http://craftboxdev.blogspot.com/

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
Just plug additional code to head.h and shell.c, modify InsertParticle and 
GSelectParticle a bit, and run - more particle effects.

+ Sound effects for
- Menu (hover, click)

>+++
--------------------------------------------------
*/

PANEL *seedPanelCover = {
	
	bmap = "c07_d.png";
	layer = 10;
	
	button(15,15,"button_startseed.png","button_startseed.png","button_startseed.png",NULL,PerformSeed,NULL);
	button(15,50,"button_editseedmap.png","button_editseedmap.png","button_editseedmap.png",NULL,RecreateSeedMap,NULL);
	button(15,85,"button_selectseedent.png","button_selectseedent.png","button_selectseedent.png",NULL,SeedEntSelector,NULL);
	button(15,120,"button_deleteseedents.png","button_deleteseedents.png","button_deleteseedents.png",NULL,RemoveSeedEnts,NULL);
	
	pos_x = 0;
	pos_y = 0;
	
	flags = OVERLAY;

}

PANEL* canvas_pan = // contains the bitmap that will be written on
{
	
	layer = 15;
	pos_x = 0;
	pos_y = 0;
	
}

PANEL *BackMenu_Items = {
	
	layer = 21;
	bmap = "BackMenu_Item_Background.bmp";
	
	button(0,0,"BackMenu_Item1_on.png","BackMenu_Item1.png","BackMenu_Item1_on.png",NULL,GBackMenuHide,NULL);
	button(0,40,"BackMenu_Item2_on.png","BackMenu_Item2.png","BackMenu_Item2_on.png",NULL,NULL,NULL);
	button(0,80,"BackMenu_Item3_on.png","BackMenu_Item3.png","BackMenu_Item3_on.png",NULL,NULL,NULL);
	button(0,120,"BackMenu_Item4_on.png","BackMenu_Item4.png","BackMenu_Item4_on.png",NULL,NULL,NULL);
	button(0,160,"BackMenu_Item5_on.png","BackMenu_Item5.png","BackMenu_Item5_on.png",NULL,NULL,NULL);
	button(0,200,"BackMenu_Item6_on.png","BackMenu_Item6.png","BackMenu_Item6_on.png",NULL,NULL,NULL);
	
	pos_x = 50;
	pos_y = 50;
	
	flags = OVERLAY;
	
}


PANEL *BackMenu_Background = {
	
	layer = 20;
	
	bmap = "BackMenu_Background.png";
	
	flags = OVERLAY | TRANSLUCENT;
	
	alpha = 50;
	
}

PANEL *TerrainToolbar = {
	
	layer = 10;
	
	bmap = "TerrainToolbar.png";
	
	//	button(10,10,"terrain_brush_raise.png","terrain_brush_raise.png","terrain_brush_raise.png",NULL,TDeform_changeBrushRaise,NULL);
	//	button(74,10,"terrain_brush_lower.png","terrain_brush_lower.png","terrain_brush_lower.png",NULL,TDeform_changeBrushLower,NULL);
	
	button_toggle(10,10,"terrain_brush_raise_on.png","terrain_brush_raise.png","terrain_brush_raise_on.png","terrain_brush_raise_on.png",NULL,TDeform_changeBrushRaise,NULL);
	button_toggle(74,10,"terrain_brush_raise_on.png","terrain_brush_raise.png","terrain_brush_raise_on.png","terrain_brush_raise_on.png",NULL,TDeform_changeBrushLower,NULL);
	
	button(138,10,"load_upload.png""load_upload.png","load_upload.png",NULL,GTerrainSaveGeoWrapper,NULL);
	button(202,10,"load_download.png","load_download.png","load_download.png",NULL,GTerrainLoadGeoWrapper,NULL);
	
	hslider(289,34,155,"slider.bmp",500,5000,bSize);
	hslider(289,72,155,"slider.bmp",5,25,brush_speed);
	//	
	//	pos_x = 10;
	//	pos_y = 10;
	
	//   flags = SHOW;
	
	on_click = GPanelDrag;
	
}

PANEL *pLoadBar = {
	
	layer = 999;
	pos_x = 0;
	
	// Purple mountain majesty sRGBB  (r, g, b)	(150, 120, 182)
	red = 150;
	green = 120;
	blue = 182;
	
}

PANEL *InDev = {
	
	layer = 999;
	
	bmap = "InDev.png";
	button(170,184,"InDev_Close.png","InDev_Close.png","InDev_Close.png",NULL,GInDevHide,GSEMenuMouseHover);
	
}

PANEL *Playtest_Loadscreen = {
	
	layer = 100;
	
	
}

PANEL *Blackboard = {
	
	layer = 25;
	
	bmap = "notificationGround.bmp";
	button(0,0,"notification.bmp","notification.bmp","notification.bmp",NULL,GBlackboardAlphaRestore,GBlackboardAlphaFade);
	
	flags = TRANSLUCENT;
	
}

PANEL *Stats = {
	
	layer = 1;
	
	bmap = "Stats.png";
	flags = OVERLAY | TRANSLUCENT;
	alpha = 50;
	
	button(261,251,"button_stats_off.png","button_stats_off.png","button_stats_off.png",NULL,GToggleStatistics,NULL);
	
	on_click = GPanelDrag;
	
}

PANEL *MusicPlayer = {
	
	layer = 15;
	
	bmap = "MusicPlayerInterface.png";
	
	button(0,0,"mp_media_previous.png","mp_media_previous.png","mp_media_previous.png",NULL,mpPrev,NULL);
	button(138,0,"mp_media_pause.png","mp_media_pause.png","mp_media_pause.png",NULL,mpPause,NULL);
	button(276,0,"mp_media_play.png","mp_media_play.png","mp_media_play.png",NULL,mpResume,NULL);
	button(414,0,"mp_media_next.png","mp_media_next.png","mp_media_next.png",NULL,mpNext,NULL);
	button_toggle(336,156,"Musicplayer_checkbox_random_on.png","Musicplayer_checkbox_random_off.png","Musicplayer_checkbox_random_on.png","Musicplayer_checkbox_random_on.png",NULL,GToggleMusicPlayerRandomize,GSEMenuMouseHover);
	
	flags = OVERLAY;
	
	on_click = GPanelDrag;
	
}

TEXT *MusicPlayerInfo = {
	
	layer = 20;
	
	strings(2);
	string(_mpSongTemp,_mpCount);
	
	font = "Arial#20b";
	
	//	flags = SHOW;
	
}

PANEL *FPCrosshair = {
	
	layer = 15;
	bmap = "crosshair.png";
	
	flags = OVERLAY;
	
}

PANEL *CreateWorld = {
	
	layer = 998;
	bmap = "white.bmp";
	
	flags = TRANSLUCENT;
	alpha = 100;
	
}

PANEL *CreateWorldCoffee = {
	
	layer = 999;
	bmap = "coffee_badge.png";
	
}

PANEL *NewGame_PreviewButton = {
	
	bmap = "button_PreviewScene_off.png";
	button(0,0,"button_PreviewScene_on.png","button_PreviewScene_off.png","button_PreviewScene_on.png",NULL,GNewGame_UnPreviewScene,GNewGame_PreviewScene);
	
	//	flags = SHOW;
	
}


PANEL *NewGame_ScreenLeft = {
	
	layer = 2;
	
	button(0,0,"arrow_left.png","arrow_left.png","arrow_left.png",NULL,GSwitchNewGameScreen,NULL);
	button(0,0,"black.bmp","black.bmp","black.bmp",NULL,NULL,NULL);
	
	flags = OVERLAY;
	
}

PANEL *NewGame_ScreenRight = {
	
	layer = 2;
	
	button(0,0,"black.bmp","black.bmp","black.bmp",NULL,NULL,NULL);
	button(0,0,"arrow_right.png","arrow_right.png","arrow_right.png",NULL,GSwitchNewGameScreen,NULL);
	
	flags = OVERLAY;
	
}

PANEL *NewGame_Screen1 = {
	
	bmap = "NewGame_Screen1.bmp";
	flags =  TRANSLUCENT;
	alpha = 75;
	
	button(121,345,"button_NewGame_Screen.bmp","button_NewGame_Screen.bmp","button_NewGame_Screen.bmp",NULL,GNewGame_ChooseWorld,NULL);
	button(517,345,"button_NewGame_Screen.bmp","button_NewGame_Screen.bmp","button_NewGame_Screen.bmp",NULL,GNewGame_ChooseWorld,NULL);
	
}

PANEL *NewGame_ScreenDyn_Step1 = {
	
	bmap = "NewGame_ScreenDyn_Step1.bmp";
	
	button_toggle(30,96,"NewGame_Checkbox_Lensflare_On.bmp","NewGame_Checkbox_Lensflare_Off.bmp","NewGame_Checkbox_Lensflare_On.bmp","NewGame_Checkbox_Lensflare_On.bmp",GSEMenuMouseClick,NULL,NULL);
	button_toggle(30,126,"NewGame_Checkbox_Sun_On.bmp","NewGame_Checkbox_Sun_Off.bmp","NewGame_Checkbox_Sun_On.bmp","NewGame_Checkbox_Sun_On.bmp",GSEMenuMouseClick,NULL,NULL);
	button_toggle(30,156,"NewGame_Checkbox_Moon_On.bmp","NewGame_Checkbox_Moon_Off.bmp","NewGame_Checkbox_Moon_On.bmp","NewGame_Checkbox_Moon_On.bmp",GSEMenuMouseClick,NULL,NULL);
	button_toggle(30,186,"NewGame_Checkbox_Stars_On.bmp","NewGame_Checkbox_Stars_Off.bmp","NewGame_Checkbox_Stars_On.bmp","NewGame_Checkbox_Stars_On.bmp",GSEMenuMouseClick,NULL,NULL);
	
	button_radio(36,250."NewGame_Radiobox_Rain_On.bmp","NewGame_Radiobox_Rain_Off.bmp","NewGame_Radiobox_Rain_On.bmp",GSEMenuMouseClick,GWeatherMode_RainOnly,NULL);
	button_radio(36,280,"NewGame_Radiobox_Snow_On.bmp","NewGame_Radiobox_Snow_Off.bmp","NewGame_Radiobox_Snow_On.bmp",GSEMenuMouseClick,GWeatherMode_SnowOnly,NULL);
	button_radio(36,310,"NewGame_Radiobox_Both_On.bmp","NewGame_Radiobox_Both_Off.bmp","NewGame_Radiobox_Both_On.bmp",GSEMenuMouseClick,GWeatherMode_RainSnow,NULL);
	button_radio(36,340,"NewGame_Radiobox_Nothing_On.bmp","NewGame_Radiobox_Nothing_Off.bmp","NewGame_Radiobox_Nothing_On.bmp",GSEMenuMouseClick,GWeatherMode_Nothing,NULL);
	
	hslider(503,115,274,"SliderKnob.bmp",0,150,_time_speed); // [0..150]
	hslider(503,164,274,"SliderKnob.bmp",0,150,_time_speed_night); // [0..150]
	hslider(503,215,274,"SliderKnob.bmp",2.5,40,_moon_scale_fac); // [2,5..40]
	hslider(503,263,274,"SliderKnob.bmp",0.5,5,_night_sky_scale_x); // [0,5..5]
	hslider(503,318,274,"SliderKnob.bmp",0,200,_night_sky_speed_x); // [0..200]
	
	flags =  TRANSLUCENT;
	
	alpha = 75;
}

PANEL *NewGame_ScreenStatic_Step1 = {
	
	bmap = "NewGame_ScreenStatic_Step1.bmp";
	
	hslider(323,107,271,"SliderKnob.bmp",-200,300,_sun_light); // actually I found sun_light ranged from -200 to 200+
	button_toggle(37,166,"NewGame_Checkbox_Fog_On.bmp","NewGame_Checkbox_Fog_Off.bmp","NewGame_Checkbox_Fog_On.bmp","NewGame_Checkbox_Fog_On.bmp",GSEMenuMouseClick,NULL,NULL);
	
	hslider(283,255,271,"SliderKnob.bmp",0,255,_d3d_fogcolor1_red);
	hslider(283,291,271,"SliderKnob.bmp",0,255,_d3d_fogcolor1_blue);
	hslider(283,329,271,"SliderKnob.bmp",0,255,_d3d_fogcolor1_green);
	hslider(283,370,271,"SliderKnob.bmp",100,50000,_camera_fog_end);
	
	flags = TRANSLUCENT;
	alpha = 75;
	
}

PANEL *NewGame_Screen3 = {
	
	bmap = "NewGame_Screen3.bmp";
	
	button(661,354,"button_Start_on.png","button_Start_off.png","button_Start_on.png",NULL,LaunchGameSession,GSEMenuMouseHover);
	
	flags = TRANSLUCENT;
	alpha = 75;
	
}

PANEL *MainMenu_Bar = {
	
	layer = 1;
	
	bmap = "bar.tga";
	
	pos_x = 0;
	pos_y = 0;
	
	flags = TRANSLUCENT | SHOW;
	
	alpha = 75;
	
}


PANEL *ZTool = {
	
	layer = 6;
	
	bmap = "z_tool.bmp";
	
	pos_x = 200;
	pos_y = 10;
	
	vslider(10,10,300,"slider.bmp",-3000,4000,v_objectz);
	
	on_click = GPanelDrag;
	
}

PANEL *LoadGame = {
	
	layer = 1;
	
	bmap = "LoadGame.bmp";
	
}

// C++'s inheritance is needed here DUDE!

PANEL *Options_Graphics = {
	
	layer = 4;
	
	bmap = "Options_Graphics.bmp";
	
	//
	button(241,81,"arrow_left.png","arrow_left.png","arrow_left.png",NULL,GOptionsAdjustSettings,NULL);
	button(400,81,"arrow_right.png","arrow_right.png","arrow_right.png",NULL,GOptionsAdjustSettings,NULL);
	
	button(241,111,"arrow_left.png","arrow_left.png","arrow_left.png",NULL,GOptionsAdjustSettings,NULL);
	button(400,111,"arrow_right.png","arrow_right.png","arrow_right.png",NULL,GOptionsAdjustSettings,NULL);
	
	button(241,141,"arrow_left.png","arrow_left.png","arrow_left.png",NULL,GOptionsAdjustSettings,NULL);
	button(400,141,"arrow_right.png","arrow_right.png","arrow_right.png",NULL,GOptionsAdjustSettings,NULL);
	
	button(241,171,"arrow_left.png","arrow_left.png","arrow_left.png",NULL,GOptionsAdjustSettings,NULL);
	button(400,171,"arrow_right.png","arrow_right.png","arrow_right.png",NULL,GOptionsAdjustSettings,NULL);
	
	button(241,201,"arrow_left.png","arrow_left.png","arrow_left.png",NULL,GOptionsAdjustSettings,NULL);
	button(400,201,"arrow_right.png","arrow_right.png","arrow_right.png",NULL,GOptionsAdjustSettings,NULL);
	
	button_toggle(30,269,"Options_checkbox_SSAO_on.bmp","Options_checkbox_SSAO_off.bmp","Options_checkbox_SSAO_on.bmp","Options_checkbox_SSAO_on.bmp",NULL,GInDevShow,NULL);
	button_toggle(30,300,"Options_checkbox_HDR_on.bmp","Options_checkbox_HDR_off.bmp","Options_checkbox_HDR_on.bmp","Options_checkbox_HDR_on.bmp",NULL,GInDevShow,NULL);
	button_toggle(250,269,"Options_checkbox_DoF_on.bmp","Options_checkbox_DoF_off.bmp","Options_checkbox_DoF_on.bmp","Options_checkbox_DoF_on.bmp",NULL,GInDevShow,NULL);
	
	//	button(241,231,"arrow_left.png","arrow_left.png","arrow_left.png",GOptionsAdjustSettings,NULL,NULL);
	//	button(400,231,"arrow_right.png","arrow_right.png","arrow_right.png",GOptionsAdjustSettings,NULL,NULL);
	//	
	
	//
	button(216,8,"button_Options_Graphics_on.png","button_Options_Graphics.png","button_Options_Graphics_on.png",NULL,GOptions_Graphics,GSEMenuMouseHover);
	button(316,8,"button_Options_Sound_on.png","button_Options_Sound.png","button_Options_Sound_on.png",NULL,GOptions_Sound,GSEMenuMouseHover);
	button(450,8,"button_Options_Themes_on.png","button_Options_Themes.png","button_Options_Themes_on.png",NULL,GOptions_Themes,GSEMenuMouseHover);
	button(555,8,"button_Options_Maintenance_on.png","button_Options_Maintenance.png","button_Options_Maintenance_on.png",NULL,GOptions_Maintenance,GSEMenuMouseHover);
	
	button(24,349,"button_Options_Back_on.png","button_Options_Back.png","button_Options_Back_on.png",NULL,GOptions_SaveSettings,GSEMenuMouseHover);
	
	flags = TRANSLUCENT;
	
	alpha = 80;
	
	//	on_click = GPanelDrag;
	
}

PANEL *Options_Sound = {
	
	layer = 4;
	
	bmap = "Options_Sound.bmp";
	
	//
	button(241,81,"arrow_left.png","arrow_left.png","arrow_left.png",NULL,GOptionsAdjustSettings,NULL);
	button(400,81,"arrow_right.png","arrow_right.png","arrow_right.png",NULL,GOptionsAdjustSettings,NULL);
	
	button(241,111,"arrow_left.png","arrow_left.png","arrow_left.png",NULL,GOptionsAdjustSettings,NULL);
	button(400,111,"arrow_right.png","arrow_right.png","arrow_right.png",NULL,GOptionsAdjustSettings,NULL);
	
	button(241,141,"arrow_left.png","arrow_left.png","arrow_left.png",NULL,GOptionsAdjustSettings,NULL);
	button(400,141,"arrow_right.png","arrow_right.png","arrow_right.png",NULL,GOptionsAdjustSettings,NULL);
	
	//
	button(216,8,"button_Options_Graphics_on.png","button_Options_Graphics.png","button_Options_Graphics_on.png",NULL,GOptions_Graphics,GSEMenuMouseHover);
	button(316,8,"button_Options_Sound_on.png","button_Options_Sound.png","button_Options_Sound_on.png",NULL,GOptions_Sound,GSEMenuMouseHover);
	button(450,8,"button_Options_Themes_on.png","button_Options_Themes.png","button_Options_Themes_on.png",NULL,GOptions_Themes,GSEMenuMouseHover);
	button(555,8,"button_Options_Maintenance_on.png","button_Options_Maintenance.png","button_Options_Maintenance_on.png",NULL,GOptions_Maintenance,GSEMenuMouseHover);
	
	button(24,349,"button_Options_Back_on.png","button_Options_Back.png","button_Options_Back_on.png",NULL,GOptions_SaveSettings,GSEMenuMouseHover);
	
	flags = TRANSLUCENT;
	
	alpha = 80;
	
}

PANEL *Options_Themes = {
	
	layer = 4;
	
	bmap = "Options_Themes.bmp";
	
	button(216,8,"button_Options_Graphics_on.png","button_Options_Graphics.png","button_Options_Graphics_on.png",NULL,GOptions_Graphics,GSEMenuMouseHover);
	button(316,8,"button_Options_Sound_on.png","button_Options_Sound.png","button_Options_Sound_on.png",NULL,GOptions_Sound,GSEMenuMouseHover);
	button(450,8,"button_Options_Themes_on.png","button_Options_Themes.png","button_Options_Themes_on.png",NULL,GOptions_Themes,GSEMenuMouseHover);
	button(555,8,"button_Options_Maintenance_on.png","button_Options_Maintenance.png","button_Options_Maintenance_on.png",NULL,GOptions_Maintenance,GSEMenuMouseHover);
	
	button(24,349,"button_Options_Back_on.png","button_Options_Back.png","button_Options_Back_on.png",NULL,GOptions_SaveSettings,GSEMenuMouseHover);
	
	flags = TRANSLUCENT;
	
	alpha = 80;
	
}

PANEL *Options_Maintenance = {
	
	layer = 4;
	
	bmap = "Options_Maintenance.bmp";
	
	button(216,8,"button_Options_Graphics_on.png","button_Options_Graphics.png","button_Options_Graphics_on.png",NULL,GOptions_Graphics,GSEMenuMouseHover);
	button(316,8,"button_Options_Sound_on.png","button_Options_Sound.png","button_Options_Sound_on.png",NULL,GOptions_Sound,GSEMenuMouseHover);
	button(450,8,"button_Options_Themes_on.png","button_Options_Themes.png","button_Options_Themes_on.png",NULL,GOptions_Themes,GSEMenuMouseHover);
	button(555,8,"button_Options_Maintenance_on.png","button_Options_Maintenance.png","button_Options_Maintenance_on.png",NULL,GOptions_Maintenance,GSEMenuMouseHover);
	
	button(24,349,"button_Options_Back_on.png","button_Options_Back.png","button_Options_Back_on.png",NULL,GOptions_SaveSettings,GSEMenuMouseHover);
	
	flags = TRANSLUCENT;
	
	alpha = 80;
	
}

PANEL *BackgroundScreen = {
	
	layer = 10;
	
	bmap = BackgroundScreen1;
	
}

PANEL *InputBox_GROUNDSTR = {
	
	/*
	
	EVENT_RELEASE and EVENT_BUTTONUP can be used to distinguish whether functionOff was triggered by leaving the button area 
	or releasing the mouse button. EVENT_CLICK and EVENT_CLICKUP can be used to distinguish whether the mouse click switches the toggle button on or off. 
	
	*/
	
	layer = 10;
	
	bmap = "InputPalette_4.bmp";
	
	button(0,0,"InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp",NULL,PassToLOADGAMESTR,NULL);
	button(0,27,"InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp",NULL,PassToGROUNDSTR,NULL);
	button(0,54,"InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp",NULL,PassToGROUNDSTR,NULL);
	button(0,81,"InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp",NULL,PassToGROUNDSTR,NULL);
	
	button(247,0,"sort_up.png","sort_up.png","sort_up.png",NULL,GGROUNDSTR_Up,NULL);
	button(247,76,"sort_down.png","sort_down.png","sort_down.png",NULL,GGROUNDSTR_Down,NULL);
	
	flags = OVERLAY | TRANSLUCENT;

	alpha = 50;
	
}

PANEL *InputBox_SKYSTR = {
	
	layer = 10;
	
	bmap = "InputPalette_4.bmp";
	
	button(0,0,"InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp",NULL,PassToSKYSTR,NULL);
	button(0,27,"InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp",NULL,PassToSKYSTR,NULL);
	button(0,54,"InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp",NULL,PassToSKYSTR,NULL);
	button(0,81,"InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp",NULL,PassToSKYSTR,NULL);
	
	button(247,0,"sort_up.png","sort_up.png","sort_up.png",NULL,GSKYSTR_Up,NULL);
	button(247,76,"sort_down.png","sort_down.png","sort_down.png",NULL,GSKYSTR_Down,NULL);
	
	flags = OVERLAY | TRANSLUCENT;

	alpha = 50;
	
}

PANEL *InputBox_LOADGAMESTR = {
	
	layer = 10;
	
	bmap = "InputPalette_8.bmp";
	
	button(0,0,"InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp",NULL,PassToLOADGAMESTR,NULL);
	button(0,27,"InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp",NULL,PassToLOADGAMESTR,NULL);
	button(0,54,"InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp",NULL,PassToLOADGAMESTR,NULL);
	button(0,81,"InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp",NULL,PassToLOADGAMESTR,NULL);
	button(0,108,"InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp",NULL,PassToLOADGAMESTR,NULL);
	button(0,135,"InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp",NULL,PassToLOADGAMESTR,NULL);
	button(0,162,"InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp",NULL,PassToLOADGAMESTR,NULL);
	button(0,189,"InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp",NULL,PassToLOADGAMESTR,NULL);
	
	button(247,0,"sort_up.png","sort_up.png","sort_up.png",NULL,GLOADGAMESTR_Up,NULL);
	button(247,184,"sort_down.png","sort_down.png","sort_down.png",NULL,GLOADGAMESTR_Down,NULL);
	
	flags = OVERLAY | TRANSLUCENT;

	alpha = 50;
	
}


PANEL *InsertObject_Inputter = {
	
	/*
	
	EVENT_RELEASE and EVENT_BUTTONUP can be used to distinguish whether functionOff was triggered by leaving the button area 
	or releasing the mouse button. EVENT_CLICK and EVENT_CLICKUP can be used to distinguish whether the mouse click switches the toggle button on or off. 
	
	*/
	
	bmap = "InputPalette_20.bmp";
	
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
	button(0,510,"InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp",NULL,GSelectObject,NULL);
	button(0,540,"InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp",NULL,GSelectObject,NULL);
	button(0,570,"InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp","InsertObject_Inputter_Button.bmp",NULL,GSelectObject,NULL);
	
	button(247,0,"sort_up.png","sort_up.png","sort_up.png",NULL,GTEMPSTR_Up,NULL);
	button(247,565,"sort_down.png","sort_down.png","sort_down.png",NULL,GTEMPSTR_Down,NULL);

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
	
	button(0,0,"torreeiffel_up.png","torreeiffel_up.png","torreeiffel_up.png",NULL,GToggleTerrainEditor,NULL);
	button(0,0,"torreeiffel_down.png","torreeiffel_down.png","torreeiffel_down.png",NULL,GToggleObjectSeeder,NULL);
	//	button(0,0,menu1_submenu3,menu1_submenu3_off,menu1_submenu3_over,NULL,NULL,NULL);
	//	button(0,0,menu1_submenu4,menu1_submenu4_off,menu1_submenu4_over,NULL,NULL,NULL);
	
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
	button(113,123,"button_newworld_on.png","button_newworld_off.png","button_newworld_over.png",NULL,GWorldNewShow,NULL);
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
	
	button(0,0,"home.png","home.png","home.png",NULL,GBackMenuShow,NULL);
	button(0,0,"objects.png","objects.png","objects.png",NULL,GInsertObjectShow,NULL);
	button(0,0,"pathing.png","pathing.png","pathing.png",NULL,GTerrainSubmenuShow,NULL);
	//	button(0,0,"path_32.png","path_32.png","path_32.png",NULL,GPathSubmenuShow,NULL);
	
	
	flags = OVERLAY | SHOW;
}

PANEL *panMain_Play = {
	layer = 0;
	
	bmap = "panMain_Play.bmp";
	
	button(0,0,"v.png","button_ok.png","button_ok.png",NULL,LoadPlayground,NULL);
	
	flags = OVERLAY | SHOW;
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

PANEL *MainMenu_Item1 = {
	
	layer = 2;
	
	bmap = "button_NewGame_off.bmp";
	button(0,0,"button_NewGame_on.bmp","button_NewGame_off.bmp","button_NewGame_on.bmp",NULL,GWorldNewShow,GSEMenuMouseHover);
	
	flags = OVERLAY | TRANSLUCENT;
	
	alpha = 75;
	
}

PANEL *MainMenu_Item2 = {
	
	layer = 2;
	
	bmap = "button_LoadGame_off.bmp";
	button(0,0,"button_LoadGame_on.bmp","button_LoadGame_off.bmp","button_LoadGame_on.bmp",NULL,GLoadGameShow,GSEMenuMouseHover);

	flags = OVERLAY | TRANSLUCENT;

	alpha = 75;

}

PANEL *MainMenu_Item3 = {
	
	layer = 2;
	
	bmap = "button_Options_off.bmp";
	button(0,0,"button_Options_on.bmp","button_Options_off.bmp","button_Options_on.bmp",NULL,GOptionsShow,GSEMenuMouseHover);
	
	flags = OVERLAY | TRANSLUCENT;

	alpha = 75;

}

PANEL *MainMenu_Item4 = {
	
	layer = 2;
	
	bmap = "button_Achievements_off.bmp";
	button(0,0,"button_Achievements_on.bmp","button_Achievements_off.bmp","button_Achievements_on.bmp",NULL,GTrophiesShow,GSEMenuMouseHover);
	
	flags = OVERLAY | TRANSLUCENT;

	alpha = 75;

}

PANEL *MainMenu_Item5 = {
	
	layer = 2;
	
	bmap = "button_Credits_off.bmp";
	button(0,0,"button_Credits_on.bmp","button_Credits_off.bmp","button_Credits_on.bmp",NULL,GCreditsShow,GSEMenuMouseHover);
	
	flags = OVERLAY | TRANSLUCENT;

	alpha = 75;

}

PANEL *MainMenu_Item6 = {
	
	layer = 2;
	
	bmap = "button_Help_on.bmp";
	button(0,0,"button_Help_on.bmp","button_Help_off.bmp","button_Help_on.bmp",NULL,GHelpShow,GSEMenuMouseHover);
	
	flags = OVERLAY | TRANSLUCENT;
	
	alpha = 75;
	
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
// Particle effects or anything else related will be defined here.
//////////////////////////////////////////////////////////// 

void rain_event(PARTICLE* p) {
	if((p.x-camera.x)*cos(camera.pan) + (p.y-camera.y)*sin(camera.pan) + (p.z-camera.z)*sin(camera.tilt) < 0)p.lifespan = 0;
	p.skill_d = (p.skill_d + time_step*(var)1.000)%100;
}

void rain_base(PARTICLE* p) {
	p.size = random(0.867)+(2.133);
	p.alpha = random(18.265)+(40.735);
	p.red = 53;
	p.green = 80;
	p.blue = 106;
	p.skill_c = 0.5;
	parted_temp_vec.x = random(191.406)+208.594;
	parted_temp_vec.y = random(600.000)+-300.000;
	parted_temp_vec.z = 100.000;
	vec_rotate(parted_temp_vec,camera.pan);
	vec_add(p.x,parted_temp_vec);
	p.vel_x = random(0.799)+(-0.399);
	p.vel_y = random(0.799)+(-0.399);
	p.vel_z = (-3.000);
	p.lifespan = 40.000;
	p.gravity = 1.000;
	p.bmap = drop1_map;
	p.flags = BRIGHT | TRANSLUCENT | MOVE;
	p.skill_x = p.vel_x;
	p.skill_y = p.vel_y;
	p.skill_z = p.vel_z;
	p.event = rain_event;
}

/////////////////////////////////creation/////////////////////////////////

void rain(var wtoggle, var density) {
	
	proc_kill(4);
	
	if(wtoggle) {
		
		ToggleRain = 1;
		
		} else {
		
		ToggleRain = 0;
		return; 
		
	}
	
	var eff_frac = 0;
	
	while ( ToggleRain ) {
		
		vec_set(parted_temp_vec,nullvector);
		vec_add(parted_temp_vec,camera.x);
		eff_frac += 5*density*time_step*6.25;
		
		if(eff_frac >= 1) {
			
			effect(rain_base,integer(eff_frac),parted_temp_vec,nullvector);
			eff_frac -= integer(eff_frac);
			
		}
		
		wait(1);
		
	}
}

void snow(var wtoggle, var density, VECTOR *wind)
{
	proc_kill(4);	// terminate previous snow functions
	
	if( !KERNEL_IS_RUNNING ) return;
	if(!wtoggle) {
		
		ToggleSnow = 0;
		return;
		
	}
	else ToggleSnow = 1;
	
	if(!density) density = 2000;
	
	VECTOR camera_lastpos; // for determining the camera movement direction
	vec_set(camera_lastpos,camera.x);

	// store the wind speed locally
	if(!wind) wind = vector(-3,2,0);
	VECTOR wind_speed;
	vec_set(wind_speed,wind);

	var num_snow = 1;	// number of snow flakes per tick
	while(ToggleSnow)
	{
		
		// place snow origin slightly in camera movement direction		
		VECTOR snow_pos;
		vec_diff(snow_pos,camera.x,camera_lastpos);
		vec_set(camera_lastpos,camera.x);
		vec_scale(snow_pos,P_SNOWRANGE*0.2);
		vec_add(snow_pos,camera.x);
		// create snow flakes		
		effect(p_snow,num_snow*time_frame,snow_pos,wind_speed);
		// increase number of flakes until density is reached		
		num_snow = minv(density,num_snow+time_frame); 
		wait(1);
		
	}
}

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
	layer = 10; 
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
	layer = 4;
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
	layer = 6; 
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
	layer = 8;
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
	layer = 2;
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
	layer = 12;
	alpha = sun_alpha;
	flags2 = SKY;
	flags = TRANSLUCENT|PASSABLE|BRIGHT;
}

ENTITY *sky_suncorona =
{
	type = "sky_suncorona.tga";
	layer = 6;
	alpha = sun_corona_alpha;
	flags2 = SKY;
	flags = TRANSLUCENT|PASSABLE|BRIGHT;
}

ENTITY *sky_sunshine =
{
	type = "sky_sunshine.tga";
	layer = 14;
	alpha = sun_shine_alpha;
	flags2 = SKY;
	flags = TRANSLUCENT|PASSABLE|BRIGHT;
}

ENTITY *sky_night =
{ 
	type = "sky_night.tga";  
	layer = 2;
	alpha = 0;//night_sky_alpha; 
	flags2 = SKY|DOME; 
	flags = TRANSLUCENT|PASSABLE; 
} 

ENTITY *sky_moon =
{
	type = "sky_moon.tga";
	layer = 4;
	alpha = moon_alpha;
	flags2 = SKY;
	flags = TRANSLUCENT|PASSABLE;
}

ENTITY *flare1_ent =
{
	type = "lens_01.tga";
	layer = 16;
	view = camera;
	scale_x = 2;
	scale_y = 2;
}

ENTITY *flare2_ent =
{
	type = "lens_02.tga";
	layer = 16;
	view = camera;
	scale_x = 2;
	scale_y = 2;
}

ENTITY *flare4_ent =
{
	type = "lens_04.tga";
	layer = 16;
	view = camera;
	scale_x = 2;
	scale_y = 2;
}

ENTITY *flare5_ent =
{
	type = "lens_05.tga";
	layer = 16;
	view = camera;
	scale_x = 2;
	scale_y = 2;
}

ENTITY *flare6_ent =
{
	type = "lens_06.tga";
	layer = 16;
	view = camera;
	scale_x = 2;
	scale_y = 2;
}

ENTITY *flare7_ent =
{
	type = "lens_07.tga";
	layer = 16;
	view = camera;
	scale_x = 2;
	scale_y = 2;
}

ENTITY *flare8_ent =
{
	type = "lens_08.tga";
	view = camera;
	layer = 16;
	scale_x = 2;
	scale_y = 2;
}

ENTITY *flare9_ent =
{
	type = "lens_09.tga";
	view = camera;
	layer = 16;
	scale_x = 2;
	scale_y = 2;
}
ENTITY *flare10_ent =
{
	type = "lens_10.tga";
	view = camera;
	layer = 16;
	scale_x = 2;
	scale_y = 2;
}

ENTITY *flare11_ent =
{
	type = "lens_11.tga";
	layer = 16;
	view = camera;
	scale_x = 2;
	scale_y = 2;
}

ENTITY *flare12_ent =
{
	type = "lens_12.tga";
	layer = 16;
	view = camera;
	scale_x = 2;
	scale_y = 2;
}

ENTITY *flare13_ent =
{
	type = "lens_13.tga";
	layer = 16;
	view = camera;
	scale_x = 2;
	scale_y = 2;
}

ENTITY *flare14_ent =
{
	type = "lens_14.tga";
	layer = 16;
	view = camera;	
	scale_x = 2.5;
	scale_y = 2.5;
}

ENTITY *flare15_ent =
{
	type = "lens_15.tga";
	layer = 16;
	view = camera;
	scale_x = 2;
	scale_y = 2;
}

ENTITY *flare16_ent =
{
	type = "lens_16.tga";
	layer = 16;
	view = camera;
	scale_x = 2;
	scale_y = 2;
}

ENTITY *flare17_ent =
{
	type = "lens_17.tga";
	layer = 16;
	view = camera;
	scale_x = 2;
	scale_y = 2;
}

ENTITY *flare18_ent =
{
	type = "lens_18.tga";
	layer = 16;
	view = camera;
	scale_x = 2;
	scale_y = 2;
}

ENTITY *flare19_ent =
{
	type = "lens_19.tga";
	layer = 16;
	view = camera;
	scale_x = 2;
	scale_y = 2;
}

ENTITY *flare20_ent =
{
	type = "lens_20.tga";
	layer = 16;
	view = camera;
	scale_x = 2.8;
	scale_y = 2.8;
}

void GWeatherMode_RainOnly() { _weather_mode = RAIN_ONLY; }
void GWeatherMode_SnowOnly() { _weather_mode = SNOW_ONLY; }
void GWeatherMode_Nothing() { _weather_mode = NO_RAIN_SNOW; }
void GWeatherMode_RainSnow() { _weather_mode = RAIN_SNOW; }

/*
--------------------------------------------------
void GGUIUpdate(PANEL *wg)

Desc:

Returns: -
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
}

/* 
--------------------------------------------------
void GWindowClose(var id, PANEL *p)

Desc: id always = 1 cuz we don't have two closebuttons at the same time. 
only one PANEL * parameter isn't enough (and it won't work too) so 
this simple ugly hack should do the trick.

Returns: -
--------------------------------------------------
*/
void GWindowClose(var id, PANEL *p) {
	
	if(event_type == EVENT_RELEASE) return;
	
	id = 1;
	
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
	
}

/* 
--------------------------------------------------
void GGameLoad()

Desc:

Returns: -
--------------------------------------------------
*/
void GGameLoad() {
	
	if(event_type == EVENT_RELEASE) return;
	
}

/* 
--------------------------------------------------
void GGameSave()

Desc:

Returns: -
--------------------------------------------------
*/
void GGameSave() {
	
	if(event_type == EVENT_RELEASE) return;
	
}

/* 
--------------------------------------------------
void GGPanelDrag(PANEL *p)

Desc:

If you have two panels that is attached to each other, with one 
(or both) is draggable, then make sure to update their positions 
after the while(mouse_left) loop.

Returns: -
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
		
		wait(1);
	}

	//hack to prevent something happens. f.e. after dragged the guis' elements didn't retain their original location.
	if(p == panHome) GGUIUpdate(panHome);
	if(p == panProp) GGUIUpdate(panProp);
	
	if(p == Stats) {
		
		StatsPanel->pos_x = Stats->pos_x + 266;
		StatsPanel->pos_y = Stats->pos_y + 66;
		
		
	}
}

/*
--------------------------------------------------
void GPanelCenter(PANEL *p)

Desc:

Returns: -
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

Desc:

Returns: -
--------------------------------------------------
*/
void GPanelCenterInside(PANEL *p, PANEL *s) {
	while(p == NULL || s == NULL) wait(1);

	// peform a S comparison
	if(bmap_width(p.bmap)*bmap_height(p.bmap) > bmap_width(s.bmap)*bmap_height(s.bmap)) {
		
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

Desc:

Returns: -
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

Desc:

Returns: -
--------------------------------------------------
*/
void GPanelResize(PANEL *p, int c) {
	
	while(p == NULL) wait(1);
	
	switch(c) {
		
		case RESIZE_X: p.scale_x = sys_metrics(0)/bmap_width(p.bmap); break;
		case RESIZE_Y: p.scale_y = sys_metrics(1)/bmap_height(p.bmap); break;
		
		case RESIZE_XY:
		
		p.scale_x = sys_metrics(0)/bmap_width(p.bmap);
		p.scale_y = sys_metrics(1)/bmap_height(p.bmap);
		
		break;
		
	}
	
}

/*
--------------------------------------------------
void GPanelAlignMainMenu(PANEL *Panel)

Desc:

Returns: -
--------------------------------------------------
*/
void GPanelAlignMainMenu(PANEL *Panel) {
	
	while(!Panel) wait(1);
	
	Panel.pos_x = (sys_metrics(0) - bmap_width(Panel.bmap)) / 2;
	Panel.pos_y = sys_metrics(1)/4 + bmap_height(MainMenu_Bar.bmap) * MainMenu_Bar.scale_y + BORDER;
	
}


/* 
--------------------------------------------------
void GGUIInit()

Desc:

Returns: -
--------------------------------------------------
*/
void GGUIInit() {
	
	wait(2);
	
	GPanelResize(CreateWorld,RESIZE_XY);
	GPanelResize(seedPanelCover,RESIZE_XY);
	CreateWorldCoffee.pos_x = screen_size.x - bmap_width(CreateWorldCoffee.bmap) - BORDER * 2;
	CreateWorldCoffee.pos_y = screen_size.y - bmap_height(CreateWorldCoffee.bmap) - BORDER * 2;
	
	ReleaseInfo.pos_x = screen_size.x - str_width( (ReleaseInfo->pstring) [1], ReleaseInfo->font ) - BORDER * 2;
	ReleaseInfo.pos_y = screen_size.y - BORDER * 4;
	
	GPanelResize(panCAMRecorder,RESIZE_XY); // x+y-scale
	GPanelResize(panScreenshot,RESIZE_XY);
	GPanelResize(BackMenu_Background,RESIZE_XY);
	GPanelCenter(FPCrosshair);
	GPanelCenter(InDev);
	
	GPanelAlignMainMenu(NewGame_Screen1);
	GPanelAlignMainMenu(NewGame_ScreenDyn_Step1);
	GPanelAlignMainMenu(NewGame_ScreenStatic_Step1);
	GPanelAlignMainMenu(NewGame_Screen3);
	GPanelAlignMainMenu(Options_Graphics);
	GPanelAlignMainMenu(Options_Sound);
	GPanelAlignMainMenu(Options_Themes);
	GPanelAlignMainMenu(Options_Maintenance);
	GPanelAlignMainMenu(LoadGame);
	
	NewGame_ScreenLeft.pos_x = NewGame_Screen1.pos_x - NewGame_Screen1.pos_x/2;
	NewGame_ScreenLeft.pos_y = NewGame_Screen1.pos_y + bmap_width(NewGame_Screen1.bmap)/4;
	
	NewGame_ScreenRight.pos_x = NewGame_ScreenLeft.pos_x + bmap_width(NewGame_Screen1.bmap) + (NewGame_Screen1.pos_x - NewGame_ScreenLeft.pos_x);
	NewGame_ScreenRight.pos_y = NewGame_ScreenLeft.pos_y;
	
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
	
	/*
	
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
	
	*/
	
	MusicPlayer.pos_x = screen_size.x - bmap_width ( MusicPlayer.bmap ) - BORDER * 2;
	MusicPlayer.pos_y = screen_size.y - BORDER * 8 - bmap_height(MusicPlayer.bmap) ;
	
	TerrainToolbar.pos_y = screen_size.y - BORDER * 10 - bmap_height(TerrainToolbar.bmap);
	TerrainToolbar.pos_x = BORDER;
	
	ZTool.pos_x = screen_size.x - bmap_width(ZTool.bmap) - BORDER * 2;
	ZTool.pos_y = (screen_size.y - bmap_height(ZTool.bmap))/2;
	
	MainMenu_Bar.pos_x = 0;
	MainMenu_Bar.pos_y = screen_size.y/4;
	
	MainMenu_Bar.scale_x = sys_metrics(0)/bmap_width(MainMenu_Bar.bmap);
	MainMenu_Bar.scale_y = .5;
	
	MainMenu_Item1.pos_y  = MainMenu_Item2.pos_y = MainMenu_Item3.pos_y = MainMenu_Item4.pos_y = MainMenu_Item5.pos_y = MainMenu_Item6.pos_y = MainMenu_Bar.pos_y + BORDER/2;
	MainMenu_Item1.pos_x = BORDER;
	MainMenu_Item2.pos_x = MainMenu_Item1.pos_x + bmap_width(MainMenu_Item1.bmap) + BORDER;
	MainMenu_Item3.pos_x = MainMenu_Item2.pos_x + bmap_width(MainMenu_Item2.bmap) + BORDER;
	MainMenu_Item4.pos_x = MainMenu_Item3.pos_x + bmap_width(MainMenu_Item3.bmap) + BORDER;
	MainMenu_Item5.pos_x = MainMenu_Item4.pos_x + bmap_width(MainMenu_Item4.bmap) + BORDER;
	MainMenu_Item6.pos_x = MainMenu_Item5.pos_x + bmap_width(MainMenu_Item5.bmap) + BORDER;
	
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
	
	InputBox_GROUNDSTR.pos_x = NewGame_Screen3.pos_x + 45;
	InputBox_GROUNDSTR.pos_y = NewGame_Screen3.pos_y + 140;
	
	InputBox_SKYSTR.pos_x = NewGame_Screen3.pos_x + 450;
	InputBox_SKYSTR.pos_y = InputBox_GROUNDSTR.pos_y;
	
	InputBox_LOADGAMESTR.pos_x = LoadGame.pos_x + 35;
	InputBox_LOADGAMESTR.pos_y = LoadGame.pos_y + 110;
	
	files_list_SKYSTR.pos_x = InputBox_SKYSTR.pos_x;
	files_list_SKYSTR.pos_y = InputBox_SKYSTR.pos_y;
	
	files_list_GROUNDSTR.pos_x = InputBox_GROUNDSTR.pos_x;
	files_list_GROUNDSTR.pos_y = InputBox_GROUNDSTR.pos_y;
	
	files_list_LOADGAMESTR.pos_x = InputBox_LOADGAMESTR.pos_x;
	files_list_LOADGAMESTR.pos_y = InputBox_LOADGAMESTR.pos_y;
	
	NewGame_PreviewButton.pos_x = (screen_size.x - bmap_width(NewGame_PreviewButton.bmap))/2;
	NewGame_PreviewButton.pos_y = 50;
	
}

/* 
--------------------------------------------------
void GPanelSelect(PANEL *p)

Desc:

Returns: -
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

Desc:

Returns: -
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
void GToggleTerrainEditor()

Desc:

Returns: -
--------------------------------------------------
*/
void GToggleTerrainEditor() {
	
	if(event_type == EVENT_RELEASE) return;
	
	if( !is(TerrainToolbar,SHOW) ) {
		
		if(is(InsertObject, SHOW) ) GInsertObjectHide();
		
		set(TerrainToolbar,SHOW);
		TerrainEditMode = 1;
		
		button_state(TerrainToolbar,1,1);
		
		if(marker) Scale(marker, SCALE_MARKER_TERRAIN);
		
		
	}
	else {
		
		TerrainEditMode = 0;
		reset(TerrainToolbar,SHOW);
		
		if(marker) Scale(marker, SCALE_MARKER );
		////		
		////		if(mark) GInsertObjectShow();
		
		return;
		
	}
	
	while( TerrainEditMode ) {
		
		if(bSize<0) bSize=0;
		//		if(sizeh<0) sizeh=0;
		
		if(key_shift) bSize += mickey.z/20*50*time_step;
		//		if(key_ctrl) sizeh +=mickey.z/200*time_step;
		//		if(key_alt) tMaxHeight +=mickey.z/20*time_step;
		
		wait(1);
		
	}
	
}

/*
--------------------------------------------------
void GToggleObjectSeeder( )

Desc:

Returns: -
--------------------------------------------------
*/
void GToggleObjectSeeder( ) {
	
	if(event_type == EVENT_RELEASE) return;
	
	var old_from_test_play = from_test_play;
	int j = 0, k = -1;
	
	BMAP *olmouse_map = mouse_map;
	mouse_map = mouse_painttex;
	
	// Simple test to see if there's a mask before
	TEXT *simple = txt_create(100, 1);
	int i = txt_for_dir( simple ,"./2d/tex/*.tga");
	if( i ) {
		
		for(;j<i;j++) {
			
			if( str_stri( ( simple.pstring )[j], SEEDMASKDATA) ) {
				
				k = j;
				
				// found the right j, now load it
				canvas_paint = bmap_create ( (simple.pstring)[j] );
				while(proc_status(bmap_create) ) wait(1);
				
				canvas_pan.bmap = canvas_paint;
				
				GPanelCenter(canvas_pan);
				while(proc_status(GPanelCenter)) wait(1);
				canvas_pan->pos_y += 100;
				
				pan_setbutton(canvas_pan,0,0,0,0,canvas_paint,canvas_paint,canvas_paint,canvas_paint,paint_canvas,NULL,NULL);
				while(proc_status(pan_setbutton)) wait(1);
				
				set(canvas_pan, SHOW);
				set(seedPanelCover,SHOW);
				
				j=i+1; // Force the loop to exit
				
			}
			
		}
	}
	
	if( k != -1 && TerrainEnt ) { // The other case, I don't use !k here because...it could be 0, which can cause bug.
		
		bmap_savetga( ent_getskin(TerrainEnt,1), "tskin.tga");
		while( proc_status(bmap_savetga) ) wait(1);
		
		// canvas_paint = ent_getskin(TerrainEnt,1);
		canvas_paint = bmap_create("tskin.tga");
		canvas_pan.bmap = canvas_paint;
		//		GPanelResize(canvas_pan,RESIZE_XY); // <- It could cause bug
		GPanelCenter(canvas_pan);
		canvas_pan->pos_y += 100;
		
		pan_setbutton(canvas_pan,0,0,0,0,canvas_paint,canvas_paint,canvas_paint,canvas_paint,paint_canvas,NULL,NULL);
		set(canvas_pan, SHOW);
		set(seedPanelCover,SHOW);
		//		set(color_picker,SHOW);
		//		set(pencils_pan,SHOW);
		
	}
	
	while( is(canvas_pan,SHOW) ) {
		
		//		DEBUG_VAR(coords_x,10);
		//		DEBUG_VAR(coords_y,30);
		//		DEBUG_VAR(mouse_pos.x,50);
		//		DEBUG_VAR(mouse_pos.y,70);
		DEBUG_VAR(paint_outside,10);
		
		if(mouse_panel != canvas_pan) paint_outside = 1;
		else paint_outside = 0;

		coords_x = mouse_cursor.x - canvas_pan.pos_x;
		coords_y = mouse_cursor.y - canvas_pan.pos_y;
		
		while ( key_space ) {
		   
		   canvas_pan.pos_x = mouse_cursor.x - canvas_pan.pos_x;
		   canvas_pan.pos_y = mouse_cursor.y - canvas_pan.pos_y;
		   
		}
		
		if(key_esc) {
			
			while(key_esc) wait(1);
			
			if (canvas_modified) {
				
				from_test_play = 1; // fake this var
				
				str_cpy(TERRAINSEEDBMAP,TerrainEnt->type );
				str_cat(TERRAINSEEDBMAP,SEEDMASKDATA);
				str_cat(TERRAINSEEDBMAP,".tga"); // bmap_savetga
				
				bmap_savetga(canvas, TERRAINSEEDBMAP );
				while(proc_status ( bmap_savetga ) ) wait(1);
				
			}			
			
			break;

		}
		
		wait(1);
		
	}
	
	reset(canvas_pan,SHOW);
	reset(seedPanelCover,SHOW);
	mouse_map = olmouse_map;
	//	reset(color_picker,SHOW);
	//	reset(pencils_pan,SHOW);
	
	from_test_play = old_from_test_play;
}

/*
--------------------------------------------------
void GTerrainLoadGeoWrapper()

Desc:

Returns: -
--------------------------------------------------
*/
void GTerrainLoadGeoWrapper() {
	
	if(event_type == EVENT_RELEASE) return;
	
	TDeform_LoadHeightFrom(TerrainEnt);
	
}

/*
--------------------------------------------------
void GTerrainSaveGeoWrapper()

Desc:

Returns: -
--------------------------------------------------
*/
void GTerrainSaveGeoWrapper() {
	
	if(event_type == EVENT_RELEASE) return;
	
	TDeform_saveterrain(TerrainEnt);
	
}

/* 
--------------------------------------------------
void GObjectSubmenuShow()

Desc:

Returns: -
--------------------------------------------------
*/
void GObjectSubmenuShow() {
	
	if(event_type == EVENT_RELEASE) return;
	
	reset(buttonlst_submenu_terrain,SHOW);
	reset(buttonlst_submenu_path,SHOW);

	set(buttonlst_submenu_object,SHOW);
}

/* 
--------------------------------------------------
void GPathSubmenuShow()

Desc:

Returns: -
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

Desc:

Returns: -
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

Desc:

Returns: -
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

Desc:

Returns: -
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

Desc:

Returns: -
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

Desc:

Returns: -
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

Desc:

Returns: -
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

Desc:

Returns: -
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

Desc:

Returns: -
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
	
	reset(rt,SHOW);
	str_remove((rt.pstring)[0]);
	txt_remove(rt);
}

/*
--------------------------------------------------
void GCreditsShow()

Desc:

Returns: -
--------------------------------------------------
*/
void GCreditsShow() {
	
	if(event_type == EVENT_RELEASE) return;
	if(proc_status(GCreditsShow)) return;
	
	var rollspeed = .5;
	
	GSEMenuMouseClick();
	
	//	reset(panNewGame,SHOW);
	GWorldNewHide();
	GLoadGameHide();
	GOptionsHide();
	GHelpHide();
	GTrophiesHide();
	
	level_load(NULL);
	
	TEXT *import = txt_create(CREDITS_ROLL_MAXSTR,1);
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
	
	reset(import,SHOW);
	reset(end,SHOW);
	
	int i = 0;
	for(;i<CREDITS_ROLL_MAXSTR;i++) str_remove((import.pstring)[i]); txt_remove(import);
	str_remove((end.pstring)[0]); /* has 1 string only */ txt_remove(end);
	
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
void GMainMenuShow()

Desc:

Returns: -
--------------------------------------------------
*/
void GMainMenuShow() {
	
	set(MainMenu_Bar,SHOW);
	set(MainMenu_Item1,SHOW);
	set(MainMenu_Item2,SHOW);
	set(MainMenu_Item3,SHOW);
	set(MainMenu_Item4,SHOW);
	set(MainMenu_Item5,SHOW);
	set(MainMenu_Item6,SHOW);
	
	set(ReleaseInfo,SHOW);
	
	guiCurrentViewPreset = MENU_CAMERA_LAUNCH;
	
}

/*
--------------------------------------------------
void GMainMenuHide()

Desc:

Returns: -
--------------------------------------------------
*/
void GMainMenuHide() {
	
	reset(MainMenu_Bar,SHOW);
	reset(MainMenu_Item1,SHOW);
	reset(MainMenu_Item2,SHOW);
	reset(MainMenu_Item3,SHOW);
	reset(MainMenu_Item4,SHOW);
	reset(MainMenu_Item5,SHOW);
	reset(MainMenu_Item6,SHOW);
	
	reset(ReleaseInfo,SHOW);
	
}


/*
--------------------------------------------------
void GLoadMainMenu()

Desc:

Returns: -
--------------------------------------------------
*/
void GLoadMainMenu() {
	
	IN_GAME = 0;
	str_cpy(SKYSTR,undef);
	
	GGUIHide();
	GMainMenuShow();
	//	GPanelCenter(panMMenu);
	
	//	launch_newgame_from_main = 1;
	
//	level_load(LEVEL_MENU);
		level_load(NULL);
	//	game_load(pref_savebmaps,0);
	
	//	GPanelSelect(panMMenu);
	
	//	panMMenu.alpha = 50;
	
	guiViewPreset(&guiCurrentViewPreset, MENU_CAMERA_LAUNCH, MENU_CAMERA_LAUNCH_pos, MENU_CAMERA_LAUNCH_ang );
	guiViewPreset(&guiCurrentViewPreset, MENU_CAMERA_NEW_GAME, MENU_CAMERA_NEW_GAME_pos, MENU_CAMERA_NEW_GAME_ang );
	guiViewPreset(&guiCurrentViewPreset, MENU_CAMERA_LOAD_GAME, MENU_CAMERA_LOAD_GAME_pos, MENU_CAMERA_LOAD_GAME_ang );
	guiViewPreset(&guiCurrentViewPreset, MENU_CAMERA_HELP, MENU_CAMERA_HELP_pos, MENU_CAMERA_HELP_ang);
	guiViewPreset(&guiCurrentViewPreset, MENU_CAMERA_TROPHIES, MENU_CAMERA_TROPHIES_pos, MENU_CAMERA_TROPHIES_ang);
	guiViewPreset(&guiCurrentViewPreset, MENU_CAMERA_LAUNCH_GAME, MENU_CAMERA_LAUNCH_GAME_pos, MENU_CAMERA_LAUNCH_GAME_ang);
	guiViewPreset(&guiCurrentViewPreset, MENU_CAMERA_EXIT, MENU_CAMERA_EXIT_pos, MENU_CAMERA_EXIT_ang );
	
}

/*
--------------------------------------------------
void GOptionsShow()

Desc:

Returns: -
--------------------------------------------------
*/
void GOptionsShow() {
	
	if(event_type == EVENT_RELEASE) return;
	
	if(InMenu_Options) {
		
		GOptionsHide();
		
		return;
		
	}
	
	//	GSEMenuMouseClick();
	
	////	guiCurrentViewPreset = ;
	
	GWorldNewHide();
	GLoadGameHide();
	GHelpHide();
	GTrophiesHide();
	
	GOptions_Graphics();
	
	InMenu_Options = 1;
	
}

/*
--------------------------------------------------
void GOptionsHide()

Desc:

Returns: -
--------------------------------------------------
*/
void GOptionsHide() {
	
	if(is(Options_Graphics,SHOW)) {
		
		reset(Options_Graphics,SHOW);
		reset(OptionsGraphicsTxt,SHOW);
		
	}
	
	if(is(Options_Sound,SHOW)) {
		
		reset(Options_Sound,SHOW);
		reset(OptionsSoundTxt,SHOW);
		
	}
	
	if(is(Options_Themes,SHOW)) {
		
		reset(Options_Themes,SHOW);
		
	}
	
	if(is(Options_Maintenance,SHOW)) {
		
		reset(Options_Maintenance,SHOW);
		
	}
	
	InMenu_Options = 0;
	
	return;
	
}

/*
--------------------------------------------------
void GPropertiesWindowShow()

Desc:

Returns: -
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

Desc:

Returns: -
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

Desc:

Returns: -
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

Desc:

Returns: -
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

Desc:

Returns: -
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

Desc:

Returns: -
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

Desc:

Returns: -
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
	if(select.LightMode == Disco) button_state(panLight,2,1);
	if(select.LightMode == Flick) button_state(panLight,3,1);
	
}

/*
--------------------------------------------------
void GLightWindowHide()

Desc:

Returns: -
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
	
	if(button_state(panLight,2,-1)) select.LightMode = Disco;
	if(button_state(panLight,3,-1)) select.LightMode = Flick;
	
	reset(panLight,SHOW);
	
}

/* 
--------------------------------------------------
void GWorldNewShow()

Desc:

Returns: -
--------------------------------------------------
*/
void GWorldNewShow() {
	
	if(event_type == EVENT_RELEASE) return;
	
	if(InMenu_NewGame) {
		
		GWorldNewHide();
		
		return;
		
	}
	
	GSEMenuMouseClick();
	
	guiCurrentViewPreset = MENU_CAMERA_NEW_GAME;
	
	GLoadGameHide();
	GOptionsHide();
	GTrophiesHide();
	GHelpHide();
	
	//	set(NewGame_ScreenLeft,SHOW);
	//	set(NewGame_ScreenRight,SHOW);
	set(NewGame_Screen1,SHOW);
	
	// Set default values
	int i = 1;
	for(; i<5;i++) button_state(NewGame_ScreenDyn_Step1,i,1);
	
	InMenu_NewGame = 1;
	
	while(InMenu_NewGame) {
		
		if( is(NewGame_ScreenDyn_Step1,SHOW) || ( is(NewGame_Screen3,SHOW) && WorldType == WORLD_DYNAMIC) ) {
			
			moon_scale_fac = _moon_scale_fac;
			time_speed_night = _time_speed_night;
			night_sky_scale_x = _night_sky_scale_x;
			night_sky_speed_x = _night_sky_speed_x;
			time_speed = _time_speed;
			
			if(is(NewGame_ScreenDyn_Step1,SHOW)) {
				
				_load_lensflare = button_state(NewGame_ScreenDyn_Step1,1,-1);
				_use_sun = button_state(NewGame_ScreenDyn_Step1,2,-1);
				_use_moon = button_state(NewGame_ScreenDyn_Step1,3,-1);
				_use_nightstars = button_state(NewGame_ScreenDyn_Step1,4,-1);
				
			}	
			
		}
		
		if( is(NewGame_ScreenStatic_Step1,SHOW) || ( is(NewGame_Screen3,SHOW) && WorldType == WORLD_STATIC) ) {
			
			_fog_color = fog_color = button_state(NewGame_ScreenStatic_Step1,1,-1);
			sun_light = _sun_light;
			d3d_fogcolor1.red = _d3d_fogcolor1_red;
			d3d_fogcolor1.green = _d3d_fogcolor1_green;
			d3d_fogcolor1.blue = _d3d_fogcolor1_blue;
			camera.fog_end = _camera_fog_end;
			
			/*
			
			//		   Uncomment the following lines to get the variable fog effect ;)
			//		   the panel will update its values very slow though.
			
			d3d_fogcolor1.red = random(255); wait(-1);
			d3d_fogcolor1.green = random(255); wait(-1);
			d3d_fogcolor1.blue = random(255); wait(-1);
			
			*/
			
		}
		
		wait(1);
		
	}
	
	reset(NewGame_Screen1,SHOW);
	reset(NewGame_Screen3,SHOW);
	reset(NewGame_ScreenLeft,SHOW);
	reset(NewGame_ScreenRight,SHOW);
	reset(NewGame_ScreenStatic_Step1,SHOW);
	reset(NewGame_ScreenDyn_Step1,SHOW);
	reset(InputBox_GROUNDSTR,SHOW);
	reset(InputBox_SKYSTR,SHOW);
	
	/*
	
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
	
	*/
	
}

/*
--------------------------------------------------
void GNewGameResetDynamicSettings()

Desc: 

Returns: -
--------------------------------------------------
*/
void GNewGameResetDynamicSettings() {
	
	moon_scale_fac = original_moon_scale_fac;
	time_speed_night = original_time_speed_night;
	night_sky_scale_x = original_night_sky_scale_x;
	night_sky_speed_x = original_night_sky_speed_x;
	fog_color = original_fog_color;
	camera->fog_start = original_camera_fog_start;
	camera->fog_end = original_camera_fog_end;
	
}

/*
--------------------------------------------------
void GNewGameResetStaticSettings()

Desc:

Returns: -
--------------------------------------------------
*/
void GNewGameResetStaticSettings() {
	
	fog_color = original_fog_color;
	d3d_fogcolor1.red = original_d3d_fogcolor1r;
	d3d_fogcolor1.green = original_d3d_fogcolor1g;
	d3d_fogcolor1.blue = original_d3d_fogcolor1b;
	sun_light = original_sun_light;
	
}

/*
--------------------------------------------------
void GWorldNewHide()

Desc:

Returns: -
--------------------------------------------------
*/
void GWorldNewHide() {
	
	//	reset(panNewGame,SHOW);
	reset(files_list_GROUNDSTR,SHOW);
	reset(files_list_SKYSTR,SHOW);
	reset(NewGame_PreviewButton,SHOW);
	
	InMenu_NewGame = 0;
	
	LoadMystymood(0,0);
	
	if(WorldType == WORLD_DYNAMIC) GNewGameResetDynamicSettings();
	else GNewGameResetStaticSettings();
	
}


/*
--------------------------------------------------
void GpanPropSwitchPage(var mode)

Desc:

Returns: -
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

Desc:

Returns: -
--------------------------------------------------
*/
void GIO_ObjectTab_SwitchTab(var ID) {
	
	if(event_type == EVENT_RELEASE) return;
	
	int _ID = ID, i;
	
	if(!button_state(IO_ObjectTab,_ID,-1)) {
		
		reset(files_list_TEMPSTR,SHOW);
		reset(InsertObject_Inputter,SHOW);
		
		FolderScan(files_list_TEMPSTR,"./","empty"); // Empty scan
		
		return;
		
	}
	
	else {
		
		if(!is(files_list_TEMPSTR,SHOW)) set(files_list_TEMPSTR,SHOW);
		if(!is(InsertObject_Inputter,SHOW)) set(InsertObject_Inputter,SHOW);
		
		switch(_ID) {
			
			// Animals
			case 1:
			
			for(i = 2;i <= 8;i++) button_state(IO_ObjectTab,i,0);
			
			FolderScan(files_list_TEMPSTR_Pool,PATH_OBJECTS_ANMS,EXT_OBJECT);
			
			break;
			
			// Architectures
			case 2:
			
			for(i = _ID-1;i >= 1;i--) button_state(IO_ObjectTab,i,0);
			for(i = _ID+1;i <= 8;i++) button_state(IO_ObjectTab,i,0);
			
			FolderScan(files_list_TEMPSTR_Pool,PATH_OBJECTS_ARCHS,EXT_OBJECT);
			
			break;
			
			// Characters
			case 3:

			for(i = _ID-1;i >= 1;i--) button_state(IO_ObjectTab,i,0);
			for(i = _ID+1;i <= 8;i++) button_state(IO_ObjectTab,i,0);
			
			FolderScan(files_list_TEMPSTR_Pool,PATH_OBJECTS_CHARS,EXT_OBJECT);   
			
			break;
			
			// Everyday objects
			case 4:
			
			for(i = _ID-1;i >= 1;i--) button_state(IO_ObjectTab,i,0);
			for(i = _ID+1;i <= 8;i++) button_state(IO_ObjectTab,i,0);
			
			FolderScan(files_list_TEMPSTR_Pool,PATH_OBJECTS_ETC,EXT_OBJECT);
			
			break;
			
			// Food
			case 5:
			
			for(i = _ID-1;i >= 1;i--) button_state(IO_ObjectTab,i,0);
			for(i = _ID+1;i <= 8;i++) button_state(IO_ObjectTab,i,0);
			
			FolderScan(files_list_TEMPSTR_Pool,PATH_OBJECTS_FOOD,EXT_OBJECT);
			
			break;
			
			// Machines
			case 6:
			
			for(i = _ID-1;i >= 1;i--) button_state(IO_ObjectTab,i,0);
			for(i = _ID+1;i <= 8;i++) button_state(IO_ObjectTab,i,0);
			
			FolderScan(files_list_TEMPSTR_Pool,PATH_OBJECTS_MACHS,EXT_OBJECT); 
			
			break;
			
			// Plants
			case 7:
			
			for(i = ID-1;i >= 1;i--) button_state(IO_ObjectTab,i,0);
			for(i = ID+1;i <= 8;i++) button_state(IO_ObjectTab,i,0);
			
			FolderScan(files_list_TEMPSTR_Pool,PATH_OBJECTS_PLANTS,EXT_OBJECT);
			
			break;
			
			// Transports
			case 8:
			
			for(i = _ID-1;i >= 1;i--) button_state(IO_ObjectTab,i,0);
			
			FolderScan(files_list_TEMPSTR_Pool,PATH_OBJECTS_TPORTTS,EXT_OBJECT); 
			
			break;
			
		}
		
		TEMPSTR_Scaler = 0;
		FillFromPool(files_list_TEMPSTR, files_list_TEMPSTR_Pool , 20, TEMPSTR_Scaler);
		
	}
	
}

/*
--------------------------------------------------
void GObjectTypeTab_Switcher(var ID)

Desc:

Returns: -
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
		if(!is(files_list_TEMPSTR,SHOW)) set(files_list_TEMPSTR,SHOW);
		if(!is(InsertObject_Inputter,SHOW)) set(InsertObject_Inputter,SHOW);
		if(!is(IO_ObjectTab,SHOW)) set(IO_ObjectTab,SHOW);
		if(is(LightPresets,SHOW)) reset(LightPresets,SHOW);
		if(is(InsertParticle,SHOW)) reset(InsertParticle,SHOW);
		
		FolderScan(files_list_TEMPSTR_Pool,PATH_OBJECTS_ANMS,EXT_OBJECT);
		
		break;
		
		case 3: // Sound
		
		if(is(IO_ObjectTab,SHOW)) reset(IO_ObjectTab,SHOW);
		if(!is(files_list_TEMPSTR,SHOW)) set(files_list_TEMPSTR,SHOW);
		if(!is(InsertObject_Inputter,SHOW)) set(InsertObject_Inputter,SHOW);
		if(is(IO_ObjectTab,SHOW)) set(IO_ObjectTab,SHOW);
		if(is(LightPresets,SHOW)) reset(LightPresets,SHOW);
		if(is(InsertParticle,SHOW)) reset(InsertParticle,SHOW);
		
		FolderScan(files_list_TEMPSTR_Pool,PATH_SOUNDS,EXT_SOUND);
		
		break;
		
		case 4: // Particle
		
		if(is(IO_ObjectTab,SHOW)) reset(IO_ObjectTab,SHOW);
		if(is(files_list_TEMPSTR,SHOW)) reset(files_list_TEMPSTR,SHOW);
		if(is(InsertObject_Inputter,SHOW)) reset(InsertObject_Inputter,SHOW);
		if(is(IO_ObjectTab,SHOW)) reset(IO_ObjectTab,SHOW);
		if(is(LightPresets,SHOW)) reset(LightPresets,SHOW);
		if(!is(InsertParticle,SHOW)) set(InsertParticle,SHOW);
		
		break;
		
		case 5: // Light
		
		if(is(IO_ObjectTab,SHOW)) reset(IO_ObjectTab,SHOW);
		if(is(files_list_TEMPSTR,SHOW)) reset(files_list_TEMPSTR,SHOW);
		if(is(InsertObject_Inputter,SHOW)) reset(InsertObject_Inputter,SHOW);
		if(is(IO_ObjectTab,SHOW)) reset(IO_ObjectTab,SHOW);
		if(!is(LightPresets,SHOW)) set(LightPresets,SHOW);
		if(is(InsertParticle,SHOW)) reset(InsertParticle,SHOW);
		
		break;
		
		case 6: // Sprite
		
		if(!is(IO_ObjectTab,SHOW)) set(IO_ObjectTab,SHOW);
		if(!is(files_list_TEMPSTR,SHOW)) set(files_list_TEMPSTR,SHOW);
		if(!is(InsertObject_Inputter,SHOW)) set(InsertObject_Inputter,SHOW);
		if(is(IO_ObjectTab,SHOW)) reset(IO_ObjectTab,SHOW);
		if(is(LightPresets,SHOW)) reset(LightPresets,SHOW);
		if(is(InsertParticle,SHOW)) reset(InsertParticle,SHOW);
		
		FolderScan(files_list_TEMPSTR_Pool,PATH_SPRITES,EXT_SPRITE);
		
		break;
		
		case 7: // Terrain
		
		if(!is(IO_ObjectTab,SHOW)) set(IO_ObjectTab,SHOW);
		if(!is(files_list_TEMPSTR,SHOW)) set(files_list_TEMPSTR,SHOW);
		if(!is(InsertObject_Inputter,SHOW)) set(InsertObject_Inputter,SHOW);
		if(is(IO_ObjectTab,SHOW)) reset(IO_ObjectTab,SHOW);
		if(is(LightPresets,SHOW)) reset(LightPresets,SHOW);
		if(is(InsertParticle,SHOW)) reset(InsertParticle,SHOW);
		
		FolderScan(files_list_TEMPSTR_Pool,PATH_TERRAINS,EXT_TERRAIN);
		
		case 8: // Node
		
		break;
		
		case 9: // Event Trigger + trigger
		
		break;
		
	}
	
	TEMPSTR_Scaler = 0;
	FillFromPool(files_list_TEMPSTR,files_list_TEMPSTR_Pool,20,TEMPSTR_Scaler);
	
}

/*
--------------------------------------------------
void GInsertObjectShow()

Desc:

Returns: -
--------------------------------------------------
*/
void GInsertObjectShow() {
	
	if(event_type == EVENT_RELEASE) return;
	
	if( is(TerrainToolbar,SHOW) ) GToggleTerrainEditor();
	
	set(InsertObject,SHOW);
	set(IO_ObjectTab,SHOW);
	set(InsertObject_Inputter,SHOW);
	
	int i;
	for(i = 2;i<=8;i++) button_state(IO_ObjectTab,i,0);
	for(i = 3;i<=7;i++) button_state(InsertObject,i,0);
	
	button_state(IO_ObjectTab,1,1);
	button_state(InsertObject,2,1);
	
	set(files_list_TEMPSTR,SHOW);
	
	layer_sort(files_list_TEMPSTR,50);
	layer_sort(InsertObject_Inputter,100);
	
	FolderScan(files_list_TEMPSTR_Pool,PATH_OBJECTS_ANMS,EXT_OBJECT);
	FillFromPool(files_list_TEMPSTR, files_list_TEMPSTR_Pool, 20, TEMPSTR_Scaler);
	
	while(is(InsertObject,SHOW)) {
		
		IO_ObjectTab.pos_x = InsertObject.pos_x + 25;
		IO_ObjectTab.pos_y = InsertObject.pos_y + 250;
		
		files_list_TEMPSTR.pos_x = InsertObject.pos_x + 200;
		files_list_TEMPSTR.pos_y = InsertObject.pos_y + 100;
		
		InsertObject_Inputter.pos_x = files_list_TEMPSTR.pos_x;
		InsertObject_Inputter.pos_y = files_list_TEMPSTR.pos_y;
		
		LightPresets.pos_x = InsertObject.pos_x + 100;
		LightPresets.pos_y = InsertObject.pos_y + 100;
		
		InsertParticle.pos_x = InsertObject.pos_x + 100;
		InsertParticle.pos_y = InsertObject.pos_y + 100;
		
		wait(1);
		
	}
	
	//	if(mark) GToggleTerrainEditor(); // flip the switch again
	
}

/*
--------------------------------------------------
void GInsertObjectHide()

Desc:

Returns: -
--------------------------------------------------
*/
void GInsertObjectHide() {
	
	
	reset(InsertObject,SHOW);
	reset(IO_ObjectTab,SHOW);
	reset(InsertObject_Inputter,SHOW);
	reset(LightPresets,SHOW);
	reset(InsertParticle,SHOW);
	
	reset(files_list_TEMPSTR,SHOW);
	
}

/*
--------------------------------------------------
void GSelectObject(var ID)

Desc:

Returns: -
--------------------------------------------------
*/
void GSelectObject(var ID) {
	
	if(event_type == EVENT_RELEASE) return;
	
	int _ID = ID-1;
	
	if( str_cmp( (files_list_TEMPSTR.pstring)[_ID],undef) )  {
		
		str_cpy(TEMPSTR,undef);
		
		_beep();
		return;
		
	}
	
	if(is(InsertObject,SHOW)) {
		
		if(is(IO_ObjectTab,SHOW) )
		{
			
			while( !is(files_list_TEMPSTR,SHOW) && !is(InsertObject_Inputter,SHOW) ) wait(1);
			
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
			
			
			str_cat(TEMPSTR,(files_list_TEMPSTR.pstring)[_ID]);
			GInsertObjectHide();
			
			mark_seedEntstr = 1;
			
			return;
			
		} 
		
		if(button_state(InsertObject,3,-1)) { // Sound
			
			str_cpy(TEMPSTR,PATH_SOUNDS);
			str_cat(TEMPSTR,(files_list_TEMPSTR.pstring)[_ID]);
			TEMP_OBJECT_TYPE = Sound;
			
			GInsertObjectHide();
			
			return;
			
		}
		
		if(button_state(InsertObject,6,-1)) { // Sprite
			
			str_cpy(TEMPSTR,PATH_SPRITES);
			str_cat(TEMPSTR,(files_list_TEMPSTR.pstring)[_ID]);
			TEMP_OBJECT_TYPE = Sprite;
			
			GInsertObjectHide();
			
			return;
			
		}
		
		if(button_state(InsertObject,7,-1)) { // Terrain
			
			str_cpy(TEMPSTR,PATH_TERRAINS);
			str_cat(TEMPSTR,(files_list_TEMPSTR.pstring)[_ID]);
			TEMP_OBJECT_TYPE = Terrain;
			
			GInsertObjectHide();
			
			return;
			
		}
		
	}
	
}

/*
--------------------------------------------------
void GSelectParticle(var ID)

Desc:

Returns: -
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

Desc:

Returns: -
--------------------------------------------------
*/
void GSelectLight(var ID) {
	
	if(event_type == EVENT_RELEASE) return;
	
	switch((int)ID) {
		
		case 1:
		// RGB color code for Pure Red
		// temp_light = CopyColor(255,0,0);
		temp_light.red = 255;
		temp_light.green = 0;
		temp_light.blue = 0;
		
		break;
		
		case 2:
		// RGB color code for Pure Green
		// temp_light = CopyColor(0,255,0);
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
		// temp_light = CopyColor(255,255,0);
		temp_light.red = 255;
		temp_light.green = 255;
		temp_light.blue = 0;
		
		break;
		
		case 4:
		// RGB color code for Teal from http://en.wikipedia.org/wiki/Teal
		// temp_light = CopyColor(54,117,136);
		temp_light.red = 54;
		temp_light.green = 117;
		temp_light.blue = 136;
		
		break;
		
		case 5:
		// RGB color code for Bud Green from http://en.wikipedia.org/wiki/List_of_colors:_A%E2%80%93F
		// Bonus: May Green, (76, 145, 65).
		// temp_light = CopyColor(123,182,97);
		temp_light.red = 123;
		temp_light.green = 182;
		temp_light.blue = 97;
		
		break;
		
		case 6:
		// RGB color code for Pure White
		// temp_light = CopyColor(255,255,255);
		temp_light.red = temp_light.green = temp_light.blue = 255;
		
		break;
		
		case 7:
		// RGB color code for Cyan from http://en.wikipedia.org/wiki/Cyan
		// green + blue = cyan
		// temp_light = CopyColor(0,255,255);
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
		// temp_light = CopyColor(255,127,0);
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
		// temp_light = CopyColor(143,0,255);
		temp_light.red = 143;
		temp_light.green = 0;
		temp_light.blue = 255;
		
		break;
		
		case 10:
		// RGB color code for Lavender from http://en.wikipedia.org/wiki/Lavender_(color)
		// temp_light = CopyColor(230,230,250);
		temp_light.red = 230;
		temp_light.green = 230;
		temp_light.blue = 250;
		
		break;
		
		case 11:
		// RGB color code for Brown from http://en.wikipedia.org/wiki/Brown
		// temp_light = CopyColor(150,75,0);
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
		// temp_light = CopyColor(75,0,130);
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

Desc:

Returns: -
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
	
	GPanelResize(BackgroundScreen,RESIZE_XY);
	
	set(BackgroundScreen,SHOW);
	set(PreMainMenuLoading,SHOW);
	
}

// Sorry for the terrible-lookin' code. I don't have much time.
/*
--------------------------------------------------
void GOptions_Graphics()

Desc:

Returns: -
--------------------------------------------------
*/
void GOptions_Graphics() {
	
	if(event_type == EVENT_RELEASE) return;
	
	GSEMenuMouseClick();
	
	if(is(Options_Sound,SHOW)) {
		
		reset(Options_Sound,SHOW);
		reset(OptionsSoundTxt,SHOW);
		
	}
	if(is(Options_Themes,SHOW)) reset(Options_Themes,SHOW);
	if(is(Options_Maintenance,SHOW)) reset(Options_Maintenance,SHOW);
	
	set(Options_Graphics, SHOW);
	set(OptionsGraphicsTxt,SHOW);
	
	OptionsGraphicsTxt.pos_x = Options_Graphics.pos_x + 290;
	OptionsGraphicsTxt.pos_y = Options_Graphics.pos_y + 90;
	
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
	
	/*
	
	if(video_aspect >= 4/3 && video_aspect < 16/10) str_cpy((OptionsGraphicsTxt.pstring)[1],"4:3");
	else if(video_aspect >= 16/10 && video_aspect < 16/9) str_cpy((OptionsGraphicsTxt.pstring)[1],"16:10");
	else if(video_aspect >= 16/9) str_cpy((OptionsGraphicsTxt.pstring)[1],"16:9");
	else str_cpy((OptionsGraphicsTxt.pstring)[1],"I don't know...");	
	
	*/
	
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

Desc:

Returns: -
--------------------------------------------------
*/
void GOptions_Sound() {
	
	if(event_type == EVENT_RELEASE) return;
	
	GSEMenuMouseClick();
	
	if(is(Options_Graphics,SHOW)) {
		
		reset(Options_Graphics, SHOW);
		reset(OptionsGraphicsTxt,SHOW);
		
		
	}
	
	if(is(Options_Themes,SHOW)) reset(Options_Themes,SHOW);
	if(is(Options_Maintenance,SHOW)) reset(Options_Maintenance,SHOW);

	set(Options_Sound,SHOW);
	set(OptionsSoundTxt,SHOW);
	
	OptionsSoundTxt.pos_x = Options_Sound.pos_x + 290;
	OptionsSoundTxt.pos_y = Options_Sound.pos_y + 90;
	
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

Desc:

Returns: -
--------------------------------------------------
*/
void GOptions_Themes() {
	
	if(event_type == EVENT_RELEASE) return;
	
	GSEMenuMouseClick();
	
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
	
	GInDevShow();
	
}

/*
--------------------------------------------------
void GOptions_Maintenance()

Desc:

Returns: -
--------------------------------------------------
*/
void GOptions_Maintenance() {
	
	if(event_type == EVENT_RELEASE) return;
	
	GSEMenuMouseClick();
	
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
	
	GInDevShow();
	
}

/*
--------------------------------------------------
void GOptions_SaveSettings()

Desc:

Returns: -
--------------------------------------------------
*/
void GOptions_SaveSettings() {
	
	if(event_type == EVENT_RELEASE) return;
	
	GSEMenuMouseClick();
	
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
		/*
		
		if( str_cmp((OptionsGraphicsTxt.pstring)[1],"4:3") ) video_aspect = 4/3;
		else if(str_cmp((OptionsGraphicsTxt.pstring)[1],"16:9")) video_aspect = 16/9;
		else video_aspect = 16/10;
		
		*/
		
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

Desc:

Returns: -
--------------------------------------------------
*/
void GOptionsAdjustSettings(var ID) {
	
	if(event_type == EVENT_RELEASE) return;
	
	GSEMenuMouseClick();
	
	if(is(Options_Graphics,SHOW)) {
		
		ID = (int)ID; // Well, I have nothing to say...
		
		switch(ID) {
			
			case 1: case 2: // Full screen <-> Windowed
			
			if( str_cmp((OptionsGraphicsTxt.pstring)[0],"Full Screen") ) str_cpy((OptionsGraphicsTxt.pstring)[0],str_create("Windowed"));
			else str_cpy((OptionsGraphicsTxt.pstring)[0],str_create("Full Screen"));
			
			break;
			
			/*
			
			case 3: case 4: // 4:3 <-> 16:10 <-> 16:9
			
			if( str_cmp((OptionsGraphicsTxt.pstring)[1],"4:3") ) str_cpy( (OptionsGraphicsTxt.pstring) [1] , str_create("16:9"));
			else if ( str_cmp((OptionsGraphicsTxt.pstring)[1],"16:9")) str_cpy( (OptionsGraphicsTxt.pstring) [1] , str_create("16:10"));
			else str_cpy( (OptionsGraphicsTxt.pstring) [1] , str_create("4:3"));
			
			break;
			
			*/
			
			case 3: case 4: // 16-bit color depth <-> 32-bit
			
			if( str_cmp((OptionsGraphicsTxt.pstring)[2],"16-bit") ) str_cpy( (OptionsGraphicsTxt.pstring) [2],str_create("32-bit"));
			else str_cpy( (OptionsGraphicsTxt.pstring) [2],str_create("16-bit"));
			
			break;
			
			case 5: // Brightness --
			
			int brightness = str_to_num( (OptionsGraphicsTxt.pstring) [3]);
			
			if(brightness <= 50) break;
			
			brightness-=5;
			
			str_for_num((OptionsGraphicsTxt.pstring)[3],brightness);
			
			break;
			
			case 6: // brightness ++
			
			int brightness = str_to_num( (OptionsGraphicsTxt.pstring) [3]);
			brightness+=5;
			
			if (brightness >= 150) break;
			
			str_for_num((OptionsGraphicsTxt.pstring)[3],brightness);
			
			break;
			
			case 7: // fsaa --
			
			int fsaa = str_to_num( (OptionsGraphicsTxt.pstring) [4]);
			
			if(fsaa <= 0) break;
			
			fsaa--;
			
			str_for_num((OptionsGraphicsTxt.pstring)[4],fsaa);
			
			break;
			
			case 8: // fsaa ++ 
			
			int fsaa = str_to_num( (OptionsGraphicsTxt.pstring) [4]);
			
			if(fsaa >= 9) break;
			fsaa++;
			
			str_for_num((OptionsGraphicsTxt.pstring)[4],fsaa);
			
			break;
			
			case 9: // af --
			
			int af = str_to_num( (OptionsGraphicsTxt.pstring) [5]);
			
			if(af <= 0) break;
			af--;
			
			str_for_num((OptionsGraphicsTxt.pstring)[5],af);
			
			break;
			
			case 10: // af ++ 
			
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
void GLoadGameShow()

Desc:

Returns: -
--------------------------------------------------
*/
void GLoadGameShow() {
	
	if(event_type == EVENT_RELEASE) return;
	
	if(is(LoadGame,SHOW)) {
		
		GLoadGameHide();
		
		return;
		
	}
	
	guiCurrentViewPreset = MENU_CAMERA_LOAD_GAME;
	
	GSEMenuMouseClick();
	
	GWorldNewHide();
	GOptionsHide();
	GTrophiesHide();
	GHelpHide();
	
	FillFromPool(files_list_LOADGAMESTR, files_list_LOADGAMESTR_Pool, 8, 0);
	
	set(LoadGame,SHOW);
	set(InputBox_LOADGAMESTR,SHOW);
	set(files_list_LOADGAMESTR,SHOW);
	
}

/*
--------------------------------------------------
void GLoadGameHide()

Desc:

Returns: -
--------------------------------------------------
*/
void GLoadGameHide() {
	
	reset(LoadGame,SHOW);
	reset(files_list_LOADGAMESTR,SHOW);
	reset(InputBox_LOADGAMESTR,SHOW);
	
}

/*
--------------------------------------------------
void GTrophiesShow()

Desc:

Returns: -
--------------------------------------------------
*/
void GTrophiesShow() {
	
	if(event_type == EVENT_RELEASE) return;
	
	GSEMenuMouseClick();
	
	guiCurrentViewPreset = MENU_CAMERA_TROPHIES;
	
	GHelpHide();
	GWorldNewHide();
	GLoadGameHide();
	GOptionsHide();
	
}

/*
--------------------------------------------------
void GTrophiesHide()

Desc:

Returns: -
--------------------------------------------------
*/
void GTrophiesHide() {
	
	wait(1);
	
}

/*
--------------------------------------------------
void GHelpShow()

Desc:

Returns: -
--------------------------------------------------
*/
void GHelpShow() {
	
	if(event_type == EVENT_RELEASE) return;
	
	GSEMenuMouseClick();
	
	guiCurrentViewPreset = MENU_CAMERA_HELP;
	
	GWorldNewHide();
	GLoadGameHide();
	GOptionsHide();
	GTrophiesHide();
	
}

/*
--------------------------------------------------
void GHelpHide()

Desc:

Returns: -
--------------------------------------------------
*/
void GHelpHide() {
	
	wait(1);
	
}

/*
--------------------------------------------------
void FillFromPool(TEXT *dest, TEXT *pool, var amount, var scaler)

Desc:

Returns: -
--------------------------------------------------
*/
void FillFromPool(TEXT *dest, TEXT *pool, var amount, var scaler) {
	
	if(amount <= 0) return;
	
	while(!pool || !dest) wait(1);
	
	amount = abs(amount);
	
	int i = 0;
	while(i < amount) {
		
		str_cpy( (dest.pstring) [i], (pool.pstring) [ scaler*amount + i ] );
		
		i++;
		
	}
	
}

/*
--------------------------------------------------
void GPanelFade(PANEL *Panel, var start, var end, var speed)

Desc:

Returns: -
--------------------------------------------------
*/
void GPanelFade(PANEL *Panel, var start, var end, var speed) {
	
	while(!Panel) wait(1);
	if(start == end) return;
	
	speed = abs(speed);
	start = abs(start);
	end = abs(end);
	
	if(end>100) end=100;
	if(start>100) start=100;
	
	Panel->alpha = start;
	
	if(start > end) { // Fade out 
		
		while(Panel->alpha >= end) {
			
			Panel->alpha -= speed * time_step;
			wait(1);
			
		}
		
	}

	else { // Fade in

		while(Panel->alpha <= end) {
			
			Panel->alpha += speed * time_step;
			wait(1);
			
		}

	}

	Panel->alpha = end;

}

/*
--------------------------------------------------
void GNewGame_PreviewScene()

Desc:

Returns: -
--------------------------------------------------
*/
void GNewGame_PreviewScene() {
	
	GSEMenuMouseClick();
	
	GMainMenuHide();
	
}

/*
--------------------------------------------------
void GNewGame_UnPreviewScene()

Desc:

Returns: -
--------------------------------------------------
*/
void GNewGame_UnPreviewScene() {
	
	if(event_type == EVENT_CLICKUP) return;
	
	//	GSEMenuMouseClick();
	
	GMainMenuShow();
	
}

void GTEMPSTR_Up() {
	
	if(event_type == EVENT_RELEASE) return;
	
	GSEMenuMouseClick();
	
	if(TEMPSTR_Scaler > 0) {
		
		TEMPSTR_Scaler -= 1;
		
		FillFromPool(files_list_TEMPSTR, files_list_TEMPSTR_Pool, 20, TEMPSTR_Scaler );
		
	}
	
}

void GTEMPSTR_Down() {
	
	if(event_type == EVENT_RELEASE) return;
	
	GSEMenuMouseClick();
	
	TEMPSTR_Scaler += 1;
	FillFromPool(files_list_TEMPSTR, files_list_TEMPSTR_Pool, 20, TEMPSTR_Scaler );
	
}

/*
--------------------------------------------------
void GLOADGAMESTR_Up()

Desc:

Returns: -
--------------------------------------------------
*/
void GLOADGAMESTR_Up() {
	
	if(event_type == EVENT_RELEASE) return;
	
	GSEMenuMouseClick();
	
	if(LOADGAMESTR_Scaler > 0) {
		
		LOADGAMESTR_Scaler -= 1;
		FillFromPool(files_list_LOADGAMESTR, files_list_LOADGAMESTR_Pool, 8, LOADGAMESTR_Scaler);
	}
	
}

/*
--------------------------------------------------
void GLOADGAMESTR_Down()

Desc:

Returns: -
--------------------------------------------------
*/
void GLOADGAMESTR_Down() {
	
	if(event_type == EVENT_RELEASE) return;
	
	GSEMenuMouseClick();
	
	LOADGAMESTR_Scaler += 1;
	FillFromPool(files_list_LOADGAMESTR, files_list_LOADGAMESTR_Pool, 8, LOADGAMESTR_Scaler);
	
}

/*
--------------------------------------------------
void GSKYSTR_Up()

Desc:

Returns: -
--------------------------------------------------
*/
void GSKYSTR_Up() {
	
	if(event_type == EVENT_RELEASE) return;
	
	GSEMenuMouseClick();
	
	if(SKYSTR_Scaler > 0) {
		
		SKYSTR_Scaler -= 1;
		FillFromPool(files_list_SKYSTR, files_list_SKYSTR_Pool, 4, SKYSTR_Scaler);
		
	}
	
}

/*
--------------------------------------------------
void GSKYSTR_Down()

Desc:

Returns: -
--------------------------------------------------
*/
void GSKYSTR_Down() {
	
	if(event_type == EVENT_RELEASE) return;
	
	GSEMenuMouseClick();
	
	SKYSTR_Scaler += 1; // ++
	FillFromPool(files_list_SKYSTR, files_list_SKYSTR_Pool, 4, SKYSTR_Scaler);
	
}

/*
--------------------------------------------------
void GGROUNDSTR_Up()

Desc:

Returns: -
--------------------------------------------------
*/
void GGROUNDSTR_Up() {
	
	if(event_type == EVENT_RELEASE) return;
	
	GSEMenuMouseClick();
	
	if(GROUNDSTR_Scaler > 0) {
		
		GROUNDSTR_Scaler -= 1;
		FillFromPool(files_list_GROUNDSTR, files_list_GROUNDSTR_Pool, 4, GROUNDSTR_Scaler);
		
	}
	
}

/*
--------------------------------------------------
void GGROUNDSTR_Down()

Desc:

Returns: -
--------------------------------------------------
*/
void GGROUNDSTR_Down() {
	
	if(event_type == EVENT_RELEASE) return;
	
	GSEMenuMouseClick();
	
	GROUNDSTR_Scaler += 1;
	FillFromPool(files_list_GROUNDSTR, files_list_GROUNDSTR_Pool, 4, GROUNDSTR_Scaler);
	
}

/*
--------------------------------------------------
void GSwitchNewGameScreen ( var ID ) 

Desc:

Returns: -
--------------------------------------------------
*/
void GSwitchNewGameScreen ( var ID ) {
	
	if(event_type == EVENT_RELEASE) return;
	
	GSEMenuMouseClick();
	
	if( (int) ID == 1) {
		
		if(is(NewGame_Screen3,SHOW)) {
			
			if(WorldType == WORLD_DYNAMIC) { // Dynamic world was picked up before
				
				reset(NewGame_ScreenStatic_Step1,SHOW);
				set(NewGame_ScreenDyn_Step1,SHOW);
				
				if(!mystymood_active) LoadMystymood(1,1);
				
			}
			else { // Static world
				
				reset(NewGame_ScreenDyn_Step1,SHOW);  
				set(NewGame_ScreenStatic_Step1,SHOW);
				
				LoadMystymood(0,0);
				mystymood_active = 0;
				
			}
			
			reset(NewGame_Screen3,SHOW);
			set(NewGame_ScreenRight,SHOW);
			
			reset(InputBox_GROUNDSTR,SHOW);
			reset(InputBox_SKYSTR,SHOW);
			reset(files_list_GROUNDSTR,SHOW);
			reset(files_list_SKYSTR,SHOW);
			
			set(NewGame_PreviewButton,SHOW);
			
			return;
			
		}
		
		if(is(NewGame_ScreenDyn_Step1,SHOW) || is(NewGame_ScreenStatic_Step1,SHOW)) {
			
			reset(NewGame_ScreenDyn_Step1,SHOW);
			reset(NewGame_ScreenStatic_Step1,SHOW);
			reset(NewGame_PreviewButton,SHOW);
			
			set(NewGame_Screen1,SHOW);
			reset(NewGame_ScreenRight,SHOW);
			reset(NewGame_ScreenLeft,SHOW);
			
			mystymood_active = 0;
			LoadMystymood(0,0);
			
			GNewGameResetDynamicSettings();
			
			return;
			
			
		}
		
	}

	else {
		
		if(is(NewGame_Screen1,SHOW)) {
			
			if(WorldType == WORLD_DYNAMIC) { // Dynamic world was picked up before
				
				reset(NewGame_ScreenStatic_Step1,SHOW);
				set(NewGame_ScreenDyn_Step1,SHOW);
				
				if(!mystymood_active) LoadMystymood(1,1);
				
			}
			else { // Static world
				
				reset(NewGame_ScreenDyn_Step1,SHOW);  
				set(NewGame_ScreenStatic_Step1,SHOW);
				
				LoadMystymood(0,0);
				mystymood_active = 0;
				
			}
			
			reset(NewGame_Screen1,SHOW);
			
			set(NewGame_ScreenRight,SHOW);
			set(NewGame_ScreenLeft,SHOW);
			set(NewGame_PreviewButton,SHOW);
			
			return;
			
		}
		
		if(is(NewGame_ScreenDyn_Step1,SHOW) || is(NewGame_ScreenStatic_Step1,SHOW)) {
			
			reset(NewGame_ScreenDyn_Step1,SHOW);
			reset(NewGame_ScreenStatic_Step1,SHOW);
			reset(NewGame_PreviewButton,SHOW);
			
			set(NewGame_Screen3,SHOW);
			reset(NewGame_ScreenRight,SHOW);
			
			if(!mystymood_active && WorldType == WORLD_DYNAMIC) LoadMystymood(1,1);
			
			set(InputBox_GROUNDSTR,SHOW);
			set(InputBox_SKYSTR,SHOW);
			set(files_list_GROUNDSTR,SHOW);
			set(files_list_SKYSTR,SHOW);
			
			FillFromPool(files_list_GROUNDSTR, files_list_GROUNDSTR_Pool, 4, 0);					
			FillFromPool(files_list_SKYSTR, files_list_SKYSTR_Pool, 4, 0);
			
			return;
			
		}
		
	}
	
}

/*
--------------------------------------------------
void GNewGame_ChooseWorld(var ID)

Desc:

Returns: -
--------------------------------------------------
*/
void GNewGame_ChooseWorld(var ID) {
	
	if(event_type == EVENT_RELEASE) return;
	
	WorldType = (int) ID;
	
	//	GSEMenuMouseClick();
	
	GSwitchNewGameScreen(2);
	
}

/*
--------------------------------------------------
void GToggleMusicPlayerRandomize()

Desc:

Returns: -
--------------------------------------------------
*/
void GToggleMusicPlayerRandomize() {
	
	if(event_type == EVENT_RELEASE) return;
	
	GSEMenuMouseClick();
	
	if(button_state(MusicPlayer,5,-1)) mpRandomize = 1;
	else mpRandomize = 0;
	
}

/*
--------------------------------------------------
void GBlackboardAlphaFade()

Desc:

Returns: -
--------------------------------------------------
*/
void GBlackboardAlphaFade() {
	
	BBTranslucency = Blackboard->alpha;
	Blackboard->alpha = 20;
	
}

/*
--------------------------------------------------
void GBlackboardAlphaRestore()

Desc:

Returns: -
--------------------------------------------------
*/
void GBlackboardAlphaRestore() {
	
	if(BBTranslucency) Blackboard->alpha = BBTranslucency;
	
}

/*
--------------------------------------------------
void GToggleStatistics()

Desc:

Returns: -
--------------------------------------------------
*/
void GToggleStatistics() {
	
	if(event_type == EVENT_RELEASE) return;

	if( is(StatsPanel,SHOW) )   {
		
		reset(StatsPanel,SHOW);
		reset(Stats,SHOW);
		
		return;
		
	}
	
	StatsPanel->pos_x = 50;
	StatsPanel->pos_y = 50;
	
	GSEMenuMouseClick();
	
	set(StatsPanel,SHOW);
	set(Stats,SHOW);
	
	while( is(StatsPanel,SHOW) ) {
		
		ConvertToCTFormat((StatsPanel.pstring) [0], CountObjects, MAX_OBJECTS);
		ConvertToCTFormat((StatsPanel.pstring) [1], CountParticles, MAX_PARTICLES);
		ConvertToCTFormat((StatsPanel.pstring) [2], CountLights, MAX_LIGHTS);
		ConvertToCTFormat((StatsPanel.pstring) [3], CountSounds, MAX_SOUNDS );
		ConvertToCTFormat((StatsPanel.pstring) [4], CountSprites, MAX_SPRITES);
		ConvertToCTFormat((StatsPanel.pstring) [5], CountObjects+CountParticles+CountLights+CountSounds+CountSprites, MAX_TOTAL);
		
		StatsPanel->pos_x = Stats->pos_x + 266;
		StatsPanel->pos_y = Stats->pos_y + 66;
		
		wait(1);
		
	}
}

/*
--------------------------------------------------
void GInDevHide()

Desc:

Returns: -
--------------------------------------------------
*/
void GInDevHide() {
	
	if(event_type == EVENT_RELEASE) return;
	
	reset(InDev,SHOW);
	
}

/*
--------------------------------------------------
void GInDevShow()

Desc:

Returns: -
--------------------------------------------------
*/
void GInDevShow() {
	
	if(event_type == EVENT_RELEASE) return;
	
	GSEMenuMouseClick();
	
	set(InDev,SHOW);
	
}


/*
--------------------------------------------------
void GSEMenuMouseHover()

Desc:

Returns: -
--------------------------------------------------
*/
void GSEMenuMouseHover() {
	
	return;
	
	proc_kill(4);
	
	str_cpy(sndConnectorShared,PATH_SOUNDS_); // STRING specifically for sndConnectorShared
	str_cat(sndConnectorShared,SE_MM_hover);
	
	sndPlay(sndConnectorShared);
	
}

/*
--------------------------------------------------
void GSEMenuMouseClick()

Desc:

Returns: -
--------------------------------------------------
*/
void GSEMenuMouseClick() {
	
	return;
	
	proc_kill(4);
	
	str_cpy(sndConnectorShared,PATH_SOUNDS_);
	str_cat(sndConnectorShared,SE_MM_click);
	
	sndPlay(sndConnectorShared);
	
}

/*
--------------------------------------------------
void GBackMenuShow()

Desc:

Returns: -
--------------------------------------------------
*/
void GBackMenuShow() {
	
	if(event_type == EVENT_RELEASE) return;
	
	GGUIHide();	
	set(BackMenu_Background,SHOW);
	set(BackMenu_Items,SHOW);
	
	InBackMenu = 1;
	
}

/*
--------------------------------------------------
void GBackMenuHide()

Desc:

Returns: -
--------------------------------------------------
*/
void GBackMenuHide() {
	
	if(event_type == EVENT_RELEASE) return;
	
	reset(BackMenu_Background,SHOW);
	reset(BackMenu_Items,SHOW);
	
	GGUIShow();
	
	InBackMenu = 0;
	
}

/*
--------------------------------------------------
void GPanelMoveAlpha(PANEL *p, var mode, var oldpos, var newpos, var oldAlpha, var newAlpha, var speed)

Desc:

Returns: -
--------------------------------------------------
*/
void GPanelMoveAlpha(PANEL *p, var mode, var oldpos, var newpos, var oldAlpha, var newAlpha, var speed) {
	
	while(!p) wait(1);
	
	speed = abs(speed);
	if( speed <= 0) speed = 5;
	
	int OldFlag = is(p,TRANSLUCENT), OldAlpha = p->alpha;		
	if(oldpos > newpos) {
		
		var swapped = oldpos + newpos;
		oldpos = swapped - oldpos;
		newpos = swapped - newpos;
		
	}

	set(p,TRANSLUCENT);

	if(mode == X) { // Move along the x-axis

		p.pos_x = oldpos;

		while(p.pos_x <= newpos) {
			
			p.pos_x += speed * time_step;
			p.alpha = GetPercent(p.pos_x, newpos);
			
			wait(1);
		}

		p.pos_x = newpos;
		
	}
	
	else { // y-axis
		
		p.pos_y = oldpos;

		while(p.pos_y <= newpos) {
			
			p.pos_y += speed * time_step;
			p.alpha = GetPercent(p.pos_y, newpos);
			
			wait(1);
		}

		p.pos_y = newpos;
		
		
	}
	
	p.alpha = GetPercent(1,1); // = 100%
	
	if( !OldFlag ) {
		
		p->alpha = OldAlpha;
		reset(p,TRANSLUCENT);
		
	}
	
}

/*
--------------------------------------------------
void GPanelMoveAlphaX(PANEL *Panel, var oldx, var newx, var speed)

Desc:

Returns: -
--------------------------------------------------
*/
void GPanelMoveAlphaX(PANEL *Panel, var oldx, var newx, var speed) {
	
	GPanelMoveAlpha(Panel,X,oldx,newx,0,0,speed);   
	
}

/*
--------------------------------------------------
void GPanelMoveAlphaY(PANEL *Panel, var oldy, var newy, var speed)

Desc: 

Returns: -
--------------------------------------------------
*/
void GPanelMoveAlphaY(PANEL *Panel, var oldy, var newy, var speed) {
	
	GPanelMoveAlpha(Panel,Y,oldy,newy,0,0,speed);
	
}