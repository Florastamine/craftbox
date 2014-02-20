#ifndef Craftbox_System_Scene

#define Craftbox_System_Scene

/*
--------------------------------------------------
Craftbox_System_Scene.c

Provides basic scene optimization methods.

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
void OptimizeFramerate(var dfr)

Desc: Continuously removing entities in the current view 
until the frame rate equals to or larger than dfr (desired frame rate).

This function should be used with caution because we don't want 
a beautiful green forest to be destroyed just to get a playable 60 fps.

Returns: -
--------------------------------------------------
*/
void OptimizeFramerate(var dfr) {

	WriteLog("[ ] Optimizing frame rate...");
	NewLine();

	WriteLog("[X] Task completed.");
	NewLine();

}

#endif