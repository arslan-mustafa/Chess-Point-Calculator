#include <stdio.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
#include <queue>

using namespace std;

//Path of info txt
string path = "/home/ubuntu/Desktop/Codes/Applicant Assesment Test_4_EK_AtFil/board1.txt";


//Define Board for implement the every pieces on an array.
string Board[8][8];

//Initialize an array that will keep the threatened stones to be used in the score calculation
string threatened_pieces[8][8];

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
		int x,y;
	//assign constructor
		Pieces(char n, char c, int pos_x, int pos_y)
		{
			n= name;
			c = color;
			x = pos_x;
			y = pos_y;
		}
	//Pure virtual function
		virtual void isThread() = 0;
};

class pawn
{		// The class
	public:
		char pawn_color;
		char pawn_name;
		int x,y;
		pawn(char col, char name, int pos_x, int pos_y)
		{
			pawn_color = col;
			pawn_name = name;
			x = pos_x;
			y = pos_y;
		}
		void isThread(void)
		{
			char c = pawn_color;
		//Black side
			if (c == 's' && Board[x + 1][y + 1] != "--" && Board[x - 1][y + 1] != "--")
			{
				threatened_pieces[x+1][y+1] = Board[x + 1][y + 1];
				threatened_pieces[x+1][y+1] = Board[x - 1][y + 1];
			}
			else if (c == 's' && Board[x+1][y+1] != "--")
			{
				threatened_pieces[x+1][y+1] = Board[x+1][y+1];
			}
			else if (c == 's' && Board[x-1][y+1] != "--")
			{
				threatened_pieces[x-1][y+1] = Board[x-1][y+1];
			}
		//white side
			if (c == 'b' && Board[x + 1][y - 1] != "--" && Board[x - 1][y - 1] != "--")
			{
				threatened_pieces[x+1][y-1] = Board[x - 1][y - 1];
				threatened_pieces[x+1][y-1] = Board[x - 1][y - 1];
			}
			else if (c == 'b' && Board[x-1][y-1] != "--")
			{
				threatened_pieces[x+1][y-1] = Board[x+1][y-1];
			}
			else if (c == 'b' && Board[x-1][y-1] != "--")
			{
				threatened_pieces[x-1][y-1] = Board[x-1][y-1];
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
				getline(BoardText, substr, '\r');
			else
				getline(BoardText, substr, ' ');
			Board[y][x] = substr;
			cout<<substr<<" ";
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

cout<< endl<<endl<<"print threat Array"<<endl;
for (int y = 0; y < 8; y++)
{
	for (int x = 0; x < 8; x++)
	{
		cout<<threatened_pieces[y][x]<<' ';
	}
}
cout<<endl;
}

void PutThePieces()
{
for (int y = 0; y < 8; y++)
{
	for (int x = 0; x < 8; x++)
	{
		if( Board[x][y] == "pb")
		{
			pawn('b', 'p', x, y);
		}
		else if(Board[x][y] == "ps")
			pawn('s', 'p', x, y);
	}
}

}
int main()
{
	readBoard();
}
