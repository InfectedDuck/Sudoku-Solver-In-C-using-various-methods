#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define SIZE 9

// Function prototypes
bool is_safe(int grid[SIZE][SIZE], int row, int col, int num);
bool find_empty_location(int grid[SIZE][SIZE], int *row, int *col);
bool solve_sudoku(int grid[SIZE][SIZE]);
void print_grid(int grid[SIZE][SIZE]);
void read_grid(int grid[SIZE][SIZE]);
bool is_valid_grid(int grid[SIZE][SIZE]);
void generate_puzzle(int grid[SIZE][SIZE]);
void read_puzzles_from_file(const char *filename);

// Print the Sudoku grid
void print_grid(int grid[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (grid[row][col] == 0)
                printf(". ");
            else
                printf("%d ", grid[row][col]);
        }
        printf("\n");
    }
}

// Check if it's safe to place num in the specified row and column
bool is_safe(int grid[SIZE][SIZE], int row, int col, int num) {
    // Check the row
    for (int x = 0; x < SIZE; x++)
        if (grid[row][x] == num)
            return false;

    // Check the column
    for (int x = 0; x < SIZE; x++)
        if (grid[x][col] == num)
            return false;

    // Check the 3x3 sub-grid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num)
                return false;

    return true;
}

// Find an empty location in the grid
bool find_empty_location(int grid[SIZE][SIZE], int *row, int *col) {
    int min_possible = SIZE + 1;
    bool found = false;

    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            if (grid[r][c] == 0) {
                int possible_values = 0;
                for (int num = 1; num <= SIZE; num++) {
                    if (is_safe(grid, r, c, num))
                        possible_values++;
                }
                if (possible_values < min_possible) {
                    min_possible = possible_values;
                    *row = r;
                    *col = c;
                    found = true;
                }
            }
        }
    }

    return found;
}

// Solve Sudoku using backtracking and heuristics
bool solve_sudoku(int grid[SIZE][SIZE]) {
    int row, col;

    // If there's no empty location, we're done
    if (!find_empty_location(grid, &row, &col))
        return true;

    // Try numbers from 1 to 9
    for (int num = 1; num <= SIZE; num++) {
        if (is_safe(grid, row, col, num)) {
            grid[row][col] = num;

            if (solve_sudoku(grid))
                return true;

            grid[row][col] = 0; // Undo assignment
        }
    }

    return false; // Trigger backtracking
}

// Read the Sudoku grid from user input
void read_grid(int grid[SIZE][SIZE]) {
    printf("Enter the Sudoku puzzle (0 for empty cells):\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            scanf("%d", &grid[i][j]);
        }
    }
}

// Check if the grid is valid
bool is_valid_grid(int grid[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (grid[i][j] < 0 || grid[i][j] > SIZE) {
                return false;
            }
        }
    }
    return true;
}

// Generate a basic Sudoku puzzle (placeholder function)
void generate_puzzle(int grid[SIZE][SIZE]) {
    // This function currently fills the grid with a fixed pattern
    // You can implement a more sophisticated puzzle generator here
    int example[SIZE][SIZE] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            grid[i][j] = example[i][j];
}

// Read multiple Sudoku puzzles from a file and solve them
void read_puzzles_from_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    int grid[SIZE][SIZE];
    while (fread(grid, sizeof(int), SIZE * SIZE, file) == SIZE * SIZE) {
        if (solve_sudoku(grid)) {
            print_grid(grid);
        } else {
            printf("No solution exists\n");
        }
        printf("\n");
    }

    fclose(file);
}

// Main function
int main() {
    int grid[SIZE][SIZE];

    int choice;
    printf("Select option:\n");
    printf("1. Enter your own Sudoku puzzle\n");
    printf("2. Generate a random Sudoku puzzle\n");
    printf("3. Read and solve puzzles from a file\n");
    printf("Choose an option (1-3): ");
    scanf("%d", &choice);

    clock_t start_time = clock();

    switch (choice) {
        case 1:
            read_grid(grid);
            if (!is_valid_grid(grid)) {
                printf("Invalid grid input.\n");
                return 1;
            }
            break;
        case 2:
            generate_puzzle(grid);
            break;
        case 3:
            read_puzzles_from_file("puzzles.txt");
            return 0; // Exit after processing file puzzles
        default:
            printf("Invalid option.\n");
            return 1;
    }

    if (solve_sudoku(grid)) {
        print_grid(grid);
    } else {
        printf("No solution exists\n");
    }

    clock_t end_time = clock();
    double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", time_taken);

    return 0;
}
