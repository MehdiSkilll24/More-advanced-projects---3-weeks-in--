#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define ROWS 9
#define COLS 9

// Initialize the maze with empty spaces
char maze[ROWS][COLS] = {
    { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
};

// Directions array for 8 possible moves: right, down, left, up, and diagonals
int dr[] = {0, 1, 0, -1, 1, -1, 1, -1};
int dc[] = {1, 0, -1, 0, 1, -1, -1, 1};

// Function to print the maze
void Print_Maze(){
    for (int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            printf("%c ", maze[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Depth-First Search (DFS) function for pathfinding
int dfs(int r, int c) {
    // Check if out of bounds
    if (r < 0 || r >= ROWS || c < 0 || c >= COLS) {
        return 0;
    }

    // If 'E' (Exit) is reached, return success
    if (maze[r][c] == 'E') {
        return 1;
    }

    // If the cell is a wall '#' or already visited '.', return failure
    if (maze[r][c] == '#' || maze[r][c] == '.') {
        return 0;
    }

    // Mark the current cell as visited
    maze[r][c] = '.';

    // Explore all 8 possible directions (right, down, left, up, and diagonals)
    for (int i = 0; i < 8; i++) {
        if (dfs(r + dr[i], c + dc[i])) {  // Recursively search in all directions
            return 1;  // If any direction leads to the exit, return success
        }
    }

    // If no valid path is found, mark this cell as a dead end 'X'
    maze[r][c] = 'X';
    return 0;  // Return failure
}

int main(){
    srand(time(0)); // Initialize the random number generator

    int rand_R_W, rand_C_W;

    // Randomly set the starting point 'S'
    int rand_R_S = rand() % ROWS;
    int rand_C_S = rand() % COLS;
    maze[rand_R_S][rand_C_S] = 'S';

    // Randomly set the exit point 'E', ensuring it's not the same as the start
    int rand_R_E , rand_C_E;
    do {
        rand_R_E = rand() % ROWS;
        rand_C_E = rand() % COLS;
    } while(maze[rand_R_E][rand_C_E] == 'S'); // Make sure 'E' is not 'S'
    maze[rand_R_E][rand_C_E] = 'E';

    // Randomly generate walls '#' in the maze
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (maze[i][j] == ' ') {  // Only place walls on empty spaces
                int rand_wall = rand() % 2;
                if (rand_wall == 1) {
                    maze[i][j] = '#';  // Mark the cell as a wall '#'
                }
            }
        }
    }

    // Print the maze before running DFS
    Print_Maze();

    // Call the DFS function from the start point and check if a path to 'E' is found
    if (dfs(rand_R_S, rand_C_S)) {
        printf("Found !\n");
    } else {
        printf("Not found !\n");
    }

    // Print the maze after the DFS attempt (showing the path marked with '.' and dead ends with 'X')
    Print_Maze();
}
