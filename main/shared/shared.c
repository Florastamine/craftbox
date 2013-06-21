
/*

[ shared.c ]

*/

//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
#define anim 16
#define total_ents 1450

///////////////////////////////////////////////////////////
// This struct is applied only to level entities.
////////////////////////////////////////////////////////////
typedef struct obj_form {
	
	STRING *filename;
	int oid; // Object ID
	
	// A pointer that points to the entity in the current obj_form object
	ENTITY *obj;
	
	var _x, _y, _z, // Do not store these vars if this is passed to the clipboard.
	_scale_x, _scale_y, _scale_z,
	_pan, _tilt, _roll,
	_alpha, _ambient;
	
	BOOL pPhysics, pStatic, _flags[8];
	
	// Some vars define its physical properties
	var mass, friction;
	
	MATERIAL *m;
	
	BOOL dp;
	
	// Animations
	
	// For humans
	
	// Normal animations
	STRING
	*anim_idle [anim],
	*anim_walk [anim],
	*anim_run [anim],
	*anim_crouch [anim],
	*anim_jump [anim],
	*anim_swim [anim],
	*anim_shoot [anim],
	*anim_die [anim],
	
	// Plus five custom animations
	*anim_custom1[anim],
	*anim_custom2[anim],
	*anim_custom3[anim],
	*anim_custom4[anim],
	
	// For objects
	
	// Three custom animations
	*anim_obj_custom1 [anim],
	*anim_obj_custom2 [anim],
	*anim_obj_custom3 [anim];
	
} obj_form;

////////////////////////////////////////////////////////////
// x Animals : 200 (1 - 200)
// x Architecture : 100 (201 - 300)
// x Characters : 100 (301 - 400)
// x Everyday objects : 500 (401 - 900)
// x Food : 150 (901 - 1050)
// Land : 50 (1051 - 1100)
// Machines : 50 (1101 - 1150)
// Plants : 200 (1151 - 1350)
// Transportations : 100 (1351 - total_ents)
// ...
////////////////////////////////////////////////////////////

