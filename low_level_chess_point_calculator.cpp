#include <stdio.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
#include <queue>

using namespace std;

//Path of info txt
string path = "board1.txt";

/*----------------------------------------------------------------------------------------------*/
/*							GLOBAL VARIABLES FOR CLASSES										*/
/*----------------------------------------------------------------------------------------------*/

//Define Board for implement the every pieces on an array.
string Board[8][8];						// To read the pieces from .txt file
char PiecesColor[8][8];				// To keep the pieces colors
string NoThreat[8][8];					// To keep the pieces that are not threatened
string InThreat[8][8];					// To keep the pieces that are threatened

// define the points of all pieces
int pawn_point   = 1,	rook_point  =	5;
int knight_point = 3,	queen_point =	9;
int bishop_point = 3,	king_point  = 100;

//Initialize all of the functions 
void readBoard();					// To read board from .txt
void readColors();					// To read colors from Board Array and generate the class objects
void calculatePoint();				// To calculate the points of each side

/*----------------------------------------------------------------------*/
/*                      Define the Pieces classes                       */
/*----------------------------------------------------------------------*/

class pawn	// Class of pawns
{
	public:
		char pawn_color;			//color initialization
		int row,column;				//position keeper
		pawn(int pos_x, int pos_y)		//constructor to generate object
		{
			row = pos_y;
			column = pos_x;
			pawn_color = PiecesColor[row][column];
			isThread();
		}
		void isThread()
		{
		//Black side
			if (pawn_color == 's')
			{
				if(row + 1 <= 7 && column + 1 <= 7 && Board[row + 1][column + 1]!= "--")// upper right cross
				{
					if ( PiecesColor[row + 1][column + 1] == 's')						// check the boundaries(board size)
					{
						InThreat[row + 1][column + 1] = Board[row + 1][column + 1];		// put it in the threatened pieces array
						NoThreat[row + 1][column + 1] = "--";							//remove it from safe pieces array
					}
				}
				else if(row + 1 <= 7 && column - 1 >= 0&& Board[row + 1][column - 1]!= "--")// upper left cross
				{
					if ( PiecesColor[row + 1][column - 1] != 's')						// check the boundaries(board size)
					{
						InThreat[row + 1][column - 1] = Board[row + 1][column - 1];		// put it in the threatened pieces array
						NoThreat[row + 1][column - 1] = "--";							//remove it from safe pieces array
					}
				}
			}

		//white side
			if (pawn_color == 'b')
			{
				if(row - 1 <= 7 && column + 1 <= 7 && Board[row - 1][column + 1]!= "--")// lower right cross
				{
					if ( PiecesColor[row - 1][column + 1] != 'b')						// check the boundaries(board size)
					{
						InThreat[row - 1][column + 1] = Board[row - 1][column + 1];		// put it in the threatened pieces array
						NoThreat[row - 1][column + 1] = "--";							//remove it from safe pieces array
					}
				}
				else if(row - 1 <= 7 && column - 1 >= 0&& Board[row - 1][column - 1]!= "--")// lower left cross
				{
					if ( PiecesColor[row - 1][column - 1] != 'b')						// check the boundaries(board size)
					{
						InThreat[row - 1][column - 1] = Board[row - 1][column - 1];		// put it in the threatened pieces array
						NoThreat[row - 1][column - 1] = "--";							//remove it from safe pieces array
					}
				}
			}
		}
};

	class knight
	{
		public:
		char knight_color;
		int row,column;
		knight(int pos_x, int pos_y)
		{
			row = pos_y;
			column = pos_x;
			knight_color = PiecesColor[row][column];
			isThread(row,column, knight_color);
		}
		void isThread(int row, int column, char knight_color)
		{
			//Black side
			if (knight_color == 's')
			{

				if(row + 2 <= 7 && column + 1 <=7 && Board[row + 2][column + 1] != "--") //upper right
				{
					if ( PiecesColor[row + 2][column + 1] != 's')						// check the boundaries(board size)
					{
						InThreat[row + 2][column + 1] = Board[row + 2][column + 1];		// put it in the threatened pieces array
						NoThreat[row + 2][column + 1] = "--";							//remove it from safe pieces array
					}
				}

				if(row + 2 <= 7 && column + 1 <=7 && Board[row + 2][column - 1] != "--") //upper left
				{
					if ( PiecesColor[row + 2][column - 1] != 's')						// check the boundaries(board size)
					{
						InThreat[row + 2][column - 1] = Board[row + 2][column - 1];		// put it in the threatened pieces array
						NoThreat[row + 2][column - 1] = "--";							//remove it from safe pieces array
					}
				}

				if(row - 2 >= 0 && column + 1 <=7 && Board[row - 2][column + 1] != "--") //lower right
				{
					if ( PiecesColor[row - 2][column + 1] != 's')						// check the boundaries(board size)
					{
						InThreat[row - 2][column + 1] = Board[row - 2][column + 1];		// put it in the threatened pieces array
						NoThreat[row - 2][column + 1] = "--";							//remove it from safe pieces array
					}
				}

				if(row - 2 >= 0 && column + 1 <=7 && Board[row - 2][column - 1] != "--") //lower left
				{
					if ( PiecesColor[row - 2][column - 1] != 's')						// check the boundaries(board size)
					{
						InThreat[row - 2][column - 1] = Board[row - 2][column - 1];		// put it in the threatened pieces array
						NoThreat[row - 2][column - 1] = "--";							//remove it from safe pieces array
					}
				}


				if(row + 1 <= 7 && column + 2 <=7 && Board[row + 1][column + 2] != "--") //right up
				{
					if ( PiecesColor[row + 1][column + 2] != 's')						// check the boundaries(board size)
					{
						InThreat[row + 1][column + 2] = Board[row + 1][column + 2];		// put it in the threatened pieces array
						NoThreat[row + 1][column + 2] = "--";							//remove it from safe pieces array
					}
				}

				if(row + 2 <= 7 && column + 1 <=7 && Board[row - 1][column + 2] != "--") //right down
				{
					if ( PiecesColor[row - 1][column + 2] != 's')						// check the boundaries(board size)
					{
						InThreat[row - 1][column + 2] = Board[row - 1][column + 2];		// put it in the threatened pieces array
						NoThreat[row - 1][column + 2] = "--";							//remove it from safe pieces array
					}
				}

				if(row + 1 <= 7 && column - 2 >= 0 && Board[row + 1][column - 2] != "--") //left up
				{
					if ( PiecesColor[row + 1][column - 2] != 's')						// check the boundaries(board size)
					{
						InThreat[row + 1][column - 2] = Board[row + 1][column - 2];		// put it in the threatened pieces array
						NoThreat[row + 1][column - 2] = "--";							//remove it from safe pieces array
					}
				}

				if(row - 1 >= 0 && column -2 >=0 && Board[row - 1][column - 2] != "--") //left down
				{
					if ( PiecesColor[row - 1][column - 2] != 's')						// check the boundaries(board size)
					{
						InThreat[row - 1][column - 2] = Board[row - 1][column - 2];		// put it in the threatened pieces array
						NoThreat[row - 1][column - 2] = "--";							//remove it from safe pieces array
					}
				}
			}
			//White sizde
			if (knight_color == 'b')
			{

				if(row + 2 <= 7 && column + 1 <=7 && Board[row + 2][column + 1] != "--") //upper right
				{
					if ( PiecesColor[row + 2][column + 1] != 'b')						// check the boundaries(board size)
					{
						InThreat[row + 2][column + 1] = Board[row + 2][column + 1];		// put it in the threatened pieces array
						NoThreat[row + 2][column + 1] = "--";							//remove it from safe pieces array
					}
				}

				if(row + 2 <= 7 && column + 1 <=7 && Board[row + 2][column - 1] != "--") //upper left
				{
					if ( PiecesColor[row + 2][column - 1] != 'b')						// check the boundaries(board size)
					{
						InThreat[row + 2][column - 1] = Board[row + 2][column - 1];		// put it in the threatened pieces array
						NoThreat[row + 2][column - 1] = "--";							//remove it from safe pieces array
					}
				}

				if(row - 2 >= 0 && column + 1 <=7 && Board[row - 2][column + 1] != "--") //lower right
				{
					if ( PiecesColor[row - 2][column + 1] != 'b')						// check the boundaries(board size)
					{
						InThreat[row - 2][column + 1] = Board[row - 2][column + 1];		// put it in the threatened pieces array
						NoThreat[row - 2][column + 1] = "--";							//remove it from safe pieces array
					}
				}

				if(row - 2 >= 0 && column + 1 <=7 && Board[row - 2][column - 1] != "--") //lower left
				{
					if ( PiecesColor[row - 2][column - 1] != 'b')						// check the boundaries(board size)
					{
						InThreat[row - 2][column - 1] = Board[row - 2][column - 1];		// put it in the threatened pieces array
						NoThreat[row - 2][column - 1] = "--";							//remove it from safe pieces array
					}
				}


				if(row + 1 <= 7 && column + 2 <=7 && Board[row + 1][column + 2] != "--") //right up
				{
					if ( PiecesColor[row + 1][column + 2] != 'b')						// check the boundaries(board size)
					{
						InThreat[row + 1][column + 2] = Board[row + 1][column + 2];		// put it in the threatened pieces array
						NoThreat[row + 1][column + 2] = "--";							//remove it from safe pieces array
					}
				}

				if(row + 2 <= 7 && column + 1 <=7 && Board[row - 1][column + 2] != "--") //right down
				{
					if ( PiecesColor[row - 1][column + 2] != 'b')						// check the boundaries(board size)
					{
						InThreat[row - 1][column + 2] = Board[row - 1][column + 2];		// put it in the threatened pieces array
						NoThreat[row - 1][column + 2] = "--";							//remove it from safe pieces array
					}
				}

				if(row + 1 <= 7 && column - 2 >= 0 && Board[row + 1][column - 2] != "--") //left up
				{
					if ( PiecesColor[row + 1][column - 2] != 'b')						// check the boundaries(board size)
					{
						InThreat[row + 1][column - 2] = Board[row + 1][column - 2];		// put it in the threatened pieces array
						NoThreat[row + 1][column - 2] = "--";							//remove it from safe pieces array
					}
				}

				if(row - 1 >= 0 && column -2 >=0 && Board[row - 1][column - 2] != "--") //left down
				{
					if ( PiecesColor[row - 1][column - 2] != 'b')						// check the boundaries(board size)
					{
						InThreat[row - 1][column - 2] = Board[row - 1][column - 2];		// put it in the threatened pieces array
						NoThreat[row - 1][column - 2] = "--";							//remove it from safe pieces array
					}
				}
			}
		}
};


	class queen
	{
		public:
		char queen_color;
		int row,column;
		queen(int pos_x, int pos_y)
		{
			row = pos_y;
			column = pos_x;
			queen_color = PiecesColor[row][column];
			isThread(row, column);
		}
		void isThread(int row, int column)
		{
			//Black side
			if (queen_color == 's')
			{
				for (int i = row; i<=7;i++)						//up side
				{
					if(Board[i][column] != "--")
					{
						if(PiecesColor[i][column] == 'b')
						{
							InThreat[i][column] = Board[i][column];				// put it in the threatened pieces array
							NoThreat[i][column] = "--";							//remove it from safe pieces array
						}
						break;
					}
				}

				for (int i = row; i>=0;i--)						//down side
				{
					if(Board[i][column] != "--")
					{
						if(PiecesColor[i][column] == 'b')
						{
							InThreat[i][column] = Board[i][column];				// put it in the threatened pieces array
							NoThreat[i][column] = "--";							//remove it from safe pieces array
						}
						break;
					}
				}

				for (int i = column; i <= 7; i++)				//right side
				{
					if(Board[row][i] != "--")
					{
						if(PiecesColor[row][i] == 'b')
						{
							InThreat[row][i] = Board[row][i];					// put it in the threatened pieces array
							NoThreat[row][i] = "--";							//remove it from safe pieces array
						}
						break;
					}
				}

				for (int i = column; i>=0;i--)					//left side
				{
					if(Board[row][i] != "--")
					{
						if(PiecesColor[row][i] == 'b')
						{
							InThreat[row][i] = Board[row][i];					// put it in the threatened pieces array
							NoThreat[row][i] = "--";							//remove it from safe pieces array
						}
						break;
					}
				}

				int move_row = 0,move_column = 0;

				while(move_row > -1 || move_column < 8)			//right up diagonal
				{
					move_row = row;
					move_column = column;
					cout<<row<<" "<<column<<" "<<endl;
					move_row -= 1;
					move_column += 1;
					if(move_row > -1 || move_column < 8)
						break;
					if(Board[move_row][move_column] != "--")
					{
						if(PiecesColor[move_row][move_column] == 'b')
						{
							InThreat[move_row][move_column] = Board[move_row][move_column];	// put it in the threatened pieces array
							NoThreat[move_row][move_column] = "--";							//remove it from safe pieces array
						}
						break;
					}
				}

				while(move_row < 8 && move_column < 8)			//right down diagonal
				{
					move_row = row;
					move_column = column;
					move_row += 1;
					move_column += 1;
					if(move_row < 8 || move_column < 8)
						break;
					if(Board[move_row][move_column] != "--")
					{
						if(PiecesColor[move_row][move_column] == 'b')
						{
							InThreat[move_row][move_column] = Board[move_row][move_column];	// put it in the threatened pieces array
							NoThreat[move_row][move_column] = "--";							//remove it from safe pieces array
						}
						break;
					}
				}

				while(move_row > -1 && move_column > -1)			//left up diagonal
				{
					move_row = row;
					move_column = column;
					move_row -= 1;
					move_column -= 1;
					if(move_row > -1 || move_column > -1)
						break;
					if(Board[move_row][move_column] != "--")
					{
						if(PiecesColor[move_row][move_column] == 'b')
						{
							InThreat[move_row][move_column] = Board[move_row][move_column];	// put it in the threatened pieces array
							NoThreat[move_row][move_column] = "--";							//remove it from safe pieces array
						}
						break;
					}
				}

				while(move_row < 8 && move_column > -1)			//left down diagonal
				{
					move_row = row;
					move_column = column;
					move_row += 1;
					move_column -= 1;
					if(move_row < 8 || move_column > -1)
						break;
					if(Board[move_row][move_column] != "--")
					{
						if(PiecesColor[move_row][move_column] == 'b')
						{
							InThreat[move_row][move_column] = Board[move_row][move_column];	// put it in the threatened pieces array
							NoThreat[move_row][move_column] = "--";							//remove it from safe pieces array
						}
						break;
					}
				}
			}
			
			//white side
			else if (queen_color == 'b')
			{

				for (int i = row; i>=0;i--)						//up side
				{
					if(Board[i][column] != "--")
					{
						if(PiecesColor[i][column] == 's')
						{
							InThreat[i][column] = Board[i][column];				// put it in the threatened pieces array
							NoThreat[i][column] = "--";							//remove it from safe pieces array
						}
						break;
					}
				}
				for (int i = row; i>=0;i--)						//down side
				{
					if(Board[i][column] != "--")
					{
						if(PiecesColor[i][column] == 's')
						{
							InThreat[i][column] = Board[i][column];				// put it in the threatened pieces array
							NoThreat[i][column] = "--";							//remove it from safe pieces array
						}
						break;
					}
				}
				for (int i = column; i <= 7; i++)				//right side
				{
					if(Board[row][i] != "--")
					{
						if(PiecesColor[row][i] == 's')
						{
							InThreat[row][i] = Board[row][i];					// put it in the threatened pieces array
							NoThreat[row][i] = "--";							//remove it from safe pieces array
						}
						break;
					}
				}
				for (int i = column; i>=0;i--)					//left side
				{
					if(Board[row][i] != "--")
					{
						if(PiecesColor[row][i] == 's')
						{
							InThreat[row][i] = Board[row][i];					// put it in the threatened pieces array
							NoThreat[row][i] = "--";							//remove it from safe pieces array
						}
						break;
					}
				}

				int move_row = 0,move_column = 0;

				while(move_row < 8 && move_column > -1)			//right up diagonal
				{
					move_row = row;
					move_column = column;
					move_row -= 1;
					move_column += 1;
					if(move_row < 8 || move_column > -1)
						break;
					if(Board[move_row][move_column] != "--")
					{
						if(PiecesColor[move_row][move_column] == 's')
						{
							InThreat[move_row][move_column] = Board[move_row][move_column];	// put it in the threatened pieces array
							NoThreat[move_row][move_column] = "--";							//remove it from safe pieces array
						}
						break;
					}
				}

				while(move_row < 8 && move_column < 8)			//right down diagonal
				{
					move_row = row;
					move_column = column;
					move_row += 1;
					move_column += 1;
					if(move_row < 8 || move_column < 8)
						break;
					if(Board[move_row][move_column] != "--")
					{
						if(PiecesColor[move_row][move_column] == 's')
						{
							InThreat[move_row][move_column] = Board[move_row][move_column];	// put it in the threatened pieces array
							NoThreat[move_row][move_column] = "--";							//remove it from safe pieces array
						}
						break;
					}
				}

				while(move_row > -1 && move_column > -1)			//left up diagonal
				{
					move_row = row;
					move_column = column;
					move_row -= 1;
					move_column -= 1;
					if(move_row > -1 || move_column > -1)
						break;
					if(Board[move_row][move_column] != "--")
					{
						if(PiecesColor[move_row][move_column] == 's')
						{
							InThreat[move_row][move_column] = Board[move_row][move_column];	// put it in the threatened pieces array
							NoThreat[move_row][move_column] = "--";							//remove it from safe pieces array
						}
						break;
					}
				}

				while(move_row < 8 && move_column > -1)			//left down diagonal
				{
					move_row = row;
					move_column = column;
					move_row += 1;
					move_column -= 1;
					if(move_row < 8 || move_column > -1)
						break;
					if(Board[move_row][move_column] != "--")
					{
						if(PiecesColor[move_row][move_column] == 's')
						{
							InThreat[move_row][move_column] = Board[move_row][move_column];	// put it in the threatened pieces array
							NoThreat[move_row][move_column] = "--";							//remove it from safe pieces array
						}
						break;
					}
				}
			}
		}
	};

