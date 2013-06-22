////////////////////////////////////////////////////////////
// This function will load the database.
////////////////////////////////////////////////////////////
void init_database() {
	
	// Don't ask me why I don't read the whole database
	// from an external file. I did it once - and failed.
	// The reason: try it yourself - it's an engine-related problem.
	
	// Still, there is an advantage. There will be no disk I/O
	// activity to be performed.
	
	// This is slow but probably because of my outdated Celeron D
	// processor. Maybe it will perform faster on a Pentium 4.
	
	wait(1);
	
	////////////////////////////////////////////////////////////

	// Animals 50 [0->49]
	// Allocated space
	sTable[0] = str_create("a_badger.mdl");
	sTable[1] = str_create("a_bat.mdl");
	sTable[2] = str_create("a_bluebird.mdl");
	sTable[3] = str_create("a_boar.mdl");
	sTable[4] = str_create("a_bug.mdl");
	sTable[5] = str_create("a_burkel.mdl");
	sTable[6] = str_create("a_butterfly.mdl");
	sTable[7] = str_create("a_crow.mdl");
	sTable[8] = str_create("a_fish1.mdl");
	sTable[9] = str_create("a_fish2.mdl");
	sTable[10] = str_create("a_fish3.mdl");
	sTable[11] = str_create("a_fish4.mdl");
	sTable[12] = str_create("a_fish5.mdl");
	sTable[13] = str_create("a_fish6.mdl");
	sTable[14] = str_create("a_fish7.mdl");
	sTable[15] = str_create("a_fish8.mdl");
	sTable[16] = str_create("a_rat.mdl");
	sTable[17] = str_create("a_snake.mdl");

	// Unallocated space
	int i;
	for(i = 18; i < 50;i++) sTable[i] = str_create("#2");

	// Architecture 80 [50->129]
	// Allocated space
	sTable[50] = str_create("a_building.wmb");
	sTable[51] = str_create("a_building1.mdl");
	sTable[52] = str_create("a_church.mdl");
	sTable[53] = str_create("a_fence.mdl");
	sTable[54] = str_create("a_fence_cylinder.mdl");
	sTable[55] = str_create("a_gate.mdl");
	sTable[56] = str_create("a_house1.mdl");
	sTable[57] = str_create("a_house2.mdl");
	sTable[58] = str_create("a_house3.mdl");
	sTable[59] = str_create("a_hut.mdl");
	sTable[60] = str_create("a_temple_entrance.mdl");
	sTable[61] = str_create("a_warehouse.mdl");
	sTable[62] = str_create("a_warehouse1.mdl");
	sTable[63] = str_create("a_warehouse2.mdl");
	sTable[64] = str_create("a_warehouse3.mdl");
	sTable[65] = str_create("a_warehouse4.mdl");
	sTable[66] = str_create("a__frame.mdl");

	// Unallocated space
	int i;
	for(i = 67;i < 130;i++) sTable[i] = str_create("#2");
	
	// Characters 50 [130->179]
	// Allocated space
	sTable[130] = str_create("c_badguy.mdl");
	sTable[131] = str_create("c_berzerka.mdl");
	sTable[132] = str_create("c_cgirl.mdl");
	sTable[133] = str_create("c_guard.mdl");
	sTable[134] = str_create("c_HCS_Warrior_C.mdl");
	sTable[135] = str_create("c_inmate.mdl");
	sTable[136] = str_create("c_ninja.mdl");
	sTable[137] = str_create("c_p_king_ochan.mdl");
	sTable[138] = str_create("c_p_lobster_mutant.mdl");
	sTable[139] = str_create("c_p_mario_h.mdl");
	sTable[140] = str_create("c_p_pirate.mdl");
	sTable[141] = str_create("c_p_r2_robot.mdl");
	sTable[142] = str_create("c_p_saucer.mdl");
	sTable[143] = str_create("c_p_skel.mdl");
	sTable[144] = str_create("c_rabbit.mdl");
	sTable[145] = str_create("c_soldier.mdl");
	sTable[146] = str_create("c_trooper.mdl");
	sTable[147] = str_create("c_warlock.mdl");
	sTable[148] = str_create("c_witch.mdl");
	sTable[149] = str_create("c__007.mdl");

	// Unallocated space
	int i;
	for(i = 150;i < 180;i++) sTable[i] = str_create("#2");

	// Everyday objects 300 [180-379]
	// Allocated objects
	sTable[180] = str_create("e_ball1.mdl");
	sTable[181] = str_create("e_ball10.mdl");
	sTable[182] = str_create("e_ball11.mdl");
	sTable[183] = str_create("e_ball12.mdl");
	sTable[184] = str_create("e_ball13.mdl");
	sTable[185] = str_create("e_ball14.mdl");
	sTable[186] = str_create("e_ball15.mdl");
	sTable[187] = str_create("e_ball2.mdl");
	sTable[188] = str_create("e_ball3.mdl");
	sTable[189] = str_create("e_ball4.mdl");
	sTable[190] = str_create("e_ball5.mdl");
	sTable[191] = str_create("e_ball6.mdl");
	sTable[192] = str_create("e_ball7.mdl");
	sTable[193] = str_create("e_ball8.mdl");
	sTable[194] = str_create("e_ball9.mdl");
	sTable[195] = str_create("e_balloon.mdl");
	sTable[196] = str_create("e_ball_white.mdl");
	sTable[197] = str_create("e_barrel.mdl");
	sTable[198] = str_create("e_barrel01.mdl");
	sTable[199] = str_create("e_barrel02.mdl");
	sTable[200] = str_create("e_barrel03.mdl");
	sTable[201] = str_create("e_barrel04.mdl");
	sTable[202] = str_create("e_barrel05.mdl");
	sTable[203] = str_create("e_barrel06.mdl");
	sTable[204] = str_create("e_barrel07.mdl");
	sTable[205] = str_create("e_barrel08.mdl");
	sTable[206] = str_create("e_barrel9.mdl");
	sTable[207] = str_create("e_barrier.mdl");
	sTable[208] = str_create("e_basketballbasket.mdl");
	sTable[209] = str_create("e_battery.mdl");
	sTable[210] = str_create("e_bench.mdl");
	sTable[211] = str_create("e_bench1.mdl");
	sTable[212] = str_create("e_bench2.mdl");
	sTable[213] = str_create("e_bench3.mdl");
	sTable[214] = str_create("e_bench4.mdl");
	sTable[215] = str_create("e_bench5.mdl");
	sTable[216] = str_create("e_bench6.mdl");
	sTable[217] = str_create("e_bench7.mdl");
	sTable[218] = str_create("e_bench8.mdl");
	sTable[219] = str_create("e_billard1.mdl");
	sTable[220] = str_create("e_billardlamp.mdl");
	sTable[221] = str_create("e_billiard.mdl");
	sTable[222] = str_create("e_billiard2.mdl");
	sTable[223] = str_create("e_billiard3.mdl");
	sTable[224] = str_create("e_billiard_queue.mdl");
	sTable[225] = str_create("e_book1.mdl");
	sTable[226] = str_create("e_books.mdl");
	sTable[227] = str_create("e_books2.mdl");
	sTable[228] = str_create("e_books3.mdl");
	sTable[229] = str_create("e_bookshelf.mdl");
	sTable[230] = str_create("e_box.mdl");
	sTable[231] = str_create("e_box1.mdl");
	sTable[232] = str_create("e_cabinet.mdl");
	sTable[233] = str_create("e_cabinet_corner.mdl");
	sTable[234] = str_create("e_cd.mdl");
	sTable[235] = str_create("e_cement_bag.mdl");
	sTable[236] = str_create("e_chair.mdl");
	sTable[237] = str_create("e_chair1.mdl");
	sTable[238] = str_create("e_chair2.mdl");
	sTable[239] = str_create("e_ciga.mdl"); 
	sTable[240] = str_create("e_clock.mdl");
	sTable[241] = str_create("e_cloud.mdl");
	sTable[242] = str_create("e_coin.mdl");
	sTable[243] = str_create("e_colamach.mdl");
	sTable[244] = str_create("e_crate.mdl");
	sTable[245] = str_create("e_crate1.mdl");
	sTable[246] = str_create("e_crate2.mdl");
	sTable[247] = str_create("e_crystal.mdl");
	sTable[248] = str_create("e_door.mdl");
	sTable[249] = str_create("e_door1.mdl");
	sTable[250] = str_create("e_door2.mdl");
	sTable[251] = str_create("e_door3.mdl");
	sTable[252] = str_create("e_door4.mdl");
	sTable[253] = str_create("e_dumpster.mdl");
	sTable[254] = str_create("e_d_booth_01.mdl");
	sTable[255] = str_create("e_extinguisher.mdl");
	sTable[256] = str_create("e_extinguisher1.mdl");
	sTable[257] = str_create("e_fence.mdl");
	sTable[258] = str_create("e_fire.mdl");
	sTable[259] = str_create("e_flag.mdl");
	sTable[260] = str_create("e_fridge.mdl");
	sTable[261] = str_create("e_frying_pan.mdl");
	sTable[262] = str_create("e_gift_box.mdl");
	sTable[263] = str_create("e_hydrant.mdl");
	sTable[264] = str_create("e_iPod.mdl");
	sTable[265] = str_create("e_lamp1.mdl");
	sTable[266] = str_create("e_lamp2.mdl");
	sTable[267] = str_create("e_lamp3.mdl");
	sTable[268] = str_create("e_lamp4.mdl");
	sTable[269] = str_create("e_leon_armoire.mdl");
	sTable[270] = str_create("e_leon_desk.mdl");
	sTable[271] = str_create("e_light.mdl");
	sTable[272] = str_create("e_mirror.mdl");
	sTable[273] = str_create("e_mirror1.mdl");
	sTable[274] = str_create("e_palette.mdl");
	sTable[275] = str_create("e_palette1.mdl");
	sTable[276] = str_create("e_parkingmeter.mdl");
	sTable[277] = str_create("e_piano.mdl");
	sTable[278] = str_create("e_picture.mdl");
	sTable[279] = str_create("e_picture1.mdl");
	sTable[280] = str_create("e_picture2.mdl");
	sTable[281] = str_create("e_picture3.mdl");
	sTable[282] = str_create("e_picture4.mdl");
	sTable[283] = str_create("e_picture5.mdl");
	sTable[284] = str_create("e_picture6.mdl");
	sTable[285] = str_create("e_picture7.mdl");
	sTable[286] = str_create("e_picture8.mdl");
	sTable[287] = str_create("e_pipe.mdl");
	sTable[288] = str_create("e_pipe1.mdl");
	sTable[289] = str_create("e_pipe2.mdl");
	sTable[290] = str_create("e_platform.mdl");
	sTable[291] = str_create("e_railway_45left.mdl");
	sTable[292] = str_create("e_railway_45right.mdl");
	sTable[293] = str_create("e_railway_doubleswitch.mdl");
	sTable[294] = str_create("e_railway_down.mdl");
	sTable[295] = str_create("e_railway_end.mdl");
	sTable[296] = str_create("e_railway_singleswitch.mdl");
	sTable[297] = str_create("e_railway_straight.mdl");
	sTable[298] = str_create("e_railway_up.mdl");
	sTable[299] = str_create("e_rail_lore1.mdl");
	sTable[300] = str_create("e_rope.mdl");
	sTable[301] = str_create("e_salonch.mdl");
	sTable[302] = str_create("e_salonch1.mdl");
	sTable[303] = str_create("e_sign_30.mdl");
	sTable[304] = str_create("e_sign_60.mdl");
	sTable[305] = str_create("e_sign_90.mdl");
	sTable[306] = str_create("e_sign_bicyclelane.mdl");
	sTable[307] = str_create("e_sign_boulder.mdl");
	sTable[308] = str_create("e_sign_bumpy-road.mdl");
	sTable[309] = str_create("e_sign_church.mdl");
	sTable[310] = str_create("e_sign_crosswinds.mdl");
	sTable[311] = str_create("e_sign_curve-ahead.mdl");
	sTable[312] = str_create("e_sign_endminimumspeed.mdl");
	sTable[313] = str_create("e_sign_exit.mdl");
	sTable[314] = str_create("e_sign_footpath.mdl");
	sTable[315] = str_create("e_sign_hospital.mdl");
	sTable[316] = str_create("e_sign_minimumspeed.mdl");
	sTable[317] = str_create("e_sign_noentry.mdl");
	sTable[318] = str_create("e_sign_noparking.mdl");
	sTable[319] = str_create("e_sign_nopassing.mdl");
	sTable[320] = str_create("e_sign_nostopping.mdl");
	sTable[321] = str_create("e_sign_novehicles.mdl");
	sTable[322] = str_create("e_sign_novisitor.mdl");
	sTable[323] = str_create("e_sign_oneside-road-narrow.mdl");
	sTable[324] = str_create("e_sign_parking.mdl");
	sTable[325] = str_create("e_sign_pedcrossing.mdl");
	sTable[326] = str_create("e_sign_pedestrian.mdl");
	sTable[327] = str_create("e_sign_phone.mdl");
	sTable[328] = str_create("e_sign_railroad.mdl");
	sTable[329] = str_create("e_sign_road-narrow.mdl");
	sTable[330] = str_create("e_sign_roundabout.mdl");
	sTable[331] = str_create("e_sign_slippery.mdl");
	sTable[332] = str_create("e_sign_traffic.mdl");
	sTable[333] = str_create("e_sign_trafficlights.mdl");
	sTable[334] = str_create("e_sign_turnscrossing.mdl");
	sTable[335] = str_create("e_sign_yield.mdl");
	sTable[336] = str_create("e_sofa.mdl");
	sTable[337] = str_create("e_strange_boar_toy.mdl");
	sTable[338] = str_create("e_strange_bowl.mdl");
	sTable[339] = str_create("e_strange_canvas.mdl");
	sTable[340] = str_create("e_strange_canvas2.mdl");
	sTable[341] = str_create("e_strange_crate.mdl");
	sTable[342] = str_create("e_strange_decorator.mdl");
	sTable[343] = str_create("e_strange_drums.mdl");
	sTable[344] = str_create("e_strange_flag.mdl");
	sTable[345] = str_create("e_strange_house.mdl");
	sTable[346] = str_create("e_strange_machine.mdl");
	sTable[347] = str_create("e_strange_placeholder.mdl");
	sTable[348] = str_create("e_strange_shelf.mdl");
	sTable[349] = str_create("e_strange_trough.mdl");
	sTable[350] = str_create("e_strange_umbrella.mdl");
	sTable[351] = str_create("e_strange_wine_barrel.mdl");
	sTable[352] = str_create("e_strange_wine_barrel2.mdl");
	sTable[353] = str_create("e_streetlight.mdl");
	sTable[354] = str_create("e_table.mdl");
	sTable[355] = str_create("e_table1.mdl");
	sTable[356] = str_create("e_table_blood.mdl");
	sTable[357] = str_create("e_target.mdl");
	sTable[358] = str_create("e_target1.mdl");
	sTable[359] = str_create("e_torch.mdl");
	sTable[360] = str_create("e_trashcan.mdl");
	sTable[361] = str_create("e_trashcan1.mdl");
	sTable[362] = str_create("e_trashcan2.mdl");
	sTable[363] = str_create("e_treasure_chest.mdl");
	sTable[364] = str_create("e_wheatpack.mdl");
	sTable[365] = str_create("e_woodchair.mdl");
	sTable[366] = str_create("e_woodchair2.mdl");

	// Unallocated space
	int i;
	for (i = 367;i < 480;i++) sTable[i] = str_create("#2");
	
	// Food 50 [480-529]
	// Allocated space
	sTable[480] = str_create("f_apple_green.mdl");
	sTable[481] = str_create("f_apple_red.mdl");
	sTable[482] = str_create("f_bagel.mdl");
	sTable[483] = str_create("f_banana.mdl");
	sTable[484] = str_create("f_bread.mdl");
	sTable[485] = str_create("f_bread_loaf.mdl");
	sTable[486] = str_create("f_carrot.mdl");
	sTable[487] = str_create("f_cookie.mdl");
	sTable[488] = str_create("f_cookie1.mdl");
	sTable[489] = str_create("f_cookie2.mdl");
	sTable[490] = str_create("f_cookie3.mdl");
	sTable[491] = str_create("f_corn.mdl");
	sTable[492] = str_create("f_croissaint.mdl");
	sTable[493] = str_create("f_donut.mdl");
	sTable[494] = str_create("f_donut1.mdl");
	sTable[495] = str_create("f_foodsack.mdl");
	sTable[496] = str_create("f_genericf.mdl");
	sTable[497] = str_create("f_hamburger.mdl");
	sTable[498] = str_create("f_hotdog.mdl");
	sTable[499] = str_create("f_icecream.mdl");
	sTable[500] = str_create("f_nectarine.mdl");
	sTable[501] = str_create("f_orange.mdl");
	sTable[502] = str_create("f_pear.mdl");
	sTable[503] = str_create("f_pizza.mdl");
	sTable[504] = str_create("f_squash.mdl");
	sTable[505] = str_create("f_steak.mdl");
	sTable[506] = str_create("f_tomato.mdl");
	sTable[507] = str_create("f_watermelon.mdl");
	sTable[508] = str_create("f_watermelon_piece.mdl");

	// Unallocated space
	int i;
	for(i = 509;i < 530;i++) sTable[i] = str_create("#2");
	
	// Machines 50 [570-619]
	// Allocated space
	sTable[570] = str_create("m_console.mdl");
	sTable[571] = str_create("m_generator.mdl");
	sTable[572] = str_create("m_generator1.mdl");
	sTable[573] = str_create("m_generator2.mdl");
	sTable[574] = str_create("m_hatch.mdl");
	sTable[575] = str_create("m_powerplant.mdl");
	sTable[576] = str_create("m_turret02.mdl");

	// Unallocated space
	int i;
	for(i = 577;i < 620;i++) sTable[i] = str_create("#2");
	
	// Plants 150 [620-779]
	// Allocated space
	sTable[620] = str_create("bigtree2.mdl");
	sTable[621] = str_create("bstone1.mdl");
	sTable[622] = str_create("bstone2.mdl");
	sTable[623] = str_create("bush1.mdl");
	sTable[624] = str_create("bush3.mdl");
	sTable[625] = str_create("bush7.mdl");
	sTable[626] = str_create("d_14_lod0.mdl");
	sTable[627] = str_create("d_Fantasy_tree1.mdl");
	sTable[628] = str_create("d_flower_10.mdl");
	sTable[629] = str_create("d_flower_6.mdl");
	sTable[630] = str_create("d_litGr.mdl");
	sTable[631] = str_create("fern_1.mdl");
	sTable[632] = str_create("flower_1.mdl");
	sTable[633] = str_create("gpalm1.mdl");
	sTable[634] = str_create("grass.mdl");
	sTable[635] = str_create("grass1.mdl");
	sTable[636] = str_create("grass2.mdl");
	sTable[637] = str_create("grass3.mdl");
	sTable[638] = str_create("grass_scatt.mdl");
	sTable[639] = str_create("indoorplant.mdl");
	sTable[640] = str_create("kava_plant.mdl");
	sTable[641] = str_create("kaya2.mdl");
	sTable[642] = str_create("kaya3.mdl");
	sTable[643] = str_create("lightray1.mdl");
	sTable[644] = str_create("lp_birke_kr.mdl");
	sTable[645] = str_create("lp_birke_st.mdl");
	sTable[646] = str_create("lp_busch1.mdl");
	sTable[647] = str_create("lp_chunk1.mdl");
	sTable[648] = str_create("lp_farn.mdl");
	sTable[649] = str_create("lp_grass.mdl");
	sTable[650] = str_create("lp_Pine1_kr.mdl");
	sTable[651] = str_create("lp_Pine1_st.mdl");
	sTable[652] = str_create("lp_spruce_kr.mdl");
	sTable[653] = str_create("lp_spruce_st.mdl");
	sTable[654] = str_create("lp_stones.mdl");
	sTable[655] = str_create("lp_tree2_kr.mdl");
	sTable[656] = str_create("lp_tree2_st.mdl");
	sTable[657] = str_create("lp_tree_trck.mdl");
	sTable[658] = str_create("mushroom1.mdl");
	sTable[659] = str_create("mushroom2.mdl");
	sTable[660] = str_create("mushroom3.mdl");
	sTable[661] = str_create("mushrooms1.mdl");
	sTable[662] = str_create("mushrooms2.mdl");
	sTable[663] = str_create("plant1.mdl");
	sTable[664] = str_create("platane.mdl");
	sTable[665] = str_create("rays1.mdl");
	sTable[666] = str_create("rays2.mdl");
	sTable[667] = str_create("shrub.mdl");
	sTable[668] = str_create("sstone1.mdl");
	sTable[669] = str_create("stone_fountain.mdl");
	sTable[670] = str_create("stone_ground_small.mdl");
	sTable[671] = str_create("t1.mdl");
	sTable[672] = str_create("t2.mdl");
	sTable[673] = str_create("t3.mdl");
	sTable[674] = str_create("t4.mdl");
	sTable[675] = str_create("t6.mdl");
	sTable[676] = str_create("t7.mdl");
	sTable[677] = str_create("tree1.mdl");
	sTable[678] = str_create("tree2.mdl");
	sTable[679] = str_create("tree4.mdl");
	sTable[680] = str_create("tree5.mdl");
	sTable[681] = str_create("Tree5_2.mdl");
	sTable[682] = str_create("tree_lo.mdl");
	sTable[683] = str_create("tree_log1.mdl");
	sTable[684] = str_create("waterfall.mdl");
	sTable[685] = str_create("weed1.mdl");
	sTable[686] = str_create("weed10.mdl");
	sTable[687] = str_create("weed11.mdl");
	sTable[688] = str_create("weed12.mdl");
	sTable[689] = str_create("weed13.mdl");
	sTable[690] = str_create("weed14.mdl");
	sTable[691] = str_create("weed15.mdl");
	sTable[692] = str_create("weed16.mdl");
	sTable[693] = str_create("weed17.mdl");
	sTable[694] = str_create("weed18.mdl");
	sTable[695] = str_create("weed2.mdl");
	sTable[696] = str_create("weed24.mdl");
	sTable[697] = str_create("weed3.mdl");
	sTable[698] = str_create("weed4.mdl");
	sTable[699] = str_create("weed5.mdl");
	sTable[700] = str_create("weed6.mdl");
	sTable[701] = str_create("weed7.mdl");
	sTable[702] = str_create("weed8.mdl");
	sTable[703] = str_create("weed9.mdl");
	sTable[704] = str_create("weedm.mdl");
	
	// Unallocated space
	int i;
	for(i = 705;i < 770;i++) sTable[i] = str_create("#2");
	
	// Transportations 50 [770-829]
	// Allocated space
	sTable[770] = str_create("t_bomber.mdl");
	sTable[771] = str_create("t_bomber1.mdl");
	sTable[772] = str_create("t_car1.mdl");
	sTable[773] = str_create("t_car2.mdl");
	sTable[774] = str_create("t_car3.mdl");
	sTable[775] = str_create("t_car4.mdl");
	sTable[776] = str_create("t_car_mr2.mdl");
	sTable[777] = str_create("t_f105_thug.mdl");
	sTable[778] = str_create("t_f16.mdl");
	sTable[779] = str_create("t_hover1.mdl");
	sTable[780] = str_create("t_lancaster.mdl");
	sTable[781] = str_create("t_mcdf4_phantom.mdl");
	sTable[782] = str_create("t_shopping.caddy.mdl");
	sTable[783] = str_create("t_tank.mdl");
	sTable[784] = str_create("t_tank1.mdl");
	sTable[785] = str_create("t_trainpart.mdl");
	sTable[786] = str_create("t_Viper.mdl");
	sTable[787] = str_create("t_wagon.mdl");

	// Unallocated space
	int i;
	for(i = 788; i < 830;i++) sTable[i] = str_create("#2");
	
	// Done!
	////////////////////////////////////////////////////////////
}