// Database
TEXT *strTable = {
	
	string (
	
	// Animals [1-200]
	
	// Allocated space
	"a_badger.mdl",
	"a_bat.mdl",
	"a_bluebird.mdl",
	"a_boar.mdl",
	"a_bug.mdl",
	"a_burkel.mdl",
	"a_butterfly.mdl",
	"a_crow.mdl",
	"a_fish1.mdl",
	"a_fish2.mdl",
	"a_fish3.mdl",
	"a_fish4.mdl",
	"a_fish5.mdl",
	"a_fish6.mdl",
	"a_fish7.mdl",
	"a_fish8.mdl",
	"a_rat.mdl",
	"a_snake.mdl",
	
	// Unallocated space (20 per line)
	"","",
	"","","","","","","","","","","","","","","","","","","","",
	"","","","","","","","","","","","","","","","","","","","",
	"","","","","","","","","","","","","","","","","","","","",
	"","","","","","","","","","","","","","","","","","","","",
	"","","","","","","","","","","","","","","","","","","","",
	"","","","","","","","","","","","","","","","","","","","",
	"","","","","","","","","","","","","","","","","","","","",
	"","","","","","","","","","","","","","","","","","","","",
	"","","","","","","","","","","","","","","","","","","",""
	
	// Architecture [201-300]
	// Allocated space
	"a_building.wmb",
	"a_building1.mdl",
	"a_church.mdl",
	"a_fence.mdl",
	"a_fence_cylinder.mdl",
	"a_gate.mdl",
	"a_house1.mdl",
	"a_house2.mdl",
	"a_house3.mdl",
	"a_hut.mdl",
	"a_temple_entrance.mdl",
	"a_warehouse.mdl",
	"a_warehouse1.mdl",
	"a_warehouse2.mdl",
	"a_warehouse3.mdl",
	"a_warehouse4.mdl",
	"a__frame.mdl",
	
	// Unallocated space
	"","","","","","","","","","","","","","","","","","","","",
	"","","","","","","","","","","","","","","","","","","","",
	"","","","","","","","","","","","","","","","","","","","",
	"","","","","","","","","","","","","","","","","","","","",
	"","","",
	
	// Characters [301-400]
	// Allocated space
	"c_badguy.mdl",
	"c_berzerka.mdl",
	"c_cgirl.mdl",
	"c_guard.mdl",
	"c_HCS_Warrior_C.mdl",
	"c_inmate.mdl",
	"c_ninja.mdl",
	"c_p_king_ochan.mdl",
	"c_p_lobster_mutant.mdl",
	"c_p_mario_h.mdl",
	"c_p_pirate.mdl",
	"c_p_r2_robot.mdl",
	"c_p_saucer.mdl",
	"c_p_skel.mdl",
	"c_rabbit.mdl",
	"c_soldier.mdl",
	"c_trooper.mdl",
	"c_warlock.mdl",
	"c_witch.mdl",
	"c__007.mdl",
	
	// Unallocated space
	"","","","","","","","","","","","","","","","","","","","",
	"","","","","","","","","","","","","","","","","","","","",
	"","","","","","","","","","","","","","","","","","","","",
	"","","","","","","","","","","","","","","","","","","","",
	
	// Everyday objects [401-900]
	// Allocated space
	"e_ball1.mdl",
	"e_ball10.mdl",
	"e_ball11.mdl",
	"e_ball12.mdl",
	"e_ball13.mdl",
	"e_ball14.mdl",
	"e_ball15.mdl",
	"e_ball2.mdl",
	"e_ball3.mdl",
	"e_ball4.mdl",
	"e_ball5.mdl",
	"e_ball6.mdl",
	"e_ball7.mdl",
	"e_ball8.mdl",
	"e_ball9.mdl",
	"e_balloon.mdl",
	"e_ball_white.mdl",
	"e_barrel.mdl",
	"e_barrel01.mdl",
	"e_barrel02.mdl",
	"e_barrel03.mdl",
	"e_barrel04.mdl",
	"e_barrel05.mdl",
	"e_barrel06.mdl",
	"e_barrel07.mdl",
	"e_barrel08.mdl",
	"e_barrel9.mdl",
	"e_barrier.mdl",
	"e_basketballbasket.mdl",
	"e_battery.mdl",
	"e_bench.mdl",
	"e_bench1.mdl",
	"e_bench2.mdl",
	"e_bench3.mdl",
	"e_bench4.mdl",
	"e_bench5.mdl",
	"e_bench6.mdl",
	"e_bench7.mdl",
	"e_bench8.mdl",
	"e_billard1.mdl",
	"e_billardlamp.mdl",
	"e_billiard.mdl",
	"e_billiard2.mdl",
	"e_billiard3.mdl",
	"e_billiard_queue.mdl",
	"e_book1.mdl",
	"e_books.mdl",
	"e_books2.mdl",
	"e_books3.mdl",
	"e_bookshelf.mdl",
	"e_box.mdl",
	"e_box1.mdl",
	"e_cabinet.mdl",
	"e_cabinet_corner.mdl",
	"e_cd.mdl",
	"e_cement_bag.mdl",
	"e_chair.mdl",
	"e_chair1.mdl",
	"e_chair2.mdl",
	"e_ciga.mdl",
	"e_clock.mdl",
	"e_cloud.mdl",
	"e_coin.mdl",
	"e_colamach.mdl",
	"e_crate.mdl",
	"e_crate1.mdl",
	"e_crate2.mdl",
	"e_crystal.mdl",
	"e_door.mdl",
	"e_door1.mdl",
	"e_door2.mdl",
	"e_door3.mdl",
	"e_door4.mdl",
	"e_dumpster.mdl",
	"e_d_booth_01.mdl",
	"e_extinguisher.mdl",
	"e_extinguisher1.mdl",
	"e_fence.mdl",
	"e_fire.mdl",
	"e_flag.mdl",
	"e_fridge.mdl",
	"e_frying_pan.mdl",
	"e_gift_box.mdl",
	"e_hydrant.mdl",
	"e_iPod.mdl",
	"e_lamp1.mdl",
	"e_lamp2.mdl",
	"e_lamp3.mdl",
	"e_lamp4.mdl",
	"e_leon_armoire.mdl",
	"e_leon_desk.mdl",
	"e_light.mdl",
	"e_mirror.mdl",
	"e_mirror1.mdl",
	"e_palette.mdl",
	"e_palette1.mdl",
	"e_parkingmeter.mdl",
	"e_piano.mdl",
	"e_picture.mdl",
	"e_picture1.mdl",
	"e_picture2.mdl",
	"e_picture3.mdl",
	"e_picture4.mdl",
	"e_picture5.mdl",
	"e_picture6.mdl",
	"e_picture7.mdl",
	"e_picture8.mdl",
	"e_pipe.mdl",
	"e_pipe1.mdl",
	"e_pipe2.mdl",
	"e_platform.mdl",
	"e_railway_45left.mdl",
	"e_railway_45right.mdl",
	"e_railway_doubleswitch.mdl",
	"e_railway_down.mdl",
	"e_railway_end.mdl",
	"e_railway_singleswitch.mdl",
	"e_railway_straight.mdl",
	"e_railway_up.mdl",
	"e_rail_lore1.mdl",
	"e_rope.mdl",
	"e_salonch.mdl",
	"e_salonch1.mdl",
	"e_sign_30.mdl",
	"e_sign_60.mdl",
	"e_sign_90.mdl",
	"e_sign_bicyclelane.mdl",
	"e_sign_boulder.mdl",
	"e_sign_bumpy-road.mdl",
	"e_sign_church.mdl",
	"e_sign_crosswinds.mdl",
	"e_sign_curve-ahead.mdl",
	"e_sign_endminimumspeed.mdl",
	"e_sign_exit.mdl",
	"e_sign_footpath.mdl",
	"e_sign_hospital.mdl",
	"e_sign_minimumspeed.mdl",
	"e_sign_noentry.mdl",
	"e_sign_noparking.mdl",
	"e_sign_nopassing.mdl",
	"e_sign_nostopping.mdl",
	"e_sign_novehicles.mdl",
	"e_sign_novisitor.mdl",
	"e_sign_oneside-road-narrow.mdl",
	"e_sign_parking.mdl",
	"e_sign_pedcrossing.mdl",
	"e_sign_pedestrian.mdl",
	"e_sign_phone.mdl",
	"e_sign_railroad.mdl",
	"e_sign_road-narrow.mdl",
	"e_sign_roundabout.mdl",
	"e_sign_slippery.mdl",
	"e_sign_traffic.mdl",
	"e_sign_trafficlights.mdl",
	"e_sign_turnscrossing.mdl",
	"e_sign_yield.mdl",
	"e_sofa.mdl",
	"e_strange_boar_toy.mdl",
	"e_strange_bowl.mdl",
	"e_strange_canvas.mdl",
	"e_strange_canvas2.mdl",
	"e_strange_crate.mdl",
	"e_strange_decorator.mdl",
	"e_strange_drums.mdl",
	"e_strange_flag.mdl",
	"e_strange_house.mdl",
	"e_strange_machine.mdl",
	"e_strange_placeholder.mdl",
	"e_strange_shelf.mdl",
	"e_strange_trough.mdl",
	"e_strange_umbrella.mdl",
	"e_strange_wine_barrel.mdl",
	"e_strange_wine_barrel2.mdl",
	"e_streetlight.mdl",
	"e_table.mdl",
	"e_table1.mdl",
	"e_table_blood.mdl",
	"e_target.mdl",
	"e_target1.mdl",
	"e_torch.mdl",
	"e_trashcan.mdl",
	"e_trashcan1.mdl",
	"e_trashcan2.mdl",
	"e_treasure_chest.mdl",
	"e_wheatpack.mdl",
	"e_woodchair.mdl",
	"e_woodchair2.mdl",
	
	// Unallocated space
	"","","","","","","","","","","","","","","","","","","","",
	"","","","","","","","","","","","","","","","","","","","",
	"","","","","","","","","","","","","","","","","","","","",
	"","","","","","","","","","","","","","","","","","","","",
	"","","","","","","","","","","","","","","","","","","","",
	"","","","","","","","","","","","","","","","","","","","",
	"","","","","","","","","","","","","","","","","","","","",
	"","","","","","","","","","","","","","","","","","","","",
	"","","","","","","","","","","","","","","","","","","","",
	"","","","","","","","","","","","","","","","","","","","",
	"","","","","","","","","","","","","","","","","","","","",
	"","","","","","","","","","","","","","","","","","","","",
	"","","","","","","","","","","","","","","","","","","","",
	"","","","","","","","","","","","","","","","","","","","",
	"","","","","","","","","","","","","","","","","","","","",
	"","","","","","","","","","","","","",
	
	// Food [901-1050]
	// Allocated space
	"f_apple_green.mdl",
	"f_apple_red.mdl",
	"f_bagel.mdl",
	"f_banana.mdl",
	"f_bread.mdl",
	"f_bread_loaf.mdl",
	"f_carrot.mdl",
	"f_cookie.mdl",
	"f_cookie1.mdl",
	"f_cookie2.mdl",
	"f_cookie3.mdl",
	"f_corn.mdl",
	"f_croissaint.mdl",
	"f_donut.mdl",
	"f_donut1.mdl",
	"f_foodsack.mdl",
	"f_genericf.mdl",
	"f_hamburger.mdl",
	"f_hotdog.mdl",
	"f_icecream.mdl",
	"f_nectarine.mdl",
	"f_orange.mdl",
	"f_pear.mdl",
	"f_pizza.mdl",
	"f_squash.mdl",
	"f_steak.mdl",
	"f_tomato.mdl",
	"f_watermelon.mdl",
	"f_watermelon_piece.mdl",
	
	// Unallocated space
	"","","","","","","","","","","","","","","","","","","","",
	"","","","","","","","","","","","","","","","","","","","",
	"","","","","","","","","","","","","","","","","","","","",
	"","","","","","","","","","","","","","","","","","","","",
	"","","","","","","","","","","","","","","","","","","","",
	"","","","","","","","","","","","","","","","","","","","",
	"",

	// Land [1051-1100]
	// Allocated space
	"l_desertgeneric.hmp",
	"l_greenland.hmp",
	"l_greenland1.hmp",
	"l_greenland_fat.hmp",
	"l_marssurface.hmp",
	"l_ocean1.hmp",
	"l_ocean2.hmp",
	"l_steppegeneric.hmp",
	"l_stonegeneric.hmp",
	"l_water1.hmp",
	"l_water2.hmp",
	
	// Unallocated space
	"","","","","","","","","","","","","","","","","","","","",
	"","","","","","","","","","","","","","","","","","","",
	
	// Machines [1101-1150]
	// Allocated space
	"m_console.mdl",
	"m_generator.mdl",
	"m_generator1.mdl",
	"m_generator2.mdl",
	"m_hatch.mdl",
	"m_powerplant.mdl",
	"m_turret02.mdl",
	
	// Unallocated space
	"","","","","","","","","","","","","","","","","","","","",
	"","","","","","","","","","","","","","","","","","","","",
	"","","",
	
	// Plants [1151-1350]
	// Allocated space
	"bigtree2.mdl",
	"bstone1.mdl",
	"bstone2.mdl",
	"bush1.mdl",
	"bush3.mdl",
	"bush7.mdl",
	"d_14_lod0.mdl",
	"d_Fantasy_tree1.mdl"
	"d_flower_6.mdl",
	"d_litGr.mdl",
	"fern_1.mdl",
	"flower_1.mdl",
	"gpalm1.mdl",
	"grass.mdl",
	"grass1.mdl",
	"grass2.mdl",
	"grass3.mdl",
	"grass_scatt.mdl",
	"indoorplant.mdl",
	"kava_plant.mdl",
	"kaya2.mdl",
	"kaya3.mdl",
	"lightray1.mdl",
	"lp_birke_kr.mdl",
	"lp_birke_st.mdl",
	"lp_busch1.mdl",
	"lp_chunk1.mdl",
	"lp_farn.mdl",
	"lp_grass.mdl",
	"lp_Pine1_kr.mdl",
	"lp_Pine1_st.mdl",
	"lp_spruce_kr.mdl",
	"lp_spruce_st.mdl",
	"lp_stones.mdl",
	"lp_tree2_kr.mdl",
	"lp_tree2_st.mdl",
	"lp_tree_trck.mdl",
	"mdl_shr4.mdl",
	"mdl__agava1.mdl",
	"mdl__aloe1.mdl",
	"mdl__bamb1.mdl",
	"mdl__bamb2.mdl",
	"mdl__banan1.mdl",
	"mdl__banan2.mdl",
	"mdl__b_o_p.mdl",
	"mdl__croton.mdl",
	"mdl__fern1.mdl",
	"mdl__fern2.mdl",
	"mdl__fern3.mdl",
	"mdl__flax1g.mdl",
	"mdl__flax1r.mdl",
	"mdl__flow2.mdl",
	"mdl__flow3.mdl",
	"mdl__grass.mdl",
	"mdl__lpalm1.mdl",
	"mdl__lpalm2.mdl",
	"mdl__palms1.mdl",
	"mdl__palms2.mdl",
	"mdl__palms3.mdl",
	"mdl__palms4.mdl",
	"mdl__palms5.mdl",
	"mdl__palms6.mdl",
	"mdl__palmt1.mdl",
	"mdl__palmt2.mdl",
	"mdl__palmt3.mdl",
	"mdl__palmt4.mdl",
	"mdl__palmt5.mdl",
	"mdl__pinet1.mdl",
	"mdl__pinet2.mdl",
	"mdl__purple.mdl",
	"mdl__red.mdl",
	"mdl__shr15.mdl",
	"mdl__shr16.mdl",
	"mdl__shr17.mdl",
	"mdl__shr17h.mdl",
	"mdl__shr18.mdl",
	"mdl__shr18h.mdl",
	"mdl__shr19.mdl",
	"mdl__shr19h.mdl",
	"mdl__shr1h.mdl",
	"mdl__shr2.mdl",
	"mdl__shr3.mdl",
	"mdl__shr9.mdl",
	"mdl__tree1.mdl",
	"mdl__tree2.mdl",
	"mdl__tree3.mdl",
	"mdl__tree4.mdl",
	"mdl__tree5.mdl",
	"mdl__tree6.mdl",
	"mdl__trops1.mdl",
	"mdl__trops2.mdl",
	"mdl__tropw1.mdl",
	"mdl__tropw6.mdl",
	"mdl__tropw7.mdl",
	"mdl__weed1.mdl",
	"mdl__weed3.mdl",
	"mdl__weed4.mdl",
	"mdl__weed4a.mdl",
	"mdl__weed5.mdl",
	"mdl__weed6.mdl",
	"mdl__yuca.mdl",
	"mushroom1.mdl",
	"mushroom2.mdl",
	"mushroom3.mdl",
	"mushrooms1.mdl",
	"mushrooms2.mdl",
	"plant1.mdl",
	"platane.mdl",
	"rays1.mdl",
	"rays2.mdl",
	"shrub.mdl",
	"sstone1.mdl",
	"stone_fountain.mdl",
	"stone_ground_small.mdl",
	"t1.mdl",
	"t2.mdl",
	"t3.mdl",
	"t4.mdl",
	"t6.mdl",
	"t7.mdl",
	"tree1.mdl",
	"tree2.mdl",
	"tree4.mdl",
	"tree5.mdl",
	"Tree5_2.mdl",
	"tree_lo.mdl",
	"tree_log1.mdl",
	"waterfall.mdl",
	"weed1.mdl",
	"weed10.mdl",
	"weed11.mdl",
	"weed12.mdl",
	"weed13.mdl",
	"weed14.mdl",
	"weed15.mdl",
	"weed16.mdl",
	"weed17.mdl",
	"weed18.mdl",
	"weed2.mdl",
	"weed24.mdl",
	"weed3.mdl",
	"weed4.mdl",
	"weed5.mdl",
	"weed6.mdl",
	"weed7.mdl",
	"weed8.mdl",
	"weed9.mdl",
	"weedm.mdl",
	
	// Unallocated space
	"","","","","","","","","","","","","","","","","","","","",
	"","","","","","","","","","","","","","","","","","","","",
	"","","","","","","","","","","",
	
	// Transportations [1351-total_ents]
	// Allocated space
	"t_bomber.Mdl",
	"t_bomber1.mdl",
	"t_car1.mdl",
	"t_car2.mdl",
	"t_car3.mdl",
	"t_car4.mdl",
	"t_car_mr2.mdl",
	"t_f105_thug.Mdl",
	"t_f16.Mdl",
	"t_hover1.mdl",
	"t_lancaster.Mdl",
	"t_mcdf4_phantom.Mdl",
	"t_shopping.caddy.mdl",
	"t_tank.mdl",
	"t_tank1.mdl",
	"t_trainpart.mdl",
	"t_Viper.mdl",
	"t_wagon.mdl",
	
	// Unallocated space
	"","","","","","","","","","","","","","","","","","","","",
	"","","","","","","","","","","","","","","","","","","","",
	"","","","","","","","","","","","","","","","","","","","",
	"","","","","","","","","","","","","","","","","","","","",
	"",""
	
	);
}

