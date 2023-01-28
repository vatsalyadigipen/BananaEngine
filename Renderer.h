#pragma once

#include <GL/glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Renderer
{
public:
    static Renderer& GetInstance();

    void Clear() const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);

private:
    // Singleton Class
    static Renderer* m_Instance;
    Renderer();
};