#include "Renderer.h"
#include "Logger/Logger.h"

Renderer* Renderer::m_Instance = nullptr;

Renderer::Renderer() {}

Renderer& Renderer::GetInstance()
{
    static Renderer renderer_;
    return renderer_;
}

void Renderer::Clear() const
{
    GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)
{
    // All the binding need to be done before the traingle is rendered //
    shader.Bind();
    va.Bind();  // binding vertex array
    ib.Bind();  // binding index buffer

    // Using Indices to and Index Buffer Obj to draw 2 triangles which looks like a square
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}