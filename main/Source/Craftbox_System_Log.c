/*
--------------------------------------------------
Craftbox_System_Log.c

Functions work with log files.

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
void WriteLogHeaders()

Desc: 

Returns: -
--------------------------------------------------
*/
void WriteLogHeaders() {
	
	// couldn't use plugins here so I just evaluate some 3D Gamestudio's variables.
	NewLine();
	
	WriteLog("-- Log file opened at ");
	WriteLog("",sys_hours);
	WriteLog(": ",sys_minutes);
	WriteLog(": ",sys_seconds);
	WriteLog(",",sys_day);
	WriteLog("/ ",sys_month);
	WriteLog("/ ",sys_year);
	NewLine();
	
	switch(sys_winversion) {
		
		/*
		
		Range:
		1 - Windows 98 SE
		2 - Windows ME
		3 - Windows 2000
		4 - Windows 2003
		5 - Windows XP 
		6 - Windows Vista or above 
		
		*/
		
		case 1: WriteLog("Windows 98/98SE detected."); break;
		case 2: WriteLog("Windows ME detected."); break;
		case 3: WriteLog("Windows 2000 detected."); break;
		case 4: WriteLog("Windows 2003 detected."); break;
		case 5: WriteLog("Windows XP detected."); break;
		case 6: WriteLog("Windows Vista/7/8 detected."); break;
		default: 
		
		WriteLog("Linux or another operating system detected.");
		UNDER_MAC_OR_LINUX = 1; // mark
		break;
		
	}
	
	NewLine();
	
	WriteLog("Allocated memory: ",sys_memory*1024);
	WriteLog("KB");
	NewLine();
	
	WriteLog("Graphic card shader version (PSVS): ");
	WriteLog( str_for_num(str_create( d3d_shaderversion ), d3d_shaderversion ) );
	
	NewLine();
	
	WriteLog("Graphic card features: ");
	NewLine();
	
	WriteLog("Hardware T&L: "); WriteLog( StringForBool(d3d_caps & 1) ); NewLine();
	WriteLog("Stencil shadows: "); WriteLog( StringForBool(d3d_caps & 4) ); NewLine();
	WriteLog("Compressed textures: "); WriteLog( StringForBool(d3d_caps & 8) ); NewLine();
	
	WriteLog("Higher features: ");
	WriteLog(StringForBool(d3d_caps & 16));
	WriteLog(",");
	WriteLog(StringForBool(d3d_caps & 32));
	
	NewLine();	
}


/*
--------------------------------------------------
int WriteLog(STRING *str)


--------------------------------------------------
*/
int WriteLog(STRING *str) {

	if(LOGFILEHNDL) {
		
		file_str_write(LOGFILEHNDL,str);
		//		NewLine();
		
	}

	else return -1;

}

/*
--------------------------------------------------
int WriteLog(STRING * str, int i)


--------------------------------------------------
*/
int WriteLog(STRING * str, int i) {

	if(LOGFILEHNDL) {
		
		file_str_write(LOGFILEHNDL,str);
		file_var_write(LOGFILEHNDL,(int)i);
		//		NewLine();
		
	}

	else return -1;

}

/*
--------------------------------------------------
int WriteLog(STRING *str, var _v)


--------------------------------------------------
*/
int WriteLog(STRING *str, var _v) {

	if(LOGFILEHNDL) {
		
		file_str_write(LOGFILEHNDL,str);
		file_var_write(LOGFILEHNDL,_v);
		//		NewLine();      
		
	}

	else return -1;

}

/*
--------------------------------------------------
int WriteLog(STRING *str, double d)


--------------------------------------------------
*/
int WriteLog(STRING *str, double d) {

	if(LOGFILEHNDL) {
		
		file_str_write(LOGFILEHNDL,str);
		file_var_write(LOGFILEHNDL,(double)d);
		//		NewLine();
		
	}

	else return -1;

}

/*
--------------------------------------------------
int WriteLog(STRING *str, BOOL b)


--------------------------------------------------
*/
int WriteLog(STRING *str, BOOL b) {

	if(LOGFILEHNDL) {
		
		file_str_write(LOGFILEHNDL,str);
		
		if(b) file_str_write(LOGFILEHNDL,"true");
		else file_str_write(LOGFILEHNDL,"false");
		
		//		NewLine();
		
	}

	else return -1;

}

/*
--------------------------------------------------
int WriteLog(STRING *str, OBJECTSTRUCT *objectstruct)


--------------------------------------------------
*/
int WriteLog(STRING *str, OBJECTSTRUCT *objectstruct) {

	if(LOGFILEHNDL) {
		
		while(!objectstruct) wait(1);
		
		WriteLog("Inside ");
		WriteLog( objectstruct->name );
		NewLine();
		
		WriteLog(objectstruct->_scale_x); NewLine();
		WriteLog(objectstruct->_scale_y); NewLine();
		WriteLog(objectstruct->_scale_z); NewLine();
		WriteLog(objectstruct->_pan); NewLine();
		WriteLog(objectstruct->_tilt); NewLine();
		WriteLog(objectstruct->_roll); NewLine();
		WriteLog(objectstruct->_alpha); NewLine();
		WriteLog(objectstruct->_ambient); NewLine();
		WriteLog(objectstruct->name); NewLine();
		WriteLog(objectstruct->pPhysics); NewLine();
		WriteLog(objectstruct->pStatic); NewLine();
		
		int i = 0;
		while(i < MAX_PUBLIC_FLAGS ) {
			
			WriteLog(objectstruct->_flags[i]);
			NewLine();
			
			i++;
			
		}
		
		i = 0;
		while(i < MAX_PUBLIC_SKILLS + MAX_PRIVATE_SKILLS) {
			
			WriteLog(objectstruct->_skill[i]);
			NewLine();
			
			i++;
			
		}
		
		//		WriteLog(objectstruct->mass); NewLine();
		//		WriteLog(objectstruct->friction); NewLine();
		WriteLog(objectstruct->_red); NewLine();
		WriteLog(objectstruct->_green); NewLine();
		WriteLog(objectstruct->_blue); NewLine();
		WriteLog(objectstruct->_range); NewLine();
		WriteLog(objectstruct->_LightMode); NewLine();
		WriteLog(objectstruct->dp); NewLine();
		
		WriteLog("Raw data produced. For more information please refer to the OBJECTSTRUCT struct definition in head.h");
		NewLine();
		
	}

	else return -1;

}
