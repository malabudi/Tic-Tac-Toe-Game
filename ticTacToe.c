#include <stdio.h>

// Function Prototypes
char askGamemode();
void displayBoard(char gameBoard[3][3]);
void setBoard(char gameBoard[3][3]);
char switchPlayer(char player);
char selectLocation(char player, char gameBoard[3][3]);
int isSpotTaken(char location, char gameBoard[3][3]);
char setTurn(char gameBoard[3][3], char location, char player);
int checkForWin(char gameBoard[3][3]);
void displayWinner(int winner);
int playAgain(char board[3][3]);
int miniMax(char board[3][3], int depth, int alpha, int beta, int isMaximizing);
void getBestMove(char board[3][3]);


int main()
{
    // Initialize/declare variables
	char gamemode;
	char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
	char location;
	char player = 'X';      // Initialize the first player to X, then switch to O for second player when necessary
	int moves = 0;
	int currentGame = 1;    // score for the current state of the TicTacToe game, 1 is default, 0 is cats, 10 and -10 are wins for X and O respectively
	char choicePlayAgain;

	// Ask the user if they want to play with two players or against an unbeatable AI
	gamemode = askGamemode();

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
                    if (playAgain(board))
                    {
                        player = 'X';   // reset player

                        currentGame = 1;

                        fflush(stdin);  // Flush out any buffer in the input device
                        continue;
                    }
                    else
                        return 0;
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
                    if (playAgain(board))
                    {
                        player = 'X';   // reset player

                        currentGame = 1;

                        fflush(stdin);  // Flush out any buffer in the input device
                        continue;
                    }
                    else
                        return 0;
                }

                // Switch player after the AI's move is done
                player = switchPlayer(player);

                location = selectLocation(player, board);

                player = setTurn(board, location, player);

                currentGame = checkForWin(board); // Check if there is a win from the human

                displayBoard(board);

                // Check if the user wants to play again after the game is finished
                if (currentGame == 0 || currentGame == 10 || currentGame == -10)
                {
                    // Display the winner
                    displayWinner(currentGame);

                    // Ask the user if they want to play again after the game is over
                    if (playAgain(board))
                    {
                        player = 'X';   // reset player

                        currentGame = 1;

                        fflush(stdin);  // Flush out any buffer in the input device
                        continue;
                    }
                    else
                        return 0;
                }
            }
    }
	return 0;
}
//-----------------------------------------------------------------------------------------------------------


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


void setBoard(char board[3][3])
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
    /*
    If x wins, +10
    If o wins, -10
    If tied, 0
    */

    // Check rows for wins
    for (i = 0; i < 3; i++)
    {
        if ((boardGame[i][0] == 'X' && (boardGame[i][1] == 'X') && (boardGame[i][2] == 'X')))
            return 10;
        else if ((boardGame[i][0] == 'O' && (boardGame[i][1] == 'O') && (boardGame[i][2] == 'O')))
            return -10;
    }

    // Check columns
    for (i = 0; i < 3; i++)
    {
        if ((boardGame[0][i] == 'X' && (boardGame[1][i] == 'X') && (boardGame[2][i] == 'X')))
            return 10;
        else if ((boardGame[0][i] == 'O' && (boardGame[1][i] == 'O') && (boardGame[2][i] == 'O')))
            return -10;
    }

    // Check diagonals
    if ((boardGame[0][0] == 'X' && (boardGame[1][1] == 'X') && (boardGame[2][2] == 'X')))
            return 10;
    else if ((boardGame[0][0] == 'O' && (boardGame[1][1] == 'O') && (boardGame[2][2] == 'O')))
            return -10;
    else if ((boardGame[2][0] == 'X' && (boardGame[1][1] == 'X') && (boardGame[0][2] == 'X')))
            return 10;
    else if ((boardGame[2][0] == 'O' && (boardGame[1][1] == 'O') && (boardGame[0][2] == 'O')))
            return -10;

    // Check if it's a cats game
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (boardGame[i][j] == 'X' || boardGame[i][j] == 'O')
                moves++;
        }
    }

    // If the board is full of X's and O's return 0 to quit the game
    if (moves == 9)
        return 0;
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


int playAgain(char board[3][3])
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

    // if the user says yes, reset the game and start again
    switch(choice)
    {
        case 'Y':
            // reset board
            setBoard(board);

            displayBoard(board);
            return 1;
        case 'N':
            printf("\nThank you for playing!");
            return 0;
    }
}


int miniMax(char board[3][3], int depth, int alpha, int beta, int isMaximizing)
{
    /*
    The algorithm will always start from the maximizing player,
    and work its way down next to minimizing player to grab the minimizing score,
    then the maximizing player grabs the max scores and it repeats until there are
    no possible moves left. The algorithm is even quicker with alpha-beta pruning,
    finding the best move with the least amount of checks possible
    */

    // Check the score for the current board
    int score = checkForWin(board);

    // Hold the max/min score in the best move variable
    int bestMove;

    int move;
    char placeholder;
    int i, j;

    // If the maximizing player wins return their score (10)
    if (score == 10)
        return score;
    // return minimizing player score if they win (-10)
    else if (score == -10)
        return score;
    // If it no player wins, return 0
    else if (score == 0)
        return 0;


    // Check if the current player is the maximizing player
    if (isMaximizing)
    {
        // set bestMove to a arbitrarily small number to begin comparison for best moves
        bestMove = -10000;

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
                    the perspective of the minimizing player, also increment the depth for every move checked.*/
                    move = miniMax(board, depth + 1, alpha, beta, 0);

                    // Undo the maximizing move
                    board[i][j] = placeholder;

                    // Check if the recursive function called and stored into move is the better move (higher score)
                    if (move > bestMove)
                        bestMove = move;

                    // Assign the maximized move to beta if the minimizing move is less than the current beta value
                    if (bestMove > alpha)
                        alpha = bestMove;

                    if (beta <= alpha)
                        break;
                }
            }

            // Break out of outer loop for alpha-beta pruning
            if (beta <= alpha)
                break;
        }

        // Return the final best move after recursion, also subtract depth to grab the max score of the move in the least amount of moves possible
        return bestMove - depth;
    }
    // If it is the minimizing player
    else
    {
        // Set this to a arbitrarily large number in order to find the numerically smallest move from the human player
        bestMove = 10000;

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

                    /* Recursively call the miniMax function to switch to maximizing and check the best move from the perspective
                    of the maximizing player.*/
                    move = miniMax(board, depth + 1, alpha, beta, 1);

                    // Undo the maximizing move
                    board[i][j] = placeholder;

                    // Check if the recursive function called and stored into move is the better move (lower score)
                    if (move < bestMove)
                        bestMove = move;

                    // Assign the minimized move to beta if the minimizing move is less than the current beta value
                    if (bestMove < beta)
                        beta = bestMove;

                    /* If beta is less than the alpha value, we prune and prevent the for loop from searching further possible moves
                    since we already found the best possible move*/
                    if (beta <= alpha)
                        break;
                }
            }

            // Break out of outer loop for alpha-beta pruning
            if (beta <= alpha)
                break;
        }
        // return the best score or move after recursion, also add depth to grab the min score of the move in the most amount of moves possible
        return bestMove + depth;
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

    // This for loop will first check any available spots, then call the minimax function
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

                // Check the score for the minimizing player using the minimax algorithm, also pass in -10000 and 10000 for alpha-beta pruning
                move = miniMax(board, 0, -10000, 10000, 0);

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
