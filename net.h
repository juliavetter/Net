#ifndef NET_H
#define NET_H

#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <locale.h>
#include <wchar.h>

#define UP    0b1000
#define RIGHT 0b0100
#define DOWN  0b0010
#define LEFT  0b0001

#define HAS_UP    wires & 0b1000
#define HAS_RIGHT wires & 0b0100
#define HAS_DOWN  wires & 0b0010
#define HAS_LEFT  wires & 0b0001

#define GEN2_CHANCE 0.75
#define GEN3_CHANCE 0.25

//Net structs

typedef struct Node Node;
struct Node {
	Node* up;
	Node* right;
	Node* down;
	Node* left;
	bool powered;
	//the least significant 4 bits of wires act as 4 boolean values, i.e. 0 0 0 0 UP RIGHT DOWN LEFT
	//these values specify whether or not the node has a wire going in that direction
	int wires;
	bool traversed;
};

/*
typedef struct {
	int x;
	int y;
} Coords;
*/

typedef struct {
	int height;
	int width;
	//nodes[height][width]
	Node** nodes;
	Node* source;
} Grid;


//Grid functs

//allocate memory for a new grid
Grid* newgrid(int height, int width);
//returns a node in a grid, given its x and y coords
//extern Coords findnode(Grid* grid, Node* node, Coords coords);
//returns the x and y coords of a node in a grid
//extern Coords getnodecoords(Grid* grid, Node* node);
//draw a grid in the console
extern void drawgrid(Grid* grid);
//generate a completed grid
extern void generategrid(Grid* grid);
//clear the connections on a grid
extern void cleargrid(Grid* grid);
//randomize the node rotations on the grid
extern void scramblegrid(Grid* grid);
//updates the powered flag for a given starting node, then recursively updates all connected nodes
extern void updatepower(Grid* grid);
//returns the number of nodes on the grid that are powered
extern int checkgrid(Grid* grid);
//
extern void freegrid(Grid* grid);


//Node functs

//allocates memory for a new node and returns a pointer to it
//extern Node* newnode();
//adds an outgoing wire connection to n in direction as defined by the constants in net.h. Returns zero if the connection already exists
extern bool addconnection(Node* n, int direction);
//adds an additional outgoing wire connection to n in a random direction, but does not add it in the direction of a node that has already been traversed. If no new connections can be added, this returns zero
extern bool addrandomconnection(Node* n);
//removes an outgoing wire connection to n in direction as defined by the constants in net.h. Returns zero if the connection already did not exist
extern bool removeconnection(Node* n, int direction);
//this will first connect the node to all adjacent nodes pointing in its direction, then additionaly randomly determine which other wire directions to generate, up to a maximum of 3 total wires
extern void generatenode(Node* n);
//returns an int in the range 0-4 based on the number of outgoing wires in the node
extern int connectioncount(Node* n);
//
extern void drawnode(Node* n);
//
extern void rotatenode(Node* n, bool clockwise);
//
extern void freenode(Node* n);

#endif

























