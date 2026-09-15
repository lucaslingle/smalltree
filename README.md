# smalltree
Tic tac toe in C++

### Usage
Compile the code somehow (will add cmake later to make easier across platforms)
```bash
clang++ -std=c++11 -stdlib=libc++ -I. oneplayer.cpp tree.cpp state.cpp -o tictactoe.out
```

Start a game as follows:
```bash
./tictactoe.out
```
The entered move locations correspond to the grid locations in zero-based raster-scan order, so upper left is 0, upper right is 2, center left is 3, etc.

### Example game
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
game status: -1 won
```
As implemented, the computer does not favor shorter games over longer ones when both are won, so it can be a bit cheeky at times. 