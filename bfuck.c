#include <stdio.h>            // For printf() and getchar()
#include <stdlib.h>           // For calloc() 
#include <string.h>           // For strlen()
/* 
 * This method returns next index of an integer
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
		i++;
	} while( cmd[i] != '!' | cmd[i] != '\n' );
	/* 
	 * If you didn't know, now you do. All strings must end 
	 * with a null character in c. The beginning is marked by address 
	 * stored in cmd. But the end must be marked by a null character. 
	 * Otherwise two strings in memory may get mixed up. As a result, 
	 * a string has one extra memory block at the end.
	 */
	cmd[i] = '\0';
	return i - 1;
}
int main() {
	/*
	 * calloc( 0, sizeof( char ) ): 0 is no. of memory blocks the string cmd will 
	 * initially have. sizeof is NOT a function but an operator that returns in bytes 
	 * the memory occupied by its operand. The operand may be a variable, or a data type.
	 * The 2nd argument of calloc() is the size of each memory block.
	 * 
	 * calloc() automatically increases no. of memory blocks as required during runtime.
	 * C has no new keyword. Dynamic allocation if memory is done by malloc() or calloc().
	 */
	// Command array that takes in the bfuck code in whole
	char *cmd = calloc( 0, sizeof( char ) );
	// Index of loop start posn in bfuck code
	int LpIndex = 0;
	// Data array to store bfuck I/O
	signed char data[32] = {0};
	// Unsigned means that range of values stored is from 0 to 2^(n-1), n is size in bits
	// Data pointer that is used to select an index from data array and operate on it.
	unsigned int ptr = 0;
	// Instruction pointer traverses the cmd array
	unsigned int i = 0;
	// Take input using our custom function
	input( cmd );
	// Read bfuck rules if you don't know them.
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
		// Work incomplete from here
		else if( cmd[i] == '[' ) {
			LpIndex = i;
			if( data[ptr] == 0 ) {
				i = indexOf( cmd, ']', i + 1 ) + 1;
			}
		}
		else if( cmd[i] == ']' & data[ptr] != 0 ) {
			i = LpIndex + 1;
		}
		else if( cmd[i] == '.' ) {
			printf( "O> %c\n", data[ptr] );
		}
		else if( cmd[i] == ',' ) {
			prinf( "I> " );
			data[ptr] = getchar();
			data[ptr+1] = '\0';
		}
	} while( cmd[i++] != '!' );
	/* 
	 * This frees up the memory allocated by calloc().
	 * In our case since the program ends here, free() is not necessary 
	 * as the system deletes the memory occupied by our program once 
	 * execution ends.
	 * But in case we had multiple arrays/strings allocated dynamically 
	 * and we had huge data inout in them and we had a huge code where 
	 * not all of them would be necessary, we will actually be wasting memory.
	 * 
	 * Also say we assign one array B to another array A as B = A. That means 
	 * now B points to memory of A. But what happens to older memory of A?
	 * In java, the garbage collector clears this automatically. In c, we must 
	 * first free A using free(A) the we must do B = A;
	 * 
	 * Hence it is a good practice to free up memory when you realise you no longer 
	 * need them in C.
	 */
	free(cmd);
}