#include <default.c>

// create a path from 4 points, and let a sphere follow it
void main()
{  
	max_paths = 1;
  level_load(0);
  me = ent_create(SPHERE_MDL,NULL,NULL);
  vec_scale(my.scale_x,5);
  vec_set(my.blue,vector(0,255,255));
  my.flags |= LIGHT;

  path_create(me,4,4);
  path_setnode(me,1,vector(500,250,-100),NULL);
  path_setnode(me,2,vector(500,-250,-100),NULL);
  path_setnode(me,3,vector(1000,-250,100),NULL);
  path_setnode(me,4,vector(1000,250,100),NULL);
  
  var distance = 0;
  while(1){
    path_spline(me,my.x,distance += 20*time_step);
    wait(1);
  }
}