ENTITY *obj_create() { // This inherits a lot from place_me
	
	if(str_len(sTable_ptr[obj_type]) == 0) return;
	
	ENTITY *tmp = ent_create(sTable_ptr[obj_type],temp_pos.x,obj_manip_setup);
	
	while(tmp == NULL) wait(1); // wait for tmp to be completely created.
	
	set(tmp, POLYGON);
	reset(tmp, NOFOG | INVISIBLE | TRANSLUCENT); // Tha giet nham con hon bo sot
	
	tmp.alpha = 0;
	tmp.ambient = 50;
	
	tmp.material = mat_model;
	
	tmp.skill1 = obj_type;
	
	return tmp;
}

MATERIAL *mat_smaragd = {
	ambient_red = 100;
	ambient_green = 255;
	ambient_blue = 100;
	diffuse_red = 0;
	diffuse_green = 100;
	diffuse_blue = 0;
	specular_red = 255;
	specular_green = 255;
	specular_blue = 255;
	power = 10;
}

MATERIAL *mat_lava = {
	emissive_red = 200;
	emissive_green = 70;
	emissive_blue = 20;
	ambient_red = 255;
	ambient_green = 150;
	ambient_blue = 50;
	diffuse_red = 200;
	diffuse_green = 150;
	diffuse_blue = 50;
	specular_red = 255;
	specular_green = 255;
	specular_blue = 255;
	alpha = 60;
	albedo = 70;
	power = 10;
}

