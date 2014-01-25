#ifndef Craftbox_System_Log

#define Craftbox_System_Log

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

+ [20/1/2014]: There's a HTML logging library in TUST already, 
but I had problem integrating it into craftbox, plus, the way 
this library works is a lot different from the original built-in logging 
library which I wrote for craftbox. So I decided to do a totally rewrite, not using 
any original code from that library but the idea.

The original library can be found by unzipping Craftbox_System_Log.zip.

LOGFILEHNDL is now internal. For convenience and safety just use OpenLog() and CloseLog().

+[24/1/2014]: Support for the old logging method, which can be toggled by commenting USE_TXT_LOG in Craftbox.h

>+++
--------------------------------------------------

*/

void hVar(STRING *str, int i) { // This function is used for writing information to txt headers

	// At this time LOGFILEHNDL has already been opened..so no check
	sprintf(compose_target,"%s %d",str, (long) i );
	file_str_write(LOGFILEHNDL,compose_target); 
	
}

/*
--------------------------------------------------
void NewLine()

Desc: Writes a new line to LOGFILEHNDL.
NewLine() is only useful for txt logs.

Returns: -
--------------------------------------------------
*/
void NewLine() {
	
	#ifdef USE_TXT_LOG
		// Windows uses CR/LF
		file_asc_write(LOGFILEHNDL,13); // CR
		file_asc_write(LOGFILEHNDL,10); // LF
	#endif

}

/*
--------------------------------------------------
void NewLine(var _HANDLE)

Desc:

Returns: -
--------------------------------------------------
*/
void NewLine(var _HANDLE) {
	
	if(!_HANDLE) return;
	file_asc_write(_HANDLE,13);
	file_asc_write(_HANDLE,10);
	
}


/*
--------------------------------------------------
STRING *StringForBool(var in)

Desc: This was created specifically for WriteLogHeaders()...

Returns: Converted input.
--------------------------------------------------
*/
STRING *StringForBool(var in) {
	
	if(in) return str_create("Yes");
	else return str_create("No");
	
}

void OpenLog (STRING *LogFile) {
	
	if(LOGFILEHNDL) return;
	
	#ifndef USE_TXT_LOG
		
		LOGFILEHNDL = file_open_append(LogFile);
		
		file_str_write(LOGFILEHNDL,"<html><title>craftbox log file</title>"); // html head + title + no tag "</html>"
		file_str_write(LOGFILEHNDL,"<head><b><u>craftbox log file</u></b></head><br><br>"); // head
		
		file_str_write(LOGFILEHNDL,"<h1><b><font size=\"10\">craftbox log file</font></b></h1>"); // the real header
		file_str_write(LOGFILEHNDL,"<b>");
		
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
			
			case 1: file_str_write(LOGFILEHNDL,"Windows 98/98SE detected."); break;
			case 2: file_str_write(LOGFILEHNDL,"Windows ME detected."); break;
			case 3: file_str_write(LOGFILEHNDL,"Windows 2000 detected."); break;
			case 4: file_str_write(LOGFILEHNDL,"Windows 2003 detected."); break;
			case 5: file_str_write(LOGFILEHNDL,"Windows XP detected."); break;
			case 6: file_str_write(LOGFILEHNDL,"Windows Vista/7/8 detected."); break;
			default: 
			
			file_str_write(LOGFILEHNDL,"Linux or another operating system detected.");
			//			UNDER_MAC_OR_LINUX = 1; // mark
			break;
			
		}
		
		file_str_write(LOGFILEHNDL,"</b><br><b>Allocated memory:</b> ");
		file_var_write(LOGFILEHNDL,sys_memory*1024);
		file_str_write(LOGFILEHNDL,"KB<br>");
		
		file_str_write(LOGFILEHNDL,"<b>Graphic card shader version (PSVS): </b>");
		file_str_write(LOGFILEHNDL, str_for_num(str_create( d3d_shaderversion ), d3d_shaderversion ) );
		file_str_write(LOGFILEHNDL,"<br>");
		
		file_str_write(LOGFILEHNDL,"<b>Graphic card features:</b><br> ");
		
		file_str_write(LOGFILEHNDL,"Hardware T&L: ");
		file_str_write(LOGFILEHNDL, StringForBool(d3d_caps & 1) ); 
		file_str_write(LOGFILEHNDL,"<br>");
		
		file_str_write(LOGFILEHNDL,"Stencil shadows: ") ;
		file_str_write(LOGFILEHNDL,StringForBool(d3d_caps & 4) );
		file_str_write(LOGFILEHNDL,"<br>");
		
		file_str_write(LOGFILEHNDL,"Compressed textures: ");
		file_str_write(LOGFILEHNDL,StringForBool(d3d_caps & 8) );
		file_str_write(LOGFILEHNDL,"<br>");
		
		file_str_write(LOGFILEHNDL,"Higher features: ");
		file_str_write(LOGFILEHNDL,StringForBool(d3d_caps & 16));
		file_str_write(LOGFILEHNDL,",");
		file_str_write(LOGFILEHNDL,StringForBool(d3d_caps & 32));
		file_str_write(LOGFILEHNDL,"<br>");
		
		file_str_write(LOGFILEHNDL,GenerateDateTime());
		file_str_write(LOGFILEHNDL,"<br><body><table border = \"1\"><br>"); // eol + body tag + table tag (no 2 tag)
		file_str_write(LOGFILEHNDL,"<tr><th>Date/Time</th><th>Notification</th></tr>");
		
		#else 
		
		LOGFILEHNDL = file_open_append(LogFile);
		while(proc_status(file_open_append)) wait(1);
		
		WriteLogHeaders();
		
	#endif
	
}

