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
string Board[8][8];						// To read from .txt file

//Initialize an array that will keep the threatened stones to be used in the score calculation
string threatened_pieces[8][8] = {"--"};

void readBoard();
void PutThePieces();
void Print_Thread();
/*----------------------------------------------------------------------*/
/*                      Define the Pieces classes                       */
/*----------------------------------------------------------------------*/

//Define pieces Abstract class to reach all of the Pieces from here
class Pieces
{
	public:
	//Define name and color of the pieces
		char name;
		char color;
		bool thread;
		int row;
		int column;
		virtual void isThread() = 0;
/*
	//assign constructor
		Pieces(char n, char c, int pos_x, int pos_y)
		{
			n= name;
			row = pos_x;
			column = pos_y;
		}
*/
};

class pawn: public Pieces
{		// The class
	public:
		char pawn_color;
		char pawn_name;
		int row,column;
		pawn(string name, int pos_x, int pos_y)
		{
			pawn_name = 'p';
			if (name == "pb")
				pawn_color = 'b';

			else if(name == "ps" )
				pawn_color = 's';
			row = pos_y;
			column = pos_x;
		}
		void isThread(void)
		{
			char c = pawn_color;
		//Black side
			if (c == 's' && Board[row + 1][column + 1] != "--" && Board[row + 1][column - 1] != "--")
			{
				if(row + 1 >= 0 && column + 1 <= 7)
					threatened_pieces[row +1][column+1] = Board[row + 1][column + 1];
				if(row-1 >= 0 && column -1 >= 0)
					threatened_pieces[row + 1][column - 1] = Board[row + 1][column - 1];
				threatened_pieces[row][column] = Board[row][column];
			}
			else if (c == 's' && Board[row + 1][column + 1] != "--" )
			{
				if(row + 1 >= 0 && column + 1 <= 7)
					threatened_pieces[row +1][column+1] = Board[row + 1][column + 1];
			}
			else if (c == 's' && Board[row + 1][column - 1] != "--" )
			{
				if(row-1 >= 0 && column -1 >= 0)
					threatened_pieces[row + 1][column - 1] = Board[row + 1][column - 1];
				threatened_pieces[row][column] = Board[row][column];
			}
			
		//white side
			if (c == 'b' && Board[row - 1][column + 1] != "--" && Board[row - 1][column - 1] != "--")
			{
				if(row - 1 <= 7 && column + 1 <= 7)
					threatened_pieces[row -1][column+1] = Board[row - 1][column + 1];
				if(row - 1 <= 7 && column -1 >= 0)
					threatened_pieces[row - 1][column - 1] = Board[row - 1][column + 1];
				threatened_pieces[row][column] = Board[row][column];
			}
			else if (c == 's' && Board[row - 1][column + 1] != "--" )
			{
				if(row - 1 <= 7 && column + 1 <= 7)
					threatened_pieces[row - 1][column+1] = Board[row - 1][column + 1];
			}
			else if (c == 's' && Board[row - 1][column - 1] != "--" )
			{
				if(row - 1 >= 0 && column - 1 >= 0)
					threatened_pieces[row - 1][column - 1] = Board[row - 1][column - 1];
				threatened_pieces[row][column] = Board[row][column];
			}
		}
};

	class knight: public Pieces 
	{
		char knight_color;
		char knight_name;
		int row,column;
		knight(string name, int pos_x, int pos_y)
		{
			knight_name = 'a';
			if (name == "ab")
				knight_color = 'b';

			else if(name == "as" )
				knight_color = 's';
			row = pos_y;
			column = pos_x;
		}
		void isThread(void)
		{
		
		}
	};


	class queen: public Pieces
	{
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
		
		}
	};

	class bishop: public Pieces 
	{
		char bishop_color;
		char bishop_name;
		int row,column;
		bishop(string name, int pos_x, int pos_y)
		{
			bishop_name = 'f';
			if (name == "fb")
				bishop_color = 'b';

			else if(name == "fs" )
				bishop_color = 's';
			row = pos_y;
			column = pos_x;
		}
	};
	class rook: public Pieces
	{
		char rook_color;
		char rook_name;
		int row,column;
		rook(string name, int pos_x, int pos_y)
		{
			rook_name = 'k';
			if (name == "kb")
				rook_color = 'b';

			else if(name == "ks" )
				rook_color = 's';
			row = pos_y;
			column = pos_x;
		}
	};

	class king: public Pieces
	{
		char king_color;
		char king_name;
		int row,column;
		king(string name, int pos_x, int pos_y)
		{
			king_name = 's';
			if (name == "sb")
				king_color = 'b';

			else if(name == "ss" )
				king_color = 's';
			row = pos_y;
			column = pos_x;
		}
	};
	class empty: public Pieces
	{
		char name = 'e';
	};

/*----------------------------------------------------------------------------------------------*/
/*							GLOBAL VARIABLES FOR FUNCTİONS										*/
/*----------------------------------------------------------------------------------------------*/


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
				cout<<substr;						//for monitoring the values of the pieces on the terminal
			}
			else									//search for space to seperate pieces
			{
				getline(BoardText, substr, ' ');
				Board[y][x] = substr;				// Assign name of the pieces on the Board array
				cout<<substr<<" ";					//for monitoring the values of the pieces on the terminal
			}
		}
	}
}

// İnsert the pieces as objects
void PutThePieces()
{
Pieces ObjectBoard[8][8];
for (int row = 0; row < 8; row++)
{
	for (int column = 0; column < 8; column++)
	{
		ObjectBoard[row][column] = Pieces(Board[row][column], row,column);
	}
}

for (int row = 0; row < 8; row++)
{
	for (int column = 0; column < 8; column++)
	{
		ObjectBoard[row][column].isThread();
		
	}
}
}


/*			This function is just for demo to watch the results is true or not*/
void Print_Thread()
{
cout<< endl<<endl<<"print threat Array"<<endl;
for (int y = 0; y < 8; y++)
{
	for (int x = 0; x < 8; x++)
	{
		if(x == 7)
		{
			if(threatened_pieces[y+1][0] != "--")
				cout<<threatened_pieces[y][x];
			else
				cout<<threatened_pieces[y][x]<<endl;
		}
		else
		{
			cout<<threatened_pieces[y][x]<<' ';
		}
	}
}
cout<<endl;
}


int main()
{
	readBoard();
	PutThePieces();
	Print_Thread();
	return 0;
}
