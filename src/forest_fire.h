// the functions are defined in forest_fire.c, which has all the things used in running the CA

// each cell has one of these states
typedef enum {
	GROWING,
	GROWN,
	BURNING,
	BURNT,
	EMPTY
} CellType;

void initCells(CellType cells[], int w, int h, int disappear, int grow);
void run(SDL_Renderer* renderer, CellType cells[]);