/*
// Animals
#define a_badger 1
#define a_bat 2
#define a_bluebird 3
#define a_boar 4
#define a_bug 5
#define a_burkel 6
#define a_butterfly 7
#define a_crow 8
#define a_fish1 9
#define a_fish2 10
#define a_fish3 11
#define a_fish4 12
#define a_fish5 13
#define a_fish6 14
#define a_fish7 15
#define a_fish8 16
#define a_rat 17
#define a_snake 18
// --> 200

// Architecture
#define a_building 201
#define a_building1 202
#define a_church 203
#define a_fence 204
#define a_fence_cylinder 205
#define a_gate 206
#define a_house1 207
#define a_house2 208
#define a_house3 209
#define a_hut 210
#define a_temple_entrance 211
#define a_warehouse 212
#define a_warehouse1 213
#define a_warehouse2 214
#define a_warehouse3 215
#define a_warehouse4 216
#define a__frame 217
// --> 300

// Characters
#define c_badguy 301
#define c_berzerka 302
#define c_cgirl 303
#define c_guard 304
#define c_HCS_Warrior_C 305
#define c_inmate 306
#define c_ninja 307
#define c_p_king_ochan 308
#define c_p_lobster_mutant 309
#define c_p_mario_h 310
#define c_p_pirate 311
#define c_p_r2_robot 312
#define c_p_saucer 313
#define c_p_skel 314
#define c_rabbit 315
#define c_soldier 316
#define c_trooper 317
#define c_warlock 318
#define c_witch 319
#define c__007 320
// --> 400

// Everyday objects
#define e_ball1 401
#define e_ball10 402
#define e_ball11 403
#define e_ball12 404 // LOL
#define e_ball13 405
#define e_ball14 406
#define e_ball15 407
#define e_ball2 408
#define e_ball3 409
#define e_ball4 410
#define e_ball5 411
#define e_ball6 412
#define e_ball7 413
#define e_ball8 414
#define e_ball9 415
#define e_balloon 416
#define e_ball_white 417
#define e_barrel 418
#define e_barrel01 419
#define e_barrel02 420
#define e_barrel03 421
#define e_barrel04 422
#define e_barrel05 423
#define e_barrel06 424
#define e_barrel07 425
#define e_barrel08 426
#define e_barrel9 427
#define e_barrier 428
#define e_basketballbasket 429
#define e_battery 430
#define e_bench 431
#define e_bench1 432
#define e_bench2 433
#define e_bench3 434
#define e_bench4 435
#define e_bench5 436
#define e_bench6 437
#define e_bench7 438
#define e_bench8 439
#define e_billard1 440
#define e_billardlamp 441
#define e_billiard 442
#define e_billiard2 443
#define e_billiard3 444 // LOL 0.2
#define e_billiard_queue 445
#define e_book1 446
#define e_books 447
#define e_books2 448
#define e_books3 449
#define e_bookshelf 450
#define e_box 451
#define e_box1 452
#define e_cabinet 453
#define e_cabinet_corner 454
#define e_cd 455
#define e_cement_bag 456
#define e_chair 457
#define e_chair1 458
#define e_chair2 459
#define e_ciga 460
#define e_clock 461
#define e_cloud 462
#define e_coin 463
#define e_colamach 464
#define e_crate 465
#define e_crate1 466
#define e_crate2 467
#define e_crystal 468
#define e_door 469
#define e_door1 470
#define e_door2 471
#define e_door3 472
#define e_door4 473
#define e_dumpster 474
#define e_d_booth_01 475
#define e_extinguisher 476
#define e_extinguisher1 477
#define e_fence 478
#define e_fire 479
#define e_flag 480
#define e_fridge 481
#define e_frying_pan 482
#define e_gift_box 483
#define e_hydrant 484
#define e_iPod 485
#define e_lamp1 486 // LOL 0.3
#define e_lamp2 487
#define e_lamp3 488
#define e_lamp4 489
#define e_leon_armoire  490
#define e_leon_desk 491
#define e_light 492
#define e_mirror 493
#define e_mirror1 494
#define e_palette 495
#define e_palette1 496
#define e_parkingmeter 497
#define e_piano 498
#define e_picture 499
#define e_picture1 500
#define e_picture2 501
#define e_picture3 502
#define e_picture4 503
#define e_picture5 504
#define e_picture6 505
#define e_picture7 506
#define e_picture8 507
#define e_pipe 508
#define e_pipe1 509
#define e_pipe2 510
#define e_platform 511
#define e_railway_45left 512 // LOL 0.4
#define e_railway_45right 513
#define e_railway_doubleswitch 514
#define e_railway_down 515
#define e_railway_end 516
#define e_railway_singleswitch 517
#define e_railway_straight 518
#define e_railway_up 519
#define e_rail_lore1 520
#define e_rope 521
#define e_salonch 522
#define e_salonch1 523
#define e_sign_30 524
#define e_sign_60 525
#define e_sign_90 526
#define e_sign_bicyclelane 527
#define e_sign_boulder 528
#define e_sign_bumpy_road 529
#define e_sign_church 530
#define e_sign_crosswinds 531
#define e_sign_curve_ahead 532
#define e_sign_endminimumspeed 533
#define e_sign_exit 534
#define e_sign_footpath 535
#define e_sign_hospital 536
#define e_sign_minimumspeed 537
#define e_sign_noentry 538
#define e_sign_noparking 539
#define e_sign_nopassing 540
#define e_sign_nostopping 541
#define e_sign_novehicles 542
#define e_sign_novisitor 543
#define e_sign_oneside_road_narrow 544
#define e_sign_parking 545
#define e_sign_pedcrossing 546
#define e_sign_pedestrian 547
#define e_sign_phone 548
#define e_sign_road_narrow 550
#define e_sign_roundabout 551
#define e_sign_slippery 552
#define e_sign_traffic 553
#define e_sign_trafficlights 554
#define e_sign_turnscrossing 555
#define e_sign_yield 556
#define e_sofa 557
#define e_strange_boar_toy 558
#define e_strange_bowl 559
#define e_strange_canvas 560
#define e_strange_canvas2 561
#define e_strange_crate 562
#define e_strange_decorator 563
#define e_strange_drums 564
#define e_strange_flag 565
#define e_strange_house 566
#define e_strange_machine 567
#define e_strange_placeholder 568
#define e_strange_shelf 569
#define e_strange_trough 570
#define e_strange_umbrella 571
#define e_strange_wine_barrel 572
#define e_strange_wine_barrel2 573
#define e_streetlight 574
#define e_table 575
#define e_table1 576
#define e_table_blood 577
#define e_target 578
#define e_target1 579
#define e_torch 580
#define e_trashcan 581
#define e_trashcan1 582
#define e_trashcan2 583
#define e_treasure_chest 584
#define e_wheatpack 585
#define e_woodchair 586
#define e_woodchair2 587
// --> 900

// Food
#define f_apple_green 901
#define f_apple_red 902
#define f_bagel 903
#define f_banana 904
#define f_bread 905
#define f_bread_loaf 906
#define f_carrot 907
#define f_cookie 908
#define f_cookie1 909
#define f_cookie2 910
#define f_cookie3 911 // LOL 0.5
#define f_corn 912
#define f_croissaint 913
#define f_donut 914
#define f_donut1 915
#define f_foodsack 916
#define f_genericf 917
#define f_hamburger 918
#define f_hotdog 919
#define f_icecream 920
#define f_nectarine 921
#define f_orange 922
#define f_pear 923
#define f_pizza 924
#define f_squash 925
#define f_steak 926
#define f_tomato 927
#define f_watermelon 928
#define f_watermelon_piece 929
// --> 1050

// Land
#define l_desertgeneric 1051
#define l_greenland 1052
#define l_greenland1 1053
#define l_greenland_fat 1054
#define l_marssurface 1055
#define l_ocean1 1056
#define l_ocean2 1057
#define l_steppegeneric 1058
#define l_stonegeneric 1059
#define l_water1 1060
#define l_water2 1061
// --> 1100

// Machines
#define m_console 1101
#define m_generator 1102
#define m_generator1 1103
#define m_generator2 1104
#define m_hatch 1105
#define m_powerplant 1106
#define m_turret02 1107
// --> 1150

// Plants
#define bigtree2 1151
#define bstone1 1152
#define bstone2 1153
#define bush1 1154
#define bush3 1155
#define bush7 1156
#define d_14_lod0 1157
#define d_Fantasy_tree1 1158
#define d_flower_10 1159
#define d_flower_6 1160
#define d_litGr 1161
#define fern_1 1162
#define flower_1 1163
#define gpalm1 1164
#define grass 1165
#define grass1 1166
#define grass2 1167
#define grass3 1168
#define grass_scatt 1169
#define indoorplant 1170
#define kava_plant 1171
#define kaya2 1172
#define kaya3 1173
#define lightray1 1174
#define lp_birke_kr 1175
#define lp_birke_st 1176
#define lp_busch1 1177
#define lp_chunk1 1178
#define lp_farn 1179
#define lp_grass 1180
#define lp_Pine1_kr 1181
#define lp_Pine1_st 1182
#define lp_spruce_kr 1183
#define lp_spruce_st 1184
#define lp_stones 1185
#define lp_tree2_kr 1186
#define lp_tree2_st 1187
#define lp_tree_trck 1188
#define mdl_shr4 1189
#define mdl__agava1 1190
#define mdl__aloe1 1191
#define mdl__bamb1 1192
#define mdl__bamb2 1193
#define mdl__banan1 1194
#define mdl__banan2 1195
#define mdl__b_o_p 1196
#define mdl__croton 1197
#define mdl__fern1 1198
#define mdl__fern2 1199
#define mdl__fern3 1200
#define mdl__flax1g 1201
#define mdl__flax1r 1202
#define mdl__flow2 1203
#define mdl__flow3 1204
#define mdl__grass 1205
#define mdl__lpalm1 1206
#define mdl__lpalm2 1207
#define mdl__palms1 1208
#define mdl__palms2 1209
#define mdl__palms3 1210
#define mdl__palms4 1211
#define mdl__palms5 1212
#define mdl__palms6 1213
#define mdl__palmt1 1214
#define mdl__palmt2 1215
#define mdl__palmt3 1216
#define mdl__palmt4 1217
#define mdl__palmt5 1218
#define mdl__pinet1 1219
#define mdl__pinet2 1220
#define mdl__purple 1221
#define mdl__red 1222
#define mdl__shr15 1223
#define mdl__shr16 1224
#define mdl__shr17 1225
#define mdl__shr17h 1226
#define mdl__shr18 1227
#define mdl__shr18h 1228
#define mdl__shr19 1229
#define mdl__shr19h 1230
#define mdl__shr1h 1231
#define mdl__shr2 1232
#define mdl__shr3 1233
#define mdl__shr9 1234
#define mdl__tree1 1235
#define mdl__tree2 1236
#define mdl__tree3 1237
#define mdl__tree4 1238
#define mdl__tree5 1239
#define mdl__tree6 1240
#define mdl__trops1 1241
#define mdl__trops2 1242
#define mdl__tropw1 1243
#define mdl__tropw6 1244
#define mdl__tropw7 1245
#define mdl__weed1 1246
#define mdl__weed3 1247
#define mdl__weed4 1248
#define mdl__weed4a 1249
#define mdl__weed5 1250
#define mdl__weed6 1251
#define mdl__yuca 1252
#define mushroom1 1253
#define mushroom2 1254
#define mushroom3 1255
#define mushrooms1 1256
#define mushrooms2 1257
#define plant1 1258
#define platane 1259
#define rays1 1260
#define rays2 1261
#define shrub 1262
#define sstone1 1263
#define stone_fountain 1264
#define stone_ground_small 1265
#define t1 1266
#define t2 1267
#define t3 1268
#define t4 1269
#define t6 1270
#define t7 1271
#define tree1 1272
#define tree2 1273
#define tree4 1274
#define tree5 1275
#define Tree5_2 1276
#define tree_lo 1277
#define tree_log1 1278
#define waterfall 1279
#define weed1 1280 // LOOOOOOL
#define weed10 1281
#define weed11 1282
#define weed12 1283
#define weed13 1284
#define weed14 1285
#define weed15 1286
#define weed16 1287
#define weed17 1288
#define weed18 1289
#define weed2 1290
#define weed24 1291
#define weed3 1292
#define weed4 1293
#define weed5 1294
#define weed6 1295
#define weed7 1296
#define weed8 1297
#define weed9 1298
#define weedm 1299
// --> 1350
*/

