#include "Renderer.h"
#include <iostream>
#include <string>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#include "Logger.h"

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::string message = "[OpenGL Error] : (" + std::to_string(error) + ") : When calling : " + function + " in \"" + file +
            "\" on line : " + std::to_string(line);
        MedLogger::Log(message, LOG_LEVEL_ERROR);
        return false;
    }
    return true;
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();

    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr))
}

void Renderer::Clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT))
}