extern int dotp(short *m, short *n, int u);
#include <stdio.h>
#include "data.h"
#define COUNT 256
short a[256] = {A_ARRAY};
short x[256] = {X_ARRAY};
int y = 0;
/* Main Code */
main()
{	
	int k = 0;
	y = dotp(a, x, COUNT);
	printf("y = %x hex (%d decimal)\n", y, y);
	k+=1;
}