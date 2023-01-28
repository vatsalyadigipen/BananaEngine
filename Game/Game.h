#pragma once

#include "../GameManager.h"

class Game
{
public:
	Game();
	~Game();

	void Init();
	void Run();
	void Quit();

private:
	GameManager m_GameManager;
};