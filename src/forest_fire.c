#include <string.h> // for copying the grid
#include <time.h> // for making a random seed
#include <stdlib.h> // for using rand() and srand()
#include "SDL2/SDL.h"
#include "forest_fire.h"

static int width, height, disappear_chance, grow_chance;
 
static void drawCell(SDL_Renderer* renderer, int x, int y, CellType cell);
static int willBurn(int x, int y, CellType cells[]);
static CellType doRule(int x, int y, CellType cells[]);

// a cell's color is determined by its type
static void drawCell(SDL_Renderer* renderer, int x, int y, CellType cell) {
	if(cell == GROWN) {
		SDL_SetRenderDrawColor(renderer, 10, 100, 50, 255); 
	} else if (cell == GROWING) {
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); 
	} else if(cell == BURNING) {
		SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255); 
	} else if(cell == BURNT) {
		SDL_SetRenderDrawColor(renderer, 100, 0, 0, 255); 
	} else {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); 
	}

	SDL_RenderDrawPoint(renderer, x, y);
}

// if a cell has burning neighbors and it's GROWN, then it will burn
static int willBurn(int x, int y, CellType cells[]) {
	int top = (y+height-1)%height;
	int bottom = (y+1)%height;
	int left = (x+width-1)%width;
	int right = (x+1)%width;

	// just look at the von Neumann neighborhood
	return cells[y*width+right] == BURNING ||
		cells[y*width+left] == BURNING ||
		cells[bottom*width+x] == BURNING ||
		cells[top*width+x] == BURNING; // ||
		// cells[top*width+right] == BURNING ||
		// cells[top*width+left] == BURNING ||
		// cells[bottom*width+left] == BURNING ||
		// cells[bottom*width+right] == BURNING;
}

// run the rules on the CA 
static CellType doRule(int x, int y, CellType cells[]) {
	CellType cell = cells[y*width+x];
	
	if(cell == GROWING) {
		return GROWN;
	} else if(cell == GROWN) {
		if(willBurn(x, y, cells) || rand()%disappear_chance == 0)
			return BURNING;
		else return GROWN;
	} else if(cell == BURNING) {
		return BURNT;
	} else if(cell == BURNT) {
		return EMPTY;
	} else if(cell == EMPTY) {
		if(rand()%grow_chance == 0) return GROWING;
		else return EMPTY;
	}

	return cell;
}

void initCells(CellType cells[], int w, int h, int disappear, int grow) {
	int choice;
	// these variables determine how the CA runs
	width = w;
	height = h;
	disappear_chance = disappear;
	grow_chance = grow;
	// set the random seed for the simulation
	srand(time(NULL));
	// fill the grid with random cells
	for(int i = 0; i < height*width; i++) {
		choice = rand()%10;
		if(choice >= 0 && choice <= 5) cells[i] = EMPTY;
		else if(choice > 5 && choice <= 8) cells[i] = GROWING;
		else cells[i] = GROWN;
	}
}

// we're putting both the drawing and updating into one function so that we only need one loop to do things
void run(SDL_Renderer* renderer, CellType cells[]) {
	// copy the current grid state into `oldCells'
	CellType oldCells[height*width];
	memcpy(oldCells, cells, sizeof(oldCells));
	
	for(int y = 0; y < height; y++) {
		for(int x = 0; x < width; x++) {
			drawCell(renderer, x, y, cells[y*width+x]);
			cells[y*width+x] = doRule(x, y, oldCells);
		}
	}
}
