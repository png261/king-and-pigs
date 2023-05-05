<div align="center">
  <a href="https://github.com/png261/king-and-pigs">
    <img src="https://user-images.githubusercontent.com/63899044/226949086-c39646ef-9228-4561-900b-7be8635ea879.png" width="400"/>
  </a>
</div>

# King and Pigs

## Description
**King and Pigs** is a 2D game written in C++ using the SDL2 libraries, Box2D physics engine, and JsonCpp for level parsing. In this game, the player controls a character who must navigate through various levels and defeat enemies.

## Installation

To build and run the game, follow these steps:

1. Clone this repository to your local machine by running the following command in a terminal or command prompt:
  ```
  git clone https://github.com/png261/king-and-pigs.git
  ```

2. Navigate to the king-and-pigs directory in a terminal or command prompt. Make sure you have installed all the prerequisites, then run the following command to build the game:
  ```
  cmake -B build && cmake --build build
  ```
The binary file will be placed in the `build/bin` directory.

3. Run the game by executing the following command:
  ```
  ./build/bin/king-and-pigs
  ```

## Controls
| Key                   | Action                           |
| --------------------- | -------------------------------- |
| D                     | Move right                       |
| A                     | Move left                        |
| W                     | Enter the door to the next level |
| K                     | Jump                             |
| J                     | Attack                           |

## Features
### Editing Maps
![image](https://user-images.githubusercontent.com/63899044/230425871-7bcc41a5-cab9-41a6-85a4-83d8db867fd5.png)
You can edit the game maps using Tiled Map Editor. The maps are stored in the `assets/levels/` directory in `.tmj` format. 
To edit a map, open it in Tiled, make your changes, and save the file. The game will automatically reload the updated map the next time you start the game.


## Documentation
For more details please see documents generate by Doxygen: https://png261.github.io/king-and-pigs/

## Credits
- [Kings and Pigs asset pack](https://pixelfrog-assets.itch.io/kings-and-pigs)

- [SDL2](https://www.libsdl.org/)
- [SDL2_image](https://www.libsdl.org/projects/SDL_image/)
- [SDL2_mixer](https://www.libsdl.org/projects/SDL_mixer/)
- [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/)
- [SDL2_gfx](https://www.ferzkopp.net/Software/SDL2_gfx/Docs/html/index.html)
- [Box2D](https://box2d.org/)
- [JsonCpp](http://open-source-parsers.github.io/jsoncpp-docs/doxygen/index.html)
- [TinyXML-2](https://github.com/leethomason/tinyxml2)

- [SDL Game Development](https://www.packtpub.com/product/sdl-game-development/9781849696821)
- [Game Programming Patterns](gameprogrammingpatterns.com)

- [alexdantas/sdl2-platformer](https://github.com/alexdantas/sdl2-platformer)
- [AdriaPm/GameDevelopment_Platformer_Game](https://github.com/AdriaPm/GameDevelopment_Platformer_Game)

<!-- CONTACT -->
## Contact
Phuong Nguyen - nhphuong.code@gmail.com

[Github](https://github.com/png261)

