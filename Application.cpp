/*
* [Game Engine Development]

* Author:   Vatsalya Yadav
* School:   DigiPen Institute of Technology
* Semester: Fall 2022
* Course:   CS529F22

* License:  TBA
*/

/*
- Program execution begin here.
- This file contains the MAIN function.
*/

#include "Game/Game.h"
#include <iostream>

int main()
{
    Game game;

    game.Init();
    game.Run();
    game.Quit();
}
