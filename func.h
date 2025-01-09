#pragma once

#include "deps/include/raylib.h"
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <random>
#include <fstream>

// std::ofstream output;

#define UNASSIGNED 0
#define SIZE 9
#define NUMBER_OF_STARTING_NUMBERS 11
#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 900
#define CELL_WIDTH SCREEN_WIDTH / SIZE
#define CELL_HEIGHT SCREEN_HEIGHT / SIZE

enum State {
    PLAYING,
    WIN
};

struct Cell
{
    int i;
    int j;
    int num;
    bool isGenerated;
};

void MainLoop();
void GridInit(Cell grid[SIZE][SIZE]);
void CellDraw(Cell cell);
void GetInput();
bool SolveSudoku(Cell board[SIZE][SIZE]);
void GenerateRandomNumberOnGrid();
void GenerateSudoku();
void CopyBoard(Cell source[SIZE][SIZE], Cell copy[SIZE][SIZE]);
int GetCellPos(Cell cell);
bool IsSolved();
void DrawGrid();
void CountSolutions(Cell grid[SIZE][SIZE], int &number);
bool IsSafe(Cell grid[SIZE][SIZE], int row, int col, int num);
void GenPuzzle(Cell grid[SIZE][SIZE]);
bool FindUnassignedLocation(Cell grid[SIZE][SIZE], int &row, int &col);
// void PrintString(Cell grid[SIZE][SIZE]);