#include "VertexArray.h"
#include "VertexBufferLayout.h"

#include "Renderer.h"
#include "Logger/Logger.h"

VertexArray::VertexArray()
{
    GLCall(glCreateVertexArrays(1, &m_rendererID));
}

VertexArray::~VertexArray()
{
    GLCall(glDeleteVertexArrays(1, &m_rendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
    Bind();
	vb.Bind();
    const auto& elements = layout.GetElements();

    for (unsigned int i = 0; i < elements.size(); i++)
    {
        const auto& element = elements[i];
        unsigned int offset = 0;
        // Enables the Vertex Array
        GLCall(glEnableVertexAttribArray(i));
        // Defines the attributes of the Array to tell OpenGL what to do with the points
        // Index 0 of vertex array (vao) is going to be bound the GL array buffer
        // This line of code basically links vertex buffer to vertex array
        GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
        offset += element.count * VertexBufferElements::GetSizeofType(element.type);
    }
}

void VertexArray::Bind() const
{
    GLCall(glBindVertexArray(m_rendererID));
}

void VertexArray::UnBind() const
{
    GLCall(glBindVertexArray(0));
}