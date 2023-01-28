#pragma once

#include <map>
#include <string>

class Shader;
class Texture;

class ResourceManager
{
public:
	// resource storage
	static std::map<std::string, Shader*> Shaders;
	static std::map<std::string, Texture*> Textures;
	static std::map<std::string, const char*> Scenes;

	static Shader* LoadShader(const char* _filename, std::string name);
	static Shader* GetShader(std::string name);

	static Texture* LoadTexture(const char* file, std::string name);
	static Texture* GetTexture(std::string name);

	static void LoadSceneByName(const char* _filename, std::string _sceneName);
	static const char* GetSceneByName(std::string _sceneName);

	// properly de-allocates all loaded resources
	static void ClearAllResources();
private:
	ResourceManager() {}

	static Shader* loadShaderFromFile(const char* _filename);
	static Texture* loadTextureFromFile(const char* _filename);
};

