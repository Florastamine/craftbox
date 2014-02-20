#ifndef Craftbox_System_GameIO

#define Craftbox_System_GameIO

/*
--------------------------------------------------
Craftbox_System_GameIO.c

Provides functions for communicating with internal data.
Contains code from the TUST library, such as the linked list implementation.

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

/*
--------------------------------------------------
void on_level_event(percent)

Desc: A modified version of the on_level_event that is shown in the 3D Gamestudio manual.

Returns: -
--------------------------------------------------
*/
void on_level_event(percent)
{
	
	set(pLoadBar,SHOW | LIGHT);   // switch load bar on
	pLoadBar->layer = 1000;
	//pLoadBar.pos_y = screen_size.y - 40;
	pLoadBar.size_x = GetPercent( percent,100 ) * screen_size.x/100; // because max percent = 100
	pLoadBar.size_y = 30;
	
	if (percent >= 100) reset(pLoadBar,SHOW);
	pLoadBar.size_x = 0;
	
}


/*
--------------------------------------------------
int GetPercent(var consumed, var total)

Desc: Calculate the percent (%) based on "consumed" and "total".

Returns: Percent (%).
--------------------------------------------------
*/
int GetPercent(var consumed, var total) {
	
	return (abs(consumed)*100)/abs(total);
	
}

/*
--------------------------------------------------
void ConvertToCTFormat(STRING *dest, var TrackVariable, var TotalVariable )

Desc: Takes TrackVariable and TotalVariable as input, convert them into 
the following format:

"(TrackVariable/TotalVariable) (% used) "

then sends the result back to dest.

Call it once to let dest be static, or place in a loop 
to dynamically update dest based on TrackVariable and TotalVariable's changes.

This is very useful, f.e. you don't have to define several texts for numbers/strings/symbols, and align them manually, which is very ugly and time-consuming.

Returns: -
--------------------------------------------------
*/
void ConvertToCTFormat(STRING *dest, var TrackVariable, var TotalVariable ) {
	
	STRING *s = "#400";
	
	str_for_num(dest,TrackVariable);
	str_cat(dest,"/");
	str_cpy(s,dest);
	
	s = str_for_num(s,TotalVariable);
	str_cat(dest,s);
	str_cat(dest," (");
	
	s = str_for_int(s,GetPercent(TrackVariable,TotalVariable));
	str_cat(dest,s);
	str_cat(dest,"%)");
	
	
}

/*
--------------------------------------------------
void LaunchGameSession()

Desc:

Returns: -
--------------------------------------------------
*/
var olmouse;
void LaunchGameSession() {

	if(event_type == EVENT_RELEASE) return;
	
	WriteLog("[ ] Creating a game session, please wait.");
	NewLine();
	
	olmouse = mouse_mode;
	mouse_mode = 0;
	
	dtimer();
	
	double time;

	// Disable all the panels first
	GMainMenuHide();
	GWorldNewHide();
	GLoadGameHide();
	GOptionsHide();
	GTrophiesHide();
	GHelpHide();
	GInDevHide();
	
	guiCurrentViewPreset = MENU_CAMERA_LAUNCH_GAME;
	
	CreateWorld->alpha = 0;
	set(CreateWorld,SHOW);
	while(CreateWorld->alpha <= 100) {
		
		CreateWorld->alpha += 5 * time_step;
		wait(1);
		
	}
	set(CreateWorldCoffee,SHOW);

	// Begin loading the level
	LoadNewLevel();
	while(proc_status(LoadNewLevel)) wait(1);
	
	mouse_mode = olmouse;
	
	reset(CreateWorldCoffee,SHOW);
	
	while(CreateWorld->alpha > 0) {
		
		CreateWorld->alpha -= 5 * time_step;
		wait(1);
		
	}	
	reset(CreateWorld,SHOW);
	
	if( ! LoadWorldBreak ) {
		
		GGUIShow();
		while(proc_status(GGUIShow)) wait(1);
		
		time = dtimer();
		
		SessionsCount += 1;
		
		WriteLog("[X] Task completed, launched game session #",SessionsCount);
		WriteLog(" , cost ",time ); // convert to sec: multiply it by pow(10,6) (microsecs)
		WriteLog(" ms");
		NewLine();
		
		WriteLog("Ground loaded: ");
		WriteLog( GROUNDSTR );
		NewLine();
		
	}
	
	else {
		
		_beep();
		WriteLog("!! [ERROR] Could not load a new world (probably missing ground files), aborting...");
		NewLine();
		
		reset(CreateWorldCoffee,SHOW);
		
		while(CreateWorld->alpha > 0) {
			
			CreateWorld->alpha -= 5 * time_step;
			wait(1);
			
		}	
		reset(CreateWorld,SHOW);
		
		WriteLog("[X] Task failed for LaunchGameSession().");
		NewLine();
		
		mouse_mode = olmouse;
		
		GMainMenuShow();
		
	}

}

