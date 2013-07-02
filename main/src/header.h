///////////////////////////////////////////////////////////
// This struct is applied to a wide range of objects.
// It can be used to copy normal objects, lights, or particle
// effects
////////////////////////////////////////////////////////////
typedef struct obj_form {
	
	////////////////////////////////////////////////////////////
	// General information that is copied regardless
	// which type the object is.
	////////////////////////////////////////////////////////////
	int oid; // Object ID
	int of_objtype; // The type of object that has been copied.
	
	var _x, _y, _z, // Do not store these vars if this is passed to the clipboard.
	_scale_x, _scale_y, _scale_z,
	_pan, _tilt, _roll,
	_alpha, _ambient;
	
	////////////////////////////////////////////////////////////
	// Unique properties each type of object has.
	////////////////////////////////////////////////////////////
	
	////////////// Normal objects (chair, mouse, salon, book...)
	BOOL pPhysics, pStatic, _flags[8];
	
	// Some vars define its physical properties
	var mass, friction;
	
	MATERIAL *m;
	
	////////////// Particle objects
	
	////////////// Light objects
	var _red, _green, _blue, _range, _flick_speed;
	int _light_mode;
	
	////////////// Sound objects
	
	BOOL dp;
	
} obj_form;

obj_form clipboard;

//////////////////////////////////////////////////////////////
#define obj_type skill1
#define light_mode skill5
#define flick_time skill6

#define FADE_IN 1
#define FADE_OUT 0

#define BORDER 10

#define DEFAULT_ALPHA 50

#define move 1
#define rotate 2
#define scale 3

#define mdl 1
#define part 2
#define light 3
#define snd 4
#define terrain_edit 5
#define node_placer 6

#define select_mat_null 15
#define select_mat_lava 1
#define select_mat_smaragd 2
#define select_mat_marble 3
#define select_mat_lavenderrose 4
#define select_mat_bitterlemon 5
#define select_mat_peachorange 6
#define select_mat_purewhite 7
#define select_mat_metal 8
#define select_mat_black 9
#define select_mat_palelilac 10

#define select_custom_mat1 11
#define select_custom_mat2 12
#define select_custom_mat3 13
#define select_custom_mat4 14

#define flick 1
#define disco 2

//////////////////////////////
// Strings and texts will be declared here.
//////////////////////////////
STRING *mdlobjs_table[1000];
STRING **mdlobjs_table_ptr;

STRING *current_folder = "a",
*file_selected = "a";

TEXT *files_list;

////////////////////////////////////////////////////////////
// Variables/Booleans will be declared here.
////////////////////////////////////////////////////////////
int mat_type, manip_type;
int files_found, list_start;

BOOL is_camera;

var files_already;

var olrange; // Old light range

var v_alpha, v_ambient,

v_ambient_r, v_ambient_g, v_ambient_b,
v_diffuse_r, v_diffuse_g, v_diffuse_b,
v_specular_r, v_specular_g, v_specular_b,
v_emissive_r, v_emissive_g, v_emissive_b,
v_power, 
v_alpha_m, // Alpha for materials

v_lred, v_lgreen, v_lblue, v_lrange;

var ctrl; // This var controls panObj_Main.

var num_mdlobjs, num_partobjs, num_lightobjs, num_sndobjs,
_obj_type, _obj_type_old;

var upper=125;

var page = 1, lfsp = 0; //launched from switch_panProp

var node = 0;

var particle_array[20];

////////////////////////////////////////////////////////////
// Panels will be declared here.
////////////////////////////////////////////////////////////
PANEL *buttonlst,
*last_pan,
*panMain_Top,
*panMain_Bottom,
*panMain_Play,
*panObj_Main,
*panObj_Subbar,
*panObj_Subbar_slider,
*panObj_Main_X,
*buttonlst_submenu_terrain,
*buttonlst_submenu_object,
*buttonlst_submenu_path,
*panHome,
*panProp,
*panProp_1,
*panProp_2,
*panProp_3,
*panMat_Sub1,
*panSnd,
*panParticle,
*_logo,
*blackscreen,
*panLight,
*debug;

////////////////////////////////////////////////////////////
// Entities will be declared here.
////////////////////////////////////////////////////////////
ENTITY *select, *fpsf_marker;

ENTITY *my_target_node;

////////////////////////////////////////////////////////////
// Vectors will be declared here.
////////////////////////////////////////////////////////////
VECTOR sharedGUI_cpos1,sharedGUI_cpos2,temp_pos;

// Vectors for dragging entities
VECTOR v1, v2;

// Vectors for backup purposes
VECTOR xy_panLight, xy_panProp, xy_panSnd, xy_panParticle;\

/*** Vectors & angles for particle effects ***/
VECTOR *parted_temp_vec = {
   
   x = 0;
   y = 0;
   z = 0;
   
}

