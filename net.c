#include "net.h"
#include "mylib.h"

#define PROGRAM_NAME "net"
#define USAGE_MESSAGE "Usage: " PROGRAM_NAME " <height> <width>\n"
int main(int argc, char* argv[]) {

	srand((unsigned)time(NULL)); //initialize random number generator
	setlocale(LC_ALL, "");
	
	if (argc != 3) {
		printf(USAGE_MESSAGE);
		return 1;
	}
	//printf("Size of node: %ld\n", sizeof(Node));
	//printf("Size of grid: %ld\n", sizeof(Grid));
	int height = strtol(argv[1], NULL, 10);
	int width = strtol(argv[2], NULL, 10);
	printf("Constructing a %dx%d grid\n", height, width);
	Grid* grid = newgrid(height, width);
	printf("Grid constructed. Now drawing the grid.\n");
	drawgrid(grid);
	printf("Grid drawn. Now generating the grid.\n");
	generategrid(grid);
	drawgrid(grid);
	printf("Grid generated. Now scrambling the grid.\n");
	scramblegrid(grid);
	drawgrid(grid);
	printf("Grid scrambled. Now free the grid.\n");
	freegrid(grid);

	//TODO: GUI/CLI

    return 0;
}









