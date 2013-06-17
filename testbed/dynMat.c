#include <acknex.h>
#include <default.c>

MATERIAL *m;

void main(void) {
   
   m = mtl_create();
   
   m.emissive_blue = 100;
   m.specular_red = 75;
   m.power = 5;
   
   wait(1);
}