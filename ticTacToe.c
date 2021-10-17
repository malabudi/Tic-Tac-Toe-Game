#include <stdio.h>

// Function Prototypes
char askGamemode();
void displayBoard(char gameBoard[3][3]);
char selectLocation(char player, char gameBoard[3][3]);
int isSpotTaken(char location, char gameBoard[3][3]);      // Can make this function bool, but used int instead so I dont need to import the stdbool.h file
char setTurn(char gameBoard[3][3], char location, char player);
int checkForWin(char gameBoard[3][3], int moves);
char playAgain();
int miniMax();


int main()
{
	// Initialize/declare variables
	char gamemode;
	char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
	char location;
	char player = 'X';      // Initialize the first player to X, then switch to O for second player when necessary
	int moves = 0;
	int currentGame = 1;    // A bool that will switch off if the user is done playing
	char choice;


	// Call functions to begin the game
	gamemode = askGamemode();
    displayBoard(board);

    switch(gamemode)
    {
        // 2 Player
        case '1':
            while(currentGame)
            {
                location = selectLocation(player, board);

                player = setTurn(board, location, player);

                moves++;    // after the user or computer makes a valid move, increment

                currentGame = checkForWin(board, moves); // if the user wins, currentGame is false

                displayBoard(board);

                // Check if the user wants to play again after the game is finished
                if (currentGame == 0)
                {
                    // Ask the user if they want to play again after the game is over
                    choice = playAgain();

                    // if the user says yes, reset the game and start again
                    switch(choice)
                    {
                        case 'Y':
                            // reset board
                            board[0][0] = '1';
                            board[0][1] = '2';
                            board[0][2] = '3';
                            board[1][0] = '4';
                            board[1][1] = '5';
                            board[1][2] = '6';
                            board[2][0] = '7';
                            board[2][1] = '8';
                            board[2][2] = '9';

                            displayBoard(board);

                            player = 'X';   // reset player
                            moves = 0;      // reset moves made in game from both players
                            currentGame = 1;
                            fflush(stdin);  // Flush out any buffer in the input device
                            break;
                        case 'N':
                            printf("\nThank you for playing!");
                            return 0;
                    }
                }
            }
            break;
        // Playing against AI or Computer
        case '2':
            printf("\nSorry this feature is not yet available");
            break;
    }
	return 0;
}
//-----------------------------------------------------------------------------------------------------------
// User defined functions

// Ask if the user wants to play against an AI or another person
char askGamemode()
{
    char gameMode;

    // Ask the user what gamemode they want to play
    printf("------Tic Tac Toe------\n");
    printf("\nWould you like to play  2-Player or against a CPU?");
    printf("\n1 - 2 Payer");
    printf("\n2 - CPU\n");
    scanf("\n%c", &gameMode);

    // Validate input
    while (gameMode != '1' && gameMode != '2')
    {
        printf("\nInvalid input! Please enter either 1 - 2\n");

        printf("\nWould you like to play  2-Player or against a CPU?");
        printf("\n1 - 2 Payer");
        printf("\n2 - CPU\n");
        scanf("\n%c", &gameMode);
    }

    fflush(stdin);
    return gameMode;
}


// Display the tic tac toe board
void displayBoard(char gameBoard[3][3])
{
	int i, j;

	printf("\n-------------\n");

	for (i = 0; i < 3; i++) // Loop through outer array
	{
		for (j = 0; j < 3; j++) // With every index at outer array, loop through the inner array
			printf("| %c ", gameBoard[i][j]);

		printf("|\n-------------\n");
	}
}


char selectLocation(char player, char gameBoard[3][3])
{
	int i;
	char strLocation[3]; // save the location into a string for further validation
	char location;
	int isTaken;

	// ------- Grab input --------
	// Ask user to select location
	printf("\nPlease select your location player %c (1-9): ", player);

	// Grab the first three characters in the string
	fgets(strLocation, 3, stdin);

	// Flush out the buffer out of the input device
	fflush(stdin);

    // check if spot is already taken
	isTaken = isSpotTaken(strLocation[0], gameBoard);



	// --------------Data validation-----------------
	/* Check if the input is only a single character with an enter key at the
	second index in string, then check if that single character is 1-9*/
	while (strLocation[1] != '\n' || strLocation[0] < 49 || strLocation[0] > 57 || isTaken)
	{
	    // Display error message
		printf("\nInvalid Input! Please select a valid position.");

        // Allow user to enter location again
		printf("\nPlease select your location player %c: ", player);
		fgets(strLocation, 3, stdin);
		fflush(stdin);
		isTaken = isSpotTaken(strLocation[0], gameBoard);
	}

	return strLocation[0];
}


int isSpotTaken(char location, char gameBoard[3][3])
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
                return 0;
        }
	}

	return 1;
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


int checkForWin(char boardGame[3][3], int moves)
{
    int i;

    // If the player wins, return false indicating the game is finished and has a winner

    // Check rows for wins
    for (i = 0; i < 3; i++)
    {
        if ((boardGame[i][0] == 'X' && (boardGame[i][1] == 'X') && (boardGame[i][2] == 'X')))
        {
            printf("\n\nPlayer X wins!\n");
            return 0;
        }
        else if ((boardGame[i][0] == 'O' && (boardGame[i][1] == 'O') && (boardGame[i][2] == 'O')))
        {
            printf("\n\nPlayer O wins!\n");
            return 0;
        }
    }

    // Check columns
    for (i = 0; i < 3; i++)
    {
        if ((boardGame[0][i] == 'X' && (boardGame[1][i] == 'X') && (boardGame[2][i] == 'X')))
        {
            printf("\n\nPlayer X wins!\n");
            return 0;
        }
        else if ((boardGame[0][i] == 'O' && (boardGame[1][i] == 'O') && (boardGame[2][i] == 'O')))
        {
            printf("\n\nPlayer O wins!\n");
            return 0;
        }
    }

    // Check diagonals
    if ((boardGame[0][0] == 'X' && (boardGame[1][1] == 'X') && (boardGame[2][2] == 'X')))
        {
            printf("\n\nPlayer X wins!\n");
            return 0;
        }
    else if ((boardGame[0][0] == 'O' && (boardGame[1][1] == 'O') && (boardGame[2][2] == 'O')))
        {
            printf("\n\nPlayer O wins!\n");
            return 0;
        }
    else if ((boardGame[2][0] == 'X' && (boardGame[1][1] == 'X') && (boardGame[0][2] == 'X')))
        {
            printf("\n\nPlayer X wins!\n");
            return 0;
        }
    else if ((boardGame[2][0] == 'O' && (boardGame[1][1] == 'O') && (boardGame[0][2] == 'O')))
        {
            printf("\n\nPlayer O wins!\n");
            return 0;
        }

    // Check if it's a cats game
    if (moves == 9)
    {
        printf("\nIt is a cats game!\n");
        return 0;
    }
}


char playAgain()
{
    char choice;

    // Ask the user to play again
    printf("\nWould you like to play again? (Y/N): ");
    scanf("\n%c", &choice);


    // turn the user choice character into uppercase if lowercase
    if (choice > 96 && choice < 123)
            choice -= 32;

    // Validate the user's choice to play again
    while (choice != 'N' && choice != 'Y')
    {
        printf("\nInvalid input, please enter Y or N.");

        printf("\nWould you like to play again? (Y/N): ");
        scanf("\n%c", &choice);

        if (choice > 96 && choice < 123)
            choice -= 32;
    }

    return choice;
}


int miniMax()
{
    return 1;
}
