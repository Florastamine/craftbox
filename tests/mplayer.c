#include <acknex.h>
#include <default.c>
 
/*
#define max_songs 500
var right_border;
TEXT *t;
STRING *musTable[max_songs], **musTable_ptr;

void init(STRING *);
void play(var);

void main(void) {
	
	level_load("");
	
	init("./m/*.mp3");
	wait_for(init);
	
	play(4);
	
}

STRING *vf = "#50000";

void play(var i) {
   
   str_cpy(vf,(t.pstring)[i]);
   
   var phndl = media_play(vf,NULL,100);
   
}

void init(STRING *path) {
   
   musTable_ptr = musTable;
   
   int i;
   for(i = 0;i < max_songs;i++) musTable[i] = str_create("#500");
	
	t = txt_create(max_songs,1);
	t.pos_x = t.pos_y = 0;
	
	right_border = txt_for_dir(t,path);
	
	set(t,SHOW);
	
	for(i = 0;i < right_border;i++) {
	   
	   str_cpy(musTable[i],(t.pstring)[i]);
	   
	}
}
*/

