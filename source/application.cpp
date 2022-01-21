
#include "application.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <iostream>

Application* Application::s_instance = nullptr;

static void glfw_error_callback(int error, const char* description)
{
    std::cout << "Glfw Error" << error << description << std::endl;
}

Application* Application::GetInstance()
{
    if(s_instance == nullptr) {
        s_instance = new Application();
    }
    return s_instance;
}

Application::Application(/* args */)
{
    Init();
}

void Application::Cleanup()
{
    std::cout << "Cleanup\n";

    for(auto iwind : m_listWindow) {
        if(iwind) {
            std::cout << "delete \n";
            delete iwind;
        }           
    }
    m_listWindow.clear();

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void Application::Init()
{
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        std::exit(EXIT_FAILURE);
    
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only

    // Create window with graphics context
    m_window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", NULL, NULL);
    if (m_window == NULL)
       std::exit(EXIT_FAILURE);

    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1); // Enable vsync

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

void Application::Update(double dt)
{
    for(auto iwind : m_listWindow) {
        if(iwind)
            iwind->Update(dt);
    }
}

void Application::Render()
{
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    for(auto iwind : m_listWindow) {
        if(iwind)
            iwind->Render();
    }

     // Rendering
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(m_window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);

    for(auto iwind : m_listWindow) {
        if(iwind)
            iwind->Render3D();
    }

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(m_window);
}

void Application::Run()
{
    while (!glfwWindowShouldClose(m_window))
    {
        glfwWaitEventsTimeout(m_fpsLimit);

        double now = glfwGetTime();
        double dt  = now - m_lastTimeFrame;
        if(dt < m_fpsLimit) {
            usleep((m_fpsLimit - dt) * 1000.0 * 1000.0);
        }

        Update(dt);
        Render();

        m_lastTimeFrame = glfwGetTime();
    }
}

void Application::AddWindow(IWindow* iwind)
{
    if(iwind) {
        iwind->Init();
        m_listWindow.push_back(iwind);
    }    
}