/*
--------------------------------------------------
void LoadNewLevel()

Desc: Loads a blank level.

Returns: -
--------------------------------------------------
*/
void LoadNewLevel() {
	
	WriteLog("[ ] Loading ground...");
	NewLine();
	
	if( !str_cmp(GROUNDSTR, undef) ) // If a ground was specified.
	level_load( GROUNDSTR );
	
	else { // else
		
		if( !str_cmp( (files_list_GROUNDSTR_Pool.pstring) [0], undef) ) { // if the pool isn't empty
			
			str_cpy( GROUNDSTR, (files_list_GROUNDSTR_Pool.pstring) [0] ); // the load the first slot
			level_load( GROUNDSTR );
			
		}
		else { // pool is empty! nothing was found in the ground folder, abort
			
			LoadWorldBreak = 1;
			
			return;
			
		}
		
	}

	WriteLog("[ ] Creating sky cube...");
	NewLine();
	
	/* _cube = */
	if( !str_cmp(SKYSTR,undef) ) {
		
		// This allows different types of skies can be created.
		if( str_stri(SKYSTR,"+6") ) skycube = ent_createlayer(SKYSTR,SKY | CUBE | SHOW, 1); // If you want to hide the sun, moon, everythiing just set layer to 999
		else skycube = ent_createlayer(SKYSTR,SKY | CYLINDER | SHOW,1);
		
	}
	else { // Default sky cube
		
		// the reason why i use SKYSTR here is: SKYSTR can be read later in act_glass.
		str_cpy(SKYSTR,PATH_SKIES);
		str_cat(SKYSTR,"cubemap+6.tga"); // cubemap+6.tga is mandatory
		skycube = ent_createlayer(SKYSTR,SKY | CUBE | SHOW, 1); // again, set layer = 999 or larger to disable moon, sun, etc.
		
	}
	
	WriteLog("[ ] Loading miscellaneous stuff...");
	NewLine();

	marker = ent_create("target.mdl",vector(0,0,0),FollowPointer); // Create a mouse pointer.
	
	//	marker.ObjectType = Neutral;
	camera.ambient = -50;

	manip_type = scale + 1;

	cbInBuildment = 1;
	
}

/*
--------------------------------------------------
void *memmove(BYTE *destination, BYTE *source, unsigned int num)

Desc: See Craftbox.h

Returns: -
--------------------------------------------------
*/
void *memmove(BYTE *destination, BYTE *source, unsigned int num)
{
	// Nothing to do here!
	if(num <= 0) return destination;
	if(destination == source) return destination;

	if(abs((int)destination - (int)source) >= num)
	{
		// No overlapping
		memcpy(destination, source, num);
		return destination;
	}
	
	if(destination < source)
	{
		while(num > 0)
		{
			*destination = *source;
			destination++;
			source++;
			num--;
		}
	}
	else
	{
		destination += num - 1;
		source += num - 1;
		while(num > 0)
		{
			*destination = *source;
			destination--;
			source--;
			num--;
		}
	}
	
	return destination;
} 

