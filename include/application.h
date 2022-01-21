#ifndef _TEST_IMGUI_INC_APPLICATION_
#define _TEST_IMGUI_INC_APPLICATION_

#include <glad/glad.h>
#include "iwindow.h"
#include <GLFW/glfw3.h>
#include <vector>


class Application
{
public:
    void Run();
    void Cleanup();
    void AddWindow(IWindow*);
    static Application* GetInstance();

private:
    void Init();
    void Update(double dt);
    void Render();
    Application(/* args */);

private:
    static Application* s_instance;
    GLFWwindow* m_window;
    static constexpr double m_fpsLimit = 1.0 / 35.0;
    double m_lastTimeFrame  = 0.0;

    std::vector<IWindow*> m_listWindow;
};
#endif