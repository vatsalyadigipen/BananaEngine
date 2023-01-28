#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

class Vertex
{
private:
	glm::vec3 m_position;
	glm::vec3 m_vertexColor;
	glm::vec3 m_texCoord;	// texture coordinates

public:
	Vertex()
		: m_position(glm::vec3(0.0f)), m_vertexColor(glm::vec3(1.0f, 0.0f, 0.0f)), m_texCoord(glm::vec3(0.0f)) {}

	Vertex(const glm::vec3& newPosition, const glm::vec3& newColor, const glm::vec3& newTexCoord)
		: m_position(newPosition), m_vertexColor(newColor), m_texCoord(newTexCoord) {}

	const glm::vec3& GetPosition() { return m_position; }
	inline void SetPosition(const glm::vec3& position) { m_position = position; }

	const glm::vec3& GetVertexColor() { return m_vertexColor; }
	inline void SetVertexColor(const glm::vec3& newColor) { m_vertexColor = newColor; }

	const glm::vec3& GetTextureCoordinates() { return m_texCoord; }
	inline void SetTextureCoordinates(const glm::vec3& newTexCoord) { m_texCoord = newTexCoord; }
};