VECTOR *parted_temp2_vec = {
   
   x = 0;
   y = 0;
   z = 0;
   
}

ANGLE *parted_temp_ang = {
   
   pan = 0;
   tilt = 0;
   roll = 0;
   
}

////////////////////////////////////////////////////////////
// Fonts and texts' declarations
////////////////////////////////////////////////////////////
FONT *f = "Arial#25b";

////////////////////////////////////////////////////////////
// Material declarations
////////////////////////////////////////////////////////////
MATERIAL *mat_select, *mat_temp;

// Predefined materials
MATERIAL *mat_lava, *mat_smaragd, *mat_marble,
*mat_lavenderrose, *mat_bitterlemon, *mat_peachorange,
*mat_purewhite, *mat_black, *mat_palelilac;

// Custom materials
MATERIAL *mat_custom[4];

////////////////////////////////////////////////////////////
// Sounds will be declared here.
////////////////////////////////////////////////////////////
SOUND *sndobjs[50];

////////////////////////////////////////////////////////////
// Bitmap declarations
////////////////////////////////////////////////////////////
BMAP* mouse = "mouse_pointer.png";

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

BMAP *flag_MOVE = "flag_MOVE.png";
BMAP *flag_MOVE_on = "flag_MOVE_on.png";

BMAP *flag_ROTATE = "flag_ROTATE.png";
BMAP *flag_ROTATE_on = "flag_ROTATE_on.png";

BMAP *flag_SCALE = "flag_SCALE.png";
BMAP *flag_SCALE_on = "flag_SCALE_on.png";

BMAP *flag_ANMS = "flag_ANMS.bmp";
BMAP *flag_ANMS_on = "flag_ANMS_on.bmp";

BMAP *flag_ARCH = "flag_ARCH.bmp";
BMAP *flag_ARCH_on = "flag_ARCH_on.bmp";

BMAP *flag_BLANDS = "flag_BLANDS.bmp";
BMAP *flag_BLANDS_on = "flag_BLANDS_on.bmp";

BMAP *flag_CHARS = "flag_CHARS.bmp";
BMAP *flag_CHARS_on = "flag_CHARS_on.bmp";

BMAP *flag_ETC = "flag_ETC.bmp";
BMAP *flag_ETC_on = "flag_ETC_on.bmp";

BMAP *flag_FOOD = "flag_FOOD.bmp";
BMAP *flag_FOOD_on = "flag_FOOD_on.bmp";

BMAP *flag_MACHS = "flag_MACHS.bmp";
BMAP *flag_MACHS_on = "flag_MACHS_on.bmp";

BMAP *flag_PLANTS = "flag_PLANTS.bmp";
BMAP *flag_PLANTS_on = "flag_PLANTS_on.bmp";

BMAP *flag_TPORTTS = "flag_TPORTTS.bmp";
BMAP *flag_TPORTTS_on = "flag_TPORTTS_on.bmp";

BMAP *flag_DISCO = "flag_DISCO.bmp";
BMAP *flag_DISCO_on = "flag_DISCO_on.bmp";

BMAP *flag_FLICK = "flag_FLICK.bmp";
BMAP *flag_FLICK_on = "flag_FLICK_on.bmp";

BMAP *slider = "slider.bmp";

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

BMAP *panObj_anms = "panObj_anms.bmp";
BMAP *panObj_arch = "panObj_arch.bmp";
BMAP *panObj_chars = "panObj_chars.bmp";
BMAP *panObj_etc = "panObj_etc.bmp";
BMAP *panObj_food = "panObj_food.bmp";
BMAP *panObj_machs = "panObj_machs.bmp";
BMAP *panObj_plants = "panObj_plants.bmp";
BMAP *panObj_tportts = "panObj_tportts.bmp";
BMAP *panObj_blands = "panObj_blands.bmp";

BMAP *panProp1_IMG = "panProp_1.bmp";
BMAP *panProp2_IMG = "panProp_2.bmp";
BMAP *panProp3_IMG = "panProp_3.bmp";

/*** For particle effects ***/
BMAP *point_blue_map = "point_blue.tga";
BMAP *sparkle1_map = "sparkle1.tga";
BMAP *fire3_map = "fire3.tga";
BMAP *fire1_map = "fire1.tga";
BMAP *blitz1_map = "blitz1.tga";
BMAP *star1_map = "star1.tga";

////////////////////////////////////////////////////////////
// Function prototypes declarations
////////////////////////////////////////////////////////////
void load_kernel(STRING *);
void loop_kernel();

/**/void sharedGUI_playintro(STRING *, var);
/**/void sharedGUI_blackscreen(int, int);
/**/void sharedGUI_loadlogo(BMAP *);
/**/void sharedGUI_mouse(BOOL);
/**/void sharedGUI_centerfrom(PANEL *, PANEL *);
void sharedGUI__loadlogo();

