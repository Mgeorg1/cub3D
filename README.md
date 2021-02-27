# cub3d
21 school (ecole 42) implementation of "3d" game raycasting engine (like Wolfenstein 3d engine).

Type "make" to compile and "./cub3d map.cub" to run it. Flag "--save" to make screenshot.

In ".cub" file is a scene description file. All element in line can be separated by one or more spaces.
Each line except the map can be separated by one or more '\n'.

Specificators:

R - resolution;

F and C - floor and ceiling color in rgb. Each parametr must separated by only comma;

NO, SO, WE, EA - path to texture for north/south/west/east wall;

S - path to sprite texture;

FILE MUST END BY ONE OR ZERO EMPTY LINE!

1 - wall;

0 - ceiling;

2 - sprite;

N/S/W/E - player;

Controls:

WASD - move, left/right arrow - rotate;
