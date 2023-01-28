#include "Texture.h"

#include "stb_image/stb_image.h"
#include "../Logger/Logger.h"
#include <iostream>

Texture::Texture(std::string FilePath)
	: m_rendererID(0), m_FilePath(FilePath), m_Image(nullptr), m_Width(0), m_Height(0), m_Depth(0)
{
	stbi_set_flip_vertically_on_load(1);
	m_Image = stbi_load(m_FilePath.c_str(), &m_Width, &m_Height, &m_Depth, 4);
	if (!m_Image) {
		std::cout << "Read error on file [" << m_FilePath.c_str() << "] : " << stbi_failure_reason() << std::endl;
		exit(-1);
	}

	GLCall(glGenTextures(1, &m_rendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Image));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (m_Image)
		stbi_image_free(m_Image);
}

void Texture::Bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));
}

void Texture::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_rendererID));
}