void CloseLog() {
	
	if(LOGFILEHNDL) { // just in case
		
		#ifndef USE_TXT_LOG
			file_str_write(LOGFILEHNDL,"</table></body></html>");
		#endif
		
		file_close(LOGFILEHNDL);
		
	}
	
}

char *GenerateDateTime() {
	
	char DateTime[150];
	sprintf(DateTime, "%d:%d:%d,%d/%d/%d", (int)sys_hours, (int)sys_minutes, (int)sys_seconds, (int)sys_day, (int)sys_month, (int)sys_year);
	
	return DateTime;
	
}

// Core function to write content to HTML
void PutToHTML(char *content) {
	
	if(LOGFILEHNDL) {
		
		file_str_write(LOGFILEHNDL,"<tr><th><i>");
		file_str_write(LOGFILEHNDL, GenerateDateTime() );
		file_str_write(LOGFILEHNDL,"</i><th>");
		file_str_write(LOGFILEHNDL,content);
		file_str_write(LOGFILEHNDL,"</th></tr>");
		
	}
	
}

////////////////////////////////////////////////////////////
// Just for general types
////////////////////////////////////////////////////////////
void WriteLog(STRING *str) {
	
	#ifndef USE_TXT_LOG
		PutToHTML(str);
		#else
		if(LOGFILEHNDL) file_str_write(LOGFILEHNDL,str);
	#endif
	
}

void WriteLog(int _int) {
	
	#ifndef USE_TXT_LOG
		PutToHTML(str_for_int(str_create(_int),_int));
		#else
		if(LOGFILEHNDL) file_var_write(LOGFILEHNDL,(int) _int) ;
	#endif

}

void WriteLog(var _var) {
	
	#ifndef USE_TXT_LOG
		PutToHTML(str_for_num(str_create(_var),_var));
		#else
		if(LOGFILEHNDL) file_var_write(LOGFILEHNDL,_var);
	#endif
	
}

void WriteLog(float _float) {
	
	#ifndef USE_TXT_LOG
		PutToHTML(str_for_float(str_create(_float),_float));
		#else
		WriteLog( (var)_float );
	#endif
	
}

void WriteLog(double _double) {
	
	#ifndef USE_TXT_LOG
		PutToHTML(str_for_float(str_create(_double),_double)); 
		#else
		WriteLog( (var)_double );
	#endif
	
}

