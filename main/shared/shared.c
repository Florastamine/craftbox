
/*

[ shared.c ]

*/

//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
typedef struct obj_form {
	
	BOOL df;
	
	int _flags[8];
	var _alpha, _albedo, _ambient;
	MATERIAL *m;
	
} obj_form;

obj_form clipboard;

#define BBOX 8

#define FADE_IN 1
#define FADE_OUT 0

#define ON 1
#define OFF 0

#define BUTTON_SIZE 32
#define BORDER 10
#define SPACE BUTTON_SIZE + BORDER

#define DEFAULT_ALPHA 50

#define obj_winterbaum 0
#define obj_snowman 1
#define obj_genericwall 2
#define obj_palmtree 3
#define obj_generictree 4

#define select_mat_null 0
#define select_mat_lava 1
#define select_mat_smaragd 2
#define select_mat_marble 3

//////////////////////////////
// Strings and texts will be declared here.
//////////////////////////////
STRING *o_winterbaum = "winterbaum.mdl",
*o_snowman = "snowman.mdl",
*o_genericwall = "wall1.mdl",
*o_palmtree = "palmtree.mdl",
*o_generictree = "tree1.mdl";

STRING *current_folder = "a",
*file_selected = "a";

TEXT *files_list;

////////////////////////////////////////////////////////////
// Variables will be declared here.
////////////////////////////////////////////////////////////
int obj_type, mat_type;

int files_found, list_start;
int is_camera;

var files_already;

var v_alpha, v_ambient, v_albedo;

var button_SaveWorld_y,
button_LoadWorld_y,
button_NewWorld_y,
button_QuitWorld_y,
button_CmpWorld_y,
button_SetWorld_y;

////////////////////////////////////////////////////////////
// Panels will be declared here.
////////////////////////////////////////////////////////////
PANEL *last_pan;

PANEL *buttonlst,
*panMain_Top,
*panMain_Bottom,
*panMain_Play,
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
*debug;

////////////////////////////////////////////////////////////
// Entities will be declared here.
////////////////////////////////////////////////////////////
ENTITY *select, *fpsf_marker;

////////////////////////////////////////////////////////////
// Vectors will be declared here.
////////////////////////////////////////////////////////////
VECTOR sharedGUI_cpos1,sharedGUI_cpos2,temp_pos;

////////////////////////////////////////////////////////////
// Fonts and texts' declarations
////////////////////////////////////////////////////////////
FONT *f = "Arial#25b";

////////////////////////////////////////////////////////////
// Material declarations
////////////////////////////////////////////////////////////
MATERIAL *mat_select, *mat_temp;
MATERIAL *mat_lava, *mat_smaragd, *mat_marble;

////////////////////////////////////////////////////////////
// Bitmap declarations
////////////////////////////////////////////////////////////
BMAP* mouse = "arrow.pcx";

BMAP *button_Play = "button_play.bmp";
BMAP *button_Play_over = "button_play_over.bmp";
BMAP *button_play_off = "button_play_off.bmp";

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
BMAP *button_Close_off = "button_Close_off.bmp";
BMAP *button_Close_over = "button_Close_over.bmp";

BMAP *button_Home_newworld = "button_Home_newworld.bmp";
BMAP *button_Home_newworld_off = "button_Home_newworld_off.bmp";
BMAP *button_Home_newworld_over = "button_Home_newworld_over.bmp";

BMAP *button_Home_loadworld = "button_Home_loadworld.bmp";
BMAP *button_Home_loadworld_off = "button_Home_loadworld_off.bmp";
BMAP *button_Home_loadworld_over = "button_Home_loadworld_over.bmp";

BMAP *button_Home_saveworld = "button_Home_saveworld.bmp";
BMAP *button_Home_saveworld_off = "button_Home_saveworld_off.bmp";
BMAP *button_Home_saveworld_over = "button_Home_saveworld_over.bmp";

BMAP *button_Home_compileworld = "button_Home_compileworld.bmp";
BMAP *button_Home_compileworld_off = "button_Home_compileworld_off.bmp";
BMAP *button_Home_compileworld_over = "button_Home_compileworld_over.bmp";

BMAP *button_Home_configworld = "button_Home_configworld.bmp";
BMAP *button_Home_configworld_off = "button_Home_configworld_off.bmp";
BMAP *button_Home_configworld_over = "button_Home_configworld_over.bmp";

BMAP *button_Home_quitworld = "button_Home_quitworld.bmp";
BMAP *button_Home_quitworld_off = "button_Home_quitworld_off.bmp";
BMAP *button_Home_quitworld_over = "button_Home_quitworld_over.bmp";

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

BMAP *flag_PHY = "flag_PHY.bmp";
BMAP *flag_PHY_on = "flag_PHY_on.bmp";

BMAP *slider = "xlider.bmp";

