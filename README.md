# Sudoku Solver

## Overview

This project is a Sudoku solver implemented in C. It provides functionality to solve Sudoku puzzles using a backtracking algorithm enhanced with heuristics. Users can input their own puzzles, generate a basic puzzle, or read puzzles from a file and output the solved puzzles to another file.

## Features

- **Solve Sudoku Puzzles**: Uses backtracking and heuristics to solve the puzzle.
- **Custom Input**: Allows users to input their own Sudoku puzzles.
- **Puzzle Generation**: Generates a basic Sudoku puzzle with a fixed pattern.
- **File Processing**: Reads multiple puzzles from a file and writes the solutions to an output file.

## Getting Started

To get started with the Sudoku solver, follow these steps:

### Compilation

1. Ensure you have a C compiler installed (e.g., `gcc`).
2. Compile the code using the following command:
   ```bash
   gcc -o sudoku_solver sudoku_solver.c

### Options
Upon running the program, you will be prompted to select one of the following options:

1. **Enter your own Sudoku puzzle**:  
   Input a Sudoku grid manually. Ensure that the grid is valid with numbers between 0 and 9.
   
2. **Generate a random Sudoku puzzle**:  
   Generates a basic Sudoku puzzle with a fixed pattern.
   
3. **Read and solve puzzles from a file**:  
   Provide an input file containing multiple Sudoku puzzles and an output file to save the solutions.

### Functions

- **`print_grid(int grid[SIZE][SIZE])`**:  
  Prints the Sudoku grid.

- **`is_safe(int grid[SIZE][SIZE], int row, int col, int num)`**:  
  Checks if placing `num` in the given cell is valid.

- **`find_empty_location(int grid[SIZE][SIZE], int *row, int *col)`**:  
  Finds an empty cell in the grid.

- **`solve_sudoku(int grid[SIZE][SIZE])`**:  
  Solves the Sudoku puzzle using backtracking.

- **`read_grid(int grid[SIZE][SIZE])`**:  
  Reads the Sudoku grid from user input.

- **`is_valid_grid(int grid[SIZE][SIZE])`**:  
  Validates the Sudoku grid.

- **`generate_puzzle(int grid[SIZE][SIZE])`**:  
  Generates a basic Sudoku puzzle.

- **`read_puzzles_from_file(const char *filename, const char *output_filename)`**:  
  Reads puzzles from a file and writes the solutions to another file.

## License

This project is licensed under the [MIT License](https://opensource.org/licenses/MIT). See the [LICENSE](LICENSE.txt) file for details.
