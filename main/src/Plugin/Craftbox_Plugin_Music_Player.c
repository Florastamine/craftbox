
/*
--------------------------------------------------
void ToggleMusicPlayer()

Desc:

Returns: -
--------------------------------------------------
*/
void ToggleMusicPlayer() {
	
	if(is(MusicPlayer,SHOW)) {
		
		reset(MusicPlayer,SHOW);
		reset(MusicPlayerInfo,SHOW);
		
		return;
		
	}
	
	set(MusicPlayer,SHOW);
	set(MusicPlayerInfo,SHOW);
	
	while(is(MusicPlayer,SHOW)) {
		
		MusicPlayerInfo.pos_x = MusicPlayer.pos_x + 170;
		MusicPlayerInfo.pos_y = MusicPlayer.pos_y + 130;
		
		wait(1);
		
	}	
}

/*
--------------------------------------------------
void mpLoad(STRING *scan_path, STRING *scan_ext)

Desc:

Returns: -
--------------------------------------------------
*/
void mpLoad(STRING *scan_path, STRING *scan_ext) {
	
	WriteLog("[ ] Scanning for external music...");
	
	STRING *_scan_path = str_create(scan_path); // Prevent modification of the original string
	
	mpSongs = txt_for_dir(mpPool, str_cat(_scan_path,scan_ext) );
	while(proc_status(txt_for_dir)) wait(1);
	
	str_remove(_scan_path);
	
	WriteLog(", found " , (var) mpSongs ); // 
	WriteLog(" tracks.");
	NewLine();
	
	WriteLog("[X] Task completed.");
	NewLine();
	
}

/*
--------------------------------------------------
void mpPlay(STRING *songName)

Desc:

Returns: -
--------------------------------------------------
*/
void mpPlay(STRING *songName) {
	
	WriteLog("[ ] Now playing: ");
	
	if(media_playing(mpHandle)) media_stop(mpHandle);
	if(mpCount > mpSongs - 1 || mpCount < 0) return;
	
	str_cpy(_mpSongTemp,songName);
	str_trunc(_mpSongTemp, str_len(EXT_MUSIC)-1 ); // because our four chars are: .ogg
	
	WriteLog(_mpSongTemp);
	NewLine();
	
	str_cpy(mpSongTemp,PATH_MUSIC);
	str_cat(mpSongTemp,songName);
	
	str_for_num(_mpCount, mpCount); // strcpy is unnecessary here
	
	mpHandle = media_play(mpSongTemp,NULL,VOL_MUSIC);
	
	while(media_playing(mpHandle)) wait(1);
	mpNext();
	
}

/*
--------------------------------------------------
void mpNext() 

Desc:

Returns: -
--------------------------------------------------
*/
void mpNext() {
	
	if(event_type == EVENT_RELEASE) return;
	
	if(mpCount < mpSongs) {
		
		if(mpRandomize) mpCount = (int) random(mpSongs);
		else mpCount += 1;
		mpPlay( (mpPool.pstring)[mpCount] );
		
	}
	
}

/*
--------------------------------------------------
void mpPrev()

Desc:

Returns: -
--------------------------------------------------
*/
void mpPrev() {
	
	if(event_type == EVENT_RELEASE) return;
	
	if(mpCount >= 0) {
		
		if(mpRandomize) mpCount = (int) random(mpSongs);
		else mpCount -= 1;
		mpPlay( (mpPool.pstring)[mpCount] );
		
	}
	
}

/*
--------------------------------------------------
void mpPause() 

Desc:

Returns: -
--------------------------------------------------
*/
void mpPause() {
	
	if(event_type == EVENT_RELEASE) return;
	
	if(media_playing(mpHandle)) {
		
		media_pause(mpHandle);
		mpPauseMark = 1;
		
	}
	
}

/*
--------------------------------------------------
void mpResume()

Desc:

Returns: -
--------------------------------------------------
*/
void mpResume() {
	
	if(event_type == EVENT_RELEASE) return;
	
	if(mpPauseMark) media_start(mpHandle);
	
}
