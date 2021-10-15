#include <stdio.h>

// Function protoypes
void displayBoard(char gameBoard[3][3]);
char selectLocation(char location);

int main()
{
	/*
	Board:
	1 2 3
	4 5 6
	7 8 9
	*/
	// Initialize/declare variables
	char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
	char location;
	
	// Call functions
	displayBoard(board);
	selectLocation(location);
	
	printf("\n%c", location);
	
	return 0;
}
//----------------------------------------------------------------------------

// User defined functions
void displayBoard(char gameBoard[3][3])
{
	int i, j;
	
	for (i = 0; i < 3; i++) // Loop through outer array
	{
		for (j = 0; j < 3; j++) // With every index at outer array, loop through the inner array
			printf("%c   ", gameBoard[i][j]);
		
		printf("\n\n");
	}
}

char selectLocation(char location)
{
	int i;
	char strLocation[3]; // save the location into a string for further validation
	
	printf("\nPlease select your location: ");
	fgets(strLocation, 3, stdin); // Grab the first three characters in the string
	fflush(stdin); // Flush out the buffer out of the input device
	
	for (i = 0; i < 3; i++)
		printf("#%d# ", strLocation[i]);
		
		
	// Data validation
	// Check if the input is only a single character
	while (strLocation[1] != '\n')
	{
		printf("\nPlease enter only one digit");
		
		for (i = 0; i < 3; i++)
			printf("#%d# ", strLocation[i]);
		
		printf("\nPlease select your location: ");
		fgets(strLocation, 3, stdin);
	}
	
	// location out of range of the board	
	while (strLocation[0] < 49 || strLocation[0] > 57)
	{
		printf("\nInvalid input!");
		
		printf("\nPlease select your location: ");
		fgets(strLocation, 3, stdin);
	}
	
	// check for spots taken
	while (strLocation[0] == 'O' || strLocation[0] == 'X')
	{
		printf("\nThis spot is already taken!");
		
		printf("\nPlease select your location: ");
		fgets(strLocation, 3, stdin);
	}
	
	return location;
}

void setTurn(char location)
{
	/*
	grab location char, match it with board 2D array, set that choice as X or O
	*/
}
