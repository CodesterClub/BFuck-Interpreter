#include <stdio.h>            // For printf() and getchar()
#include <stdlib.h>           // For calloc() 
#include <string.h>           // For strlen()
/* 
 * This method returns next index of an integer
 * 
 * char *cmd creates a read-only string (rather array) of characters.
 * char *cmd creates a reference to the [0]th posn of the string only.
 * End of string is marked by (char) 0. 'cmd' stores the address of the 
 * 0th memory location of the string, while '*cmd' stores the reference. 
 * Hence strings are passed as a reference to methods.
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
 * 
 * NOTE that printf ( "%s", cmd ); prints the whole string
 * BUT printf( "%c", *cmd ); only prints the 0th character
 */
// Index of loop start posn in bfuck code
unsigned int LpIndex = 0;
// Data array to store bfuck I/O
signed short int data[32] = {0};
// Unsigned means that range of values stored is from 0 to 2^(n-1), n is size in bits
// Data pointer that is used to select an index from data array and operate on it.
unsigned int ptr = 0;
// 1 if nested
unsigned short int nested;
int indexOf( char *cmd, char el, int from ) {
	unsigned int braceCount = 0;
	// Usual for loop, strlen() is 'string length'
	for( int i = from; i < strlen( cmd ); i++) {
		// This cmd[i] is previously explained
		if( cmd[i] == '[' ) {
			braceCount++;
			nested = 1;
		}
		else if( cmd[i] == ']' & braceCount != 0 ) {
			braceCount--;
		}
		else if( cmd[i] == el & braceCount == 0 ) {
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
	} while( cmd[i++] != '\n' );
	/* 
	 * If you didn't know, now you do. All strings must end 
	 * with a null character in C. The beginning is marked by address 
	 * stored in cmd. But the end must be marked by a null character. 
	 * Otherwise two strings in memory may get mixed up. As a result, 
	 * a string has one extra memory block at the end, making its
	 * length l + 1.
	 */
	cmd[i--] = '\0';
	return i;
}
void interpret( char *cmd ) {
	char *cmdCOPY = calloc(1, sizeof( char ) );
	// Instruction pointer traverses the cmd array
	unsigned int i = 0, j = i, k = j;
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
			int clsIndex = indexOf( cmd, ']', i + 1 ) + 1;
			// If nested bf loop
			if( nested ) {
				// Copying string to remove reference
				for( j = 0, k = LpIndex; j < i - LpIndex; j++, k++ ) {
					cmdCOPY[j] = cmd[k];
				}
				cmdCOPY[j] = 0;
				interpret( cmdCOPY );
			}
			if( data[ptr] == 0 ) {
				i = clsIndex;
			}
		}
		else if( cmd[i] == ']' & data[ptr] != 0 ) {
			i = LpIndex;
		}
		else if( cmd[i] == '.' ) {
			printf( "O> %c\n", data[ptr] );
		}
		else if( cmd[i] == ',' ) {
			printf( "I> " );
			scanf( "%hd", &data[ptr] );
		}
	} while( cmd[i++] != '\0' );
	free( cmdCOPY );
}
int main() {
	/*
	 * calloc( 0, sizeof( char ) ): 0 is no. of memory blocks the string cmd will 
	 * initially have. sizeof is NOT a function but an operator that returns in bytes 
	 * the memory occupied by its operand. The operand may be a variable, or a data type.
	 * The 2nd argument of calloc() is the size of each memory block.
	 * 
	 * calloc() automatically increases no. of memory blocks as required during runtime.
	 * C has no new keyword. Dynamic allocation of memory is done by malloc() or calloc().
	 */
	// Command array that takes in the bfuck code in whole
	char *cmd = calloc( 1, sizeof( char ) );
	// Take input using our custom function
	input( cmd );
	// Read bfuck rules if you don't know them.
	interpret( cmd );
	/* 
	 * This frees up the memory allocated by calloc().
	 * In our case since the program ends here, free() is not necessary 
	 * as the system deletes the memory occupied by our program once 
	 * execution ends.
	 * But in case we had multiple arrays/strings allocated dynamically 
	 * and we had huge data input in them and we had a huge code where 
	 * not all of them would be necessary, we will actually be wasting memory.
	 * 
	 * Also say we assign one array A to another array B as B = A. That means 
	 * now B points to memory of A. But what happens to older memory of B?
	 * In java, the garbage collector clears this automatically. In C, we must 
	 * first free B using free(B), then we must do B = A;
	 * 
	 * Hence it is a good practice to free up memory when you realise you no longer 
	 * need them in C.
	 */
	free(cmd);
}
