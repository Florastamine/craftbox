/*
--------------------------------------------------
CBoxScratch.c

A place for temporary, experimental, unstable code.

TODO:
<+++



>+++

NOTES:
<+++

-

>+++
--------------------------------------------------
*/

ENTITY *SkyCube = {
	
	type = "./2d/skies/s_s_greenland+6.tga";
	
	flags2 = SKY | CUBE | SHOW;
	
}

void main(void) {
	
	random_seed(0);
	
	level_load(NULL);
}