#ifndef Craftbox_System_AI

#define Craftbox_System_AI

/*
Craftbox_System_AI.c

Provides TUST's AI-related functions.

Written by Nguyen Ngoc Huy
https://github.com/ngochuy2101
http://craftboxdev.blogspot.com/

TODO:
<+++



>+++

NOTES:
<+++



>+++
--------------------------------------------------
*/

/** -> Node based pathfinder **/
void nodemesh_startup () { route_delete = list_delete; }

NodeMesh *nodemesh_create ()
{
	NodeMesh *nodemesh = sys_malloc ( sizeof(NodeMesh) );
	nodemesh->nodes = (Node*)sys_malloc ( sizeof(Node) * 4 );
	nodemesh->count = 0;
	nodemesh->capacity = 4;
	return nodemesh;
}

void nodemesh_remove ( NodeMesh *nodemesh )
{
	int i;
	Node *node = nodemesh->nodes;
	Node *nodeLast = node + nodemesh->count;
	for ( ; node<nodeLast; node++ )
	{
		if ( node->linked != NULL )
		sys_free ( node->linked );
	}
	sys_free ( nodemesh->nodes );
	sys_free ( nodemesh );
}

int nodes_trace ( Node *nodeFrom, Node *nodeTo, var mode, ENTITY *collider )
{
	ENTITY *me_old = me;
	me = collider;
	mode |= USE_BOX;
	int free_way = !(c_trace ( &nodeFrom->x, &nodeTo->x, mode ) > 0);
	me = me_old;
	return free_way;
}

void nodes_connect ( Node *nodeFrom, Node *nodeTo )
{
	if ( nodeFrom->count >= nodeFrom->capacity )
	{
		Node *newarray = sys_malloc ( sizeof(int) * ( nodeFrom->count + 4 ) );
		memcpy ( newarray, nodeFrom->linked, sizeof(int) * nodeFrom->count );
		sys_free ( nodeFrom->linked );
		nodeFrom->linked = newarray;
		nodeFrom->capacity += 4;
	}
	if ( nodeTo->count >= nodeTo->capacity )
	{
		Node *newarray = sys_malloc ( sizeof(int) * ( nodeTo->count + 4 ) );
		memcpy ( newarray, nodeTo->linked, sizeof(int) * nodeTo->count );
		sys_free ( nodeTo->linked );
		nodeTo->linked = newarray;
		nodeTo->capacity += 4;
	}
	*(nodeFrom->linked+nodeFrom->count) = nodeTo->index;
	nodeFrom->count += 1;
	*(nodeTo->linked+nodeTo->count) = nodeFrom->index;
	nodeTo->count += 1;
}

void nodemesh_ctrace_node ( NodeMesh *nodemesh, int nodeindex )
{
	int i;
	Node *node = nodemesh->nodes;
	Node *nodeLast = node + nodemesh->count;
	Node *nodeTemp = node + nodeindex;
	for ( ; node<nodeLast; node++ )
	{
		if ( node == nodeTemp ) 
		continue;
		if ( nodes_trace ( node, nodeTemp, IGNORE_PASSABLE, nodemesh_collider ) > 0 )
		nodes_connect ( node, nodeTemp );
	}
}

int nodemesh_add ( NodeMesh *nodemesh, VECTOR *pos )
{
	int i;
	
	if ( nodemesh_collider == NULL )
	{
		nodemesh_collider = ent_create ( CUBE_MDL, nullvector, NULL );
		vec_fill ( &nodemesh_collider->max_x, 20 );
		vec_fill ( &nodemesh_collider->min_x, -20 );
	}
	if ( nodemesh->count >= nodemesh->capacity )
	{
		Node *newarray = sys_malloc ( sizeof(Node) * ( nodemesh->count + 4 ) );
		memcpy ( newarray, nodemesh->nodes, sizeof(Node) * nodemesh->count );
		sys_free ( nodemesh->nodes );
		nodemesh->nodes = newarray;
		nodemesh->capacity += 4;
	}
	
	Node *newnode = nodemesh->nodes + nodemesh->count;
	vec_set ( &newnode->x, pos );
	newnode->weight = 0;
	newnode->index = nodemesh->count;
	newnode->includer = 0;
	newnode->linked = (int*)sys_malloc ( sizeof(int) * 4 );
	newnode->count = 0;
	newnode->capacity = 4;
	nodemesh->count ++;
	return newnode->index;
}

