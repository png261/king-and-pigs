<div align="center">
  <a href="https://github.com/png261/king-and-pigs">
    <img src="https://user-images.githubusercontent.com/63899044/226949086-c39646ef-9228-4561-900b-7be8635ea879.png" width="400"/>
  </a>
  <img src="https://user-images.githubusercontent.com/63899044/226949294-75333ced-5a50-4fac-925c-50c47259b90a.gif"/>
</div>

# King and Pigs

**King and Pigs** is a 2D game written in C++ using the SDL2 libraries, Box2D physics engine, and JsonCpp for level parsing. In this game, the player controls a character who must navigate through various levels and defeat enemies.

## Prerequisites

To build and run the game, you will need the following libraries installed on your system:

- SDL2 (https://www.libsdl.org/)
- SDL2_image (https://www.libsdl.org/projects/SDL_image/)
- SDL2_mixer (https://www.libsdl.org/projects/SDL_mixer/)
- SDL2_ttf (https://www.libsdl.org/projects/SDL_ttf/)
- Box2D (https://box2d.org/)
- JsonCpp (http://open-source-parsers.github.io/jsoncpp-docs/doxygen/index.html)

### Linux

To install the prerequisites on Ubuntu, run the following commands in your terminal:
  ```bash
  sudo apt-get update
  sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev libbox2d-dev libjsoncpp-dev
  ```
For Arch Linux, run:
  ```bash
  sudo pacman -S sdl2 sdl2-image sdl2-mixer sdl2-ttf box2d jsoncpp
  ```

### macOS

On macOS, you can use Homebrew to install these libraries.
  ```bash
  brew install sdl2 sdl2_image sdl2_mixer sdl2_ttf box2d jsoncpp
  ```

### Windows

On Windows, you can download the precompiled binaries for each library and install them manually. You can find the binaries on the respective library's website.

## Installation

To build and run the game, follow these steps:

1. Clone this repository to your local machine by running the following command in a terminal or command prompt:
  ```
  git clone https://github.com/png261/king-and-pigs.git
  ```

2. Navigate to the king-and-pigs directory in a terminal or command prompt. Make sure you have installed all the prerequisites, then run the following command to build the game:
  ```
  make
  ```
The binary file will be placed in the `bin/` directory.

3. Run the game by executing the following command:
  ```
  make run
  ```
  Alternatively, you can run the game by executing the binary file:
  ```
  ./bin/binary
  ```

## Controls

The controls for the game are shown in the table below:

| Key                   | Action                           |
| --------------------- | -------------------------------- |
| Arrow Right           | Move right                       |
| Arrow Left            | Move left                        |
| Space                 | Jump                             |
| A                     | Attack                           |
| W                     | Enter the door to the next level |

## Features
### Editing Maps
![image](https://user-images.githubusercontent.com/63899044/230425871-7bcc41a5-cab9-41a6-85a4-83d8db867fd5.png)
You can edit the game maps using Tiled Map Editor. The maps are stored in the `assets/levels/` directory in `.tmj` format. 
To edit a map, open it in Tiled, make your changes, and save the file. The game will automatically reload the updated map the next time you start the game.


# Source Code Structure
For more details please see Docs generate by Doxygen: https://png261.github.io/king-and-pigs/

<!-- CONTACT -->
## Contact
Phuong Nguyen - nhphuong.code@gmail.com

[Github](https://github.com/png261)

