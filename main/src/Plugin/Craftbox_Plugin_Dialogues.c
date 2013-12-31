// this isn't protected from the NULL textfile - StartDialogue will handle that
void DialogueInitialize(STRING *textfile) {
	
	var dialoguehndl = file_open_read(textfile);
	if(!dialoguehndl) return;
	
	STRING *temp = "#200";
	var completed = 0;
	
	// clean the pool first
	int i = 0;
	for(; i<1000;i++) str_cpy ( (DialogueContainer.pstring)[i]," " );
	
	while( !completed ) {
	   
		file_str_readtow(dialoguehndl,temp,DialogueSentenceDelimiter,200);
		
		if( !str_stri(temp, DialogueFileEnd) ) {
			
			str_cpy((DialogueContainer.pstring) [DialogueSentencesCount] , temp);			
			DialogueSentencesCount += 1;
			
		}
		else completed = 1;
		
		wait(1);
		
	}
	
	file_close(dialoguehndl);
	
}

void StartDialogue(BMAP *DialogueInterface, BMAP *avatar, STRING *input) {
	
	if(proc_status(StartDialogue)) return;
	if(!DialogueInterface || !input) return;
	
	var createAvatar = 0;
	
	DialogueInitialize(input);
	
	PANEL *DialogueInterfacePanel = pan_create(NULL,5);
	PANEL *DialogueAvatar;
	DialogueInterfacePanel.bmap = DialogueInterface;
	DialogueInterfacePanel.flags |= (TRANSLUCENT);
	DialogueInterfacePanel.alpha = 0;
	
	DialogueInterfacePanel.pos_x = (screen_size.x - bmap_width(DialogueInterfacePanel.bmap)) / 2; 
	DialogueInterfacePanel.pos_y = screen_size.y - bmap_height(DialogueInterfacePanel.bmap) - 10 * 5 ;
	Dialogue.pos_x = DialogueInterfacePanel.pos_x + 15;
	Dialogue.pos_y = DialogueInterfacePanel.pos_y + 15;
	
	set(DialogueInterfacePanel,SHOW);
	set(Dialogue,SHOW);
	layer_sort(Dialogue,DialogueInterfacePanel->layer+5);
	
	while(DialogueInterfacePanel.alpha <= 100) {
		
		DialogueInterfacePanel.alpha += 50 * time_step;
		wait(1);
		
	}
	
	if(avatar) { // avatar is optional
		
		DialogueAvatar = pan_create(NULL,5);
		DialogueInterfacePanel.bmap = DialogueInterface;
		DialogueAvatar.bmap = avatar;
		DialogueAvatar.pos_x = DialogueInterfacePanel.pos_x + 10;
		DialogueAvatar.pos_y = DialogueInterfacePanel.pos_y - 50;
		
		Dialogue.pos_y = DialogueAvatar.pos_y + bmap_height(avatar) + 10 * 2;
		
		layer_sort(DialogueAvatar, DialogueInterfacePanel->layer+1);
		set(DialogueAvatar,SHOW);
		
		createAvatar = 1;
		
	}
	
	
	int i = 0;
	while(i < DialogueSentencesCount) {
		
		str_cpy( (Dialogue.pstring) [0], (DialogueContainer.pstring) [i] );
		
		if(key_enter || mouse_left) {
			
			while(key_enter || mouse_left) wait(1);
			i+=1;
			
		}
		
		wait(1);
		
	}
	
	DialogueSentencesCount = 0;
	

	//	str_remove( (Dialogue.pstring) [0] );
	reset(Dialogue,SHOW);
	if(createAvatar) pan_remove(DialogueAvatar);
	
	while(DialogueInterfacePanel.alpha > 0 ) {
		
		DialogueInterfacePanel.alpha -= 35 * time_step;
		wait(1);
		
	}
	pan_remove(DialogueInterfacePanel);
	
	return;
	
}