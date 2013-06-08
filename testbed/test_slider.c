#include <acknex.h>
#include "../shared/ka7def2.c" //force the app to use native default.c
var targ;

PANEL *slider = {
	hslider(10,10,100,"xlider.bmp",1,100,targ);
	digits(10,20,99,"Arial#25b",1,targ);
	flags=SHOW;
}

int main() {
	mouse_mode = 2;
	
	level_load("");
	
	while(1) {
		vec_set(mouse_pos,mouse_cursor);
		wait(1);
	}
	
	return 0;
}