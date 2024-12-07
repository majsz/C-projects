# C-projects
A collection of C language projects I made for my university class.

- ### Palindrom Game:
This is a simple two-player game implemented on a customizable grid (default is 8x8) where players take turns to drop pieces into columns. The game checks for palindromic sequences of length 5 (default) in four directions: horizontally, vertically, and diagonally. The first player to form such a palindrome wins the game.
You can customize the grid's width, height, and palindrome length at compile time by modifying the following preprocessor constants:
```c
    #define WIERSZE // for rows
    #define KOLUMNY // for columns
    #define DLUGOSC // for the required palindrome sequence length
```
The game board is displayed after each move, and the next player is prompted to make their move. The game ends when a palindrome is found or the players choose to quit by entering '.'.