////////////////////////////////////////////////////////////
// Functions declared for the obj_form struct.
////////////////////////////////////////////////////////////
void of_create(obj_form *);
void of_init(obj_form *, int, STRING *);
void of_kill(obj_form *);

obj_form clipboard;

////////////////////////////////////////////////////////////
// Defines the (large) object set.
////////////////////////////////////////////////////////////
obj_form 

// Animals
burkel, fish1, fish2, fish5, fish7, crow, bug, snake, rat,
bluebird, bat, butterfly, fish3, fish6, fish8, fish4, badger,
boar,

// Architectures
fence, fence_cylinder, temple_entrance, _frame, gate, warehouse,
chruch, hut, house1, building, warehouse1, warehouse2, warehouse3,
warehouse4, building1, house2, house3,

// Characters
p_skel, p_saucer, soldier, trooper, inmate, witch, berzerka,
p_r2_robot, guard, _007, cgirl, p_pirate, badguy, p_king_ochan,
p_lobster_mutant, warlock, rabbit, p_mario_h, ninja, HCS_Warrior_C,

// Machines
console, generator, generator1, generator2, hatch, powerplant, turret02,

// Base lands
desertgeneric, greenland, greenland1, greenland_fat, marssurface, ocean1,
ocean2, steppegeneric, stonegeneric, water1, water2,