BMAP *button_Mat1 = "button_Mat1.bmp";
BMAP *button_Mat2 = "button_Mat2.bmp";
BMAP *button_Mat3 = "button_Mat3.bmp";
BMAP *button_Mat4 = "button_Mat4.bmp";
BMAP *button_Mat5 = "button_Mat5.bmp";
BMAP *button_Mat6 = "button_Mat6.bmp";
BMAP *button_MatNorm = "button_MatNorm.bmp";

BMAP *menu1_submenu1 = "button_loadfrom.bmp";
BMAP *menu1_submenu1_off = "button_loadfrom_off.bmp";
BMAP *menu1_submenu1_over = "button_loadfrom_over.bmp";

BMAP *menu1_submenu2 = "button_saveto.bmp";
BMAP *menu1_submenu2_off = "button_saveto_off.bmp";
BMAP *menu1_submenu2_over = "button_saveto_over.bmp";

BMAP *menu1_submenu3 = "button_brusht.bmp";
BMAP *menu1_submenu3_off = "button_brusht_off.bmp";
BMAP *menu1_submenu3_over = "button_brusht_over.bmp";

BMAP *menu1_submenu4 = "button_deformt.bmp";
BMAP *menu1_submenu4_off = "button_deformt_off.bmp";
BMAP *menu1_submenu4_over = "button_deformt_over.bmp";

BMAP *menu2_submenu1 = "button_addobject.bmp";
BMAP *menu2_submenu1_off = "button_addobject_off.bmp";
BMAP *menu2_submenu1_over = "button_addobject_over.bmp";

BMAP *menu2_submenu2 = "button_addevent.bmp";
BMAP *menu2_submenu2_off = "button_addevent_off.bmp";
BMAP *menu2_submenu2_over = "button_addevent_over.bmp";

//BMAP *menu2_submenu3 = "button_submenu2_3.bmp";
//BMAP *menu2_submenu4 = "button_submenu2_4.bmp";

BMAP *menu3_submenu1 = "button_addnode.bmp";
BMAP *menu3_submenu1_off = "button_addnode_off.bmp";
BMAP *menu3_submenu1_over = "button_addnode_over.bmp";

BMAP *menu3_submenu2 = "button_nodetype.bmp";
BMAP *menu3_submenu2_off = "button_nodetype_off.bmp";
BMAP *menu3_submenu2_over = "button_nodetype_over.bmp";

//BMAP *menu3_submenu3 = "button_submenu3_3.bmp";
//BMAP *menu3_submenu4 = "button_submenu3_4.bmp";

BMAP *button_back = "button_back.bmp";
BMAP *button_back_over = "button_back_over.bmp";

BMAP *button_default = "button_default.bmp";
BMAP *button_default_off = "button_default_off.bmp";
BMAP *button_default_over = "button_default_over.bmp";

BMAP *button_editmat = "button_editmat.bmp";
BMAP *button_editmat_def = "button_editmat_default.bmp";
BMAP *button_editmat_save = "button_editmat_savechanges.bmp";

BMAP *button_matapply = "button_matapply.bmp";
BMAP *button_matapply_off = "button_matapply_off.bmp";
BMAP *button_matapply_over = "button_matapply_over.bmp";

////////////////////////////////////////////////////////////
// Function prototypes declarations
////////////////////////////////////////////////////////////
/**/void sharedGUI_rescale(PANEL *);
/**/void sharedGUI_release(STRING *);
/**/void sharedGUI_playintro(STRING *, var);
/**/void sharedGUI_blackscreen(int, int);
void sharedGUI_loadscene(STRING *);
void sharedGUI_loadbackground(STRING *);
/**/void sharedGUI_loadlogo(BMAP *);
/**/void sharedGUI_mouse(int);
/**/void sharedGUI_mouseset(BMAP *);
/**/void sharedGUI_loadbuttons();
/**/void sharedGUI_centerpanel(PANEL *);
/**/void sharedGUI_dragpanel(PANEL *);
/**/void sharedGUI_centerfrom(PANEL *, PANEL *);
void draw_bounding_box(ENTITY *);

void sharedGUI_home();
void sharedGUI_prop();
void sharedGUI_mat();
void sharedGUI_editmat();
void sharedGUI_phy();
void controlcam();

void sharedGUI_toggle_translucent();

void sharedGUI_launchsubmenu(PANEL *);
void sharedGUI_launch_terrain();
void sharedGUI_launch_object();
void sharedGUI_launch_path();

void sharedGUI_updategui(PANEL *);
void sharedGUI_closewindow(var, PANEL *);
void sharedGUI_panelselect(PANEL *);

void sharedGUI__release();
void sharedGUI__loadlogo();
void sharedGUI__loadbuttons();

void scan_folder(STRING *,STRING *);

void manipobj();
void follow_pointer();
void place_me(ENTITY *);
void restore();

void pass_to_gui(ENTITY *);
void pass_to_object();
void pass_mat_to_object();

void mat_select_lava();
void mat_select_marble();
void mat_select_smaragd();
void mat_select_null();