MATERIAL *mat_marble = {
	emissive_red = 30;
	emissive_green = 30;
	emissive_blue = 30;
	ambient_red = 200;
	ambient_green = 225;
	ambient_blue = 200;
	diffuse_red = 255;
	diffuse_green = 255;
	diffuse_blue = 255;
	specular_red = 255;
	specular_green = 255;
	specular_blue = 255;
	power = 10;
}

MATERIAL* mat_select = 
{
	ambient_red=255;
	ambient_green=255;
	ambient_blue=0;
	diffuse_red=255;
	diffuse_green=255;
	diffuse_blue=0;
}

TEXT* files_list = 
{ 
	strings = 1000; 
	pos_x = 0;
	pos_y = 0;
	font = "Arial#25b";
	flags=SHOW;
}

/*
void main(void) {
	//	CreateDirectory("cd",0);
	scan_folder("sharedData","pcx");
}
*/

void scan_folder(STRING *dir, STRING *ext)
{
	TEXT* read_files = {strings = 1000;}
	
	STRING* search_form = "a";

	str_cpy(current_folder,dir);

	str_cpy(search_form,dir);
	str_cat(search_form,"\\*.");
	str_cat(search_form,ext);
	
	files_found = txt_for_dir(read_files, search_form);
	
	var num = files_already;
	while(num<999)
	{
		str_cpy((files_list.pstring)[num],"");
		num+=1;
	}
	
	num=0;
	while(num<files_found)
	{
		str_cpy((files_list.pstring)[num+files_already],(read_files.pstring)[num]);
		num+=1;
	}
	list_start=0;
	
	wait(1);
}

