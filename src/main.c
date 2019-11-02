/**
	 FOREST FIRE
	 This is the forest fire cellular automaton, implemented in C with SDL2. 
*/

#define SDL_MAIN_HANDLED
#include "SDL2/SDL.h"
#include "main.h" // main.h contains all the functionality for running the simulation

int main() {
	int width = 300;
	int height = 300;
	
	SDL_Event event;
	SDL_Renderer* renderer;
	SDL_Window* window;
	CellType cells[height*width];
	// init SDL stuff
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
	// init cell grid by filling it randomly
	// and define width, height, and chances for certain cells to grow or disappear
	initCells(cells, width, height, 100000, 1000);
  
	while(1) {
		// exit main loop when window is closed
		if(SDL_PollEvent(&event) && event.type == SDL_QUIT) break;

		run(renderer, cells);	
		SDL_RenderPresent(renderer);	
	}

	// end all the SDL parts
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
    
	return 0;
}

