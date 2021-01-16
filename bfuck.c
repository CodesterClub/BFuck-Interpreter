#include <stdio.h>            // For printf() and scanf()
#include <stdlib.h>           // For malloc() and calloc() 
#include <string.h>           // For strcmp() and strlen()

/* This method returns next index of an integer
 * 
 * char *cmd creates a reference to the [0]th posn of the string 
 * passed in, which means, cmd stores the value of its memory address, 
 * while *cmd stores the reference. Hence strings are passed as a 
 * reference to methods.
 * 
 * Why char? 
 * Because C has no string data type. *cmd indicates only one memory 
 * location, also denoted by cmd[0]. Note that in this case we don't 
 * use the *. *cmd is same as cmd[0].
 * 
 * On doing cmd[i], we access the address at RAM[cmd + i]. As it's 
 * said previously, printing cmd gives the address as a hex. printing 
 * cmd[0] gives the value at 0th. cmd[i] gives value i places beyond 
 * cmd.
 */
int indexOf( char *cmd, char el, int from ) {
	// Usual for loop, strlen() is 'string length'
	for( int i = from; i < strlen( cmd ); i++) {
		// This cmd[i] is previously explained
		if( cmd[i] == el) {
			return i;
		}
	}
	return -1;
}
// Same as first method, we take in a string
int input( char *cmd ) {
	int i = 0;
	// We assign ith posn of cmd to one single character input
	do {
		// getchar() gets next character from input stream
		cmd[i] = getchar();
	} while( cmd[i++] != '!' );
	/* If you didn't know, now you do. All strings must end 
	 * with a null character in c. The beginning is marked by address 
	 * stored in cmd. But the end must be marked by a null character. 
	 * Otherwise two strings in memory may get mixed up. As a result, 
	 * a string has one extra memory block at the end.
	 */
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