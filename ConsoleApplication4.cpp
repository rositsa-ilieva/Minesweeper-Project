/**
*
* Solution to course project # 7
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2022/2023
*
* @author Rositsa Ilieva
* @idnumber 6MI0600209
* @compiler VC
*
* <Minesweeper>
*
*/

#include <iostream>
#include <iomanip>
#include <cstdlib>
//#pragma warning( disable : 4996)
using namespace std;

const char UNOPENED_SYMBOL = ' ';
const char MINE_SYMBOL = '*';
const char ZERO_BOX = '0';
const char EMPTY_BOX = '-';
const char FLAG_BOX = 'F';

void isDimensionValid(int &N)
{
	//function to check if the dimention is in the range
	int newN = 0;
	while (N < 3 || N > 10)
	{
		cout << "THE VALUE IS OUT OF RANGE. PLEASE ENTER NEW ONE.";
		cout << endl;
		cin >> newN; // if it is not valid, enter new one
		N = newN;
	}
	cout << "YOUR FIELD IS: " << N << " X " << N << endl;
}
void isTheNumOfMinesValid(int &N, int mines)
{
	//function to check if the number of mines is in the range
	while (mines < 1 || mines >(3 * N))
	{
		cout << "THE VALUE IS OUT OF RANGE. PLEASE ENTER NEW ONE.";
		cout << endl;
		cin >> mines; // if the number is not in the range, enter new number
	}

	cout << "THE NUMBER OF MINES IS: " << mines << endl;
	cout << "----------------------------" << endl;
}

char** createField(int N)
{
	char** field;
	field = new char* [N];
	for (size_t i = 0; i < N; i++)
	{
		field[i] = new char[N];
	}
	for (size_t i = 0; i < N; i++) {
		for (size_t y = 0; y < N; y++) {
			field[i][y] = NULL; //default initialization
		}
	}

	return field;
}

void initializeDisplayBoard(char** field, char value, size_t N)
{
	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < N; j++)
		{
			field[i][j] = value;
		}
	}
} 
void initializeRealBoard(char** field, char value, size_t N)
{
	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < N; j++)
		{
			field[i][j] = ZERO_BOX;
		}
	}
}

void printBoard(char** field, size_t N)
{
	//print the board in the middle of the screen
	cout << endl;
	for (int i = 0; i < 1; i++)
	{
		cout << setw(30);
		for (int j = 0; j < N; j++)
		{
			cout << j  << "      "; // the numbers in the upper part of the board
		}
	}
	cout << endl; 

	cout << setw(27);
	for (int i = 0; i < N * 7; i++)
		{
			cout << "_";  //the upper frame of the board
		}
	cout << endl << endl; 

	for (int i = 0; i < N; i++)
	{
		cout << setw(23) << i << " | ";
		for (int j = 0; j < N; j++)
		{
			cout << " [ " << field[i][j] << " ] "; // each box
		}
		cout << " | " << i << endl << endl;
	}
}
void free(char** field, size_t N)
{
	for (int i = 0; i < N; i++) {
		
			delete[] field[i];
	}

	delete[] field;
}


bool isMine(int x, int y, char** field)
{
	return field[x][y] == MINE_SYMBOL;
}

bool isValidCoordinate(int x, int y, size_t N)
{
	//checks if the coodinates entered are valid or not
	return ((x >= 0) && (x < N) && 
		    (y >= 0) && (y < N));
}

char countNeighbourMines(int row, int col, char** realBoard, size_t N)
{
	char count = ZERO_BOX;

	int right = col + 1;
	int left = col - 1;

	int down = row + 1;
	int up = row - 1;

	
		if (isValidCoordinate(row, left, N) == true)
		{
			if (isMine(row, left, realBoard) == true)
			{
				count++;
			}
		}

		if (isValidCoordinate(row, right, N) == true)
		{
			if (isMine(row, right, realBoard) == true)
			{
				count++;
			}
		}

		if (isValidCoordinate(down, col, N) == true)
		{
			if (isMine(down, col, realBoard) == true)
			{
				count++;
			}
		}

		if (isValidCoordinate(up, col, N) == true)
		{
			if (isMine(up, col, realBoard) == true)
			{
				count++;
			}
		}

		if (isValidCoordinate(down, left, N) == true)
		{
			if (isMine(down, left, realBoard) == true)
			{
				count++;
			}
		}

		if (isValidCoordinate(down, right, N) == true)
		{
			if (isMine(down, right, realBoard) == true)
			{
				count++;
			}
		}

		if (isValidCoordinate(up,left, N) == true)
		{
			if (isMine(up,left, realBoard) == true)
			{
				count++;
			}
		}

		if (isValidCoordinate(up,right, N) == true)
		{
			if (isMine(up,right, realBoard) == true)
			{
				count++;
			}
		}
	
	return count;

}


