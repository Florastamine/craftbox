void ClockStart() {
	
	set(ClockText,SHOW);
	
	while( !StopClock ){
		
		wait(-1); // a second
		SecondsPassed += 1;
		
		ClockUpdateVar();
		ClockUpdateGUI();
		
		wait(1);
		
	}
	
}

void ClockUpdateVar() {
	
	if( SecondsPassed >= 60 ) {
		
		SecondsPassed = 0;
		MinutesPassed += 1;
		
	}

	if(MinutesPassed >= 60) {
		
		MinutesPassed = 0;
		HoursPassed += 1;
		
	}

	if(HoursPassed >= 24 ) {
		
		HoursPassed = 0;
		DaysPassed += 1;
		
	}

	if( DaysPassed >= 30 ){
		
		DaysPassed = 0;
		MonthsPassed += 1;
		
	}

	if(MonthsPassed >= 3) SeasonsPassed += 1;
	
	if(SeasonsPassed >= 4) {
		
		MonthsPassed = 0;
		YearsPassed += 1;   
		
	}
	
}

void ClockUpdateGUIElement(var _var, STRING *_STRING) {
	
	str_cat( (ClockText.pstring) [0], str_for_num(str_create("#4"),_var) );
	str_cat( (ClockText.pstring) [0], _STRING);
	
}

void ClockUpdateGUI() {
	
	str_cpy( (ClockText.pstring) [0], " ");
	
	// Update years
	ClockUpdateGUIElement(YearsPassed," years, ");
	
	// Update seasons
	ClockUpdateGUIElement(SeasonsPassed," seasons, ");
	
	// Update months
	ClockUpdateGUIElement(MonthsPassed, " months, ");
	
	// Update days
	ClockUpdateGUIElement(DaysPassed, " days, ");
	
	// Update hours
	ClockUpdateGUIElement(HoursPassed," hours, ");
	
	// Update minutes
	ClockUpdateGUIElement(MinutesPassed," minutes, ");
	
	// Finally, update seconds
	ClockUpdateGUIElement(SecondsPassed," seconds.");	
}

void ClockStop() {
	
	StopClock = 1;
	
	reset(ClockText,SHOW);
}

#define PRAGMA_PRINT " [Loaded plugin clock] "