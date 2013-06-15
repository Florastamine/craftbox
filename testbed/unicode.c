#include <acknex.h>
#include <default.c>

TEXT* substr;

void main() {
   substr = txt_create(256,1);
   substr.font = font_create("#30"); // Unicode text
   txt_loadw(substr,"subtxt.txt");
   substr.pos_x = 25;
   substr.pos_y = substr.pos_x;
   
   level_load("");
   wait(1);
   
   set(substr,SHOW);
}