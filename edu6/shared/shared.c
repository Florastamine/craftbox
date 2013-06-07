
/*

[ shared.c ]

a .c file which contains many general-purpose functions that is shared among 
all available frameworks.

Contains portion of code from VLED project

*/

var enable_click;

#define	FADE_IN					1
#define	FADE_OUT					0

#define	ON							1
#define	OFF						0

#define BUTTON_SIZE 32
#define BORDER 10
#define SPACE BUTTON_SIZE + BORDER

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
