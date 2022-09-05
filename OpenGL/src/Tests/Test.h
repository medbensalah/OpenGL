#pragma once
#include <functional>
#include <string>
#include <vector>

#include "Logger.h"

namespace GLTest
{
    class Test
    {
    public:
        Test()
        {
        }

        virtual ~Test()
        {
        }

        virtual void OnUpdate(float deltaTime)
        {
        }

        virtual void OnRender()
        {
        }

        virtual void OnImGuiRender()
        {
        }
    };

    class TestMenu : public Test
    {
    public:
        TestMenu(Test*& CurrentTestPointer);

        void OnImGuiRender() override;

        template <typename T>
        void RegisterTest(const std::string& name)
        {
            m_Tests.push_back(std::make_pair(name, []() { return new T(); }));
        }

    private:
        Test*& m_CurrentTest;
        std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;
    };
}
