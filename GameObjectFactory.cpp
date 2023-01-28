#include "GameObjectFactory.h"

GameObjectFactory* GameObjectFactory::m_Instance = nullptr;

GameObjectFactory::GameObjectFactory() {}

GameObjectFactory& GameObjectFactory::GetInstance()
{
    static GameObjectFactory instance_;
    return instance_;
}

//////////////////////////////////////////////////////////////
// Below Multiple GameObjects (from file or iterator) ////////
//////////////////////////////////////////////////////////////

std::vector<GameObject*> GameObjectFactory::CreateAllGameObjects(const char* _filename)
{
    std::vector<GameObject*> gameObjectList;

    FILE* fp;
    fopen_s(&fp, _filename, "rb");
    if (!fp)
    {
        std::cout << "Cannot open file \"" << _filename << "\"!" << std::endl;
        std::cout << "Check the filename and try again!" << std::endl;
        std::cout << "Press any key to exit program!" << std::endl;
        getchar();
        exit(-1);
    }

    char cbuffer[256];
    rapidjson::FileReadStream Jfs(fp, cbuffer, sizeof(cbuffer));

    rapidjson::Document Jdoc;
    Jdoc.ParseStream(Jfs);

    rapidjson::Value::ConstMemberIterator gameObjectsItr = Jdoc.MemberBegin();
    std::cout << "Creating GameObjects from JSON!" << std::endl;
    for (; gameObjectsItr != Jdoc.MemberEnd(); ++gameObjectsItr)
    {
        std::cout << "Creating: " << gameObjectsItr->name.GetString() << std::endl;
        gameObjectList.push_back(CreateGameObject(gameObjectsItr));
    }

    fclose(fp);

    return gameObjectList;
}

std::vector<GameObject*> GameObjectFactory::CreateGameObjectCopies(const char* _filename, const unsigned int& num_copies)
{
    rapidjson::Document Jdoc = ReadFile(_filename);

    // List of game objects to return
    std::vector<GameObject*> gameObjectList;

    rapidjson::Value::ConstMemberIterator gameObjectsItr = Jdoc.MemberBegin();
    std::cout << "Generating " << num_copies << " copies of the GameObject from JSON!" << std::endl;

    for (unsigned int i = 0; i < num_copies; ++i)
        gameObjectList.push_back(CreateGameObject(gameObjectsItr));

    return gameObjectList;   // return the copies
}

//////////////////////////////////////////////////////////////
// Below Creates Single GameObjects (from file or iterator) //
//////////////////////////////////////////////////////////////

// Creates GameObjects from file
GameObject* GameObjectFactory::CreateGameObject(const char* _filename)
{
    rapidjson::Document Jdoc = ReadFile(_filename);

    // Game Object to return
    GameObject* gameObject;

    rapidjson::Value::ConstMemberIterator gameObjectsItr = Jdoc.MemberBegin();

    std::cout << "Creating Single GameObject from JSON!" << std::endl;
    gameObject = CreateGameObject(gameObjectsItr);

    return gameObject;
}

// Create GameObjects from rapidjson value::iterator
GameObject* GameObjectFactory::CreateGameObject(rapidjson::Value::ConstMemberIterator _member)
{
    GameObject* gameObject;

    std::string objectName = _member->name.GetString();
    std::cout << "Creating GameObject called " << objectName << "!" << std::endl;
    if (objectName == "Player")
        gameObject = new Player(objectName);
    else if (objectName == "Enemy")
        gameObject = new Enemy(objectName);
    else
        gameObject = new GameObject(objectName);

    rapidjson::Value::ConstMemberIterator componentMembers = _member->value.FindMember("Components")->value.MemberBegin();
    for (; componentMembers != _member->value.MemberEnd(); ++componentMembers)
    {
        std::string ComponentName = componentMembers->name.GetString();
        if (ComponentName == "Transform")
        {
            gameObject->AddComponent<TransformComponent>();
            TransformComponent* transform_ = (TransformComponent*)gameObject->FindComponent<TransformComponent>();
            if (transform_)
            {
                auto temp = _member->value.GetObject();
                rapidjson::Value& tempMember = (rapidjson::Value&)temp.begin()->value;
                transform_->Deserialize(tempMember);
            }
        }

        if (ComponentName == "Mesh")
        {
            gameObject->AddComponent<MeshComponent>();
            MeshComponent* mesh_ = (MeshComponent*)gameObject->FindComponent<MeshComponent>();
            if (mesh_)
            {
                auto temp = _member->value.GetObject();
                rapidjson::Value& tempMember = (rapidjson::Value&)temp.begin()->value;
                mesh_->Deserialize(tempMember);
            }
        }

        if (ComponentName == "Input")
            gameObject->AddComponent<InputComponent>();

        if (ComponentName == "Physics")
            gameObject->AddComponent<PhysicsComponent>();
    }

    return gameObject;
}

//////////////////////////////////////////////////////////////
// Helper Functions Below (if any) ///////////////////////////
//////////////////////////////////////////////////////////////

rapidjson::Document GameObjectFactory::ReadFile(const char* _filename)
{
    FILE* fp;
    fopen_s(&fp, _filename, "rb");
    if (!fp)
    {
        std::cout << "Cannot open file \"" << _filename << "\"!" << std::endl;
        std::cout << "Check the filename and try again!" << std::endl;
        std::cout << "Press any key to exit program!" << std::endl;
        getchar();
        exit(-1);
    }

    char cbuffer[256];
    rapidjson::FileReadStream Jfs(fp, cbuffer, sizeof(cbuffer));

    rapidjson::Document Jdoc;
    Jdoc.ParseStream(Jfs);

    fclose(fp);

    return Jdoc;
}