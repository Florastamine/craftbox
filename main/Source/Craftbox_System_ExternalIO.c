#ifndef Craftbox_System_ExternalIO

#define Craftbox_System_ExternalIO

/*
--------------------------------------------------
Craftbox_System_ExternalIO.c

Provides functions for communicating with external data sources
( config. file, load/save structs from/to file for example. )

Contains INI functions from the TUST library (ini.h)

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
void FolderScan(TEXT *filler, STRING *dir, STRING *ext)

Desc: Did a little optimization here - the string clearing 
is redundant, because str_cpy will automatically overwrites 
string while writing from source.

27.10.2013: Added a simple extension that fills undef char to the text object

Returns: -
--------------------------------------------------
*/
void FolderScan(TEXT *filler, STRING *dir, STRING *ext)
{
	
	WriteLog("[ ] Scanning folder ");
	WriteLog( dir );
	WriteLog(" for all ");
	WriteLog(ext);
	WriteLog(" files.");
	NewLine();
	
	while(!filler) wait(1); // wait for our customer
	
	TEXT *read_files = txt_create(filler.strings,1);
	
	STRING *search_form = "a";

	str_cpy(current_folder,dir);
	str_cpy(search_form,dir);
	str_cat(search_form,"\\*.");
	str_cat(search_form,ext);
	
	files_found = txt_for_dir(read_files, search_form);
	
	var num = 0;
	
	while(num<files_found)
	{
		str_cpy((filler.pstring)[num+files_already],(read_files.pstring)[num]);
		num++;
	}
	list_start=0;
	
	if(files_found < filler.strings) {
		
		while(files_found < filler.strings) {
			
			str_cpy( (filler.pstring) [(int) files_found], undef);
			files_found += 1;
			
		}
		
	}
	
	WriteLog("[X] Task completed for FolderScan(TEXT *filler, STRING *dir, STRING *ext).");
	NewLine();
	
}


/*
--------------------------------------------------
int ConfigFileWrite(STRING *cf)

Desc: Writes engine variables to "cf" ( [c]onfig [f]ile ).

Returns: -1 if "cf" couldn't be opened.
--------------------------------------------------
*/
int ConfigFileWrite(STRING *cf) {
	
	WriteLog("[ ] Writing current configuration to file (");
	WriteLog(cf);
	WriteLog(")");
	NewLine();

	var file = file_open_write(cf);
	
	if(!file) {
		
		_beep();
		
		WriteLog("!! [ERROR] The file couldn't be opened, returns -1.");
		NewLine();
		
		return -1;
		
	}

	/*

	Follow this form:

	These variables won't be saved and loaded:
	- d3d_alphadepth
	- d3d_shadowdepth
	- d3d_texdepth 
	- d3d_skydepth

	These variables will be saved/loaded from the .cfg file:
	- d3d_anisotropy
	- d3d_antialias
	- d3d_mipmapping
	- d3d_triplebuffer
	- d3d_lightres
	- video_aspect
	- video_gamma
	- sys_metrics(0), sys_metrics(1)
	- video_depth
	- video_screen

	*/

	// -> Graphics + system
	file_var_write(file,defaultConfig.AFLevel);
	file_var_write(file,defaultConfig.AALevel);
	file_var_write(file,d3d_mipmapping);
	file_var_write(file,d3d_triplebuffer);
	file_var_write(file,d3d_lightres);
	file_var_write(file,video_aspect);
	file_var_write(file,defaultConfig.Brightness);

	//	file_var_write(file,video_mode);
	//	file_var_write(file,sys_metrics(0));
	//	file_var_write(file,sys_metrics(1));
	file_var_write(file,sResX);
	file_var_write(file,sResY);

	file_var_write(file,video_screen);

	file_var_write(file,defaultConfig.BitDepth);

	file_var_write(file,shot);

	// -> Sound effects' volume
	file_var_write(file,VOL_EFFECTS);
	file_var_write(file,VOL_MUSIC);

	// -> Shaders + PPs parameters
	file_var_write(file,defaultConfig.HDR);
	file_var_write(file,defaultConfig.DOF);
	file_var_write(file,defaultConfig._SSAO);
	file_var_write(file,defaultConfig.ObjShaders);
	file_var_write(file,defaultConfig.Shadows);
	file_var_write(file,defaultConfig.PPE);

	file_close(file);
	
	WriteLog("[X] Task completed.");
	NewLine();

}

