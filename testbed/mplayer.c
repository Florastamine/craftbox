#include <acknex.h>
#include <default.c>

TEXT *mlibrary;
var mplayer_songmax, mplayer_songcurr;

void mplayer_init(STRING *);
void mplayer_play(int);
void out(var);

void main(void) {
	
	level_load("");
	
	mplayer_init("../main/sounds/*.wav");
	wait_for(mplayer_init);
	
//	wait(5);
	
//	str_cpy((mlibrary.pstring)[0],"ff");
	
//	var i;
//	for(i = 0;i<4;i++) out(i);
	
	mplayer_play(2);
}

void mplayer_init(STRING *scan_path) {
	
	mlibrary = txt_create(500,1);
	mlibrary.pos_x = mlibrary.pos_y = 0;
	
	mplayer_songmax = txt_for_dir(mlibrary, scan_path);
	
	set(mlibrary,SHOW);
	
}

void mplayer_play(int id) {
	
	STRING *tmp[6000];
	str_cpy(tmp,(mlibrary.pstring)[id]);
	
	var tmphndl = media_play(tmp,NULL,100);
	printf("%i",tmphndl);
	
}

void out(var id) {
   printf("%s",(mlibrary.pstring)[id]);
}