void nodemesh_draw ( NodeMesh *nodemesh, COLOR *color )
{
	int i, ii;
	VECTOR vtemp;
	Node *node = nodemesh->nodes;
	Node *nodeLast = node + nodemesh->count;
	for ( ; node<nodeLast; node++ )
	{
		vec_set ( &vtemp, &node->x );
		vec_to_screen ( &vtemp, camera );
		draw_text(str_for_int(NULL,node->index),vtemp.x,vtemp.y-20,COLOR_WHITE);
		//		draw_text(str_for_int(NULL,node->count),vtemp.x,vtemp.y,COLOR_GREY);
		draw_text(str_for_int(NULL,node->includer),vtemp.x,vtemp.y,COLOR_GREEN);
		
		int *link = node->linked;
		int *linkLast = link + node->count;
		for ( ; link<linkLast; link++ )
		{
			Node *neighbor = nodemesh->nodes + *link;
			draw_line3d ( &neighbor->x, color, 0 );
			draw_line3d ( &neighbor->x, color, 100 );
			draw_line3d ( &node->x, color, 100 );
			draw_line3d ( &node->x, color, 0 );
		}
	}
}

int nodemesh_nearest ( NodeMesh *nodemesh, VECTOR *pos )
{
	var distance = 1000000;
	int i, nearest_index = -1;
	for ( i=0; i<nodemesh->count; i++ )
	{
		Node *node = nodemesh->nodes + i;
		var new_distance = vec_dist ( &node->x, pos );
		if ( new_distance > distance )
		continue;
		distance = new_distance;
		nearest_index = i;
	}
	
	return nearest_index;
}

void *nodemesh_connect_nodes ( NodeMesh *nodemesh, int indexFrom, int indexTo )
{
	nodes_connect ( nodemesh->nodes + indexFrom, nodemesh->nodes + indexTo ); 
}

Route *nodemesh_find_route ( NodeMesh *nodemesh, int indexFrom, int indexTo )
{
	Node *nodesall = nodemesh->nodes;
	int i, ii;
	Node *start = nodesall + indexFrom;
	if ( start == NULL )
	return NULL;
	start->weight = -1000000;
	start->includer = -1;
	Node *end = nodesall + indexTo;
	if ( end == NULL )
	return NULL;
	end->includer = -1;
	
	Node *open = start;
	open->next = NULL;
	Node *close = NULL;
	
	while ( open != NULL )
	{
		Node *node = open;
		open = open->next;
		for ( i=0; i<node->count; i++ )
		{
			int index = *(node->linked + i);
			if ( index == node->includer )
			continue;
			Node *neighbor = nodesall + index;
			var distance = vec_dist ( &node->x, &neighbor->x );
			Node *prev = NULL, *tclose = close, *topen = open;
			for ( tclose = close; tclose != NULL; )
			{
				if ( tclose != neighbor )
				{
					prev = tclose;
					tclose = tclose->next;
					continue;
				}
				if ( neighbor->weight > node->weight + distance )
				{
					if ( close == neighbor )
					close = close->next;
					else
					prev->next = neighbor->next;
					
					topen = NULL;
				}
				else
				{
					topen = !NULL;
				}
				break;
			}
			if ( tclose == NULL )
			{
				for ( topen = open; topen != NULL; )
				{
					if ( topen != neighbor )
					{
						topen = topen->next;
						continue;
					}
					if ( neighbor->weight > node->weight + distance )				
					{
						neighbor->weight = node->weight + distance;
						neighbor->includer = node->index;
					}
					break;
				}
			}
			if ( topen == NULL )
			{
				neighbor->weight = node->weight + distance;
				neighbor->includer = node->index;
				if ( open == NULL )
				{
					neighbor->next = NULL;
					open = neighbor;
				}
				else
				{
					prev = NULL;
					for ( topen = open; topen != NULL; )
					{
						if ( topen->weight < neighbor->weight )
						{
							if ( topen->next == NULL )
							{
								topen->next = neighbor;
								neighbor->next = NULL;
								break;
							}
							prev = topen;
							topen = topen->next;
							continue;
						}
						if ( prev == NULL )
						{
							neighbor->next = open;
							open = neighbor;
						}
						else
						{
							neighbor->next = prev->next;
							prev->next = neighbor;
						}
						break;
					}			
				}
			}
		}
		node->next = close;
		close = node;
		
		if ( ( end->includer >= 0 ) && ( node->weight > end->weight ) )
		break;
	}
	
	if ( end->includer < 0 )
	return NULL;
	
	Route *route = list_create ();
	Node *node = end;
	i = 0;
	while ( 1 )
	{
		list_add_first ( route, node );
		i++;
		if ( node->includer >= 0 )
		node = nodesall + node->includer;
		else
		break;
	}
	
	return route;
}

