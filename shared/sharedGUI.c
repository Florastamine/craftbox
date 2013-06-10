// 28/5/2013, 19:02 the recipe - kendrick lamar, dr.dre
// 29/5/2013, 8:00 swimming pools - kendrick lamar
// 9/6/2013, 18:04 love me - lil wayne, drake, future
//#include<acknex.h>
/*

[ sharedGUI.c ]

a .c file that defines the general-purpose GUI/HUD for use within all 
available frameworks. its kernel is located in ./sharedCustom/sharedCustom.c
*/

/*

close button will be the first element no matter what.

*/

PANEL *buttonlst,
*panMain_Top,
*panMain_Bottom,
*buttonlst_submenu_terrain,
*buttonlst_submenu_object,
*buttonlst_submenu_path,
*panHome,
*panProp,
*panPhy,
*panMat,
*panMat_Sub1,
*_logo,
*blackscreen,
*blackpix,
*inst,
*debug;

//TEXT *t_panProp[3];

/*
BMAP *button_New = "button_general.bmp";
BMAP *button_New_Over = "button_general_over.bmp";

BMAP *button_Open = "button_general.bmp";
BMAP *button_Open_Over = "button_general_over.bmp";

BMAP *button_Save = "button_general.bmp";
BMAP *button_Save_Over = "button_general_over.bmp";
*/

BMAP *button_black = "button_black.bmp";

BMAP *button_Copy = "button_Copy.bmp";
BMAP *button_Copy_Over = "button_Copy_over.bmp";
BMAP *button_Copy_Off = "button_Copy_off.bmp";

BMAP *button_Paste = "button_Paste.bmp";
BMAP *button_Paste_Over = "button_Paste_over.bmp";
BMAP *button_Paste_off = "button_Paste_off.bmp";

BMAP *button_Cut = "button_Cut.bmp";
BMAP *button_Cut_Over = "button_Cut_over.bmp";
BMAP *button_Cut_Off = "button_Cut_off.bmp";

BMAP *button_Move = "button_Move.bmp";
BMAP *button_Move_Over = "button_Move_over.bmp";
BMAP *button_Move_Off = "button_Move_off.bmp";

BMAP *button_Rotate = "button_Rotate.bmp";
BMAP *button_Rotate_Over = "button_Rotate_over.bmp";
BMAP *button_Rotate_Off = "button_Rotate_off.bmp";

BMAP *button_Scale = "button_Scale.bmp";
BMAP *button_Scale_Over = "button_Scale_over.bmp";
BMAP *button_Scale_Off = "button_Scale_off.bmp";

BMAP *button_Prop = "button_Prop.bmp";
BMAP *button_Prop_Over = "button_Prop_over.bmp";
BMAP *button_Prop_Off = "button_Prop_off.bmp";

BMAP *button_Phy = "button_Phy.bmp";
BMAP *button_Phy_Over = "button_Phy_over.bmp";
BMAP *button_Phy_Off = "button_Phy_off.bmp";

BMAP *button_Mat = "button_Mat.bmp";
BMAP *button_Mat_Over = "button_Mat_over.bmp";
BMAP *button_Mat_Off = "button_Mat_off.bmp";

BMAP *button_Home = "button_Home_on.bmp";
BMAP *button_Home_Over = "button_Home_over.bmp";
BMAP *button_Home_Off = "button_Home_off.bmp";

BMAP *button_Cam = "button_Camera_on.bmp";
BMAP *button_Cam_Over = "button_Camera_over.bmp";
BMAP *button_Cam_Off = "button_Camera_off.bmp";

BMAP *button_Terrain = "button_Terrain_on.bmp";
BMAP *button_Terrain_Over = "button_Terrain_over.bmp";
BMAP *button_Terrain_Off = "button_Terrain_off.bmp";

BMAP *button_Objs = "button_Object_on.bmp";
BMAP *button_Objs_Over = "button_Object_over.bmp";
BMAP *button_Objs_Off = "button_Object_off.bmp";

BMAP *button_Path = "button_Path_on.bmp";
BMAP *button_Path_Over = "button_Path_over.bmp";
BMAP *button_Path_Off = "button_Path_off.bmp";

BMAP *button_Close = "button_Close.bmp";

BMAP *button_Home_newworld = "button_Home_newworld.bmp";
BMAP *button_Home_loadworld = "button_Home_loadworld.bmp";
BMAP *button_Home_saveworld = "button_Home_saveworld.bmp";
BMAP *button_Home_compileworld = "button_Home_compileworld.bmp";
BMAP *button_Home_configworld = "button_Home_configworld.bmp";
BMAP *button_Home_quitworld = "button_Home_quitworld.bmp";