// Food
apple_green, apple_red, bagel, banana,
bread,  bread_loaf,  carrot,  cookie,
cookie1,  cookie2,  cookie3,  corn, 
croissaint,  donut,  donut1,  foodsack, 
genericf,  hamburger,  hotdog,  icecream,
nectarine,  orange,  pear,  pizza,
squash,  steak,  steak,  tomato,  watermelon,
watermelon_piece,

// Everyday objects
ball1, ball10, ball11, ball12, ball13, ball14,
ball15, ball2, ball3, ball4, ball5, ball6, ball7,
ball8, ball9, balloon, ball_white, barrel, barrel01, barrel02,
barrel03, barrel04, barrel05, barrel06, barrel07, barrel08, barrel9,
barrier, basketballbasket, battery, bench, bench1, bench2, bench3,
bench4, bench5, bench6, bench7, bench8, billard1, billardlamp,
billiard, billiard2, billiard3, billiard_queue, book1, books, books2,
books3, bookshelf, box, box1, cabinet, cabinet_corner, cd,
cement_bag, chair, chair1, chair2, ciga, clock, cloud,
coin, colamach, crate, crate1, crate2, crystal, door,
door1, door2, door3, door4, dumpster, d_booth_01, extinguisher,
extinguisher1, fence, fire, flag, fridge, frying_pan, gift_box,
hydrant, iPod, lamp1, lamp2, lamp3, lamp4, leon_armoire,
leon_desk, light, mirror, mirror1, palette, palette1, parkingmeter,
piano, picture, picture1, picture2, picture3, picture4, picture5,
picture6, picture7, picture8, pipe, pipe1, pipe2,
platform, railway_45left, railway_45right, railway_doubleswitch, railway_down, railway_end, railway_singleswitch,
railway_straight, railway_up, rail_lore1, rope ,salonch, salonch1, sign_30,
sign_60, sign_90, sign_bicyclelane, sign_boulder, sign_bumpy_road, sign_church, sign_crosswinds,
sign_curvahead, sign_endminimumspeed, sign_exit, sign_footpath, sign_hospital, sign_minimumspeed, sign_noentry,
sign_noparking, sign_nopassing, sign_nostopping, sign_novehicles, sign_novisitor, sign_onesidroad_narrow, sign_parking,
sign_pedcrossing, sign_pedestrian, sign_phone, sign_railroad, sign_road_narrow, sign_roundabout, sign_slippery,
sign_traffic, sign_trafficlights, sign_turnscrossing, sign_yield, sofa, strangboar_toy, strangbowl,
strangcanvas, strangcanvas2, strangcrate, strangdecorator, strangdrums, strangflag, stranghouse,
strangmachine, strangplaceholder, strangshelf, strangtrough, strangumbrella, strangwinbarrel, strangwinbarrel2,
streetlight, table, table1, tablblood, _target, _target1, torch,
trashcan, trashcan1, trashcan2, treasurchest, wheatpack, woodchair, woodchair2,

