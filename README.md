# Clue

COMPILATION:
type "make" in the project directory to compile the program.
Or you can run gcc -o adventure adventure.c rooms/rooms.c items/items.c to compile the program.

RUNNING:
type "./adventure" in the project directory to run the program.

BOARD STRUCTURE:
The board is a 3x3 grid of rooms.
The board is connected to its neighbours by pointers.
Each room has a pointer to the room to the north, south, east and west.

GAMEPLAY:
The player starts in a random room.
The player will be promped to input a command which can be viewed by typing "help".
The player has to use the commands to navigate the board and collect items.
The objective of the game is to guess the correct character and item in the correct room within 10 guesses.
