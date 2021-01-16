#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int indexOf( const char *cmd, char el, int from ) {
	for( int i = from; i < strlen( cmd ); i++) {
		if( cmd[i] == el) {
			return i;
		}
	}
	return -1;
}
int input( char *cmd ) {
	int i = 0;
	do {
		cmd[i] = getchar();
	} while( cmd[i++] != '!' );
	cmd[i] = '\0';
	return i - 1;
}
int main() {
	char *cmd = calloc( 0, sizeof( char ) );
	int LpIndex = 0;
	int data[32];
	unsigned int ptr = 0;
	unsigned int i = 0;
	input( cmd );
	do {
		if( cmd[i] == '<' ) {
			ptr--;
		}
		if( cmd[i] == '>' ) {
			ptr++;
		}
		else if( cmd[i] == '+' ) {
			data[ptr]++;
		}
		else if( cmd[i] == '-' ) {
			data[ptr]--;
		}
		else if( cmd[i] == '[' & data[ptr] == 0 ) {
			LpIndex = i;
			i = indexOf( cmd, ']', i + 1 ) + 1;
		}
		else if( cmd[i] == ']' & data[ptr] != 0 ) {
			i = LpIndex + 1;
		}
		else if( cmd[i] == '.' ) {
			printf( "O> %c\n", data[ptr] );
		}
		else if( cmd[i] == ',' ) {
			scanf( "%d", &data[ptr] );
		}
	} while( cmd[i++] != '!' );
	free(cmd);
}