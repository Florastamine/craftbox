#include <acknex.h>
#include <default.c>

BMAP *mouse = "../main/2d/gui/arrow.pcx";

var test;

PANEL *background = {
	
	layer = 1;
	
	bmap = "rain.jpg";
	flags = SHOW;
	
}

TEXT *start = {
	
	layer = 2;
	string("Start =))");
	pos_x = 25;
	pos_y = 25;
	font = "Arial#25b";
	flags = SHOW;
	
}

PANEL *big_in = {
	
	layer = 2;
	bmap = "panObj_etc.bmp";
	
	button(0,0,"panObj_button.bmp","panObj_button.bmp","panObj_button.bmp",NULL,NULL,NULL);
	button(0,0,"panObj_button.bmp","panObj_button.bmp","panObj_button.bmp",NULL,NULL,NULL);
	button(0,0,"panObj_button.bmp","panObj_button.bmp","panObj_button.bmp",NULL,NULL,NULL);
	button(0,0,"panObj_button.bmp","panObj_button.bmp","panObj_button.bmp",NULL,NULL,NULL);
	button(0,0,"panObj_button.bmp","panObj_button.bmp","panObj_button.bmp",NULL,NULL,NULL);
	button(0,0,"panObj_button.bmp","panObj_button.bmp","panObj_button.bmp",NULL,NULL,NULL);
	button(0,0,"panObj_button.bmp","panObj_button.bmp","panObj_button.bmp",NULL,NULL,NULL);
	button(0,0,"panObj_button.bmp","panObj_button.bmp","panObj_button.bmp",NULL,NULL,NULL);
	button(0,0,"panObj_button.bmp","panObj_button.bmp","panObj_button.bmp",NULL,NULL,NULL);
	button(0,0,"panObj_button.bmp","panObj_button.bmp","panObj_button.bmp",NULL,NULL,NULL);
	button(0,0,"panObj_button.bmp","panObj_button.bmp","panObj_button.bmp",NULL,NULL,NULL);
	button(0,0,"panObj_button.bmp","panObj_button.bmp","panObj_button.bmp",NULL,NULL,NULL);
	button(0,0,"panObj_button.bmp","panObj_button.bmp","panObj_button.bmp",NULL,NULL,NULL);
	button(0,0,"panObj_button.bmp","panObj_button.bmp","panObj_button.bmp",NULL,NULL,NULL);
	button(0,0,"panObj_button.bmp","panObj_button.bmp","panObj_button.bmp",NULL,NULL,NULL);
	button(0,0,"panObj_button.bmp","panObj_button.bmp","panObj_button.bmp",NULL,NULL,NULL);
	button(0,0,"panObj_button.bmp","panObj_button.bmp","panObj_button.bmp",NULL,NULL,NULL);
	button(0,0,"panObj_button.bmp","panObj_button.bmp","panObj_button.bmp",NULL,NULL,NULL);
	button(0,0,"panObj_button.bmp","panObj_button.bmp","panObj_button.bmp",NULL,NULL,NULL);
	button(0,0,"panObj_button.bmp","panObj_button.bmp","panObj_button.bmp",NULL,NULL,NULL);
	button(0,0,"panObj_button.bmp","panObj_button.bmp","panObj_button.bmp",NULL,NULL,NULL);
	button(0,0,"panObj_button.bmp","panObj_button.bmp","panObj_button.bmp",NULL,NULL,NULL);
	button(0,0,"panObj_button.bmp","panObj_button.bmp","panObj_button.bmp",NULL,NULL,NULL);
	button(0,0,"panObj_button.bmp","panObj_button.bmp","panObj_button.bmp",NULL,NULL,NULL);
	button(0,0,"panObj_button.bmp","panObj_button.bmp","panObj_button.bmp",NULL,NULL,NULL);
	button(0,0,"panObj_button.bmp","panObj_button.bmp","panObj_button.bmp",NULL,NULL,NULL);
	button(0,0,"panObj_button.bmp","panObj_button.bmp","panObj_button.bmp",NULL,NULL,NULL);
	button(0,0,"panObj_button.bmp","panObj_button.bmp","panObj_button.bmp",NULL,NULL,NULL);
	button(0,0,"panObj_button.bmp","panObj_button.bmp","panObj_button.bmp",NULL,NULL,NULL);
	button(0,0,"panObj_button.bmp","panObj_button.bmp","panObj_button.bmp",NULL,NULL,NULL);
	button(0,0,"panObj_button.bmp","panObj_button.bmp","panObj_button.bmp",NULL,NULL,NULL);
	button(0,0,"panObj_button.bmp","panObj_button.bmp","panObj_button.bmp",NULL,NULL,NULL);
	button(0,0,"panObj_button.bmp","panObj_button.bmp","panObj_button.bmp",NULL,NULL,NULL);
	button(0,0,"panObj_button.bmp","panObj_button.bmp","panObj_button.bmp",NULL,NULL,NULL);
	button(0,0,"panObj_button.bmp","panObj_button.bmp","panObj_button.bmp",NULL,NULL,NULL);
	button(0,0,"panObj_button.bmp","panObj_button.bmp","panObj_button.bmp",NULL,NULL,NULL);
	button(0,0,"panObj_button.bmp","panObj_button.bmp","panObj_button.bmp",NULL,NULL,NULL);
	button(0,0,"panObj_button.bmp","panObj_button.bmp","panObj_button.bmp",NULL,NULL,NULL);
	button(0,0,"panObj_button.bmp","panObj_button.bmp","panObj_button.bmp",NULL,NULL,NULL);
	button(0,0,"panObj_button.bmp","panObj_button.bmp","panObj_button.bmp",NULL,NULL,NULL);
	button(0,0,"panObj_button.bmp","panObj_button.bmp","panObj_button.bmp",NULL,NULL,NULL);
	button(0,0,"panObj_button.bmp","panObj_button.bmp","panObj_button.bmp",NULL,NULL,NULL);
	button(0,0,"panObj_button.bmp","panObj_button.bmp","panObj_button.bmp",NULL,NULL,NULL);
	button(0,0,"panObj_button.bmp","panObj_button.bmp","panObj_button.bmp",NULL,NULL,NULL);
	button(0,0,"panObj_button.bmp","panObj_button.bmp","panObj_button.bmp",NULL,NULL,NULL);
	button(0,0,"panObj_button.bmp","panObj_button.bmp","panObj_button.bmp",NULL,NULL,NULL);
	button(0,0,"panObj_button.bmp","panObj_button.bmp","panObj_button.bmp",NULL,NULL,NULL);
	button(0,0,"panObj_button.bmp","panObj_button.bmp","panObj_button.bmp",NULL,NULL,NULL);
	button(0,0,"panObj_button.bmp","panObj_button.bmp","panObj_button.bmp",NULL,NULL,NULL);
	//button(0,0,"panObj_button.bmp","panObj_button.bmp","panObj_button.bmp",NULL,NULL,NULL);
	
	flags = OVERLAY | SHOW;
	
}