/*----------------------------------------------------------------------------------------------*/
/*									REQUIRED FUNCTIONS											*/
/*----------------------------------------------------------------------------------------------*/

void readBoard()
{
	//Read the input file from the adress
	ifstream BoardText(path);

	//Put the datas into a string to seperate
	cout << endl << "Write on Board array" << endl;
	//for loop to assign names of Pieces from text file
	for (int y = 0; y < 8; y++)							// Vertical axis loop
	{
		for (int x = 0; x < 8; x++)						//Horizontal axis loop
		{
			string substr;							// sub string to hold pieces name
			if(x == 7)								// if reach the end of line search for '\r'
			{
				getline(BoardText, substr, '\r');
				Board[y][x] = substr;				// Assign name of the pieces on the Board array
				NoThreat[y][x] = substr;			// Assign the all pieces as safe. According to the threat condition pieces that threatened is deleter from this array
				InThreat[y][x] = "--";				// Assign all of the threatened array as empty for initialization
				cout<<substr;						//for monitoring the values of the pieces on the terminal
				getline(BoardText, substr, '\n');
			}
			else									//search for space to seperate pieces
			{
				getline(BoardText, substr, ' ');
				Board[y][x] = substr;				// Assign name of the pieces on the Board array
				NoThreat[y][x] = substr;			// Assign the all pieces as safe. According to the threat condition pieces that threatened is deleter from this array
				InThreat[y][x] = "--";				// Assign all of the threatened array as empty for initialization
				cout<<substr<<" ";					//for monitoring the values of the pieces on the terminal
			}
		}
		cout<<endl;
	}
	cout<<endl<<endl;
}