PANEL *buttonlst_submenu_terrain = {
	layer = 1;
	
	bmap = "button_submenu_black.bmp";
	
	button(0,0,menu1_submenu1,menu1_submenu1_off,menu1_submenu1_over,NULL,NULL,NULL);
	button(0,0,menu1_submenu2,menu1_submenu2_off,menu1_submenu2_over,NULL,NULL,NULL);
	button(0,0,menu1_submenu3,menu1_submenu3_off,menu1_submenu3_over,NULL,NULL,NULL);
	button(0,0,menu1_submenu4,menu1_submenu4_off,menu1_submenu4_over,NULL,NULL,NULL);
	
	// The final button will be the back button.
	button(0,0,button_back,button_back,button_back_over,sharedGUI_closewindow,NULL,NULL);
	
	flags = OVERLAY;
}

PANEL *buttonlst_submenu_object = {
	layer = 1;
	
	bmap = "button_submenu_black.bmp";
	
	button(0,0,menu2_submenu1,menu2_submenu1_off,menu2_submenu1_over,NULL,NULL,NULL);
	button(0,0,menu2_submenu2,menu2_submenu2_off,menu2_submenu2_over,NULL,NULL,NULL);
	//	button(0,0,menu2_submenu3,menu2_submenu3,menu2_submenu3,NULL,NULL,NULL);
	//	button(0,0,menu2_submenu4,menu2_submenu4,menu2_submenu4,NULL,NULL,NULL);
	
	button(0,0,button_back,button_back,button_back_over,sharedGUI_closewindow,NULL,NULL);
	
	flags = OVERLAY;
}

