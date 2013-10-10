/*
--------------------------------------------------
CBoxDDecl.c

Contains databases and data declarations. This file can be used to 
add and/or remove data, however it can cause unexpected side effects/
crashing if not careful. Only linear data modification is supported for
less development time, support for importing/exporting data from/to file
will be added later.

TODO:
<+++



>+++

NOTES:
<+++



>+++
--------------------------------------------------
*/

/*
--------------------------------------------------
void LoadSavedBMAPs() 


--------------------------------------------------
*/
void LoadSavedBMAPs() {
	
	save_array[0] = handle(slot1);
	save_array[1] = handle(slot2);
	save_array[2] = handle(slot3);
	save_array[3] = handle(slot4);
	save_array[4] = handle(slot5);
	save_array[5] = handle(slot6);
	save_array[6] = handle(slot7);
	save_array[7] = handle(slot8);
	save_array[8] = handle(slot9);
	//	save_array[9] = handle(slot10);
	//	save_array[10] = handle(slot11);
	//	save_array[11] = handle(slot12);
	//	save_array[12] = handle(slot13);
	//	save_array[13] = handle(slot14);
	//	save_array[14] = handle(slot15);
	//	save_array[15] = handle(slot16);
	//	save_array[16] = handle(slot17);
	//	save_array[17] = handle(slot18);
	//	save_array[18] = handle(slot19);
	//	save_array[19] = handle(slot20);
	
	game_load(pref_savebmaps,0);
	
}