// Plants
bigtree, bstone1, bstone2, bush1, bush3, bush7,
d_14_lod0, d_Fantasy_tree1, d_flower_10, d_flower_6, d_litGr, fern_1, flower_1,
gpalm1, grass, grass1, grass2, grass3, grass_scatt, indoorplant,
kava_plant, kaya2, kaya3, lightray1, lp_birke_kr, lp_birke_st, lp_busch1,
lp_chunk1, lp_farn, lp_grass, lp_Pine1_kr, lp_Pine1_st, lp_spruce_kr, lp_spruce_st,
lp_stones, lp_tree2_kr, lp_tree2_st, lp_tree_trck, mdl_shr4, mdl__agava1, mdl__aloe1,
mdl__bamb1, mdl__bamb2, mdl__banan1, mdl__banan2, mdl__b_o_p, mdl__croton, mdl__fern1,
mdl__fern2, mdl__fern3, mdl__flax1g, mdl__flax1r, mdl__flow2, mdl__flow3,mdl__grass,
mdl__lpalm1, mdl__lpalm2, mdl__palms1, mdl__palms2, mdl__palms3, mdl__palms4, mdl__palms5,
mdl__palms6, mdl__palmt1, mdl__palmt2, mdl__palmt3, mdl__palmt4, mdl__palmt5, mdl__pinet1,
mdl__pinet2, mdl__purple, mdl__red, mdl__shr15, mdl__shr16, mdl__shr17, mdl__shr17h,
mdl__shr18, mdl__shr18h, mdl__shr19, mdl__shr19h, mdl__shr1h, mdl__shr2, mdl__shr3,
mdl__shr9, mdl__tree1, mdl__tree2, mdl__tree3, mdl__tree4, mdl__tree5mdl__tree6,
mdl__trops1, mdl__trops2, mdl__tropw1, mdl__tropw6, mdl__tropw7, mdl__weed1,
mdl__weed3, mdl__weed4, mdl__weed4a, mdl__weed5, mdl__weed6, mdl__yuca, mushroom1,
mushroom2, mushroom3, mushrooms1, mushrooms2, plant1, platane, rays1,
rays2, shrub, sstone1, stone_fountain, stone_ground_small, t1, t2,
t3, t4, t6, t7, tree1, tree2, tree4,
tree5, Tree5_2, tree_lo, tree_log1, waterfall, weed1, weed10,
weed11, weed12, weed13, weed14, weed15, weed16, weed17,
weed18, weed2, weed24, weed3, weed4, weed5, weed6,
weed7, weed8, weed9, weedm,

// Transportations
bomber, bomber1, car1, car2, car3, car4,
car_mr2, f105_thug, f16, hover1, lancaster, mcdf4_phantom, shopping_caddy,
tank, tank1, trainpart, Viper, wagon;

//////////////////////////////////////////////////////////////
#define FADE_IN 1
#define FADE_OUT 0

#define ON 1
#define OFF 0

#define BUTTON_SIZE 32
#define BORDER 10
#define SPACE BUTTON_SIZE + BORDER

#define DEFAULT_ALPHA 50

#define move 1
#define rotate 2
#define scale 3

#define obj_winterbaum 0
#define obj_snowman 1
#define obj_genericwall 2
#define obj_palmtree 3
#define obj_generictree 4

#define select_mat_null 0
#define select_mat_lava 1
#define select_mat_smaragd 2
#define select_mat_marble 3
#define select_mat_4 4
#define select_mat_5 5
#define select_mat_6 6
#define select_mat_7 7
#define select_mat_8 8
#define select_mat_9 9
#define select_mat_10 10
#define select_custom_mat1 11
#define select_custom_mat2 12
#define select_custom_mat3 13
#define select_custom_mat4 14

//////////////////////////////
// Strings and texts will be declared here.
//////////////////////////////
STRING *o_winterbaum = "winterbaum.mdl",
*o_snowman = "snowman.mdl",
*o_genericwall = "wall1.mdl",
*o_palmtree = "palmtree.mdl",
*o_generictree = "tree1.mdl";

STRING *current_folder = "a",
*file_selected = "a";

TEXT *files_list;

////////////////////////////////////////////////////////////
// Variables will be declared here.
////////////////////////////////////////////////////////////
int obj_type, mat_type, manip_type;

int files_found, list_start;
int is_camera;

var files_already;