PANEL *buttonlst_submenu_path = {
	layer = 1;
	
	bmap = "button_submenu_black.bmp";
	
	button(0,0,menu3_submenu1,menu3_submenu1_off,menu3_submenu1_over,NULL,NULL,NULL);
	button(0,0,menu3_submenu2,menu3_submenu2_off,menu3_submenu2_over,NULL,NULL,NULL);
	//	button(0,0,menu3_submenu3,menu3_submenu3,menu3_submenu3,NULL,NULL,NULL);
	//	button(0,0,menu3_submenu4,menu3_submenu4,menu3_submenu4,NULL,NULL,NULL);
	
	button(0,0,button_back,button_back,button_back_over,sharedGUI_closewindow,NULL,NULL);
	
	flags = OVERLAY;
}

PANEL *panHome = {
	layer = 2;
	
	bmap = "panHome.bmp";
	
	button(0,0,button_Close,button_Close_off,button_Close_over,sharedGUI_closewindow,NULL,NULL);
	
	button(0,0,button_Home_saveworld,button_Home_saveworld_off,button_Home_saveworld_over,NULL,NULL,NULL);
	button(0,0,button_Home_loadworld,button_Home_loadworld_off,button_Home_loadworld_over,NULL,NULL,NULL);
	button(0,0,button_Home_newworld,button_Home_newworld_off,button_Home_newworld_over,NULL,NULL,NULL);
	button(0,0,button_Home_quitworld,button_Home_quitworld_off,button_Home_quitworld_over,NULL,NULL,NULL);
	button(0,0,button_Home_compileworld,button_Home_compileworld_off,button_Home_compileworld_over,NULL,NULL,NULL);
	button(0,0,button_Home_configworld,button_Home_configworld_off,button_Home_configworld_over,NULL,NULL,NULL);
	
	on_click = sharedGUI_dragpanel;
	
	flags = OVERLAY | TRANSLUCENT;
}

PANEL *panProp = {
	layer = 2;
	
	bmap = "panProp.bmp";
	
	button(0,0,button_Close,button_Close_off,button_Close_over,sharedGUI_closewindow,NULL,NULL);
	
	button_toggle(0,0,flag_BIRGHT_on,flag_BIRGHT,flag_BIRGHT_on,flag_BIRGHT_on,NULL,NULL,NULL);
	button_toggle(0,0,flag_INVISIBLE_on,flag_INVISIBLE,flag_INVISIBLE_on,flag_INVISIBLE_on,NULL,NULL,NULL);
	button_toggle(0,0,flag_NOFOG_on,flag_NOFOG,flag_NOFOG_on,flag_NOFOG_on,NULL,NULL,NULL);
	button_toggle(0,0,flag_OVERLAY_on,flag_OVERLAY,flag_OVERLAY_on,flag_OVERLAY_on,NULL,NULL,NULL);
	button_toggle(0,0,flag_PASSABLE_on,flag_PASSABLE,flag_PASSABLE_on,flag_PASSABLE_on,NULL,NULL,NULL);
	button_toggle(0,0,flag_POLYGON_on,flag_POLYGON,flag_POLYGON_on,flag_POLYGON_on,NULL,NULL,NULL);
	button_toggle(0,0,flag_SHADOW_on,flag_SHADOW,flag_SHADOW_on,flag_SHADOW_on,NULL,NULL,NULL);
	button_toggle(0,0,flag_TRANSLUCENT_on,flag_TRANSLUCENT,flag_TRANSLUCENT_on,flag_TRANSLUCENT_on,NULL,NULL,NULL);
	
	button(0,0,button_default,button_default_off,button_default_over,restore,NULL,NULL);
	
	hslider(0,0,100,slider,0,100,v_alpha);	
	hslider(0,0,100,slider,0,100,v_ambient);	
	
	on_click = sharedGUI_dragpanel;
	
	flags = TRANSLUCENT | OVERLAY;
}

PANEL *panPhy = {
	layer = 2;
	
	bmap = "panPhy.bmp";
	
	button(0,0,button_Close,button_Close_off,button_Close_over,sharedGUI_closewindow,NULL,NULL);
	
	button_toggle(0,0,flag_PHY_on,flag_PHY,flag_PHY_on,flag_PHY_on,NULL,NULL,NULL);
	
	hslider(0,0,100,slider,0,100,v_friction);
	hslider(0,0,100,slider,0,100,v_bounciness);
	
	on_click = sharedGUI_dragpanel;
	
	flags = OVERLAY | TRANSLUCENT;
}

PANEL *panMat = {
	layer = 2;
	
	bmap = "panMat.bmp";
	
	button(0,0,button_Close,button_Close_off,button_Close_over,sharedGUI_closewindow,NULL,NULL);
	
	button(0,0,button_Mat1,button_Mat1,button_Mat1,mat_select_lava,NULL,NULL);
	button(0,0,button_Mat2,button_Mat2,button_Mat2,mat_select_marble,NULL,NULL);
	button(0,0,button_Mat3,button_Mat3,button_Mat3,mat_select_smaragd,NULL,NULL);
	button(0,0,button_Mat4,button_Mat4,button_Mat4,mat_select_4,NULL,NULL);
	button(0,0,button_Mat5,button_Mat5,button_Mat5,mat_select_5,NULL,NULL);
	button(0,0,button_Mat6,button_Mat6,button_Mat6,mat_select_6,NULL,NULL);
	button(0,0,button_Mat7,button_Mat7,button_Mat7,mat_select_7,NULL,NULL);
	button(0,0,button_Mat8,button_Mat8,button_Mat8,mat_select_8,NULL,NULL);
	button(0,0,button_Mat9,button_Mat9,button_Mat9,mat_select_9,NULL,NULL);
	button(0,0,button_Mat10,button_Mat10,button_Mat10,mat_select_10,NULL,NULL);
	button(0,0,button_Mat11,button_Mat11,button_Mat11,mat_select_11,NULL,NULL);
	button(0,0,button_Mat12,button_Mat12,button_Mat12,mat_select_12,NULL,NULL);
	button(0,0,button_Mat13,button_Mat13,button_Mat13,mat_select_13,NULL,NULL);
	button(0,0,button_Mat14,button_Mat14,button_Mat14,mat_select_14,NULL,NULL);
	button(0,0,button_Mat15,button_Mat15,button_Mat15,mat_select_null,NULL,NULL);
	
	button(0,0,button_editmat,button_editmat,button_editmat,sharedGUI_editmat,NULL,NULL);
	button(0,0,button_matapply,button_matapply_off,button_matapply_over,pass_mat_to_object,NULL,NULL);
	
	on_click = sharedGUI_dragpanel;
	
	flags = OVERLAY | TRANSLUCENT;
}

