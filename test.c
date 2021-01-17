#include <stdio.h>
int main() {
	char a[32];
	a[0] = getchar();
	a[1] = 0;
	printf( "%c", a[0] );
	return 0;
}