#include "func.h"

char currentNumberText[2] = "1";
int currentNumber = 1;
Cell grid[SIZE][SIZE];
Cell solution[SIZE][SIZE];
State currentState = PLAYING;

void MainLoop()
{
    while (!WindowShouldClose())
    {
        GetInput();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && currentState == PLAYING)
        {
            Vector2 mPos = GetMousePosition();
            int indexI = mPos.x / CELL_WIDTH;
            int indexJ = mPos.y / CELL_HEIGHT;
            if (!grid[indexI][indexJ].isGenerated)
            {
                if (grid[indexI][indexJ].num == currentNumber)
                {
                    grid[indexI][indexJ].num = 0;
                }
                else
                {
                    grid[indexI][indexJ].num = currentNumber;
                }
            }
            if (IsSolved())
            {
                currentState = WIN;
            }
        }
        BeginDrawing();
        if (currentState == PLAYING)
        {
            ClearBackground(BLACK);
            DrawGrid();
            DrawText(currentNumberText, 10, 10, 20, RED);
        }
        else
        {
            ClearBackground(WHITE);
            DrawText("YOU WIN", SCREEN_WIDTH / 2 - 80, SCREEN_HEIGHT / 2 - 40, 40, BLACK);
        }
        EndDrawing();
    }
}

void GridInit(Cell grid[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            grid[i][j] = (Cell)
            {
                .i = i,
                .j = j,
                .num = 0,
                .isGenerated = false
            };
        }
    }
}

void CellDraw(Cell cell)
{
    int cellPos = GetCellPos(cell);
    if (cellPos == 0 || cellPos == 1 || cellPos == 3 || cellPos ==  4)
    {
        DrawRectangle(cell.i * CELL_WIDTH, cell.j * CELL_HEIGHT, CELL_WIDTH - 1, CELL_HEIGHT - 1, WHITE);
    }
    else if (cellPos == 6 || cellPos == 7)
    {
        DrawRectangle(cell.i * CELL_WIDTH, cell.j * CELL_HEIGHT, CELL_WIDTH - 1, CELL_HEIGHT - 3, WHITE);
    }
    else if (cellPos == 2 || cellPos == 5)
    {
        DrawRectangle(cell.i * CELL_WIDTH, cell.j * CELL_HEIGHT, CELL_WIDTH - 3, CELL_HEIGHT - 1, WHITE);
    }
    else
    {
        DrawRectangle(cell.i * CELL_WIDTH, cell.j * CELL_HEIGHT, CELL_WIDTH - 3, CELL_HEIGHT - 3, WHITE);
    }
    
    char number[20];
    if (cell.num != 0)
    {
        if (cell.isGenerated)
        {
            DrawText(itoa(cell.num, number, 10), cell.i * CELL_HEIGHT + 25, cell.j * CELL_WIDTH + 6, 100, DARKGREEN);
        }
        else
        {
            DrawText(itoa(cell.num, number, 10), cell.i * CELL_HEIGHT + 25, cell.j * CELL_WIDTH + 6, 100, BLACK);
        }
    }
}

void GetInput()
{
    if (IsKeyPressed(KEY_ONE))
    {
        currentNumber = 1;
        currentNumberText[0] = '1';
    }
    if (IsKeyPressed(KEY_TWO))
    {
        currentNumber = 2;
        currentNumberText[0] = '2';
    }
    if (IsKeyPressed(KEY_THREE))
    {
        currentNumber = 3;
        currentNumberText[0] = '3';
    }
    if (IsKeyPressed(KEY_FOUR))
    {
        currentNumber = 4;
        currentNumberText[0] = '4';
    }
    if (IsKeyPressed(KEY_FIVE))
    {
        currentNumber = 5;
        currentNumberText[0] = '5';
    }
    if (IsKeyPressed(KEY_SIX))
    {
        currentNumber = 6;
        currentNumberText[0] = '6';
    }
    if (IsKeyPressed(KEY_SEVEN))
    {
        currentNumber = 7;
        currentNumberText[0] = '7';
    }
    if (IsKeyPressed(KEY_EIGHT))
    {
        currentNumber = 8;
        currentNumberText[0] = '8';
    }
    if (IsKeyPressed(KEY_NINE))
    {
        currentNumber = 9;
        currentNumberText[0] = '9';
    }
}

