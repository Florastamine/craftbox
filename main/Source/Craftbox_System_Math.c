VECTOR *vec_form(VECTOR *v1, VECTOR *v2) {
	
	VECTOR *v3 = nullvector;
	v3.x = v2.x - v1.x;
	v3.y = v2.y - v1.y;
	v3.z = v2.z - v1.z;
	
	return v3;
	
}

VECTOR *_vec_add(VECTOR *v1, VECTOR *v2) {
	
	VECTOR *v3 = nullvector;
	v3.x = v1.x + v2.x;
	v3.y = v1.y + v2.y;
	v3.z = v1.z + v2.z;
	
	return v3;
	
}

VECTOR *_vec_sub(VECTOR *v1, VECTOR *v2) {
	
	VECTOR *v3 = nullvector;
	v3.x = v1.x - v2.x;
	v3.y = v1.y - v2.y;
	v3.z = v1.z - v2.z;
	
	return v3;
	
}

VECTOR *_vec_scale(VECTOR *vektor, float scale) {
	
	VECTOR *v3 = nullvector;
	v3.x = scale * vektor.x;
	v3.y = scale * vektor.y;
	v3.z = scale * vektor.z;
	
	return v3;
	
}

float _vec_length(VECTOR *vektor) {
	
	return sqrt(pow(vektor.x,2) + pow(vektor.y,2) + pow(vektor.z,2));
	
}

float _vec_dot(VECTOR *v1, VECTOR *v2) { // Tich vo huong
	
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
	
}

float _vec_ang(VECTOR *a, VECTOR *b) {
	
	return( acosv(
	
	_vec_dot(a,b)/ // Tich vo huong
	(_vec_length(a) * _vec_length(b)) // Tich do dai
	
	));
	
}

VECTOR *vec_center(VECTOR *a, VECTOR *b) {
   
   VECTOR *c = nullvector;
   c.x = (a.x + b.x)/2;
   c.y = (a.y + b.y)/2;
   c.z = (a.z + b.z)/2;
   
   return c;
   
}

VECTOR *_vec_cross(VECTOR *a, VECTOR *b) {
   
   // [a;b]
   VECTOR *c = nullvector;
   c.x = a.x * b.z - b.x * a.z;
   c.y = a.y * b.z - b.y * a.z;
   c.z = a.x * b.y - b.x * a.y;
   
   return c;
   
}

int vec_same_plane(VECTOR *a, VECTOR *b, VECTOR *c, VECTOR *d) {
   
   // Forms three vectors for calculation
   VECTOR *ab = vec_form(a,b);
   VECTOR *ac = vec_form(a,c);
   VECTOR *ad = vec_form(a,d);
   
   if(_vec_dot(_vec_cross(ab,ac),ad)) return 1;
   
   return 0;
   
}