void readColors()
{
	for (int y = 0; y < 8; y++)							// Vertical axis loop
	{
		for (int x = 0; x < 8; x++)						//Horizontal axis loop
		{
			if (Board[y][x] == "pb")
				PiecesColor[y][x] = 'b';

			else if (Board[y][x] == "ps")
				PiecesColor[y][x] = 's';

			else if (Board[y][x] == "ab")
				PiecesColor[y][x] = 'b';

			else if (Board[y][x] == "as")
				PiecesColor[y][x] = 's';

			else if (Board[y][x] == "vb")
				PiecesColor[y][x] = 'b';

			else if (Board[y][x] == "vs")
				PiecesColor[y][x] = 's';

			else if (Board[y][x] == "fb")
				PiecesColor[y][x] = 'b';

			else if (Board[y][x] == "fs")
				PiecesColor[y][x] = 's';

			else if (Board[y][x] == "kb")
				PiecesColor[y][x] = 'b';

			else if (Board[y][x] == "ks")
				PiecesColor[y][x] = 's';

			else if (Board[y][x] == "sb")
				PiecesColor[y][x] = 'b';

			else if (Board[y][x] == "ss")
				PiecesColor[y][x] = 's';

			else
				PiecesColor[y][x] = '-';

		}
	}
}

void checkThreat()
{
	for (int y = 0; y < 8; y++)							// Vertical axis loop
	{
		for (int x = 0; x < 8; x++)						//Horizontal axis loop
		{
/*			if (Board[y][x] == "pb" || Board[y][x] == "ps")
				pawn piyon(x,y);

			else if (Board[y][x] == "ab" || Board[y][x] == "as")
				knight at(x,y);
*/
			if (Board[y][x] == "vb" || Board[y][x] == "vs")
				queen vezir(x,y);

		}
	}
};

