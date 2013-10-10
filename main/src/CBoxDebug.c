/*
--------------------------------------------------
CBoxDebug.c

Contains debug & statistics code, which can be toggled using the -dev 
parameter.

TODO:
<+++



>+++

NOTES:
<+++

-

>+++
--------------------------------------------------
*/

FONT *TFont = "Arial#25b";

PANEL *Statistics = {
	
	layer = 3;

	digits(0,0,99,TFont,1,manip_type); // v_objectz
	digits(0,20,99,TFont,1,TEMP_OBJECT_TYPE);
	
}

/*
--------------------------------------------------
void OpenDebug()


--------------------------------------------------
*/
void OpenDebug() {
	
	if(!is(Statistics,SHOW)) set(Statistics,SHOW);
	
}

/*
--------------------------------------------------
void CloseDebug()


--------------------------------------------------
*/
void CloseDebug() {
	
	pan_remove(Statistics);
	
}