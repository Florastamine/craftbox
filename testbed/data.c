#include <acknex.h>
#include <default.c>

STRING *s[5];
STRING **s_ptr;

void main(void) {
	
	s_ptr = s;
	
	var f = file_open_read("f.txt");
	if(f == 0) sys_exit(NULL);
	
	int i;
	for(i = 0;i < 5;i++) {
		
		s[i] = str_create("#255");
		file_str_read(f,s[i]);
		
	}
	
	file_close(f);
	
	int i;
	for(i = 0;i < 5;i++) error(s_ptr[i]);
	
}