#include "GameManager.h"

#include "Levels/Menu/GameMenu.h"
#include "Levels/Level1/Level1.h"
#include "Levels/EndGame/EndGame.h"

#include <iostream>

GameManager::GameManager()
	: bQuitGame(false), m_NextSceneToLoad(0)
{}

// GameLevels are defined inside GameLevels
void GameManager::CreateScene(GameLevels _typeOfScene)
{
	// TODO: Create a scene factory later
	Scene* scene = nullptr;
	if (_typeOfScene == GameLevels::MENU)
		scene = new GameMenu;
	else if (_typeOfScene == GameLevels::LEVEL1)
		scene = new Level1;
	else
		scene = new EndGame;

	m_ListOfAllScenes.push_back(scene);	// push to vector
}

void GameManager::InititialzeNextScene()
{
	if (m_NextSceneToLoad > (int)m_ListOfAllScenes.size())
	{
		// Restart the game
		RestartGame();

		return;
	}

	PushSceneToStack(m_ListOfAllScenes[m_NextSceneToLoad++]);
	Scene* currentScene = m_ScenesStack.top();
	std::string sceneName = currentScene->GetSceneName();

	std::cout << "==========================================" << std::endl;
	std::cout << "\nCREATING SCENE: " << sceneName << "\n" << std::endl;
	std::cout << "==========================================" << std::endl;

	currentScene->LoadAllResources();
	currentScene->InitializeAllGameObjects(ResourceManager::GetSceneByName(sceneName));
	currentScene->BeginPlay();
}

void GameManager::UpdateScene()
{
	if (bQuitGame == true)
	{
		ClearStack();
		DeleteAllScenes();
	}

	Scene* currentScene = m_ScenesStack.top();

	if (currentScene != NULL)
		currentScene->UpdateScene();
}

void GameManager::DrawScene()
{
	Scene* currentScene = m_ScenesStack.top();

	if (currentScene != NULL)
		currentScene->DrawScene();
}

void GameManager::PushSceneToStack(Scene* scene)
{
	m_ScenesStack.push(scene);
}

void GameManager::PopSceneFromStack()
{
	m_ScenesStack.pop();
}

void GameManager::LoadNextScene()
{
	if (m_NextSceneToLoad < (int)m_ListOfAllScenes.size())
	{
		PopSceneFromStack();
		InititialzeNextScene();
	}
	else
	{
		RestartGame();
	}
	//if (m_ScenesStack.size() > 1)
	//{
	//	ReleaseAllContentFromPreviousScene();
	//	PopSceneFromStack();
	//
	//	InititialzeNextScene();
	//}
	//else
	//{
	//	// TODO: Don't create use the previous sceneVector and push it into the stack
	//	for (auto scene : m_ListOfAllScenes)
	//		m_ScenesStack.push(scene);
	//
	//	//CreateScene(GameLevels::MENU);
	//	InititialzeNextScene();
	//}
}

void GameManager::ReleaseAllContentFromPreviousScene()
{
	Scene* currentScene = m_ScenesStack.top();
	if (currentScene)
	{
		currentScene->ReleaseAllResources();
	}
}

void GameManager::RestartGame()
{
	ClearStack();
	m_NextSceneToLoad = 0;
	InititialzeNextScene();
}

void GameManager::StopGame()
{
	//bQuitGame = true;
	ClearStack();
	// TODO: Find another solution later
	DeleteAllScenes();
}

void GameManager::ClearStack()
{
	int stackSize = m_ScenesStack.size();
	for (int i = 0; i < stackSize; ++i)
		m_ScenesStack.pop();
}

void GameManager::DeleteAllScenes()
{
	for (auto scene_ : m_ListOfAllScenes)
		if (scene_ != nullptr)
			delete scene_;

	m_ListOfAllScenes.clear();
}

GameManager::~GameManager()
{
	std::cout << "GameManager Destructor Called!" << std::endl;
}