void placeCountOfMines(int row, int col, char** realBoard, size_t N)
{
	for (int row = 0; row < N; row++)
	{
		for (int col = 0; col < N; col++)
		{
			if(isMine(row,col,realBoard)==false)
			realBoard[row][col] = countNeighbourMines(row, col, realBoard, N);
		}
	}
}


void placeMines(char** realBoard, size_t N, int mines)
{
	int XCoordinate;
	int YCoordinate;

	for (int i = 0; i < mines; i++)
	{
		XCoordinate = rand() % N; // x coordinate is in the range of 0 and N-1
		YCoordinate = rand() % N; // y coordinate is in the range of 0 and N-1

		while (isMine(XCoordinate, YCoordinate, realBoard))
		{
			XCoordinate = rand() % N;
			YCoordinate = rand() % N;
		}

		realBoard[XCoordinate][YCoordinate] = MINE_SYMBOL;
	}

}

void revealMines(char** realBoard, char** displayBoard, size_t N)
{
	//when you lose the game the mines would be revealed
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (realBoard[i][j] == MINE_SYMBOL) // if there is a mine it would be displayed on the board
				displayBoard[i][j] = realBoard[i][j];
		}
	}
	printBoard(displayBoard, N); 
}

bool winCondition(char** displayBoard, size_t N)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (displayBoard[i][j] != UNOPENED_SYMBOL)
				return true;
		}
	}
	return false;
}
bool loseCondition(char** displayBoard, size_t N)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (displayBoard[i][j] == MINE_SYMBOL)
				return true;
		}
	}
	return false;
}

void revealNeighboursWhenZero(int row, int col, char** realBoard, char** displayBoard, size_t N)
{
	if (displayBoard[row][col] == UNOPENED_SYMBOL)
		displayBoard[row][col] = realBoard[row][col]; 

	if (displayBoard[row][col] == ZERO_BOX)
		displayBoard[row][col] = EMPTY_BOX; // if the box that you opened doesn't have any mines around it

	for (int i = row - 1; i <= row + 1; i++) 
	{
		for (int j = col - 1; j <= col + 1; j++)
		{
			if (i >= 0 && j >= 0 && i < N && j < N) // check if the neighbour box is valid coordinate
			{
				if (i == row && j == col) // the box is already opened 
					continue;

				if (displayBoard[i][j] == UNOPENED_SYMBOL && realBoard[i][j] != MINE_SYMBOL)
				{
					displayBoard[i][j] = realBoard[i][j];

					if (displayBoard[i][j] == ZERO_BOX)
					{
						displayBoard[i][j] = EMPTY_BOX;
						revealNeighboursWhenZero(i, j, realBoard, displayBoard, N);
					}
				}
			}
				
		}
	}
}
void isNeighbourBoxZero(int row, int col, char** realBoard, char** displayBoard, size_t N)
{
	for (int i = row - 1; i <= row + 1; i++)
	{
		for (int j = col - 1; j <= col + 1; j++)
		{
			if (i == row && j == col)
				continue;

			if (realBoard[i][j] == ZERO_BOX && displayBoard[i][j] == UNOPENED_SYMBOL && realBoard[i][j] != MINE_SYMBOL)
			{
				revealNeighboursWhenZero(i, j, realBoard, displayBoard, N);
				break;
			}
		}
	}
}

