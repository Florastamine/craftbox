/***

http://mp3.zing.vn/bai-hat/Silent-Hill-Promise-Reprise-Piano-Unknow/IW9OIZD6.html
http://mp3.zing.vn/album/Piano-Spa-In-Love-Mr-Tuk-Bo-Tree/ZWZACZFW.html?st=12
http://mp3.zing.vn/tim-kiem/bai-hat.html?q=Various+Artists
http://www.youtube.com/watch?v=evSwhNl-HhQ

***/

var percentage;

PANEL *perc = {
	digits(0,0,99,"Arial#25b",1,percentage);
	layer=5555;
	flags=SHOW;
	pos_x=10;
	pos_y=10;
}

void timebar(var _TimeRemain,var _DecrTime)
{
	/*
	_GameLoaderDigitCover.pos_x = (screen_size.x - bmap_width(_GameLoaderDigitCover.bmap)) - 45;
	_GameLoaderDigitCover.pos_y = 15;
	
	_GameLoader.pos_x = _GameLoaderPOSX;
	_GameLoader.pos_y = _GameLoaderPOSY;
	
	getx__GameLoader = _GameLoader.pos_x;
	gety__GameLoader = _GameLoader.pos_y;
	
	_GameLoaderFrame.pos_x = getx__GameLoader;
	_GameLoaderFrame.pos_y = gety__GameLoader;
	_GameLoaderFrame.layer = _GameLoader.layer + 1;
	
	if(!is(_GameLoader,SHOW)) set(_GameLoader,SHOW);
	if(!is(_GameLoaderFrame,SHOW)) set(_GameLoaderFrame,SHOW);
	if(!is(_GameLoaderDigit,SHOW)) set(_GameLoaderDigit,SHOW);
	if(!is(_GameLoaderDigitCover,SHOW)) set(_GameLoaderDigitCover,SHOW);
	
	set(_GameLoaderDigitCover,TRANSLUCENT);
	_GameLoaderDigitCover.alpha = 75;
	_GameLoaderDigitCover.layer = _GameLoaderDigit.layer + 1;
	
	if(_TimeRemain > screen_size.x) printf("In OSGP.c -> kgame.c -> osgp_time_decr(var _TimeRemain,var _DecrTime, var _GameLoaderPOSX, var _GameLoaderPOSY)\nYou've exceeded screen_size.x. OSGP will ignore it, but you'll have to fix it manually.");
	_TimeRemain = abs(_TimeRemain);
	
	_GameLoader.scale_x = maxv(.01,_TimeRemain / 100);
	_GameLoaderFrame.scale_x = _GameLoader.scale_x;
	
	_GameLoader.scale_x = .01;*/
	var __TimeRemain = _TimeRemain;
	
	while(abs(_TimeRemain) > 0 && percentage > 0) 
	{
		_TimeRemain -= _DecrTime;
		percentage = (_TimeRemain / __TimeRemain) * 100;

		//		_GameLoader.scale_x = maxv(.01,_TimeRemain / 100);
		wait(1);
	}
	
	//	sys_exit(NULL);
}

void generate_waypoint()
{
	while(my == NULL) wait(1);
	
	node++;

	my_target_node = me;
	my_target_node.emask |= ENABLE_SCAN;
}

void generate_sound() {
	
	ent_playloop(my,sndobjs[num_sndobjs],100);
	
}

void generate_light() {
	
	set(my, BRIGHT | NOFOG | PASSABLE | TRANSLUCENT);
	
	/* Some adjustments for our little jabber.png */
	my.scale_x = my.scale_y = my.scale_z /= 2;
	
	my.z += 25;
	my.alpha = DEFAULT_ALPHA+25;
	my.ambient = 100;
	
	my.lightrange = random(500);
	vec_set(my.red,vector(random(255),random(255),random(255)));
	
	my.z += 75;
	
	if(my.flick_time == 0) my.flick_time = .5;
	
	// Like men and women, lights should equal to normal entities.
	// They have the rights to be manipulated by the mouse.
	// oooh, wait, was the mouse belonged to the government??
	// ...
	// oh no.
	my.emask |= ENABLE_CLICK;
	// my.event = 	
	
	while(my) { // This loop will active as long as its entity is alive.
		
		if(my.light_mode == flick) { // Flickering lights (Flashing lights)
			
			my.lightrange = 0;
			wait(-my.flick_time);
			my.lightrange = olrange;
			wait(-my.flick_time);
			
		}
		
		if(my.light_mode == disco) { // Lights that change its r/g/b values continuously.
			
			random_seed(0);
			
			my.red = random(255);
			my.green = random(255);
			my.red = random(255);
			
			wait(-.1);
			
		}
		
		wait(1);
	}
}

////////////////////////////////////////////////////////////
// Panel manipulation functions.
// Some I wrote by myself, some I borrowed from the others.
////////////////////////////////////////////////////////////
void pan_rotate(PANEL *p,var lim,var speed,BOOL rotate_on_center)
{
	while(p == NULL) wait(1);
	while(!is(p,SHOW)) wait(1);
	
	if(rotate_on_center)
	{
		p->center_x = p->size_x * 0.5;
		p->center_y = p->size_y * 0.5;
	}
	while(p->angle < lim)
	{
		p->angle += speed * time_step;
		wait(1);
	}
	p->angle = 0; 
}

void pan_resize(PANEL *p, char c) {
	
	while(p == NULL) wait(1);
	
	switch(c) {
		
		case 'x': p.scale_x = screen_size.x/bmap_width(p.bmap);
		break;
		
		case 'y': p.scale_y = screen_size.y/bmap_height(p.bmap);
		break;
		
		default:
		
		p.pos_x = p.pos_y = 0;
		
		p.scale_x = screen_size.x/bmap_width(p.bmap);
		p.scale_y = screen_size.y/bmap_height(p.bmap);
		
		break;
		
	}
	
}

////////////////////////////////////////////////////////////
// This function will load the database.
////////////////////////////////////////////////////////////
void init_database_snd() {
	
	int i;
	
	////////////////////////////////////////////////////////////
	// Stupid sound database.
	// Use the same stupid database structure as init_database().
	////////////////////////////////////////////////////////////
	sndobjs[0] = snd_create("hit.wav");
	
	// Unallocated space
	for(i = 1;i < 50;i++) sndobjs[i] = snd_create("beep.wav");
	
}

void init_database_part() {
	
	int i;
	
	partobjs[0] = part_spiral;
	partobjs[1] = part_colorfulspark;
	partobjs[2] = part_spacehole;
	partobjs[3] = part_fountain2;
	partobjs[4] = part_fountain1;
	partobjs[5] = part_fire2;
	partobjs[6] = part_fire1;
	partobjs[7] = part_doublehelix;
	partobjs[8] = part_composition;
	
	// Unallocated space
	for(i = 9;i < 20;i++) partobjs[i] = 0;
} 

