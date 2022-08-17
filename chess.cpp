#include <stdio.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
#include <queue>

using namespace std;

/* USED RESOURCES
https://www.geeksforgeeks.org/array-of-objects-in-c-with-examples/
*/


//Path of info txt
string path = "/home/ubuntu/Desktop/Codes/Applicant Assesment Test_4_EK_AtFil/board1.txt";

//Define a queue that holds to all of the threat conditions
queue<string> threat;

//Define Board for implement the every pieces on an array.
//Dimensions are y_size, x_size,
string Board[8][8];

/*----------------------------------------------------------------------*/
/*                      Define the Pieces classes                       */
/*----------------------------------------------------------------------*/

class Pieces
{
	public:
		char color;
		char name;
		virtual void isThread();
		void setColor(char c)
		{
			color = c;
		}
		void setName(char n)
		{
			name = n;
		}
};

class pawn : public Pieces
{		// The class
	public:          
		char color;
		char name;
		int x_position;
		int y_position;

		pawn(int x, int y, char c)
		{ // Constructor with parameters
		color = c;
		x_position = x;
		y_position = y;
		}
		void isThread(int x, int y, char c)
		{
			c = color;
			if (c == 's' && Board[x + 1][y + 1] != "--" && Board[x - 1][y + 1] != "--")
			{
				threat.push(Board[x + 1][y + 1]);
				threat.push(Board[x - 1][y + 1]);
			}
			else if (c == 's' && Board[x + 1][y + 1] != "--")
			{
				threat.push(Board[x + 1][y + 1]);
			}
			else if (c == 's' && Board[x - 1][y + 1] != "--")
			{
				threat.push(Board[x - 1][y + 1]);
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
}

void PutThePieces()
{
for (int y = 0; y < 8; y++)
{
	for (int x = 0; x < 8; x++)
	{
		if( Board[x][y] == "pb")
		{
			pawn p;
			pawn.setColor('b');
			pawn.setName('p');
		}
		else if(Board[x][y] == "ps")
			
	}
}

}
int main()
{
	readBoard();
}
