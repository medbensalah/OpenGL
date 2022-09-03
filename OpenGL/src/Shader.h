#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader
{
public:
    Shader(const std::string& filepath);
    ~Shader();

    
    ShaderProgramSource ParseShader(const std::string& filePath);
    void Bind() const;
    void Unbind() const;

    void SetUniform1i(const std::string& name, int value);
    void SetUniform1f(const std::string& name, float value);
    void SetUniform4f(const std::string& name, float r, float g, float b, float a);
    void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

private:
    unsigned int m_RendererID;

    std::string m_filepath;

    std::unordered_map<std::string, int> m_UniformLocationCache;

    unsigned CompileShader(unsigned type, const std::string& source);
    unsigned CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
    
    int GetUniformLocation(const std::string& name);
};
