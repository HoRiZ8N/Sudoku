#include "func.h"

int main()
{
    // output.open("output.txt");
    srand(time(0));
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sudoku");
    SetTargetFPS(60);
    GenerateSudoku();
    // PrintString(grid);
    MainLoop();

    return 0;
}