void route_draw ( Route *route, COLOR *color )
{
	Node *node, *prev=NULL;
	ListIterator *it = list_begin_iterate(route);
	for ( node = list_iterate(it); it->hasNext; node = list_iterate(it) )
	{
		if ( prev != NULL )
		{
			draw_line3d ( &node->x, color, 0 );
			draw_line3d ( &node->x, color, 100 );
			draw_line3d ( &prev->x, color, 100 );
			draw_line3d ( &prev->x, color, 0 );
		}
		prev = node;
	}
	list_end_iterate(it);
}

/** <- **/

/** -> State machine **/

#define STMC_ACTIVE					(1<<8)
#define STMC_DELETE					(1<<9)
#define STMC_INDEX					(1<<10)

typedef struct STMCOL
{
	// private:
	STMACHINE *stmFirst;
	int count;
	int capacity;
	var flags;
} STMCOL;

STMCOL *gblMachines = NULL;
STMCOL *gblNewMachines = NULL;

STMCOL *stmcol_create ()
{
	STMCOL *stmcol = sys_malloc(sizeof(STMCOL));
	stmcol->stmFirst = sys_malloc(sizeof(STMACHINE)*STMC_MEMSTEP);
	stmcol->count = 0;
	stmcol->capacity = STMC_MEMSTEP;
	return stmcol;
}

void *stm_add ( void *obj, void *remover, void *fnc, var state, int *index )
{
	#ifdef STMC_SAFEMODE
		if ( fnc == NULL )
		{
			#ifdef STMC_ERRORS
				error ( "null function in stm_add" );
			#endif
			return;
		}
	#endif
	if ( gblNewMachines->count == gblNewMachines->capacity )
	{
		int old_capacity = gblNewMachines->capacity;
		gblNewMachines->capacity += STMC_MEMSTEP;
		STMACHINE *stmTemp = gblNewMachines->stmFirst;
		gblNewMachines->stmFirst = sys_malloc(sizeof(STMACHINE)*gblNewMachines->capacity);
		memcpy ( gblNewMachines->stmFirst, stmTemp, sizeof(STMACHINE)*old_capacity );
		sys_free ( stmTemp );
	}
	STMACHINE *stmTemp = gblNewMachines->stmFirst + gblNewMachines->count;
	stmTemp->flags = STMC_ACTIVE;
	stmTemp->ptrMe = obj;
	stmTemp->remover = remover;
	if ( remover != NULL )
	stmTemp->flags |= STMC_DELETE;
	stmTemp->fncPtr = fnc;
	stmTemp->fncNext = fnc;
	stmTemp->state = state;
	stmTemp->stateNext = state;
	if ( index == NULL )
	{
		index = sys_malloc(sizeof(int));
		stmTemp->flags |= STMC_INDEX;
	}
	*index = gblNewMachines->count;
	stmTemp->index = index;
	gblNewMachines->count++;
	return obj;
}

void stm_remove ( STMCOL *stmcol )
{
	#ifdef STMC_SAFE_MODE
		if ( stmcol == NULL ) 
		{
			#ifdef STMC_ERRORS
				error ( "null stmcollection in stm_remove" );
			#endif
			return;
		}
	#endif
	STMACHINE *stmTemp = stmcol->stmFirst;
	STMACHINE *stmTempLast = stmTemp + stmcol->count;
	for ( ; stmTemp<stmTempLast; stmTemp++ )
	{
		if ( stmTemp->ptrMe != NULL )
		if ( stmTemp->flags & STMC_DELETE )
		stmTemp->remover ( stmTemp->ptrMe );
		
		sys_free ( stmTemp );
	}
	sys_free ( stmcol );
}

void stm_set_state ( STMACHINE *stm, void *fnc, var state )
{
	stm->fncNext = fnc;
	stm->stateNext = state;
}

void stm_set_me ( STMACHINE *stm, void *obj, void *remover )
{
	stm->ptrMe = obj;
	stm->remover = remover;
	if ( remover != NULL )
	stm->flags |= STMC_DELETE;
	else
	stm->flags &= ~STMC_DELETE;
}

