#include <default.c>

var files_found, list_start;
var files_already;

STRING *current_folder = "a";
STRING *file_selected = "a";

TEXT *files_list = txt_create(100,1);

void FolderScan(STRING *dir, STRING *ext)
{
	TEXT *read_files = txt_create(1000,1);
	
	STRING *search_form = "a";

	str_cpy(current_folder,dir);

	str_cpy(search_form,dir);
	str_cat(search_form,"\\*.");
	str_cat(search_form,ext);
	
	files_found = txt_for_dir(read_files, search_form);
	
	var num = files_already;
	while(num<999)
	{
		str_cpy((files_list.pstring)[num],"");
		num++;
	}
	
	num=0;
	while(num<files_found)
	{
		str_cpy((files_list.pstring)[num+files_already],(read_files.pstring)[num]);
		num++;
	}
	list_start=0;
	
	wait(1);
}

void main(void) {
	
}