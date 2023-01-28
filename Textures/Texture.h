#pragma once

#include "../Renderer.h"

class Texture
{
private:
	unsigned int m_rendererID;
	std::string m_FilePath;
	unsigned char* m_Image;
	int m_Width, m_Height, m_Depth;
public:
	Texture(std::string FilePath);
	~Texture();

	const unsigned int& GetTextureID() { return m_rendererID; }

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
};