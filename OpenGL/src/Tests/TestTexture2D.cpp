﻿#include "TestTexture2D.h"

#include "Renderer.h"
#include "imgui/imgui.h"

namespace GLTest
{
    TestTexture2D::TestTexture2D()
    {
    }

    TestTexture2D::~TestTexture2D()
    {
    }

    void TestTexture2D::OnUpdate(float DeltaTime)
    {
    }

    void TestTexture2D::OnRender()
    {
        GLCall(glClearColor(0.0f,0.0f,0.0f,0.0f););
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
    }

    void TestTexture2D::OnImGuiRender()
    {
    }
}
