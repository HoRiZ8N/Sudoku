all: compile run

compile:
	g++ func.cpp main.cpp -o Sudoku.exe -I ./deps/include/ -L ./deps/lib/ -lraylib -lopengl32 -lgdi32 -lwinmm -lshell32
run:
	.\Sudoku.exe 