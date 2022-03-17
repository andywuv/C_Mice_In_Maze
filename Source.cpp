#include<stdio.h>
#include<stdlib.h>

//for recording path you've walked on every block of maze
typedef struct MazeBlock {
	bool left, right, top, down;
	char block;
} MB;

void InitialMazeBlock(MazeBlock **MB, int y, int x)
{
	MB[y][x].left = true;
	MB[y][x].right = true;
	MB[y][x].top = true;
	MB[y][x].down = true;
	MB[y][x].block = 'W';
}

//showing the map on the screen
void PrintMap(MazeBlock **MB, int row, int col) {
	system("CLS");
	
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			printf("%c", MB[i][j].block);
		}
		printf("\n");
	}

}

//recursively walk in the maze
bool WalkOneStep(MazeBlock **MB, int row, int col, int cury, int curx) {


	PrintMap(MB, row, col);

	//this block is goal!!
	if (MB[cury][curx].block == 'E') {
		return true;
	}

	//mark this block as path
	if(MB[cury][curx].block != 'S')
		MB[cury][curx].block = '*';

	//go right
	if (curx+1 < col && MB[cury][curx].right && (MB[cury][curx+1].block=='.' || MB[cury][curx + 1].block == 'E')) {
		MB[cury][curx].right = false;
		if (WalkOneStep(MB, row, col, cury, curx+1))
			return true;
	}
	//go left
	if (curx-1 >= 0 && MB[cury][curx].left && (MB[cury][curx-1].block == '.' || MB[cury][curx - 1].block == 'E')) {
		MB[cury][curx].left = false;
		if (WalkOneStep(MB, row, col, cury, curx-1))
			return true;
	}
	//go top
	if (cury + 1 < row && MB[cury][curx].top && (MB[cury + 1][curx].block == '.' || MB[cury + 1][curx].block == 'E')) {
		MB[cury][curx].top = false;
		if (WalkOneStep(MB, row, col, cury + 1, curx))
			return true;
	}
	//go down
	if (cury - 1 >= 0 && MB[cury][curx].down && (MB[cury - 1][curx].block == '.' || MB[cury - 1][curx].block == 'E')) {
		MB[cury][curx].down = false;
		if (WalkOneStep(MB, row, col, cury - 1, curx))
			return true;
	}


	//find no way to goal
	//mark that this block is unable to reach the goal
	MB[cury][curx].block = 'X';
	return false;

}

int main(void) {
	//a 2D array to save the map
	MB **map;

	//record the start point coordination
	int starty=-1, startx=-1;

	//a file pointer used to read map file
	FILE * fptr = NULL;
	char InChar = NULL;
	fopen_s(&fptr,"map.txt", "r");

	//read map to count row and column
	fread(&InChar, sizeof(char), 1, fptr);
	//count row and column of the map
	int row = 0, col = 0;
	while(!feof(fptr)) {

		if (InChar == '\n') {
			row += 1;
		}
		//decide the column count by the first row
		if (row==0){
			col += 1;
		}
	
			
		printf("%c", InChar);

		fread(&InChar, sizeof(char), 1, fptr);
	}
	//EOF won't count in, so add 1 for the last row
	row += 1;
	printf("\nrow: %d col: %d\n", row, col);

	//allocate 2D array
	map = (MB**) calloc(row, sizeof(MB*));
	for (int i = 0; i < row; i++) {
		map[i] = (MB*)calloc(col, sizeof(MB));
	}

	//initialize the 2D array
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			InitialMazeBlock(map, i, j);
		}
	}

	//read map again to save the map 
	rewind(fptr);
	fread(&InChar, sizeof(char), 1, fptr);
	int y = 0, x = 0;
	while (!feof(fptr)) {

		//record the start point
		if (InChar == 'S') {
			starty = y;
			startx = x;
		}
		if (InChar == '\n') {
			y += 1;
			x = 0;
		}
		else {
			map[y][x].block = InChar;
			x += 1;
		}

		fread(&InChar, sizeof(char), 1, fptr);
	}

	//close the file
	fclose(fptr);

	printf("starty: %d startx: %d\n\n", starty, startx);
	system("PAUSE");

	PrintMap(map, row, col);

	if (WalkOneStep(map, row, col, starty, startx) == true) {
		printf("GOAL!");
	}
	else {
		printf("FAIL...");
	}

	system("PAUSE");

}