void openBox(int row, int col, char** realBoard, char** displayBoard, size_t N)
{
	bool conditionForOpeningBox = false;

	char right = col + 1;
	char left = col - 1;

	char down = row + 1;
	char up = row - 1;

	while (conditionForOpeningBox != true)
	{
		cout << "ROW NUMBER: ";
		cin >> row;
		cout << "COLUMN NUMBER: ";
		cin >> col;
		cout << "----------------------------" << endl;

		    if (isValidCoordinate(row, col, N) == false)
		        {
		        	cout << "LOCATION ENTERED IS OUT OF THE SCOPE OF THE BOARD !" << endl;
		        	break;
		        }

			if (displayBoard[row][col] != FLAG_BOX && realBoard[row][col] != MINE_SYMBOL &&
				displayBoard[row][col] == UNOPENED_SYMBOL && realBoard[row][col] != ZERO_BOX &&
				isValidCoordinate(row, col, N))
			    {
			    	displayBoard[row][col] = realBoard[row][col];
			    	isNeighbourBoxZero(row, col, realBoard, displayBoard, N);
			    	conditionForOpeningBox = false;
			    	break;
			    }

			else if (realBoard[row][col] == ZERO_BOX && displayBoard[row][col] == UNOPENED_SYMBOL &&
					isValidCoordinate(row, col, N))
				{
					revealNeighboursWhenZero(row, col, realBoard, displayBoard, N);
					conditionForOpeningBox = false;
					break;
				}

		    else if (realBoard[row][col] == MINE_SYMBOL && displayBoard[row][col] == UNOPENED_SYMBOL &&
						isValidCoordinate(row, col, N))
				{
					revealMines(realBoard, displayBoard, N);
					cout << "YOU HIT A MINE!" << endl << "~ GAME OVER ~" << endl;
					loseCondition(displayBoard, N);
					break;
				}

			else if (displayBoard[row][col] != UNOPENED_SYMBOL && displayBoard[row][col] != FLAG_BOX &&
							isValidCoordinate(row, col, N))
				 {
				     cout << "THE BOX IS ALREADY OPENED !!" << endl;
				     break;
				 }

			else if (displayBoard[row][col] == FLAG_BOX && isValidCoordinate(row, col, N))
				 {
				 	cout << "THE BOX IS FLAGGED, SO YOU CANNOT OPEN IT. TRY UNFLAGGING IT." << endl;
				 	conditionForOpeningBox = false;
				 	break;
				 }

			else if (realBoard[row][col] == MINE_SYMBOL)
			    {
			    	displayBoard[row][col] = MINE_SYMBOL;
			    	printBoard(displayBoard, N);
			    	cout << "YOU HIT A MINE.\n~ GAME OVER ~" << endl;
			    }	
	}
}
void flagBox(int row, int col, char** realBoard, char** displayBoard, size_t N)
{
	bool flagedBox = false;
	
	while (flagedBox != true)
	{
		cout << "ROW NUMBER: ";
		cin >> row;
		cout << "COLUMN NUMNER: ";
		cin >> col;
		cout << "----------------------------" << endl;

       if (isValidCoordinate(row, col, N) == false)
		{
			cout << "THIS COORDINATES ARE NOT VALID." << endl;
			flagedBox = false;
			break;
		}

		else if (displayBoard[row][col] == UNOPENED_SYMBOL && isValidCoordinate(row, col, N))
		{
			displayBoard[row][col] = FLAG_BOX;
			flagedBox = true;
			break;
		}

		else if (displayBoard[row][col] == FLAG_BOX && isValidCoordinate(row, col, N))
		{
			cout << "THIS BOX IS ALREADY FLAGGED. TRY TO FLAG NEW ONE."<<endl;
			flagedBox = false;
			break;

		}

		else if (displayBoard[row][col] != FLAG_BOX && displayBoard[row][col] != UNOPENED_SYMBOL &&
			isValidCoordinate(row, col, N))
		{
			cout << "THE BOX IS ALREDY OPENED." << endl;
			flagedBox = false;
			break;
		}
	}
	
}
void unflagBox(int row, int col, char** realBoard, char** displayBoard, size_t N)
{
	bool unFlagedBox = false;

	while (unFlagedBox != true)
	{
		cout << "ROW NUMBER: ";
		cin >> row;
		cout << "COLUMN NUMNER: ";
		cin >> col;
		cout << "----------------------------" << endl;


		if (isValidCoordinate(row, col, N) == false)
		{
		     cout << "THIS COORDINATES ARE NOT VALID." << endl;
		     unFlagedBox = false;
		     break;
		}

		else if (displayBoard[row][col] == FLAG_BOX && isValidCoordinate(row, col, N))
		{
			displayBoard[row][col] = UNOPENED_SYMBOL;
			unFlagedBox = true;
			break;
		}
		
		else if (displayBoard[row][col] != FLAG_BOX && isValidCoordinate(row, col, N))
		{
			cout << "THIS BOX IS NOT FLAGGED. TO UNFLAG IT, PLEASE FLAG IT FIRST." << endl;
			unFlagedBox = true;
			continue;
		}

		else if (displayBoard[row][col] != FLAG_BOX && displayBoard[row][col] != UNOPENED_SYMBOL &&
			isValidCoordinate(row, col, N))
		{
			cout << "THE BOX IS ALREDY OPENED." << endl;
			unFlagedBox = false;
			continue;
		}

		break;
	}


}

