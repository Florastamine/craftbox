#include <acknex.h>
#include "../main/ka7def2.c"

typedef struct stupid {
   
   STRING *str;
   
} stupid;

STRING *t = "                   ";

TEXT *tx = {
   string(t);
   pos_x=0;
   pos_y=0;
   flags=SHOW;
}

void copy(stupid *, STRING *);

stupid st;

void main(void) {
   
   copy(st,"wtwrutu");
   
	
}

void copy(stupid *st, STRING *strs) {
   st.str = str_create("#400");
   
   str_cpy(st.str,strs);
}