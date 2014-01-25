/******************************

- [ 15.1.2014 ] rewrote saving/loading functions (support for custom, external deformation data)

******************************/


/*
--------------------------------------------------
void TDeform_changeBrushSingle()

Desc:

Returns: -
--------------------------------------------------
*/
//void TDeform_changeBrushSingle() { bType = B_SIBGLE; }

/*
--------------------------------------------------
void TDeform_changeBrushMultiple()

Desc:

Returns: - 
--------------------------------------------------
*/
//void TDeform_changeBrushMultiple() { bType = B_MULT;	}

/*
--------------------------------------------------
void TDeform_changeBrushMultipleSmooth()

Desc:

Returns: -
--------------------------------------------------
*/
//void TDeform_changeBrushMultipleSmooth() { bType = B_MULT_SMOOT; }

/*
--------------------------------------------------
void TDeform_changeBrushRaise()

Desc:

Returns: -
--------------------------------------------------
*/
void TDeform_changeBrushRaise() {
	
	if(event_type == EVENT_RELEASE) return;
	
	if( button_state(TerrainToolbar,2,-1)) button_state(TerrainToolbar,2,0); // The lower button
	bHeight = DEF_UPPER;
	
}

/*
--------------------------------------------------
void TDeform_changeBrushLower()

Desc:

Returns: -
--------------------------------------------------
*/
void TDeform_changeBrushLower() {
	
	if(event_type == EVENT_RELEASE) return;
	
	if (button_state(TerrainToolbar,1,-1)) button_state(TerrainToolbar,1,0); // The raise button
	bHeight = DEF_LOWER;
	
}


/*
--------------------------------------------------
void TDeform_single()

Desc: Deform Single Vertex, no smooth

Returns: -
--------------------------------------------------
*/
void TDeform_single()
{

	proc_kill(4);

	var vertex_number = ent_nextvertex(my,temp_pos);
	CONTACT* c = ent_getvertex(my,NULL,vertex_number);     
	
	if(bHeight == DEF_UPPER)
	{
		c.z += sizeh * brush_speed;  // increase the vertex height
		c.v = NULL;
		if(c.z <= tMaxHeight) ent_setvertex(my,c,vertex_number);     // update the mesh
		
		else if(bHlimit)
		{
			c.z=tMaxHeight;
			ent_setvertex(my,c,vertex_number);     // update the mesh		
		}
	}
	else if(bHeight == DEF_LOWER)
	{
		c.z -= sizeh * brush_speed;  // increase the vertex height
		c.v = NULL; 
		if(c.z >= 0) ent_setvertex(my,c,vertex_number);     // update the mesh
		else if(bHlimit)
		{	
			c.z=0;
			ent_setvertex(my,c,vertex_number);    // update the mesh		
		}
		
	}

}

/*
--------------------------------------------------
void TDeform_multiple()

Desc:Deform Multiple Vertex no smooth

Returns: -
--------------------------------------------------
*/
void TDeform_multiple()
{

	proc_kill(4);
	proc_mode = PROC_EARLY;
	
	VECTOR vertex_pos;
	int ping=1;

	CONTACT* c;    

	while(ping <= ent_status(TerrainEnt,1))
	{	 		
		vec_for_vertex(vertex_pos,TerrainEnt,ping);	
		
		if(vec_dist(vertex_pos,temp_pos)<=bSize)
		{
			c = ent_getvertex(TerrainEnt,NULL,ping);
			
			if(bHeight == DEF_UPPER)
			{
				c.z += sizeh * brush_speed;  // increase the vertex height
				c.v = NULL;
				
				
				
				if(c.z <= tMaxHeight) ent_setvertex(my,c,ping);    			// update the mesh					
				else if(bHlimit)
				{
					c.z = tMaxHeight;
					ent_setvertex(my,c,ping);    			// update the mesh					
					
				}
			}
			else if(bHeight == DEF_LOWER)
			{
				
				c.z -= sizeh * brush_speed;  // increase the vertex height
				c.v = NULL;
				
				if(c.z >= 0) ent_setvertex(my,c,ping);    			// update the mesh					
				else if(bHlimit)
				{
					c.z = 0;
					ent_setvertex(my,c,ping);    			// update the mesh					
					
				}
				
				
				
			}
		}		
		ping +=1;				
	}

}

/*
--------------------------------------------------
void TDeform_multipleSmooth()

Desc: Deform multiple vertices with smooth

Returns: -
--------------------------------------------------
*/
void TDeform_multipleSmooth()
{

	proc_kill(4);
	proc_mode = PROC_EARLY;

	int ping=1;
	VECTOR vertex_pos;
	CONTACT* c;

	while(ping <= ent_status(TerrainEnt,1))
	{	
		vec_for_vertex(vertex_pos,TerrainEnt,ping);			
		
		if(vec_dist(vertex_pos,temp_pos)<=bSize)
		{	
			
			c = ent_getvertex(my,NULL,ping);
			
			if(bHeight == DEF_UPPER)
			{	
				
				c.z += (sizeh/vec_dist(vertex_pos,temp_pos)) * brush_speed;
				c.v = NULL;			
				
				if(c.z <= tMaxHeight) ent_setvertex(my,c,ping);   		 	// update the mesh			
				else if(bHlimit)
				{
					c.z = tMaxHeight;
					c.v = NULL;			
					ent_setvertex(my,c,ping);
				}
			}
			else if(bHeight == DEF_LOWER)
			{
				c.z -= (sizeh/vec_dist(vertex_pos,temp_pos)) * brush_speed;
				c.v = NULL;			
				
				if(c.z >= 0) ent_setvertex(my,c,ping);   		 	// update the mesh			
				else if(bHlimit)
				{
					c.z = 0;
					c.v = NULL;			
					ent_setvertex(my,c,ping);
				}
				
			}
			
			
			
		}			
		ping +=1;		
		
	}	
}

