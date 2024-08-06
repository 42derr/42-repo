#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#define N 20  // Size of the maze

// Directions for moving in the maze
int rowDirs[] = {1, -1, 0, 0};  // Down, Up, Right, Left
int colDirs[] = {0, 0, 1, -1};

// Queue structure for BFS
typedef struct {
    int x, y, dist;
} Node;

// Function prototypes
bool isSafe(int x, int y, char maze[N][N], bool visited[N][N]);
void printMazeWithPath(int sol[N][N]);
int bfs(char maze[N][N], int sol[N][N]);

// Checks if maze[x][y] is a valid move
bool isSafe(int x, int y, char maze[N][N], bool visited[N][N]) {
    return (x >= 0 && x < N && y >= 0 && y < N && maze[x][y] != '1' && !visited[x][y]);
}

// BFS algorithm to find the shortest path
int bfs(char maze[N][N], int sol[N][N]) {
    bool visited[N][N] = {false};
    Node queue[N*N];
    int front = 0, rear = 0;

    // Initialize start point
    queue[rear++] = (Node){0, 0, 0};  // Starting from (0, 0)
    visited[0][0] = true;

    while (front < rear) {
        Node current = queue[front++];

        // Check if we reached the end
        if (current.x == N-1 && current.y == N-1) {
            sol[current.x][current.y] = 1;
            return current.dist;  // Return the number of moves
        }

        // Explore all 4 directions
        for (int i = 0; i < 4; i++) {
            int newX = current.x + rowDirs[i];
            int newY = current.y + colDirs[i];

            if (isSafe(newX, newY, maze, visited)) {
                visited[newX][newY] = true;
                queue[rear++] = (Node){newX, newY, current.dist + 1};
                sol[newX][newY] = 1;
            }
        }
    }

    return -1;  // No path found
}

// Prints the maze with 'S' for start, 'E' for end, and path marked with '*'
void printMazeWithPath(int sol[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == 0 && j == 0)
                printf(" S ");  // Start
            else if (i == N-1 && j == N-1)
                printf(" E ");  // End
            else if (sol[i][j] == 1)
                printf(" * ");  // Path
            else
                printf("   ");  // Empty space
        }
        printf("\n");
    }
}

// Main function to solve the maze problem
int main() {
    // Example 20x20 maze with '0' as path, '1' as wall, 'S' as start, and 'E' as end
    char *mazeArray[N] = {
        "S00000000000000000000",
        "01011111111111111000",
        "00000000000011111000",
        "11111000000000010000",
        "10000111111111110000",
        "00000000000000000000",
        "11111111111111111000",
        "10000000000000010000",
        "11111111111111100000",
        "10000000000000000000",
        "00000000000000011111",
        "11111111000000000000",
        "00000000000011110000",
        "11111111111110000000",
        "00000000000000000000",
        "11111111111111110000",
        "00000000000000010000",
        "11111111111111110000",
        "00000000000000000101",
        "1111111111111111000E"
    };

    // Convert the mazeArray to a 2D char array
    char maze[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            maze[i][j] = mazeArray[i][j];
        }
    }

    int sol[N][N] = {0};
    int moves = bfs(maze, sol);

    if (moves == -1) {
        printf("Solution doesn't exist\n");
    } else {
        printMazeWithPath(sol);
        printf("Number of moves: %d\n", moves);
    }

    return 0;
}
