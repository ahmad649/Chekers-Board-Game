# Checkers Game in C++

**Checkers Game** is a console-based program that allows two players to enjoy a classic game of Checkers. Players take turns moving their pieces diagonally, capturing opponent's pieces by jumping over them, and aiming to king their pieces by reaching the opposite side of the board.

## Features

* **Two-player Gameplay:** Engage in a match of Checkers against another human player on the same computer.
* **Standard 8x8 Board:** Play on a traditional 8x8 Checkers game board.
* **Diagonal Movement:** Move your pieces diagonally forward to adjacent dark squares.
* **Capturing by Jumping:** Capture opponent's pieces by jumping over them diagonally onto an empty dark square immediately beyond. Multiple jumps in a single turn are possible.
* **Kinging of Pieces:** When one of your pieces reaches the opposite side of the board, it becomes a "king" and gains the ability to move both forwards and backwards diagonally.
* **Turn-Based System:** Players alternate their turns to make moves.
* **Input Validation:** The game provides basic checks to ensure that the selected piece and attempted moves are within the board boundaries.
* **Kill Count:** The program keeps track of the number of pieces captured by each player throughout the game.
* **Game Over:** The game concludes when one player has successfully captured all of the opponent's pieces, and the winner is declared.

## Rules

1.  Red pieces are represented by the symbol **`$`**, and White pieces are represented by **`X`** on the board. Empty playable squares are indicated by **`.`**.
2.  Players take turns moving one of their pieces. Red goes first.
3.  A regular piece can only move diagonally forward one square to an empty dark square.
4.  To capture an opponent's piece, your piece must jump over it diagonally onto an empty dark square immediately beyond. Jumps must be made if they are available.
5.  If a jump is made, and another jump is immediately possible with the same piece, the player *can* (but is not currently forced to, based on the previous "limitations" discussion) continue jumping in the same turn.
6.  When a regular piece reaches the opposite side of the board (the first row for Red, the last row for White), it is crowned a king.
7.  Kings can move one square diagonally in any of the four diagonal directions (forward or backward).
8.  Kings can also capture opponent's pieces by jumping over them diagonally in any of the four diagonal directions, landing on an empty square immediately beyond.
9.  The game ends when one player has no more pieces left, or cannot make a legal move (though the latter is not explicitly checked in the current implementation). The player who captures all of the opponent's pieces wins.

## Instructions to Run the Program

1.  Save the provided C++ code as a `.cpp` file (e.g., `checkers.cpp`).
2.  Open a terminal or command prompt.
3.  Navigate to the directory where you saved the `checkers.cpp` file.
4.  Compile the program using a C++ compiler (like g++):
    ```bash
    g++ checkers.cpp -o checkers
    ```
5.  Run the compiled executable:
    ```bash
    ./checkers
    ```
    (On Windows, it might be `checkers.exe`)

## License

This project is currently unlicensed. Feel free to use the code for personal learning and experimentation. If you intend to distribute or use it in other projects, please consider reaching out to the authors for clarification.