/*
--------------------------------------------------
void TDeform_saveterrain(ENTITY *terrain)

Desc:

Returns: -
--------------------------------------------------
*/
void TDeform_saveterrain(ENTITY *terrain)
{
	/*
	
	proc_kill(4);
	
	WriteLog("[ ] Saving terrain data to ");
	
	while(!terrain) wait(1);
	
	STRING *savestr = "#400";
	
	str_cpy(savestr,terrain->type ); // 4 = ".hmp";
	str_cat(savestr,TERRAINDATA);
	str_cat(savestr,".txt");
	
	WriteLog(savestr);
	WriteLog(", please wait.");
	NewLine();
	
	var terrainHandle = file_open_write(savestr);
	if(!terrainHandle) {
		
		WriteLog("!! [ERROR] Cannot open ");
		WriteLog(savestr);
		WriteLog(" for writing terrain geometry data. Operation aborted.");
		NewLine();
		
		return;
		
	}
	
	VECTOR mesh_coords;
	var index = 0;
	while(index <= total_vertices) // go through all the vertices
	{
		vec_for_mesh(mesh_coords.x, terrain, index); // and get their z coordinates		
		file_var_write(terrainHandle,mesh_coords.z);
		
		index++;
	}
	
	var _size = file_length(terrainHandle)*1024; // original in bytes, convert to KBs
	
	file_close(terrainHandle);
	
	WriteLog("[X] Task completed, file size: ");
	WriteLog(_size);
	NewLine();
	
	*/
	
	proc_kill(4);
	
	WriteLog("[ ] Saving terrain data to ");
	
	while(!terrain) wait(1);
	
	char *c = file_dialog_save(" ",EXT_GEO);
	
	if( !c ) return;
	
	STRING *_c = "#400";
	str_cpy( _c, _str(c) );
	str_cat(_c, ".ctdd" );
	
	WriteLog(_c);
	WriteLog(", please wait.");
	NewLine();
	
	var terrainHandle = file_open_write(_c);
	if(!terrainHandle) {
		
		WriteLog("!! [ERROR] Cannot open ");
		WriteLog(_c);
		WriteLog(" for writing terrain geometry data. Operation aborted.");
		NewLine();
		
		return;
		
	}
	
	VECTOR mesh_coords;
	var index = 0;
	while(index <= total_vertices) // go through all the vertices
	{
		vec_for_mesh(mesh_coords.x, terrain, index); // and get their z coordinates		
		file_var_write(terrainHandle,mesh_coords.z);
		
		index++;
	}
	
	var _size = file_length(terrainHandle)*1024; // original in bytes, convert to KBs
	
	file_close(terrainHandle);
	
	WriteLog("[X] Task completed, file size: ");
	WriteLog(_size);
	NewLine();
	
	
}

/*
--------------------------------------------------
void TDeform_LoadHeightFrom(ENTITY *terrain)

Desc:

Returns: -
--------------------------------------------------
*/
void TDeform_LoadHeightFrom(ENTITY *terrain) {
	
	/*
	
	proc_kill(4);
	
	WriteLog("[ ] Attempting to load terrain data from ");
	
	while(!terrain) wait(1);
	
	STRING *loadstr = "#400";
	
	str_cpy(loadstr,terrain->type);
	str_cat(loadstr,TERRAINDATA);
	str_cat(loadstr,".txt");
	
	WriteLog(loadstr);
	WriteLog(", please wait.");
	NewLine();

	if(file_exists(loadstr))  // previously saved data exists?
	{
		
		var terrainHandle = file_open_read(loadstr);
		
		var index = 0;
		while(index <= total_vertices) // then load the previously stored height values and apply them to the terrain
		{
			// no need to load the x and y coordinates of the terrain - they can't be changed
			vec_to_mesh(vector (0, 0, file_var_read(terrainHandle) ), terrain, index);
			index += 1;
			
		}
		
		file_close(terrainHandle);
		} else {
		
		WriteLog("Failed to open ");
		WriteLog(loadstr);
		WriteLog(" for passing geometry data to terrain. Operation aborted.");
		NewLine();
		
	}
	
	WriteLog("[X] Task completed.");
	NewLine();
	
	*/
	
	proc_kill(4);
	
	WriteLog("[ ] Attempting to load terrain data from ");
	
	while(!terrain) wait(1);
	
	char *c = file_dialog_open(" ",EXT_GEO);
	if( !c ) return;
	
	WriteLog(c);
	WriteLog(", please wait.");
	NewLine();

	if(file_exists(c))  // previously saved data exists?
	{
		
		var terrainHandle = file_open_read(c);
		
		var index = 0;
		while(index <= total_vertices) // then load the previously stored height values and apply them to the terrain
		{
			// no need to load the x and y coordinates of the terrain - they can't be changed
			vec_to_mesh(vector (0, 0, file_var_read(terrainHandle) ), terrain, index);
			index += 1;
			
		}
		
		file_close(terrainHandle);
		
		} else {
		
		WriteLog("Failed to open ");
		WriteLog(c);
		WriteLog(" for passing geometry data to terrain. Operation aborted.");
		NewLine();
		
	}
	
	WriteLog("[X] Task completed.");
	NewLine();
	
}

#define PRAGMA_PRINT " [Loaded plugin terrain deformation] "