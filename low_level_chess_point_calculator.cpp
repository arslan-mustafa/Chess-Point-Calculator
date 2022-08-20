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
string PiecesColor[8][8];				// To keep the pieces colors
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
		pawn(char color int pos_x, int pos_y)		//constructor to generate object
		{
			pawn_color = color;
			row = pos_y;
			column = pos_x;
			isThread();
		}
		void isThread()
		{
		//Black side
			if (pawn_color == 's')
			{
				if(row + 1 <= 7 && column + 1 <= 7 && Board[row + 1][column + 1]!= "--")// upper right cross
				{
					if ( PiecesColor[row + 1][column + 1] != 's')						// check the boundaries(board size)
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

	class knight: public Pieces 
	{
		public:
		char knight_color;
		int row,column;
		knight(char color, int pos_x, int pos_y)
		{
			knight_color = color;
			row = pos_y;
			column = pos_x;
		}
		void isThread(void)
		{
			//Black side
			if (knight_color == 's')
			{
				if(row + 3 <= 7 && column + 1 <=7 && Board[row + 3][column + 1] != "--") //upper right
				{
					if ( PiecesColor[row + 3][column + 1] != 's')						// check the boundaries(board size)
					{
						InThreat[row + 3][column + 1] = Board[row + 3][column + 1];		// put it in the threatened pieces array
						NoThreat[row + 3][column + 1] = "--";							//remove it from safe pieces array
					}
				}

				if(row + 3 <= 7 && column + 1 <=7 && Board[row + 3][column - 1] != "--") //upper left
				{
					if ( PiecesColor[row + 3][column - 1] != 's')						// check the boundaries(board size)
					{
						InThreat[row + 3][column - 1] = Board[row + 3][column - 1];		// put it in the threatened pieces array
						NoThreat[row + 3][column - 1] = "--";							//remove it from safe pieces array
					}
				}

				if(row - 3 >= 0 && column + 1 <=7 && Board[row - 3][column + 1] != "--") //lower right
				{
					if ( PiecesColor[row - 3][column + 1] != 's')						// check the boundaries(board size)
					{
						InThreat[row - 3][column + 1] = Board[row - 3][column + 1];		// put it in the threatened pieces array
						NoThreat[row - 3][column + 1] = "--";							//remove it from safe pieces array
					}
				}

				if(row - 3 >= 0 && column + 1 <=7 && Board[row - 3][column - 1] != "--") //lower left
				{
					if ( PiecesColor[row - 3][column - 1] != 's')						// check the boundaries(board size)
					{
						InThreat[row - 3][column - 1] = Board[row - 3][column - 1];		// put it in the threatened pieces array
						NoThreat[row - 3][column - 1] = "--";							//remove it from safe pieces array
					}
				}
			}
			//upper right side check
			else if (knight_color == 's' && Board[row + 1][column + 1] != "--" )
			{
				if(row + 1 >= 0 && column + 1 <= 7)
					threatened_pieces[row +1][column+1] = Board[row + 1][column + 1];
			}
			//lower left
			else if (knight_color == 's' && Board[row + 1][column - 1] != "--" )
			{
				if(row-1 >= 0 && column -1 >= 0)
					threatened_pieces[row + 1][column - 1] = Board[row + 1][column - 1];
				threatened_pieces[row][column] = Board[row][column];
			}
			
		//white side
			if (knight_color == 'b' && Board[row - 1][column + 1] != "--" && Board[row - 1][column - 1] != "--")
			{
				if(row - 1 <= 7 && column + 1 <= 7)
					threatened_pieces[row -1][column+1] = Board[row - 1][column + 1];
				if(row - 1 <= 7 && column -1 >= 0)
					threatened_pieces[row - 1][column - 1] = Board[row - 1][column + 1];
				threatened_pieces[row][column] = Board[row][column];
			}
			else if (knight_color == 's' && Board[row - 1][column + 1] != "--" )
			{
				if(row - 1 <= 7 && column + 1 <= 7)
					threatened_pieces[row - 1][column+1] = Board[row - 1][column + 1];
			}
			else if (knight_color == 's' && Board[row - 1][column - 1] != "--" )
			{
				if(row - 1 >= 0 && column - 1 >= 0)
					threatened_pieces[row - 1][column - 1] = Board[row - 1][column - 1];
				threatened_pieces[row][column] = Board[row][column];
			}
		}
};


	class queen: public Pieces
	{
		public:
		char queen_color;
		char queen_name;
		int row,column;
		queen(string name, int pos_x, int pos_y)
		{
			queen_name = 'v';
			if (name == "vb")
				queen_color = 'b';

			else if(name == "vs" )
				queen_color = 's';
			row = pos_y;
			column = pos_x;
		}
		void isThread(void)
		{
			if(queen_color == 'b')
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

			cout<<PiecesColor[y][x]<<" ";
		}
		cout<<endl;
	}
}

int main()
{
	readBoard();
	readColors();
	
	return 0;
}
