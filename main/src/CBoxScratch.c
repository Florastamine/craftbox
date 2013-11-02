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

int num = 2;
var hndl;

void play() {
	
	/*
	if(media_playing(hndl)) {
		
		printf("I'm playing something");
		return;
		
	}
	*/
	
	if(!str_cmp((music_list.pstring)[num],undef)) {
		
		/*
		
		STRING *parse = str_create("..\\sounds\\music\\");
		
		str_cat(parse,(music_list.pstring)[num]);
		str_cpy((music_list.pstring)[num],parse);
		
		hndl = media_play(parse,NULL,100);
		//		printf("%i",hndl);
		
		*/
		
		STRING *read = "#500";
		str_cpy(read,"..\\sounds\\music\\");
		str_cat(read,(music_list.pstring)[num]);
		
		TEXT *txt = txt_create(100,999);
		
		str_printf(NULL,"%s",read);
		printf("%s",read);
		
		hndl = media_play(read,NULL,100);
		
		/*
		while(media_playing(hndl)) {
			
			if(key_n) {
				
				while(key_n) wait(1);
				num++;
				
				media_playing(hndl);
				
			}
			
			if(key_p) {
				
				while(key_p) wait(1);
				num--;
				
				media_playing(hndl);
				
			}
			
			wait(1);
			
		}*/
		
	}
	
}

void a_startup() {
	
	FolderScan(music_list,"./sounds/music","ogg");
	
	on_p = play;
	
}


void LoadCBOIF(ENTITY *from) {
	
	while(!from) wait(1);
	
	/*
	
	var temp;
	STRING *CBOIF = "#200"; // this is the limit
	//   str_cpy(CBOIF, (STRING *) from->type );
	
	// LoadCBOIF uses TEMPSTR to evaluate the exact path without having to
	// do it again. Because of this: If you use LoadCBOIF in other places than 
	// CreateObject(), it won't work, because either TEMPSTR is left undefined 
	// or containing wrong data!
	str_cpy(CBOIF,TEMPSTR);
	
	str_cat(CBOIF,".cboif");
	
	var CBOIFHNDL = file_open_read(CBOIF);
	
	if(file_length(CBOIFHNDL) <= 0) {
		
		// File is empty, no need to pass anything
		file_close(CBOIFHNDL);
		
		return;
		
	}
	
	// Dirty, ugly code.
	// Don't have time to optimize them though.
	temp = file_var_read(CBOIFHNDL);
	if(temp != -1) from.scale_x = temp;
	
	temp = file_var_read(CBOIFHNDL);
	if(temp != -1) from.scale_y = temp;
	
	temp = file_var_read(CBOIFHNDL);
	if(temp != -1) from.scale_z = temp;
	
	temp = file_var_read(CBOIFHNDL);
	if(temp != -1) from.pan = temp;
	
	temp = file_var_read(CBOIFHNDL);
	if(temp != -1) from.tilt = temp;
	
	temp = file_var_read(CBOIFHNDL);
	if(temp != -1) from.roll = temp;
	
	// flags after
	// NARROW, FAT, CLIPPED, CAST, SPOTLIGHT
	// OVERLAY, DECAL, NOFILTER, SHOW/INVISIBLE,
	// ANIMATE, DYNAMIC
	
	if(file_var_read(CBOIFHNDL)) set(from,PASSABLE);
	else reset(from,PASSABLE);
	
	if(file_var_read(CBOIFHNDL)) set(from,POLYGON);
	else reset(from,POLYGON);
	
	if(file_var_read(CBOIFHNDL)) set(from,UNTOUCHABLE);
	else reset(from,UNTOUCHABLE);
	
	if(file_var_read(CBOIFHNDL)) set(from,SHADOW);
	else reset(from,SHADOW);
	
	if(file_var_read(CBOIFHNDL)) set(from,TRANSLUCENT);
	else reset(from,TRANSLUCENT);
	
	if(file_var_read(CBOIFHNDL)) set(from,BRIGHT);
	else reset(from,BRIGHT);
	
	if(file_var_read(CBOIFHNDL)) set(from,LIGHT);
	else reset(from,LIGHT);
	
	if(file_var_read(CBOIFHNDL)) set(from,UNLIT);
	else reset(from,UNLIT);
	
	if(file_var_read(CBOIFHNDL)) set(from,NOFOG);
	else reset(from,NOFOG);
	
	if(file_var_read(CBOIFHNDL)) set(from,ZNEAR);
	else reset(from,ZNEAR);
	
	//+flags
	if(file_var_read(CBOIFHNDL)) set(from,FLAG1);
	else reset(from,FLAG1);
	
	if(file_var_read(CBOIFHNDL)) set(from,FLAG2);
	else reset(from,FLAG2);
	
	if(file_var_read(CBOIFHNDL)) set(from,FLAG3);
	else reset(from,FLAG3);
	
	if(file_var_read(CBOIFHNDL)) set(from,FLAG4);
	else reset(from,FLAG4);
	
	if(file_var_read(CBOIFHNDL)) set(from,FLAG5);
	else reset(from,FLAG5);
	
	if(file_var_read(CBOIFHNDL)) set(from,FLAG6);
	else reset(from,FLAG6);
	
	if(file_var_read(CBOIFHNDL)) set(from,FLAG7);
	else reset(from,FLAG7);
	
	if(file_var_read(CBOIFHNDL)) set(from,FLAG8);
	else reset(from,FLAG8);
	
	//+skills
	int i = 30; // pass from skill 30 and up, also pass 30 skills
	var temp;
	
	while(i < 60) {
		
		temp = file_var_read(CBOIFHNDL);
		if(temp != -1) from.skill[i] = temp;
		
		i += 1;
		
		wait(1);
		
	}
	
	file_close(CBOIFHNDL);
	
	*/
	
}