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


void LoadCBOIF(ENTITY *From) {
	
	while(!From) wait(1);
	
	var temp;
	STRING *CBOIF = str_create("#200"); // this is the limit
	//   str_cpy(CBOIF, (STRING *) From->type );
	
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
	if(temp != -1) From.scale_x = temp;
	
	temp = file_var_read(CBOIFHNDL);
	if(temp != -1) From.scale_y = temp;
	
	temp = file_var_read(CBOIFHNDL);
	if(temp != -1) From.scale_z = temp;
	
	temp = file_var_read(CBOIFHNDL);
	if(temp != -1) From.pan = temp;
	
	temp = file_var_read(CBOIFHNDL);
	if(temp != -1) From.tilt = temp;
	
	temp = file_var_read(CBOIFHNDL);
	if(temp != -1) From.roll = temp;
	
	// flags after
	// NARROW, FAT, CLIPPED, CAST, SPOTLIGHT
	// OVERLAY, DECAL, NOFILTER, SHOW/INVISIBLE,
	// ANIMATE, DYNAMIC
	
	if(file_var_read(CBOIFHNDL)) set(From,PASSABLE);
	else reset(From,PASSABLE);
	
	if(file_var_read(CBOIFHNDL)) set(From,POLYGON);
	else reset(From,POLYGON);
	
	if(file_var_read(CBOIFHNDL)) set(From,UNTOUCHABLE);
	else reset(From,UNTOUCHABLE);
	
	if(file_var_read(CBOIFHNDL)) set(From,SHADOW);
	else reset(From,SHADOW);
	
	if(file_var_read(CBOIFHNDL)) set(From,TRANSLUCENT);
	else reset(From,TRANSLUCENT);
	
	if(file_var_read(CBOIFHNDL)) set(From,BRIGHT);
	else reset(From,BRIGHT);
	
	if(file_var_read(CBOIFHNDL)) set(From,LIGHT);
	else reset(From,LIGHT);
	
	if(file_var_read(CBOIFHNDL)) set(From,UNLIT);
	else reset(From,UNLIT);
	
	if(file_var_read(CBOIFHNDL)) set(From,NOFOG);
	else reset(From,NOFOG);
	
	if(file_var_read(CBOIFHNDL)) set(From,ZNEAR);
	else reset(From,ZNEAR);
	
	//+flags
	if(file_var_read(CBOIFHNDL)) set(From,FLAG1);
	else reset(From,FLAG1);
	
	if(file_var_read(CBOIFHNDL)) set(From,FLAG2);
	else reset(From,FLAG2);
	
	if(file_var_read(CBOIFHNDL)) set(From,FLAG3);
	else reset(From,FLAG3);
	
	if(file_var_read(CBOIFHNDL)) set(From,FLAG4);
	else reset(From,FLAG4);
	
	if(file_var_read(CBOIFHNDL)) set(From,FLAG5);
	else reset(From,FLAG5);
	
	if(file_var_read(CBOIFHNDL)) set(From,FLAG6);
	else reset(From,FLAG6);
	
	if(file_var_read(CBOIFHNDL)) set(From,FLAG7);
	else reset(From,FLAG7);
	
	if(file_var_read(CBOIFHNDL)) set(From,FLAG8);
	else reset(From,FLAG8);
	
	//+skills
	
	int i = 30; // pass from skill 30 and up, also pass 30 skills
	var temp;
	
	while(i < 60) {
		
		temp = file_var_read(CBOIFHNDL);
		if(temp != -1) From.skill[i] = temp;
		
		i += 1;
		
		wait(1);
		
	}
	
	file_close(CBOIFHNDL);
	
}