/*
--------------------------------------------------
int ConfigFileRead(STRING *cf)

Desc: Reads engine variables from "cf" ( [c]onfig [f]ile ). 
This function must be called prior to loading the kernel.

Returns: -1 if "cf" couldn't be opened - default settings will 
then be used.
--------------------------------------------------
*/
int ConfigFileRead(STRING *cf) {
	
	WriteLog("[ ] Reading configuration from ");
	WriteLog(cf);
	NewLine();

	var file = file_open_read(cf);
	if(!file) { // Fail? Then use default settings.
		
		_beep();
		
		WriteLog("! [ERROR] The file couldn't be opened, returns -1.");
		NewLine();
		WriteLog("! Will now use default configuration.");
		NewLine();
		
		/* Default config. goes here. */
		video_depth = 32;
		video_set(sys_metrics(0),sys_metrics(1),0,1);
		// other settings remain default (in the game engine/library)
		
		return -1;
		
	}

	// -> Graphics + system
	defaultConfig.AFLevel = file_var_read(file);
	defaultConfig.AALevel = file_var_read(file);
	d3d_mipmapping = file_var_read(file);
	d3d_triplebuffer = file_var_read(file);
	d3d_lightres = file_var_read(file);
	video_aspect = file_var_read(file);
	defaultConfig.Brightness = file_var_read(file);
	
	sResX = file_var_read(file);
	sResY = file_var_read(file);
	sResMode = file_var_read(file);
	defaultConfig.BitDepth = file_var_read(file);

	//	video_set( file_var_read(file), file_var_read(file),

	shot = file_var_read(file);

	// -> Sound effects' volume
	VOL_EFFECTS = file_var_read(file);
	VOL_MUSIC = file_var_read(file);

	// -> Shaders + PPs parameters
	defaultConfig.HDR = /*(int)*/file_var_read(file);
	defaultConfig.DOF = /*(int)*/file_var_read(file);
	defaultConfig._SSAO = /*(int)*/file_var_read(file);
	defaultConfig.ObjShaders = /*(int)*/file_var_read(file);
	defaultConfig.Shadows = /*(int)*/file_var_read(file);
	defaultConfig.PPE = /*(int)*/file_var_read(file);

	file_close(file);
	
	WriteLog("[X] Task completed.");
	NewLine();

}

/** -> Here goes INI functions **/
void ini_write(STRING *filename, STRING *section, STRING *entry, STRING *value)
{	
	WritePrivateProfileString(_chr(section), _chr(entry), _chr(value), _chr(filename));
}

void ini_write_int(STRING *filename, STRING *section, STRING *entry, int value)
{
	ini_write(filename, section, entry, str_for_int(NULL, value));
}

void ini_write_var(STRING *filename, STRING *section, STRING *entry, var value)
{
	ini_write(filename, section, entry, str_for_num(NULL, value));
}

void ini_write_float(STRING *filename, STRING *section, STRING *entry, float value)
{
	ini_write(filename, section, entry, str_for_float(NULL, value));
}

int ini_read_sections(TEXT *txt, STRING *filename)
{	
	int length = GetPrivateProfileString(NULL, NULL, NULL, iniBuffer, 2047, _chr(filename));
	int i = 0;
	char *str = iniBuffer;
	while(str < (iniBuffer + length))
	{
		(txt->pstring)[i] = str_create(str);
		str = str + strlen(str) + 1;
		i++;
	}
	return i;
}

