#include "MeshComponent.h"

#include "../VertexArray.h"
#include "../VertexBuffer.h"
#include "../VertexBufferLayout.h"
#include "../Renderer.h"
#include "../Shader.h"

MeshComponent::MeshComponent()
	: m_vb(nullptr), m_vblayout(nullptr), m_ib(nullptr), m_va(nullptr)
{
	
}

MeshComponent::MeshComponent(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
	: m_vertices(vertices), m_indices(indices), m_vb(nullptr), m_vblayout(nullptr), m_ib(nullptr), m_va(nullptr)
{
	SetupMesh();
}

void MeshComponent::BeginPlay()
{}

void MeshComponent::Update()
{}

std::string MeshComponent::GetComponentName() { return "MeshComponent"; }

void MeshComponent::SetMeshData(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{
    m_vertices = vertices;
    m_indices = indices;

    SetupMesh();
}

/// Setting up Vertex Array, VB + VB_Layout, IB
/// ///////////////////////////////////////////////////////
void MeshComponent::SetupMesh()
{
    // Init Vertex Buffer and VB Layout
    m_vb = new VertexBuffer(&this->m_vertices[0], this->m_vertices.size() * sizeof(Vertex));
    m_vblayout = new VertexBufferLayout;
    m_vblayout->Push<float>(3);
    m_vblayout->Push<float>(3);
    m_vblayout->Push<float>(3);

    // Init Vertex Array -> Bind VB and VB Layout
    m_va = new VertexArray;
    m_va->AddBuffer(*m_vb, *m_vblayout);

    // Init Index Buffer
    m_ib = new IndexBuffer(&this->m_indices[0], m_indices.size());
}

void MeshComponent::DrawMesh(Shader& shader, Renderer& renderer)
{
    renderer.Draw(*m_va, *m_ib, shader);
}

void MeshComponent::Serialize()
{

}

void MeshComponent::Deserialize(rapidjson::Value& componentMembers)
{
    std::cout << "Deserializing Mesh Data!" << std::endl;

    rapidjson::Value& meshData = componentMembers.FindMember("Mesh")->value;

    // use rapidjson to get the names of the vertices
    std::vector<std::string> vertexNames = { "vertex0", "vertex1", "vertex2", "vertex3" };
    rapidjson::Value& vertex0Data = meshData.FindMember(vertexNames[0].c_str())->value;
    rapidjson::Value& vertex1Data = meshData.FindMember(vertexNames[1].c_str())->value;
    rapidjson::Value& vertex2Data = meshData.FindMember(vertexNames[2].c_str())->value;
    rapidjson::Value& vertex3Data = meshData.FindMember(vertexNames[3].c_str())->value;
    rapidjson::Value& indiceData  = meshData.FindMember("indices")->value;
    
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    for (unsigned int i = 0; i < indiceData.Size(); ++i)
        indices.push_back(indiceData[i].GetInt());

    if (vertex0Data.IsArray())
    {
        Vertex vert;
        glm::vec3 data;

        // loop for how many elements there are in a vertex
        // position, color, texCoord so, (j < 3)
        for (int j = 0, i = 0; j < 3; ++j)
        {
            // data[x] x = 0, 1, 2
            data[i % 3] = vertex0Data[i].GetFloat(); ++i;
            data[i % 3] = vertex0Data[i].GetFloat(); ++i;
            data[i % 3] = vertex0Data[i].GetFloat(); ++i;

            switch (j) { // j decides which data to set
            case 0: vert.SetPosition(data); break;
            case 1: vert.SetVertexColor(data); break;
            case 2: vert.SetTextureCoordinates(data); break;
            }
        }

        //glm::vec3 texCoord = vert.GetTextureCoordinates();
        //std::cout << "TexCoord: " << glm::to_string(texCoord) << std::endl;

        vertices.push_back(vert);
    }

    if (vertex1Data.IsArray())
    {
        Vertex vert;
        glm::vec3 data;

        for (int j = 0, i = 0; j < 3; ++j)
        {
            data[i % 3] = vertex1Data[i].GetFloat(); ++i;
            data[i % 3] = vertex1Data[i].GetFloat(); ++i;
            data[i % 3] = vertex1Data[i].GetFloat(); ++i;

            switch (j)
            {
            case 0: vert.SetPosition(data); break;
            case 1: vert.SetVertexColor(data); break;
            case 2: vert.SetTextureCoordinates(data); break;
            }
        }

        //glm::vec3 texCoord = vert.GetTextureCoordinates();
        //std::cout << "TexCoord: " << glm::to_string(texCoord) << std::endl;

        vertices.push_back(vert);
    }

    if (vertex2Data.IsArray())
    {
        Vertex vert;
        glm::vec3 data;

        for (int j = 0, i = 0; j < 3; ++j)
        {
            data[i % 3] = vertex2Data[i].GetFloat(); ++i;
            data[i % 3] = vertex2Data[i].GetFloat(); ++i;
            data[i % 3] = vertex2Data[i].GetFloat(); ++i;

            switch (j)
            {
            case 0: vert.SetPosition(data); break;
            case 1: vert.SetVertexColor(data); break;
            case 2: vert.SetTextureCoordinates(data); break;
            }
        }
        //glm::vec3 texCoord = vert.GetTextureCoordinates();
        //std::cout << "TexCoord: " << glm::to_string(texCoord) << std::endl;

        vertices.push_back(vert);
    }

    if (vertex3Data.IsArray())
    {
        Vertex vert;
        glm::vec3 data;

        for (int j = 0, i = 0; j < 3; ++j)
        {
            data[i % 3] = vertex3Data[i].GetFloat(); ++i;
            data[i % 3] = vertex3Data[i].GetFloat(); ++i;
            data[i % 3] = vertex3Data[i].GetFloat(); ++i;

            switch (j)
            {
            case 0: vert.SetPosition(data); break;
            case 1: vert.SetVertexColor(data); break;
            case 2: vert.SetTextureCoordinates(data); break;
            }
        }
        //glm::vec3 texCoord = vert.GetTextureCoordinates();
        //std::cout << "TexCoord: " << glm::to_string(texCoord) << std::endl;

        vertices.push_back(vert);
    }

    SetMeshData(vertices, indices);
}

MeshComponent::~MeshComponent()
{
    delete m_vb;
    delete m_vblayout;
    delete m_ib;
    delete m_va;
}
