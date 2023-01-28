#pragma once

// Forward Declerations
class Shader;
class Renderer;
class Camera;
class Texture;

class GameObjectFactory;
class GameObject;
class Player;
class Enemy;

#include <vector>
#include <string>

class Scene
{
public:
	GameObject* m_Player;
	std::vector<GameObject*> m_AllGameObjects;

private:
	std::string m_SceneName;

	GameObjectFactory* m_GameObjectFactory;
	std::vector<GameObject*> m_GameObjectsToDelete;

public:
	Scene();
	~Scene();

	void SetSceneName(const std::string& _sceneName) { m_SceneName = _sceneName; }
	const std::string& GetSceneName() const { return m_SceneName; }

	// STRICT Scene Heirarchy
	virtual void LoadAllResources();	// LOAD EVERYTHING FOR NOW
	void InitializeAllGameObjects(const char* _fileName);
	virtual void BeginPlay();
	virtual void Update();	// CALLED AT END OF UPDATE SCENE
	void DrawScene();
	void UpdateScene();
	void ReleaseAllResources();

private: // Helper functions
	
	// GameObjects Init Functions
	void CreateGameObjects(const char* _fileName);
	void AssignTexturesToGameObjects();

	void DeletePendingGameObjects();

	// AABB - AABB Collision Detection
	bool CheckForCollision(GameObject* _one, GameObject* _two);
};