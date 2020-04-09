#include "net.h"
#include "mylib.h"

//
//Node Functions
//

/* currently unused
Node* newnode() {
	Node* n = mymalloc(sizeof(Node));
	n->up = NULL;
	n->right = NULL;
	n->down = NULL;
	n->left = NULL;
	n->powered = false;
	return n;
}
*/

//adds an outgoing wire connection to n in direction as defined by the constants in net.h. Returns zero if the connection already exists
bool addconnection(Node* n, int direction) {
	bool t = !(n->wires & direction);
	n->wires |= direction;
	return t;
}

//adds an additional outgoing wire connection to n in a random direction, but does not add it in the direction of a node that has already been traversed. If no new connections can be added, this returns zero
bool addrandomconnection(Node* n) {
	//TODO
	//p is the number of possible connections to choose from, that is, the number of adjacent nodes that have not already been traversed
	//potential is a bitfield where 1 is a possible choice
	int p = 0;
	int potential = 0;
	if (!n->up->traversed) {
		p++;
		potential |= UP;
	}
	if (!n->right->traversed) {
		p++;
		potential |= RIGHT;
	}
	if (!n->down->traversed) {
		p++;
		potential |= DOWN;
	}
	if (!n->left->traversed) {
		p++;
		potential |= LEFT;
	}
	//Choose a random integer r between 0 and p. Proceed clockwise starting at the up direction, subtracting 1 from r on each rotation that is a possible choice for a connection, then add a connection when r reaches 0. 
	int r = rand() % p;
	if (r == 0) {
		return false;
	}
	for (int i = 1; i <= 0b1000; i <<= 1) {
		//if the current direction is a potential choice...
		if (i & potential) {
			if (r == 0) {
				addconnection(n, i);
				return true;
			} else {
				r--;
			}
		}
	}
	return false;
}

//removes an outgoing wire connection to n in direction as defined by the constants in net.h. Returns zero if the connection already did not exist
bool removeconnection(Node* n, int direction) {
	bool t = n->wires & direction;
	n->wires &= (~direction) & 0b1111;
	return t;
}

//this will first connect the node to all adjacent nodes pointing in its direction, then additionaly randomly determine which other wire directions to generate, up to a maximum of 3 total wires
//TODO: make this random generation better
void generatenode(Node* n) {
	//add wires to match adjacent nodes
	if (n->up->HAS_DOWN)
		addconnection(n, UP);
	if (n->right->HAS_LEFT)
		addconnection(n, RIGHT);
	if (n->down->HAS_UP)
		addconnection(n, DOWN);
	if (n->left->HAS_RIGHT)
		addconnection(n, LEFT);
	//randomly add new wires
	if (connectioncount(n) == 0) {
		addrandomconnection(n);
	}
	if (connectioncount(n) == 1 && randfloat() < GEN2_CHANCE) {
		addrandomconnection(n);
	}
	if (connectioncount(n) == 2 && randfloat() < GEN3_CHANCE) {
		addrandomconnection(n);	
	}
}

//returns an int in the range 0-4 based on the number of outgoing wires in the node
int connectioncount(Node* n) {
	int connections = 0;
	if (n->HAS_UP)
		connections++;
	if (n->HAS_RIGHT)
		connections++;
	if (n->HAS_DOWN)
		connections++;
	if (n->HAS_LEFT)
		connections++;
	return connections;
}

void drawnode(Node* n) {
	wint_t wch = 0;
	switch(n->wires) {
		case 0b0000:
			wch = 0x2027;
			break;
		case 0b0001:
			wch = 0x2578;
			break;
		case 0b0010:
			wch = 0x257B;
			break;
		case 0b0011:
			wch = 0x2513;
			break;
		case 0b0100:
			wch = 0x257A;
			break;
		case 0b0101:
			wch = 0x2501;
			break;
		case 0b0110:
			wch = 0x250F;
			break;
		case 0b0111:
			wch = 0x2533;
			break;
		case 0b1000:
			wch = 0x2579;
			break;
		case 0b1001:
			wch = 0x251B;
			break;
		case 0b1010:
			wch = 0x2503;
			break;
		case 0b1011:
			wch = 0x252B;
			break;
		case 0b1100:
			wch = 0x2517;
			break;
		case 0b1101:
			wch = 0x253B;
			break;
		case 0b1110:
			wch = 0x2523;
			break;
		case 0b1111:
			wch = 0x254B;
			break;
	}
	printf("%lc", wch);

}

void rotatenode(Node* n, bool clockwise) {
	if (clockwise) {
		n->wires <<= 1;
		int temp = n->wires >> 3;
		n->wires &= 0b1111;
		n->wires |= temp;
	} else {
		int temp = n->wires & 1;
		temp <<= 3;
		n->wires >>= 1;
		n->wires |= temp;
	}
}

void freenode(Node* n) {
	free(n);
}
