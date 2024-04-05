#include <SDL.h>
#include <vector>
#include <cmath>
#include <iostream>
#include <cstdlib> 
/*
Author:HaydenD100
GitHub: https://github.com/HaydenD100

Random maze generation using prims algorithm, Prims algorith uses a set of rules to generate path tiles through a grid of solid tiles by connecting neighbours in a random order
*/

//Window size
const int WIDTH = 800, HEIGHT = 600;

struct GridCell {
	//Cordinates 
	int x;
	int y;
	//Bool for if the point is solid etc a wall 0 for false 1 for true, solid points are shown in gray
	int solid = 1;
	//So you dont have to check the frontier list to see if this Cell is already in the frontierCells list
	int frontier = 0;
	//Parent cell so the algorithm knows what cell it should connect this cell with
	GridCell* parentCell = NULL;
};

//2D array of all the grids
struct GridCell grid[80][60];
//this is a vector that holds all the caculated neighbours of a cells.
std::vector<GridCell*> frontierCells;


//Draws the grid and the diffrent colour for each tile depending on if it a solid tile (Black) or a path (White) red tiles are frontier tiles
void Draw(SDL_Renderer* renderer) {
	//sets the background colour and then clears the window 
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	for (int y = 0; y < 60; y++) {
		for (int x = 0; x < 80; x++) {
			SDL_Rect rect = { x * 10,y * 10,10,10 };
			
			if (grid[x][y].solid == 0) {
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			}
			else if (grid[x][y].solid == 1 && grid[x][y].frontier == 1) {
				SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			}
			else if(grid[x][y].solid == 1)
			{
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			}
			
			SDL_RenderFillRect(renderer, &rect);
		}
	}

	//updates the screen with the new drawings in the renderer 
	SDL_RenderPresent(renderer);

}

//Calculates all the neighbouring cells of a certain cell inputed as x and y and adds them to the frontierCells vector to be randomly picked later on
void Neighbours(int x, int y) {

	if (x > 1 && grid[x - 2][y].frontier == 0 && grid[x - 2][y].solid == 1) {
		frontierCells.push_back(&grid[x - 2][y]);
		grid[x - 2][y].frontier = 1;
		grid[x - 2][y].parentCell = &grid[x][y];

	}
	if (x < 79 && grid[x + 2][y].frontier == 0 && grid[x + 2][y].solid == 1) {
		frontierCells.push_back(&grid[x + 2][y]);
		grid[x + 2][y].frontier = 1;
		grid[x + 2][y].parentCell = &grid[x][y];
	}
	if (y > 1 && grid[x][y - 2].frontier == 0 && grid[x][y - 2].solid == 1) {
		frontierCells.push_back(&grid[x][y - 2]);
		grid[x][y - 2].frontier = 1;
		grid[x][y-2].parentCell = &grid[x][y];
	}
	if (y < 59 && grid[x][y + 2].frontier == 0 && grid[x][y + 2].solid == 1) {
		frontierCells.push_back(&grid[x][y + 2]);
		grid[x][y + 2].frontier = 1;
		grid[x][y + 2].parentCell = &grid[x][y];
	}

}

GridCell* NextCell(int x, int y) {
	
	//Checks to see if there is not more frontier cells to choce from if so the maze is complete 
	if (frontierCells.size() <= 0)
		return NULL;

	GridCell* nextCell = frontierCells[rand() % frontierCells.size()];
	nextCell->solid = 0;

	grid[(nextCell->parentCell->x + nextCell->x) / 2][(nextCell->parentCell->y + nextCell->y) / 2].solid = 0;

	Neighbours(nextCell->x, nextCell->y);

	frontierCells.erase(std::find(frontierCells.begin(), frontierCells.end(), nextCell));

	return nextCell;
}


int main(int argc, char* args[]) {

	int solve = 1;

	for (int y = 0; y < 60; y++) {
		for (int x = 0; x < 80; x++) {
			struct GridCell newCell;
			newCell.x = x;
			newCell.y = y;
			grid[x][y] = newCell;

		}
	}


	//SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Maze", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
	SDL_Event event;
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	int currentX = 20;
	int currentY = 20;
	GridCell* currentCell = &grid[currentX][currentY];
	currentCell->solid = 0;
	Neighbours(currentCell->x, currentCell->y);

	

	while (true) {
		if (SDL_PollEvent(&event)) {
			if (SDL_QUIT == event.type) break;
		}
		
		if(solve == 1)
		{
			currentCell = NextCell(currentCell->x, currentCell->y);
			if (currentCell == NULL)
				solve = 0;

		}
		

		
		Draw(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 1;
}