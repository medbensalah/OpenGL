#pragma once

#include "Test.h"

namespace GLTest
{
    class TestTexture2D : public Test
    {
    public:
        TestTexture2D();
        ~TestTexture2D();

        void OnUpdate(float DeltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;
    };
}
