#include <iostream>

#include "Scene.h"
#include "Shader.h"
#include "BananaWindow.h"
#include "Textures/Texture.h"
#include "ResourceManager/ResourceManager.h"
#include "Logger/Logger.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/string_cast.hpp"

#include "GameObjectFactory.h"

Scene::Scene()
    : m_Player(nullptr), m_SceneName("Scene"), m_GameObjectFactory(&GameObjectFactory::GetInstance())
{}

void Scene::LoadAllResources()
{
    // Load all the resources
    ResourceManager::LoadShader("res/shaders/Basic.shader", "Basic");
    ResourceManager::LoadTexture("src/resources/Texture_Files/spaceship.png", "Spaceship");
    ResourceManager::LoadTexture("src/resources/Texture_Files/bullet.png", "Projectile");
    ResourceManager::LoadTexture("src/resources/Texture_Files/grass.jpg", "Enemy");
    ResourceManager::LoadTexture("src/resources/Texture_Files/apple.png", "Pickup");
}

void Scene::InitializeAllGameObjects(const char* _fileName)
{
    CreateGameObjects(_fileName);
    AssignTexturesToGameObjects();
}

void Scene::BeginPlay()
{

}

void Scene::Update()
{
    
}

/*
Draw Scene Function
This is inside the game loop.
Update Scene after render, clear loop
*/
void Scene::DrawScene()
{
    /* Render here */
    Renderer renderer_ = Renderer::GetInstance();
    renderer_.Clear();

    if (m_AllGameObjects.size() > 0)
        for (auto go : m_AllGameObjects)
            go->Draw(*ResourceManager::GetShader("Basic"), renderer_);
}

void Scene::UpdateScene()
{
    // Collision Detection
    for (auto gameobject : m_AllGameObjects) {
        if (CheckForCollision(m_Player, gameobject)) {
            gameobject->SetActive(false);
        }
    }

    // Update Game Objects
    if (m_AllGameObjects.size() > 0) {
        for (auto gameObject_ : m_AllGameObjects) {
            if (gameObject_ && gameObject_->IsActive())
                gameObject_->Update();
            else
            {
                m_GameObjectsToDelete.push_back(gameObject_);
                
                /*auto go_ = std::find(m_AllGameObjects.begin(), m_AllGameObjects.end(), gameObject_);
                if (*go_)
                    m_AllGameObjects.erase(std::find(m_AllGameObjects.begin(), m_AllGameObjects.end(), gameObject_));*/
            }
        }

        DeletePendingGameObjects();
    }

    Update();
}

void Scene::ReleaseAllResources()
{
    if (m_AllGameObjects.size() > 0)
    {
        for (auto gameObjects_ : m_AllGameObjects)
        {
            gameObjects_->SetActive(false);
            delete gameObjects_;
            gameObjects_ = nullptr;
        }
    }

    if (m_GameObjectsToDelete.size() > 0)
    {
        for (auto gameObjects_ : m_GameObjectsToDelete)
        {
            gameObjects_->SetActive(false);
            delete gameObjects_;
            gameObjects_ = nullptr;
        }
    }

    ResourceManager::ClearAllResources();
}

///////////////////////// Helper Functions ////////////////////////////

void Scene::CreateGameObjects(const char* _fileName)
{
    // Create Other Game Objects like Enemy
    //m_AllGameObjects = m_GameObjectFactory->CreateGameObjectCopies(_gameObjectFile, _numOfObjects);
    m_AllGameObjects = m_GameObjectFactory->CreateAllGameObjects(_fileName);

    for (auto go : m_AllGameObjects)
        if (go->GetObjectName() == "Player")
            m_Player = go;

    // TODO: Fix enemy logic and don't keep it here
    // 1. Maybe make some simple AI logic (easy)
    for (auto go : m_AllGameObjects)
    {
        if (go->GetObjectName() != "Player")
        {
            float i = (float)(rand() % 5);
            float j = (float)(rand() % 5);
            TransformComponent* TC = (TransformComponent*)go->FindComponent<TransformComponent>();
            TC->SetLocalPosition(glm::vec3(i, j, 0.0));
        }
    }

    std::cout << "Total GameObjects created in Scene(Not including Player): " << m_AllGameObjects.size() << std::endl;
}

void Scene::AssignTexturesToGameObjects()
{
    // TODO: Find a suitable spot for these two
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    if (m_AllGameObjects.size() > 0)
    {
        for (auto go : m_AllGameObjects)
        {
            std::string gameObjectName = go->GetObjectName();
            if (gameObjectName == "Player")
                go->AssignTexture(ResourceManager::GetTexture("Spaceship"), 0);
            else if (gameObjectName == "Enemy")
                go->AssignTexture(ResourceManager::GetTexture("Enemy"), 1);
            else if (gameObjectName == "Background")
                go->AssignTexture(ResourceManager::GetTexture("Background"), 2);
            else
                go->AssignTexture(ResourceManager::GetTexture("Projectile"), 3);
        }
    }
}

void Scene::DeletePendingGameObjects()
{
    if (m_GameObjectsToDelete.size() > 0)
    {
        for (auto go_ : m_GameObjectsToDelete)
        {
            m_AllGameObjects.erase(std::find(m_AllGameObjects.begin(), m_AllGameObjects.end(), go_));
            go_->SetActive(false);
            delete go_;
            go_ = nullptr;
        }
        m_GameObjectsToDelete.clear();
    }
}

bool Scene::CheckForCollision(GameObject* _one, GameObject* _two) // AABB - AABB collision
{
    TransformComponent* TC_one = (TransformComponent*)_one->FindComponent<TransformComponent>();
    TransformComponent* TC_two = (TransformComponent*)_two->FindComponent<TransformComponent>();
    if (TC_one && TC_two)
    {
        // Check collision with self
        if (_two->GetObjectName() == "Player")
            return false;

        _one->CalculateSize();
        _two->CalculateSize();

        // collision x-axis
        bool collisionX = TC_one->m_position.x + _one->m_size.x >= TC_two->m_position.x &&
            TC_two->m_position.x + _two->m_size.x >= TC_one->m_position.x;

        // collision y-axis
        bool collisionY = TC_one->m_position.y + _one->m_size.y >= TC_two->m_position.y &&
            TC_two->m_position.y + _two->m_size.y >= TC_one->m_position.y;

        // collision only if on both axes
        return collisionX && collisionY;
    }

    std::cout << "[Collison Check] Transform Component not present!" << std::endl;
    return false;
}

//////////////////////////// Destructor ///////////////////////////////

Scene::~Scene()
{
    if (m_AllGameObjects.size() > 0)
        for (auto gameObjects_ : m_AllGameObjects)
            if (gameObjects_ != nullptr && !gameObjects_->IsActive())
                delete gameObjects_;

    if (m_GameObjectsToDelete.size() > 0)
        for (auto gameObjects_ : m_GameObjectsToDelete)
            if (gameObjects_ != nullptr && !gameObjects_->IsActive())
                delete gameObjects_;
}