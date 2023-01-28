#include "ResourceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include "../Shader.h"
#include "../Textures/Texture.h"
#include "../Renderer.h"
#include "../Logger/Logger.h"

#include "../Textures/stb_image/stb_image.h"

// Instantiate static variables
std::map<std::string, Shader*> ResourceManager::Shaders;
std::map<std::string, Texture*> ResourceManager::Textures;
std::map<std::string, const char*> ResourceManager::Scenes;

Shader* ResourceManager::LoadShader(const char* _filename, std::string name)
{
    Shaders[name] = loadShaderFromFile(_filename);
    return Shaders[name];
}

Shader* ResourceManager::GetShader(std::string name)
{
    return Shaders[name];
}

Texture* ResourceManager::LoadTexture(const char* file, std::string name)
{
    Textures[name] = loadTextureFromFile(file);
    return Textures[name];
}

Texture* ResourceManager::GetTexture(std::string name)
{
    Texture* temp = Textures[name];
    return temp;
}

void ResourceManager::LoadSceneByName(const char* _filename, std::string _sceneName)
{
    Scenes[_sceneName] = _filename;
}

const char* ResourceManager::GetSceneByName(std::string _sceneName)
{
    return Scenes[_sceneName];
}

void ResourceManager::ClearAllResources()
{
    // (properly) delete all shaders	
    for (auto iter : Shaders)
        glDeleteProgram(iter.second->GetShaderID());
    // (properly) delete all textures
    for (auto iter : Textures)
        glDeleteTextures(1, &iter.second->GetTextureID());
}

Shader* ResourceManager::loadShaderFromFile(const char* _filename)
{
    Shader* shader = new Shader(_filename);
    return shader;
}

Texture* ResourceManager::loadTextureFromFile(const char* _filename)
{
    // create texture object
    // TODO: Find a suitable spot for these two
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    Texture* texture = new Texture(_filename);
    return texture;
}

