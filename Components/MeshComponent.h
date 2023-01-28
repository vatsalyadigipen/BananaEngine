#pragma once

#include <vector>

#include "Component.h"
#include "../Vertex.h"

class VertexArray;
class VertexBuffer;
class VertexBufferLayout;
class IndexBuffer;
class Renderer;
class Shader;

class MeshComponent : public Component
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

public:
	MeshComponent();
	MeshComponent(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	virtual ~MeshComponent();

	// override functions
	void BeginPlay() override;
	void Update() override;
	std::string GetComponentName() override;

	// Mesh Data and Draw Call
	void SetMeshData(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	void DrawMesh(Shader& shader, Renderer& renderer);

	// Serialize & Deserialize
	void Serialize();
	void Deserialize(rapidjson::Value& componentMember);

private:	// helper functions
	void SetupMesh();
};