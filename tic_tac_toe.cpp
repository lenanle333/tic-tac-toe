#include "tic_tac_toe.h"
#include <sstream>

// Prints the current grid of the game
void print_grid(char **grid, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << " " << grid[i][j] << " ";
            if (j < size - 1)
            {
                cout << "|";
            }
        }
        cout << endl;
        if (i < size - 1)
        {
            for (int k = 0; k < size; k++)
            {
                cout << "----";
            }
            cout << endl;
        }
    }
    cout << endl;
};

// Checks if there are winners
bool check_gameover(char **grid, int size)
{

    int x_count = 0;
    int o_count = 0;
    // Check rows for winner
    for (int row = 0; row < size; row++)
    {
        x_count = 0;
        o_count = 0;
        for (int col = 0; col < size; col++)
        {
            if (grid[row][col] == 'X')
            {
                x_count += 1;
            }
            else if (grid[row][col] == 'O')
            {
                o_count += 1;
            }

            if (x_count == size)
            {
                return true;
            }
            else if (o_count == size)
            {
                return true;
            }
        }
    }

    // Check columns for winner
    for (int row = 0; row < size; row++)
    {
        x_count = 0;
        o_count = 0;
        for (int col = 0; col < size; col++)
        {
            if (grid[col][row] == 'X')
            {
                x_count += 1;
            }
            else if (grid[col][row] == 'O')
            {
                o_count += 1;
            }

            if (x_count == size)
            {
                return true;
            }
            else if (o_count == size)
            {
                return true;
            }
        }
    }
    // Check top left -> bottom right diagonal for winner
    x_count = 0;
    o_count = 0;
    for (int row = 0; row < size; row++)
    {
        if (grid[row][row] == 'X')
        {
            x_count += 1;
        }
        else if (grid[row][row] == 'O')
        {
            o_count += 1;
        }

        if (x_count == size)
        {
            return true;
        }
        else if (o_count == size)
        {
            return true;
        }
    }
    // Check top right -> bottom left diagonal for winner
    x_count = 0;
    o_count = 0;
    for (int row = 0; row < size; row++)
    {
        if (grid[row][size - row - 1] == 'X')
        {
            x_count += 1;
        }
        else if (grid[row][size - row - 1] == 'O')
        {
            o_count += 1;
        }

        if (x_count == size)
        {
            return true;
        }
        else if (o_count == size)
        {
            return true;
        }
    }

    return false;
}

// Checks if there is a draw
bool check_draw(char **grid, int size)
{
    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            if (grid[row][col] == ' ')
            {
                return false;
                break;
            }
        }
    }
    return true;
}
void next_move(char **grid, int size, int pid, bool &is_game_over)
{
    int row, col;
    string move = "";
    bool valid_move = false;
    // Displays player's turn
    string player = (pid > 0) ? "Player 2 (O)" : "Player 1 (X)";
    while (!valid_move)
    {
        cout << player << ": your turn" << endl;
        cout << "Enter the row and column number to mark your move (e.g. 2 3)" << endl;

        cout << "Row and column: ";
        getline(cin, move);
        cout << endl;

        // ERROR: invalid integer
        try
        {
            row = stoi(move.substr(move.find(' ') + 1));
            col = stoi(move.substr(0, move.find(' ')));
        }
        catch (exception &e)
        {
            cerr << "Error: input must be an integer" << endl;
            continue;
        }
        // ERROR: user doesnt enter 2 inputs
        istringstream iss(move);
        string token;
        int count = 0;
        while (iss >> token)
        {
            count++;
        }
        if (count != 2)
        {
            cerr << "Error: missing input" << endl;
            continue;
        }
        else if (count > 2)
        {
            cerr << "Error: too many input" << endl;
            continue;
        }
        // ERROR: coordinates out of bounds
        if (row > size || row < 1 || col > size || col < 1)
        {
            cerr << "Error: input out of bounds (Min: 0, Max: " << size << ")" << endl;
            continue;
        }

        // ERROR: coordinate already marked
        if (grid[row - 1][col - 1] != ' ')
        {
            cerr << "Error: that spot is already marked" << endl;
            continue;
        }
        valid_move = true;
    }

    // Mark the grid
    pid > 0 ? grid[row - 1][col - 1] = 'O' : grid[row - 1][col - 1] = 'X';
    print_grid(grid, size);

    // Check winner
    if (check_gameover(grid, size))
    {
        cout << player << " wins!" << endl;
        print_grid(grid, size);
        is_game_over = true;
        return;
    }
    if (check_draw(grid, size))
    {
        cout << "It's a draw!" << endl;
        print_grid(grid, size);
        is_game_over = true;
        return;
    }
};