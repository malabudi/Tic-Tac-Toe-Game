#include <stdio.h>

// Function Prototypes
char askGamemode();
void displayBoard(char gameBoard[3][3]);
void resetBoard(char gameBoard[3][3]);
char switchPlayer(char player);
char selectLocation(char player, char gameBoard[3][3]);
int isSpotTaken(char location, char gameBoard[3][3]);      // Can make this function bool, but used int instead so I dont need to import the stdbool.h file
char setTurn(char gameBoard[3][3], char location, char player);
int checkForWin(char gameBoard[3][3]);
void displayWinner(int winner);
char playAgain();
int miniMax(char board[3][3], int depth, int isMaximizing);
void getBestMove(char board[3][3]);


int main()
{
	// Initialize/declare variables
	char gamemode;
	char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
	char location;
	char player = 'X';      // Initialize the first player to X, then switch to O for second player when necessary
	int moves = 0;
	int currentGame = 1;    // A bool that will switch off if the user is done playing
	char choicePlayAgain;


	// Call functions to begin the game
	gamemode = askGamemode();
    //displayBoard(board);

    switch(gamemode)
    {
        // 2 Players
        case '1':
            // Display the board to the user before while loop
            displayBoard(board);

            while(currentGame)
            {
                location = selectLocation(player, board);

                player = setTurn(board, location, player);

                currentGame = checkForWin(board); // if the user wins, currentGame is false

                displayBoard(board);

                // Check if the user wants to play again after the game is finished
                if (currentGame == 0 || currentGame == 10 || currentGame == -10)
                {
                    // Display the winner
                    displayWinner(currentGame);

                    // Ask the user if they want to play again after the game is over
                    choicePlayAgain = playAgain();

                    // if the user says yes, reset the game and start again
                    switch(choicePlayAgain)
                    {
                        case 'Y':
                            // reset board
                            resetBoard(board);

                            displayBoard(board);

                            player = 'X';   // reset player
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

        // Playing against CPU
        case '2':

            displayBoard(board);

            while (currentGame)
            {
                getBestMove(board);

                displayBoard(board);

                printf("\nThe CPU has made their move.\n");

                currentGame = checkForWin(board); // Check if there is a win from the AI


                // Ask the user if they want to play again if they lose to the AI
                if (currentGame == 0 || currentGame == 10 || currentGame == -10)
                {
                    // Display the winner
                    displayWinner(currentGame);

                    // Ask the user if they want to play again after the game is over
                    choicePlayAgain = playAgain();

                    // if the user says yes, reset the game and start again
                    switch(choicePlayAgain)
                    {
                        case 'Y':
                            // reset board
                            resetBoard(board);

                            displayBoard(board);

                            player = 'X';   // reset player
                            currentGame = 1;
                            fflush(stdin);  // Flush out any buffer in the input device
                            break;
                        case 'N':
                            printf("\nThank you for playing!");
                            return 0;
                    }

                    continue;
                }


                // Switch player after the move is done
                player = switchPlayer(player);

                location = selectLocation(player, board);

                player = setTurn(board, location, player);

                currentGame = checkForWin(board); // Check if there is a win from the human

                displayBoard(board);


                // Check if the user wants to play again after the human wins
                if (currentGame == 0 || currentGame == 10 || currentGame == -10)
                {
                    // Display the winner
                    displayWinner(currentGame);

                    // Ask the user if they want to play again after the game is over
                    choicePlayAgain = playAgain();

                    // if the user says yes, reset the game and start again
                    switch(choicePlayAgain)
                    {
                        case 'Y':
                            // reset board
                            resetBoard(board);

                            displayBoard(board);

                            player = 'X';   // reset player
                            currentGame = 1;
                            fflush(stdin);  // Flush out any buffer in the input device
                            break;
                        case 'N':
                            printf("\nThank you for playing!");
                            return 0;
                    }

                    continue;
                }
            }
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
    printf("\n1 - 2 Player");
    printf("\n2 - CPU\n");
    scanf("\n%c", &gameMode);

    // Validate input
    while (gameMode != '1' && gameMode != '2')
    {
        printf("\nInvalid input! Please enter either 1 - 2\n");

        printf("\nWould you like to play  2-Player or against a CPU?");
        printf("\n1 - 2 Player");
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


void resetBoard(char board[3][3])
{
    // Reinitialize the board to its empty values
    board[0][0] = '1';
    board[0][1] = '2';
    board[0][2] = '3';
    board[1][0] = '4';
    board[1][1] = '5';
    board[1][2] = '6';
    board[2][0] = '7';
    board[2][1] = '8';
    board[2][2] = '9';
}


char switchPlayer(char player)
{
    char switchedPlayer;

    // Switch the player whenever the function is called
    switch(player)
    {
        case 'X':
            switchedPlayer = 'O';
            break;
        case 'O':
            switchedPlayer = 'X';
            break;
    }

    return switchedPlayer;
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


int checkForWin(char boardGame[3][3])
{
    int i, j;
    int moves = 0;

    // If the player wins, return false indicating the game is finished and has a winner

    // Check rows for wins
    for (i = 0; i < 3; i++)
    {
        if ((boardGame[i][0] == 'X' && (boardGame[i][1] == 'X') && (boardGame[i][2] == 'X')))
        {
            return 10;
        }
        else if ((boardGame[i][0] == 'O' && (boardGame[i][1] == 'O') && (boardGame[i][2] == 'O')))
        {
            return -10;
        }
    }

    // Check columns
    for (i = 0; i < 3; i++)
    {
        if ((boardGame[0][i] == 'X' && (boardGame[1][i] == 'X') && (boardGame[2][i] == 'X')))
        {
            return 10;
        }
        else if ((boardGame[0][i] == 'O' && (boardGame[1][i] == 'O') && (boardGame[2][i] == 'O')))
        {
            return -10;
        }
    }

    // Check diagonals
    if ((boardGame[0][0] == 'X' && (boardGame[1][1] == 'X') && (boardGame[2][2] == 'X')))
        {
            return 10;
        }
    else if ((boardGame[0][0] == 'O' && (boardGame[1][1] == 'O') && (boardGame[2][2] == 'O')))
        {
            return -10;
        }
    else if ((boardGame[2][0] == 'X' && (boardGame[1][1] == 'X') && (boardGame[0][2] == 'X')))
        {
            return 10;
        }
    else if ((boardGame[2][0] == 'O' && (boardGame[1][1] == 'O') && (boardGame[0][2] == 'O')))
        {
            return -10;
        }

    // Check if it's a cats game
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (boardGame[i][j] == 'X' || boardGame[i][j] == 'O')
            {
                moves++;
            }
        }
    }

    if (moves == 9)
    {
        return 0;
    }
}


void displayWinner(int winner)
{
    switch(winner)
    {
        case 10:
            printf("\nThe winner is X!\n");
            break;
        case -10:
            printf("\nThe winner is O!\n");
            break;
        case 0:
            printf("\nCats game! It is a tie!\n");
            break;
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


int miniMax(char board[3][3], int depth, int isMaximizing)
{
    // Check the score for the current board
    int score = checkForWin(board);

    // Hold the max/min score in the best move variable
    int bestMove;

    int move;
    char placeholder;
    int i, j;

    /*
    If x wins, +10
    If o wins, -10
    If tied, 0
    */

    // If the maximizing player wins return their score (10)
    if (score == 10)
        return score;
    // return minimizing player score if they win (-10)
    else if (score == -10)
        return score;
    // If it is a cats game, return 0 indicating there is no score
    else if (score == 0)
        return 0;


    // Check if the current player is the maximizing player
    if (isMaximizing)
    {
        /*
        The algorithm will always start from the maximizing player,
        and work its way down next to minimizing player, then maximizing and
        so on.
        */

        // set bestMove to a arbitrarily small number to begin comparison for best moves
        bestMove = -1000;

        // Check all spaces in the board
        for (i = 0; i < 3; i++)
        {
            for (j = 0; j < 3; j++)
            {
                // If spot is available
                if (board[i][j] != 'X' && board[i][j] != 'O')
                {
                    // store the char value of the available space in a variable
                    placeholder = board[i][j];

                    // Add the maximizing player
                    board[i][j] = 'X';

                    /* Recursively call the miniMax function to switch to minimizing and check the best move from
                    the perspective of the minimizing player*/
                    move = miniMax(board, depth + 1, 0);

                    // Undo the maximizing move
                    board[i][j] = placeholder;

                    // Check if the recursive function called and stored into move is the better move (higher score)
                    if (move > bestMove)
                        bestMove = move;
                }
            }
        }

        // Return the final best move after recursion
        return bestMove;
    }
    // If it is the minimizing player
    else
    {
        // Set this to a arbitrarily large number in order to find the numerically smallest move from the human player
        bestMove = 1000;

        // Check all spaces in the board
        for (i = 0; i < 3; i++)
        {
            for (j = 0; j < 3; j++)
            {
                // If spot is available
                if (board[i][j] != 'X' && board[i][j] != 'O')
                {
                    // store the char value of the available space in a variable
                    placeholder = board[i][j];

                    // Add minimizing player to the board
                    board[i][j] = 'O';

                    /* Recursively call the miniMax function to switch to mazimizing and check the best move from
                    the perspective of the maximizing player*/
                    move = miniMax(board, depth + 1, 1);

                    // Undo the maximizing move
                    board[i][j] = placeholder;

                    // Check if the recursive function called and stored into move is the better move (lower score)
                    if (move < bestMove)
                        bestMove = move;
                }
            }
        }
        // return the best score or move after recursion
        return bestMove;
    }
}


// This function is our trigger to begin the minimax algorithm
// Start off as the maximizing player
void getBestMove(char board[3][3])
{
    int move, bestMoveI, bestMoveJ;
    int bestMove = -10000;
    char placeholder;
    int i, j;

    // This for loop will first check any available spots, then call the minmax function
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
            // Check if spot is available
            if (board[i][j] != 'X' && board[i][j] != 'O')
            {
                // store the char value of the available space
                placeholder = board[i][j];

                // Temporarily make the move for the AI
                board[i][j] = 'X';

                // Check the score for the minimizing player using the minimax algorithm
                move = miniMax(board, 0, 0);

                // Revert the board to how it was
                board[i][j] = placeholder;

                // compare the value of move from the minimax algorithm to later determine if it is the best move
                if (move > bestMove)
                {
                    // Save the indexes that the best move was found
                    bestMoveI = i;
                    bestMoveJ = j;

                    // Save the score of the best move
                    bestMove = move;
                }
            }
    }

    // Assign the best move the AI can make to take a spot on the board
    board[bestMoveI][bestMoveJ] = 'X';
}
