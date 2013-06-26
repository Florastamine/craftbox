/*
void timebar_decrease(var _TimeRemain,var _DecrTime, var _GameLoaderPOSX, var _GameLoaderPOSY)
{
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
	
	_GameLoader.scale_x = .01;
	__TimeRemain = _TimeRemain;
	
	while(abs(_TimeRemain) > 0 && Perc > 0) 
	{
		_TimeRemain -= _DecrTime;
		Perc = (_TimeRemain / __TimeRemain) * 100;

		_GameLoader.scale_x = maxv(.01,_TimeRemain / 100);
		wait(1);
	}
	
	sys_exit(NULL);
}
*/

////////////////////////////////////////////////////////////
// Panel manipulation functions.
// Some I wrote by myself, some I borrowed from the others.
////////////////////////////////////////////////////////////
void pan_rotate(PANEL *p,var lim,var speed,BOOL rotate_on_center)
{
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
		
		case 'x':
		
		p.scale_x = screen_size.x/bmap_width(p.bmap);
		
		break;
		
		case 'y':
		
		p.scale_y = screen_size.y/bmap_height(p.bmap);
		
		break;
		
		default:
		
		p.pos_x = 0;
		p.pos_y = 0;
		
		p.scale_x = screen_size.x/bmap_width(p.bmap);
		p.scale_y = screen_size.y/bmap_height(p.bmap);
		
		break;
		
	}
	
}

////////////////////////////////////////////////////////////
// This function will load the database.
////////////////////////////////////////////////////////////
void init_database() {
	
	int i;
	
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
	mdlobjs_table[832] = str_create("l_greenland1.hmp");
	mdlobjs_table[833] = str_create("l_greenland_fat.hmp");
	mdlobjs_table[834] = str_create("l_marssurface.hmp");
	mdlobjs_table[835] = str_create("l_ocean1.hmp");
	mdlobjs_table[836] = str_create("l_ocean2.hmp");
	mdlobjs_table[837] = str_create("l_steppegeneric.hmp");
	mdlobjs_table[838] = str_create("l_stonegeneric.hmp");
	mdlobjs_table[839] = str_create("l_water1.hmp");
	mdlobjs_table[840] = str_create("l_water2.hmp");
	
	// Unallocated space
	for(i = 841;i < 880;i++) mdlobjs_table[i] = str_create("#2");
	
	// Particle effects 100 [880->979]
	mdlobjs_table[880] = str_create("part_avatar.mdl");
	
	// Unallocated space
	for(i = 881;i < 980;i++) mdlobjs_table[i] = str_create("#2");
	
	// Done!
	////////////////////////////////////////////////////////////
}

ENTITY *obj_create() { // This inherits a lot from place_me

	ENTITY *tmp;

	switch(_obj_type) {
		
		////////////////////////////////////////////////////////////
		case mdl:
		
		if(str_len(mdlobjs_table_ptr[num_mdlobjs]) == 0) {
			
			printf("Wrong object ID.\nMaybe you're trying to access unallocated space in the database.");
			return;
			
		}
		
		ENTITY *tmp = ent_create(mdlobjs_table_ptr[num_mdlobjs],temp_pos.x,obj_manip_setup);
		
		while(tmp == NULL) wait(1); // wait for tmp to be completely created.
		
		set(tmp, POLYGON);
		reset(tmp, NOFOG | INVISIBLE | TRANSLUCENT); // Tha giet nham con hon bo sot
		
		tmp.alpha = 0;
		tmp.ambient = 50;
		tmp.pan = random(360); // Give it a random pan value.
		
		tmp.material = mat_model;
		
		tmp.obj_type = mdl;
		tmp.skill4 = num_mdlobjs;
		
		tmp.skill2 = 1; // This is a static object
		tmp.skill3 = 0; // And physics aren't enabled by default.
		
		return tmp;
		
		break;
		////////////////////////////////////////////////////////////
		
		////////////////////////////////////////////////////////////
		case light:
		
		tmp = ent_create("marker.mdl",temp_pos.x,NULL);
		
		tmp.obj_type = light; // Du sao thi light cung ngan hon _obj_type
		tmp.skill4 = num_lightobjs;
		
		return tmp;
		
		break;
		////////////////////////////////////////////////////////////
		
		////////////////////////////////////////////////////////////
		case part :
		
		tmp = ent_create("part_avatar.mdl",temp_pos.x,NULL);
		
		tmp.obj_type = part;
		tmp.skill4 = num_partobjs;
		
		return tmp;
		
		break;	
		////////////////////////////////////////////////////////////
		
		////////////////////////////////////////////////////////////
		case snd:
		
		tmp = ent_create("part_avatar.mdl",temp_pos.x,NULL);
		tmp.obj_type = snd;
		tmp.skill4 = num_sndobjs;
		
		return tmp;
		
		break;
		////////////////////////////////////////////////////////////
		
		default:
		sys_exit(NULL);
		break;
		
		
	}

	/*
	
	if(str_len(mdlobjs_table_ptr[num_mdlobjs]) == 0) {
		
		printf("Wrong object ID.\nMaybe you're trying to access unallocated space in the database.");
		return;
		
	}
	
	ENTITY *tmp = ent_create(mdlobjs_table_ptr[num_mdlobjs],temp_pos.x,obj_manip_setup);
	
	while(tmp == NULL) wait(1); // wait for tmp to be completely created.
	
	set(tmp, POLYGON);
	reset(tmp, NOFOG | INVISIBLE | TRANSLUCENT); // Tha giet nham con hon bo sot
	
	tmp.alpha = 0;
	tmp.ambient = 50;
	tmp.pan = random(360); // Give it a random pan value.
	
	tmp.material = mat_model;
	
	tmp.skill1 = num_mdlobjs;
	tmp.skill2 = 1; // This is a static object
	tmp.skill3 = 0; // And physics aren't enabled by default.
	
	return tmp;
	
	*/
}

