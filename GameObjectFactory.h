#pragma once

#include "Player/Player.h"
#include "Player/Enemy.h"

#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"

// Singleton Class
class GameObjectFactory
{
private:
    static GameObjectFactory* m_Instance;

public:
    static GameObjectFactory& GetInstance();

    // These methods create a list of GameObjects
    // Uses std::vector<> to save them
    std::vector<GameObject*> CreateAllGameObjects(const char* _filename);
    std::vector<GameObject*> CreateGameObjectCopies(const char* _filename, const unsigned int& num_copies);
    
    // These methods create single GameObjects
    GameObject* CreateGameObject(const char* filename);
private: 
    GameObjectFactory();

    // Helper Functions //////////////////////////////////////
    // Creates GameObjects for you
	GameObject* CreateGameObject(rapidjson::Value::ConstMemberIterator _members);

    // Reads the file and returns the parsed rapidjson Document
    rapidjson::Document ReadFile(const char* _filename);
};