PANEL *panMat_Sub1 = {
	layer = 2;
	
	bmap = "panMatEd.bmp";
	
	button(0,0,button_Close,button_Close_off,button_Close_over,sharedGUI_closewindow,NULL,NULL);
	
	button(0,0,button_editmat_def,button_editmat_def,button_editmat_def,NULL,NULL,NULL);
	button(0,0,button_editmat_save,button_editmat_save,button_editmat_save,mat_save,NULL,NULL);
	
	// we need 14 sliders for ambient x3, specular x3, diffuse x3 and emissive x3
	// +power, +alpha.
	
	hslider(0,0,50,slider,0,255,v_emissive_r);
	hslider(0,0,50,slider,0,255,v_emissive_g);
	hslider(0,0,50,slider,0,255,v_emissive_b);
	
	hslider(0,0,50,slider,0,255,v_ambient_r);
	hslider(0,0,50,slider,0,255,v_ambient_g);
	hslider(0,0,50,slider,0,255,v_ambient_b);
	
	hslider(0,0,50,slider,0,255,v_diffuse_r);
	hslider(0,0,50,slider,0,255,v_diffuse_g);
	hslider(0,0,50,slider,0,255,v_diffuse_b);
	
	hslider(0,0,50,slider,0,255,v_specular_r);
	hslider(0,0,50,slider,0,255,v_specular_g);
	hslider(0,0,50,slider,0,255,v_specular_b);
	
	hslider(0,0,50,slider,0,10,v_power);
	hslider(0,0,50,slider,0,255,v_alpha_m);
	
	on_click = sharedGUI_dragpanel;
	
	flags = OVERLAY | TRANSLUCENT;
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
		
		pan_setpos(panProp,4,1,vector(BORDER + 102,BORDER * 2 + 23,0));
		pan_setpos(panProp,4,2,vector(BORDER + 102,BORDER * 3 + 23 * 2,0));
		pan_setpos(panProp,4,3,vector(BORDER + 102,BORDER * 4 + 23 * 3,0));
		
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
	if(bmap_width(p.bmap)*bmap_height(p.bmap) > bmap_width(s.bmap)*bmap_height(s.bmap)) return;
	
	if(bmap_width(s.bmap) > bmap_width(p.bmap))
	p.pos_x = (bmap_width(s.bmap) - bmap_width(p.bmap))/2;
	
	if(bmap_height(s.bmap) > bmap_height(p.bmap))
	p.pos_y = (bmap_height(s.bmap) - bmap_height(p.bmap))/2;
}

