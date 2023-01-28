#pragma once

#include <string>
#include <stack>

#include "Scene.h"

enum class GameLevels
{
	MENU = 0, LEVEL1, END
};

class GameManager
{
private:
	// Unload everything if true and quit game
	bool bQuitGame;
	
	// Holds state of the next scene
	int m_NextSceneToLoad;

	std::vector<Scene*> m_ListOfAllScenes;
	std::stack<Scene*> m_ScenesStack;

public:
	GameManager();
	~GameManager();
	//static GameManager& GetInstance();

	void CreateScene(GameLevels _typeOfScene);
	void InititialzeNextScene();
	void UpdateScene();
	void DrawScene();

	void PushSceneToStack(Scene* _scene);
	void PopSceneFromStack();
	void LoadNextScene();
	void ReleaseAllContentFromPreviousScene();

	void RestartGame();
	void StopGame();

private: // Helper Functions
	void ClearStack();
	void DeleteAllScenes();
};