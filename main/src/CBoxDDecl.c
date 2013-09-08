/*
--------------------------------------------------
CBoxDDecl.c

Contains databases and data declarations. This file can be used to 
add and/or remove data, however it can cause unexpected side effects/
crashing if not careful. Only linear data modification is supported for
less development time, support for importing/exporting data from/to file
will be added later.

TODO:
<+++



>+++

NOTES:
<+++



>+++
--------------------------------------------------
*/

/*
--------------------------------------------------
void LoadSoundDatabase()


--------------------------------------------------
*/
void LoadSoundDatabase() {
	
	int i;
	
	////////////////////////////////////////////////////////////
	// Stupid sound database.
	// Use the same stupid database structure as LoadObjectDatabase().
	////////////////////////////////////////////////////////////
	sndobjs[0] = snd_create("hit.wav");
	
	// Unallocated space
	for(i = 1;i < MAX_SOUNDS;i++) sndobjs[i] = snd_create("beep.wav");
	
}

/*
--------------------------------------------------
void LoadParticleDatabase()


--------------------------------------------------
*/
void LoadParticleDatabase() {
	
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
	int i;
	for(i = 9;i < MAX_PARTICLES;i++) partobjs[i] = 0;
} 

/*
--------------------------------------------------
void LoadObjectDatabase()


--------------------------------------------------
*/
void LoadObjectDatabase() {
	
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
	mdlobjs_table[337] = str_create("e_streetlight.mdl");
	mdlobjs_table[338] = str_create("e_table.mdl");
	mdlobjs_table[339] = str_create("e_table1.mdl");
	mdlobjs_table[340] = str_create("e_table_blood.mdl");
	mdlobjs_table[341] = str_create("e_target.mdl");
	mdlobjs_table[342] = str_create("e_target1.mdl");
	mdlobjs_table[343] = str_create("e_torch.mdl");
	mdlobjs_table[344] = str_create("e_trashcan.mdl");
	mdlobjs_table[345] = str_create("e_trashcan1.mdl");
	mdlobjs_table[346] = str_create("e_trashcan2.mdl");
	mdlobjs_table[347] = str_create("e_treasure_chest.mdl");
	mdlobjs_table[348] = str_create("e_wheatpack.mdl");
	mdlobjs_table[349] = str_create("e_woodchair.mdl");
	mdlobjs_table[350] = str_create("e_woodchair2.mdl");

	// Unallocated space
	for (i = 351;i < 480;i++) mdlobjs_table[i] = str_create("#2");
	
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
	for(i = 841;i < MAX_OBJECTS;i++) mdlobjs_table[i] = str_create("#2");
	
	// Done!
	////////////////////////////////////////////////////////////
}

void LoadSavedBMAPs() {
	
	save_array[0] = handle(slot1);
	save_array[1] = handle(slot2);
	save_array[2] = handle(slot3);
	save_array[3] = handle(slot4);
	save_array[4] = handle(slot5);
	save_array[5] = handle(slot6);
	save_array[6] = handle(slot7);
	save_array[7] = handle(slot8);
	save_array[8] = handle(slot9);
	//	save_array[9] = handle(slot10);
	//	save_array[10] = handle(slot11);
	//	save_array[11] = handle(slot12);
	//	save_array[12] = handle(slot13);
	//	save_array[13] = handle(slot14);
	//	save_array[14] = handle(slot15);
	//	save_array[15] = handle(slot16);
	//	save_array[16] = handle(slot17);
	//	save_array[17] = handle(slot18);
	//	save_array[18] = handle(slot19);
	//	save_array[19] = handle(slot20);
	
	game_load(pref_savebmaps,0);
	
}