BMAP *flag_BIRGHT = "flag_BIRGHT.bmp";
BMAP *flag_BIRGHT_on = "flag_BIRGHT_on.bmp";

BMAP *flag_INVISIBLE = "flag_INVISIBLE.bmp";
BMAP *flag_INVISIBLE_on = "flag_INVISIBLE_on.bmp";

BMAP *flag_NOFOG = "flag_NOFOG.bmp";
BMAP *flag_NOFOG_on = "flag_NOFOG_on.bmp";

BMAP *flag_OVERLAY = "flag_OVERLAY.bmp";
BMAP *flag_OVERLAY_on = "flag_OVERLAY_on.bmp";

BMAP *flag_PASSABLE = "flag_PASSABLE.bmp";
BMAP *flag_PASSABLE_on = "flag_PASSABLE_on.bmp";

BMAP *flag_POLYGON = "flag_POLYGON.bmp";
BMAP *flag_POLYGON_on = "flag_POLYGON_on.bmp";

BMAP *flag_SHADOW = "flag_SHADOW.bmp";
BMAP *flag_SHADOW_on = "flag_SHADOW_on.bmp";

BMAP *flag_TRANSLUCENT = "flag_TRANSLUCENT.bmp";
BMAP *flag_TRANSLUCENT_on = "flag_TRANSLUCENT_on.bmp";

BMAP *slider = "xlider.bmp";

BMAP *button_Mat1 = "button_Mat1.bmp";
BMAP *button_Mat2 = "button_Mat2.bmp";
BMAP *button_Mat3 = "button_Mat3.bmp";
BMAP *button_Mat4 = "button_Mat4.bmp";
BMAP *button_Mat5 = "button_Mat5.bmp";
BMAP *button_Mat6 = "button_Mat6.bmp";
BMAP *button_MatNorm = "button_MatNorm.bmp";

BMAP *menu1_submenu1 = "button_submenu1_1.bmp";
BMAP *menu1_submenu2 = "button_submenu1_2.bmp";
BMAP *menu1_submenu3 = "button_submenu1_3.bmp";
BMAP *menu1_submenu4 = "button_submenu1_4.bmp";

BMAP *menu2_submenu1 = "button_submenu2_1.bmp";
BMAP *menu2_submenu2 = "button_submenu2_2.bmp";
BMAP *menu2_submenu3 = "button_submenu2_3.bmp";
BMAP *menu2_submenu4 = "button_submenu2_4.bmp";

BMAP *menu3_submenu1 = "button_submenu3_1.bmp";
BMAP *menu3_submenu2 = "button_submenu3_2.bmp";
BMAP *menu3_submenu3 = "button_submenu3_3.bmp";
BMAP *menu3_submenu4 = "button_submenu3_4.bmp";

BMAP *button_back = "button_back.bmp";
BMAP *button_back_over = "button_back_over.bmp";

BMAP *button_default = "button_default.bmp";
BMAP *button_editmat = "button_editmat.bmp";
BMAP *button_editmat_def = "button_editmat_default.bmp";
BMAP *button_editmat_save = "button_editmat_savechanges.bmp";

//////////////////////////////
// functions
//////////////////////////////

// Functions do intialize
/**/void sharedGUI_rescale(PANEL *);
/**/void sharedGUI_release(STRING *);
/**/void sharedGUI_playintro(STRING *, var);
/**/void sharedGUI_blackscreen(int, int);
void sharedGUI_loadscene(STRING *);
void sharedGUI_loadbackground();
/**/void sharedGUI_loadlogo();
/**/void sharedGUI_mouse(int);
/**/void sharedGUI_mouseset(BMAP *);
/**/void sharedGUI_loadbuttons();
/**/void sharedGUI_centerpanel(PANEL *);
/**/void sharedGUI_dragpanel(PANEL *);
/**/void sharedGUI_centerfrom(PANEL *, PANEL *);

void sharedGUI_home();
void sharedGUI_prop();
void sharedGUI_mat();
void sharedGUI_editmat();
void sharedGUI_phy();

void sharedGUI_toggle_translucent();

void sharedGUI_launchsubmenu(PANEL *);
void sharedGUI_launch_terrain();
void sharedGUI_launch_object();
void sharedGUI_launch_path();

void sharedGUI_updategui(PANEL *);
void sharedGUI_closewindow(var, PANEL *);
void sharedGUI_panelselect(PANEL *);

// Functions do uninitialize
void sharedGUI__release();
void sharedGUI__loadlogo();
void sharedGUI__loadbuttons();