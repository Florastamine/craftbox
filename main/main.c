#include "A8.c"

//////////////////////////////////////////////////////////////
#define PRAGMA_PATH "./src"
#define PRAGMA_PATH "./src/cfg"
#define PRAGMA_PATH "./src/txt"

#define PRAGMA_PATH "./2d/gui"
#define PRAGMA_PATH "./2d/tex"

#define PRAGMA_PATH "./objects/sys"
#define PRAGMA_PATH "./objects/anms"
#define PRAGMA_PATH "./objects/arch"
#define PRAGMA_PATH "./objects/blands"
#define PRAGMA_PATH "./objects/chars"
#define PRAGMA_PATH "./objects/etc"
#define PRAGMA_PATH "./objects/food"
#define PRAGMA_PATH "./objects/machs"
#define PRAGMA_PATH "./objects/plants"
#define PRAGMA_PATH "./objects/tportts"

#define PRAGMA_PATH "./sounds"
#define PRAGMA_PATH "./sounds/music"

#define PRAGMA_PATH "./levels"
//////////////////////////////////////////////////////////////


var a,b;
PANEL *t ={
	digits(40,0,99,"Arial#25b",1,a);
	digits(40,40,99,"Arial#25b",1,b);
	
	pos_x=0;
	pos_y=0;
	flags=SHOW;
}

#include "header.h"
#include "data.c"
#include "kernel.c"

void main(void)  {
	
	load_kernel("sandbox.wmb");
	loop_kernel();
	
	//	printf("%i",sizeof(var) - sizeof(int));
}