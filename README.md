# TicTacToe
TicTacToe is a command-line implementation of the classic TicTacToe game, written in C. The game allows one or two players to play against each other or against the computer, which simply randomizes its moves.

# Usage
To start the game, run ./tictactoe. The following options are available:
* -i: Enables the computer player. If not specified, the game will be a two-player game.
* -s size: Designates board size, which is 3 by default. Valid sizes are 3 to 10.
* -h: Displays help information.
# Gameplay
The game is played on a square board of designated size, where players take turns marking a cell with their chosen symbol (usually X or O). The first player to get three of their symbols in a row, column, or diagonal wins the game.

In two-player mode, players take turns entering the coordinates of the cell they wish to mark. In computer player mode, the computer will wait for the user to make a move.

To quit the game on your turn, enter qq.