void sharedGUI_loadbuttons() {
	
	panMain_Top.pos_x = screen_size.x - bmap_width(panMain_Top.bmap) - (BORDER + 3 * BUTTON_SIZE);
	panMain_Top.pos_y = BORDER;
	
	panMain_Bottom.pos_x = BORDER;
	panMain_Bottom.pos_y = screen_size.y - bmap_height(panMain_Bottom.bmap) - BORDER;

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

void sharedGUI__loadbuttons() {
	
	if(is(panMain_Top,SHOW)) reset(panMain_Top,SHOW);
	if(is(panMain_Bottom,SHOW)) reset(panMain_Bottom,SHOW);
	if(is(panMain_Play,SHOW)) reset(panMain_Play,SHOW);
}

PANEL *panMain_Top = {
	layer = 0;
	
	bmap = "panMain_Top.bmp";
	
	//	button(0,0,button_Cut,button_Cut_Off,button_Cut_Over,obj_cut,NULL,NULL);
	//	button(0,0,button_Copy,button_Copy_Off,button_Copy_Over,obj_copy,NULL,NULL);
	//	button(0,0,button_Paste,button_Paste_Off,button_Paste_Over,obj_paste,NULL,NULL);
	
	button_toggle(0,0,flag_MOVE_on,flag_MOVE,flag_MOVE_on,flag_MOVE_on,switch_to_move,NULL,NULL);
	button_toggle(0,0,flag_ROTATE_on,flag_ROTATE,flag_ROTATE_on,flag_ROTATE_on,switch_to_rotate,NULL,NULL);
	button_toggle(0,0,flag_SCALE_on,flag_SCALE,flag_SCALE_on,flag_SCALE_on,switch_to_scale,NULL,NULL);
	
	button(0,0,button_Prop,button_Prop_Off,button_Prop_Over,sharedGUI_prop,NULL,NULL);
	button(0,0,button_Phy,button_Phy_Off,button_Phy_Over,sharedGUI_phy,NULL,NULL);
	button(0,0,button_Mat,button_Mat_Off,button_Mat_Over,sharedGUI_mat,NULL,NULL);
	
	flags = SHOW;
}

PANEL *panMain_Bottom = {
	layer = 0;
	
	bmap = "panMain_Bottom.bmp";

	button(0,0,button_Home,button_Home_Off,button_Home_Over,sharedGUI_home,NULL,NULL);
	button_toggle(0,0,button_Cam,button_Cam_Off,button_Cam,button_Cam,controlcam,NULL,NULL);
	button(0,0,button_Terrain,button_Terrain_Off,button_Terrain_Over,sharedGUI_launch_terrain,NULL,NULL);
	button(0,0,button_Objs,button_Objs_Off,button_Objs_Over,sharedGUI_launch_object,NULL,NULL);
	button(0,0,button_Path,button_Path_Off,button_Path_Over,sharedGUI_launch_path,NULL,NULL);
	
	flags = OVERLAY | SHOW;
}

PANEL *panMain_Play = {
	layer = 0;
	
	bmap = "panMain_Play.bmp";
	
	button(0,0,button_Play,button_Play_off,button_Play_over,NULL,NULL,NULL);
	
	flags = OVERLAY | SHOW;
}

STRING *sharedGUI_releaseStr = "                       ";

TEXT *sharedGUI_releaseTEXT = {
	string(sharedGUI_releaseStr);
	font = "Arial#25b";
}

PANEL *_logo = {
	bmap = "_logo.bmp";
	flags = OVERLAY;	
}

PANEL *blackscreen = {
	bmap = "bitmap.bmp";
}

void sharedGUI_loadscene(STRING *s) {
	level_load(s);
}

void sharedGUI_rescale(PANEL *p) {
	while(p == NULL) wait(1);
	
	p.pos_x = 0;
	p.pos_y = 0;
	
	p.scale_x = screen_size.x/bmap_width(p.bmap);
	p.scale_y = screen_size.y/bmap_height(p.bmap);
}

void sharedGUI_blackscreen(int mode, int sec) {
	sharedGUI_rescale(blackscreen);
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

void sharedGUI_release(STRING *str) {
	str_cpy(sharedGUI_releaseStr,str);

	sharedGUI_releaseTEXT->pos_x = screen_size.x - str_width(sharedGUI_releaseStr,"Arial#25b");
	sharedGUI_releaseTEXT->pos_y = screen_size.y - str_width(sharedGUI_releaseStr,"Arial#25b");
	
	set(sharedGUI_releaseTEXT,SHOW);
}

void sharedGUI__release() {
	if(is(sharedGUI_releaseTEXT,SHOW)) reset(sharedGUI_releaseTEXT,SHOW);
	str_cpy(sharedGUI_releaseStr,"");
}

void sharedGUI_playintro(STRING *what, var vol) {
	proc_kill(4);
	
	if(vol<0) vol = 100;
	
	var hndl;
	hndl = media_play(what,NULL,vol);

	while(media_playing(hndl)) wait(1);
}

void sharedGUI_loadbackground(STRING *lv_name) {
	//		sharedGUI_playintro(100);
	//		wait_for(sharedGUI_playintro);
	
	sharedGUI_loadscene(lv_name);
	wait_for(sharedGUI_loadscene);
	
	sharedGUI_loadbuttons();
	wait_for(sharedGUI_loadbuttons);
	
	sharedGUI_blackscreen(FADE_OUT,2);
	wait_for(sharedGUI_blackscreen);
	
	sharedGUI_mouse(ON);
}

void sharedGUI_mouse(int mode) {
	if(mode == OFF) mouse_mode = 0;
	if(mode == ON) mouse_mode = 4;
}

void sharedGUI_mouseset(BMAP *b) {
	mouse_map = b;
}

void sharedGUI_home() {
	
	sharedGUI_centerpanel(panHome);
	sharedGUI_updategui(panHome);
	
	set(panHome,SHOW);
}

void sharedGUI_prop() {
	
	if(select) {
		
		panProp.pos_x = BORDER;
		panProp.pos_y = screen_size.y - (2 * BORDER) - 32 - bmap_height(panProp.bmap);
		
		sharedGUI_updategui(panProp);
		
		set(panProp,SHOW);
		
	}
}

void sharedGUI_mat() {
	
	sharedGUI_centerpanel(panMat);
	sharedGUI_updategui(panMat);
	
	set(panMat,SHOW);
}

void sharedGUI_editmat() {
	
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

void sharedGUI_phy() {
	
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

void pass_to_object()
{
	while(select)
	{
		if(key_del) ptr_remove(select);
		
		select.alpha = v_alpha;
		select.ambient = v_ambient;
		
		if(button_state(panProp,2,-1) == ON) set(select,BRIGHT);
		else reset(select,BRIGHT);
		
		if(button_state(panProp,3,-1) == ON) set(select,INVISIBLE);
		else reset(select,INVISIBLE);
		
		if(button_state(panProp,4,-1) == ON) set(select,NOFOG);
		else reset(select,NOFOG);
		
		if(button_state(panProp,5,-1) == ON) set(select,OVERLAY);
		else reset(select,OVERLAY);
		
		if(button_state(panProp,6,-1) == ON) set(select,PASSABLE);
		else reset(select,PASSABLE);
		
		if(button_state(panProp,7,-1) == ON) set(select,POLYGON);
		else reset(select,POLYGON);
		
		if(button_state(panProp,8,-1) == ON) set(select,SHADOW);
		else reset(select,SHADOW);
		
		if(button_state(panProp,9,-1) == ON) set(select,TRANSLUCENT);
		else reset(select,TRANSLUCENT);
		
		wait(1);
	}
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
	if(button_state(panMain_Bottom,2,-1) == OFF) is_camera = 0;
	else is_camera = 1;
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

////////////////////////////////////////////////////////////
// These materials can't be customized. Thus selecting them make panMat_Sub1 disappears.
////////////////////////////////////////////////////////////
void mat_select_null() {
	mat_type = select_mat_null;
	if(is(panMat_Sub1,SHOW)) {
		reset(panMat_Sub1,SHOW);
		
		if(is(debug_material,SHOW)) reset(debug_material,SHOW);
	}
}

void mat_select_lava() {
	mat_type = select_mat_lava;
	if(is(panMat_Sub1,SHOW)) {
		reset(panMat_Sub1,SHOW);
		
		if(is(debug_material,SHOW)) reset(debug_material,SHOW);
	}
}

void mat_select_smaragd() {
	mat_type = select_mat_smaragd;
	if(is(panMat_Sub1,SHOW)) {
		reset(panMat_Sub1,SHOW);
		
		if(is(debug_material,SHOW)) reset(debug_material,SHOW);
	}
}

void mat_select_marble() {
	mat_type = select_mat_marble;
	if(is(panMat_Sub1,SHOW)) {
		reset(panMat_Sub1,SHOW);
		
		if(is(debug_material,SHOW)) reset(debug_material,SHOW);
	}
}

void mat_select_4() {
	mat_type = select_mat_4;
	if(is(panMat_Sub1,SHOW)) {
		reset(panMat_Sub1,SHOW);
		
		if(is(debug_material,SHOW)) reset(debug_material,SHOW);
	}
}

void mat_select_5() {
	mat_type = select_mat_5;
	if(is(panMat_Sub1,SHOW)) {
		reset(panMat_Sub1,SHOW);
		
		if(is(debug_material,SHOW)) reset(debug_material,SHOW);
	}
}

void mat_select_6() {
	mat_type = select_mat_6;
	if(is(panMat_Sub1,SHOW)) {
		reset(panMat_Sub1,SHOW);
		
		if(is(debug_material,SHOW)) reset(debug_material,SHOW);
	}
}

void mat_select_7() {
	mat_type = select_mat_7;
	if(is(panMat_Sub1,SHOW)) {
		reset(panMat_Sub1,SHOW);
		
		if(is(debug_material,SHOW)) reset(debug_material,SHOW);
	}
}

void mat_select_8() {
	mat_type = select_mat_8;
	if(is(panMat_Sub1,SHOW)) {
		reset(panMat_Sub1,SHOW);
		
		if(is(debug_material,SHOW)) reset(debug_material,SHOW);
	}
}

void mat_select_9() {
	mat_type = select_mat_9;
	if(is(panMat_Sub1,SHOW)) {
		reset(panMat_Sub1,SHOW);
		
		if(is(debug_material,SHOW)) reset(debug_material,SHOW);
	}
}

void mat_select_10() {
	mat_type = select_mat_10;
	if(is(panMat_Sub1,SHOW)) {
		reset(panMat_Sub1,SHOW);
		
		if(is(debug_material,SHOW)) reset(debug_material,SHOW);
	}
}

////////////////////////////////////////////////////////////
// These materials are customizable. You know what to do.
// Only customizable materials' properties is passed through
// pass_mat_to_matsub(MATERIAL *).
////////////////////////////////////////////////////////////
void mat_select_11() {
	mat_type = select_custom_mat1;
	
	/*
	a quick terrible ugly hack
	normally panMat_Sub1 will only be updated
	if you click on "Edit Material",
	but this hack allows you to update panMat_Sub1 directly
	without pressing that button.
	
	this can be useful if you've already opened panMat_Sub1
	and select another customizable material, the panel
	will be updated immediately without having to click
	the "Edit Material" button again.
	*/
	if(is(panMat_Sub1,SHOW))
	pass_mat_to_matsub(mat_custom[0]);
}

void mat_select_12() {
	mat_type = select_custom_mat2;
	
	if(is(panMat_Sub1,SHOW))
	pass_mat_to_matsub(mat_custom[1]);
}

void mat_select_13() {
	mat_type = select_custom_mat3;
	
	if(is(panMat_Sub1,SHOW))
	pass_mat_to_matsub(mat_custom[2]);
}

void mat_select_14() {
	mat_type = select_custom_mat4;
	
	if(is(panMat_Sub1,SHOW))
	pass_mat_to_matsub(mat_custom[3]);
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
			error("mat_type exceeded/wrong.");
			break; 
			
		}
		
	}
	
}

void pass_object_to_clipboard(ENTITY *o, obj_form *of) {
	of._scale_x = o.scale_x;
	of._scale_y = o.scale_y;
	of._scale_z = o.scale_z;
	
	of._pan = o.pan;
	of._tilt = o.tilt;
	of._roll = o.roll;
	
	of._alpha = o.alpha;
	of._ambient = o.ambient;
	
	if(is(o,BRIGHT)) of._flags[0] = ON;
	else of._flags[0] = OFF;
	
	if(is(o,INVISIBLE)) of._flags[1] = ON;
	else of._flags[1] = OFF;
	
	if(is(o,NOFOG)) of._flags[2] = ON;
	else of._flags[2] = OFF;
	
	if(is(o,OVERLAY)) of._flags[3] = ON;
	else of._flags[3] = OFF;
	
	if(is(o,PASSABLE)) of._flags[4] = ON;
	else of._flags[4] = OFF;
	
	if(is(o,POLYGON)) of._flags[5] = ON;
	else of._flags[5] = OFF;
	
	if(is(o,SHADOW)) of._flags[6] = ON;
	else of._flags[6] = OFF;
	
	if(is(o,TRANSLUCENT)) of._flags[7] = ON;
	else of._flags[7] = OFF;
	
	of.oid = o.skill1;
	of.dp = 1;
}

void pass_clipboard_to_object(ENTITY *e) {
	e.material = clipboard.m;
	e.skill1 = clipboard.oid;
	
	e.ambient = clipboard._ambient;
	e.alpha = clipboard._alpha;
	
	e.scale_x = clipboard._scale_x;
	e.scale_y = clipboard._scale_y;
	e.scale_z = clipboard._scale_z;
	
	e.pan = clipboard._pan;
	e.tilt = clipboard._tilt;
	e.roll = clipboard._roll;
	
	if(clipboard._flags[0] == ON) set(e,BRIGHT);
	else reset(e,BRIGHT);
	
	if(clipboard._flags[1] == ON) set(e,INVISIBLE);
	else reset(e,INVISIBLE);
	
	if(clipboard._flags[2] == ON) set(e,NOFOG);
	else reset(e,NOFOG);
	
	if(clipboard._flags[3] == ON) set(e,OVERLAY);
	else reset(e,OVERLAY);
	
	if(clipboard._flags[4] == ON) set(e,PASSABLE);
	else reset(e,PASSABLE);
	
	if(clipboard._flags[5] == ON) set(e,POLYGON);
	else reset(e,POLYGON);
	
	if(clipboard._flags[6] == ON) set(e,SHADOW);
	else reset(e,SHADOW);
	
	if(clipboard._flags[7] == ON) set(e,TRANSLUCENT);
	else reset(e,TRANSLUCENT);
	
}

void obj_cut() {
	
	if(select) {
		
		pass_object_to_clipboard(select,clipboard);
		
		// Perform manual access to clipboard to copy material
		
		/*
		select is selected.
		so something must have been copied into mat_temp.
		so I directly take mat_temp and copy it into the clipboard.
		
		otherwise if we pass select.material to clipboard.m,
		mat_select is passed but not select's material.
		*/
		clipboard.m = mat_temp;
		
		ptr_remove(select);
		select = NULL;
	}
	
}

void obj_copy() {
	
	if(select) {
		
		pass_object_to_clipboard(select,clipboard);
		
		// Perform manual access to clipboard to copy material
		clipboard.m = mat_temp;
	}
	
}

void obj_paste() {
	
	if(clipboard.dp) {
		
		// Extract the ID from clipboard.
		obj_type = clipboard.oid;
		
		// The outcome of obj_create is an ENTITY * so
		// pass_clipboard_to_object will be able to pass its 
		// properties (that was saved before to the clipboard)
		// back to the newly created object.
		pass_clipboard_to_object(obj_create());
		
	}
	
}

// Read material properties from a file and pass it to a
// previously-defined material.
void pass_file_to_material(MATERIAL *m, STRING *file) {
	while(m == NULL) wait(1); // wait for m to be completely created
	
	var vpass = file_open_read(file);
	if(vpass == 0) return;
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
	if(vpass == 0) return;
	
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
		pass_material_to_file("mat_custom_1.cfg",mat_custom[0]);
		
		break;
		//////////////////////////////////////////////////////////////
		
		case select_custom_mat2 :
		pass_material_to_file("mat_custom_2.cfg",mat_custom[1]);
		
		break;
		//////////////////////////////////////////////////////////////
		
		case select_custom_mat3 :
		pass_material_to_file("mat_custom_3.cfg",mat_custom[2]);
		
		break;
		//////////////////////////////////////////////////////////////
		
		case select_custom_mat4 :
		pass_material_to_file("mat_custom_4.cfg",mat_custom[3]);
		
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
	while(mouse_left)
	{
		if(manip_type == scale) 
		{
			
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
			
			my.pan = mouse_pos.x;
			my.tilt = mouse_pos.y;
			
		}

		wait (1);
	}
	
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
	
	// Check its state first.
	if(button_state(panMain_Top,1,-1) == ON) {
		
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
	
	if(button_state(panMain_Top,2,-1) == ON) {
		
		button_state(panMain_Top,1,0);
		button_state(panMain_Top,3,0);
		
		manip_type = rotate;
		
	}

	else manip_type = scale+1;
}

void switch_to_scale() {
	
	if(button_state(panMain_Top,3,-1) == ON) {
		
		button_state(panMain_Top,1,0);
		button_state(panMain_Top,2,0);
		
		manip_type = scale;
		
	}
	
	else manip_type = scale+1;
	
}

////////////////////////////////////////////////////////////
// Initialization before the game can be launched.
////////////////////////////////////////////////////////////
void init_startup() {
	
	// So that we can get access to the database.
	sTable_ptr = sTable;
	
	panHome.alpha = panMat.alpha = panPhy.alpha = panProp.alpha = DEFAULT_ALPHA;
	
	// Initialize the object database and load them.
	init_database();
	
	// Intialize and read custom materials' properties.
	int i;
	for(i = 0;i < 4;i++) mat_custom[i] = mtl_create();
	
	pass_file_to_material(mat_custom[0],"./shared/mat_custom_1.cfg");
	pass_file_to_material(mat_custom[1],"./shared/mat_custom_2.cfg");
	pass_file_to_material(mat_custom[2],"./shared/mat_custom_3.cfg");
	pass_file_to_material(mat_custom[3],"./shared/mat_custom_4.cfg");
	
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
				sharedGUI_prop();
				
			}
			
			if(key_m) {
				
				while(key_m) wait(1);
				sharedGUI_mat();
				
			}
			
			if(key_h) {
				
				while(key_h) wait(1);
				sharedGUI_phy();
				
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
				error(" I don't want to die =(( ");
				
				sys_exit(NULL);
				
			}
			
		}
		
		// These keys are pressed solely.
		
		// I seperately defined key_esc here
		// so I must disable the one that has been defined 
		// in ka7def2.c/default.c
		if(key_esc) {
			
			while(key_esc) wait(1);
			sharedGUI_home();
			
		}
		
		wait(1);
	}
	// End of shortcut keys implementation.
	
}

//////////////////////////////
// Debug & statistics
//////////////////////////////
PANEL *debug = {
	layer = 3;
	
	digits(0,0,99,"arial#25b",1,obj_type);
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