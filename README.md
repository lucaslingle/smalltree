# smalltree
Tic tac toe in C++

### Build
Build with CMake:
```bash
cmake -S . -B build
cmake --build build
```
This produces three executables in `build/`: `oneplayer` (vs. the computer), `twoplayer` (vs. another human), and `zeroplayer` (prints the game-theoretic value of the empty board, i.e. no players).

### Usage
Start a game against the computer as follows:
```bash
./build/oneplayer
```
The move locations use zero-based raster-scan order, like so:
```
0 1 2
3 4 5
6 7 8
```
The computer will move immediately after you, before the board is printed. The player icons are 1 for X and -1 for O. Blank spaces are denoted by zeros. 

### Example
```
0 0 0 
0 0 0 
0 0 0 
Your turn. Where will you go?
4

-1 0 0 
0 1 0 
0 0 0 
Your turn. Where will you go?
5

-1 0 0 
-1 1 1 
0 0 0 
Your turn. Where will you go?
7

-1 -1 0 
-1 1 1 
0 1 0 
Your turn. Where will you go?
6

-1 -1 -1 
-1 1 1 
1 1 0 
Game status: -1 won
```
As implemented, the computer does not favor shorter games over longer ones when both are won, so it can be a bit cheeky at times. 