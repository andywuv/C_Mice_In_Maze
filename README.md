# C_Mice_In_Maze
A Smart mice will find the way out from the maze

This is a C-language project.<br />
Program will walk in a maze, and try every way recursively to get out.<br />
This program contains:
1. a main C-language file (Source.cpp)
2. a maze map file that you can cusomize (map.txt)

About the format of the maze map:
* 'S' means Start Point
* 'E' means End Point
* '.' means a way to walk on.
* other characters mean wall.<br />
* Each column of the map must has same length, and each row must has same length, too.

When you run the program, the mice will set out from the Start Point, and:
* marks its path by '*'
* mark some unavailable block by 'X' (it thinks those block can't let it reach the End point) 
* when it find the End point, the program will stop, and say "GOAL!"
* if the mice can't find a way out, it will say "FAIL..."

Have fun with your mice!
