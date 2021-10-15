#include <stdio.h>
#include <stdbool.h>

// Function Prototypes
void displayBoard(char gameBoard[3][3]);
char selectLocation(char player, char gameBoard[3][3]);
bool isSpotTaken(char location, char gameBoard[3][3]);
char setTurn(char gameBoard[3][3], char location, char player);


int main()
{
	// Initialize/declare variables
	char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
	char location = '1';
	char player = 'X'; // Initialize the first player to X, then switch to O for second player when necessary

	// Call functions
	while(1 < 2)
    {
        displayBoard(board);

        location = selectLocation(player, board);

        player = setTurn(board, location, player);
    }


	return 0;
}
//-----------------------------------------------------------------------------------------------------------



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



char selectLocation(char player, char gameBoard[3][3])
{
	int i;
	char strLocation[3]; // save the location into a string for further validation
	char location;
	bool isTaken;

	// ------- Grab input --------
	printf("\nPlease select your location player %c: ", player);

	// Grab the first three characters in the string
	fgets(strLocation, 3, stdin);

	// Flush out the buffer out of the input device
	fflush(stdin);

    // check if spot is already taken
	isTaken = isSpotTaken(strLocation[0], gameBoard);



	// Data validation
	/* Check if the input is only a single character with an enter key at the
	second index in string, then check if that single character is 1-9*/
	while (strLocation[1] != '\n' || strLocation[0] < 49 || strLocation[0] > 57 || isTaken)
	{
	    // Display error message
		printf("\nInvalid Input! Please select 1-9");

        // Allow user to enter location again
		printf("\nPlease select your location: ");
		fgets(strLocation, 3, stdin);
		fflush(stdin);
		isTaken = isSpotTaken(strLocation[0], gameBoard);
	}

	// After validation, return location
	location = strLocation[0];

	return location;
}



bool isSpotTaken(char location, char gameBoard[3][3])
{
    /* Initialize the variable to be true so in case the spot that the user chose is free
    we can just set isTaken to false*/
    int i, j;

    // Check if chosen location is available
    for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
        {
            if (location == gameBoard[i][j])
                return false;
        }
	}

	return true;
}



char setTurn(char gameBoard[3][3], char location, char player)
{
	int i, j;

	// Set the proper location that the player chose in the 2D array
	for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (location == gameBoard[i][j])
                gameBoard[i][j] = player;
        }
    }

    // Switch the turn of the player after their turn is finished
    switch(player)
    {
        case 'X':
            player = 'O';
            break;
        case 'O':
            player = 'X';
            break;
    }

    return player;
}
