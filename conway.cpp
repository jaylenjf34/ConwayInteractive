/*

   Jaylen Figueroa
   CS300 Massey
   Homework two

   10/20/2020


 */

#include <iostream>
#include <string.h>
#include <ncurses.h>
#define  ORGANISM  'X'
#define SPACE     ' '
#define MAX  100


using namespace std;

class Grid // class that holds the information of the grid
{

	public:

		int add(int, int); // adds elements to the grid
		int generation(); // calculates the generation and updates the screen
		int copy(); // copy results from ne_grid to grid
		int print(int, int); // prints all elements to the screen

		Grid() // initalizes the grid
		{
			for(int i = 0; i < 100; ++i) // set every element in the array to 0
			{
				for (int k = 0; k < 100 ; ++k)
				{

					grid[i][k] = 0;
					ne_grid[i][k] = 0;


				}


			}



		}

	protected:

		int grid[100][100];
		int ne_grid[100][100];
		int rows; // number of rows 
		int columns; // number of columns


};



int main ()
{

	int ch ; // for grabbing user input
	bool started = true;
	int pr = 0;

	int columns  = 100;
	int rows = 100;

	int num_neighbors ; // used to keep track of number of neighbors


	int x; // starting postion x / current placement
	int y; // starting postion y /current charcter placement
	initscr();

	x = columns;
	y = rows;

	x = x/2; // start cursor in the middle
	y = y/2;


	Grid mygrid; // make a grid


	keypad(stdscr, true); // used for arrow key input
	noecho();


	move(y,x);
	refresh();



	nodelay(stdscr, true);

	do {




		move(y,x);
		refresh();

		ch = getch();




		if( ch == 'p'|| ch == 'P') // user hits p to play
		{  

			ch = -1; // set up for the while loop



			while( ch == -1)
			{
				refresh();

				timeout(500); // update every .5 seconds
				ch = getch();  // wait for user input

				mygrid.generation(); // calculate gliders


				for(int i = 0; i < 100; ++i)
				{

					for(int  k = 0; k < 100; ++k)
					{
						int alive = mygrid.print(i, k); // print new generation to screen

						if(alive) // cell is alive
						{
				                   mvaddch(i, k, 'X');



						}

						else // cell is dead
						{
				                   mvaddch(i, k, ' ');



						}





					}
				                   

				}




			}






		}



		switch (ch)      // source S2
		{
			case KEY_UP: // players moves up



				if( y < rows) // in window bounds
				{
					//	mvaddch(y, x, SPACE);
					--y;


				}



				break;



			case KEY_DOWN: // player moves down


				if( y >  0 && y < rows)

				{
					//	mvaddch(y, x, SPACE);
					++y;




				}


				break;







			case KEY_LEFT: // player moves left



				if( x > 0)
				{
					// mvaddch(y, x, SPACE);
					--x;



				}

				break;




			case  KEY_RIGHT: // right arrow key




				if(x < rows)

				{
					//mvaddch(y, x, SPACE);

					++x;

				}



				break ;




			case 'n': // move one step 

				if(x < rows)
				{
					++x;



				}


				break;



			case 'X': // user presses uppercase x
				getyx(stdscr, y, x);

				mvaddch(y, x, ORGANISM);
				mygrid.add(y,x);



				break;

			case 'x': // user presses lowerscase x
				getyx(stdscr, y, x);

				mvaddch(y, x, ORGANISM);
				mygrid.add(y,x);


				break;


		}


	} while ( ch != 'q' && ch!= 'Q');



	endwin();





	return 0;

}






int Grid :: add (int y , int x) // add a elment to the grid
{


	grid[y][x] = 1;
	ne_grid[y][x] = 1;

	return 1;



}



int Grid :: copy() // copy results from ne_grid to grid
{


	for(int i = 0; i < 100; ++i)
	{
		for (int k = 0; k < 100; ++k)
		{

			grid[i][k] = ne_grid[i][k];
		}
	}

	return 1;

}


int Grid :: print(int y, int x) // print all elements on the screen
{

	if( y < 0 || x < 0) // x or y out of bounds
	{
		return 0;

	}



	else if( y > 99 || x > 99) // x or y out of bounds
	{


		return 0;


	}



	else if(grid[y][x] == 1) // cell is alive
	{

		return 1;



	}


	else if(grid[y][x] == 0) // cell is dead
	{


		return 0;


	}


	return 0;

}


int Grid :: generation () // calculates and prints generations on the screen
{


	for(int i = 0; i < 100; ++i)   // source S1
	{

		for(int k = 0; k < 100; ++k)
		{
			int num_neighbors = 0; // number of neighbors a a cell has.
			for(int j = -1; j < 2; ++j) // count all live neighbors
			{

				for(int m  = -1; m < 2; ++m)
				{
						num_neighbors += grid[i + j][m + k];


				}


			}

			num_neighbors -= grid[i][k]; // subtract one's self



			if( grid[i][k] == 1 && num_neighbors < 2 ) // we are a live cell
			{
				ne_grid[i][k] = 0;
			}


			else if(grid[i][k] == 1 && num_neighbors > 3) // we die of overpopulation
			{
				ne_grid[i][k] = 0;


			}


			else if(grid[i][k] == 0 && num_neighbors == 3) // we have exactly three neighbors
			{
				ne_grid[i][k] = 1;



			}


			else // stays the same
			{

				ne_grid[i][k] = grid[i][k];


			}


		}


	}




	copy(); // copy all elements from ne_grid to the grid

	return 1;

}
