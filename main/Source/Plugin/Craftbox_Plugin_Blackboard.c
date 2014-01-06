
/*
--------------------------------------------------
void WriteToBlackboard(STRING *str, STRING *str2, var duration) 

Desc:

Returns: -
--------------------------------------------------
*/
void WriteToBlackboard(STRING *str, STRING *str2, var duration) {
	
	if(proc_status(WriteToBlackboard)) return; // avoid proc_kill(4).
	
	WriteLog("[ ] Writing to blackboard -> ");
	
	var dy = BORDER * 2; // adjust the destination y here
	
	if(!str_len (str) && !str_len(str2) ) {
		
		WriteLog("empty");
		NewLine();
		
		return;
		
	}
	
	TEXT *notistr = txt_create(2,1);
	while(proc_status( txt_create )) wait(1);
	
	Blackboard->pos_x = BORDER;
	Blackboard->pos_y = -bmap_height(Blackboard->bmap);
	
	notistr->font = font_create("Arial#23b");
	notistr->pos_x = Blackboard.pos_x + BORDER;
	notistr->pos_y = Blackboard.pos_y + BORDER*2.5;
	layer_sort(notistr,Blackboard->layer+1);
	
	str_cpy( (notistr.pstring) [0], str);
	str_cpy( (notistr.pstring) [1], str2);
	
	set(Blackboard,SHOW);
	set(notistr,SHOW);
	
	Blackboard->alpha = 0;
	
	while(Blackboard->pos_y <= dy ) {
		
		Blackboard->pos_y += 25 * time_step;
		notistr->pos_y = Blackboard->pos_y;
		Blackboard->alpha = GetPercent(Blackboard->pos_y, dy);
		
		wait(1);
		
	}
	
	wait(- abs(duration) );
	
	while(Blackboard->pos_y >= -bmap_height(Blackboard->bmap) ) {
		
		Blackboard->pos_y -= 25 * time_step;
		notistr->pos_y = Blackboard->pos_y;
		
		Blackboard->alpha = 100 - GetPercent(Blackboard->pos_y, -bmap_height(Blackboard->bmap) );
		
		wait(1);
		
	}
	
	reset(Blackboard,SHOW);
	reset(notistr,SHOW);
	
	str_remove( (notistr.pstring) [0] );
	str_remove( (notistr.pstring) [1] );
	txt_remove(notistr);
	
	NewLine();
	WriteLog("[X] Task completed.");
	
}