var v_alpha, v_ambient,
v_ambient_r, v_ambient_g, v_ambient_b,
v_diffuse_r, v_diffuse_g, v_diffuse_b,
v_specular_r, v_specular_g, v_specular_b,
v_emissive_r, v_emissive_g, v_emissive_b,
v_power, 
v_alpha_m; // Alpha for materials

var button_SaveWorld_y,
button_LoadWorld_y,
button_NewWorld_y,
button_QuitWorld_y,
button_CmpWorld_y,
button_SetWorld_y;

////////////////////////////////////////////////////////////
// Panels will be declared here.
////////////////////////////////////////////////////////////
PANEL *last_pan;

PANEL *buttonlst,
*panMain_Top,
*panMain_Bottom,
*panMain_Play,
*buttonlst_submenu_terrain,
*buttonlst_submenu_object,
*buttonlst_submenu_path,
*panHome,
*panProp,
*panPhy,
*panMat,
*panMat_Sub1,
*_logo,
*blackscreen,
*debug,
*debug_material;

////////////////////////////////////////////////////////////
// Entities will be declared here.
////////////////////////////////////////////////////////////
ENTITY *select, *fpsf_marker;

////////////////////////////////////////////////////////////
// Vectors will be declared here.
////////////////////////////////////////////////////////////
VECTOR sharedGUI_cpos1,sharedGUI_cpos2,temp_pos;

// Vectors for dragging entities
VECTOR v1, v2;

////////////////////////////////////////////////////////////
// Fonts and texts' declarations
////////////////////////////////////////////////////////////
FONT *f = "Arial#25b";

////////////////////////////////////////////////////////////
// Material declarations
////////////////////////////////////////////////////////////
MATERIAL *mat_select, *mat_temp;

// Predefined materials
MATERIAL *mat_lava, *mat_smaragd, *mat_marble;

// Custom materials
MATERIAL *mat_custom[4];

////////////////////////////////////////////////////////////
// Bitmap declarations
////////////////////////////////////////////////////////////
BMAP* mouse = "arrow.pcx";

BMAP *button_Play = "button_play.bmp";
BMAP *button_Play_over = "button_play_over.bmp";
BMAP *button_play_off = "button_play_off.bmp";

//BMAP *button_Copy = "button_Copy.bmp";
//BMAP *button_Copy_Over = "button_Copy_over.bmp";
//BMAP *button_Copy_Off = "button_Copy_off.bmp";
//
//BMAP *button_Paste = "button_Paste.bmp";
//BMAP *button_Paste_Over = "button_Paste_over.bmp";
//BMAP *button_Paste_off = "button_Paste_off.bmp";
//
//BMAP *button_Cut = "button_Cut.bmp";
//BMAP *button_Cut_Over = "button_Cut_over.bmp";
//BMAP *button_Cut_Off = "button_Cut_off.bmp";

BMAP *button_Move = "button_Move.bmp";
BMAP *button_Move_Over = "button_Move_over.bmp";
BMAP *button_Move_Off = "button_Move_off.bmp";

BMAP *button_Rotate = "button_Rotate.bmp";
BMAP *button_Rotate_Over = "button_Rotate_over.bmp";
BMAP *button_Rotate_Off = "button_Rotate_off.bmp";

BMAP *button_Scale = "button_Scale.bmp";
BMAP *button_Scale_Over = "button_Scale_over.bmp";
BMAP *button_Scale_Off = "button_Scale_off.bmp";

BMAP *button_Prop = "button_Prop.bmp";
BMAP *button_Prop_Over = "button_Prop_over.bmp";
BMAP *button_Prop_Off = "button_Prop_off.bmp";

BMAP *button_Phy = "button_Phy.bmp";
BMAP *button_Phy_Over = "button_Phy_over.bmp";
BMAP *button_Phy_Off = "button_Phy_off.bmp";

BMAP *button_Mat = "button_Mat.bmp";
BMAP *button_Mat_Over = "button_Mat_over.bmp";
BMAP *button_Mat_Off = "button_Mat_off.bmp";

BMAP *button_Home = "button_Home_on.bmp";
BMAP *button_Home_Over = "button_Home_over.bmp";
BMAP *button_Home_Off = "button_Home_off.bmp";

BMAP *button_Cam = "button_Camera_on.bmp";
BMAP *button_Cam_Over = "button_Camera_over.bmp";
BMAP *button_Cam_Off = "button_Camera_off.bmp";

BMAP *button_Terrain = "button_Terrain_on.bmp";
BMAP *button_Terrain_Over = "button_Terrain_over.bmp";
BMAP *button_Terrain_Off = "button_Terrain_off.bmp";

BMAP *button_Objs = "button_Object_on.bmp";
BMAP *button_Objs_Over = "button_Object_over.bmp";
BMAP *button_Objs_Off = "button_Object_off.bmp";

BMAP *button_Path = "button_Path_on.bmp";
BMAP *button_Path_Over = "button_Path_over.bmp";
BMAP *button_Path_Off = "button_Path_off.bmp";

BMAP *button_Close = "button_Close.bmp";
BMAP *button_Close_off = "button_Close_off.bmp";
BMAP *button_Close_over = "button_Close_over.bmp";

BMAP *button_Home_newworld = "button_Home_newworld.bmp";
BMAP *button_Home_newworld_off = "button_Home_newworld_off.bmp";
BMAP *button_Home_newworld_over = "button_Home_newworld_over.bmp";

BMAP *button_Home_loadworld = "button_Home_loadworld.bmp";
BMAP *button_Home_loadworld_off = "button_Home_loadworld_off.bmp";
BMAP *button_Home_loadworld_over = "button_Home_loadworld_over.bmp";

BMAP *button_Home_saveworld = "button_Home_saveworld.bmp";
BMAP *button_Home_saveworld_off = "button_Home_saveworld_off.bmp";
BMAP *button_Home_saveworld_over = "button_Home_saveworld_over.bmp";

BMAP *button_Home_compileworld = "button_Home_compileworld.bmp";
BMAP *button_Home_compileworld_off = "button_Home_compileworld_off.bmp";
BMAP *button_Home_compileworld_over = "button_Home_compileworld_over.bmp";

BMAP *button_Home_configworld = "button_Home_configworld.bmp";
BMAP *button_Home_configworld_off = "button_Home_configworld_off.bmp";
BMAP *button_Home_configworld_over = "button_Home_configworld_over.bmp";

BMAP *button_Home_quitworld = "button_Home_quitworld.bmp";
BMAP *button_Home_quitworld_off = "button_Home_quitworld_off.bmp";
BMAP *button_Home_quitworld_over = "button_Home_quitworld_over.bmp";

BMAP *flag_BIRGHT = "flag_BIRGHT.bmp";
BMAP *flag_BIRGHT_on = "flag_BIRGHT_on.bmp";

BMAP *flag_INVISIBLE = "flag_INVISIBLE.bmp";
BMAP *flag_INVISIBLE_on = "flag_INVISIBLE_on.bmp";

BMAP *flag_NOFOG = "flag_NOFOG.bmp";
BMAP *flag_NOFOG_on = "flag_NOFOG_on.bmp";