PANEL *slider = {
	
	layer = 2;
	bmap = "big_slider.bmp";
	hslider(0,0,800,"slider.tga",0,100,test);
	digits(0,50,99,"Arial#25b",1,test);
	
	flags = OVERLAY | SHOW;
	
}

void main(void) {
	
	video_set(800,600,32,1);
	mouse_mode = 2;
	mouse_map = mouse;
	
	level_load("");
	
	big_in.pos_x = 0;
	big_in.pos_y = (screen_size.y - bmap_height(big_in.bmap))/2;
	
	slider.pos_x = 0;
	slider.pos_y = bmap_height(big_in.bmap) + 200;
	
	background.pos_x=0;
	background.pos_y=0;
	background.scale_x = big_in.scale_x;
	background.scale_y = screen_size.y/bmap_height(background.bmap);
	
	int i;
	for(i = 1;i <= 50;i++) {
		
		pan_setpos(big_in,3,i,vector(10*i + 56*(i-1),10,0));
		
	}
	
	while(1) {
		
		vec_set(mouse_pos,mouse_cursor);
		
		big_in.pos_x = (test * (-bmap_width(big_in.bmap) + screen_size.x))/100;
		background.pos_x = -test*2;
		
		if(key_cul) test--;
		if(key_cur) test++;
		
		if(test<0) test=0; // prevent unexpected situations
		if(test>100) test=100;
		
		if(big_in.pos_x > 0) big_in.pos_x = 0;
		if(big_in.pos_x < -bmap_width(big_in.bmap) + screen_size.x) {
			
			big_in.pos_x = -bmap_width(big_in.bmap) + screen_size.x;
			
		}
		
		wait(1);
		
	}
}