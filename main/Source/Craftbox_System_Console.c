#ifndef Craftbox_System_Console

#define Craftbox_System_Console

/*
--------------------------------------------------
Craftbox_System_Console.c

Handles the console for working with craftbox when the  
kernel is switched off.

Written by Nguyen Ngoc Huy
https://github.com/ngochuy2101
http://craftboxdev.blogspot.com/

TODO:
<+++


>+++

NOTES:
<+++

+ Whenever a command is entered, there should be a few outputs to the console before 
the appropriate Con_*() function is executed.

- "startkernel": Launches the kernel.
- "loadw x": Load an existing saved world, with x count from 0 as the slot number
- "exit": Exits craftbox.
- "report": Runs the report generator.
- "default": Reset settings to default.
- "benchmark": Starts a benchmark session.

>+++
--------------------------------------------------

*/

void Con_StartKernel();
void Con_ParseAndLoadWorld();
void Con_Exit();
void Con_ReportGenerator();
void Con_Reset();

void Con_StartKernel() {
   
   LoadKernel();
   while(proc_status(LoadKernel)) wait(1);
   
   LoopKernel();
   
}

void Con_ParseAndLoadWorld() {
   
   wait(1);
   
}

void Con_Exit() {
   
   ExitEvent();
   
}

void Con_ReportGenerator() {
   
   wait(1);
   
}

void Con_Reset() {
	
	proc_mode = PROC_NOFREEZE;
	
	freeze_mode = 2;
	
	if( file_exists(FILE_CONFIG) ) {
		
		STRING *_FILE_CONFIG = str_create(str_len(FILE_CONFIG));
		str_cpy(_FILE_CONFIG, FILE_CONFIG);
		str_trunc(_FILE_CONFIG,4); // .cfg
		str_cat(_FILE_CONFIG,".kfg");
		
	}
	
	SetDefaultGraphicsSettings();
	while(proc_status(SetDefaultGraphicsSettings)) wait(1);
	
	ConfigFileWrite(FILE_CONFIG);
	
	freeze_mode = 0;
	
}

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

	if(cbKernelRunning) {
		
		_beep();
		
		WriteLog("! [ERROR] Console couldn't be executed while the kernel is running, returns -1.");
		NewLine();
		
		return -1;
		
	}
	
	WriteLog("[SYS] Setup console...");
	NewLine();

	ConsoleText->pos_x = 2;
	ConsoleText->pos_y = screen_size.y/4;
	toggle(ConsoleText,SHOW);

	// Additional WriteLogs here.

	while(!cbKernelRunning) {
		
		inkey((ConsoleText->pstring)[1]);
		
		if (result == CINPUT_ENTER) { // [Enter]
			
			void* found = var_for_name((ConsoleText->pstring)[1]);
			if (!found) execute((ConsoleText->pstring)[1]);
			
		}
		
		// No you can't exit from the console that easy!
		/*
		
		if(result == CINPUT_ESC) { // [Esc]
			
			str_cpy((ConsoleText->pstring)[1],"Loading kernel...");
			
			Con_StartKernel();
			
			str_cpy((ConsoleText->pstring)[1],"Switching off console...");
			
			break;	
			
		}
		
		*/
		
		if(str_stri( (ConsoleText.pstring)[1], VAREXPLORER_STARTKERNELSTR)) {
		   
		   str_cpy((ConsoleText->pstring)[1],"Loading kernel...");
		   
		   Con_StartKernel();
		   
		   str_cpy((ConsoleText->pstring)[1],"Switching off console...");
		   
		}
		
		if(str_stri ( (ConsoleText.pstring)[1],VAREXPLORER_EXITSTR )) {
			
			WriteLog("[SYS] Exit event was triggered from the console.");
			NewLine();
			
			Con_Exit();
			
		}
		
		if(str_stri ( (ConsoleText.pstring)[1],VAREXPLORER_REPORTSTR )) {
			
			WriteLog("[SYS] Preparing to run the report generator, please wait.");
			NewLine();
			
			Con_ReportGenerator();
			
		}
		
		if(str_stri ( (ConsoleText.pstring)[1],VAREXPLORER_FACTORYSTR )) {
			
			WriteLog("[SYS] Preparing to reset settings to its original state, please wait.");
			NewLine();
			
			Con_Reset();
			
		}
		
		if(str_stri((ConsoleText.pstring)[1],VAREXPLORER_BENCHMARK)) {
			
			WriteLog("[SYS] Preparing to benchmark your computer, please wait...");
			NewLine();
			
			OpenBenchmark();
			
		}
		
		wait(1);
		
	}

	reset(ConsoleText,SHOW);

	WriteLog("[SYS] The console has been closed. Probably the user has started the kernel again, or craftbox is preparing to shut down itself.");
	NewLine();

}

void OpenConsole() {
	
	if(event_type == EVENT_RELEASE) return;
	
	#ifdef CBOX_DEVELOPMENT
	UnloadKernel();
	Console();
	#endif
	
}

#endif 