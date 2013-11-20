#ifndef dof_c
#define dof_c

float dofTapping = 1;

float dofNearPlane  = 100;
float dofFocalBegin = 300;
float dofFocalEnd   = 300;
float dofFarPlane   = 1300;

BOOL dofActive = false;

MATERIAL* mtlDofCombine = {
	effect = "dof_combine.fx";
	flags = ENABLE_VIEW;
}

VIEW* viewDofCombine = {
	flags = PROCESS_TARGET | CHILD;
	material = mtlDofCombine;
}

MATERIAL* mtlDofBlur = {
	effect = "dof_blur.fx";
	flags = ENABLE_VIEW;
}

VIEW* viewDofBlur = {
	flags = PROCESS_TARGET | CHILD;
	material = mtlDofBlur;
	stage = viewDofCombine;
}

// Asserts that a target bmap is allocated and has a specific size (is deter-
// mined as <screen_size.xy> divided by <lodRatio>
void dofAssertScreenSizedBmap (BMAP** bmap, int format, int lodRatio)
{
	if (*bmap != NULL) // check bitmap
	{
		// check dimensions of bitmap against screen size to detect a changed screen resolution
		if (((*bmap)->width != (int)screen_size.x / lodRatio) || ((*bmap)->height != (int)screen_size.y / lodRatio))
		{
			ptr_remove(*bmap); // remove bitmap from memory
			*bmap = NULL; // nullify bitmap
		}
	}

	// (re-)create bitmap if not allocated or removed due to resolution change
	if (*bmap == NULL) {
		*bmap = bmap_createblack((int)screen_size.x / lodRatio, (int)screen_size.y / lodRatio, format);
	}
}

void dofAssertBitmaps ()
{
	dofAssertScreenSizedBmap(&(viewDofBlur->bmap), 888, 2);
}

void dofUpdateChain ()
{
	if (dofActive)
	{
		setSsaoContext(NULL, viewDofBlur);
		
		mtlDofBlur->skin1 = getSsaoCombineMap();
		
		mtlDofCombine->skin1 = getSsaoCombineMap();
		mtlDofCombine->skin2 = viewDofBlur->bmap;
		mtlDofCombine->skin3 = getSsaoFullDepthMap();
	}
}

void dofRecreateTargetsEvent ()
{
	dofAssertBitmaps();
	dofUpdateChain();
}

void dofShowSsaoEvent ()
{
	dofRecreateTargetsEvent();
}

void dof ()
{
	dofActive = true;
	
	dofAssertBitmaps();
	dofUpdateChain();

	on_ssaoTargetRecreated = dofRecreateTargetsEvent;
	on_ssaoDeactivated = dofUpdateChain;
	on_ssaoActivated = dofShowSsaoEvent;
}

void toggleDof ()
{
	if (dofActive)
		setSsaoContext(NULL, NULL); 
	else
		setSsaoContext(NULL, viewDofBlur);
		
	dofActive = !dofActive;
	
	dofUpdateChain();
}

#endif /* dof_c */