/*
--------------------------------------------------
void draw_font(STRING* text, var x, var y, COLOR* color, FONT *font, int flags, var alpha)

Desc: Writes a string at the given XY screen position in the current frame, using a Gamestudio FONT.

Returns: -
--------------------------------------------------
*/
void draw_font(STRING* text, var x, var y, COLOR* color, FONT *font, int flags, var alpha)
{
	static TEXT *txt = NULL;
	if(txt == NULL)
		txt = txt_create(1, -1);
	
	flags = flags & (CENTER_X | CENTER_Y | FILTER | ARIGHT | CONDENSED | SHADOW | OUTLINE);
	
	txt->pos_x = x;
	txt->pos_y = y;
	txt->flags = flags | LIGHT | TRANSLUCENT;
	txt->alpha = alpha;
	txt->font = font;
	(txt->pstring)[0] = text;
	if(color != NULL)
		vec_set(&txt->blue, color);
	
	draw_obj(txt);
}

/*
--------------------------------------------------
void ang_normalize(ANGLE* _ang)

Desc: Sets all values of an angle between 0 and 360

Returns: -
--------------------------------------------------
*/
void ang_normalize(ANGLE* _ang) {
	_ang->pan = cycle(_ang->pan, 0, 360);
	_ang->tilt = cycle(_ang->tilt, 0, 360);
	_ang->roll = cycle(_ang->roll, 0, 360);
}

/*
--------------------------------------------------
VECTOR* vec_for_ent_ext(VECTOR* _target, ENTITY* _ent, int _vertexNumber)

Desc: Calculates a vertex position of an entity in world space.

Returns: -
--------------------------------------------------
*/
VECTOR* vec_for_ent_ext(VECTOR* _target, ENTITY* _ent, int _vertexNumber) {
	CONTACT* c = ent_getvertex(_ent, NULL, _vertexNumber);
	if (c != NULL) {
		vec_set(_target, vector(c->v->x, c->v->z, c->v->y));
		vec_mul(_target, vector(_ent.scale_x, _ent.scale_y, _ent.scale_z));
		vec_rotate(_target, _ent.pan);
		vec_add(_target, _ent.x);
		//printf("Ent pos: (%i,%i,%i), new pos: (%i,%i,%i)", (long)_ent->x, (long)_ent->y, (long)_ent->z, (long)_target->x, (long)_target->y, (long)_target->z);
		return _target;
	} else {
		return NULL;
	}
}

////////////////////////////////////////////////////////////
// Linked list implementation
////////////////////////////////////////////////////////////
List *list_create()
{
	List *list = sys_malloc(sizeof(List));
	list->first = NULL;
	list->last = NULL;
	list->count = 0;
	return list;
}

void list_delete(List *list)
{
	// Free all items.
	list_clear(list);
	sys_free(list);
}

List *list_clone(List *list)
{
	List *clone = list_create();
	
	// Just iterate through all items and add them to the new list.
	ListItem *it = list->first;
	for(it = list->first; it != NULL; it = it->next)
	{
		list_add(clone, it->data);
	}
	
	return clone;
}

void list_add(List *list, ListData *data)
{
	ListItem *item = sys_malloc(sizeof(ListItem));
	
	// Add at the end of the list.
	item->previous = list->last;
	item->next = NULL;
	item->data = data;
	
	if(list->first == NULL)
	{
		// Set as first if list is empty.
		list->first = item;
	}
	else
	{
		// Else append to the last item.
		list->last->next = item;
	}
	list->last = item;
	list->count += 1;
}

void list_add_range(List *list, ListData **array, int count)
{
	int i;
	for(i = 0; i < count; i++)
	{
		list_add(list, array[i]);
		list->count += 1;
	}
}