void GenerateRandomNumberOnGrid()
{
    int randomCellsCreated = 0;
    while (randomCellsCreated < NUMBER_OF_STARTING_NUMBERS)
    {
        int currI, currJ, randomNum;
        do
        {
            currI = rand() % SIZE;
            currJ = rand() % SIZE;
            randomNum = rand() % SIZE + 1;
        } while (grid[currI][currJ].num != 0 || !IsSafe(grid, currI, currJ, randomNum));

        grid[currI][currJ].num = randomNum;
        randomCellsCreated++;
    }
}

void GenerateSudoku()
{
    GridInit(grid);
    GridInit(solution);
    GenerateRandomNumberOnGrid();
    SolveSudoku(grid);
    CopyBoard(grid, solution);
    GenPuzzle(grid);
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (grid[i][j].num != UNASSIGNED)
            {
                grid[i][j].isGenerated = true;
            }
        }
    }
    
}

bool SolveSudoku(Cell board[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; ++row) {
        for (int col = 0; col < SIZE; ++col) {
            if (board[row][col].num == UNASSIGNED) {
                for (int num = 1; num <= SIZE; ++num) {
                    if (IsSafe(board, row, col, num)) {
                        board[row][col].num = num;

                        if (SolveSudoku(board)) {
                            return true;
                        }

                        board[row][col].num = UNASSIGNED;
                    }
                }
                return false;
            }
        }
    }
    return true;
}



void CopyBoard(Cell source[SIZE][SIZE], Cell copy[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            copy[i][j].num = source[i][j].num;
            copy[i][j].i = source[i][j].i;
            copy[i][j].j = source[i][j].j;
            copy[i][j].isGenerated = source[i][j].isGenerated;
        }
    }
}

int GetCellPos(Cell cell)
{
    return (cell.j % 3) * 3 + (cell.i % 3);
}

bool IsSolved()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (grid[i][j].num != solution[i][j].num)
            {
                return false;
            }
        }
    }
    return true;
}

void DrawGrid()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            CellDraw(grid[i][j]);
        }
    }
}

void CountSolutions(Cell grid[SIZE][SIZE], int &number)
{
    int row, col;

    if (!FindUnassignedLocation(grid, row, col)) {
        number++;
        return;
    }

    for (int i = 0; i < 9 && number < 2; i++) {
        if (IsSafe(grid, row, col, i + 1)) {
            grid[row][col].num = i + 1;  

            CountSolutions(grid, number);

            grid[row][col].num = 0;
        }
    }
}

bool IsSafe(Cell grid[SIZE][SIZE], int row, int col, int num)
{
    for (int i = 0; i < 9; i++) {
        if (grid[row][i].num == num || grid[i][col].num == num) {
            return false;
        }
    }

    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = startRow; i < startRow + 3; i++) {
        for (int j = startCol; j < startCol + 3; j++) {
            if (grid[i][j].num == num) {
                return false;
            }
        }
    }

    return true;
}

void GenPuzzle(Cell grid[SIZE][SIZE])
{
    std::pair<int, int> positions[SIZE * SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            positions[i * SIZE + j] = {i, j};
        }
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(positions, positions + SIZE * SIZE, g); 

    for (int k = 0; k < SIZE * SIZE; k++)
    {
        int i = positions[k].first;
        int j = positions[k].second;

        int temp = grid[i][j].num;
        grid[i][j].num = 0;

        int check = 0;
        CountSolutions(grid, check); 
        if (check != 1)
        {
            grid[i][j].num = temp;
        }
    }
}

bool FindUnassignedLocation(Cell grid[SIZE][SIZE], int &row, int &col)
{
    for (row = 0; row < 9; row++)
    {
        for (col = 0; col < 9; col++)
        {
            if (grid[row][col].num == UNASSIGNED) {
                return true;
            }
        }
    }

    return false;
}

// void PrintString(Cell grid[SIZE][SIZE])
// {
//     for (int i = 0; i < SIZE; i++)
//     {
//         for (int j = 0; j < SIZE; j++)
//         {
//             if (grid[j][i].num != UNASSIGNED)
//             {
//                 output << grid[j][i].num;
//             }
//             else
//             {
//                 output << '.';
//             }
//         }
        
//     }
// }