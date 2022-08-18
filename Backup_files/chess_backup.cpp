#include <stdio.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
#include <queue>

using namespace std;

//Path of info txt
string path = "board1.txt";


//Define Board for implement the every pieces on an array.
string Board[8][8];

//Initialize an array that will keep the threatened stones to be used in the score calculation
string threatened_pieces[8][8] = {
{"--","--","--","--","--","--","--","--"},
{"--","--","--","--","--","--","--","--"},
{"--","--","--","--","--","--","--","--"},
{"--","--","--","--","--","--","--","--"},
{"--","--","--","--","--","--","--","--"},
{"--","--","--","--","--","--","--","--"},
{"--","--","--","--","--","--","--","--"},
{"--","--","--","--","--","--","--","--"}};

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
		int row,column;
	//assign constructor
		Pieces(char n, char c, int pos_x, int pos_y)
		{
			n= name;
//		c =color;
			row = pos_x;
			column = pos_y;
	//define class of pieces
			define_class();
		}
		void define_class()
		{
		}
};

class pawn
{		// The class
	public:
		char pawn_color;
		char pawn_name;
		int row,column;
		pawn(char col, char name, int pos_x, int pos_y)
		{
			pawn_color = col;
			pawn_name = name;
			row = pos_y;
			column = pos_x;
			isThread();
		}
		void isThread(void)
		{
			char c = pawn_color;
		//Black side
			if (c == 's' && Board[row + 1][column + 1] != "--" && Board[row - 1][column + 1] != "--")
			{
				if(row+1 <= 7 && column+1 <= 7)
					threatened_pieces[row+1][column+1] = Board[row + 1][column + 1];
				if(row-1 >= 0 && column+1 <= 7)
					threatened_pieces[row+1][column+1] = Board[row - 1][column + 1];
				threatened_pieces[row][column] = Board[row][column];
			}
			else if (c == 's' && Board[row+1][column+1] != "--")
			{
				if(row+1 <= 7 && column+1 <= 7)
					threatened_pieces[row+1][column+1] = Board[row+1][column+1];
				threatened_pieces[row][column] = Board[row][column];
			}
			else if (c == 's' && Board[row-1][column+1] != "--")
			{
				if(row-1 >= 0 && column+1 <= 7)
					threatened_pieces[row-1][column+1] = Board[row-1][column+1];
				threatened_pieces[row][column] = Board[row][column];
			}
		//white side
			if (c == 'b' && Board[row + 1][column - 1] != "--" && Board[row - 1][column - 1] != "--")
			{
				if(row+1 <= 7 && column-1 >= 0)
					threatened_pieces[row+1][column-1] = Board[row + 1][column - 1];
				if(row-1 <= 0 && column-1 >= 0)
					threatened_pieces[row-1][column-1] = Board[row - 1][column - 1];
				cout<<"debug1 "<<"row= "<<row+1<<" column= "<<column+1<<" "<<threatened_pieces[row+1][column-1]<< "      "<<endl;
				threatened_pieces[row][column] = Board[row][column];
			}
			else if (c == 'b' && Board[row-1][column-1] != "--")
			{
				if(row+1 <= 7 && column-1 >= 0)
					threatened_pieces[row+1][column-1] = Board[row+1][column-1];
				threatened_pieces[row][column] = Board[row][column];
			}
			else if (c == 'b' && Board[row-1][column-1] != "--")
			{
				if(row-1 >= 0 && column-1 >= 0)
					threatened_pieces[row-1][column-1] = Board[row-1][column-1];
				threatened_pieces[row][column] = Board[row][column];
			}

		}
};
	class bishop {
	};
	class knight {
	};
	class rook {
	};
	class queen { 
	};
	class king {
	};

void readBoard()
{
//Read the input file from the adress
ifstream BoardText(path);
//Put the datas into a string to seperate
cout<<"Write on Board array"<<endl;
for (int y = 0; y < 8; y++)
{
	for (int x = 0; x < 8; x++)
	{
			string substr;
			if(x == 7)
			{
				getline(BoardText, substr, '\r');
				Board[y][x] = substr;
				cout<<substr;
			}
			else
			{
				getline(BoardText, substr, ' ');
				Board[y][x] = substr;
				cout<<substr<<" ";
			}
	}
}

cout<< endl<<endl<<"Read from Board Array"<<endl;
for (int y = 0; y < 8; y++)
{
	for (int x = 0; x < 8; x++)
	{
		cout<<Board[y][x]<<' ';
	}
}
cout<<endl;
}

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

void PutThePieces()
{
for (int row = 0; row < 8; row++)
{
	for (int column = 0; column < 8; column++)
	{
		if( Board[row][column] == "pb")
		{
			pawn('b', 'p', row, column);
		}
		else if(Board[row][column] == "ps")
		{
			pawn('s', 'p', row, column);
		}
	}
}

}
int main()
{
	readBoard();
	PutThePieces();
	Print_Thread();
	return 0;
}
