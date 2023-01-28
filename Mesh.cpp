#include "Mesh.h"

#include "Vertex.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"
#include "Shader.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
    : m_vertices(vertices), m_indices(indices)
{
    /// Setting up Vertex Array, VB + VB_Layout, IB
    /// ///////////////////////////////////////////////////////
	SetupMesh();
}

void Mesh::SetMeshData(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{
    /// Setting Vertices and Indices
    /// ///////////////////////////////////////////////////////
    m_vertices = vertices;
    m_indices = indices;

    /// Setting up Vertex Array, VB + VB_Layout, IB
    /// ///////////////////////////////////////////////////////
    SetupMesh();
}

void Mesh::SetupMesh()
{
    // Init Vertex Buffer and VB Layout
    m_vb = new VertexBuffer(&this->m_vertices[0], this->m_vertices.size() * sizeof(Vertex));
    m_vblayout = new VertexBufferLayout;
    m_vblayout->Push<float>(3);
    m_vblayout->Push<float>(3);
    
    // Init Vertex Array -> Bind VB and VB Layout
    m_va = new VertexArray;
    m_va->AddBuffer(*m_vb, *m_vblayout);
    
    // Init Index Buffer
    m_ib = new IndexBuffer(&this->m_indices[0], m_indices.size());
}

void Mesh::DrawMesh(Shader& shader, Renderer& renderer)
{
    // render the mesh in Scene
    renderer.Draw(*m_va, *m_ib, shader);
}

Mesh::~Mesh()
{
    delete m_vb;
    delete m_vblayout;
    delete m_ib;
    delete m_va;
}