void printBoards()
{
	int row,column;
	
	cout<<"Readed board array"<<endl<<endl;
	
	for(row = 0; row <= 7; row++)
	{
		for(column = 0; column <= 7; column++)
		{
			cout<<Board[row][column]<<" ";
		}
		cout<<endl;
	}
	cout<<endl<<endl;


	cout<<"Color array"<<endl<<endl;
	
	for(row = 0; row <= 7; row++)
	{
		for(column = 0; column <= 7; column++)
		{
			cout<<PiecesColor[row][column]<<" ";
		}
		cout<<endl;
	}
	cout<<endl<<endl;


	cout<<"In threat array"<<endl<<endl;
	
	for(row = 0; row <= 7; row++)
	{
		for(column = 0; column <= 7; column++)
		{
			cout<<InThreat[row][column]<<" ";
		}
		cout<<endl;
	}
	cout<<endl<<endl;

	cout<<"No thread array"<<endl<<endl;
	
	for(row = 0; row <= 7; row++)
	{
		for(column = 0; column <= 7; column++)
		{
			cout<<NoThreat[row][column]<<" ";
		}
		cout<<endl;
	}
	cout<<endl<<endl;
}

int main()
{
	readBoard();
	readColors();
	checkThreat();
	printBoards();
	return 0;
}