void playerInput(int row, int col, char** realBoard, char** displayBoard, size_t N)
{
	int playersChoice;
	bool conditionForInput = false;

	cout << endl << "~PRESS (1) TO OPEN THE BOX~\n~PRESS (2) TO FLAG THE BOX~\n~PRESS (3) TO UNFLAG THE BOX~" << endl<<endl;
	cout << "YOUR CHOICE: ";
	cin >> playersChoice;
	cout<<"----------------------------" << endl;

	while (conditionForInput != true)
	{
		if (playersChoice == 1)
		{
			openBox(row, col, realBoard, displayBoard, N);
			conditionForInput = true;
		}

		if (playersChoice == 2)
		{
			flagBox(row, col, realBoard, displayBoard, N);
			conditionForInput = true;
		}

		if (playersChoice == 3)
		{
			unflagBox(row, col, realBoard, displayBoard, N);
			conditionForInput = true;
		}

		else
		{
			while (playersChoice != 1 && playersChoice != 2 && playersChoice != 3)
			{
				cout << "INVALID CHOICE. TRY AGAIN." << endl;
				cout << "----------------------------" << endl;
				cout << "YOUR CHOICE: ";
				cin >> playersChoice;
				cout << "----------------------------" << endl;
				conditionForInput = false;
				continue;
			}

		}
	}
		
}

void playMinesweeper(char** displayBoard, char** realBoard, size_t N, int mines , int x , int y)
{
	bool gameOver = false;
	int currentMoveIndex = 0;

	initializeDisplayBoard(displayBoard, UNOPENED_SYMBOL, N);
	placeMines(realBoard, N, mines);

	while (gameOver == false)
	{
		printBoard(displayBoard, N);
		playerInput(x,y,realBoard,displayBoard,N);

		if (currentMoveIndex == 0)
		{
			/*if (isMine(x, y, realBoard) == true)
			{

			}*/
		}

		currentMoveIndex++;

		


	}

}


int main()
{

	int N;
	int mines;
	int row = 0, col = 0;
	cout << "~MINESWEEPER~"<<endl;
	cout << "----------------------------" << endl;
	cout << "ENTER THE DIFFICULTY LEVEL \n~(BETWEEN 3 AND 10)~" << endl;
	cin >> N;
	cout << "----------------------------" << endl;
	isDimensionValid(N);
	cout << "----------------------------"<<endl;
	cout << "NUMBER OF MINES\n~(BETWEEN 1 AND 3*DIFFICULTY LEVEL)~" << endl;
	cin >> mines;
	cout << "----------------------------" << endl;
	isTheNumOfMinesValid(N, mines);


	char** displayBoard = createField(N);
	char** realBoard = createField(N);

	initializeDisplayBoard(displayBoard, UNOPENED_SYMBOL, N);
	initializeRealBoard(realBoard, UNOPENED_SYMBOL, N);
	
	placeMines(realBoard,N,mines);
	placeCountOfMines(row, col, realBoard, N);

	while (true)
	{
		printBoard(displayBoard, N);
		printBoard(realBoard, N);
		playerInput(row, col, realBoard, displayBoard, N);
	}
    
	free(displayBoard, N);
	free(realBoard, N);

}


 