void list_remove(List *list, ListData *data)
{
	ListItem *it = list->first;
	for(it = list->first; it != NULL; it = it->next)
	{
		if(it->data != data)
			continue;
		ListItem *previous = it->previous;
		ListItem *next = it->next;
		
		if(previous != NULL)
		{
			previous->next = next;
		}
		else
		{
			list->first = next;
		}
		
		if(next != NULL)
		{
			next->previous = previous;
		}
		else
		{
			list->last = previous;
		}
		sys_free(it);
		list->count -= 1;
		return;
	}
}

void list_remove_all(List *list, ListData *data)
{
	ListItem *it = list->first;
	for(it = list->first; it != NULL; )
	{
		if(it->data != data)
		{
			it = it->next;
			continue;
		}
		ListItem *previous = it->previous;
		ListItem *next = it->next;
		
		if(previous != NULL)
		{
			previous->next = next;
		}
		else
		{
			list->first = next;
		}
		
		if(next != NULL)
		{
			next->previous = previous;
		}
		else
		{
			list->last = previous;
		}
		sys_free(it);
		list->count -= 1;
		it = next;
	}
}

void list_remove_at(List *list, int index)
{
	int i = 0;
	ListItem *it = list->first;
	for(it = list->first; it != NULL; it = it->next)
	{
		if(i != index)
		{
			i++;
			continue;
		}
		ListItem *previous = it->previous;
		ListItem *next = it->next;
		
		if(previous != NULL)
		{
			previous->next = next;
		}
		else
		{
			list->first = next;
		}
		
		if(next != NULL)
		{
			next->previous = previous;
		}
		else
		{
			list->last = previous;
		}
		sys_free(it);
		list->count -= 1;
		return;
	}
}

int list_contains(List *list, ListData *item)
{
	ListItem *it = list->first;
	for(it = list->first; it != NULL; it = it->next)
	{
		if(it->data != item)
			continue;
		return 1;
	}
	return 0;
}

ListData *list_item_at(List *list, int index)
{
	int i = 0;
	ListItem *it = list->first;
	for(it = list->first; it != NULL; it = it->next)
	{
		if(i != index)
		{
			i++;
			continue;
		}
		return it->data;
	}
	return NULL;
}

void list_clear(List *list)
{
	ListItem *it = list->first;
	for(it = list->first; it != NULL; )
	{
		ListItem *next = it->next;
		sys_free(it);		
		it = next;
	}
	list->first = NULL;
	list->last = NULL;
	list->count = 0;
}

void list_sort(List *list, void *compare)
{
	int swapped = 0;
	do
	{
		swapped = 0;
		ListItem *it;
		for(it = list->first; it != list->last; it = it->next)
		{
			int compare_func(ListData *left, ListData *right);
			compare_func = compare;
			if(compare_func(it->data, it->next->data) > 0)
			{
				/* swap them and remember something changed */
				ListData *data2 = it->next->data;
				it->next->data = it->data;
				it->data = data2;
				swapped = 1;
			}
		}
	}
	while(swapped != 0);
}

void list_reverse(List *list)
{
	ListItem *it = list->first;
	for(it = list->first; it != NULL; )
	{
		ListItem *next = it->next;
		ListItem *prev = it->previous;
		it->previous = it->next;
		it->next = prev;
		it = next;
	}
	ListItem *last = list->last;
	list->last = list->first;
	list->first = last;
}

int list_get_count(List *list)
{
	//int count = 0;
	//ListItem *it = list->first;
	//for(it = list->first; it != NULL; it = it->next)
	//{
	//	count++;
	//}
	return list->count;
}

int list_copy_to(List *list, ListData **array, int arrayLength)
{
	int count = 0;
	ListItem *it = list->first;
	for(it = list->first; it != NULL; it = it->next)
	{
		if(count >= arrayLength)
			return count;
		array[count] = it->data;
		count++;
	}
	return count;
}


ListIterator *list_begin_iterate(List *list)
{
	ListIterator *iterator = sys_malloc(sizeof(ListIterator));
	
	iterator->list = list;
	iterator->current = NULL;
	iterator->valid = 0;
	iterator->hasNext = list->first != NULL;
	return iterator;
}

