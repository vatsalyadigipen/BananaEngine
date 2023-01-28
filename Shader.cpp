#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "Logger/Logger.h"

#include "Shader.h"

Shader::Shader(const std::string& filepath)
	: m_rendererID(0), m_FilePath(filepath)
{
    ShaderProgramSource source = ParseShader(filepath);
    m_rendererID = CreateShaders(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_rendererID));
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);
    if (stream.fail()) {
        std::cout << "Failed to open shader file << " << filepath << std::endl;
    }
    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            ss[(int)type] << line << "\n";
        }
    }

    return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    // (basically creating a shader object) Giving an id to the Shader we are going to create
    GLCall(unsigned int id = glCreateShader(type));
    const char* src = source.c_str();

    // Putting/Replacing the shader source in shader object
    GLCall(glShaderSource(id, 1, &src, nullptr));

    // Compiling the shader
    GLCall(glCompileShader(id));

    // Error handling while compiling Shaders
    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE)
    {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)alloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << "Message: " << message << std::endl;
        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}

unsigned int Shader::CreateShaders(const std::string& vertexShader, const std::string& fragmentShader)
{
    GLCall(unsigned int program = glCreateProgram());
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));

    // Error handling while linking multiple shaders
    int result;
    GLCall(glGetProgramiv(program, GL_LINK_STATUS, &result));
    if (result == GL_FALSE)
    {
        int length;
        GLCall(glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)alloca(length * sizeof(char));
        GLCall(glGetProgramInfoLog(program, length, &length, message));
        std::cout << "Failed to link program!" << std::endl;
        std::cout << "Message: " << message << std::endl;
        GLCall(glDeleteProgram(program));
        return 0;
    }

    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}

void Shader::Bind() const
{
    GLCall(glUseProgram(m_rendererID));
}

void Shader::UnBind() const
{
    GLCall(glUseProgram(0));
}

void Shader::SetUniform1i(const std::string& name, int value)
{
    GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform1f(const std::string& name, float value) { GLCall(glUniform1f(GetUniformLocation(name), value)); }
void Shader::SetUniform2f(const std::string& name, float v0, float v1) { GLCall(glUniform2f(GetUniformLocation(name), v0, v1)); }
void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2) { GLCall(glUniform3f(GetUniformLocation(name), v0, v1, v2)); }
void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) { GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3)); }

void Shader::SetUniformMat4(const std::string& name, const glm::mat4& matrix)
{
    GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

int Shader::GetUniformLocation(const std::string& name)
{
    // Better Optimization
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];

    GLCall(int location = glGetUniformLocation(m_rendererID, name.c_str()));
    if (location == -1) {
        std::cout << "Warning: uniform '" << name << "' doesn't exists!" << std::endl;
    }

    m_UniformLocationCache[name] = location;
    return location;
}