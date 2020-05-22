// Course: 							DSA555 NSA
// Assignment:      		1 - Part 2
// Name: 								Xiaomin (Mica) Luo
// Seneca Student ID:   133728170
// Seneca email: 				xluo42@myseneca.ca

#include <stdlib.h>
#include "wall.h"
#include "disjointset.h"

int generateMaze(int row, int col, Wall walls[]){
	/*row and col describe the size of the maze in terms of the number of cells along its rows and columns.
	function will generate a list of Wall objects that form the maze and pass those back to the calling function using the walls array.
	function return the number of walls in the final maze*/

	bool wallFilled = false;
	int finalWalls = 0;
	int count = 0;
	int wallSize = col * (row - 1) + row * (col - 1);
	Wall** wallArray = new Wall*[wallSize];
	DisjointSet theSet(row * col);

	for (int i = 0; i < row * col; i++) {
		theSet.makeSet(i);
	}
	for (int i = 0; i < (row * col - 1); i++) {
		if ((i + 1) % col != 0) {
			wallArray[count++] = new Wall(i, i + 1);
		}
	}
	for (int j = 0; j < (row * col - col); j++) {
		wallArray[count++] = new Wall(j, j + col);
	}

	int wallUnfilled = count;
	while (!wallFilled) {
		int any = rand() % count;
		if (wallArray[any] != nullptr) {
			// compare rep
			int first = theSet.findSet(wallArray[any]->cell1());
			int second = theSet.findSet(wallArray[any]->cell2());
			if (first != second) { // new route
				theSet.unionSets(wallArray[any]->cell1(), wallArray[any]->cell2());
				wallUnfilled--;
				wallArray[any] = nullptr;
			}
		}
		else if (wallUnfilled == wallSize - (col * row - 1)) {
			wallFilled = true;
		}
	}
	for (int i = 0; i < count; i++) { // final maze
		if (wallArray[i] != nullptr) {
			walls[finalWalls++] =*wallArray[i];
		}
	}

	return finalWalls;
}
