
/*
--------------------------------------------------
int Console()

Desc: Available only if the kernel isn't running. 
Used for checking variables' values and/or executing 
engine functions. For the convenience, I defined several 
Con*() functions which perform various tasks without the need 
to enter a long list of commands.

To call this function properly, you must first call UnloadKernel(), 
because the console runs only if the kernel isn't running (as stated before).

Returns: -1 if the kernel is currently running.
--------------------------------------------------
*/
int Console() {

	WriteLog("[SYS] Trying to start the console...");
	NewLine();

	if(KERNEL_IS_RUNNING) {
		
		_beep();
		
		WriteLog("! [ERROR] Console couldn't be executed while the kernel is running, returns -1.");
		NewLine();
		
		return -1;
		
	}
	
	WriteLog("[SYS] Setup console...");

	ConsoleText->pos_x = 2;
	ConsoleText->pos_y = screen_size.y/4;
	toggle(ConsoleText,SHOW);

	// Additional WriteLogs here.

	while(!KERNEL_IS_RUNNING) {
		
		inkey((ConsoleText->pstring)[1]);
		
		if (result == CINPUT_ENTER) { // [Enter]
			
			void* found = var_for_name((ConsoleText->pstring)[1]);
			if (!found) execute((ConsoleText->pstring)[1]);
			
		}
		
		if(result == CINPUT_ESC) { // [Esc]
			
			str_cpy((ConsoleText->pstring)[1],"Loading kernel...");
			
			LoadKernel();
			while(proc_status(LoadKernel)) wait(1);
			
			LoopKernel();
			
			str_cpy((ConsoleText->pstring)[1],"Switching off console...");
			
			break;	
			
		}
		
		if(str_cmp( (ConsoleText.pstring)[1],VAREXPLORER_EXITSTR )) {
			
			WriteLog("[SYS] Exit event was triggered from the console.");
			NewLine();
			
			ExitEvent();
			
		}
		
		if(str_cmp( (ConsoleText.pstring)[1],VAREXPLORER_REPORTSTR )) {
			
			WriteLog("[SYS] Preparing to run the report generator, please wait.");
			NewLine();
			
			_beep();
			
		}
		
		if(str_cmp( (ConsoleText.pstring)[1],VAREXPLORER_FACTORYSTR )) {
			
			WriteLog("[SYS] Preparing to reset settings to its original state, please wait.");
			NewLine();
			
			_beep();
			
		}
		
		wait(1);
		
	}

	reset(ConsoleText,SHOW);

	WriteLog("[SYS] The console has been closed. Probably the user has started the kernel again, or craftbox is preparing to shut down itself.");
	NewLine();

}
