#include <iostream>
#include <iomanip>
#include <cstdlib>
//#include <ctime>
#pragma warning( disable : 4996)
using namespace std;

const char X_SYMBOL = 'X';
const char MINE_SYMBOL = '*';
const char ZERO_BOX = '0';
const char EMPTY_BOX = '-';
const char FLAG_BOX = 'F';
const char UNFLAG_BOX = 'U';

void isDimensionValid(int &N)
{
	int newN = 0;
	while (N < 3 || N > 10)
	{
		cout << "THE VALUE IS OUT OF RANGE. PLEASE ENTER NEW ONE.";
		cout << endl;
		cin >> newN;
		N = newN;
	}
	cout << "YOUR FIELD IS: " << N << " X " << N << endl;
}
void isTheNumOfMinesValid(int &N, int mines)
{
	while (mines < 1 || mines >(3 * N))
	{
		cout << "THE VALUE IS OUT OF RANGE. PLEASE ENTER NEW ONE.";
		cout << endl;
		cin >> mines;
	}

	cout << "THE NUMBER OF MINES IS: " << mines << endl << endl;
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
	cout << endl;
	for (int i = 0; i < 1; i++)
	{
		cout << setw(30);
		for (int j = 0; j < N; j++)
		{
			cout << j  << "      ";
		}
	}
	cout << endl;  // the numbers in the upper part of the board

	cout << setw(27);
	for (int i = 0; i < N * 7; i++)
		{
			cout << "_";
		}
	cout << endl << endl;  //the upper frame of the board
	
	


	for (int i = 0; i < N; i++)
	{
		cout << setw(23) << i << " | ";
		for (int j = 0; j < N; j++)
		{
			cout << " [ " << field[i][j] << " ] ";
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

void makeMove(int* x, int* y)
{
	
}

bool isMine(int x, int y, char** field)
{ 
	return field[x][y] == MINE_SYMBOL;
}

int intFromChar(char ch)
{
	if (ch < '0' || ch > '9')
		return 10;
	return ch - '0';
}

bool isValidCoordinate(int x, int y, size_t N)
{
	return ((x >= 0) && (x <= N - 1) && 
		    (y >= 0) && (y <= N - 1));
}

void hints(int x, int y, char** field, size_t N)
{
	int boxCoords = intFromChar(field[x][y]);
	int minesInBoxCount = intFromChar(MINE_SYMBOL);

	if (boxCoords != minesInBoxCount && isValidCoordinate(x, y, N))
	{
		boxCoords = minesInBoxCount + 1;
	}
}

char countNeighbourMines(int row, int col, char** realBoard, size_t N)
{
	char count = ZERO_BOX;

	int right = col + 1;
	int left = col - 1;

	int down = row + 1;
	int up = row - 1;

	
		/*if (isMine(row, col, realBoard) == true)
		{
			return 999;
		}*/
	
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

//bool conditionToPlayMinesweeper(int x, int y, char** realBoard, size_t N, char** displayBoard, int mines)
//{
//	if (displayBoard[x][y] != X_SYMBOL)
//	{
//		return false;
//	}
//	if (realBoard[x][y] == MINE_SYMBOL)
//	{
//		displayBoard[x][y] = MINE_SYMBOL;
//
//		for (int i = 0; i < mines; i++)
//		{
//
//		}
//	}
//	else
//	{
//		int count = countNeighbourMines(x, y, realBoard, N);
//
//		displayBoard[x][y] = count + '0';
//
//	}
//}

void placeMines(char** realBoard, size_t N, int mines)
{
	int XCoordinate;
	int YCoordinate;

	for (int i = 1; i <= mines; i++)
	{
		XCoordinate = rand() % N;
		YCoordinate = rand() % N;

		while (isMine(XCoordinate, YCoordinate, realBoard))
		{
			XCoordinate = rand() % N;
			YCoordinate = rand() % N;
		}

		realBoard[XCoordinate][YCoordinate] = MINE_SYMBOL;
		
		/*hints(XCoordinate, YCoordinate + 1, realBoard, N);
	    hints(XCoordinate, YCoordinate - 1, realBoard, N);
	    hints(XCoordinate - 1, YCoordinate, realBoard, N);
	    hints(XCoordinate - 1, YCoordinate + 1, realBoard, N);
	    hints(XCoordinate - 1, YCoordinate - 1, realBoard, N);
	    hints(XCoordinate + 1, YCoordinate, realBoard, N);
	    hints(XCoordinate + 1, YCoordinate + 1, realBoard, N);
	    hints(XCoordinate + 1, YCoordinate - 1, realBoard, N);*/
		
		/*
		countNeighbourMines(XCoordinate, YCoordinate, realBoard, N);*/
	}

	
	

}



void revealEmptyBoxes(int row, int col, char** realBoard, char** displayBoard , int N)
{
	int right = col + 1;
	int left = col - 1;

	int down = row + 1;
	int up = row - 1;

	if (realBoard[row][col] != MINE_SYMBOL && displayBoard[row][col] == X_SYMBOL && isValidCoordinate(row,col,N))
	{
		displayBoard[row][col] = realBoard[row][col];

		if (realBoard[row][col] == ZERO_BOX)
		{
			displayBoard[row][col] = EMPTY_BOX;

			revealEmptyBoxes(row, right, realBoard, displayBoard, N);
			revealEmptyBoxes(row, left, realBoard, displayBoard, N);
			revealEmptyBoxes(up, right, realBoard, displayBoard, N);
			revealEmptyBoxes(up, col, realBoard, displayBoard, N);
			revealEmptyBoxes(up, left, realBoard, displayBoard, N);
			revealEmptyBoxes(down, col, realBoard, displayBoard, N);
			revealEmptyBoxes(down, right, realBoard, displayBoard, N);
			revealEmptyBoxes(down, left, realBoard, displayBoard, N);
		}
			

	}
}


void openBox(int x, int y, char** realBoard, char** displayBoard, size_t N)
{
	cout << "ROW NUMBER: ";
	cin >> x;
	cout << "COLUMN NUMNER: ";
	cin >> y;

	if (realBoard[x][y] != ZERO_BOX && displayBoard[x][y] != FLAG_BOX && realBoard[x][y] != MINE_SYMBOL && displayBoard[x][y] == X_SYMBOL && 
		isValidCoordinate(x,y,N))
	{
		displayBoard[x][y] = realBoard[x][y];
	}
	else
	{
		if (realBoard[x][y]=ZERO_BOX && realBoard[x][y] != ZERO_BOX && displayBoard[x][y] == X_SYMBOL &&
			isValidCoordinate(x, y, N)) // 0 - empty box
		{
			revealEmptyBoxes(x, y, realBoard, displayBoard, N);
		}
		else
		{
			if (realBoard[x][y] == MINE_SYMBOL && displayBoard[x][y] == X_SYMBOL &&
				isValidCoordinate(x, y, N))
			{
				cout << "YOU HIT A MINE!";
			}
			else
			{
				while (displayBoard[x][y] != X_SYMBOL && isValidCoordinate(x, y, N))
				{
					cout << "THE BOX IS ALREADY OPENED";
				}
			}
		}
	}
}

void flagBox(int row, int col, char** realBoard, char** displayBoard, size_t N)
{
	cout << "ROW NUMBER: ";
	cin >> row;
	cout << "COLUMN NUMNER: ";
	cin >> col;

	if (realBoard[row][col] != ZERO_BOX && displayBoard[row][col] == X_SYMBOL && isValidCoordinate(row, col, N))
	{
		displayBoard[row][col] = FLAG_BOX;	
	}
}

void playerInput(int row, int col, char** realBoard, char** displayBoard, size_t N)
{
	int playersChoice;
	bool isValid = false;
	cout << endl<< "~PRESS (1) TO OPEN THE BOX~\n~PRESS (2) TO MARK THE BOX~\n~PRESS (3) TO UNMARK THE BOX~" << endl;
	cout << "YOUR CHOICE: ";
	cin >> playersChoice;

	switch (playersChoice)
	{
	    case 1: 
	    {
	    	openBox(row, col, realBoard, displayBoard, N);
	    	break;
	    }
		case 2: 
		{
			flagBox(row, col, realBoard, displayBoard, N);
			break;
		}

		case 3: ;
	}
	

	
	
}

//bool isValid(int N, int row, int col) // check if the given cell is a valid cell or not
//{
//	return (row >= 0) && (row <= N) && (col >= 0) && (col <= N);
//}
//
//bool isMine(int row, int col, char** field)
//{
//	if (field[row][col] == '*')
//		return true;
//	else
//		return false;
//}
//
//void mineGenerator(char** field , int mines)
//{
//
//}

//void makeMove(int* row, int* col/*,command 1 2 3*/)
//{
//	// Take the input move
//	cout<< "Enter your move, (row, column) -> ";
//	cin << row;
//	return;
//}

void playMinesweeper(char** displayBoard, char** realBoard, size_t N, int mines , int x , int y)
{
	bool gameOver = false;
	int currentMoveIndex = 0;

	initializeDisplayBoard(displayBoard, X_SYMBOL, N);
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
	cout << "ENTER THE DIFFICULTY LEVEL \n~(BETWEEN 3 AND 10)~" << endl;
	cin >> N;
	isDimensionValid(N);
	cout << "----------------------------"<<endl;
	cout << "NUMBER OF MINES\n~(BETWEEN 1 AND 3*DIFFICULTY LEVEL)~" << endl;
	cin >> mines;
	isTheNumOfMinesValid(N, mines);


	char** displayBoard = createField(N);
	char** realBoard = createField(N);

	initializeDisplayBoard(displayBoard, X_SYMBOL, N);
	initializeRealBoard(realBoard, X_SYMBOL, N);
	
	placeMines(realBoard,N,mines);
	placeCountOfMines(row, col, realBoard, N);

	while (true)
	{
		printBoard(displayBoard, N);
		printBoard(realBoard, N);
		playerInput(row, col, realBoard, displayBoard, N);
	}
    

	/*isMine(1, 3, realBoard);*/
	/*cout<<countNeighbourMines(3, 4, realBoard, N);*/
	/*cin >> x >> y;*/
	/*placeCountOfMines(x, y, realBoard, N);*/
	/*
	openBox(x, y, realBoard, displayBoard, N);*/


	

	free(displayBoard, N);
	free(realBoard, N);

}


 