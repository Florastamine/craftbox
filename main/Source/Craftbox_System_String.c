#ifndef Craftbox_System_String

#define Craftbox_System_String

/*
--------------------------------------------------
Craftbox_System_String.c

String functions for passing user requests (normally from the GUI).

Written by Nguyen Ngoc Huy
https://github.com/ngochuy2101
http://craftboxdev.blogspot.com/

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
void PassToSKYSTR(var position)

Desc:

Returns: -
--------------------------------------------------
*/
void PassToSKYSTR(var position) {
	
	if(event_type == EVENT_RELEASE) return;
	
	WriteLog("[ ] Passing information from the input box to SKYSTR");
	
	// I don't care 'bout blank spaces 'cause all of them have been flooded
	// with undef.
	int absposition = position - 1;
	if(!str_cmp( (files_list_SKYSTR.pstring) [absposition], undef ) ) {
		
		str_cpy(SKYSTR, PATH_SKIES);
		str_cat(SKYSTR, (files_list_SKYSTR.pstring) [absposition] );
		
		WriteLog("copied "); WriteLog(SKYSTR);
		NewLine();		
		
	}
	
	WriteLog("[X] Task completed.");
	NewLine();
	
}

/*
--------------------------------------------------
void PassToGROUNDSTR(var position)

Desc:

Returns: -
--------------------------------------------------
*/
void PassToGROUNDSTR(var position) {
	
	if(event_type == EVENT_RELEASE) return;
	
	WriteLog("[ ] Passing information from the input box to GROUNDSTR");
	NewLine();
	
	int absposition = position - 1;
	if( !str_cmp((files_list_GROUNDSTR.pstring) [absposition], undef) ) {
		
		str_cpy(GROUNDSTR,PATH_GROUNDS);
		str_cat(GROUNDSTR,(files_list_GROUNDSTR.pstring) [absposition]);
		
		WriteLog("copied "); WriteLog(GROUNDSTR);
		NewLine();
		
		
	}
	
	WriteLog("[X] Task completed.");
	NewLine();
	
}

/*
--------------------------------------------------
void PassToLOADGAMESTR(var position)

Desc:

Returns: -
--------------------------------------------------
*/
void PassToLOADGAMESTR(var position) {
	
	if(event_type == EVENT_RELEASE) return;
	
	WriteLog("[ ] Passing information from the input box to LOADGAMESTR");
	
	int absposition = position - 1;
	if( !str_cmp((files_list_LOADGAMESTR.pstring) [absposition], undef) ) {
		
		str_cpy(LOADGAMESTR, PATH_SAVEDGAMES);
		str_cat(LOADGAMESTR,(files_list_LOADGAMESTR.pstring) [absposition]);
		
		WriteLog("copied "); WriteLog(LOADGAMESTR);
		NewLine();
		
	}
	
	WriteLog("[X] Task completed.");
	NewLine();
	
}

#endif