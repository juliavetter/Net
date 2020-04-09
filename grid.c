#include "net.h"
#include "mylib.h"

//
//Grid Functions
//

//allocate memory for a new grid
Grid* newgrid(int height, int width) {
	//initialize the grid struct
	Grid* grid = (Grid*)mymalloc(sizeof(Grid));
	grid->height = height;
	grid->width = width;
	grid->nodes = (Node**)mymalloc(height * width * sizeof(Node));
	for (int i = 0; i < grid->height; i++) {
			grid->nodes[i] = (Node*)mymalloc(width * sizeof(Node));
	}
	//initialize the fields of each node and connect its directional pointers to adjacent nodes
	for (int i = 0; i < grid->height; i++) {
		for (int j = 0; j < grid->width; j++) {
			//Includes special cases for the connector when the node is on the border of the grid -- it should 'wrap around', i.e., the pointer should point to the node on the opposite side of the grid
			Node* n = &(grid->nodes[i][j]);
			n->powered = false;
			n->wires = 0;
			n->traversed = false;
			if (i == 0) {
				n->up = &(grid->nodes[height - 1][j]);
			} else {
				n->up = n - width * sizeof(Node);
			}
			if (j == grid->height - 1) {
				n->right = &(grid->nodes[i][0]);
			} else {
				n->right = n + sizeof(Node);
			}
			if (i == grid->height - 1) {
				n->down = &(grid->nodes[0][j]);
			} else {
				n->down = n + width * sizeof(Node);
			}
			if (j == 0) {
				n->left = &(grid->nodes[i][width - 1]);
			} else {
				n->left = n - sizeof(Node);
			}
		}
	}
	//set the source node to the center
	grid->source = &(grid->nodes[(width - 1) / 2][(height - 1) / 2]);
	printf("Set source node to 0x%lx\n", (unsigned long)grid->source);
	return grid;
}

/*
//returns a node in a grid, given its x and y coords
Coords findnode(Grid* grid, Node* node, Coords coords) {
	//TODO
	return (Coords){};
}

//returns the x and y coords of a node in a grid
//Coords getnodecoords(Grid* grid, Node* node) {
	//TODO
	return (Coords){};
}
*/

//draw a grid in the console
void drawgrid(Grid* grid) {
	printf("Width: %d | Height: %d | Active: %d/%d\n", grid->width, grid->height, checkgrid(grid), grid->width * grid->height);
	for (int i = 0; i < grid->height; i++) {
		for (int j = 0; j < grid->width; j++) {
			drawnode(&(grid->nodes[i][j]));
		}
		printf("\n");
	}
}

//generate a completed grid from an empty grid
void generategrid(Grid* grid) {
	//set up a stack which will be used to traverse the nodes
	Stack* stack = newstack();
	push(stack, grid->source);
	//while the stack is not empty, pop a node off the stack, then push all connected nodes that have not been traversed already
	while (!empty(stack)) {
		Node* n = pop(stack);
		generatenode(n);
		n->traversed = true;
		if (!n->up->traversed) {
			push(stack, n->up);
		}
		if (!n->right->traversed) {
			push(stack, n->right);
		}
		if (!n->down->traversed) {
			push(stack, n->down);
		}
		if (!n->left->traversed) {
			push(stack, n->left);
		}
	}
	//reset the traversed values of all the nodes
	for (int i = 0; i < grid->height; i++) {
		for (int j = 0; j < grid->width; j++) {
			grid->nodes[i][j].traversed = false;
		}
	}
	freestack(stack);
}

//clear the connections on a grid
void cleargrid (Grid* grid) {
	for (int i = 0; i < grid->height; i++) {
		for (int j = 0; j < grid->width; j++) {
			grid->nodes[i][j].wires = 0;
			grid->nodes[i][j].powered = false;
		}
	}
}

//randomize the node rotations on the grid
void scramblegrid(Grid* grid) {
	for (int i = 0; i < grid->height; i++) {
		for (int j = 0; j < grid->width; j++) {
			//rotate each node 0-3 times
			for (int k = 0; k < rand() % 4; k++) {
				rotatenode(&(grid->nodes[i][j]), true);
			}
		}
	}
}

//updates the powered flag for a given starting node, then recursively updates all connected nodes
void updatepower(Grid* grid) {
	//reset the power of all nodes -- the source will be powered since it is initially added to the stack 
	for (int i = 0; i < grid->height; i++) {
		for (int j = 0; j < grid->width; j++) {
			grid->nodes[i][j].powered = false;
		}
	}
	//set up a stack which will be used to traverse the nodes
	Stack* stack = newstack();
	push(stack, grid->source);
	//while the stack is not empty, pop a node off the stack, then push all connected nodes that have not been traversed already
	while (!empty(stack)) {
		Node* n = pop(stack);
		n->powered = true;
		n->traversed = true;
		if (n->HAS_UP && !n->up->traversed) {
			push(stack, n->up);
		}
		if (n->HAS_RIGHT && !n->right->traversed) {
			push(stack, n->right);
		}
		if (n->HAS_DOWN && !n->down->traversed) {
			push(stack, n->down);
		}
		if (n->HAS_LEFT && !n->left->traversed) {
			push(stack, n->left);
		}
	}
	//reset the traversed values of all the nodes
	for (int i = 0; i < grid->height; i++) {
		for (int j = 0; j < grid->width; j++) {
			grid->nodes[i][j].traversed = false;
		}
	}
	//	
	freestack(stack);
}

//returns true iff all nodes on the grid are powered
int checkgrid(Grid* grid) {
	int n = 0;
	for (int i = 0; i < grid->height; i++) {
		for (int j = 0; j < grid->width; j++) {
			if (grid->nodes[i][j].powered)
				n++;
		}
	}
	return n;
}

void freegrid(Grid* grid) {
	for (int i = 0; i < grid->height; i++) {
		free(grid->nodes[i]);
	}
	free(grid->nodes);
	free(grid);
}
