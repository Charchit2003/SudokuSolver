#include <iostream>
#include <array>

using std::cout;
using std::endl;

#define N 9
#define BLANK 0
#define SPACE " "
#define LINE "|"
#define NEW_ROW "-------------------------------------"
#define GRID_FULL std::make_pair(9, 9)

// Function to print the Sudoku grid
void print_grid(int grid[N][N])
{
    for (int i = 0; i < N; i++)
    {
        cout << SPACE << SPACE << SPACE << SPACE << endl;
        cout << NEW_ROW << endl;
        for (int j = 0; j < N; j++)
        {
            cout << SPACE;
            if (BLANK == grid[i][j])
            {
                cout << SPACE;
            }
            else
            {
                cout << grid[i][j];
            }
            cout << SPACE;
            cout << LINE;
        }
    }
    cout << endl << NEW_ROW << endl << endl;;
}

// Function to check if a number is used in the specified row
bool used_in_row(int grid[N][N], int row, int num)
{
    for (int col = 0; col < N; col++)
        if (grid[row][col] == num)
        {
            return true;
        }
    return false;
}

// Function to check if a number is used in the specified column
bool used_in_col(int grid[N][N], int col, int num)
{
    for (int row = 0; row < N; row++)
        if (grid[row][col] == num)
        {
            return true;
        }
    return false;
}

// Function to check if a number is used in the specified 3x3 box
bool used_in_box(int grid[N][N], int box_start_row, int box_start_col, int num)
{
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (grid[row + box_start_row][col + box_start_col] == num)
            {
                return true;
            }
    return false;
}

// Function to check if it is safe to assign a number to a location
bool is_safe(int grid[N][N], int row, int col, int num)
{
    return !used_in_row(grid, row, num) &&
        !used_in_col(grid, col, num) &&
        !used_in_box(grid, row - row % 3, col - col % 3, num);
}

// Function to get an unassigned location in the grid
std::pair<int, int> get_unassigned_location(int grid[N][N])
{
    for (int row = 0; row < N; row++)
        for (int col = 0; col < N; col++)
            if (grid[row][col] == BLANK)
            {
                return std::make_pair(row, col);
            }
    return GRID_FULL;
}

// Function to solve the Sudoku puzzle
bool solve_sudoku(int grid[N][N])
{
    if (GRID_FULL == get_unassigned_location(grid))
    {
        return true;
    }

    std::pair<int, int> row_and_col = get_unassigned_location(grid);
    int row = row_and_col.first;
    int col = row_and_col.second;

    for (int num = 1; num <= 9; num++)
    {
        if (is_safe(grid, row, col, num))
        {
            grid[row][col] = num;

            if (solve_sudoku(grid))
            {
                return true;
            }

            grid[row][col] = BLANK;
        }
    }

    return false;
}

int main()
{
    cout << "********************************\n\n\tSudoku Solver\n\n********************************" << endl << endl;

    int grid[N][N] = { { 0, 9, 0, 0, 0, 0, 8, 5, 3 },
                       { 0, 0, 0, 8, 0, 0, 0, 0, 4 },
                       { 0, 0, 8, 2, 0, 3, 0, 6, 9 },
                       { 5, 7, 4, 0, 0, 2, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 9, 0, 0, 6, 3, 7 },
                       { 9, 4, 0, 1, 0, 8, 5, 0, 0 },
                       { 7, 0, 0, 0, 0, 6, 0, 0, 0 },
                       { 6, 8, 2, 0, 0, 0, 0, 9, 0 } };

    print_grid(grid);

    if (true == solve_sudoku(grid))
    {
        print_grid(grid);
    }
    else
    {
        cout << "No solution exists for the given Sudoku" << endl << endl;
    }

    return 0;
}
