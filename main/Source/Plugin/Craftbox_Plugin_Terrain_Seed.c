#ifndef Craftbox_Plugin_Terrain_Seed

#define Craftbox_Plugin_Terrain_Seed

#ifndef A7_DEVELOPMENT

/*
--------------------------------------------------
var ent_seed_c(

char* name, // entity filename
ENTITY* terrain, // ground entity
BMAP* mask,	  // color mask
COLOR* color, // target color 
var dist,	// average distance between entities
EVENT act

)

Desc: A custom variation of ent_seed.

Returns: The same as ent_seed.
--------------------------------------------------
*/
var ent_seed_c(

char* name, // entity filename
ENTITY* terrain, // ground entity
BMAP* mask,	  // color mask
COLOR* color, // target color 
var dist,	// average distance between entities
EVENT act

)	// entity action
{
	if(!name || !color) return 0;
	if(!terrain) terrain = level_ent;
	if(!mask) mask = ent_getskin(terrain,1);
	if(!mask) return 0;
	
	var width = bmap_width(mask);
	var height = bmap_height(mask);
	float fdx = PIXEL_DX(terrain,mask);
	float fdy = PIXEL_DY(terrain,mask);

	var i,j,n=0;
	float fnum = 0;
	float fdist = dist;
	var format = bmap_lock(mask,0);
	var pixel = pixel_for_vec(color,NULL,format);
	// check all pixels of the mask, and plant entities on all pixels with the right color
	for(j=0; j<height; j++)
	for(i=0; i<width; i++)
	{
		// right mask color?		
		if(pixel != pixel_for_bmap(mask,i,j)) continue;
		// accumulate the probability for an entity per pixel   	
		fnum += fdx/fdist*fdy/fdist;
		while(fnum > random(1))
		{  	 
			ENTITY* ent = ent_create(name,NULL,act);
			if (!ent) return 0;
			// calculate random position within the size of the terrain pixel
			vec_set(&ent->x,terrain_pixel_to_pos(terrain,i,j,mask) + 50);
			ent->x += random(fdx);
			ent->y += random(fdy) + 50;
			// put it on the terrain height at that place
			ent_place_z(ent,terrain_height(terrain,&ent->x)-2);		
			// reduce the placement probability for the next pixel	  	
			fnum -= random(2);
			n++;
		}
	} 
	bmap_unlock(mask);
	return n;
}


/*
--------------------------------------------------
void PerformSeed()

Desc: Starts the seeding process.

Returns: -
--------------------------------------------------
*/
void PerformSeed() {
	
	if(event_type == EVENT_RELEASE) return;
	
	STRING *tempTERRAINSEEDBMAP = "#400";
	
	str_cpy( tempTERRAINSEEDBMAP, TerrainEnt->type );
	str_cat(tempTERRAINSEEDBMAP,SEEDMASKDATA);
	str_cat( tempTERRAINSEEDBMAP, ".tga");
	
	if( file_exists(tempTERRAINSEEDBMAP) ) {
		
		if(is(canvas_pan,SHOW)) reset(canvas_pan,SHOW);
		if(is(seedPanelCover,SHOW)) reset(seedPanelCover,SHOW);
		
		var def = collision_mode;
		collision_mode = 0; // Entities are created faster this way.
		
		if( str_len(seedEnt) && !str_cmp(seedEnt,undef) && !str_cmp((seedEnt->chars)[0],"") ) ent_seed_c(seedEnt,TerrainEnt,bmap_create(tempTERRAINSEEDBMAP),current_color2,15,SeedEntCore);
		while(proc_status(ent_seed_c)) wait(1);
		
		collision_mode = def;
		
		mark_seedEntstr = 0;
		
	}
	
}

/*
--------------------------------------------------
void SeedEntCore()

Desc: Core function for each seeded entity,

Returns: -
--------------------------------------------------
*/
void SeedEntCore() {
	
	my.flags |= PASSABLE; 
	my.flags &= ~(POLYGON | DYNAMIC);
	my.ObjectType = SeedEnt;
	
	my.pan = random(360);
	Scale(my,5);
	
}

/*
--------------------------------------------------
void RemoveSeedEnts()

Desc: Removes all seeded entities in the entity chain.

Returns: -
--------------------------------------------------
*/
void RemoveSeedEnts() {
	
	proc_mode = PROC_NOFREEZE;
	
	if(event_type == EVENT_RELEASE) return;
	
	freeze_mode = 2;
	
	you = ent_next(NULL);
	while(you != NULL) {
		
		if(you.ObjectType == SeedEnt) ptr_remove(you);
		you = ent_next(you);
		
	}
	
	freeze_mode = 0;

}

/*
--------------------------------------------------
void RecreateSeedMap()

Desc:

Returns: -
--------------------------------------------------
*/
void RecreateSeedMap() {
	
	if(event_type == EVENT_RELEASE) return;
	
	ptr_remove(canvas_paint);
	while( proc_status(ptr_remove) ) wait(1);
	canvas_paint = bmap_create("tskin.tga");
	
}

/*
--------------------------------------------------
void SeedEntSelector()

Desc:

Returns: -
--------------------------------------------------
*/
void SeedEntSelector() {
	
	if(event_type == EVENT_RELEASE) return;
	
	STRING *oldTEMPSTR = str_create(TEMPSTR);
	
	GInsertObjectShow();
	while(proc_status( GInsertObjectShow )) wait(1);
	
	while( ! mark_seedEntstr ) wait(1); // Wait until something is selected
	
	if( !str_cmp(TEMPSTR,undef) ) {
		
		str_cpy(seedEnt,TEMPSTR);
		str_cpy(TEMPSTR,oldTEMPSTR);
		
	}
	
}


/*
--------------------------------------------------
void paint_canvas()

Desc:

Returns: -
--------------------------------------------------
*/
void paint_canvas()
{
	
	canvas = canvas_paint; // set the pointer to our canvas
	canvas_modified = 1; // the player has painted something on the canvas, so the file will be saved on exit automatically
	while(mouse_left && !paint_outside) // this look runs for as long as the left mouse button is being pressed
	{
		
		format = bmap_lock(canvas, 0); // lock the canvas bitmap
		pixel = pixel_for_vec(current_color2, 100, format); // convert the color (alpha = 100) to a pixel in the given format
		pixel_to_bmap(canvas, coords_x, coords_y, pixel); // now write the pixel at the coords_x, coords_y position
		
		pixel_to_bmap(canvas,coords_x, coords_y,pixel);
		pixel_to_bmap(canvas,coords_x + 1, coords_y,pixel);
		pixel_to_bmap(canvas,coords_x + 2, coords_y,pixel);
		pixel_to_bmap(canvas,coords_x, coords_y + 1,pixel);
		pixel_to_bmap(canvas,coords_x, coords_y + 2,pixel);
		pixel_to_bmap(canvas,coords_x + 1, coords_y + 1,pixel);
		pixel_to_bmap(canvas,coords_x + 1, coords_y + 2,pixel);
		pixel_to_bmap(canvas,coords_x + 2, coords_y + 1,pixel);
		pixel_to_bmap(canvas,coords_x + 2, coords_y + 2,pixel);
		
		bmap_unlock(canvas); // unlock the bitmap now
		wait(1);
		
	}     
	
}

#define PRAGMA_PRINT " [Loaded plugin terrain seeding] "

#else

#define PRAGMA_PRINT " [Gamestudio A7 detected - terrain seeding functionality will be disabled.]"

#endif

#endif