#pragma once

#include <vector>

#include "Vertex.h"

class VertexArray;
class VertexBuffer;
class VertexBufferLayout;
class IndexBuffer;
class Renderer;
class Shader;

class Mesh
{
private:
	// render data
	VertexBuffer* m_vb;
	VertexBufferLayout* m_vblayout;
	IndexBuffer* m_ib;
public:
	//render data
	VertexArray* m_va;
	
	// mesh data
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
private:
	void SetupMesh();
public:
	// Constructors
	Mesh() : m_vb(nullptr), m_vblayout(nullptr), m_ib(nullptr), m_va(nullptr) {}
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	
	// Destructor
	~Mesh();

	void SetMeshData(std::vector<Vertex> vertices, std::vector<unsigned int> indices);

	void DrawMesh(Shader& shader, Renderer& renderer);
};