void pan_resize(PANEL *, char);
void pan_rotate(PANEL *,var,var,BOOL);

void home();
void editmat();
void objadd();

void prop(BOOL);
void _light(BOOL);
void _part(BOOL);
void sound(BOOL);

void controlcam();

void sharedGUI_launch_terrain();
void sharedGUI_launch_object();
void sharedGUI_launch_path();

void updategui(PANEL *);
void closewindow(var, PANEL *);
void panelselect(PANEL *);
void scan_folder(STRING *,STRING *);
void centerpanel(PANEL *);
void dragpanel(PANEL *);

void follow_pointer();

void restore();
void random_pan();

void pass_to_gui(ENTITY *);
void pass_mat_to_object();

void pass_file_to_material(MATERIAL *, STRING *);
void pass_mat_to_matsub(MATERIAL *);
void pass_material_to_file(STRING *, MATERIAL *);

void pass_object_to_clipboard(ENTITY *, obj_form *);
void pass_clipboard_to_object(ENTITY *);

void _mat_select(var); // MATERIAL *mat_select
void mat_save();

void obj_cut();
void obj_copy();
void obj_paste();

void obj_manip_setup();
void obj_manip_interface();

void switch_to_move();
void switch_to_rotate();
void switch_to_scale();
void panObj_Subbar_switcher(var);
void update_size(PANEL *, BMAP *);

ENTITY *obj_create();

void init_database();
void init_database_snd();

void loadGUI();
void hideGUI();
void showGUI();

void showr(FONT *, STRING *);

void config_write_video(STRING *);
void config_read_video(STRING *);

void a_patroller();
void a_patroller_node();

void generate_light();
void generate_sound();
void generate_waypoint();

void fix(ENTITY *);
void switch_panProp(var);

void save_level();

/*** For particle effects ***/
void New_Base_Effect_base_event(PARTICLE *);
void New_Base_Effect_base(PARTICLE *);
void Base_Effect_base_event(PARTICLE *);
void Base_Effect_base(PARTICLE *);
void Base_Effect1_base_event(PARTICLE *);
void Base_Effect1_base(PARTICLE *);
void Base_Effect2_base_event(PARTICLE *);
void Base_Effect2_base(PARTICLE *);
void Base_Effect15_base_event(PARTICLE *);
void Base_Effect15_base(PARTICLE *);
void Base_Effect14_base_event(PARTICLE *);
void Base_Effect14_base(PARTICLE *);
void Base_Effect13_base_event(PARTICLE *);
void Base_Effect13_base(PARTICLE *);
void Base_Effect12_base_event(PARTICLE *);
void Base_Effect12_base(PARTICLE *);
void Base_Effect11_base_event(PARTICLE *);
void Base_Effect11_base(PARTICLE *);
void Base_Effect3_base_event(PARTICLE *);
void Base_Effect3_base(PARTICLE *);
void New_child2_child_event(PARTICLE *);
void New_child2_child(PARTICLE *);
void New_child_child_event(PARTICLE *);
void New_child_child(PARTICLE *);
void Base_Effect4_base_event(PARTICLE *);
void Base_Effect4_base(PARTICLE *);
void New_effect1_base_event(PARTICLE *);
void New_effect1_base(PARTICLE *);
void New_child_child_event2(PARTICLE *);
void New_child_child2(PARTICLE *);
void Base_Effect_base_event2(PARTICLE *);
void Base_Effect_base2(PARTICLE *);
void Base_Effect_base_event3(PARTICLE *);
void Base_Effect_base3(PARTICLE *);
void Base_Effect1_base_event3(PARTICLE *);
void Base_Effect1_base3(PARTICLE *);
void star1_base(PARTICLE *);
void second_base(PARTICLE *);
void firstb_base_event(PARTICLE *);
void firstb_base(PARTICLE *);
void first_base_event(PARTICLE *);
void first_base(PARTICLE *);
void standard_base(PARTICLE *);
void sparkleblue_base(PARTICLE *);

void emit_spark();
void emit_colorfulspark();
void emit_spacehole();
void emit_fountain2();
void emit_fountain1();
void emit_fire2();
void emit_fire1();
void emit_doublehelix();
void emit_composition();

void p_spiral_create(VECTOR *);
void p_spark_colorful_create(VECTOR *);
void p_space_hole_create(VECTOR *);
void p_fountain_2_create(VECTOR *);
void p_fountain_1_create(VECTOR *);
void p_fire_2_create(VECTOR *);
void p_fire_1_create(VECTOR *);
void p_double_helix_create(VECTOR *);
void p_composition_create(VECTOR *);