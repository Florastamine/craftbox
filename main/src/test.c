#include <default.c>

TEXT *music = {
   
   string("#50","#50","#50","#50","#50");
   pos_x=0;pos_y=0;
   font="arial#15b";
   flags=SHOW;
   
}

PANEL *panel = {
   
   bmap="ell_c02_01a.bmp";
   flags=OVERLAY | SHOW;
}

void main(void) {
   
   video_set(800,600,32,1);
   level_load(NULL);
   
   /*
   txt_for_dir(music,"..\\sounds\\music\\*.ogg");
   
   STRING *tmp = str_create("#400");
   str_cpy(tmp,str_create("..\\sounds\\music\\"));
   str_cat(tmp,(music.pstring)[0]);
   
   media_play(tmp,NULL,100);
   */
   
}