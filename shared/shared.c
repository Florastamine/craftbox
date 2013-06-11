/*

[ shared.c ]

a .c file which contains many general-purpose functions.

Contains portion of code from VLED project

*/

var enable_click, is_select;
PANEL *last_pan;

#define FADE_IN 1
#define FADE_OUT 0

#define ON 1
#define OFF 0

#define BUTTON_SIZE 32
#define BORDER 10
#define SPACE BUTTON_SIZE + BORDER

#define DEFAULT_ALPHA 50

MATERIAL* mat_select = 
{
	ambient_red=255;
	ambient_green=255;
	ambient_blue=0;
	diffuse_red=255;
	diffuse_green=255;
	diffuse_blue=0;
}

FONT *f = "Arial#25b";

TEXT* files_list = 
{ 
	strings = 1000; 
	pos_x = 0;
	pos_y = 0;
	font = "Arial#25b";
	flags=SHOW;
}

int list_start;
void scan_folder(STRING *,STRING *);
/*
void main(void) {
	//	CreateDirectory("cd",0);
	scan_folder("sharedData","pcx");
}
*/
STRING *current_folder = "a", *file_selected = "a";
int files_found;var files_already;
void scan_folder(STRING* dir,STRING* ext)
{
	TEXT* read_files = {strings = 1000;}
	
	STRING* search_form = "a";

	str_cpy(current_folder,dir);

	str_cpy(search_form,dir);
	str_cat(search_form,"\\*.");
	str_cat(search_form,ext);
	
	files_found = txt_for_dir(read_files, search_form);
	
	var num = files_already;
	while(num<999)
	{
		str_cpy((files_list.pstring)[num],"");
		num+=1;
	}
	
	num=0;
	while(num<files_found)
	{
		str_cpy((files_list.pstring)[num+files_already],(read_files.pstring)[num]);
		num+=1;
	}
	list_start=0;
	
	wait(1);
}


void draw_bounding_box(ENTITY* ent)
{
	VECTOR bounding_box[BBOX];
	int i;
	for(i = 0;i < BBOX;i++) {
		vec_set(bounding_box[i],vector(ent.min_x,ent.min_y,ent.min_z));
		vec_rotate(bounding_box[i],ent.pan);
		vec_add(bounding_box[i],ent.x);
	}
	
	draw_line3d(bounding_box[0],NULL,100);
	for(i = 0;i < BBOX;i++) draw_line3d(bounding_box[i],vector(0,0,255),100);
	
	draw_line3d(bounding_box[4],vector(0,0,255),100);
	draw_line3d(bounding_box[5],vector(0,0,255),100);
	
	draw_line3d(bounding_box[2],NULL,100);
	draw_line3d(bounding_box[6],vector(0,0,255),100);
	
	draw_line3d(bounding_box[3],NULL,100);
	draw_line3d(bounding_box[7],vector(0,0,255),100);
}
