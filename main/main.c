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

#include "header.h"
#include "data.c"
#include "kernel.c"

void main(void)  {
   
   skCube=1;
	
	load_kernel("");
	loop_kernel();
	
}