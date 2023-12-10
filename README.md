
# Grid Traversal Project

## Overview
This project involves developing a program to find the fastest way to traverse a grid from the top to the bottom. The program calculates the shortest time and path to traverse a grid, given specific rules for movement and time spent at each grid location.

## Features
- Grid traversal algorithm to find the fastest path from top to bottom.
- Handling of binary and text file formats for input and output.
- Calculation of the fastest times and paths for each entry point on the top row of the grid.

## Files
- `grid_traversal.c`: Implementation file for the grid traversal algorithm.
- `grid_utils.h`: Header file defining utility functions and structures.

## How to Run
1. Compile the program using GCC with the following command:
   ```
   gcc -std=c99 -pedantic -Wvla -Wall -Wshadow -O3 *.c -o pa3
   ```
2. Run the program with:
   ```
   ./pa3 binary_grid_file text_grid_file fastest_times_file fastest_path_file
   ```
   - `binary_grid_file`: Input file in binary format representing the grid.
   - `text_grid_file`: Output file storing the grid in text form.
   - `fastest_times_file`: Output file storing the fastest time for each entry location at the top row.
   - `fastest_path_file`: Output file storing the fastest path from top to bottom.

## Input/Output File Formats
- **Binary Grid File**: Contains the grid dimensions and the time values for each grid location.
- **Text Grid File**: Textual representation of the grid.
- **Fastest Times File**: Binary file with the fastest times to exit the grid for each entry point.
- **Fastest Path File**: Binary file with the coordinates of the fastest path through the grid.

