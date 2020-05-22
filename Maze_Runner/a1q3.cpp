// Course: 							DSA555 NSA
// Assignment:      		1 - Part 3
// Name: 								Xiaomin (Mica) Luo
// Seneca Student ID:   133728170
// Seneca email: 				xluo42@myseneca.ca

#include "wall.h"
#include "maze.h"

// runMaze() will find a path, markup the maze with path and pass back an array,
// return the number of cells along the pathway from startCell to endCell

// recursive
bool runMaze(Maze& theMaze, int path[], int startCell, int endCell, int& cellCount) {
	int rows = theMaze.numRows();
	int startRow = theMaze.getRow(startCell);
	int columns = theMaze.numCols();
	int startColumn = theMaze.getCol(startCell);
	int leftCell = startCell - 1;
	int rightCell = startCell + 1;
	int topCell = startCell - columns;
	int bottomCell = startCell + columns;

	theMaze.mark(startCell);

	if (startCell == endCell) { // easiest
		path[cellCount++] = startCell;
		return true;
	}

	if (startColumn != 0 && !theMaze.isMarked(leftCell) && theMaze.canGo(startCell, leftCell)) { // left
		if (runMaze(theMaze, path, leftCell, endCell, cellCount))
		{
			path[cellCount++] = startCell;
			return true;
		}
	}

	if (startRow != 0 && !theMaze.isMarked(topCell) && theMaze.canGo(startCell, topCell)) { // top
		if (runMaze(theMaze, path, topCell, endCell, cellCount))
		{
			path[cellCount++] = startCell;
			return true;
		}
	}

	if (startColumn != columns - 1 && !theMaze.isMarked(rightCell) && theMaze.canGo(startCell, rightCell)) { // right
		if (runMaze(theMaze, path, rightCell, endCell, cellCount))
		{
			path[cellCount++] = startCell;
			return true;
		}
	}

	if (startRow != rows - 1 && !theMaze.isMarked(bottomCell) && theMaze.canGo(startCell, bottomCell)) { // bottom
		if (runMaze(theMaze, path, bottomCell, endCell, cellCount))
		{
			path[cellCount++] = startCell;
			return true;
		}
	}

	return false;

}

// for client call
int runMaze(Maze& theMaze, int path[], int startCell, int endCell) {
	int cellCount = 0;
	runMaze(theMaze, path, endCell, startCell, cellCount);

	return cellCount;
}