BMAP *flag_OVERLAY = "flag_OVERLAY.bmp";
BMAP *flag_OVERLAY_on = "flag_OVERLAY_on.bmp";

BMAP *flag_PASSABLE = "flag_PASSABLE.bmp";
BMAP *flag_PASSABLE_on = "flag_PASSABLE_on.bmp";

BMAP *flag_POLYGON = "flag_POLYGON.bmp";
BMAP *flag_POLYGON_on = "flag_POLYGON_on.bmp";

BMAP *flag_SHADOW = "flag_SHADOW.bmp";
BMAP *flag_SHADOW_on = "flag_SHADOW_on.bmp";

BMAP *flag_TRANSLUCENT = "flag_TRANSLUCENT.bmp";
BMAP *flag_TRANSLUCENT_on = "flag_TRANSLUCENT_on.bmp";

BMAP *flag_PHY = "flag_PHY.bmp";
BMAP *flag_PHY_on = "flag_PHY_on.bmp";

BMAP *slider = "slider.tga";

BMAP *button_Mat1 = "button_Mat1.bmp";
BMAP *button_Mat2 = "button_Mat2.bmp";
BMAP *button_Mat3 = "button_Mat3.bmp";
BMAP *button_Mat4 = "button_Mat4.bmp";
BMAP *button_Mat5 = "button_Mat5.bmp";
BMAP *button_Mat6 = "button_Mat6.bmp";
BMAP *button_Mat7 = "button_Mat7.bmp";
BMAP *button_Mat8 = "button_Mat8.bmp";
BMAP *button_Mat9 = "button_Mat9.bmp";
BMAP *button_Mat10 = "button_Mat10.bmp";
BMAP *button_Mat11 = "button_Mat11.bmp";
BMAP *button_Mat12 = "button_Mat12.bmp";
BMAP *button_Mat13 = "button_Mat13.bmp";
BMAP *button_Mat14 = "button_Mat14.bmp";
BMAP *button_Mat15 = "button_Mat15.bmp";

BMAP *menu1_submenu1 = "button_loadfrom.bmp";
BMAP *menu1_submenu1_off = "button_loadfrom_off.bmp";
BMAP *menu1_submenu1_over = "button_loadfrom_over.bmp";

BMAP *menu1_submenu2 = "button_saveto.bmp";
BMAP *menu1_submenu2_off = "button_saveto_off.bmp";
BMAP *menu1_submenu2_over = "button_saveto_over.bmp";

BMAP *menu1_submenu3 = "button_brusht.bmp";
BMAP *menu1_submenu3_off = "button_brusht_off.bmp";
BMAP *menu1_submenu3_over = "button_brusht_over.bmp";

BMAP *menu1_submenu4 = "button_deformt.bmp";
BMAP *menu1_submenu4_off = "button_deformt_off.bmp";
BMAP *menu1_submenu4_over = "button_deformt_over.bmp";

BMAP *menu2_submenu1 = "button_addobject.bmp";
BMAP *menu2_submenu1_off = "button_addobject_off.bmp";
BMAP *menu2_submenu1_over = "button_addobject_over.bmp";

BMAP *menu2_submenu2 = "button_addevent.bmp";
BMAP *menu2_submenu2_off = "button_addevent_off.bmp";
BMAP *menu2_submenu2_over = "button_addevent_over.bmp";

//BMAP *menu2_submenu3 = "button_submenu2_3.bmp";
//BMAP *menu2_submenu4 = "button_submenu2_4.bmp";

BMAP *menu3_submenu1 = "button_addnode.bmp";
BMAP *menu3_submenu1_off = "button_addnode_off.bmp";
BMAP *menu3_submenu1_over = "button_addnode_over.bmp";

BMAP *menu3_submenu2 = "button_nodetype.bmp";
BMAP *menu3_submenu2_off = "button_nodetype_off.bmp";
BMAP *menu3_submenu2_over = "button_nodetype_over.bmp";

//BMAP *menu3_submenu3 = "button_submenu3_3.bmp";
//BMAP *menu3_submenu4 = "button_submenu3_4.bmp";

BMAP *button_back = "button_back.bmp";
BMAP *button_back_over = "button_back_over.bmp";

BMAP *button_default = "button_default.bmp";
BMAP *button_default_off = "button_default_off.bmp";
BMAP *button_default_over = "button_default_over.bmp";

BMAP *button_editmat = "button_editmat.bmp";
BMAP *button_editmat_def = "button_editmat_default.bmp";
BMAP *button_editmat_save = "button_editmat_savechanges.bmp";

BMAP *button_matapply = "button_matapply.bmp";
BMAP *button_matapply_off = "button_matapply_off.bmp";
BMAP *button_matapply_over = "button_matapply_over.bmp";

////////////////////////////////////////////////////////////
// Function prototypes declarations
////////////////////////////////////////////////////////////
/**/void sharedGUI_rescale(PANEL *);
/**/void sharedGUI_release(STRING *);
/**/void sharedGUI_playintro(STRING *, var);
/**/void sharedGUI_blackscreen(int, int);
void sharedGUI_loadscene(STRING *);
void sharedGUI_loadbackground(STRING *);
/**/void sharedGUI_loadlogo(BMAP *);
/**/void sharedGUI_mouse(int);
/**/void sharedGUI_mouseset(BMAP *);
/**/void sharedGUI_loadbuttons();
/**/void sharedGUI_centerpanel(PANEL *);
/**/void sharedGUI_dragpanel(PANEL *);
/**/void sharedGUI_centerfrom(PANEL *, PANEL *);

void sharedGUI_home();
void sharedGUI_prop();
void sharedGUI_mat();
void sharedGUI_editmat();
void sharedGUI_phy();
void controlcam();

void sharedGUI_launch_terrain();
void sharedGUI_launch_object();
void sharedGUI_launch_path();

void sharedGUI_updategui(PANEL *);
void sharedGUI_closewindow(var, PANEL *);
void sharedGUI_panelselect(PANEL *);

void sharedGUI__release();
void sharedGUI__loadlogo();
void sharedGUI__loadbuttons();

void scan_folder(STRING *,STRING *);

void follow_pointer();
void place_me(STRING *, int);
void restore();

void pass_to_gui(ENTITY *);
void pass_to_object();
void pass_mat_to_object();

void pass_file_to_material(MATERIAL *, STRING *);
void pass_mat_to_matsub(MATERIAL *);
void pass_material_to_file(STRING *, MATERIAL *);

void pass_object_to_clipboard(ENTITY *, obj_form *);
void pass_clipboard_to_object(ENTITY *);

void mat_select_null();
void mat_select_lava();
void mat_select_marble();
void mat_select_smaragd();
void mat_select_4();
void mat_select_5();
void mat_select_6();
void mat_select_7();
void mat_select_8();
void mat_select_9();
void mat_select_10();
void mat_select_11();
void mat_select_12();
void mat_select_13();
void mat_select_14();
void mat_save();

void obj_cut();
void obj_copy();
void obj_paste();

void obj_manip_setup();
void obj_manip_interface();

void switch_to_move();
void switch_to_rotate();
void switch_to_scale();