int ini_read(STRING *targetValue, STRING *filename, STRING *section, STRING *entry, STRING *defaultValue)
{	
	int length = GetPrivateProfileString(_chr(section), _chr(entry), _chr(defaultValue), iniBuffer, 2047, _chr(filename));
	if(targetValue != NULL)
		str_cpy(targetValue, iniBuffer);
	return length;
}

int ini_read_int(STRING *filename, STRING *section, STRING *entry, int defaultValue)
{
	STRING *tmp = "#64";
	STRING *def = "#64";
	ini_read(tmp, filename, section, entry, str_for_int(def, defaultValue));
	return str_to_int(tmp);
}

var ini_read_var(STRING *filename, STRING *section, STRING *entry, var defaultValue)
{
	STRING *tmp = "#64";
	STRING *def = "#64";
	ini_read(tmp, filename, section, entry, str_for_num(def, defaultValue));
	return str_to_num(tmp);
}

float ini_read_float(STRING *filename, STRING *section, STRING *entry, float defaultValue)
{
	STRING *tmp = "#64";
	STRING *def = "#64";
	ini_read(tmp, filename, section, entry, str_for_float(def, defaultValue));
	return str_to_float(tmp);
}
/** <- **/

/*
--------------------------------------------------
bool bmap_savetga (BMAP* b, char* filename)

Desc: By HeelX (http://www.opserver.de/ubb7/ubbthreads.php?ubb=showflat&Number=421231#Post421231)

Saves a bitmap as tga file.

Some users reported that they can't properly save a bitmap as TGA with bmap_save, because the bitmap gets mirrored. 
This is due the fact that TGA stores a handedness flag that defines if the image origin is in the upper- or lower left corner 
I found out, that if you set the flag in the TGA, that indicates the origin in the lower left corner, and you write the image upside down into the file, the bitmap is saved correctly and is loaded correctly back into the engine.

So I have written the following function "bmap_savetga" a while ago (inspired by ventilator's C-Script in the wiki) in Lite-C for another project to circumvent the upside-down problem; 
it also saves the alpha channel in the TGA, if and only if the passed BMAP* has an alpha channel, too; otherwise the TGA just saves RGB data.

Returns: -
--------------------------------------------------
*/
bool bmap_savetga (BMAP* b, char* filename)
{
	bool bSuccess = false;

	if (b && filename && strlen(filename) > 0)
	{
		var fh = file_open_write(filename);
		if (fh)
		{
			int height = b->height;
			int width = b->width;

			var format = bmap_lock(b, 0);

			// if the bitmap has an alpha channel
			bool bAlpha = (((format == 8888) || (format == 1555) || (format == 4444)) && (b->bytespp == 4));

			// header

			int i;
			for (i = 0; i < 2; i++)
			file_asc_write(fh, 0);

			file_asc_write(fh, 2); // uncompressed

			for (i = 0; i < 7; i++)
			file_asc_write(fh, 0);

			// y origin (lower left corner)
			file_asc_write(fh, height & 255);
			file_asc_write(fh, (height >> 8) & 255);

			file_asc_write(fh, width & 255);
			file_asc_write(fh, (width >> 8) & 255);

			file_asc_write(fh, height & 255);
			file_asc_write(fh, (height >> 8) & 255);
			
			int bypp = 24;
			if (bAlpha)
			bypp = 32;

			file_asc_write(fh, bypp); // bypp
			file_asc_write(fh, 0);

			// pixels

			COLOR bgr;
			var alpha;

			int ix, iy;
			for (iy = 0; iy < height; iy++)
			{
				for (ix = 0; ix < width; ix++)
				{
					// retrieve BGR color and alpha
					pixel_to_vec(&bgr, &alpha, format, pixel_for_bmap(b, ix, height - 1 - iy));

					file_asc_write(fh, bgr.blue); // b
					file_asc_write(fh, bgr.green); // g
					file_asc_write(fh, bgr.red); // r

					if (bAlpha)
					file_asc_write(fh, alpha * 2.55); // a
				}
			}

			// done!
			bmap_unlock(b);
			file_close(fh);

			bSuccess = true;
		}
	}

	return(bSuccess);
}


#endif