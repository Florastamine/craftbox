// 28/5/2013, 19:02 the recipe - kendrick lamar, dr.dre
// 29/5/2013, 8:00 swimming pools - kendrick lamar
// 9/6/2013, 18:04 love me - lil wayne, drake, future
//#include<acknex.h>
/*

[ sharedGUI.c ]

a .c file that defines the general-purpose GUI/HUD for use within all 
available frameworks. its kernel is located in ./sharedCustom/sharedCustom.c
*/

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