ListData *list_iterate(ListIterator *iterator)
{
	if(iterator->hasNext == 0)
		return NULL;
	if(iterator->valid)
	{
		iterator->current = iterator->current->next;
		iterator->hasNext = iterator->current != NULL;
		if(iterator->current == NULL)
			return NULL;
	}
	else
	{
		iterator->current = iterator->list->first;
		iterator->valid = 1;
	}
	return iterator->current->data;
}

void list_end_iterate(ListIterator *iterator)
{
	sys_free(iterator);
}

void list_clear_content ( List *list, void *remove_function )
{
	ListItem *it = list->first;
	void itemdata_remover ( ListData *data );
	itemdata_remover = remove_function;
	for ( it = list->first; it != NULL; )
	{
		ListItem *next = it->next;
		itemdata_remover ( it->data );
		sys_free(it);		
		it = next;
	}
	list->first = NULL;
	list->last = NULL;
	list->count = 0;
}

void list_add_first ( List *list, ListData *item )
{
	ListItem *listitem = sys_malloc(sizeof(ListItem));
	listitem->previous = NULL;
	listitem->next = list->first;
	listitem->data = item;
	if ( list->first == NULL )
		list->last = listitem;
	else
		list->first->previous = listitem;
	list->first = listitem;
	list->count += 1;
}

void list_add_sorted ( List *list, ListData *item, void *compare )
{
	ListItem *newitem = sys_malloc(sizeof(ListItem));
	newitem->previous = NULL;
	newitem->next = NULL;
	newitem->data = item;
	ListItem *it = list->first;
	if ( it == NULL )
	{
		list->last = newitem;
		list->first = newitem;
		list->count += 1;
		return;
	}
	int compare_func(ListData *left, ListData *right);
	compare_func = compare;
	if ( compare_func ( it->data, item ) > 0 )
	{
		newitem->next = list->first;
		list->first->previous = newitem;
		list->first = newitem;
		list->count += 1;
		return;
	}
	for ( it = list->first; it != list->last; )
	{
		ListItem *next = it->next;
		if ( compare_func ( next->data, item ) > 0 )
		{
			newitem->previous = it;
			newitem->next = next;
			next->previous = newitem;
			it->next = newitem;
			list->count += 1;
			return;
		}
		it = next;
	}
	newitem->previous = list->last;
	list->last->next = newitem;
	list->last = newitem;
	list->count += 1;
}

////////////////////////////////////////////////////////////
// Alternative vector implementation
////////////////////////////////////////////////////////////

VECTOR *lvector(var x, var y, var z)
{
	if(lvectorStorage == NULL)
	{
		lvectorStorageSize = 1024;
		lvectorStorage = sys_malloc(lvectorStorageSize * sizeof(VECTOR));
	}
	if(lvectorLastFrame < total_frames)
	{
		lvectorStoragePointer = 0;
		lvectorLastFrame = total_frames;
	}
	
	int currentPos = lvectorStoragePointer;
	lvectorStoragePointer += 1;
	
	if(lvectorStoragePointer >= lvectorStorageSize)
	{
		VECTOR *oldLvectorStorage = lvectorStorage;
		int oldLvectorStorageSize = lvectorStorageSize;
		
		lvectorStorageSize += 1024;
		lvectorStorage = sys_malloc(lvectorStorageSize * sizeof(VECTOR));
		memcpy(lvectorStorage, oldLvectorStorage, sizeof(VECTOR) * oldLvectorStorageSize);
		
		sys_free(oldLvectorStorage);
	}
	
	lvectorStorage[currentPos].x = x;
	lvectorStorage[currentPos].y = y;
	lvectorStorage[currentPos].z = z;
	
	return &(lvectorStorage[currentPos]);
}

int lvector_usage()
{
	return sizeof(VECTOR) * lvectorStorageSize;
}

#endif