void stm_stop_machine ( STMACHINE *stm )
{
	stm->flags &= ~STMC_ACTIVE;
}

void stm_stop_ptr ( void *ptr )
{
	STMACHINE *stmTemp = gblMachines->stmFirst;
	STMACHINE *stmTempLast = stmTemp + gblMachines->count;
	for ( ; stmTemp<stmTempLast; stmTemp++ )
	{
		if ( stmTemp->ptrMe == ptr )
		stm_set_state ( stmTemp, stm_stop_machine, 0 );
	}
}

void stm_open ()
{
	gblMachines = stmcol_create ();
	gblNewMachines = stmcol_create ();
	gblMachines->flags |= STMC_ACTIVE;
	while ( gblMachines->flags & STMC_ACTIVE )
	{
		proc_mode = PROC_LATE;
		#ifdef STMC_COUNT
			draw_text ( str_for_int(NULL,gblMachines->count), 400, 20, COLOR_WHITE );
			draw_text ( str_for_int(NULL,gblMachines->capacity), 400, 40, COLOR_WHITE );
			draw_text ( str_for_int(NULL,gblNewMachines->count), 460, 20, COLOR_WHITE );
			draw_text ( str_for_int(NULL,gblNewMachines->capacity), 460, 40, COLOR_WHITE );
		#endif
		STMACHINE *stmTemp = gblMachines->stmFirst;
		STMACHINE *stmTempLast = stmTemp + gblMachines->count;
		for ( ; stmTemp<stmTempLast; stmTemp++ )
		{
			if ( stmTemp->flags & STMC_ACTIVE )
			stmTemp->fncPtr ( stmTemp );
		}
		int tail = 0;
		for ( stmTemp=gblMachines->stmFirst; stmTemp<stmTempLast; stmTemp++ )
		{
			if ( stmTemp->flags & STMC_ACTIVE )
			{
				stmTemp->fncPtr = stmTemp->fncNext;
				stmTemp->state = stmTemp->stateNext;
				if ( tail == 0 )
				continue;
				int ibytes = (long)stmTempLast - (long)stmTemp;
				//int ibytes = (long)(gblMachines->stmFirst+gblMachines->capacity) - (long)stmTemp;
				memcpy ( stmTemp-tail, stmTemp, ibytes ); // It copies to a previous memory overlapped for sure ;)
				stmTemp -= tail;
				stmTempLast -= tail;
				gblMachines->count -= tail;
				STMACHINE *stmTemp2 = stmTemp;
				for ( ; stmTemp2<stmTempLast; stmTemp2++ )
				*stmTemp2->index -= tail;
				tail = 0;
				continue;
			}
			if ( stmTemp->ptrMe != NULL )
			{
				if ( stmTemp->flags & STMC_DELETE )
				{
					stmTemp->remover ( stmTemp->ptrMe );
					stmTemp->flags &= ~STMC_DELETE;
				}
				stmTemp->ptrMe = NULL;
			}
			if ( stmTemp->flags & STMC_INDEX )
			{
				sys_free ( stmTemp->index );
				stmTemp->flags &= ~STMC_INDEX;
			}
			tail ++;
		}
		gblMachines->count -= tail;
		if ( gblNewMachines->count > 0 )
		{
			if ( gblMachines->count + gblNewMachines->count > gblMachines->capacity )
			{
				int old_capacity = gblMachines->capacity;
				gblMachines->capacity += gblNewMachines->count + STMC_MEMSTEP;
				STMACHINE *stmTemp = gblMachines->stmFirst;
				gblMachines->stmFirst = sys_malloc(sizeof(STMACHINE)*gblMachines->capacity);
				memcpy ( gblMachines->stmFirst, stmTemp, sizeof(STMACHINE)*old_capacity );
				sys_free ( stmTemp );
			}
			stmTemp = gblMachines->stmFirst + gblMachines->count;
			int ibytes = sizeof(STMACHINE)*gblNewMachines->count;
			memcpy ( stmTemp, gblNewMachines->stmFirst, ibytes );
			memset ( gblNewMachines->stmFirst, 0, ibytes );
			gblMachines->count += gblNewMachines->count;
			gblNewMachines->count = 0;
		}
		wait(1);
	}
	stm_remove ( gblMachines );
	stm_remove ( gblNewMachines );
}

void stm_close ()
{
	gblMachines->flags &= ~STMC_ACTIVE;
}

/** <- **/

#endif