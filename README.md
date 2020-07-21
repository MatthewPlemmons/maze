### Maze Project
A 3D maze demo, written in C and built using the SDL2 library, compiled on Ubuntu 20.04 with GCC 9.3.  The maze is rendered using raycasting, the same technique as the old Wolfenstein 3D game.  Custom mazes can be loaded in and rendered but are currently restricted to 20x20 size maps.

#### Installation
The SDL2-dev library will be needed for the program to successfully compile.  It can be installed by running
```
$ sudo apt-get update
$ sudo apt-get install libsdl2-dev
```
If needed, documentation on installing the SDL library can be found at https://wiki.libsdl.org/Installation.

Once SDL is installed, clone the repo and compile using GCC.
```
$ gcc -Wall -Werror -Wextra -pedantic *.c -o maze -lm -lSDL2
```
If successful, this will create an executable called `maze` in the directory.

#### Usage
To start the app, run the `maze` executable, passing in `mapfile.txt` as an argument.
```
$ ./maze mapfile.txt
```
The `WASD` keys are used for navigating the maze. `W` and `S` for forward and backward movement, `A` and `D` for left and right rotation. Press `ESC` to close the app.

#### mapfile.txt
`mapfile.txt` is a text representation of the maze that will be rendered when the application is ran. The application scans this file and then renders the contents.  `0` represents an open space, and `1` represents a wall.  The file has to maintain the 20x20 size or it will fail to load, or result in unexpected behavior.

Custom maze designs can be loaded and rendered by editing the contents of this file.
