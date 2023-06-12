#include "tic_tac_toe.h"
#include <sstream>
#include <unistd.h>
#include <sys/mman.h>

#define MIN_GRID_SIZE 3
#define MAX_GRID_SIZE 10

int main(int argc, char *argv[])
{
    int size;

    // ERROR: too many arguments
    if (argc > 2)
    {
        cerr << "Error: too many arguments" << endl;
        cerr << "Usage: " << argv[0]
             << " size (Min: " << MIN_GRID_SIZE << ", Max: " << MAX_GRID_SIZE << ")" << endl;
        return -1;
    }
    // If: user doesnt declare a grid size
    else if (argc == 1)
    {
        size = 3;
    }
    // If: user declares a grid size
    else if (argc == 2)
    {
        stringstream ss(argv[1]);

        // ERROR: invalid input
        if (!(ss >> size) || !ss.eof())
        {
            cerr << "Error: input must be an integer" << endl;
            cerr << "Enter a valid grid size (Min: " << MIN_GRID_SIZE << ", Max: " << MAX_GRID_SIZE << ")" << endl;
            return -1;
        }
        // ERROR: size too small
        else if (size < MIN_GRID_SIZE)
        {
            cerr << "Error: grid size too small" << endl;
            cerr << "Enter a valid grid size (Min: " << MIN_GRID_SIZE << ", Max: " << MAX_GRID_SIZE << ")" << endl;
            return -1;
        }
        // ERROR: size too large
        else if (size > MAX_GRID_SIZE)
        {
            cerr << "Error: grid size too large" << endl;
            cerr << "Enter a valid grid size (Min: " << MIN_GRID_SIZE << ", Max: " << MAX_GRID_SIZE << ")" << endl;
            return -1;
        }
    }

    // Creating the shared memory for the grid
    void *memory = mmap(NULL, sizeof(char) * size * size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    // ERROR: Failed to map memory
    if (memory == MAP_FAILED)
    {
        perror("mmap");
        return -1;
    }

    // Initializing grid by allocating memory for a pointer array
    char **grid = new char *[size];
    for (int i = 0; i < size; i++)
    {
        grid[i] = reinterpret_cast<char *>(static_cast<char *>(memory) + i * size * sizeof(char));
    }

    memset(memory, ' ', sizeof(char) * size * size);

    // Start game
    cout << endl;
    cout << "===== Tic-Tac-Toe Game =====" << endl;
    if (size == 3)
    {
        cout << "Default grid size: 3 x 3" << endl;
    }
    cout << endl;
    print_grid(grid, size);

    // Continue game until game is over
    bool is_game_over = false;
    while (!is_game_over)
    {
        pid_t pid = fork();
        // Parent process | Player 2 = O
        if (pid > 0)
        {
            wait(NULL);
            if (check_gameover(grid, size) == true || check_draw(grid, size) == true)
            {
                exit(0);
            }
            next_move(grid, size, pid, is_game_over);
        }
        // Child process | Player 1 = X
        else
        {
            if (check_gameover(grid, size) == true || check_draw(grid, size) == true)
            {
                exit(0);
            }
            next_move(grid, size, pid, is_game_over);
            exit(0);
        }
    }
    munmap(memory, sizeof(char) * size * size);
    return 0;
}