void WriteLog(VECTOR *vektor) {
	
	sprintf(compose_target,"(%d,%d,%d)",(long)(vektor->x),(long)(vektor->y),(long)(vektor->z));
	WriteLog(compose_target);
	
}

void WriteLog(ANGLE *angle) {
	
	sprintf(compose_target,"(pan = %d, tilt = %d, roll = %d)",(long)(angle->pan), (long)(angle->tilt),(long)(angle->roll));
	WriteLog(compose_target);
}

////////////////////////////////////////////////////////////
// Strings combined with different data types
////////////////////////////////////////////////////////////
void WriteLog(STRING *str, int i) {
	
	if(!str) {
		
		WriteLog(i);
		return;
		
	}

	str_cat(str_cpy(holder,str),str_for_int(holder_num,i));
	
}

void WriteLog(STRING *str, VECTOR *vektor) {
	
	if(!str && vektor) {
		
		WriteLog(vektor);
		return;
		
	}
	
	str_cat(str_cpy(holder,str),"(");
	
	str_for_float(holder_num,vektor->x);
	str_cat(holder,str_cat(holder_num,";"));
	
	str_for_float(holder_num,vektor->y);
	str_cat(holder,str_cat(holder_num,";"));
	
	str_for_float(holder_num,vektor->z);
	str_cat(holder,str_cat(holder_num,")"));
	
	WriteLog(holder);
	
	/*
	
	// compose a string from a vector
	sprintf(compose_target,"%s = (%d,%d,%d)",str,(long)(vektor->x),(long)(vektor->y),(long)(vektor->z));
	WriteLog(compose_target);
	
	*/
	
}

void WriteLog(STRING *str, var _var) {
	
	if(!str) {
		
		WriteLog(_var);
		return;
		
	}
	
	WriteLog(str_cat(str_cpy(holder,str),str_for_float(holder_num,_var)));
	
	/*
	
	//	sprintf(compose_target,"%s = %d",str,(long)_var);
	sprintf(compose_target,"%s %s",str,str_for_float(str_create("#10"),_var));
	
	WriteLog(compose_target);
	
	*/
	
}

void WriteLog(STRING *str, float f) {
	
	if(!str) {
		
		WriteLog(f);
		return;
		
	}
	
	WriteLog(str_cat(str_cpy(holder,str),str_for_float(holder_num,f)));
	
}

void WriteLog(STRING *str, double d ) { WriteLog(str,(float)d); }

void WriteLog(STRING *str, int i) {
	
	if(!str) {
		
		WriteLog(i);
		return;
		
	}
	
	WriteLog(str_cat(str_cpy(holder,str),str_for_int(holder_num,i)));
	
}

void WriteLog(STRING *str, ANGLE *_ang) {
	
	if(!str) {
		
		WriteLog(_ang);
		return;
		
	}
	
	str_cat(str_cpy(holder,str),"(");
	
	str_for_float(holder_num,_ang->pan);
	str_cat(holder,str_cat(holder_num,";"));
	
	str_for_float(holder_num,_ang->tilt);
	str_cat(holder,str_cat(holder_num,";"));
	
	str_for_float(holder_num,_ang->roll);
	str_cat(holder,str_cat(holder_num,")"));
	
	WriteLog(holder);
	
}

/*
--------------------------------------------------
void WriteLogHeaders()

Desc: [24/1/2013]: Black night. Added back to the 
logging library for maintaining the old logging style.

Returns: -
--------------------------------------------------
*/
void WriteLogHeaders() {
	
	// couldn't use plugins here so I just evaluate some 3D Gamestudio's variables.
	NewLine();
	
	WriteLog("-- Log file opened at ");
	hVar("",sys_hours);
	hVar(": ",sys_minutes);
	hVar(": ",sys_seconds);
	hVar(",",sys_day);
	hVar("/ ",sys_month);
	hVar("/ ",sys_year);
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
	
	hVar("Allocated memory: ",sys_memory*1024);
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
	
	#ifdef CBOX_DEVELOPMENT
		
		WriteLog("--Development build--");
		NewLine();
		
	#endif
	
}

#endif