ENTITY *obj_create_from_clipboard() { // This inherits a lot from place_me

	ENTITY *tmp;

	switch(clipboard.of_objtype) {
		
		////////////////////////////////////////////////////////////
		case mdl:
		
		if(str_len(mdlobjs_table_ptr[num_mdlobjs]) == 0) {
			
			printf("Wrong object ID.\nMaybe you're trying to access unallocated space in the database.");
			return;
			
		}
		
		tmp = ent_create(mdlobjs_table_ptr[num_mdlobjs],temp_pos.x,obj_manip_setup);
		
		while(tmp == NULL) wait(1); // wait for tmp to be completely created.
		
		set(tmp, POLYGON);
		reset(tmp, NOFOG | INVISIBLE | TRANSLUCENT); // Tha giet nham con hon bo sot
		
		tmp.alpha = 0;
		tmp.ambient = 50;
		tmp.pan = random(360); // Give it a random pan value.
		
		tmp.material = mat_model;
		
		tmp.obj_type = mdl;
		tmp.skill4 = num_mdlobjs;
		
		tmp.skill2 = 1; // This is a static object
		tmp.skill3 = 0; // And physics aren't enabled by default.
		
		return tmp;
		
		break;
		////////////////////////////////////////////////////////////
		
		////////////////////////////////////////////////////////////
		case light:
		
		tmp = ent_create("marker.mdl",temp_pos.x,NULL);
		
		tmp.obj_type = light; // Du sao thi light cung ngan hon _obj_type
		tmp.skill4 = num_lightobjs;
		
		return tmp;
		
		break;
		////////////////////////////////////////////////////////////
		
		////////////////////////////////////////////////////////////
		case part :
		
		tmp = ent_create("part_avatar.mdl",temp_pos.x,NULL);
		
		tmp.obj_type = part;
		tmp.skill4 = num_partobjs;
		
		return tmp;
		
		break;	
		////////////////////////////////////////////////////////////
		
		////////////////////////////////////////////////////////////
		case snd:
		
		tmp = ent_create("part_avatar.mdl",temp_pos.x,NULL);
		tmp.obj_type = snd;
		tmp.skill4 = num_sndobjs;
		
		return tmp;
		
		break;
		////////////////////////////////////////////////////////////
		
		default:
		sys_exit(NULL);
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

void sharedGUI_updategui(PANEL *wg) {
	
	if(wg == panHome) {
		
		button_SaveWorld_y = BORDER;
		button_LoadWorld_y = button_SaveWorld_y + 40 + BORDER/2.5;
		button_NewWorld_y = button_LoadWorld_y + 40 + BORDER/2.5;
		button_QuitWorld_y = button_NewWorld_y + 40 + BORDER/2.5;
		button_CmpWorld_y = button_QuitWorld_y + 40 + BORDER/2.5;
		button_SetWorld_y = button_CmpWorld_y + 40 + BORDER/2.5;
		
		pan_setpos(panHome,3,2,vector(BORDER,button_SaveWorld_y,0));
		pan_setpos(panHome,3,3,vector(BORDER,button_LoadWorld_y,0));	
		pan_setpos(panHome,3,4,vector(BORDER,button_NewWorld_y,0));
		pan_setpos(panHome,3,5,vector(BORDER,button_QuitWorld_y,0));
		pan_setpos(panHome,3,6,vector(BORDER,button_CmpWorld_y,0));
		pan_setpos(panHome,3,7,vector(BORDER,button_SetWorld_y,0));
		
		pan_setpos(panHome,3,1,vector(bmap_width(panHome.bmap) - BORDER * 2,BORDER,0));
		
	}
	
	if(wg == panProp) { 
		
		int i;
		for(i = 2;i < 10;i++) pan_setpos(panProp,3,i,vector(BORDER,BORDER + 23 * (i - 1),0));
		
		pan_setpos(panProp,3,10,vector(bmap_width(panProp.bmap) - BORDER - 64, bmap_height(panProp.bmap) - BORDER - 32,0));
		pan_setpos(panProp,3,11,vector(bmap_width(panProp.bmap) - BORDER - 64, bmap_height(panProp.bmap) - BORDER - 64,0));		
		
		pan_setpos(panProp,4,1,vector(BORDER + 102,BORDER * 2 + 23,0));
		pan_setpos(panProp,4,2,vector(BORDER + 102,BORDER * 3 + 23 * 2,0));
		
		pan_setpos(panProp,3,1,vector(bmap_width(panProp.bmap) - BORDER * 2,BORDER,0));
	}
	
	if(wg == panMat) {
		
		var i = 2, j = 0, k;
		k = i;
		while(i < 17) {
			pan_setpos(panMat,3,i,vector( (k-1) * BORDER + (k-2) * 64,BORDER * 2 + 15 + j,0));
			i++; k++;
			
			if(i == 7) {
				j = 74; // 64 + BORDER
				k = 2;
			}
			
			if(i == 12) {
				j = 148; // 128 + 2x BORDER
				k = 2;
			}
			
		}
		
		var cache = bmap_width(panMat.bmap) - BORDER - 100;
		pan_setpos(panMat,3,17,vector(cache, bmap_height(panMat.bmap) - BORDER - 24 ,0));
		pan_setpos(panMat,3,18,vector(cache, bmap_height(panMat.bmap) - BORDER * 2 - 48,0));
		
		pan_setpos(panMat,3,1,vector(bmap_width(panMat.bmap) - BORDER * 2, BORDER,0));
	}
	
	if(wg == panPhy) {
		pan_setpos(panPhy,3,1,vector(bmap_width(panPhy.bmap) - BORDER * 2, BORDER,0));
		
		pan_setpos(panPhy,3,2,vector(BORDER,BORDER*4,0));
		pan_setpos(panPhy,4,1,vector(141,bmap_height(panPhy.bmap) - 109,0)); // Bounciness
		pan_setpos(panPhy,4,2,vector(141,bmap_height(panPhy.bmap) - 135,0)); // Friction
	}
	
	if(wg == panMat_Sub1) { 
		
		pan_setpos(panMat_Sub1,3,1,vector(bmap_width(panMat_Sub1.bmap) - BORDER * 2,BORDER,0));
		
		var i = 2;
		while(i < 4) {
			pan_setpos(panMat_Sub1,3,i,vector(BORDER, bmap_height(panMat_Sub1.bmap) - BORDER * (i-1) - 24 * (i-1),0));
			i++;
		}
		
		var i = 1, j = 0, k;
		k = i; //lite-C doesn't allow me to initialize continuous variables during declaring them so...
		
		while(i < 15) {
			
			pan_setpos(panMat_Sub1,4,i,vector( BORDER * k + (k-1) * 50, BORDER * 2 + 45 + j,0 ));
			i++; k++;
			
			if(i == 4) {
				j = 23 + BORDER; // 23 = slider height
				k = 1;
			}
			
			if(i == 7) {
				j = (23 + BORDER) * 2;
				k = 1;
			}
			
			if(i ==  10) {
				j = (23 + BORDER) * 3;
				k = 1;
			}
			
			if(i == 13) {
				j = (23 + BORDER) * 4;
				k = 1;
			}
			
		}
	}
}

/* 

id always = 1 cuz we don't have two closebuttons at the same time. 
only one PANEL * parameter isn't enough (and it won't work too) so 
this simple ugly hack should do the trick.

*/
void sharedGUI_closewindow(var id, PANEL *p) {
	id = 1;
	
	if(p == panHome) {
		reset(panHome,SHOW);
	}
	
	if(p == panPhy) {
		reset(panPhy,SHOW);
	}
	
	if(p == panMat) {
		
		if(is(panMat_Sub1,SHOW)) {
			reset(panMat_Sub1,SHOW);
			
			if(is(debug_material,SHOW)) reset(debug_material,SHOW);
			
		}
		
		reset(panMat,SHOW);
	}
	
	if(p == panMat_Sub1) {
		reset(panMat_Sub1,SHOW);
		
		if(is(debug_material,SHOW)) reset(debug_material,SHOW);
	}
	
	if(p == panProp) {		
		
		reset(panProp,SHOW);
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
	
	if(p == panObj_Main) {
		
		reset(panObj_Main,SHOW);
		reset(panObj_Subbar,SHOW);
		reset(panObj_Subbar_slider,SHOW);
		ctrl = 0;
		
		showGUI();
		
	}
}

void sharedGUI_dragpanel(PANEL *p)
{
	var click_offset[2];
	
	click_offset[0]=p.pos_x - mouse_pos.x;
	click_offset[1]=p.pos_y - mouse_pos.y;
	
	sharedGUI_panelselect(p);
	
	while(mouse_left)
	{
		proc_mode = PROC_EARLY;
		
		p.pos_x = mouse_pos.x+click_offset[0];
		p.pos_y = mouse_pos.y+click_offset[1];
		
		//hack hack hack!!!!
		if(p == panHome) sharedGUI_updategui(panHome);
		if(p == panProp) sharedGUI_updategui(panProp);
		if(p == panPhy) sharedGUI_updategui(panPhy);
		if(p == panMat) sharedGUI_updategui(panMat);
		
		wait(1);
	}
	
	//hack to prevent shit happens. f.e. after dragged the guis' elements didn't retain their original location.
	if(p == panHome) sharedGUI_updategui(panHome);
	if(p == panProp) sharedGUI_updategui(panProp);
	if(p == panPhy) sharedGUI_updategui(panPhy);
	if(p == panMat) sharedGUI_updategui(panMat);
}

void sharedGUI_centerpanel(PANEL *p) {
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
	
	panMain_Top.pos_x = screen_size.x - bmap_width(panMain_Top.bmap) - (BORDER + 3 * BUTTON_SIZE);
	panMain_Top.pos_y = BORDER;
	
	panMain_Bottom.pos_x = BORDER;
	panMain_Bottom.pos_y = screen_size.y - bmap_height(panMain_Bottom.bmap) - BORDER;
	
	panObj_Main.pos_x = 0;
	panObj_Main.pos_y = (screen_size.y - bmap_height(panObj_Main.bmap))/2 - 3 * BORDER;
	
	// Position the close button for panObj_Main
	pan_setpos(panObj_Main,3,1,vector(bmap_width(panObj_Main.bmap) - BORDER * 2,BORDER,0));
	
	pan_resize(panObj_Subbar_slider,'x');
	
	panObj_Subbar.pos_x = panObj_Subbar_slider.pos_x = 0;
	panObj_Subbar.pos_y = panObj_Main.pos_y + bmap_height(panObj_Main.bmap) + BORDER;
	panObj_Subbar_slider.pos_y = panObj_Subbar.pos_y + bmap_height(panObj_Subbar_slider.bmap) + BORDER * 3;
	
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
	while(i < 5){
		pan_setpos(buttonlst_submenu_terrain,3,i,vector(BORDER * (i-1) + 32 * (i-1),NULL,NULL));
		pan_setpos(buttonlst_submenu_object,3,i,vector(BORDER * (i-1) + 32 * (i-1),NULL,NULL));
		pan_setpos(buttonlst_submenu_path,3,i,vector(BORDER * (i-1) + 32 * (i-1),NULL,NULL));
		
		i++;
	}
	
	var cache = BORDER * 4 + 32 * 4; // the above formula, i = 5
	pan_setpos(buttonlst_submenu_terrain,3,5,vector(cache,NULL,NULL));
	pan_setpos(buttonlst_submenu_object,3,3,vector(cache,NULL,NULL));
	pan_setpos(buttonlst_submenu_path,3,3,vector(cache,NULL,NULL));
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
	
	sharedGUI_centerpanel(panHome);
	sharedGUI_updategui(panHome);
	
	set(panHome,SHOW);
}

void prop() {
	
	if(select) {
		
		panProp.pos_x = BORDER;
		panProp.pos_y = screen_size.y - (2 * BORDER) - 32 - bmap_height(panProp.bmap);
		
		sharedGUI_updategui(panProp);
		
		set(panProp,SHOW);
		
	}
}

void mat() {
	
	sharedGUI_centerpanel(panMat);
	sharedGUI_updategui(panMat);
	
	set(panMat,SHOW);
}

void editmat() {
	
	// Precache panMat_Sub1
	sharedGUI_centerfrom(panMat_Sub1,panMat);
	sharedGUI_updategui(panMat_Sub1);
	
	// Material editor is available only to custom materials
	switch(mat_type) {
		
		case select_custom_mat1 :
		
		pass_mat_to_matsub(mat_custom[0]);
		set(panMat_Sub1,SHOW);
		
		// For debug purposes
		reset(debug,SHOW);
		set(debug_material,SHOW);
		
		break;
		//////////////////////////////////////////////////////////////
		
		case select_custom_mat2 :
		
		pass_mat_to_matsub(mat_custom[1]);
		set(panMat_Sub1,SHOW);
		
		reset(debug,SHOW);
		set(debug_material,SHOW);
		
		break;
		//////////////////////////////////////////////////////////////
		
		case select_custom_mat3 :
		
		pass_mat_to_matsub(mat_custom[2]);
		set(panMat_Sub1,SHOW);
		
		reset(debug,SHOW);
		set(debug_material,SHOW);
		
		break;
		//////////////////////////////////////////////////////////////
		
		case select_custom_mat4 :
		
		pass_mat_to_matsub(mat_custom[3]);
		set(panMat_Sub1,SHOW);
		
		reset(debug,SHOW);
		set(debug_material,SHOW);
		
		break;
		//////////////////////////////////////////////////////////////
		
		default:
		printf("Material editor is available only to custom materials.");
		break;
	}	
}

void phy() {
	
	sharedGUI_centerpanel(panPhy);
	sharedGUI_updategui(panPhy);
	
	set(panPhy,SHOW);
}

void sharedGUI_panelselect(PANEL *p)
{
	if(last_pan) {
		last_pan.alpha = DEFAULT_ALPHA;
		layer_sort(last_pan,2);
		
		last_pan = p;
		layer_sort(last_pan,3);
		last_pan.alpha = 100;
	}
	else {
		last_pan = p;
		layer_sort(last_pan,3);
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

	////////////////////////////////////////////////////////////
	// For panProp
	////////////////////////////////////////////////////////////
	if(is(e,BRIGHT)) button_state(panProp,2,1);
	else button_state(panProp,2,0);
	
	if(is(e,INVISIBLE)) button_state(panProp,3,1);
	else button_state(panProp,3,0);
	
	if(is(e,NOFOG)) button_state(panProp,4,1);
	else button_state(panProp,4,0);
	
	if(is(e,OVERLAY)) button_state(panProp,5,1);
	else button_state(panProp,5,0);
	
	if(is(e,PASSABLE)) button_state(panProp,6,1);
	else button_state(panProp,6,0);
	
	if(is(e,POLYGON)) button_state(panProp,7,1);
	else button_state(panProp,7,0);
	
	if(is(e,SHADOW)) button_state(panProp,8,1);
	else button_state(panProp,8,0);
	
	if(is(e,TRANSLUCENT)) button_state(panProp,9,1);
	else button_state(panProp,9,0);
	
}

void controlcam() {
	
	if(button_state(panMain_Bottom,2,-1)) is_camera = 1;
	else {
		
		is_camera = 0;
		
		/* Free all checked flags */
		int i;
		for(i = 1;i < 4;i++) button_state(panMain_Top,i,0);
		
		manip_type = scale + 1;
		
	}
	
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

////////////////////////////////////////////////////////////
// These materials can't be customized. Thus selecting them make panMat_Sub1 disappears.
////////////////////////////////////////////////////////////
void _mat_select(var id) {
	
	switch(id) {
		
		case 2: // Lava
		
		mat_type = select_mat_lava;
		if(is(panMat_Sub1,SHOW)) {
			reset(panMat_Sub1,SHOW);
			
			if(is(debug_material,SHOW)) reset(debug_material,SHOW);
		}
		
		break;
		
		case 3: // Marble
		
		mat_type = select_mat_marble;
		if(is(panMat_Sub1,SHOW)) {
			reset(panMat_Sub1,SHOW);
			
			if(is(debug_material,SHOW)) reset(debug_material,SHOW);
		}
		
		break;
		
		case 4: // Smaragd
		
		mat_type = select_mat_smaragd;
		if(is(panMat_Sub1,SHOW)) {
			reset(panMat_Sub1,SHOW);
			
			if(is(debug_material,SHOW)) reset(debug_material,SHOW);
		}
		
		break;
		
		case 5: // Mat 4
		
		mat_type = select_mat_4;
		if(is(panMat_Sub1,SHOW)) {
			reset(panMat_Sub1,SHOW);
			
			if(is(debug_material,SHOW)) reset(debug_material,SHOW);
		}
		
		break;
		
		case 6: // Mat 5
		
		mat_type = select_mat_5;
		if(is(panMat_Sub1,SHOW)) {
			reset(panMat_Sub1,SHOW);
			
			if(is(debug_material,SHOW)) reset(debug_material,SHOW);
		}
		
		break;
		
		case 7: // Mat 6
		
		mat_type = select_mat_6;
		if(is(panMat_Sub1,SHOW)) {
			reset(panMat_Sub1,SHOW);
			
			if(is(debug_material,SHOW)) reset(debug_material,SHOW);
		}
		
		break;
		
		case 8: // Mat 7
		
		mat_type = select_mat_7;
		if(is(panMat_Sub1,SHOW)) {
			reset(panMat_Sub1,SHOW);
			
			if(is(debug_material,SHOW)) reset(debug_material,SHOW);
		}
		
		break;
		
		case 9: // Mat 8
		
		mat_type = select_mat_8;
		if(is(panMat_Sub1,SHOW)) {
			reset(panMat_Sub1,SHOW);
			
			if(is(debug_material,SHOW)) reset(debug_material,SHOW);
		}
		
		break;
		
		case 10: // Mat 9
		
		mat_type = select_mat_9;
		if(is(panMat_Sub1,SHOW)) {
			reset(panMat_Sub1,SHOW);
			
			if(is(debug_material,SHOW)) reset(debug_material,SHOW);
		}
		
		break;
		
		case 11: // Mat 10
		
		mat_type = select_mat_10;
		if(is(panMat_Sub1,SHOW)) {
			reset(panMat_Sub1,SHOW);
			
			if(is(debug_material,SHOW)) reset(debug_material,SHOW);
		}
		
		break;
		
		default:
		sys_exit(NULL);
		break;
		
	}
	
}

////////////////////////////////////////////////////////////
// These materials are customizable. You know what to do.
// Only customizable materials' properties is passed through
// pass_mat_to_matsub(MATERIAL *).
////////////////////////////////////////////////////////////
void _mat_select_custom(var id) {
	
	switch(id) {
		
		case 12: // Custom material #1
		
		mat_type = select_custom_mat1;
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
		
		case 13: // Custom material #2
		
		mat_type = select_custom_mat2;
		
		if(is(panMat_Sub1,SHOW))
		pass_mat_to_matsub(mat_custom[1]);
		
		break;
		
		case 14: // Custom material #3
		
		mat_type = select_custom_mat3;
		
		if(is(panMat_Sub1,SHOW))
		pass_mat_to_matsub(mat_custom[2]);
		
		break;
		
		case 15: // Custom material #4
		mat_type = select_custom_mat4;
		
		if(is(panMat_Sub1,SHOW))
		pass_mat_to_matsub(mat_custom[3]);
		
		break;
		
		default:
		sys_exit(NULL);
		break;
		
	}
	
}

////////////////////////////////////////////////////////////
// Select the NULL material.
////////////////////////////////////////////////////////////
void mat_select_null() {
	mat_type = select_mat_null;
	if(is(panMat_Sub1,SHOW)) {
		reset(panMat_Sub1,SHOW);
		
		if(is(debug_material,SHOW)) reset(debug_material,SHOW);
	}
}

void pass_mat_to_object() {
	
	if(select) { // make sure something have been saved to mat_temp
		
		switch(mat_type) {
			
			case select_mat_null :
			mat_temp = mat_model;
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
			
			case select_mat_4 :
			mat_temp = mat_marble;
			break;
			
			case select_mat_5 :
			mat_temp = mat_marble;
			break;
			
			case select_mat_6 :
			mat_temp = mat_marble;
			break;
			
			case select_mat_7 :
			mat_temp = mat_marble;
			break;
			
			case select_mat_8 :
			mat_temp = mat_marble;
			break;
			
			case select_mat_9 :
			mat_temp = mat_marble;
			break;
			
			case select_mat_10 :
			mat_temp = mat_marble;
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
		
		of.oid = o.skill4;
		of.of_objtype = o.obj_type;
		
		of.pStatic = o.skill2;
		of.pPhysics = o.skill3;
		
		of.dp = 1;
		
		break;
		////////////////////////////////////////////////////////////
		
		////////////////////////////////////////////////////////////
		case light:
		
		of._red = o.red;
		of._green = o.green;
		of._blue = o.blue;
		of._range = o.lightrange;
		
		of.of_objtype = o.obj_type;
		of.dp = 1;
		
		break;
		////////////////////////////////////////////////////////////
		
		////////////////////////////////////////////////////////////
		case snd:
		
		of.of_objtype = o.obj_type;
		of.oid = o.skill4;
		
		of.dp = 1;
		
		break;
		////////////////////////////////////////////////////////////
		
		////////////////////////////////////////////////////////////
		case part:
		
		of.of_objtype = o.obj_type;
		
		of.dp = 1;
		
		break;
		////////////////////////////////////////////////////////////
		
		default:
		sys_exit(NULL);
		break;
		
	}
	
	/*
	of._scale_x = o.scale_x;
	of._scale_y = o.scale_y;
	of._scale_z = o.scale_z;
	
	of._pan = o.pan;
	of._tilt = o.tilt;
	of._roll = o.roll;
	
	of._alpha = o.alpha;
	of._ambient = o.ambient;
	
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
	
	of.oid = o.skill1;
	of.pStatic = o.skill2;
	of.pPhysics = o.skill3;
	
	of.dp = 1;
	*/
	
}

void pass_clipboard_to_object(ENTITY *e) {
	
	/*
	e.material = clipboard.m;
	
	e.skill1 = clipboard.oid;
	e.skill2 = clipboard.pStatic;
	e.skill3 = clipboard.pPhysics;
	
	e.ambient = clipboard._ambient;
	e.alpha = clipboard._alpha;
	
	e.scale_x = clipboard._scale_x;
	e.scale_y = clipboard._scale_y;
	e.scale_z = clipboard._scale_z;
	
	e.pan = clipboard._pan;
	e.tilt = clipboard._tilt;
	e.roll = clipboard._roll;
	
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
	*/
	
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
		
		num_mdlobjs = clipboard.oid;
		
		e.obj_type = clipboard.of_objtype;
		e.skill4 = clipboard.oid;
		
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
		
		num_lightobjs = clipboard.oid;
		
		e.red = clipboard._red;
		e.green = clipboard._green;
		e.blue = clipboard._blue;
		e.lightrange = clipboard._range;
		
		e.material = mat_model;
		
		break;
		////////////////////////////////////////////////////////////
		
		////////////////////////////////////////////////////////////
		case part:
		
		e.material = mat_model;
		
		num_partobjs = clipboard.oid;
		
		break;
		////////////////////////////////////////////////////////////
		
		////////////////////////////////////////////////////////////
		case snd:
		
		e.material = mat_model;
		
		num_sndobjs = clipboard.oid;
		
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
	
	//	_obj_type_old = _obj_type;
	
	if(clipboard.dp) {
	   
		pass_clipboard_to_object(obj_create_from_clipboard());
		
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
	
	printf("Saved successfully.");
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
	while(mouse_left && is_camera && (manip_type > 0 && manip_type < 4))
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
	
	// Houston we got a problem here !
	if(!is_camera) {
		
		int i;
		for(i = 1;i < 4;i++) button_state(panMain_Top,i,0);
		manip_type = scale+1;
		
		return; // Kill him (stop him from doing bad things)
		
	}
	
	// Check its state first.
	if(button_state(panMain_Top,1,-1)) {
		
		button_state(panMain_Top,2,0);
		button_state(panMain_Top,3,0);
		
		// Switch to ' object move ' state.
		manip_type = move;
		
	}
	
	else {
		
		// The loop can't check this so nothing will be assigned
		// to manip_type.
		manip_type = scale+1;
		
	}
}

void switch_to_rotate() {
	
	if(!is_camera) {
		
		int i;
		for(i = 1;i < 4;i++) button_state(panMain_Top,i,0);
		manip_type = scale+1;
		
		return; // Kill him (stop him from doing bad things)
		
	}
	
	if(button_state(panMain_Top,2,-1)) {
		
		button_state(panMain_Top,1,0);
		button_state(panMain_Top,3,0);
		
		manip_type = rotate;
		
	}

	else manip_type = scale+1;
}

void switch_to_scale() {
	
	if(!is_camera) {
		
		int i;
		for(i = 1;i < 4;i++) button_state(panMain_Top,i,0);
		manip_type = scale+1;
		
		return; // Kill him (stop him from doing bad things)
		
	}
	
	if(button_state(panMain_Top,3,-1)) {
		
		button_state(panMain_Top,1,0);
		button_state(panMain_Top,2,0);
		
		manip_type = scale;
		
	}
	
	else manip_type = scale+1;
	
}

void hideGUI() {
	
	reset(panMain_Top,SHOW);
	reset(panMain_Bottom,SHOW);
	reset(panMain_Play,SHOW);
	
	// Also disables any remaining active content.
	reset(buttonlst_submenu_object,SHOW);
	reset(buttonlst_submenu_path,SHOW);
	reset(buttonlst_submenu_terrain,SHOW);
	
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
	ctrl = 0;
	
}

// Just a small function for use within panObj_Subbar_switcher(var).
// Updates the size of p according to b's size.
void update_size(PANEL *p, BMAP *b) {
	while(b == NULL || p == NULL) wait(1);
	
	p.size_x = bmap_width(b);
	p.size_y = bmap_height(b);
	
}

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

////////////////////////////////////////////////////////////
// Kernel-related functions.
////////////////////////////////////////////////////////////
void load_kernel(STRING *lvl_str) {
	
	// Initialization for loopix-project.com's MystyMood_Lite-C
	sky_curve = 2;
	sky_clip = -10;
	
	// Our own setup
	
	// Read and setup video settings prior to executing other functions.
	config_read_video("./src/cfg/video_config.cfg");
	
	video_window(NULL,NULL,0,"editor 0.8 Milestone 4");
	
	_obj_type = 1;
	
	mouse_range = 500000;
	mouse_map = mouse;
	
	// So that we can get access to the database.
	mdlobjs_table_ptr = mdlobjs_table;
	
	panHome.alpha = panMat.alpha = panPhy.alpha = panProp.alpha = DEFAULT_ALPHA;
	
	// Initialize the object database and load them.
	init_database();
	
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
	
	// Load the level.
	level_load(lvl_str);
	wait_for(level_load); // Wait for level_load to be completed.
	
	// Some nice effects and further setup before the game can be started.
	sharedGUI_blackscreen(FADE_OUT,2);
	wait_for(sharedGUI_blackscreen);
	
	sharedGUI_mouse(1); // Enables the mouse.
	
	ent_create("marker.mdl",nullvector,follow_pointer); // Create a mouse pointer.
	def_move();
	//	
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
			
			if(key_p) {
				
				while(key_p) wait(1);
				prop();
				
			}
			
			if(key_m) {
				
				while(key_m) wait(1);
				mat();
				
			}
			
			if(key_h) {
				
				while(key_h) wait(1);
				phy();
				
			}
			
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
		if(key_esc) {
			
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
		
		a=clipboard.oid;
		b=clipboard.of_objtype;
		
		if(key_t) 
		{
			while(key_t) wait(1);
			num_mdlobjs++;
		}
		
		if(key_y) {
			while(key_y) wait(1);
			num_mdlobjs--;
		}
		
		if(key_r) {
			
			while(key_r) wait(1);
			you = ent_next(NULL); // Point to the first entity in the list
			while(you) {
				
				ptr_remove(you);
				you = ent_next(you);
				
			}
			
			ent_create("marker.mdl",nullvector,follow_pointer); // Create a mouse pointer.
			
		}
		
		if(mouse_left) 
		{
			while(mouse_left) wait(1);
			
			if(!mouse_panel)
			{
				if(!is_camera) obj_create();
				
				if(mouse_ent)
				{
					if(select)
					{
						select.material = mat_temp;
						select = NULL;
					}
					
					select = mouse_ent;
					
					mat_temp = select.material; // Luc nay select da duoc xac dinh nen ta cu thoai mai
					select.material = mat_select;
					
					pass_to_gui(select);
					
				}
				
				else
				{
					if(select)
					{
						if(mat_temp) select.material = mat_temp;
						else select.material = NULL;
						
						select = NULL;
						
						reset(panProp,SHOW);
					}
					
					select = NULL;
					
					if(is(panProp,SHOW)) reset(panProp,SHOW);
					
				}
				
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
			
			if(key_del) ptr_remove(select);
			
			select.alpha = v_alpha;
			select.ambient = v_ambient;
			
			if(button_state(panProp,2,-1)) set(select,BRIGHT);
			else reset(select,BRIGHT);
			
			if(button_state(panProp,3,-1)) set(select,INVISIBLE);
			else reset(select,INVISIBLE);
			
			if(button_state(panProp,4,-1)) set(select,NOFOG);
			else reset(select,NOFOG);
			
			if(button_state(panProp,5,-1)) set(select,OVERLAY);
			else reset(select,OVERLAY);
			
			if(button_state(panProp,6,-1)) set(select,PASSABLE);
			else reset(select,PASSABLE);
			
			if(button_state(panProp,7,-1)) set(select,POLYGON);
			else reset(select,POLYGON);
			
			if(button_state(panProp,8,-1)) set(select,SHADOW);
			else reset(select,SHADOW);
			
			if(button_state(panProp,9,-1)) set(select,TRANSLUCENT);
			else reset(select,TRANSLUCENT);
			
		}
		
		if(key_cul) ctrl--;
		if(key_cur) ctrl++;
		
		if(ctrl<0) ctrl=0; // prevent unexpected situations
		if(ctrl>100) ctrl=100;
		
		panObj_Main.pos_x = (ctrl * (-bmap_width(panObj_Main.bmap) + screen_size.x))/100;
		
		if(panObj_Main.pos_x > 0) panObj_Main.pos_x = 0;
		if(panObj_Main.pos_x < -bmap_width(panObj_Main.bmap) + screen_size.x) {
			
			panObj_Main.pos_x = -bmap_width(panObj_Main.bmap) + screen_size.x;
			
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
void a_patroller()
{
	while(my == NULL) wait(1);
	
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

void a_patroller_node()
{
	while(my == NULL) wait(1);
	
	my_target_node = me;
	set(my_target_node, PASSABLE | POLYGON);
	
	my_target_node.emask |= ENABLE_SCAN;
}

////////////////////////////////////////////////////////////
// This is the camera controller I found when I was tweaking Mystymood.
////////////////////////////////////////////////////////////
action free_camera()
{
	VECTOR camera_force;
	set(my, INVISIBLE | POLYGON);
	
	camera_force.z = 0;
	vec_set(camera.x,my.x);
	vec_set(camera.pan,my.pan);

	while(1)
	{
		camera_force.x = (key_w - key_s)*10*time_step;
		camera_force.y = (key_a - key_d)*10*time_step;
		vec_add(my.pan,vector(mouse_force.x*(-7)*time_step,mouse_force.y*7*time_step,0));
		
		c_move(my,camera_force,nullvector,GLIDE+IGNORE_PASSABLE+IGNORE_PASSENTS+IGNORE_PUSH);
		vec_set(camera.x,vector(my.x,my.y,my.z+15));
		vec_set(camera.pan,my.pan);
		
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
	digits(0,20,99,"arial#25b",1,is_camera);
	
	flags = SHOW;
}

PANEL *debug_material = {
	layer = 3;
	
	digits(0,0,"Ambient red: %f","arial#15b",1,v_ambient_r);
	digits(0,10,"Ambient green: %f","arial#15b",1,v_ambient_g);
	digits(0,20,"Ambient blue: %f","arial#15b",1,v_ambient_b);
	
	digits(0,30,"Specular red: %f","arial#15b",1,v_specular_r);
	digits(0,40,"Specular green: %f","arial#15b",1,v_specular_g);
	digits(0,50,"Specular blue: %f","arial#15b",1,v_specular_b);
	
	digits(0,60,"Emissive red: %f","arial#15b",1,v_emissive_r);
	digits(0,70,"Emissive green: %f","arial#15b",1,v_emissive_g);
	digits(0,80,"Emissive blue: %f","arial#15b",1,v_emissive_b);
	
	digits(0,90,"Diffuse red: %f","arial#15b",1,v_diffuse_r);
	digits(0,100,"Diffuse green: %f","arial#15b",1,v_diffuse_g);
	digits(0,110,"Diffuse blue: %f","arial#15b",1,v_diffuse_b);
	
	digits(0,120,"Power: %f","arial#15b",1,v_power);
	digits(0,130,"Alpha: %f","arial#15b",1,v_alpha_m);
}