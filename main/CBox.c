/*
--------------------------------------------------
CBox.c

This file is responsible for setting up the environment
and calling the main modules.

TODO:
<+++



>+++

NOTES:
<+++

There are a few things that I need to note down:

+] I defined several functions that act like switchers instead of
a single function consists of switching parameters. For example:

void foo(int toggle); // 1 = on, 0 = off - I don't use this.
void fooOn(); // I use this.
void fooOff();

1/ Panels' elements is always counted from 1. That is - always a 
positive number. Normally we use a zero or negative value to switch
off something, and guess what? Switchers-included parameters seem to 

>+++
--------------------------------------------------
*/

#include "CBox8.c"

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

#include "CBox.h"
#include "CBoxCore.c"
#include "CBoxShell.c"

void main(void)  {
	
	if(LOAD_KERNEL) {
		
		LoadKernel();
		wait_for(LoadKernel);
		
		LoopKernel();
		
	}
	else Console();
	
	on_t = UnloadKernel;
	
}