void init_database() {
	
	int i;
	
	////////////////////////////////////////////////////////////
	// Don't ask me why I don't read the whole database
	// from an external file. I did it once - and failed.
	// The reason: try it yourself - it's an engine-related problem.
	
	// Still, there is an advantage. There will be no disk I/O
	// activity to be performed.
	
	// This is slow but probably because of my outdated Celeron D
	// processor. Maybe it will perform faster on a Pentium 4.	
	////////////////////////////////////////////////////////////

	// Animals 50 [0->49]
	// Allocated space
	mdlobjs_table[0] = str_create("a_badger.mdl");
	mdlobjs_table[1] = str_create("a_bat.mdl");
	mdlobjs_table[2] = str_create("a_bluebird.mdl");
	mdlobjs_table[3] = str_create("a_boar.mdl");
	mdlobjs_table[4] = str_create("a_bug.mdl");
	mdlobjs_table[5] = str_create("a_burkel.mdl");
	mdlobjs_table[6] = str_create("a_butterfly.mdl");
	mdlobjs_table[7] = str_create("a_crow.mdl");
	mdlobjs_table[8] = str_create("a_fish1.mdl");
	mdlobjs_table[9] = str_create("a_fish2.mdl");
	mdlobjs_table[10] = str_create("a_fish3.mdl");
	mdlobjs_table[11] = str_create("a_fish4.mdl");
	mdlobjs_table[12] = str_create("a_fish5.mdl");
	mdlobjs_table[13] = str_create("a_fish6.mdl");
	mdlobjs_table[14] = str_create("a_fish7.mdl");
	mdlobjs_table[15] = str_create("a_fish8.mdl");
	mdlobjs_table[16] = str_create("a_rat.mdl");
	mdlobjs_table[17] = str_create("a_snake.mdl");

	// Unallocated space
	for(i = 18; i < 50;i++) mdlobjs_table[i] = str_create("#2");

	// Architecture 80 [50->129]
	// Allocated space
	mdlobjs_table[50] = str_create("a_building.wmb");
	mdlobjs_table[51] = str_create("a_building1.mdl");
	mdlobjs_table[52] = str_create("a_church.mdl");
	mdlobjs_table[53] = str_create("a_fence.mdl");
	mdlobjs_table[54] = str_create("a_fence_cylinder.mdl");
	mdlobjs_table[55] = str_create("a_gate.mdl");
	mdlobjs_table[56] = str_create("a_house1.mdl");
	mdlobjs_table[57] = str_create("a_house2.mdl");
	mdlobjs_table[58] = str_create("a_house3.mdl");
	mdlobjs_table[59] = str_create("a_hut.mdl");
	mdlobjs_table[60] = str_create("a_temple_entrance.mdl");
	mdlobjs_table[61] = str_create("a_warehouse.mdl");
	mdlobjs_table[62] = str_create("a_warehouse1.mdl");
	mdlobjs_table[63] = str_create("a_warehouse2.mdl");
	mdlobjs_table[64] = str_create("a_warehouse3.mdl");
	mdlobjs_table[65] = str_create("a_warehouse4.mdl");
	mdlobjs_table[66] = str_create("a__frame.mdl");

	// Unallocated space
	for(i = 67;i < 130;i++) mdlobjs_table[i] = str_create("#2");
	
	// Characters 50 [130->179]
	// Allocated space
	mdlobjs_table[130] = str_create("c_badguy.mdl");
	mdlobjs_table[131] = str_create("c_berzerka.mdl");
	mdlobjs_table[132] = str_create("c_cgirl.mdl");
	mdlobjs_table[133] = str_create("c_guard.mdl");
	mdlobjs_table[134] = str_create("c_HCS_Warrior_C.mdl");
	mdlobjs_table[135] = str_create("c_inmate.mdl");
	mdlobjs_table[136] = str_create("c_ninja.mdl");
	mdlobjs_table[137] = str_create("c_p_king_ochan.mdl");
	mdlobjs_table[138] = str_create("c_p_lobster_mutant.mdl");
	mdlobjs_table[139] = str_create("c_p_mario_h.mdl");
	mdlobjs_table[140] = str_create("c_p_pirate.mdl");
	mdlobjs_table[141] = str_create("c_p_r2_robot.mdl");
	mdlobjs_table[142] = str_create("c_p_saucer.mdl");
	mdlobjs_table[143] = str_create("c_p_skel.mdl");
	mdlobjs_table[144] = str_create("c_rabbit.mdl");
	mdlobjs_table[145] = str_create("c_soldier.mdl");
	mdlobjs_table[146] = str_create("c_trooper.mdl");
	mdlobjs_table[147] = str_create("c_warlock.mdl");
	mdlobjs_table[148] = str_create("c_witch.mdl");
	mdlobjs_table[149] = str_create("c__007.mdl");

	// Unallocated space
	for(i = 150;i < 180;i++) mdlobjs_table[i] = str_create("#2");

	// Everyday objects 300 [180-479]
	// Allocated objects
	mdlobjs_table[180] = str_create("e_ball1.mdl");
	mdlobjs_table[181] = str_create("e_ball10.mdl");
	mdlobjs_table[182] = str_create("e_ball11.mdl");
	mdlobjs_table[183] = str_create("e_ball12.mdl");
	mdlobjs_table[184] = str_create("e_ball13.mdl");
	mdlobjs_table[185] = str_create("e_ball14.mdl");
	mdlobjs_table[186] = str_create("e_ball15.mdl");
	mdlobjs_table[187] = str_create("e_ball2.mdl");
	mdlobjs_table[188] = str_create("e_ball3.mdl");
	mdlobjs_table[189] = str_create("e_ball4.mdl");
	mdlobjs_table[190] = str_create("e_ball5.mdl");
	mdlobjs_table[191] = str_create("e_ball6.mdl");
	mdlobjs_table[192] = str_create("e_ball7.mdl");
	mdlobjs_table[193] = str_create("e_ball8.mdl");
	mdlobjs_table[194] = str_create("e_ball9.mdl");
	mdlobjs_table[195] = str_create("e_balloon.mdl");
	mdlobjs_table[196] = str_create("e_ball_white.mdl");
	mdlobjs_table[197] = str_create("e_barrel.mdl");
	mdlobjs_table[198] = str_create("e_barrel01.mdl");
	mdlobjs_table[199] = str_create("e_barrel02.mdl");
	mdlobjs_table[200] = str_create("e_barrel03.mdl");
	mdlobjs_table[201] = str_create("e_barrel04.mdl");
	mdlobjs_table[202] = str_create("e_barrel05.mdl");
	mdlobjs_table[203] = str_create("e_barrel06.mdl");
	mdlobjs_table[204] = str_create("e_barrel07.mdl");
	mdlobjs_table[205] = str_create("e_barrel08.mdl");
	mdlobjs_table[206] = str_create("e_barrel9.mdl");
	mdlobjs_table[207] = str_create("e_barrier.mdl");
	mdlobjs_table[208] = str_create("e_basketballbasket.mdl");
	mdlobjs_table[209] = str_create("e_battery.mdl");
	mdlobjs_table[210] = str_create("e_bench.mdl");
	mdlobjs_table[211] = str_create("e_bench1.mdl");
	mdlobjs_table[212] = str_create("e_bench2.mdl");
	mdlobjs_table[213] = str_create("e_bench3.mdl");
	mdlobjs_table[214] = str_create("e_bench4.mdl");
	mdlobjs_table[215] = str_create("e_bench5.mdl");
	mdlobjs_table[216] = str_create("e_bench6.mdl");
	mdlobjs_table[217] = str_create("e_bench7.mdl");
	mdlobjs_table[218] = str_create("e_bench8.mdl");
	mdlobjs_table[219] = str_create("e_billard1.mdl");
	mdlobjs_table[220] = str_create("e_billardlamp.mdl");
	mdlobjs_table[221] = str_create("e_billiard.mdl");
	mdlobjs_table[222] = str_create("e_billiard2.mdl");
	mdlobjs_table[223] = str_create("e_billiard3.mdl");
	mdlobjs_table[224] = str_create("e_billiard_queue.mdl");
	mdlobjs_table[225] = str_create("e_book1.mdl");
	mdlobjs_table[226] = str_create("e_books.mdl");
	mdlobjs_table[227] = str_create("e_books2.mdl");
	mdlobjs_table[228] = str_create("e_books3.mdl");
	mdlobjs_table[229] = str_create("e_bookshelf.mdl");
	mdlobjs_table[230] = str_create("e_box.mdl");
	mdlobjs_table[231] = str_create("e_box1.mdl");
	mdlobjs_table[232] = str_create("e_cabinet.mdl");
	mdlobjs_table[233] = str_create("e_cabinet_corner.mdl");
	mdlobjs_table[234] = str_create("e_cd.mdl");
	mdlobjs_table[235] = str_create("e_cement_bag.mdl");
	mdlobjs_table[236] = str_create("e_chair.mdl");
	mdlobjs_table[237] = str_create("e_chair1.mdl");
	mdlobjs_table[238] = str_create("e_chair2.mdl");
	mdlobjs_table[239] = str_create("e_ciga.mdl"); 
	mdlobjs_table[240] = str_create("e_clock.mdl");
	mdlobjs_table[241] = str_create("e_cloud.mdl");
	mdlobjs_table[242] = str_create("e_coin.mdl");
	mdlobjs_table[243] = str_create("e_colamach.mdl");
	mdlobjs_table[244] = str_create("e_crate.mdl");
	mdlobjs_table[245] = str_create("e_crate1.mdl");
	mdlobjs_table[246] = str_create("e_crate2.mdl");
	mdlobjs_table[247] = str_create("e_crystal.mdl");
	mdlobjs_table[248] = str_create("e_door.mdl");
	mdlobjs_table[249] = str_create("e_door1.mdl");
	mdlobjs_table[250] = str_create("e_door2.mdl");
	mdlobjs_table[251] = str_create("e_door3.mdl");
	mdlobjs_table[252] = str_create("e_door4.mdl");
	mdlobjs_table[253] = str_create("e_dumpster.mdl");
	mdlobjs_table[254] = str_create("e_d_booth_01.mdl");
	mdlobjs_table[255] = str_create("e_extinguisher.mdl");
	mdlobjs_table[256] = str_create("e_extinguisher1.mdl");
	mdlobjs_table[257] = str_create("e_fence.mdl");
	mdlobjs_table[258] = str_create("e_fire.mdl");
	mdlobjs_table[259] = str_create("e_flag.mdl");
	mdlobjs_table[260] = str_create("e_fridge.mdl");
	mdlobjs_table[261] = str_create("e_frying_pan.mdl");
	mdlobjs_table[262] = str_create("e_gift_box.mdl");
	mdlobjs_table[263] = str_create("e_hydrant.mdl");
	mdlobjs_table[264] = str_create("e_iPod.mdl");
	mdlobjs_table[265] = str_create("e_lamp1.mdl");
	mdlobjs_table[266] = str_create("e_lamp2.mdl");
	mdlobjs_table[267] = str_create("e_lamp3.mdl");
	mdlobjs_table[268] = str_create("e_lamp4.mdl");
	mdlobjs_table[269] = str_create("e_leon_armoire.mdl");
	mdlobjs_table[270] = str_create("e_leon_desk.mdl");
	mdlobjs_table[271] = str_create("e_light.mdl");
	mdlobjs_table[272] = str_create("e_mirror.mdl");
	mdlobjs_table[273] = str_create("e_mirror1.mdl");
	mdlobjs_table[274] = str_create("e_palette.mdl");
	mdlobjs_table[275] = str_create("e_palette1.mdl");
	mdlobjs_table[276] = str_create("e_parkingmeter.mdl");
	mdlobjs_table[277] = str_create("e_piano.mdl");
	mdlobjs_table[278] = str_create("e_picture.mdl");
	mdlobjs_table[279] = str_create("e_picture1.mdl");
	mdlobjs_table[280] = str_create("e_picture2.mdl");
	mdlobjs_table[281] = str_create("e_picture3.mdl");
	mdlobjs_table[282] = str_create("e_picture4.mdl");
	mdlobjs_table[283] = str_create("e_picture5.mdl");
	mdlobjs_table[284] = str_create("e_picture6.mdl");
	mdlobjs_table[285] = str_create("e_picture7.mdl");
	mdlobjs_table[286] = str_create("e_picture8.mdl");
	mdlobjs_table[287] = str_create("e_pipe.mdl");
	mdlobjs_table[288] = str_create("e_pipe1.mdl");
	mdlobjs_table[289] = str_create("e_pipe2.mdl");
	mdlobjs_table[290] = str_create("e_platform.mdl");
	mdlobjs_table[291] = str_create("e_railway_45left.mdl");
	mdlobjs_table[292] = str_create("e_railway_45right.mdl");
	mdlobjs_table[293] = str_create("e_railway_doubleswitch.mdl");
	mdlobjs_table[294] = str_create("e_railway_down.mdl");
	mdlobjs_table[295] = str_create("e_railway_end.mdl");
	mdlobjs_table[296] = str_create("e_railway_singleswitch.mdl");
	mdlobjs_table[297] = str_create("e_railway_straight.mdl");
	mdlobjs_table[298] = str_create("e_railway_up.mdl");
	mdlobjs_table[299] = str_create("e_rail_lore1.mdl");
	mdlobjs_table[300] = str_create("e_rope.mdl");
	mdlobjs_table[301] = str_create("e_salonch.mdl");
	mdlobjs_table[302] = str_create("e_salonch1.mdl");
	mdlobjs_table[303] = str_create("e_sign_30.mdl");
	mdlobjs_table[304] = str_create("e_sign_60.mdl");
	mdlobjs_table[305] = str_create("e_sign_90.mdl");
	mdlobjs_table[306] = str_create("e_sign_bicyclelane.mdl");
	mdlobjs_table[307] = str_create("e_sign_boulder.mdl");
	mdlobjs_table[308] = str_create("e_sign_bumpy-road.mdl");
	mdlobjs_table[309] = str_create("e_sign_church.mdl");
	mdlobjs_table[310] = str_create("e_sign_crosswinds.mdl");
	mdlobjs_table[311] = str_create("e_sign_curve-ahead.mdl");
	mdlobjs_table[312] = str_create("e_sign_endminimumspeed.mdl");
	mdlobjs_table[313] = str_create("e_sign_exit.mdl");
	mdlobjs_table[314] = str_create("e_sign_footpath.mdl");
	mdlobjs_table[315] = str_create("e_sign_hospital.mdl");
	mdlobjs_table[316] = str_create("e_sign_minimumspeed.mdl");
	mdlobjs_table[317] = str_create("e_sign_noentry.mdl");
	mdlobjs_table[318] = str_create("e_sign_noparking.mdl");
	mdlobjs_table[319] = str_create("e_sign_nopassing.mdl");
	mdlobjs_table[320] = str_create("e_sign_nostopping.mdl");
	mdlobjs_table[321] = str_create("e_sign_novehicles.mdl");
	mdlobjs_table[322] = str_create("e_sign_novisitor.mdl");
	mdlobjs_table[323] = str_create("e_sign_oneside-road-narrow.mdl");
	mdlobjs_table[324] = str_create("e_sign_parking.mdl");
	mdlobjs_table[325] = str_create("e_sign_pedcrossing.mdl");
	mdlobjs_table[326] = str_create("e_sign_pedestrian.mdl");
	mdlobjs_table[327] = str_create("e_sign_phone.mdl");
	mdlobjs_table[328] = str_create("e_sign_railroad.mdl");
	mdlobjs_table[329] = str_create("e_sign_road-narrow.mdl");
	mdlobjs_table[330] = str_create("e_sign_roundabout.mdl");
	mdlobjs_table[331] = str_create("e_sign_slippery.mdl");
	mdlobjs_table[332] = str_create("e_sign_traffic.mdl");
	mdlobjs_table[333] = str_create("e_sign_trafficlights.mdl");
	mdlobjs_table[334] = str_create("e_sign_turnscrossing.mdl");
	mdlobjs_table[335] = str_create("e_sign_yield.mdl");
	mdlobjs_table[336] = str_create("e_sofa.mdl");
	mdlobjs_table[337] = str_create("e_strange_boar_toy.mdl");
	mdlobjs_table[338] = str_create("e_strange_bowl.mdl");
	mdlobjs_table[339] = str_create("e_strange_canvas.mdl");
	mdlobjs_table[340] = str_create("e_strange_canvas2.mdl");
	mdlobjs_table[341] = str_create("e_strange_crate.mdl");
	mdlobjs_table[342] = str_create("e_strange_decorator.mdl");
	mdlobjs_table[343] = str_create("e_strange_drums.mdl");
	mdlobjs_table[344] = str_create("e_strange_flag.mdl");
	mdlobjs_table[345] = str_create("e_strange_house.mdl");
	mdlobjs_table[346] = str_create("e_strange_machine.mdl");
	mdlobjs_table[347] = str_create("e_strange_placeholder.mdl");
	mdlobjs_table[348] = str_create("e_strange_shelf.mdl");
	mdlobjs_table[349] = str_create("e_strange_trough.mdl");
	mdlobjs_table[350] = str_create("e_strange_umbrella.mdl");
	mdlobjs_table[351] = str_create("e_strange_wine_barrel.mdl");
	mdlobjs_table[352] = str_create("e_strange_wine_barrel2.mdl");
	mdlobjs_table[353] = str_create("e_streetlight.mdl");
	mdlobjs_table[354] = str_create("e_table.mdl");
	mdlobjs_table[355] = str_create("e_table1.mdl");
	mdlobjs_table[356] = str_create("e_table_blood.mdl");
	mdlobjs_table[357] = str_create("e_target.mdl");
	mdlobjs_table[358] = str_create("e_target1.mdl");
	mdlobjs_table[359] = str_create("e_torch.mdl");
	mdlobjs_table[360] = str_create("e_trashcan.mdl");
	mdlobjs_table[361] = str_create("e_trashcan1.mdl");
	mdlobjs_table[362] = str_create("e_trashcan2.mdl");
	mdlobjs_table[363] = str_create("e_treasure_chest.mdl");
	mdlobjs_table[364] = str_create("e_wheatpack.mdl");
	mdlobjs_table[365] = str_create("e_woodchair.mdl");
	mdlobjs_table[366] = str_create("e_woodchair2.mdl");

	// Unallocated space
	for (i = 367;i < 480;i++) mdlobjs_table[i] = str_create("#2");
	
	// Food 90 [480-569]
	// Allocated space
	mdlobjs_table[480] = str_create("f_apple_green.mdl");
	mdlobjs_table[481] = str_create("f_apple_red.mdl");
	mdlobjs_table[482] = str_create("f_bagel.mdl");
	mdlobjs_table[483] = str_create("f_banana.mdl");
	mdlobjs_table[484] = str_create("f_bread.mdl");
	mdlobjs_table[485] = str_create("f_bread_loaf.mdl");
	mdlobjs_table[486] = str_create("f_carrot.mdl");
	mdlobjs_table[487] = str_create("f_cookie.mdl");
	mdlobjs_table[488] = str_create("f_cookie1.mdl");
	mdlobjs_table[489] = str_create("f_cookie2.mdl");
	mdlobjs_table[490] = str_create("f_cookie3.mdl");
	mdlobjs_table[491] = str_create("f_corn.mdl");
	mdlobjs_table[492] = str_create("f_croissaint.mdl");
	mdlobjs_table[493] = str_create("f_donut.mdl");
	mdlobjs_table[494] = str_create("f_donut1.mdl");
	mdlobjs_table[495] = str_create("f_foodsack.mdl");
	mdlobjs_table[496] = str_create("f_genericf.mdl");
	mdlobjs_table[497] = str_create("f_hamburger.mdl");
	mdlobjs_table[498] = str_create("f_hotdog.mdl");
	mdlobjs_table[499] = str_create("f_icecream.mdl");
	mdlobjs_table[500] = str_create("f_nectarine.mdl");
	mdlobjs_table[501] = str_create("f_orange.mdl");
	mdlobjs_table[502] = str_create("f_pear.mdl");
	mdlobjs_table[503] = str_create("f_pizza.mdl");
	mdlobjs_table[504] = str_create("f_squash.mdl");
	mdlobjs_table[505] = str_create("f_steak.mdl");
	mdlobjs_table[506] = str_create("f_tomato.mdl");
	mdlobjs_table[507] = str_create("f_watermelon.mdl");
	mdlobjs_table[508] = str_create("f_watermelon_piece.mdl");

	// Unallocated space
	for(i = 509;i < 570;i++) mdlobjs_table[i] = str_create("#2");
	
	// Machines 50 [570-619]
	// Allocated space
	mdlobjs_table[570] = str_create("m_console.mdl");
	mdlobjs_table[571] = str_create("m_generator.mdl");
	mdlobjs_table[572] = str_create("m_generator1.mdl");
	mdlobjs_table[573] = str_create("m_generator2.mdl");
	mdlobjs_table[574] = str_create("m_hatch.mdl");
	mdlobjs_table[575] = str_create("m_powerplant.mdl");
	mdlobjs_table[576] = str_create("m_turret02.mdl");

	// Unallocated space
	for(i = 577;i < 620;i++) mdlobjs_table[i] = str_create("#2");
	
	// Plants 160 [620-779]
	// Allocated space
	mdlobjs_table[620] = str_create("bigtree2.mdl");
	mdlobjs_table[621] = str_create("bstone1.mdl");
	mdlobjs_table[622] = str_create("bstone2.mdl");
	mdlobjs_table[623] = str_create("bush1.mdl");
	mdlobjs_table[624] = str_create("bush3.mdl");
	mdlobjs_table[625] = str_create("bush7.mdl");
	mdlobjs_table[626] = str_create("d_14_lod0.mdl");
	mdlobjs_table[627] = str_create("d_Fantasy_tree1.mdl");
	mdlobjs_table[628] = str_create("d_flower_10.mdl");
	mdlobjs_table[629] = str_create("d_flower_6.mdl");
	mdlobjs_table[630] = str_create("d_litGr.mdl");
	mdlobjs_table[631] = str_create("fern_1.mdl");
	mdlobjs_table[632] = str_create("flower_1.mdl");
	mdlobjs_table[633] = str_create("gpalm1.mdl");
	mdlobjs_table[634] = str_create("grass.mdl");
	mdlobjs_table[635] = str_create("grass1.mdl");
	mdlobjs_table[636] = str_create("grass2.mdl");
	mdlobjs_table[637] = str_create("grass3.mdl");
	mdlobjs_table[638] = str_create("grass_scatt.mdl");
	mdlobjs_table[639] = str_create("indoorplant.mdl");
	mdlobjs_table[640] = str_create("kava_plant.mdl");
	mdlobjs_table[641] = str_create("kaya2.mdl");
	mdlobjs_table[642] = str_create("kaya3.mdl");
	mdlobjs_table[643] = str_create("lightray1.mdl");
	mdlobjs_table[644] = str_create("lp_birke_kr.mdl");
	mdlobjs_table[645] = str_create("lp_birke_st.mdl");
	mdlobjs_table[646] = str_create("lp_busch1.mdl");
	mdlobjs_table[647] = str_create("lp_chunk1.mdl");
	mdlobjs_table[648] = str_create("lp_farn.mdl");
	mdlobjs_table[649] = str_create("lp_grass.mdl");
	mdlobjs_table[650] = str_create("lp_Pine1_kr.mdl");
	mdlobjs_table[651] = str_create("lp_Pine1_st.mdl");
	mdlobjs_table[652] = str_create("lp_spruce_kr.mdl");
	mdlobjs_table[653] = str_create("lp_spruce_st.mdl");
	mdlobjs_table[654] = str_create("lp_stones.mdl");
	mdlobjs_table[655] = str_create("lp_tree2_kr.mdl");
	mdlobjs_table[656] = str_create("lp_tree2_st.mdl");
	mdlobjs_table[657] = str_create("lp_tree_trck.mdl");
	mdlobjs_table[658] = str_create("mushroom1.mdl");
	mdlobjs_table[659] = str_create("mushroom2.mdl");
	mdlobjs_table[660] = str_create("mushroom3.mdl");
	mdlobjs_table[661] = str_create("mushrooms1.mdl");
	mdlobjs_table[662] = str_create("mushrooms2.mdl");
	mdlobjs_table[663] = str_create("plant1.mdl");
	mdlobjs_table[664] = str_create("platane.mdl");
	mdlobjs_table[665] = str_create("rays1.mdl");
	mdlobjs_table[666] = str_create("rays2.mdl");
	mdlobjs_table[667] = str_create("shrub.mdl");
	mdlobjs_table[668] = str_create("sstone1.mdl");
	mdlobjs_table[669] = str_create("stone_fountain.mdl");
	mdlobjs_table[670] = str_create("stone_ground_small.mdl");
	mdlobjs_table[671] = str_create("t1.mdl");
	mdlobjs_table[672] = str_create("t2.mdl");
	mdlobjs_table[673] = str_create("t3.mdl");
	mdlobjs_table[674] = str_create("t4.mdl");
	mdlobjs_table[675] = str_create("t6.mdl");
	mdlobjs_table[676] = str_create("t7.mdl");
	mdlobjs_table[677] = str_create("tree1.mdl");
	mdlobjs_table[678] = str_create("tree2.mdl");
	mdlobjs_table[679] = str_create("tree4.mdl");
	mdlobjs_table[680] = str_create("tree5.mdl");
	mdlobjs_table[681] = str_create("Tree5_2.mdl");
	mdlobjs_table[682] = str_create("tree_lo.mdl");
	mdlobjs_table[683] = str_create("tree_log1.mdl");
	mdlobjs_table[684] = str_create("waterfall.mdl");
	mdlobjs_table[685] = str_create("weed1.mdl");
	mdlobjs_table[686] = str_create("weed10.mdl");
	mdlobjs_table[687] = str_create("weed11.mdl");
	mdlobjs_table[688] = str_create("weed12.mdl");
	mdlobjs_table[689] = str_create("weed13.mdl");
	mdlobjs_table[690] = str_create("weed14.mdl");
	mdlobjs_table[691] = str_create("weed15.mdl");
	mdlobjs_table[692] = str_create("weed16.mdl");
	mdlobjs_table[693] = str_create("weed17.mdl");
	mdlobjs_table[694] = str_create("weed18.mdl");
	mdlobjs_table[695] = str_create("weed2.mdl");
	mdlobjs_table[696] = str_create("weed24.mdl");
	mdlobjs_table[697] = str_create("weed3.mdl");
	mdlobjs_table[698] = str_create("weed4.mdl");
	mdlobjs_table[699] = str_create("weed5.mdl");
	mdlobjs_table[700] = str_create("weed6.mdl");
	mdlobjs_table[701] = str_create("weed7.mdl");
	mdlobjs_table[702] = str_create("weed8.mdl");
	mdlobjs_table[703] = str_create("weed9.mdl");
	mdlobjs_table[704] = str_create("weedm.mdl");
	
	// Unallocated space
	for(i = 705;i < 780;i++) mdlobjs_table[i] = str_create("#2");
	
	// Transportations 50 [780-829]
	// Allocated space
	mdlobjs_table[780] = str_create("t_bomber.mdl");
	mdlobjs_table[781] = str_create("t_bomber1.mdl");
	mdlobjs_table[782] = str_create("t_car1.mdl");
	mdlobjs_table[783] = str_create("t_car2.mdl");
	mdlobjs_table[784] = str_create("t_car3.mdl");
	mdlobjs_table[785] = str_create("t_car4.mdl");
	mdlobjs_table[786] = str_create("t_car_mr2.mdl");
	mdlobjs_table[787] = str_create("t_f105_thug.mdl");
	mdlobjs_table[788] = str_create("t_f16.mdl");
	mdlobjs_table[789] = str_create("t_hover1.mdl");
	mdlobjs_table[790] = str_create("t_lancaster.mdl");
	mdlobjs_table[791] = str_create("t_mcdf4_phantom.mdl");
	mdlobjs_table[792] = str_create("t_shopping.caddy.mdl");
	mdlobjs_table[793] = str_create("t_tank.mdl");
	mdlobjs_table[794] = str_create("t_tank1.mdl");
	mdlobjs_table[795] = str_create("t_trainpart.mdl");
	mdlobjs_table[796] = str_create("t_Viper.mdl");
	mdlobjs_table[797] = str_create("t_wagon.mdl");

	// Unallocated space
	for(i = 798; i < 830;i++) mdlobjs_table[i] = str_create("#2");
	
	// Land 50 [830->879]
	// Allocated space
	mdlobjs_table[830] = str_create("l_desertgeneric.hmp");
	mdlobjs_table[831] = str_create("l_greenland.hmp");
	mdlobjs_table[832] = str_create("l_greenland1.mdl");
	mdlobjs_table[833] = str_create("l_greenland_fat.mdl");
	mdlobjs_table[834] = str_create("l_marssurface.hmp");
	mdlobjs_table[835] = str_create("l_ocean1.hmp");
	mdlobjs_table[836] = str_create("l_ocean2.hmp");
	mdlobjs_table[837] = str_create("l_steppegeneric.hmp");
	mdlobjs_table[838] = str_create("l_stonegeneric.hmp");
	mdlobjs_table[839] = str_create("l_water1.hmp");
	mdlobjs_table[840] = str_create("l_water2.hmp");
	
	// Unallocated space
	for(i = 841;i < 880;i++) mdlobjs_table[i] = str_create("#2");
	
	// Done!
	////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////
// This function will fix incorrect scale ratio on models.
// Actually, I borrowed models from various source, and surely,
// they don't have the same scale ratio. So this quick fix
// will re-scale the models.
////////////////////////////////////////////////////////////
void fix(ENTITY *e) {
	
	if(num_mdlobjs == 52) // church/temple model
	e.scale_x = e.scale_y = e.scale_z *= 3;
	
	if(num_mdlobjs == 51) // big building
	e.scale_x = e.scale_y = e.scale_z *= 2;
	
	if(num_mdlobjs == 53) // [big] fence
	e.scale_x = e.scale_y = e.scale_z /= 1.5;
	
	if(num_mdlobjs == 54) // [big] fence bar
	e.scale_x = e.scale_y = e.scale_z /= 1.5;
	
	if(num_mdlobjs == 55) // wood entrance
	e.scale_x = e.scale_y = e.scale_z *= 2;
	
	if(e.obj_ID == 835 || e.obj_ID == 836) {
		
		e.z += 525;
		
	}
	
}

ENTITY *obj_create() { // This inherits a lot from place_me

	// Stupid objects couldn't float
	if(!temp_pos.x && !temp_pos.y && !temp_pos.z) return;

	ENTITY *tmp;

	switch(_obj_type) {
		
		////////////////////////////////////////////////////////////
		case mdl:
		
		if(str_len(mdlobjs_table_ptr[num_mdlobjs]) == 0) {
			
			printf("Wrong object ID.\nMaybe you're trying to access unallocated space in the object database.");
			return;
			
		}
		
		tmp = ent_create(mdlobjs_table_ptr[num_mdlobjs],temp_pos.x,obj_manip_setup);
		
		while(tmp == NULL) wait(1); // wait for tmp to be completely created.
		
		set(tmp, POLYGON);
		reset(tmp, NOFOG | INVISIBLE | TRANSLUCENT); // Tha giet nham con hon bo sot
		
		tmp.alpha = 0;
		tmp.ambient = 50;
		tmp.pan = random(360); // Give it a random pan value.
		
		tmp.material = mtl_model;
		
		tmp.obj_type = mdl;
		tmp.obj_ID = num_mdlobjs;
		
		tmp.obj_dynamic = 0; // This is a static object
		tmp.obj_physics = 0; // And physics aren't enabled by default.		
		
		fix(tmp);
		
		return tmp;
		
		break;
		////////////////////////////////////////////////////////////
		
		////////////////////////////////////////////////////////////
		// Lights don't have a database. So the "unallocated space"
		// error would never happen.
		
		case light:
		
		tmp = ent_create("jabber.png",temp_pos.x,generate_light);
		
		tmp.obj_type = light; // Du sao thi light cung ngan hon _obj_type
		// Lights don't have IDs so passing them is redundant.
		//		num_lightobjs
		
		return tmp;
		
		break;
		////////////////////////////////////////////////////////////
		
		////////////////////////////////////////////////////////////
		case part :
		
		switch(num_partobjs) {
			
			case part_spiral: tmp = ent_create("desktop_effect.png",temp_pos.x,emit_spiral); break;
			case part_colorfulspark: tmp = ent_create("desktop_effect.png",temp_pos.x,emit_colorfulspark); break;
			case part_spacehole: tmp = ent_create("desktop_effect.png",temp_pos.x,emit_spacehole); break;
			case part_fountain2: tmp = ent_create("desktop_effect.png",temp_pos.x,emit_fountain2); break;
			case part_fountain1: tmp = ent_create("desktop_effect.png",temp_pos.x,emit_fountain1); break;
			case part_fire2: tmp = ent_create("desktop_effect.png",temp_pos.x,emit_fire2); break;
			case part_fire1: tmp = ent_create("desktop_effect.png",temp_pos.x,emit_fire1); break;
			case part_doublehelix: tmp = ent_create("desktop_effect.png",temp_pos.x,emit_doublehelix); break;
			case part_composition: tmp = ent_create("desktop_effect.png",temp_pos.x,emit_composition); break;
			
			default:
			
			printf("num_partobjs outside range.");
			
			break;
			
		}
		
		set(tmp, BRIGHT | NOFOG | PASSABLE | TRANSLUCENT);
		
		tmp.obj_type = part;
		tmp.obj_ID = num_partobjs;
		
		tmp.scale_x = tmp.scale_y = tmp.scale_z /= 2;
		
		tmp.z += upper;
		tmp.alpha = DEFAULT_ALPHA+25;
		tmp.ambient = 100;
		
		return tmp;
		
		break;	
		////////////////////////////////////////////////////////////
		
		////////////////////////////////////////////////////////////
		case snd:
		
		if(!sndobjs[num_sndobjs] || num_sndobjs < 0 || num_sndobjs > 50) {
			
			printf("Wrong sound ID or damaged sound file.\nMaybe you're trying to access unallocated space in the sound database.");
			return;
			
		}
		
		tmp = ent_create("sound_32.png",temp_pos.x,generate_sound);
		
		set(tmp, BRIGHT | NOFOG | PASSABLE | TRANSLUCENT);
		
		// Am thanh nho be cu de cho no an :|
		//		tmp.scale_x = tmp.scale_y = tmp.scale_z /= 2;
		
		tmp.z += upper;
		tmp.alpha = DEFAULT_ALPHA+25;
		tmp.ambient = 100;
		
		tmp.obj_type = snd;
		tmp.obj_ID = num_sndobjs;
		
		return tmp;
		
		break;
		////////////////////////////////////////////////////////////
		
		////////////////////////////////////////////////////////////
		case node_placer:
		tmp = ent_create("ix_waypoint.mdl",temp_pos.x,generate_waypoint);
		
		set(tmp, BRIGHT | PASSABLE);
		tmp.ambient = 100;
		
		tmp.scale_x = tmp.scale_y = tmp.scale_z *= 1.5;
		
		tmp.obj_type = node_placer;
		
		return tmp;
		
		break;
		////////////////////////////////////////////////////////////
		
		////////////////////////////////////////////////////////////
		case terrain_edit :
		
		return;
		////////////////////////////////////////////////////////////
		
		default:
		
		printf("_obj_type outside range.");
		
		break;
		
		
	}
}

/*
void main(void) {
	//	CreateDirectory("cd",0);
	scan_folder("sharedData","pcx");
}
*/

void scan_folder(STRING *dir, STRING *ext)
{
	TEXT *read_files = txt_create(1000,1);
	
	STRING *search_form = "a";

	str_cpy(current_folder,dir);

	str_cpy(search_form,dir);
	str_cat(search_form,"\\*.");
	str_cat(search_form,ext);
	
	files_found = txt_for_dir(read_files, search_form);
	
	var num = files_already;
	while(num<999)
	{
		str_cpy((files_list.pstring)[num],"");
		num++;
	}
	
	num=0;
	while(num<files_found)
	{
		str_cpy((files_list.pstring)[num+files_already],(read_files.pstring)[num]);
		num++;
	}
	list_start=0;
	
	wait(1);
}

void updategui(PANEL *wg) {
	
	if(wg == panHome) {
		
		pan_setpos(panHome,3,1,vector(bmap_width(panHome.bmap) - 38 - 15,0,0));
		
	}
	
	if(wg == panProp) 
	{ 
		
		int i;
		for(i = 2;i < 6;i++) pan_setpos(panProp,3,i,vector(4, 20 + 35*(i-2),0));

		pan_setpos(panProp,3,1,vector(bmap_width(panProp.bmap) - 38 - 15,0,0));
		
		//////////////////////////////////////////////////////////////
		panProp_1.pos_x = panProp.pos_x + 121;
		panProp_1.pos_y = panProp.pos_y + 75;
		
		panProp_2.pos_x = panProp.pos_x + 121;
		panProp_2.pos_y = panProp.pos_y + 43;
		
		panProp_3.pos_x = panProp.pos_x + 121;
		panProp_3.pos_y = panProp.pos_y + 75;
		//////////////////////////////////////////////////////////////
		
	}

	if(wg == panMat_Sub1) { 
		
		pan_setpos(panMat_Sub1,3,1,vector(bmap_width(panMat_Sub1.bmap) - 38 - 15,0,0));
	}

	if(wg == panLight) {
		
		pan_setpos(panLight,3,1,vector(bmap_width(panLight.bmap) - 38 - 15,0,0));
		
	}
	
	if(wg == panSnd) {
		
		pan_setpos(panSnd,3,1,vector(bmap_width(panSnd.bmap) - 38 - 15,0,0));
		
	}
	
	if(wg == panParticle) {
		
		pan_setpos(panParticle,3,1,vector(bmap_width(panParticle.bmap) - 38 - 15,0,0));
		
	}
}

/* 

id always = 1 cuz we don't have two closebuttons at the same time. 
only one PANEL * parameter isn't enough (and it won't work too) so 
this simple ugly hack should do the trick.

*/
void closewindow(var id, PANEL *p) {
	id = 1;

	if(p == panHome) {
		reset(panHome,SHOW);
	}

	if(p == panMat_Sub1) {
		reset(panMat_Sub1,SHOW);
		
		
		/* code to save changes */
		
	}

	if(p == panProp) {		
		
		prop(0);
		
	}

	if(p == buttonlst_submenu_terrain) {
		wait(1);
		
		reset(buttonlst_submenu_terrain,SHOW);
	}

	if(p == buttonlst_submenu_object) {
		wait(1);
		
		reset(buttonlst_submenu_object,SHOW);
	}

	if(p == buttonlst_submenu_path) {
		wait(1);
		
		reset(buttonlst_submenu_path,SHOW);
	}
	
	if(p == panObj_Main_X) { // This is a bit special, since panObj_Main_X will pop up ONLY if panObj_Main pops.
		
		reset(panObj_Main,SHOW);
		reset(panObj_Subbar,SHOW);
		reset(panObj_Subbar_slider,SHOW);
		reset(panObj_Main_X,SHOW);
		
		ctrl = 0;
		
		showGUI();
		
	}
	
	if(p == panObj_Part_Main_X ) {
		
		reset(panObj_Part_Main,SHOW);
		reset(panObj_Part_slider,SHOW);
		reset(panObj_Part_Main_X,SHOW);
		
		ctrl = 0;
		
		showGUI();
		
	}
	
	if(p == panObj_Snd_Main_X) {
		
		reset(panObj_Snd_Main,SHOW);
		reset(panObj_Snd_slider,SHOW);
		reset(panObj_Snd_Main_X,SHOW);
		
		ctrl = 0;
		
		showGUI();
		
	}

	if(p == panLight) {
		
		_light(0);
		
	}
	
	if(p == panSnd) {
		
		sound(0);
		
	}
	
	if(p == panParticle) {
		
		_part(0);
		
	}
}

void dragpanel(PANEL *p)
{
	var click_offset[2];

	click_offset[0]=p.pos_x - mouse_pos.x;
	click_offset[1]=p.pos_y - mouse_pos.y;

	panelselect(p);

	while(mouse_left)
	{
		proc_mode = PROC_EARLY;
		
		p.pos_x = mouse_pos.x+click_offset[0];
		p.pos_y = mouse_pos.y+click_offset[1];
		
		//hack hack hack!!!!
		if(p == panHome) updategui(panHome);
		if(p == panProp) updategui(panProp);
		
		wait(1);
	}

	//hack to prevent shit happens. f.e. after dragged the guis' elements didn't retain their original location.
	if(p == panHome) updategui(panHome);
	if(p == panProp) updategui(panProp);
}

void centerpanel(PANEL *p) {
	while(p == NULL) wait(1);

	p.pos_x = (screen_size.x - bmap_width(p.bmap)) / 2; 
	p.pos_y = (screen_size.y - bmap_height(p.bmap)) / 2;
}

void sharedGUI_centerfrom(PANEL *p, PANEL *s) {
	while(p == NULL || s == NULL) wait(1);

	// peform a S comparison
	if(bmap_width(p.bmap)*bmap_height(p.bmap) > bmap_width(s.bmap)*bmap_height(s.bmap)) {
		
		printf("The size of the image that needs to be centered is too large.\nTry resizing it.");
		return;
		
	}

	if(bmap_width(s.bmap) > bmap_width(p.bmap))
	p.pos_x = (bmap_width(s.bmap) - bmap_width(p.bmap))/2;

	if(bmap_height(s.bmap) > bmap_height(p.bmap))
	p.pos_y = (bmap_height(s.bmap) - bmap_height(p.bmap))/2;
}

void loadGUI() {

	panMain_Top.pos_x = screen_size.x - bmap_width(panMain_Top.bmap) - (BORDER + 3 * 32);
	panMain_Top.pos_y = BORDER;

	panMain_Bottom.pos_x = BORDER;
	panMain_Bottom.pos_y = screen_size.y - bmap_height(panMain_Bottom.bmap) - BORDER;

	panObj_Main.pos_x = 0;
	panObj_Main.pos_y = (screen_size.y - bmap_height(panObj_Main.bmap))/2 - 3 * BORDER;

	panObj_Part_Main.pos_x = 0;
	panObj_Part_Main.pos_y = (screen_size.y - bmap_height(panObj_Main.bmap))/2 - 3 * BORDER;

	panObj_Snd_Main.pos_x = 0;
	panObj_Snd_Main.pos_y = (screen_size.y - bmap_height(panObj_Main.bmap))/2 - 3 * BORDER;
	
	panObj_Main_X.pos_x = screen_size.x - 40 - BORDER;
	panObj_Main_X.pos_y = panObj_Main.pos_y + 25;
	
	panObj_Part_Main_X.pos_x = panObj_Main_X.pos_x;
	panObj_Part_Main_X.pos_y = panObj_Main_X.pos_y;
	
	panObj_Snd_Main_X.pos_x = panObj_Main_X.pos_x;
	panObj_Snd_Main_X.pos_y = panObj_Main_X.pos_y;
	
	pan_resize(panObj_Subbar_slider,'x');
	pan_resize(panObj_Part_slider,'x');
	pan_resize(panObj_Snd_slider,'x');

	panObj_Subbar.pos_x = panObj_Subbar_slider.pos_x = panObj_Part_slider.pos_x = 0;
	
	panObj_Subbar.pos_y = panObj_Main.pos_y + bmap_height(panObj_Main.bmap) + BORDER;
	panObj_Subbar_slider.pos_y = panObj_Subbar.pos_y + bmap_height(panObj_Subbar_slider.bmap) + BORDER * 3;
	
	panObj_Part_slider.pos_y = panObj_Subbar_slider.pos_y;
	panObj_Snd_slider.pos_y = panObj_Subbar_slider.pos_y;
	
	panRotateHelp.pos_x = screen_size.x - bmap_width(panRotateHelp.bmap) - BORDER * 2;
	panRotateHelp.pos_y = panMain_Top.pos_y + BORDER * 2;
	
	panScaleHelp.pos_x = screen_size.x - bmap_width(panScaleHelp.bmap) - BORDER * 2;
	panScaleHelp.pos_y = panRotateHelp.pos_y;

	int i;
	for(i = 1; i < 10;i++) {
		
		pan_setpos(panObj_Subbar,3,i,vector(bmap_width(panObj_Subbar.bmap)/9 * (i-1),0,0));
		
	}

	int i = 1;
	while(i < 7) {
		pan_setpos(panMain_Top,3,i,vector((i - 1) * (BORDER + 32),0,0));
		i++;
	}

	int i = 1;
	while(i < 6) {
		pan_setpos(panMain_Bottom,3,i,vector((i-1) * (BORDER + 32),0,0));
		
		i++;
	}

	/*

	setup for submenus
	* buttonlst_submenu_terrain
	* buttonlst_submenu_object
	* buttonlst_submenu_path

	*/

	panMain_Play.pos_x = screen_size.x - BORDER - bmap_width(panMain_Play.bmap);
	panMain_Play.pos_y = screen_size.y - BORDER - bmap_height(panMain_Play.bmap);

	buttonlst_submenu_terrain.pos_x = 
	buttonlst_submenu_object.pos_x = 
	buttonlst_submenu_path.pos_x = BORDER;

	buttonlst_submenu_terrain.pos_y = 
	buttonlst_submenu_object.pos_y =
	buttonlst_submenu_path.pos_y = screen_size.y - 2 * BORDER - 64;

	int i = 1;
	while(i < 5) {
		
		pan_setpos(buttonlst_submenu_terrain,3,i,vector(BORDER * (i-1) + 32 * (i-1),NULL,NULL));
		pan_setpos(buttonlst_submenu_object,3,i,vector(BORDER * (i-1) + 32 * (i-1),NULL,NULL));
		pan_setpos(buttonlst_submenu_path,3,i,vector(BORDER * (i-1) + 32 * (i-1),NULL,NULL));
		
		i++;
	}

	var cache = BORDER * 4 + 32 * 4; // the above formula, i = 5
	pan_setpos(buttonlst_submenu_terrain,3,5,vector(cache,NULL,NULL));
	pan_setpos(buttonlst_submenu_object,3,5,vector(cache,NULL,NULL));
	pan_setpos(buttonlst_submenu_path,3,5,vector(cache,NULL,NULL));
}

void sharedGUI_blackscreen(int mode, int sec) {

	pan_resize(blackscreen,'0');
	set(blackscreen,SHOW);

	if(mode == FADE_IN) {
		
		set(blackscreen,TRANSLUCENT);
		blackscreen->alpha = 0;
		
		wait(-sec);
		
		while(blackscreen->alpha <= 100) {
			blackscreen->alpha += 10 * time_step;
			wait(1);
		}
		
		blackscreen->alpha = 100;
		
	}

	if(mode == FADE_OUT) {
		if(!is(blackscreen,SHOW)) set(blackscreen,SHOW);
		set(blackscreen,TRANSLUCENT);
		blackscreen->alpha = 100;
		
		wait(-sec);
		
		while(blackscreen->alpha >= 0) {
			blackscreen->alpha -= 10 * time_step;
			wait(1);
		}
		
		blackscreen->alpha = 0;
		reset(blackscreen,SHOW);
		
	}

}

void sharedGUI_loadlogo(BMAP *logo_bmap) {
	while(logo_bmap == NULL) wait(1);

	_logo.bmap = logo_bmap;

	_logo->pos_x = screen_size.x - bmap_width(_logo.bmap) - 2 * BORDER;
	_logo->pos_y = 20;

	set(_logo,SHOW);
}

void sharedGUI__loadlogo() {
	if(is(_logo,SHOW)) reset(_logo,SHOW);
}

void sharedGUI_playintro(STRING *what, var vol) {
	proc_kill(4);

	var hndl;
	hndl = media_play(what,NULL,abs(vol));

	while(media_playing(hndl)) wait(1);
}

void sharedGUI_mouse(BOOL mode) {

	if(mode) mouse_mode = 4;
	else mouse_mode = 0;

}

void home() {

	centerpanel(panHome);
	updategui(panHome);

	set(panHome,SHOW);
}

void prop(BOOL m) {

	if(m) {
		
		if(!lfsp) { // If prop() was launched from switch_panProp, don't re-change window's position.
			
			panProp.pos_x = xy_panProp.x;
			panProp.pos_y = xy_panProp.y;
			
		}
		
		else lfsp = 0;
		
		if(select) {
			
			if(select.obj_type != light &&
			select.obj_type != snd &&
			select.obj_type != part) {
				
				set(panProp,SHOW);
				
				////////////////////////////////////////////////////////////
				// Set rules for opening and closing panProp.
				////////////////////////////////////////////////////////////
				if(page == 1) { // Properties panel
					
					int i = 3;
					while(i<5) {
						
						button_state(panProp,i,0);
						i++;
						
					}
					
					panProp.bmap = panProp1_IMG;
					
					set(panProp_1,SHOW);
					reset(panProp_2,SHOW);
					reset(panProp_3,SHOW);
					
				}

				if(page == 2) { // Materials panel
					
					button_state(panProp,2,0);
					button_state(panProp,4,0);
					
					panProp.bmap = panProp2_IMG;
					
					reset(panProp_1,SHOW);
					set(panProp_2,SHOW);
					reset(panProp_3,SHOW);
					
				}

				if(page == 3) { // Physics panel
					
					button_state(panProp,3,0);
					button_state(panProp,2,0);
					
					panProp.bmap = panProp3_IMG;
					
					reset(panProp_1,SHOW);
					reset(panProp_2,SHOW);
					set(panProp_3,SHOW);
					
				}
				////////////////////////////////////////////////////////////
				
				updategui(panProp);
				
			}
			
		}
		
	}

	else { // Object is deactivated/other object has been selected.
		
		// Disable subpanels.
		// Actually we have only one subpanel opened at a time,
		// so only one value is passed to page.
		if(is(panProp_1,SHOW)) { // If something has been opened before.
			
			// save it to page.
			page = 1;
			// close the panel.
			reset(panProp_1,SHOW);
			
		}
		if(is(panProp_2,SHOW)) {
			
			page = 2;
			reset(panProp_2,SHOW);
			
		}
		
		if(is(panProp_3,SHOW)) {
			
			page = 3;
			reset(panProp_3,SHOW);
			
		}
		
		// Save window's location.
		xy_panProp.x = panProp.pos_x;
		xy_panProp.y = panProp.pos_y;	
		
		if(is(panMat_Sub1,SHOW)) reset(panMat_Sub1,SHOW);
		reset(panProp,SHOW);
		
	}
}

void editmat() {

	// Precache panMat_Sub1
	//	sharedGUI_centerfrom(panMat_Sub1,panMat);
	updategui(panMat_Sub1);

	// Material editor is available only to custom materials
	switch(mat_type) {
		
		case select_custom_mat1 :
		
		pass_mat_to_matsub(mat_custom[0]);
		set(panMat_Sub1,SHOW);
		
		break;
		//////////////////////////////////////////////////////////////
		
		case select_custom_mat2 :
		
		pass_mat_to_matsub(mat_custom[1]);
		set(panMat_Sub1,SHOW);
		
		break;
		//////////////////////////////////////////////////////////////
		
		case select_custom_mat3 :
		
		pass_mat_to_matsub(mat_custom[2]);
		set(panMat_Sub1,SHOW);
		
		break;
		//////////////////////////////////////////////////////////////
		
		case select_custom_mat4 :
		
		pass_mat_to_matsub(mat_custom[3]);
		set(panMat_Sub1,SHOW);
		
		break;
		//////////////////////////////////////////////////////////////
		
		default:
		printf("Material editor is available only to custom materials.");
		break;
	}	
}

void switch_panProp(var mode) {
	
	page=mode--;
	lfsp++;
	prop(1);
	
}

void sound(BOOL m) {
	
	if(m) {
		
		panSnd.pos_x = xy_panSnd.x;
		panSnd.pos_y = xy_panSnd.y;
		
		updategui(panSnd);
		set(panSnd,SHOW);
		
	}
	
	else {
		
		xy_panSnd.x = panSnd.pos_x;
		xy_panSnd.y = panSnd.pos_y;
		
		reset(panSnd,SHOW);
		
	}
	
}

void _part(BOOL m) {
	
	if(m) {
		
		panParticle.pos_x = xy_panParticle.x;
		panParticle.pos_y = xy_panParticle.y;
		
		updategui(panParticle);
		
		set(panParticle,SHOW);
		
	}

	else {
		
		xy_panParticle.x = panParticle.pos_y;
		xy_panParticle.y = panParticle.pos_y;
		
		reset(panParticle,SHOW);
		
	}
	
}

void _light(BOOL m) {

	if(m) {
		
		panLight.pos_x = xy_panLight.x;
		panLight.pos_y = xy_panLight.y;
		
		//		centerpanel(panLight);
		updategui(panLight);
		
		set(panLight,SHOW);
		
		// Surely, select has been selected already.
		
		v_lred = select.red;
		v_lgreen = select.green;
		v_lblue = select.blue;
		v_lrange = select.lightrange;
		
		// 'cause no#1 is the close button so we start from 2.
		if(select.light_mode == disco) button_state(panLight,2,1);
		if(select.light_mode == flick) button_state(panLight,3,1);
		
	}

	else { // !m
		
		// Backup
		xy_panLight.x = panLight.pos_x;
		xy_panLight.y = panLight.pos_y;
		
		// For passing to loop_kernel without messing up the code 
		// and/or write a new one.
		if(!select) return; 
		
		// Apply new values to the selected object.
		select.red = v_lred;
		select.green = v_lgreen;
		select.blue = v_lblue;
		
		// I grouped.
		// Assignment will happen this way: A <-- B <-- C
		// So we obtain C first, in this case is v_lrange
		olrange = select.lightrange = v_lrange;
		
		if(button_state(panLight,2,-1)) select.light_mode = disco;
		if(button_state(panLight,3,-1)) select.light_mode = flick;
		
		reset(panLight,SHOW);
		
	}

}

void panelselect(PANEL *p)
{
	if(last_pan) {
		last_pan.alpha = DEFAULT_ALPHA;
		layer_sort(last_pan,2);
		
		last_pan = p;
		layer_sort(last_pan,4);
		last_pan.alpha = 100;
	}
	else {
		last_pan = p;
		layer_sort(last_pan,4);
		last_pan.alpha = 100;
	}
}

void sharedGUI_launch_terrain() {
	reset(buttonlst_submenu_object,SHOW);
	reset(buttonlst_submenu_path,SHOW);

	set(buttonlst_submenu_terrain,SHOW);
}

void sharedGUI_launch_object() {
	reset(buttonlst_submenu_terrain,SHOW);
	reset(buttonlst_submenu_path,SHOW);

	set(buttonlst_submenu_object,SHOW);
}

void sharedGUI_launch_path() {
	reset(buttonlst_submenu_object,SHOW);
	reset(buttonlst_submenu_terrain,SHOW);

	set(buttonlst_submenu_path,SHOW);
}

void follow_pointer() {
	fpsf_marker = me;
	set(fpsf_marker,PASSABLE);

	while(1) {
		
		sharedGUI_cpos1.x = mouse_pos.x;
		sharedGUI_cpos1.y = mouse_pos.y;
		sharedGUI_cpos1.z = 0;
		vec_for_screen(sharedGUI_cpos1,camera);
		sharedGUI_cpos2.x = mouse_pos.x;
		sharedGUI_cpos2.y = mouse_pos.y;
		sharedGUI_cpos2.z = 200000;
		vec_for_screen(sharedGUI_cpos2,camera);

		c_trace(sharedGUI_cpos1.x,sharedGUI_cpos2.x,IGNORE_ME | IGNORE_PASSABLE | IGNORE_MODELS);
		vec_set(fpsf_marker.x,hit.x);
		vec_set(temp_pos.x,hit.x);
		wait(1);
		
	}
}

void pass_to_gui(ENTITY *e) {
	v_ambient = e.ambient;
	v_alpha = e.alpha;
	
	if(is(e,BRIGHT)) button_state(panProp_1,1,1);
	else button_state(panProp_1,1,0);

	if(is(e,INVISIBLE)) button_state(panProp_1,2,1);
	else button_state(panProp_1,2,0);

	if(is(e,NOFOG)) button_state(panProp_1,3,1);
	else button_state(panProp_1,3,0);

	if(is(e,OVERLAY)) button_state(panProp_1,4,1);
	else button_state(panProp_1,4,0);

	if(is(e,PASSABLE)) button_state(panProp_1,5,1);
	else button_state(panProp_1,5,0);

	if(is(e,POLYGON)) button_state(panProp_1,6,1);
	else button_state(panProp_1,6,0);

	if(is(e,SHADOW)) button_state(panProp_1,7,1);
	else button_state(panProp_1,7,0);

	if(is(e,TRANSLUCENT)) button_state(panProp_1,8,1);
	else button_state(panProp_1,8,0);

}

void restore() {
	if(select) {
		select.alpha = 0;
		select.ambient = 0;
		reset(select, BRIGHT | INVISIBLE | NOFOG | OVERLAY | PASSABLE | SHADOW | TRANSLUCENT);
		set(select,POLYGON);
		
		pass_to_gui(select); // update the properties panel
	}
}

// The simplest function in the kernel. ;)
void random_pan() {

	if(select) {
		
		select.pan = random(360);		
		
	}

}

void _mat_select(var id) {

	// Clear evidence first
	int i = id;
	while(i > 0) {
		
		button_state(panProp_2,i,0);
		i--;
		
	}

	i = id; // fetch again
	while(i < 16) {
		
		button_state(panProp_2,i,0);
		i++;
		
	}

	button_state(panProp_2,id,1);

	if(select) {
		
		switch(id) {
			
			case 1: // Lava
			
			mat_type = select_mat_lava;
			pass_mat_to_object();
			
			if(is(panMat_Sub1,SHOW)) {
				reset(panMat_Sub1,SHOW);
				
			}
			
			break;
			
			case 2: // Marble
			
			mat_type = select_mat_marble;
			pass_mat_to_object();
			
			if(is(panMat_Sub1,SHOW)) {
				reset(panMat_Sub1,SHOW);
				
			}
			
			break;
			
			case 3: // Smaragd
			
			mat_type = select_mat_smaragd;
			pass_mat_to_object();
			
			if(is(panMat_Sub1,SHOW)) {
				reset(panMat_Sub1,SHOW);
				
			}
			
			break;
			
			case 4: // Lavender rose
			
			mat_type = select_mat_lavenderrose;
			pass_mat_to_object();
			
			if(is(panMat_Sub1,SHOW)) {
				reset(panMat_Sub1,SHOW);
				
			}
			
			break;
			
			case 5: // Bitter lemon
			
			mat_type = select_mat_bitterlemon;
			pass_mat_to_object();
			
			if(is(panMat_Sub1,SHOW)) {
				reset(panMat_Sub1,SHOW);
				
			}
			
			break;
			
			case 6: // Peach orange
			
			mat_type = select_mat_peachorange;
			pass_mat_to_object();
			
			if(is(panMat_Sub1,SHOW)) {
				reset(panMat_Sub1,SHOW);
				
			}
			
			break;
			
			case 7: // Pure white light
			
			mat_type = select_mat_purewhite;
			pass_mat_to_object();
			
			if(is(panMat_Sub1,SHOW)) {
				reset(panMat_Sub1,SHOW);
				
			}
			
			break;
			
			case 8: // Metallic
			
			mat_type = select_mat_metal;
			pass_mat_to_object();
			
			if(is(panMat_Sub1,SHOW)) {
				reset(panMat_Sub1,SHOW);
				
			}
			
			break;
			
			case 9: // Pure black
			
			mat_type = select_mat_black;
			pass_mat_to_object();
			
			if(is(panMat_Sub1,SHOW)) {
				reset(panMat_Sub1,SHOW);
				
			}
			
			break;
			
			case 10: // Soft pale lilac
			
			mat_type = select_mat_palelilac;
			pass_mat_to_object();
			
			if(is(panMat_Sub1,SHOW)) {
				reset(panMat_Sub1,SHOW);
				
			}
			
			break;
			
			case 11: // Custom material #1
			
			mat_type = select_custom_mat1;
			pass_mat_to_object();
			
			/*
			a quick terrible ugly hack
			normally panMat_Sub1 will only be updated
			if you click 1 "Edit Material",
			but this hack allows you to update panMat_Sub1 directly
			without pressing that button.
			
			this can be useful if you've already opened panMat_Sub1
			and select another customizable material, the panel
			will be updated immediately without having to click
			the "Edit Material" button again.
			*/
			if(is(panMat_Sub1,SHOW))
			pass_mat_to_matsub(mat_custom[0]);
			
			break;
			
			case 12: // Custom material #2
			
			mat_type = select_custom_mat2;
			pass_mat_to_object();
			
			if(is(panMat_Sub1,SHOW))
			pass_mat_to_matsub(mat_custom[1]);
			
			break;
			
			case 13: // Custom material #3
			
			mat_type = select_custom_mat3;
			pass_mat_to_object();
			
			if(is(panMat_Sub1,SHOW))
			pass_mat_to_matsub(mat_custom[2]);
			
			break;
			
			case 14: // Custom material #4
			mat_type = select_custom_mat4;
			pass_mat_to_object();
			
			if(is(panMat_Sub1,SHOW))
			pass_mat_to_matsub(mat_custom[3]);
			
			break;
			
			case 15: // Default
			
			mat_type = select_mat_null;
			pass_mat_to_object();
			
			break;		
			
			default:
			sys_exit(NULL);
			break;
			
		}
		
	}

}

void pass_mat_to_object() {

	if(select) { // make sure something have been saved to mat_temp
		
		switch(mat_type) {
			
			case select_mat_null :
			mat_temp = mtl_model;
			break;
			
			case select_mat_lava :
			mat_temp = mat_lava;
			break;
			
			case select_mat_smaragd :
			mat_temp = mat_smaragd;
			break;
			
			case select_mat_marble :
			mat_temp = mat_marble;
			break;
			
			case select_mat_lavenderrose :
			mat_temp = mat_lavenderrose;
			break;
			
			case select_mat_bitterlemon :
			mat_temp = mat_bitterlemon;
			break;
			
			case select_mat_peachorange :
			mat_temp = mat_peachorange;
			break;
			
			case select_mat_purewhite :
			mat_temp = mat_purewhite;
			break;
			
			case select_mat_metal :
			mat_temp = mat_metal; // this is just one of the predefined materials.
			break;
			
			case select_mat_black :
			mat_temp = mat_black;
			break;
			
			case select_mat_palelilac :
			mat_temp = mat_palelilac;
			break;
			
			// Custom materials
			case select_custom_mat1 :
			mat_temp = mat_custom[0];
			break;
			
			case select_custom_mat2 :
			mat_temp = mat_custom[1];
			break;
			
			case select_custom_mat3 :
			mat_temp = mat_custom[2];
			break;
			
			case select_custom_mat4 :
			mat_temp = mat_custom[3];
			break;
			
			default:
			printf("mat_type exceeded/wrong.");
			break; 
			
		}
		
	}

}

void pass_object_to_clipboard(ENTITY *o, obj_form *of) {
	
	if(o.obj_type == terrain_edit) return;

	////////////////////////////////////////////////////////////
	// Pass general information to the clipboard first.
	////////////////////////////////////////////////////////////
	of._scale_x = o.scale_x;
	of._scale_y = o.scale_y;
	of._scale_z = o.scale_z;

	of._pan = o.pan;
	of._tilt = o.tilt;
	of._roll = o.roll;

	of._alpha = o.alpha;
	of._ambient = o.ambient;

	////////////////////////////////////////////////////////////
	switch(o.obj_type) {
		
		////////////////////////////////////////////////////////////
		case mdl:
		
		if(is(o,BRIGHT)) of._flags[0] = 1;
		else of._flags[0] = 0;
		
		if(is(o,INVISIBLE)) of._flags[1] = 1;
		else of._flags[1] = 0;
		
		if(is(o,NOFOG)) of._flags[2] = 1;
		else of._flags[2] = 0;
		
		if(is(o,OVERLAY)) of._flags[3] = 1;
		else of._flags[3] = 0;
		
		if(is(o,PASSABLE)) of._flags[4] = 1;
		else of._flags[4] = 0;
		
		if(is(o,POLYGON)) of._flags[5] = 1;
		else of._flags[5] = 0;
		
		if(is(o,SHADOW)) of._flags[6] = 1;
		else of._flags[6] = 0;
		
		if(is(o,TRANSLUCENT)) of._flags[7] = 1;
		else of._flags[7] = 0;
		
		of.oid = o.obj_ID;
		of.of_objtype = o.obj_type;
		
		of.pStatic = o.obj_dynamic;
		of.pPhysics = o.obj_physics;
		
		// Flag indicates that the copy progress has done.
		// Also, it can be used to determine if the clipboard has any piece of data or not.
		of.dp = 1;
		
		break;
		////////////////////////////////////////////////////////////
		
		////////////////////////////////////////////////////////////
		case light:
		
		of._red = o.red;
		of._green = o.green;
		of._blue = o.blue;
		of._range = o.lightrange;
		of._light_mode = o.light_mode;
		
		of.of_objtype = o.obj_type;
		
		of.dp = 1;
		
		break;
		////////////////////////////////////////////////////////////
		
		////////////////////////////////////////////////////////////
		case snd:
		
		of.of_objtype = o.obj_type;
		of.oid = o.obj_ID;
		
		of.dp = 1;
		
		break;
		////////////////////////////////////////////////////////////
		
		////////////////////////////////////////////////////////////
		case part:
		
		of.of_objtype = o.obj_type;
		of.oid = o.obj_ID;
		
		of.dp = 1;
		
		break;
		////////////////////////////////////////////////////////////
		
		////////////////////////////////////////////////////////////
		case node_placer:
		
		of.of_objtype = o.obj_type;
		
		of.dp = 1;
		
		break;
		////////////////////////////////////////////////////////////
		
		default:
		sys_exit(NULL);
		break;
		
	}

}

void pass_clipboard_to_object(ENTITY *e) {
	
	if(e.obj_type == terrain_edit) return;

	////////////////////////////////////////////////////////////
	// As usual, pass general data first.
	////////////////////////////////////////////////////////////
	e.ambient = clipboard._ambient;
	e.alpha = clipboard._alpha;

	e.scale_x = clipboard._scale_x;
	e.scale_y = clipboard._scale_y;
	e.scale_z = clipboard._scale_z;

	e.pan = clipboard._pan;
	e.tilt = clipboard._tilt;
	e.roll = clipboard._roll;

	////////////////////////////////////////////////////////////	
	switch(clipboard.of_objtype) {
		
		////////////////////////////////////////////////////////////
		case mdl:
		
		e.obj_type = clipboard.of_objtype;
		e.obj_ID = clipboard.oid;
		
		e.skill2 = clipboard.pStatic;
		e.skill3 = clipboard.pPhysics;
		e.material = clipboard.m;
		
		if(clipboard._flags[0]) set(e,BRIGHT);
		else reset(e,BRIGHT);
		
		if(clipboard._flags[1]) set(e,INVISIBLE);
		else reset(e,INVISIBLE);
		
		if(clipboard._flags[2]) set(e,NOFOG);
		else reset(e,NOFOG);
		
		if(clipboard._flags[3]) set(e,OVERLAY);
		else reset(e,OVERLAY);
		
		if(clipboard._flags[4]) set(e,PASSABLE);
		else reset(e,PASSABLE);
		
		if(clipboard._flags[5]) set(e,POLYGON);
		else reset(e,POLYGON);
		
		if(clipboard._flags[6]) set(e,SHADOW);
		else reset(e,SHADOW);
		
		if(clipboard._flags[7]) set(e,TRANSLUCENT);
		else reset(e,TRANSLUCENT);
		
		break;
		////////////////////////////////////////////////////////////
		
		////////////////////////////////////////////////////////////
		case light:
		
		e.red = clipboard._red;
		e.green = clipboard._green;
		e.blue = clipboard._blue;
		e.lightrange = clipboard._range;
		e.light_mode = clipboard._light_mode;
		
		e.material = mtl_model;
		
		break;
		////////////////////////////////////////////////////////////
		
		////////////////////////////////////////////////////////////
		case part:
		
		e.material = mtl_model;
		
		break;
		////////////////////////////////////////////////////////////
		
		////////////////////////////////////////////////////////////
		case snd:
		
		e.material = mtl_sprite;
		
		break;
		////////////////////////////////////////////////////////////
		
		////////////////////////////////////////////////////////////
		default:
		sys_exit(NULL);
		break;
		////////////////////////////////////////////////////////////
		
	}

}

void obj_cut() {

	if(select) {
		
		pass_object_to_clipboard(select,clipboard);
		
		if(select.obj_type == mdl) 
		{
			// Perform manual access to clipboard to copy material
			
			/*
			select is selected.
			so something must have been copied into mat_temp.
			so I directly take mat_temp and copy it into the clipboard.
			
			otherwise if we pass select.material to clipboard.m,
			mat_select is passed but not select's material.
			*/
			clipboard.m = mat_temp;
		}
		
		ptr_remove(select);
		select = NULL;
	}

}

void obj_copy() {

	if(select) {
		
		pass_object_to_clipboard(select,clipboard);
		
		if(select.obj_type == mdl) 
		{
			//		// Perform manual access to clipboard to copy material
			clipboard.m = mat_temp;
		}
	}

}

void obj_paste() {

	if(clipboard.dp) {
		
		int _obj_type_old = _obj_type, obj_ID_old;
		
		if(clipboard.of_objtype == part) {
			
			obj_ID_old = num_partobjs;
			num_partobjs = clipboard.oid;
			
		}
		if(clipboard.of_objtype == mdl) {
			
			obj_ID_old = num_mdlobjs;
			num_mdlobjs = clipboard.oid;
			
		}
		
		if(clipboard.of_objtype == snd) {
			
			obj_ID_old = num_sndobjs;
			num_sndobjs = clipboard.oid;
			
		}
		
		_obj_type = clipboard.of_objtype;
		
		pass_clipboard_to_object(obj_create());
		
		if(clipboard.of_objtype == part) num_partobjs = obj_ID_old;
		if(clipboard.of_objtype == mdl) num_mdlobjs = obj_ID_old;
		if(clipboard.of_objtype == snd) num_sndobjs = obj_ID_old;
		
	}

}

// Read material properties from a file and pass it to a
// previously-defined material.
void pass_file_to_material(MATERIAL *m, STRING *file) {
	while(m == NULL) wait(1); // wait for m to be completely created

	var vpass = file_open_read(file);
	if(vpass == 0) {
		
		printf("Failed to open %s for passing parameters.",file);
		return;
		
	}

	// Follow this form :
	/*

	ambient_red, ambient_green, ambient_blue
	specular_red, specular_green, specular_blue,
	diffuse_red, diffuse_green, diffuse_blue,
	emissive_red, emissive_green, emissive_blue,
	alpha, power (no need for albedo)

	*/

	m.ambient_red = file_var_read(vpass);
	m.ambient_green = file_var_read(vpass);
	m.ambient_blue = file_var_read(vpass);

	m.specular_red = file_var_read(vpass);
	m.specular_green = file_var_read(vpass);
	m.specular_blue = file_var_read(vpass);

	m.diffuse_red = file_var_read(vpass);
	m.diffuse_green = file_var_read(vpass);
	m.diffuse_blue = file_var_read(vpass);

	m.emissive_red = file_var_read(vpass);
	m.emissive_green = file_var_read(vpass);
	m.emissive_blue = file_var_read(vpass);

	m.alpha = file_var_read(vpass);
	m.power = file_var_read(vpass);

	file_close(vpass);
}

void pass_mat_to_matsub(MATERIAL *m) {
	while(m == NULL) wait(1);

	v_ambient_r = m.ambient_red;
	v_ambient_g = m.ambient_green;
	v_ambient_b = m.ambient_blue;

	v_diffuse_r = m.diffuse_red;
	v_diffuse_g = m.diffuse_green;
	v_diffuse_b = m.diffuse_blue;

	v_specular_r = m.specular_red;
	v_specular_g = m.specular_green;
	v_specular_b = m.specular_blue;

	v_emissive_r = m.emissive_red;
	v_emissive_g = m.emissive_green;
	v_emissive_b = m.emissive_blue;

	v_power = m.power;
	v_alpha_m = m.alpha;
}

void pass_material_to_file(STRING *file, MATERIAL *m) {

	while(m == NULL) wait(1);

	var vpass = file_open_write(file);
	if(vpass == 0) {
		
		printf("Failed to open %s for writing data.",file);
		return;
		
	}

	// Copy values from the sliders
	m.ambient_red = v_ambient_r;
	m.ambient_green = v_ambient_g;
	m.ambient_blue = v_ambient_b;

	m.specular_red = v_specular_r;
	m.specular_green = v_specular_g;
	m.specular_blue = v_specular_b;

	m.diffuse_red = v_diffuse_r;
	m.diffuse_green = v_diffuse_g;
	m.diffuse_blue = v_diffuse_b;

	m.emissive_red = v_emissive_r;
	m.emissive_green = v_emissive_g;
	m.emissive_blue = v_emissive_b;

	m.alpha = v_alpha_m;
	m.power = v_power;

	// Write these copied values to vpass handle
	file_var_write(vpass,m.ambient_red);
	file_var_write(vpass,m.ambient_green);
	file_var_write(vpass,m.ambient_blue);

	file_var_write(vpass,m.specular_red);
	file_var_write(vpass,m.specular_green);
	file_var_write(vpass,m.specular_blue);

	file_var_write(vpass,m.diffuse_red);
	file_var_write(vpass,m.diffuse_green);
	file_var_write(vpass,m.diffuse_blue);

	file_var_write(vpass,m.emissive_red);
	file_var_write(vpass,m.emissive_green);
	file_var_write(vpass,m.emissive_blue);

	file_var_write(vpass,m.alpha);
	file_var_write(vpass,m.power);

	file_close(vpass);
	
	// close the panel.
	if(is(panMat_Sub1,SHOW)) reset(panMat_Sub1,SHOW);
}

void mat_save() {

	// Material saving is available only to custom materials
	switch(mat_type) {
		
		case select_custom_mat1 :
		pass_material_to_file("./src/cfg/mat_custom_1.cfg",mat_custom[0]);
		
		break;
		//////////////////////////////////////////////////////////////
		
		case select_custom_mat2 :
		pass_material_to_file("./src/cfg/mat_custom_2.cfg",mat_custom[1]);
		
		break;
		//////////////////////////////////////////////////////////////
		
		case select_custom_mat3 :
		pass_material_to_file("./src/cfg/mat_custom_3.cfg",mat_custom[2]);
		
		break;
		//////////////////////////////////////////////////////////////
		
		case select_custom_mat4 :
		pass_material_to_file("./src/cfg/mat_custom_4.cfg",mat_custom[3]);
		
		break;
		//////////////////////////////////////////////////////////////
		
		default:
		// This line will never be executed.
		printf("Material saving is available only to custom materials.");
		break;
	}

}

////////////////////////////////////////////////////////////
// The following function will handle how the object is manipulated: move, rotate, or scale.
// While holding mouse_left, press L/R Alt to downscale the object,
// or release it to upscale the object.
// Why do I have to comment the lines above if you've already
// read through the code.
// Actually this is just an extended version of follow_pointer
// because I'm too lazy to code a new one.
////////////////////////////////////////////////////////////
void obj_manip_interface()
{
	while(mouse_left && (manip_type > 0 && manip_type < 4))
	{
		
		if(manip_type == scale) 
		{
			hideGUI();
			
			if(key_alt) {
				
				my.scale_x -= .05;
				my.scale_y -= .05;
				my.scale_z -= .05;
				
			}
			
			else {
				
				my.scale_x += .05;
				my.scale_y += .05;
				my.scale_z += .05;
				
			}
			
		}
		
		if(manip_type == move) {
			
			hideGUI();
			
			v1.x = mouse_pos.x;
			v1.y = mouse_pos.y;
			v1.z = 0;
			vec_for_screen(v1,camera);
			v2.x = mouse_pos.x;
			v2.y = mouse_pos.y;
			v2.z = 200000;
			vec_for_screen(v2,camera);
			
			c_trace(v1.x,v2.x,IGNORE_ME | IGNORE_PASSABLE | IGNORE_MODELS);
			vec_set(my.x,hit.x);
			
		}
		
		if(manip_type == rotate) {
			
			hideGUI();
			
			my.pan = -mouse_pos.x;
			//			my.tilt = -mouse_pos.y;
			
		}
		
		

		wait (1);
	}

	showGUI();

}

void obj_manip_setup()
{
	my.emask |= ENABLE_CLICK;
	my.event = obj_manip_interface;
}

////////////////////////////////////////////////////////////
// These functions will be assigned to move, rotate, scale button respectively.
////////////////////////////////////////////////////////////

// stupid switchers
// lite-C compiler: stupid programmer
void switch_to_move() {
	
	/*
	// Houston we got a problem here !
	if(!is_camera) {
		
		int i;
		for(i = 1;i < 4;i++) button_state(panMain_Top,i,0);
		manip_type = scale+1;
		
		return; // Kill him (stop him from doing bad things)
		
	}
	*/

	// Check its state first.
	if(button_state(panMain_Top,1,-1)) {
		
		button_state(panMain_Top,2,0);
		button_state(panMain_Top,3,0);
		
		// Switch to ' object move ' state.
		manip_type = move;
		
		reset(panRotateHelp,SHOW);
		reset(panScaleHelp,SHOW);
		
	}

	else {
		
		// The loop can't check this so nothing will be assigned
		// to manip_type.
		manip_type = scale+1;
		
	}
}

void switch_to_rotate() {
	
	/*
	if(!is_camera) {
		
		int i;
		for(i = 1;i < 4;i++) button_state(panMain_Top,i,0);
		manip_type = scale+1;
		
		return; // Kill him (stop him from doing bad things)
		
	}
	*/

	if(button_state(panMain_Top,2,-1)) {
		
		button_state(panMain_Top,1,0);
		button_state(panMain_Top,3,0);
		
		manip_type = rotate;
		
		set(panRotateHelp,SHOW);
		reset(panScaleHelp,SHOW);
		
	}

	else {
		
		manip_type = scale+1;
		reset(panRotateHelp,SHOW);
		
	}
}

void switch_to_scale() {
	
	/*
	if(!is_camera) {
		
		int i;
		for(i = 1;i < 4;i++) button_state(panMain_Top,i,0);
		manip_type = scale+1;
		
		return; // Kill him (stop him from doing bad things)
		
	}
	*/
	
	if(button_state(panMain_Top,3,-1)) {
		
		button_state(panMain_Top,1,0);
		button_state(panMain_Top,2,0);
		
		manip_type = scale;
		
		reset(panRotateHelp,SHOW);
		set(panScaleHelp,SHOW);
		
	}

	else {
		
		manip_type=scale+1;
		reset(panScaleHelp,SHOW);
		
	}

}

void hideGUI() {
	
	if(select) {
		
		// Deselect any selected entity first
		if(select.obj_type == light) _light(0);
		if(select.obj_type == mdl) prop(0);
		if(select.obj_type == snd) sound(0);
		if(select.obj_type == part) _part(0);
		
		select.material = mat_temp;
		select = NULL;
		
	}

	reset(panMain_Top,SHOW);
	reset(panMain_Bottom,SHOW);
	reset(panMain_Play,SHOW);

	// Also disables any remaining active content.
	reset(buttonlst_submenu_object,SHOW);
	reset(buttonlst_submenu_path,SHOW);
	reset(buttonlst_submenu_terrain,SHOW);
	reset(panRotateHelp,SHOW);
	reset(panScaleHelp,SHOW);
}

void showGUI() {

	set(panMain_Top,SHOW);
	set(panMain_Bottom,SHOW);
	set(panMain_Play,SHOW);

}

void showr(FONT *f, STRING *r)
{
	proc_kill(4);

	TEXT *rt = txt_create(1,1);

	rt->font = f;
	str_cpy((rt.pstring)[0],r);

	rt->pos_x = screen_size.x -  str_width((rt.pstring)[0],f) - BORDER - 30; // -30 because I'm using the free edition.
	rt->pos_y = BORDER;

	set(rt,SHOW);

	// It's supposed to be "while(Game Is Running) wait(1);"
	// but I haven't added into the game yet.
	while(1) wait(1);

	txt_remove(rt);
}

void objadd() {

	hideGUI();

	set(panObj_Main,SHOW);
	set(panObj_Subbar,SHOW);
	set(panObj_Subbar_slider,SHOW);
	set(panObj_Main_X,SHOW);
	
	ctrl = 0;

}

void objpartadd() {
	
	hideGUI();
	set(panObj_Part_Main,SHOW);
	set(panObj_Part_Main_X,SHOW);
	set(panObj_Part_slider,SHOW);
	
	ctrl = 0;
}

void objsndadd() {
	
	hideGUI();
	set(panObj_Snd_Main,SHOW);
	set(panObj_Snd_Main_X,SHOW);
	set(panObj_Snd_slider,SHOW);
	
	ctrl = 0;
	
}

void objlightadd() {
	
	set(panLightNoti,SHOW);
	
	wait(-5);
	
	reset(panLightNoti,SHOW);
	
}

// Just a small function for use within panObj_Subbar_switcher(var).
// Updates the size of p according to b's size.
void update_size(PANEL *p, BMAP *b) {
	while(b == NULL || p == NULL) wait(1);

	p.size_x = bmap_width(b);
	p.size_y = bmap_height(b);

}

/*
////////////////////////////////////////////////////////////
// This struct was created by trial and error.
// Sucks to be that developer.
// Wait...I'm the developer.
////////////////////////////////////////////////////////////
VECTOR *vt = {
	
	x = 250;
	y = 135;
	z = -30;
	
}

ENTITY *creat[500];
*/

// We met again stupid switcher.
// lite-C compiler: Without me you're nothing bitch.
void panObj_Subbar_switcher(var id) {
	// 10 = upper limit (9 buttons); 0 = lower limit
	// This is more efficient than using a bunch of switch..case.

	int i;

	// Switches off all available buttons after id.
	for(i = id + 1;i < 10;i++) button_state(panObj_Subbar,i,0);
	// Switches off all available buttons before id.
	for(i = id - 1;i > 0;i--) button_state(panObj_Subbar,i,0);

	// Switches on id.
	button_state(panObj_Subbar,id,1);

	// Eeehhh..switch..case..I hate it.

	switch(id) {
		
		case 1: // ANMS
		
		panObj_Main.bmap = panObj_anms;
		update_size(panObj_Main,panObj_anms);
		
		ctrl = 0;
		
		/*
		int i;
		
		for(i = 0;i < 50;i++) {
			
			if(str_cmp(mdlobjs_table_ptr[i],"  ")) {
			   
			   i++;
			   continue;
			   
			}
			
			creat[i] = ent_createlayer(mdlobjs_table_ptr[i],SHOW,NULL);
			layer_sort(creat[i],999);
			
			vec_set(creat[i].x,vt.x);
			vt.y -= 30;
			vec_set(creat[i].y,vt.y);
			
			vec_set(creat[i].z,vt.z);
			
			set(creat, PASSABLE | OVERLAY);
			creat[i].scale_x = creat[i].scale_y = creat[i].scale_z /= 2.5;
			
		}
		*/
		
		break;
		
		case 2: // ARCH
		
		panObj_Main.bmap = panObj_arch;
		update_size(panObj_Main,panObj_arch);
		
		ctrl = 0;
		
		break;
		
		case 3: // BLANDS
		
		panObj_Main.bmap = panObj_blands;
		update_size(panObj_Main,panObj_blands);
		
		ctrl = 0;
		
		break;
		
		case 4: // CHARS
		
		panObj_Main.bmap = panObj_chars;
		update_size(panObj_Main,panObj_chars);
		
		ctrl = 0;
		
		break;
		
		case 5: // ETC
		
		panObj_Main.bmap = panObj_etc;
		update_size(panObj_Main,panObj_etc);
		
		ctrl = 0;
		
		break;
		
		case 6: // FOOD
		
		panObj_Main.bmap = panObj_food;
		update_size(panObj_Main,panObj_food);
		
		ctrl = 0;
		
		break;
		
		case 7: // MACHS
		
		panObj_Main.bmap = panObj_machs;
		update_size(panObj_Main,panObj_machs);
		
		ctrl = 0;
		
		break; 
		
		case 8: // PLANTS
		
		panObj_Main.bmap = panObj_plants;
		update_size(panObj_Main,panObj_plants);
		
		ctrl = 0;
		
		break;
		
		case 9: // TPORTTS
		
		panObj_Main.bmap = panObj_tportts;
		update_size(panObj_Main,panObj_tportts);
		
		ctrl = 0;
		
		break;
		
		default:
		sys_exit(NULL);
		break;
		
	}

}

void config_write_video(STRING *cf) {

	var file = file_open_write(cf);
	if(!file) {
		
		printf("Failed to open file handle for writing configuration to %s",cf);
		return;
		
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
	- video_mode
	- video_depth
	- video_screen

	*/

	file_var_write(file,d3d_anisotropy);
	file_var_write(file,d3d_antialias);
	file_var_write(file,d3d_mipmapping);
	file_var_write(file,d3d_triplebuffer);
	file_var_write(file,d3d_lightres);
	file_var_write(file,video_aspect);
	file_var_write(file,video_gamma);
	file_var_write(file,video_mode);
	file_var_write(file,video_depth);
	file_var_write(file,video_screen);

	file_close(file);

}

// This function must be called prior to loading the level.
void config_read_video(STRING *cf) {

	var file = file_open_read(cf);
	if(!file) { // Fail? Then use default settings.
		
		printf("Failed to open file handle for reading configuration from %s.\nDefault configuration will now be applied.",cf);
		
		/* Default config. goes here. */
		
		return;
		
	}

	d3d_anisotropy = file_var_read(file);
	d3d_antialias = file_var_read(file);
	d3d_mipmapping = file_var_read(file);
	d3d_triplebuffer = file_var_read(file);
	d3d_lightres = file_var_read(file);

	video_aspect = file_var_read(file);
	video_gamma = file_var_read(file);
	video_mode = file_var_read(file);
	video_depth = file_var_read(file);
	video_screen = file_var_read(file);

	file_close(file);
}

//void save_level(STRING *filef) {
	//	
	//	STRING *filef_original = str_create("#300");
	//	str_cpy(filef_original,filef);
	//	
	//	var hndl_sys = file_open_write(str_cat(filef,"_sys.txt"));
	//	str_cpy(filef,filef_original);
	//	
	//	var hndl_mdlobjs = file_open_write(str_cat(filef,"_ents.txt"));
	//	str_cpy(filef,filef_original);
	//	
	//	var hndl_lights = file_open_write(str_cat(filef,"_lights.txt"));
	//	str_cpy(filef,filef_original);
	//	
	//	var hndl_parts = file_open_write(str_cat(filef,"_parts.txt"));
	//	str_cpy(filef,filef_original);
	//	
	//	var hndl_snds = file_open_write(str_cat(filef,"_snds.txt"));
	//	str_cpy(filef,filef_original);
	//	
	//	var hndl_terraindata = file_open_write(str_cat(filef,"_tdata.txt"));
	//	str_cpy(filef,filef_original);
	//	
	//	var hndl_nodedata = file_open_write(str_cat(filef,"_ndata.txt"));
	//	str_cpy(filef,filef_original);
	//	
	//	var hndl_garbage = file_open_write(str_cat(filef,"_trash.txt"));
	//	str_cpy(filef,filef_original);
	//	
	//	// Get the first entity in entities list
	//	you = ent_next(NULL);
	//	
	//	// Begin checking and writing entities data into various file handles.
	//	while(you) {
		//		
		//		switch(you.obj_type) {
			//			
			//			case mdl :
			//			/*
			//			x,y,z
			//			scale_x,scale_y,scale_z
			//			pan,tilt,roll
			//			alpha,ambient
			//			8 flags:
			//			- BRIGHT/INVISIBLE/NOFOG/OVERLAY/PASSABLE/POLYGON/SHADOW/TRANSLUCENT
			//			object ID
			//			// material
			//			static/dynamic
			//			physics
			//			object_type
			//			*/
			//			file_var_write(hndl_mdlobjs,you.obj_ID); // Object ID
			//			file_var_write(hndl_mdlobjs,you.obj_type); // The type of the object
			//			
			//			file_var_write(hndl_mdlobjs,you.x);
			//			file_var_write(hndl_mdlobjs,you.y);
			//			file_var_write(hndl_mdlobjs,you.z);
			//			
			//			file_var_write(hndl_mdlobjs,you.scale_x);
			//			file_var_write(hndl_mdlobjs,you.scale_y);
			//			file_var_write(hndl_mdlobjs,you.scale_z);
			//			
			//			file_var_write(hndl_mdlobjs,you.pan);
			//			file_var_write(hndl_mdlobjs,you.tilt);
			//			file_var_write(hndl_mdlobjs,you.roll);
			//			
			//			file_var_write(hndl_mdlobjs,you.alpha);
			//			file_var_write(hndl_mdlobjs,you.ambient);
			//			
			//			if(is(you,BRIGHT)) file_var_write(hndl_mdlobjs,1);
			//			else file_var_write(hndl_mdlobjs,0);
			//			
			//			if(is(you,INVISIBLE)) file_var_write(hndl_mdlobjs,1);
			//			else file_var_write(hndl_mdlobjs,0);
			//			
			//			if(is(you,NOFOG)) file_var_write(hndl_mdlobjs,1);
			//			else file_var_write(hndl_mdlobjs,0);
			//			
			//			if(is(you,OVERLAY)) file_var_write(hndl_mdlobjs,1);
			//			else file_var_write(hndl_mdlobjs,0);
			//			
			//			if(is(you,PASSABLE)) file_var_write(hndl_mdlobjs,1);
			//			else file_var_write(hndl_mdlobjs,0);
			//			
			//			if(is(you,POLYGON)) file_var_write(hndl_mdlobjs,1);
			//			else file_var_write(hndl_mdlobjs,0);
			//			
			//			if(is(you,SHADOW)) file_var_write(hndl_mdlobjs,1);
			//			else file_var_write(hndl_mdlobjs,0);
			//			
			//			if(is(you,TRANSLUCENT)) file_var_write(hndl_mdlobjs,1);
			//			else file_var_write(hndl_mdlobjs,0);
			//			
			//			file_var_write(hndl_mdlobjs,you.obj_dynamic); // Object state, dynamic/static
			//			file_var_write(hndl_mdlobjs,you.obj_physics); // Physics flag
			//			
			//			break;
			//			
			//			case light :
			//			/*
			//			x,y,z,pan,tilt,roll, alpha,ambient
			//			r/g/b
			//			lightrange
			//			mode
			//			*/
			//			
			//			file_var_write(hndl_lights,you.x);
			//			file_var_write(hndl_lights,you.y);
			//			file_var_write(hndl_lights,you.z);
			//			
			//			file_var_write(hndl_lights,you.pan);
			//			file_var_write(hndl_lights,you.tilt);
			//			file_var_write(hndl_lights,you.roll);
			//			
			//			file_var_write(hndl_lights,you.ambient);
			//			file_var_write(hndl_lights,you.alpha);
			//			
			//			file_var_write(hndl_lights,you.red);
			//			file_var_write(hndl_lights,you.green);
			//			file_var_write(hndl_lights,you.blue);
			//			
			//			file_var_write(hndl_lights,you.lightrange);
			//			file_var_write(hndl_lights,you.light_mode);
			//			file_var_write(hndl_lights,you.flick_time);
			//			break;
			//			
			//			case part :
			//			
			//			file_var_write(hndl_parts,you.obj_ID);
			//			file_var_write(hndl_parts,you.obj_type);
			//			
			//			/*x,y,z,pan,tilt,roll,ambient,alpha
			//			obj_ID,obj_type*/
			//			file_var_write(hndl_parts,you.x);
			//			file_var_write(hndl_parts,you.y);
			//			file_var_write(hndl_parts,you.z);
			//			
			//			file_var_write(hndl_parts,you.pan);
			//			file_var_write(hndl_parts,you.tilt);
			//			file_var_write(hndl_parts,you.roll);
			//			
			//			file_var_write(hndl_parts,you.ambient);
			//			file_var_write(hndl_parts,you.alpha);
			//			
			//			break;
			//			
			//			case snd :
			//			
			//			file_var_write(hndl_snds,you.obj_ID);
			//			file_var_write(hndl_snds,you.obj_type);
			//			
			//			/*x,y,z,pan,tilt,roll, ambient, alpha, obj_ID, obj_type */
			//			file_var_write(hndl_snds,you.x);
			//			file_var_write(hndl_snds,you.y);
			//			file_var_write(hndl_snds,you.z);
			//			
			//			file_var_write(hndl_snds,you.pan);
			//			file_var_write(hndl_snds,you.tilt);
			//			file_var_write(hndl_snds,you.roll);
			//			
			//			file_var_write(hndl_snds,you.ambient);
			//			file_var_write(hndl_snds,you.alpha);
			//			
			//			break;
			//			
			//			case node_placer :
			//			/*x,y,z*/
			//			file_var_write(hndl_nodedata,you.x);
			//			file_var_write(hndl_nodedata,you.y);
			//			file_var_write(hndl_nodedata,you.z);
			//			break;
			//			
			//			case terrain_edit :
			//			break;
			//			
			//			default: // garbage entities
			//			/* x,y,z, scale_x/y/z,pan,tilt,roll,
			//			alpha,ambient, +8 flags, */
			//			
			//			//you!=NULL
			//			file_var_write(hndl_garbage,you.x);
			//			file_var_write(hndl_garbage,you.y);
			//			file_var_write(hndl_garbage,you.z);
			//			
			//			file_var_write(hndl_garbage,you.scale_x);
			//			file_var_write(hndl_garbage,you.scale_y);
			//			file_var_write(hndl_garbage,you.scale_z);
			//			
			//			file_var_write(hndl_garbage,you.pan);
			//			file_var_write(hndl_garbage,you.tilt);
			//			file_var_write(hndl_garbage,you.roll);
			//			
			//			file_var_write(hndl_garbage,you.alpha);
			//			file_var_write(hndl_garbage,you.ambient);
			//			
			//			if(is(you,BRIGHT)) file_var_write(hndl_garbage,1);
			//			else file_var_write(hndl_garbage,0);
			//			
			//			if(is(you,INVISIBLE)) file_var_write(hndl_garbage,1);
			//			else file_var_write(hndl_garbage,0);
			//			
			//			if(is(you,NOFOG)) file_var_write(hndl_garbage,1);
			//			else file_var_write(hndl_garbage,0);
			//			
			//			if(is(you,OVERLAY)) file_var_write(hndl_garbage,1);
			//			else file_var_write(hndl_garbage,0);
			//			
			//			if(is(you,PASSABLE)) file_var_write(hndl_garbage,1);
			//			else file_var_write(hndl_garbage,0);
			//			
			//			if(is(you,POLYGON)) file_var_write(hndl_garbage,1);
			//			else file_var_write(hndl_garbage,0);
			//			
			//			if(is(you,SHADOW)) file_var_write(hndl_garbage,1);
			//			else file_var_write(hndl_garbage,0);
			//			
			//			if(is(you,TRANSLUCENT)) file_var_write(hndl_garbage,1);
			//			else file_var_write(hndl_garbage,0);
			//			
			//			break;
			//			
		//		}
		//		
		//		you = ent_next(you);
		//		wait(1);
		//		
	//	}
	//	
	//	file_var_write(hndl_mdlobjs,999999);
	//	
	//	// Write to system.
	//	file_var_write(hndl_sys,camera.x);
	//	file_var_write(hndl_sys,camera.y);
	//	file_var_write(hndl_sys,camera.z);
	//	file_var_write(hndl_sys,camera.pan);
	//	file_var_write(hndl_sys,camera.tilt);
	//	file_var_write(hndl_sys,camera.roll);
	//	file_var_write(hndl_sys,camera.aspect);
	//	file_var_write(hndl_sys,camera.arc);
	//	file_var_write(hndl_sys,camera.ambient);
	//	file_var_write(hndl_sys,sun_light);
	//	file_var_write(hndl_sys,sun_angle.pan);
	//	file_var_write(hndl_sys,sun_angle.tilt);
	//	file_var_write(hndl_sys,sun_color.blue);
	//	file_var_write(hndl_sys,sun_color.green);
	//	file_var_write(hndl_sys,sun_color.red);
	//	file_var_write(hndl_sys,fog_color);
	//	file_var_write(hndl_sys,d3d_fogcolor1.red);
	//	file_var_write(hndl_sys,d3d_fogcolor1.green);
	//	file_var_write(hndl_sys,d3d_fogcolor1.blue);
	//	file_var_write(hndl_sys,d3d_fogcolor2.red);
	//	file_var_write(hndl_sys,d3d_fogcolor2.green);
	//	file_var_write(hndl_sys,d3d_fogcolor2.blue);
	//	file_var_write(hndl_sys,d3d_fogcolor3.red);
	//	file_var_write(hndl_sys,d3d_fogcolor3.green);
	//	file_var_write(hndl_sys,d3d_fogcolor3.blue);
	//	file_var_write(hndl_sys,d3d_fogcolor4.red);
	//	file_var_write(hndl_sys,d3d_fogcolor4.green);
	//	file_var_write(hndl_sys,d3d_fogcolor4.blue);
	//	file_var_write(hndl_sys,camera.fog_start);
	//	file_var_write(hndl_sys,camera.fog_end);
	//	file_var_write(hndl_sys,skCube);
	//	
	//	// Close
	//	file_close(hndl_sys);
	//	file_close(hndl_mdlobjs);
	//	file_close(hndl_lights);
	//	file_close(hndl_parts);
	//	file_close(hndl_snds);
	//	file_close(hndl_terraindata);
	//	file_close(hndl_nodedata);
	//	file_close(hndl_garbage);
//}

// Loads a new level
void new_level() {
	
	level_load("dry.wmb");
	/*
	switch(skCube) {
		
		case 0:
		
		_cube = ent_createlayer("s_shamrock+6.tga",SKY | CUBE | SHOW,5);
		layer_sort(_cube,6);
		
		break;
		
		case 1:
		
		_cube = ent_createlayer("s_ocean_sunset+6.tga",SKY | CUBE | SHOW,5);
		layer_sort(_cube,6);
		
		break;
	}
	*/
	camera.ambient = 50;
	
	ent_create("marker.mdl",nullvector,follow_pointer); // Create a mouse pointer.
	cam = ent_create("marker.mdl",vector(0,0,0),free_camera);
}

//void load_level(STRING *filef) {
	//	
	//	int i = _obj_type;
	//	ENTITY *tmp;
	//	
	//	int tmpID, tmpobjtype;
	//	VECTOR tmpVector;
	//	
	//	vec_zero(tmpVector);
	//	
	//	// Use the same stupid core as save_level
	//	STRING *filef_original = str_create("#300");
	//	str_cpy(filef_original,filef);
	//	
	//	var hndl_sys = file_open_read(str_cat(filef,"_sys.txt"));
	//	str_cpy(filef,filef_original);
	//	
	//	var hndl_mdlobjs = file_open_read(str_cat(filef,"_ents.txt"));
	//	str_cpy(filef,filef_original);
	//	
	//	var hndl_lights = file_open_read(str_cat(filef,"_lights.txt"));
	//	str_cpy(filef,filef_original);
	//	
	//	var hndl_parts = file_open_read(str_cat(filef,"_parts.txt"));
	//	str_cpy(filef,filef_original);
	//	
	//	var hndl_snds = file_open_read(str_cat(filef,"_snds.txt"));
	//	str_cpy(filef,filef_original);
	//	
	//	var hndl_terraindata = file_open_read(str_cat(filef,"_tdata.txt"));
	//	str_cpy(filef,filef_original);
	//	
	//	var hndl_nodedata = file_open_read(str_cat(filef,"_ndata.txt"));
	//	str_cpy(filef,filef_original);
	//	
	//	var hndl_garbage = file_open_read(str_cat(filef,"_trash.txt"));
	//	str_cpy(filef,filef_original);
	//	//////////////////////////////////////////////////////////////
	//	
	//	level_load("dry.wmb");
	//	
	//	// System
	//	camera.x = file_var_read(hndl_sys);
	//	camera.y = file_var_read(hndl_sys);
	//	camera.z = file_var_read(hndl_sys);
	//	camera.pan = file_var_read(hndl_sys);
	//	camera.tilt = file_var_read(hndl_sys);
	//	camera.roll = file_var_read(hndl_sys);
	//	camera.aspect = file_var_read(hndl_sys);
	//	camera.arc = file_var_read(hndl_sys);
	//	camera.ambient = file_var_read(hndl_sys);
	//	sun_light = file_var_read(hndl_sys);
	//	sun_angle.pan = file_var_read(hndl_sys);
	//	sun_angle.tilt = file_var_read(hndl_sys);
	//	sun_color.blue = file_var_read(hndl_sys);
	//	sun_color.green = file_var_read(hndl_sys);
	//	sun_color.red = file_var_read(hndl_sys);
	//	fog_color = file_var_read(hndl_sys);
	//	d3d_fogcolor1.red = file_var_read(hndl_sys);
	//	d3d_fogcolor1.green = file_var_read(hndl_sys);
	//	d3d_fogcolor1.blue = file_var_read(hndl_sys);
	//	d3d_fogcolor2.red = file_var_read(hndl_sys);
	//	d3d_fogcolor2.green = file_var_read(hndl_sys);
	//	d3d_fogcolor2.blue = file_var_read(hndl_sys);
	//	d3d_fogcolor3.red = file_var_read(hndl_sys);
	//	d3d_fogcolor3.green = file_var_read(hndl_sys);
	//	d3d_fogcolor3.blue = file_var_read(hndl_sys);
	//	d3d_fogcolor4.red = file_var_read(hndl_sys);
	//	d3d_fogcolor4.green = file_var_read(hndl_sys);
	//	d3d_fogcolor4.blue = file_var_read(hndl_sys);
	//	camera.fog_start = file_var_read(hndl_sys);
	//	camera.fog_end = file_var_read(hndl_sys);
	//	skCube = file_var_read(hndl_sys);
	//	
	//	file_close(hndl_sys);
	//	
	//	// filef_ents.txt
	//	var j = num_mdlobjs;
	//	
	//	tmpID = file_var_read(hndl_mdlobjs);
	//	tmpobjtype = file_var_read(hndl_mdlobjs);
	//	
	//	tmpVector.x = file_var_read(hndl_mdlobjs);
	//	tmpVector.y = file_var_read(hndl_mdlobjs);
	//	tmpVector.z = file_var_read(hndl_mdlobjs);
	//	
	//	tmp = ent_create(_str(mdlobjs_table_ptr[tmpID]),tmpVector,NULL);
	//	
	//	tmp.obj_ID = num_mdlobjs;
	//	tmp.obj_type = file_var_read(hndl_mdlobjs);
	//	
	//	camera.ambient = 50;
	//	
	//	ent_create("marker.mdl",nullvector,follow_pointer); // Create a mouse pointer.
	//	cam = ent_create("marker.mdl",vector(0,0,0),free_camera);
	//	
//}

// Cleaner
void clean() {
	
	// Scan through all entities in the current level.
	you = ent_next(NULL);
	while(you) {
		
		// scale_x = scale_y = scale_z so only scale_x is enough.
		if(you.scale_x < .001) {
			
			ptr_remove(you);
			
		}

		you = ent_next(you);

		wait(1);
		
	}
	
}


////////////////////////////////////////////////////////////
// Kernel-related functions.
////////////////////////////////////////////////////////////
void load_kernel(STRING *lvl_str) {

	// Initialization for loopix-project.com's MystyMood_Lite-C
	sky_curve = 2;
	sky_clip = -10;

	// Our own setup
	//	load_mystymood(1,0);

	// Read and setup video settings prior to executing other functions.
	config_read_video("./src/cfg/video_config.cfg");

	video_window(NULL,NULL,0,"craftbox 0.8 Pre-Alpha 4.1");

	_obj_type = 2;
	num_partobjs = 1;

	mouse_range = 500000;
	mouse_map = mouse;
	random_seed(0); // e.g. random light generators.

	// So that we can get access to the database.
	mdlobjs_table_ptr = mdlobjs_table;

	panHome.alpha = panProp.alpha = DEFAULT_ALPHA;

	// Initialize the databases and load them.
	init_database();
	init_database_snd(); // Sound database doesn't require a pointer to access.
	init_database_part(); // So does particle database.

	// Intialize and read custom materials' properties.
	int i;
	for(i = 0;i < 4;i++) mat_custom[i] = mtl_create();

	pass_file_to_material(mat_custom[0],"./src/cfg/mat_custom_1.cfg");
	pass_file_to_material(mat_custom[1],"./src/cfg/mat_custom_2.cfg");
	pass_file_to_material(mat_custom[2],"./src/cfg/mat_custom_3.cfg");
	pass_file_to_material(mat_custom[3],"./src/cfg/mat_custom_4.cfg");

	////////////////////////////////////////////////////////////
	// After all stages have done its job, we load the level and pass "something" to it. Actually I don't know what I mean by "something".
	////////////////////////////////////////////////////////////

	// If we want a video to be played...
	//		sharedGUI_playintro(100);
	//		wait_for(sharedGUI_playintro);

	// Intialize and load the GUI system.
	loadGUI();
	wait_for(loadGUI);

	// Load a blank level.
	new_level();
	
	// Some nice effects and further setup before the game can be started.
	sharedGUI_blackscreen(FADE_OUT,2);
	wait_for(sharedGUI_blackscreen);

	sharedGUI_mouse(1); // Enables the mouse.

	//	def_move();
	
	// Shortcut keys implementation
	while(1) {
		
		// These keys are combined together with the Ctrl key.
		if(key_ctrl) {
			
			if(key_c) {
				
				while(key_c) wait(1);
				obj_copy();
				
			}
			
			if(key_x) {
				
				while(key_x) wait(1);
				obj_cut();
				
			}
			
			if(key_v) {
				
				while(key_v) wait(1);
				obj_paste();
				
			}
			
			if(key_n) {
				
				while(key_n) wait(1);
				new_level();
				
			}
			
			/*
			if(key_p) {
				
				while(key_p) wait(1);
				
				if(select) prop(1);
				else prop(0);
				
			}
			*/
			
		}
		
		// These keys are combined together with the Alt key.
		if(key_alt) {
			
			if(key_f4) {
				
				while(key_f4) wait(1);
				
				/* 
				TODO: Perform various operations prior to
				call sys_exit
				*/
				
				// Operation #1
				printf(" I don't want to die =(( ");
				
				sys_exit(NULL);
				
			}
			
		}
		
		// These keys are pressed solely.
		
		// I seperately defined key_esc here
		// so I must disable the one that has been defined 
		// in ka7def2.c/default.c
		if(key_esc && !from_test_play) { // If ESC is pressed and we're not pressing ESC while we were in testing mode.
			
			while(key_esc) wait(1);
			home();
			
		}
		
		wait(1);
	}
	// End of shortcut keys implementation.

}

void loop_kernel() {

	while(1) 
	{
		
		// Prevent the cursor from going outside the level border
		if(!temp_pos.x) temp_pos.x = level_ent.max_x;
		if(!temp_pos.y) temp_pos.y = level_ent.max_y;
		if(!temp_pos.z) temp_pos.z = level_ent.max_z;
		
		if(key_t) 
		{
			while(key_t) wait(1);
			num_partobjs++;
		}
		
		if(key_y) {
			while(key_y) wait(1);
			num_partobjs--;
		}
		
		if(key_r) {
			
			while(key_r) wait(1);
			you = ent_next(NULL); // Point to the first entity in the list
			while(you) {
				
				ptr_remove(you);
				you = ent_next(you);
				
			}
			
			ent_create("marker.mdl",nullvector,follow_pointer); // Create a mouse pointer.
			cam = ent_create("marker.mdl",vector(0,0,0),free_camera);
			
		}
		
		if(mouse_left) 
		{
			while(mouse_left) wait(1);
			
			if(!mouse_panel)
			{
				if(!mouse_ent) obj_create();
				
				else
				{
					if(select)
					{
						
						if(select.obj_type == light) _light(0);
						if(select.obj_type == mdl) prop(0);
						if(select.obj_type == snd) sound(0);
						if(select.obj_type == part) _part(0);
						
						select.material = mat_temp;
						select = NULL;
					}
					
					select = mouse_ent;
					
					mat_temp = select.material; // Luc nay select da duoc xac dinh nen ta cu thoai mai
					select.material = mat_select;
					
					if(select.obj_type == light) _light(1);
					else _light(0);
					
					if(select.obj_type == mdl) prop(1);
					else prop(0);
					
					if(select.obj_type == snd) sound(1);
					else sound(0);
					
					if(select.obj_type == part) _part(1);
					else _part(0);
					
					pass_to_gui(select);
					
				}
				
				/*
				else
				{
					if(select)
					{
						if(mat_temp) select.material = mat_temp;
						else select.material = NULL;
						
						if(select.obj_type == light) _light(0);						
						if(select.obj_type == mdl) prop(0);
						if(select.obj_type == snd) sound(0);
						if(select.obj_type == part) _part(0);
						
						select = NULL;
					}
					
					_light(0);	
					_part(0);
					prop(0);
					sound(0);
					
					select = NULL;
				}
				*/
				
				wait(1);
				
			}		
			
		}
		
		wait(1);
		
	}

	////////////////////////////////////////////////////////////
	// Game exit point
	////////////////////////////////////////////////////////////
	sys_exit(NULL);

}

////////////////////////////////////////////////////////////
// This _startup function needs to be run alongside with
// kernel_loop. Don't ask why, they just don't share the
// same while loop...
// And no need for an extra call to main() because functions
// with _startup prefix execute themshelves automatically.
////////////////////////////////////////////////////////////
void misc_startup() {

	while(1) {
		
		
		
		
		if(select) {
			
			if(key_del) {
				
				ptr_remove(select);
				
				// After this nothing is selected so we disable panProp.
				prop(0);
				
			}
			
			//////////////////////////////////////////////////////////////
			// panProp
			select.alpha = v_alpha;
			select.ambient = v_ambient;
			
			if(button_state(panProp_1,1,-1)) set(select,BRIGHT);
			else reset(select,BRIGHT);
			
			if(button_state(panProp_1,2,-1)) set(select,INVISIBLE);
			else reset(select,INVISIBLE);
			
			if(button_state(panProp_1,3,-1)) set(select,NOFOG);
			else reset(select,NOFOG);
			
			if(button_state(panProp_1,4,-1)) set(select,OVERLAY);
			else reset(select,OVERLAY);
			
			if(button_state(panProp_1,5,-1)) set(select,PASSABLE);
			else reset(select,PASSABLE);
			
			if(button_state(panProp_1,6,-1)) set(select,POLYGON);
			else reset(select,POLYGON);
			
			if(button_state(panProp_1,7,-1)) set(select,SHADOW);
			else reset(select,SHADOW);
			
			if(button_state(panProp_1,8,-1)) set(select,TRANSLUCENT);
			else reset(select,TRANSLUCENT);
			//////////////////////////////////////////////////////////////
			
			//////////////////////////////////////////////////////////////
			// panLight
			select.red = v_lred;
			select.blue = v_lblue;
			select.green = v_lgreen;
			select.lightrange = v_lrange;
			
			if(button_state(panLight,2,-1)) {
				
				button_state(panLight,3,-1);
				select.light_mode = disco;
				
			}
			
			if(button_state(panLight,3,-1)) {
				
				button_state(panLight,2,-1);
				select.light_mode = flick;
				
			}
			
			if(button_state(panLight,2,-1) && button_state(panLight,3,-1)) {
				
				button_state(panLight,2,0);
				button_state(panLight,3,0);
				select.light_mode = 0;
				
			}
			
			// panProp
			// select.material now holds mat_select
			// so we must pass something else
			
		}
		
		else { // If select isn't selected.
			
			prop(0); // prop() somehow got stuck
			sound(0);
			_light(0);
			
		}
		
		/*
		if(key_cul) ctrl--;
		if(key_cur) ctrl++;
		*/
		
		if(ctrl<0) ctrl=0; // prevent unexpected situations
		if(ctrl>100) ctrl=100;
		
		panObj_Main.pos_x = (ctrl * (-bmap_width(panObj_Main.bmap) + screen_size.x))/100;
		panObj_Part_Main.pos_x = (ctrl * (-bmap_width(panObj_Part_Main.bmap) + screen_size.x))/100;
		panObj_Snd_Main.pos_x = (ctrl * (-bmap_width(panObj_Snd_Main.bmap) + screen_size.x))/100;
		
		if(panObj_Main.pos_x > 0) panObj_Main.pos_x = 0;
		if(panObj_Main.pos_x < -bmap_width(panObj_Main.bmap) + screen_size.x) {
			
			panObj_Main.pos_x = -bmap_width(panObj_Main.bmap) + screen_size.x;
			
		}
		
		if(panObj_Part_Main.pos_x > 0) panObj_Part_Main.pos_x = 0;
		if(panObj_Part_Main.pos_x < -bmap_width(panObj_Part_Main.bmap) + screen_size.x) {
			
			panObj_Part_Main.pos_x = -bmap_width(panObj_Part_Main.bmap) + screen_size.x;
			
		}
		
		if(panObj_Snd_Main.pos_x > 0) panObj_Snd_Main.pos_x = 0;
		if(panObj_Snd_Main.pos_x < -bmap_width(panObj_Snd_Main.bmap) + screen_size.x) {
			
			panObj_Snd_Main.pos_x = -bmap_width(panObj_Snd_Main.bmap) + screen_size.x;
			
		}
		
		wait(1);
		
	}

}

////////////////////////////////////////////////////////////
// Actions
// This is the place where magic happens. Walking people,
// flying birds,...anything that will be assigned to non-static
// objects in the game.
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// A patroller and a node.
////////////////////////////////////////////////////////////
action a_patroller()
{
	while(my == NULL && node <= 0) wait(1);

	VECTOR temp[3];
	set(my,POLYGON | SHADOW);

	while(true)
	{
		c_scan(my.x, my.pan, vector(360, 60, 1000), IGNORE_ME | SCAN_ENTS | SCAN_LIMIT);
		if(you)
		{
			my_target_node = you;
			my_target_node.scale_z = 2;
			vec_set(temp, my_target_node.x);
			vec_sub(temp, my.x);
			vec_to_angle(my.pan, temp);
			my.tilt = 0;
			while (vec_dist (my.x, my_target_node.x) > 50)
			{
				my.skill22 += 5 * time_step;
				c_move(my, vector(5 * time_step, 0, 0), nullvector, IGNORE_PASSABLE | GLIDE); // 5 = movement speed
				ent_animate(my, "walk", my.skill22, ANM_CYCLE);
				wait (1);
			}
			my.skill99 = 0;
			while (my.skill99 < my_target_node.skill1)
			{
				my.skill99 += time_step / 16;
				ent_animate(my, "stand", my.skill22, ANM_CYCLE);
				my.skill22 += 3 * time_step;
				wait (1);
			}
			ent_remove(my_target_node);
		}
		else
		{
			ent_animate(my, "stand", my.skill22, ANM_CYCLE);
			my.skill22 += 3 * time_step;
		}
		wait (1);
	}
}

////////////////////////////////////////////////////////////
// This is the camera controller I found when I was tweaking Mystymood.
// 5.7.2013 : This camera is good, but I have to partly rewrite it
// because...well, I won't explain, find out for yourself.
// This code won't be checked against engine_play because
// it will be killed prior to set engine_play to 1.
// and restored later when engine_play has been set to 0.
////////////////////////////////////////////////////////////
VECTOR *camera_force = { z = 0; }

void free_camera()
{
	var rotatespeed = 5;
	var speed = 40;
	
	set(my, INVISIBLE | POLYGON);
	
	vec_set(camera.x,my.x);
	vec_set(camera.pan,my.pan);
	vec_set(camera.tilt,my.tilt);

	while(1)
	{	
		camera_force.x = (key_w - key_s)*speed*time_step;
		camera_force.y = (key_a - key_d)*speed*time_step;
		
		c_move(my,camera_force,nullvector,GLIDE+IGNORE_PASSABLE+IGNORE_PASSENTS+IGNORE_PUSH);
		vec_set(camera.x,vector(my.x,my.y,my.z+15));
		
		camera.tilt += rotatespeed * mouse_right*mouse_force.y * time_step;
		camera.pan += rotatespeed * mouse_right*-mouse_force.x * time_step;
		
		vec_set(my.tilt,camera.tilt);
		vec_set(my.pan,camera.pan);
		
		wait(1);
	}
}
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Debug & statistics
////////////////////////////////////////////////////////////
PANEL *debug = {
	layer = 3;

	digits(0,0,99,"arial#25b",1,num_mdlobjs);
	//	digits(0,20,99,"arial#25b",1,is_camera);
	digits(0,40,99,"arial#25b",1,camera.arc);


	flags = SHOW;
}

// Mystymood
// Template file v5.202 (02/20/02)
////////////////////////////////////////////////////////////////////////
// File: lflare.wdl
//	WDL code for lens flare and lighting effects
//
// 2007 Modified by David Lancaster and Loopix, based on ideas of HeelX
// Lite-C conversion by Alexis Rozhkov aka Shadow
//
// www.loopix-project.com
////////////////////////////////////////////////////////////////////////

void flare_init(ENTITY *flare_ent)
{
	my = flare_ent;
	my.flags2 &= ~SHOW;
	my.flags |= (BRIGHT|PASSABLE|TRANSLUCENT);
}

// Desc: places a flare at temp.x/temp.y deviations from screen center
void flare_place(ENTITY *flare_ent)
{
	my = flare_ent;
	my.flags2 |= SHOW;
	
	camera.pan%=360;//needed to keep the correct sun_angle for lensflare visibility
	
	// multiply the pixel deviation with the pivot factor,
	// and add the screen center
	my.x = ctemp.x*my.pivot_dist + 0.5*screen_size.x;
	my.y = ctemp.y*my.pivot_dist + 0.5*screen_size.y;
	my.z = 1000;	// screen distance, determines the size of the flare
	
	if(my == flare1_ent)
	{
		vec_set(temp2,sun_pos);
		you = player;	
		
		c_trace(camera.x,temp2.x,IGNORE_ME | IGNORE_YOU | IGNORE_PASSABLE | IGNORE_SPRITES | SCAN_TEXTURE);
		if(trace_hit)
		{
			
			if(flare1_ent.alpha > 0) flare1_ent.alpha -= flare_fadespeed * time_step;
			else flare1_ent.alpha = 0;
			
		}
		else
		{
			if((camera.pan > sun_angle.pan + 25) || (camera.pan < sun_angle.pan - 25) || (camera.tilt < sun_angle.tilt - 20) || (camera.tilt > sun_angle.tilt + 20))
			{
				
				if(flare1_ent.alpha > 0) flare1_ent.alpha -= flare_fadespeed * time_step;
				else flare1_ent.alpha = 0;
				
			}
			else
			{	
				temp2.x = sqrt(abs(((my.x - (0.5*screen_size.x))*(my.x - (0.5*screen_size.x)))+((my.y - (0.5*screen_size.y))*(my.y - (0.5*screen_size.y)))));
				if(abs(temp2.x) > (0.5*screen_size.x))
				{
					
					flare1_ent.alpha = flare_alpha - (abs(temp2.x) - (0.5*screen_size.x));
					if(flare1_ent.alpha < 0) flare1_ent.alpha = 0;
					
				}
				else
				{
					
					if(flare1_ent.alpha < flare_alpha) flare1_ent.alpha += flare_fadespeed * time_step;
					else flare1_ent.alpha = flare_alpha;
					
				}
			}
		}
		
		if (flare1_ent.alpha < 0) flare1_ent.alpha = 0;
		if (flare1_ent.alpha > flare_alpha) flare1_ent.alpha = flare_alpha;
	}
	rel_for_screen(my.x,camera);
}

void load_lensflare()
{
	
	flare_init(flare1_ent);
	flare_init(flare2_ent);
	flare_init(flare4_ent);
	flare_init(flare5_ent);
	flare_init(flare6_ent);
	flare_init(flare7_ent);
	flare_init(flare8_ent);
	flare_init(flare9_ent);
	flare_init(flare10_ent);
	flare_init(flare11_ent);
	flare_init(flare12_ent);
	flare_init(flare13_ent);
	flare_init(flare14_ent);
	flare_init(flare15_ent);
	flare_init(flare16_ent);
	flare_init(flare17_ent);
	flare_init(flare18_ent);
	flare_init(flare19_ent);
	flare_init(flare20_ent);
	
	wait(1);
	
	lens_active = 1;
	
	while(1)
	{
		vec_set(ctemp,sun_pos);
		vec_to_screen(ctemp,camera);
		
		ctemp.x -= 0.5 * screen_size.x;
		ctemp.y -= 0.5 * screen_size.y;
		
		flare_place(flare1_ent);
		flare_place(flare2_ent);	
		flare_place(flare4_ent);
		flare_place(flare5_ent);
		flare_place(flare6_ent);
		flare_place(flare7_ent);
		flare_place(flare8_ent);
		flare_place(flare9_ent);
		flare_place(flare10_ent);
		flare_place(flare11_ent);
		flare_place(flare12_ent);
		flare_place(flare13_ent);
		flare_place(flare14_ent);
		flare_place(flare15_ent);
		flare_place(flare16_ent);
		flare_place(flare17_ent);
		flare_place(flare18_ent);
		flare_place(flare19_ent);
		flare_place(flare20_ent);
		
		flare1_ent.alpha = flare1_ent.alpha - (sky_cloud3.alpha/10);
		flare2_ent.alpha = flare1_ent.alpha;		
		flare4_ent.alpha = flare1_ent.alpha;
		flare5_ent.alpha = flare1_ent.alpha;
		flare6_ent.alpha = flare1_ent.alpha;
		flare7_ent.alpha = flare1_ent.alpha;
		flare8_ent.alpha = flare1_ent.alpha;
		flare9_ent.alpha = flare1_ent.alpha;
		flare10_ent.alpha = flare1_ent.alpha;
		flare11_ent.alpha = flare1_ent.alpha;
		flare12_ent.alpha = flare1_ent.alpha;
		flare13_ent.alpha = flare1_ent.alpha;
		flare14_ent.alpha = flare1_ent.alpha;
		flare15_ent.alpha = flare1_ent.alpha;
		flare16_ent.alpha = flare1_ent.alpha;
		flare17_ent.alpha = flare1_ent.alpha;
		flare18_ent.alpha = flare1_ent.alpha;
		flare19_ent.alpha = flare1_ent.alpha;
		flare20_ent.alpha = flare1_ent.alpha;
		wait(1);
	}
	
	lens_active = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
////MystyMood sky/sun/weather template...works without shader, uses 3dgs sky entitys!
////
////Note: All sky/weather values must be adjusted in this script...exept from the mysty_mood trigger values 
////that can be adjusted for each trigger dummy via the behaviour panel in WED.
////
////Jun 07 by www.loopix-project.com
////Nov 07 Lite-C conversion by Alexis Rozhkov aka Shadow
/////////////////////////////////////////////////////////////

void func_fade_colors(var *col_target, var *col1, var *col2)
{
	var i = 0;
	if(i < 100)
	{
		i = minv(i + fog_fade_speed*time_step, 100);
		vec_lerp(col_target, col1, col2, i/100);
	}
}

//start rain/snow particle effects////

void func_particle_seed_infinity(PARTICLE *p)
{
	
	vec_set(p.x,vector(cycle(p.x,camera.x-particle_seedbox.x,camera.x+particle_seedbox.x),
	cycle(p.y,camera.y-particle_seedbox.y,camera.y+particle_seedbox.y),
	cycle(p.z,camera.z-particle_seedbox.z,camera.z+particle_seedbox.z)));
	
	if(p.z<camera.z-100) p.lifespan = 0;
	
}

void func_effect_particle_seed(PARTICLE *p) {

	vec_set(p.x,vector(camera.x+random(particle_seedbox.x*2)-particle_seedbox.x,
	camera.y+random(particle_seedbox.y*2)-particle_seedbox.y,
	camera.z+random(particle_seedbox.z*2)-particle_seedbox.z));
	
	p.flags |= MOVE;
	
	if(sky_cloud3.alpha > 0) {
		
		p.bmap = part_bmp_weather;	
		p.vel_x = part_vel_x;
		p.vel_y = part_vel_y;
		p.vel_z = part_vel_z;
		p.size = part_size;
		p.alpha = part_alpha;
		
		p.event  = func_particle_seed_infinity;	
	}	
}
////end rain/snow particle setup////

////start thunder lighning////
void func_fade_lightning(PARTICLE *p)  { p.lifespan = 0; }

void func_particle_lightning(PARTICLE *p)
{
	VECTOR temp;
	temp.x = random(2) - 1;
	temp.y = random(2) - 1;
	temp.z = random(2) - 1;
	vec_set(p.vel_x, temp);
	p.bmap = bmp_lightning;
	p.size = 3;
	p.flags |= (MOVE|BRIGHT|TRANSLUCENT);
	p.lifespan = 1;
	p.event  = func_fade_lightning;
}

void func_particle_segment()
{
	vec_set(temporary, segment_end);
	vec_sub(segment_end, segment_start);
	segment_length = vec_length(segment_end);
	segment_end.x = (segment_end.x * 2) / segment_length; // create particles every 2. quant
	segment_end.y = (segment_end.y * 2) / segment_length;
	segment_end.z = (segment_end.z * 2) / segment_length;
	while(segment_length > 0)
	{
		
		effect(func_particle_lightning, 2, segment_start.x, nullvector);	
		vec_add(segment_start, segment_end);
		segment_length -= 2;
		
	}
}

void func_particle_segment()
{
	vec_set(temporary, stroke_start);
	vec_sub(stroke_end, stroke_start);
	stroke_length = vec_length(stroke_end);
	stroke_end.x = (stroke_end.x * 100) / stroke_length; // create segments every 200 quants
	stroke_end.y = (stroke_end.y * 100) / stroke_length;
	stroke_end.z = (stroke_end.z * 100) / stroke_length;
	while(stroke_length > 0)
	{
		vec_add(stroke_start, stroke_end);
		vec_set(segment_start, temporary);
		vec_set(segment_end, stroke_start);
		segment_end.x += random(60) - 30; // displace the lightning segments (don't make the lightning look like a straight stroke)
		segment_end.y += random(60) - 30;
		segment_end.z += random(60) - 30;
		func_particle_segment();
		stroke_length -= 100; // keep the same value here
	}
}

void func_increase_brightness()
{
	lightning_on = 1;
	
	lightning = 255;
	wait(2+random(3));
	lightning = 1;
	wait(2+random(2));
	lightning = 255;
	wait(1+random(2));
	lightning = 1;
	wait(2+random(2));
	lightning = 255;
	wait(2+random(5));
	lightning = 1;
	
	wait(random(50));	
	lightning_on = 0;
}

////end thunder lightning////

void toggle_weather()//just for testing
{
	weather_state += 1;
	if(weather_state > 2) weather_state = 0;
}

void good_weather()  { weather_state = 0; }

void weather_change() {
	
	VECTOR temp;
	
	// Sound handlers.
	var snd_handle_thunder, snd_handle_rain, snd_handle_wind, snd_handle_bg_day, snd_handle_bg_night;
	var snd_vol_rain = 2, snd_vol_wind = 2, snd_vol_bg_day = 2, snd_vol_bg_night = 2;
	
	var rand_count, rand_count_state;
	var outer_radius, inner_radius;
	
	var eff_density = 1;
	
	snd_handle_wind = snd_loop(wind_wav,snd_vol_wind,0);
	snd_handle_rain = snd_loop(rain_wav,snd_vol_rain,0);
	
	outer_radius = weather_fog_far;
	inner_radius = weather_fog_far-(weather_fog_far/8);

	if(use_bg_sounds) {
		
		snd_handle_bg_day = snd_loop(day_wav,snd_vol_bg_day,0);
		snd_handle_bg_night = snd_loop(night_wav,snd_vol_bg_night,0);
		
	}
	
	weather_state = 0;
	
	while(1)
	{
		
		random_seed(0);
		rand_count = integer(random(6));//creates a integer random number 0-4		
		
		//////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////
		
		if(use_random_weather) {
			
			var i = random(random_weather_change_frequency);
			
			if(i>(random_weather_change_frequency/1.3)) {
				
				weather_state = 1;
				wait(-(random(random_weather_state_time/2)+random_weather_state_time/2));	
				
			}
			if(i>(random_weather_change_frequency/1.3)) {
				
				weather_state = 2;
				wait(-(random(random_weather_state_time/2)+random_weather_state_time/2));
				
			}	
			
			if(i>(random_weather_change_frequency/6)) {
				
				weather_state = 0;
				wait(-(random(random_weather_state_time/2)+random_weather_state_time/2));
				
			}
		}	
		
		//////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////
		
		if(weather_state == 1) {
			
			part_bmp_weather = bmp_rain;
			
			if(rain_random_move_on) {	
				
				part_vel_x = rain_wind_x + ((rain_random_move/2)-random(rain_random_move));
				part_vel_y = rain_wind_y + ((rain_random_move/2)-random(rain_random_move));	
				
			}
			
			else {
				
				part_vel_x = rain_wind_x;
				part_vel_y = rain_wind_y;
				
			}	
			
			part_vel_z = -rain_fallspeed;
			part_size=random(2)+8;
			part_alpha=random(10)+60;	
			
		}
		
		if(weather_state == 2) {
			
			part_bmp_weather = bmp_snow;
			
			if(snow_random_move_on == 1) {
				
				part_vel_x = snow_wind_x + ((snow_random_move/2)-random(snow_random_move));
				part_vel_y = snow_wind_y + ((snow_random_move/2)-random(snow_random_move));	
				
			}
			
			else {
				
				part_vel_x = snow_wind_x;
				part_vel_y = snow_wind_y;
				
			}	
			
			part_vel_z = -snow_fallspeed;
			part_size=random(1)+2;
			part_alpha=random(50)+40;	
		}
		
		//////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////
		
		if(weather_state == 1 && disable_lightning_thunder == 0)
		{	
			func_increase_brightness();
			
			vec_set(temp,vector(inner_radius+random(outer_radius-inner_radius),0,0));
			vec_rotate(temp,vector(random(360),0,0));
			vec_add(temp,camera.x); //Camera.x is center now. Maybe you want "player.x" here or something different altogether, depending on your game
			//Temp now is a random position somewhere on your "ring"
			//In your case:
			vec_set(stroke_start,temp);
			stroke_start.z += 600;
			vec_set(stroke_end,vector(temp.x+random(100)-200,temp.y+random(100)-200,temp.z));
			stroke_end.z -= 200;
			
			func_lightning_effect();
			while(lightning_on>0) wait(1); //thunder comes after lightning...
			
			if(rand_count == 1 && rand_count_state != 1)
			{
				snd_handle_thunder = snd_play(thunder1_wav, 100, 0);
				rand_count_state = 1;
			}
			if(rand_count == 2 && rand_count_state != 2)
			{
				snd_handle_thunder = snd_play(thunder2_wav, 100, 0);
				rand_count_state = 2;
			}
			if(rand_count == 3 && rand_count_state != 3)
			{
				snd_handle_thunder = snd_play(thunder3_wav, 100, 0);
				rand_count_state = 3;	
			}
			if(rand_count == 4 && rand_count_state != 4)
			{
				snd_handle_thunder = snd_play(thunder4_wav, 100, 0);
				rand_count_state = 4;	
			}
			if(rand_count == 5 && rand_count_state != 5)
			{
				snd_handle_thunder = snd_play(thunder5_wav, 100, 0);
				rand_count_state = 5;	
			}	
		}
		
		wait(-random(5));
		
		//////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////
		
		particle_seedbox.x=cx/2;
		particle_seedbox.y=cy/2;
		particle_seedbox.z=cz/2;
		
		if(weather_state>0) {
			
			reset(sky_cloud3,SHOW);
			if (sky_cloud3.alpha < 90) sky_cloud3.alpha += weather_fade_speed/20*time_step;
			
			if(sky_cloud3.alpha>40) {
				
				if(weather_fader<100 && weather_state>0)  weather_fader += weather_fade_speed/20*time_step;
				
				if(weather_state == 0) {
					
					if(weather_fader>1) weather_fader -= weather_fade_speed/20*time_step;
					
				}
				
				eff_density = (weather_fader*part_num);
			}
			
			if(weather_state == 1) {
				
				if(rain_to_snow_on_altitude && camera.z>snow_altitude && trigg_active_id == -1)
				weather_state = 2;
				
				part_num = rain_part_num;
				
				if(snd_vol_bg_day>2 || snd_vol_bg_night>2) {

					snd_vol_bg_day -= weather_soundfade_speed*time_step;
					snd_vol_bg_night -= weather_soundfade_speed*time_step;
					
				}	
				
				if(sky_cloud3.alpha>40) {
					
					if(snd_vol_rain<snd_vol_rain_max) snd_vol_rain += weather_soundfade_speed*time_step;
					if(snd_vol_wind<snd_vol_wind_max_when_rainy) snd_vol_wind += weather_soundfade_speed*time_step;
					
					else snd_vol_wind -= weather_soundfade_speed*time_step;
					
					effect(func_effect_particle_seed,eff_density,nullvector,nullvector);
					
				}
			}	
			
			if(weather_state == 2) {
				
				if(rain_to_snow_on_altitude == 1 && camera.z<snow_altitude && trigg_active_id == -1)
				weather_state = 1;
				
				part_num = snow_part_num;
				
				if(sky_cloud3.alpha>40) {
					
					if(snd_vol_rain>2) snd_vol_rain -= weather_soundfade_speed*time_step*2;
					if(snd_vol_wind<snd_vol_wind_max) snd_vol_wind += (eff_density/50)*weather_soundfade_speed*time_step;
					
					if(snd_vol_bg_day>2 || snd_vol_bg_night>2) {
						
						snd_vol_bg_day -= weather_soundfade_speed*time_step;
						snd_vol_bg_night -= weather_soundfade_speed*time_step;
						
					}
					
					effect(func_effect_particle_seed,eff_density,nullvector,nullvector);
				}
			}
			
			if(trigg_active_id < 0) {
				
				if(camera.fog_start>weather_fog_near) camera.fog_start -= weather_fade_speed*time_step;
				else camera.fog_start += weather_fade_speed*time_step;
				
				if(camera.fog_end>weather_fog_far) camera.fog_end -= weather_fade_speed*time_step;
				else camera.fog_end += weather_fade_speed*time_step;
				
			}
			
			
		}
		
		if(weather_state == 0) {
			
			if(sky_cloud3.alpha > 1) sky_cloud3.alpha -= weather_fade_speed/60*time_step;
			if(sky_cloud3.alpha<1) reset(sky_cloud3,SHOW);
			
			if(sky_cloud3.alpha > 40) {
				
				if(snd_vol_rain>2 || snd_vol_wind>2) {
					
					snd_vol_rain -= weather_soundfade_speed*time_step;
					snd_vol_wind -= weather_soundfade_speed*time_step;
					
					effect(func_effect_particle_seed,eff_density/4,nullvector,nullvector);
					
				}		
			}
			
			if(sky_cloud3.alpha < 60) {
				
				if(sun_angle.pan > 160 && sun_angle.pan < 360) {
					
					if(snd_vol_bg_night<snd_vol_bg_night_max) {
						
						snd_vol_bg_night += weather_soundfade_speed*time_step;
						
						if(snd_vol_bg_day > 2) snd_vol_bg_day -= weather_soundfade_speed*time_step;
						
					}			
				}
				
				if(sun_angle.pan>0 && sun_angle.pan<160) {
					
					if(snd_vol_bg_day<snd_vol_bg_day_max) {
						
						snd_vol_bg_day += weather_soundfade_speed*time_step;
						if(snd_vol_bg_night > 2) snd_vol_bg_night -= weather_soundfade_speed*time_step;
						
					}	
				}
			}
			
			if(trigg_active_id < 0) {
				
				if(camera.fog_start>land_fog_near) camera.fog_start -= weather_fade_speed*time_step;
				else camera.fog_start += weather_fade_speed*time_step;
				
				if(camera.fog_end>land_fog_far) camera.fog_end -= weather_fade_speed*time_step;
				else camera.fog_end += weather_fade_speed*time_step;
				
			}	
		}
		
		sky_sun.alpha = clamp((90-sky_cloud3.alpha),2,100);
		
		
		snd_tune(snd_handle_rain,snd_vol_rain,0,0);
		snd_tune(snd_handle_wind,snd_vol_wind,0,0);	
		snd_tune(snd_handle_bg_day,snd_vol_bg_day,0,0);
		snd_tune(snd_handle_bg_night,snd_vol_bg_night,0,0);
		
		wait(1);		
	}	
}

/*** load_mystymood(BOOL on, BOOL load_lens) 

Set on = 1, load mystymood
Set load_lens = 1, load lens flare

***/
void load_mystymood(BOOL on, BOOL load_lens)
{
	
	if(!on) { // Unload mystymood & lensflare effect
		
		// macros work only with flag1? :-? (idk)
		// so we use the inverse flag to control flags2.
		sky_horizon.flags2 &= ~SHOW;
		sky_cloud1.flags2 &= ~SHOW;
		sky_cloud2.flags2 &= ~SHOW;
		sky_cloud3.flags2 &= ~SHOW;
		sky_day.flags2 &= ~SHOW;
		sky_sun.flags2 &= ~SHOW;
		sky_suncorona.flags2 &= ~SHOW;
		sky_sunshine.flags2 &= ~SHOW;
		sky_night.flags2 &= ~SHOW;
		sky_moon.flags2 &= ~SHOW;
		
		lens_active = 0;
		mystymood_active = 0;
		
		return;
		
	}
	
	// else, if on != 0
	if(load_lens) load_lensflare();
	
	////////////////////////////////////////////////////////////
	// Setup for lensflare
	////////////////////////////////////////////////////////////
	flare1_ent.pivot_dist = 1.278;
	flare2_ent.pivot_dist = 1.200;
	flare4_ent.pivot_dist = 0.522;
	flare5_ent.pivot_dist = 0.434;
	flare6_ent.pivot_dist = 0.348;
	flare7_ent.pivot_dist = 0.306;
	flare8_ent.pivot_dist = 0.262;	
	flare9_ent.pivot_dist = 0.174;
	flare10_ent.pivot_dist = 0.114;
	flare11_ent.pivot_dist = 0.044;
	flare12_ent.pivot_dist = 0.002;
	flare13_ent.pivot_dist = -0.128;
	flare14_ent.pivot_dist = -0.258;
	flare15_ent.pivot_dist = -0.304;
	flare16_ent.pivot_dist = -0.372;
	flare17_ent.pivot_dist = -0.390;
	flare18_ent.pivot_dist = -0.432;
	flare19_ent.pivot_dist = -0.654;
	flare20_ent.pivot_dist = -1.000;
	////////////////////////////////////////////////////////////
	
	sky_horizon.flags2 |= SHOW;
	sky_cloud1.flags2 |= SHOW;
	sky_cloud2.flags2 |= SHOW;
	sky_cloud3.flags2 |= SHOW;
	sky_day.flags2 |= SHOW;
	sky_sun.flags2 |= SHOW;
	sky_suncorona.flags2 |= SHOW;
	sky_sunshine.flags2 |= SHOW;
	sky_night.flags2 |= SHOW;
	sky_moon.flags2 |= SHOW;
	
	VECTOR temp;
	
	on_space = toggle_weather;
	on_alt = good_weather;

	weather_change();
	
	sky_sun.scale_x = sun_scale_x;
	sky_sun.scale_y = sun_scale_y;

	camera.fog_start = land_fog_near;//-50;
	camera.fog_end = land_fog_far;//300;

	vec_set(d3d_fogcolor1,fog_day);//set the default day fog-color 
	
	mystymood_active = 1;

	while(1) {

		camera.fog_start = land_fog_near;
		camera.fog_end = land_fog_far;
		
		fog_color = 1;
		
		vec_set(sun_color.blue,vector(d3d_fogcolor1.blue*sun_col_fac,d3d_fogcolor1.green*sun_col_fac,d3d_fogcolor1.red*sun_col_fac));
		vec_set(sky_color.blue,d3d_fogcolor1.blue);	
		vec_set(sky_horizon.blue,d3d_fogcolor1.blue);
		
		if(weather_state == 0 && trigg_active_id < 0) {
			
			if(!dynamic_day_night) func_fade_colors(d3d_fogcolor1,current_color,fog_dynamic_day_night_off);
			
			if(camera.fog_start>land_fog_near) camera.fog_start -= weather_fade_speed*time_step;
			else camera.fog_start += weather_fade_speed*time_step;
			
			if(camera.fog_end>land_fog_far) camera.fog_end -= weather_fade_speed*time_step;
			else camera.fog_end += weather_fade_speed*time_step;
			
		}	
		
		vec_set(current_color,d3d_fogcolor1);
		
		//		camera.clip_near = 0; 
		//		camera.clip_far = land_fog_far+10;//camera.fog_end+10;//
		
		vec_set(temp,sun_pos); 
		vec_set(sky_sun.x,temp);  // copy the sun_pos location
		vec_sub(temp,camera.x); // direction vector from camera to our sun_pos
		vec_normalize(temp,land_fog_far-sun_dist_minus); // chop our direction vector to a set distance	
		
		vec_set(sky_sun.x,temp);
		
		if(use_moon) {
			
			vec_set(temp,sky_sun.x); 
			vec_inverse(temp);
			vec_set(sky_moon.x,temp);  // copy the sun_pos location
		}
		
		if(dynamic_day_night) {
			
			if(sun_angle.pan > 230 && sun_angle.pan < 360) {sun_angle.pan += 0.01*time_speed_night*time_step;}
			else{sun_angle.pan += 0.01*time_speed*time_step;}
			
			sun_angle.pan %= 360;
			sun_angle.tilt = fsin(sun_angle.pan, max_zenith);
			
			//sun "grows" at low azimut
			if(sky_sun.z<sun_grow_z) {
				
				if(sky_sun.scale_x<sun_scale_x+1 && sky_sun.scale_y<sun_scale_y+1) {
					
					sky_sun.scale_x += 0.01*time_step*time_speed/10;
					sky_sun.scale_y += 0.01*time_step*time_speed/10;
					
				}	
				
			}
			
			else {
				
				if(sky_sun.scale_x>sun_scale_x && sky_sun.scale_y>sun_scale_y) {
					
					sky_sun.scale_x -= 0.01*time_step*time_speed/10;
					sky_sun.scale_y -= 0.01*time_step*time_speed/10;
					
				}
			}
		}
		
		else {
			
			sun_angle.pan = sun_azimuth;
			sun_angle.tilt = sun_elevation;
			
		}
		
		if(sun_angle.pan > 0 && sun_angle.pan < 40) {
			
			if (sky_cloud1.alpha < 80) {sky_cloud1.alpha += sky_fade_speed*time_step*time_speed;} 
			if (sky_cloud2.alpha < 60) {sky_cloud2.alpha += sky_fade_speed*time_step*time_speed;}
			if (sky_day.alpha < 60) {sky_day.alpha += sky_fade_speed*time_step*time_speed;}
			if (sky_night.alpha > 1) {sky_night.alpha -= sky_fade_speed*time_step*time_speed;}	
			
		}
		
		if(sun_angle.pan > 10 && sun_angle.pan < 160) func_fade_colors(d3d_fogcolor1,current_color,fog_day);
		
		if(sun_angle.pan > 40 && sun_angle.pan < 160) {
			
			sky_cloud1.alpha = 80;
			sky_cloud2.alpha = 60;
			sky_day.alpha = 60;
			sky_night.alpha = 1;
			
		}
		
		if(sun_angle.pan > 160 && sun_angle.pan < 190) {
			
			if (sky_cloud1.alpha > 10) {sky_cloud1.alpha -= sky_fade_speed*time_step*time_speed;} 
			if (sky_cloud2.alpha > 10) {sky_cloud2.alpha -= sky_fade_speed*time_step*time_speed;} 
			if (sky_night.alpha < 100) {sky_night.alpha += sky_fade_speed*time_step*time_speed;}
			if (sky_day.alpha > 1) {sky_day.alpha -= sky_fade_speed*time_step*time_speed;}		
			
			func_fade_colors(d3d_fogcolor1,current_color,fog_eve);
			
		}
		
		if(sun_angle.pan > 190 && sun_angle.pan < 340) func_fade_colors(d3d_fogcolor1,current_color,fog_night);
		
		if(sun_angle.pan > 190 && sun_angle.pan < 340) {
			
			sky_cloud1.alpha = 10;
			sky_cloud2.alpha = 10;
			sky_day.alpha = 10;
			sky_night.alpha = 100;
			
		}
		
		if(sun_angle.pan > 340 && sun_angle.pan < 360) func_fade_colors(d3d_fogcolor1,current_color,fog_mor);
		
		if(sun_angle.pan > 190 && sun_angle.pan < 350) {
			
			if(weather_state>0) func_fade_colors(d3d_fogcolor1,current_color,fog_weather_night);
			
		}
		
		else {
			
			if(weather_state>0) func_fade_colors(d3d_fogcolor1,current_color,fog_weather_day);
			
		}
		
		vec_set(sky_sunshine.x,sky_sun.x);	
		vec_set(sky_suncorona.x,sky_sun.x);
		
		sky_suncorona.scale_x = sun_scale_x*5;//15;
		sky_suncorona.scale_y = sun_scale_y*4;//7;
		
		sky_sunshine.scale_x = sun_scale_x*10;
		sky_sunshine.scale_y = sun_scale_y*4;
		
		sky_moon.scale_x = sun_scale_x*moon_scale_fac;
		sky_moon.scale_y = sun_scale_y*moon_scale_fac;	 
		
		sky_night.scale_x = night_sky_scale_x;
		sky_night.scale_y = night_sky_scale_y;
		
		wait(1);
	}	
}

//title:MystyMood Sky Template
//image:loopix_logo.pcx
//action:act_mystymood_trigg  
//skill1:trigg_range 300.000
//help: sets  range within the mood-trigger is activated
//skill2:trigg_rain_wind_x 2.000
//help: wind strenght on direction x
//skill3:trigg_rain_wind_y 0.000
//help:  wind strenght on direction y
//skill4:trigg_rain_fallspeed 20.000
//help: fallingspeed of the raindrops
// section:
//skill5:trigg_snow_wind_x 4.000
//help: wind strenght on direction x
//skill6:trigg_snow_wind_y 0.000
//help: wind strenght on direction y
//skill7:trigg_snow_fallspeed 5.000
//help: fallingspeed of the snowflakes
// section:
//skill8:trigg_rain_random_move 2.000
//help: random-xy movement of the rain particle
//skill9:trigg_snow_random_move 4.000
//help: random-xy movement of the snow particle
// section:
//skill10:trigg_weather_fade_speed 10.000
//help: speed of fading one weather/mood state into the next
//section:
//skill11:trigg_fog_near 0.000
//help: sets the fog_near distance...use negative values for starting the fog behind the camera
//skill12:trigg_fog_far 0.000
//help: sets the fog_far distance
//skill13: trigg_fog_red 140.000
//help: fog color red
//skill14: trigg_fog_green 170.000
//help: fog color green
//skill15: trigg_fog_blue 160.000
//help: fog color blue
//section:
//text: flag to enable rain
//flag1:trigg_rain 0.000
//text: flag to enable snow
//flag2:trigg_snow 0.000
//text: flag to disable lightning and thunder
//flag3:trigg_disable_lightning_thunder
// section:
//text: flag to enable random-xy movement of the rain particle
//flag4:trigg_rain_random_move_on 1.000
//text: flag to enable random-xy movement of the snow particle
//flag5:trigg_snow_random_move_on 1.000
// section:
//text: flag to enable fog distance/density change
//flag6:trigg_fog_col_dist 1.000
//uses:trigg_range,trigg_rain,trigg_snow,trigg_rain_wind_x,trigg_rain_wind_y,trigg_rain_fallspeed
//uses:trigg_snow_wind_x,trigg_snow_wind_y,trigg_snow_fallspeed
//uses:trigg_rain_random_move_on,trigg_snow_random_move_on,trigg_rain_random_move,trigg_snow_random_move
//uses:trigg_weather_fade_speed,trigg_disable_lightning_thunder
//uses:trigg_fog_col_dist,trigg_fog_near,trigg_fog_far,trigg_fog_red,trigg_fog_green,trigg_fog_blue
action act_mystymood_trigg()
{
	ent_mystymood_trigg = me;
	
	set(my,PASSABLE);
	
	//set default skills
	if(!my.trigg_range) my.trigg_range = 300;
	if(!my.trigg_rain_fallspeed) my.trigg_rain_fallspeed = 20;
	if(!my.trigg_snow_fallspeed) my.trigg_snow_fallspeed = 5;
	if(!my.trigg_weather_fade_speed) my.trigg_weather_fade_speed = 10;

	my.trigg_ID = trigg_num_off;
	trigg_num_off += 1;

	my.skill70 = weather_state;	
	my.skill71 = rain_random_move_on;
	my.skill72 = rain_random_move;
	my.skill73 = rain_wind_x;
	my.skill74 = rain_wind_y;
	my.skill75 = rain_fallspeed;
	my.skill76 = disable_lightning_thunder;
	my.skill77 = snow_random_move_on;
	my.skill78 = snow_random_move;
	my.skill79 = snow_wind_x;
	my.skill80 = snow_wind_y;
	my.skill81 = snow_fallspeed;
	my.skill82 = weather_fade_speed;	

	while(1)
	{
		if(vec_dist(my.x,camera.x) < my.trigg_range)
		{
			trigg_active_id = my.trigg_ID;
			
			if(is(my,trigg_rain)) weather_state = 1;
			if(is(my,trigg_snow)) weather_state = 2;
			if(!is(my,trigg_snow) && !is(my,trigg_rain)) weather_state = 0;
			
			weather_fade_speed = my.trigg_weather_fade_speed;
			
			if(weather_state > 0)
			{
				
				rain_random_move_on = is(my,trigg_rain_random_move_on);
				rain_random_move = my.trigg_rain_random_move;
				
				rain_wind_x = my.trigg_rain_wind_x;
				rain_wind_y = my.trigg_rain_wind_y;
				
				rain_fallspeed = my.trigg_rain_fallspeed;
				
				disable_lightning_thunder = is(my,trigg_disable_lightning_thunder);
				
				snow_random_move_on = is(my,trigg_snow_random_move_on);
				snow_random_move = my.trigg_snow_random_move;
				
				snow_wind_x = my.trigg_snow_wind_x;
				snow_wind_y = my.trigg_snow_wind_y;
				
				snow_fallspeed = my.trigg_snow_fallspeed;		
				
			}
			
			if(is(my,trigg_fog_col_dist))
			{
				func_fade_colors(d3d_fogcolor1,current_color,fog_col_trigg);
				
				fog_dist_near_trigg = my.trigg_fog_near;
				fog_dist_far_trigg= my.trigg_fog_far;
				
				if(camera.fog_start>fog_dist_near_trigg) camera.fog_start -= weather_fade_speed*time_step;
				else camera.fog_start += weather_fade_speed*time_step;
				
				if(camera.fog_end>fog_dist_far_trigg) camera.fog_end -= weather_fade_speed*time_step;
				else camera.fog_end += weather_fade_speed*time_step;
				
				fog_col_trigg[2] = my.trigg_fog_red;
				fog_col_trigg[1] = my.trigg_fog_green;
				fog_col_trigg[0] = my.trigg_fog_blue;
				
				
			}
		}
		else
		{
			if(trigg_active_id == my.trigg_ID)
			{
				trigg_active_id = -1;		
				act_mystymood_trigg_label1();	
				break;
			}
		}
		
		wait(1);	
	}
}

void act_mystymood_trigg_label1()
{
	weather_fader = 1;//reset this var

	weather_state = my.skill70;
	rain_random_move_on = my.skill71;
	rain_random_move = my.skill72;
	rain_wind_x = my.skill73;
	rain_wind_y = my.skill74;
	rain_fallspeed = my.skill75;
	disable_lightning_thunder = my.skill76;
	snow_random_move_on = my.skill77;
	snow_random_move = my.skill78;
	snow_wind_x = my.skill79;
	snow_wind_y = my.skill80;
	snow_fallspeed = my.skill81;
	weather_fade_speed = my.skill82;
	
	act_mystymood_trigg();
}


VECTOR dist, absdist, force, camera_center;
var my_height; //
var step_height = 8; //
var overallspeed = 7.9; // Overall player's movement speed
var mouse_spd = 9; // Mouse sensivity
var cam_height = 110; // Camera's Z-height
var temp_cam = 0;

void fpcam_push(var Speed,var Amount)
{
	dist.x = Speed * Amount * time_step;
	force.x = Speed * time_step;
	accelerate(dist.x,force.x,0.7);
}

void fpcam_update()
{
	vec_lerp(camera.x,camera.x,camera_center.x,0.3);
	vec_lerp(camera_center,camera_center,vector(0,0,cam_height),1);
	vec_rotate(camera_center,my.pan);
	vec_add(camera_center,my.x);
	camera.pan -= mouse_spd * mouse_force.x * time_step;
	camera.tilt += mouse_spd * mouse_force.y * time_step;
	if(camera.tilt > 70) camera.tilt = 70;
	if(camera.tilt < -70) camera.tilt = -70;
}

void fpcam_input()
{
	if(key_z)
	{
		while(camera->arc >= 45)
		{
			camera->arc -= .2 * time_step;
			wait(1);
		}
	}
	else
	{
		while(camera->arc <= 60)
		{
			camera->arc += .2 * time_step;
			wait(1);
		}
	}
	
	if(my_height <= 10)
	{
		force.x = overallspeed * (key_w - key_s) * time_step;
		
		if(key_shift && (key_w)) accelerate(dist.x,force.x + 3.5,0.5);
		else accelerate(dist.x,force.x,0.7);
		
		force.y = overallspeed * (key_a - key_d) * time_step;
		
		if(key_shift && (key_w)) accelerate(dist.x,force.x + 1.5,0.5);
		else accelerate(dist.y,force.y,0.7);
	}
	
	move_friction = 0.2;
	move_min_z = -1;

}

action a_visitor_foot()
{
	player = my;
	set(my,POLYGON | SHADOW | INVISIBLE);
	my.scale_x = 4.5;
	my.scale_y = my.scale_x;
	my.scale_z = my.scale_x;
	
	my.cam_fp = 1;
	
	while(my)
	{
		if(engine_play && my.cam_fp && !my.cam_race)
		{
			if(my_height <= 10) my.pan = camera.pan;
			my_height = c_trace(my.x,vector(my.x,my.y,my.z-9999),IGNORE_MODELS|IGNORE_PASSABLE|IGNORE_ME|USE_BOX);
			if(my_height > 10) accelerate(absdist.z,-10 * time_step,-1);    
			
			else
			{
				absdist.z = -(my_height/1.2)+ step_height;
				absdist.z = clamp(absdist.z,-step_height,step_height);
				if((my_height + absdist.z) > 10){ absdist.z = -my_height -10; }
			} 
			
			c_move(my,dist,absdist, IGNORE_PASSABLE|GLIDE);	
			
			fpcam_update();
			fpcam_input();
		}
		wait(1);
	} 
}

action a_visitor_bike() {
	
	var movement_speed = 0; // initial movement speed
	var rotation_speed = 3; // rotation speed
	
	my.cam_race = 1;

	VECTOR bike_speed, temp;
	player = my;
	
	set(my,SHADOW | POLYGON);

	while(my)
	{
		if(engine_play && my.cam_race && !my.cam_fp) {
			
			if(key_w || key_s) {
				
				ent_animate(my,"run",my.skill5,ANM_CYCLE);
				my.skill5 += 4 * time_step;
				
			}
			
			my.pan += rotation_speed * (key_a - key_d) * time_step;
			if (key_a)
			{
				if (my.roll > -20) my.roll -= 5 * time_step;
			}
			else
			{
				if (my.roll < 0) my.roll += 5 * time_step;
			}

			if (key_d)
			{
				if (my.roll < 20) my.roll += 5 * time_step;      
			}
			else
			{
				if (my.roll > 0) my.roll -= 5 * time_step;
			}

			// 15 gives the acceleration, 0.1 gives the frictiob
			vec_set(bike_speed.x, accelerate (movement_speed, 15 * (key_w - key_s), 0.1));

			bike_speed.y = 0;

			vec_set (temp.x, my.x);

			temp.z -= 10000;
			bike_speed.z = -c_trace (my.x, temp.x, IGNORE_ME | IGNORE_PASSABLE | USE_BOX) + 5;

			c_move (my, bike_speed.x, nullvector, IGNORE_PASSABLE | GLIDE);                

			camera.x = my.x - 250 * cos(my.pan); // put the camera 250 quants behind the bike
			camera.y = my.y - 250 * sin(my.pan);
			camera.pan = my.pan; // the camera and the bike have the same pan angle
			camera.z = my.z + 140; // place the camera above the bike, play with this value
			camera.tilt = -10; // look downwards   
			
		}             

		wait (1);

	}


}

////////////////////////////////////////////////////////////
// This function will set up and manage the playground.
////////////////////////////////////////////////////////////
void test_play() {
	
	// Deselect any selected entity first
	if(select.obj_type == light) _light(0);
	if(select.obj_type == mdl) prop(0);
	if(select.obj_type == snd) sound(0);
	if(select.obj_type == part) _part(0);
	
	select.material = mat_temp;
	select = NULL;
	
	/***
	
	This code will scan through all available entities
	
	***/
	you = ent_next(NULL);
	while(you) {
		
		if(you.cam_fp) you.cam_race = 0;
		if(you.cam_race) you.cam_fp = 0;
		
		// Scan for any light, particle, or sound entity
		if(you.obj_type == light || you.obj_type == part || you.obj_type == snd) {
			
			// I wonder how I couldn't just use reset(you,SHOW) or you.flags &= ~SHOW here
			set(you,INVISIBLE); 
			
		}
		
		you = ent_next(you);
		
		wait(1);
		
	}
	
	mouse_mode = 0;
	
	ent_remove(fpsf_marker);
	ent_remove(cam);
	
	hideGUI();
	
	engine_play = 1;
	
	while(engine_play) {
		
		temp_cam += 3 * time_step;
		camera.z += .5 * sin(temp_cam);
		
		if(key_esc) {
			
			from_test_play = 1;
			
			while(key_esc) wait(1);
			
			engine_play = 0;
			from_test_play = 0; // reset
			
		}
		
		wait(1);
		
	}
	
	mouse_mode = 4;
	ent_create("marker.mdl",nullvector,follow_pointer); // Create a mouse pointer.
	cam = ent_create("marker.mdl",vector(0,0,0),free_camera);
	
	showGUI();
	//	def_move();
	
	/***
	
	Scan through all available entities in the level
	and set them to their original state.
	
	***/
	you = ent_next(NULL);
	
	while(you) {
		
		if(you.obj_type == light || you.obj_type == part || you.obj_type == snd) {
			
			reset(you,INVISIBLE);
			
		}
		
		you = ent_next(you);
		
	}
}