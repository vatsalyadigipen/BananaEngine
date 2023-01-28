#include "Game.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

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

#include <stack>

#include "../BananaWindow.h"
#include "../ResourceManager/ResourceManager.h"

#define WINDOW_TITLE "Banana Engine 1.0.0"

BananaWindowHandler bananaWindow = BananaWindowHandler::getInstance();
//GameManager gameManager = GameManager::GetInstance();

Game::Game()
{

}

Game::~Game()
{

}

void Game::Init()
{
    bananaWindow.m_Props.Title = WINDOW_TITLE;
    bananaWindow.Init();

    ResourceManager::LoadSceneByName("./src/JSON_Files/GameMenu.json", "GameMenu");
    ResourceManager::LoadSceneByName("./src/JSON_Files/Level1.json", "Level1");
    ResourceManager::LoadSceneByName("./src/JSON_Files/EndGame.json", "EndGame");

    m_GameManager.CreateScene(GameLevels::MENU);
    m_GameManager.CreateScene(GameLevels::LEVEL1);
    m_GameManager.CreateScene(GameLevels::END);

    m_GameManager.InititialzeNextScene();
}

void Game::Run()
{
    int count = 1;
    // Main loop
    while (!bananaWindow.ShouldClose())
    {
        //std::cout << "Time: " << count << std::endl;
        if (count % 2000 == 0)
        {
            //m_GameManager.LoadNextScene();
        }

        bananaWindow.Update();

        // update scene
        m_GameManager.UpdateScene();

        // render loop
        m_GameManager.DrawScene();

        bananaWindow.SwapBuffers();

        ++count;
    }
}

void Game::Quit()
{
    m_GameManager.StopGame();

    bananaWindow.ShutDown();

    exit(EXIT_SUCCESS);
}