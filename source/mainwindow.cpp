
#include <glad/glad.h>
#include <iostream>
#include "mainwindow.h"
#include "utils/glutils.h"

GLuint VBO, VAO;
GLuint shaderProgram;

MainWindow::MainWindow()
{
}

MainWindow::~MainWindow()
{
}

void MainWindow::Init()
{
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    std::string vertexShaderSource = GLUtils::loadShaderSource("../shaders/shader.vert");
    const char* sourceCodeVert = vertexShaderSource.c_str();
    glShaderSource(vertexShader, 1, &sourceCodeVert, NULL);
    glCompileShader(vertexShader);

    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    std::string fragmentShaderSource = GLUtils::loadShaderSource("../shaders/shader.frag");
    const char* sourceCodeFrag = fragmentShaderSource.c_str();
    glShaderSource(fragmentShader, 1, &sourceCodeFrag, NULL);
    glCompileShader(fragmentShader);

    // Check for compile time errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // Check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Set up vertex data (and buffer(s)) and attribute pointers
    // We add a new set of vertices to form a second triangle (a total of 6 vertices); the vertex attribute configuration remains the same (still one 3-float position vector per vertex)
    GLfloat vertices[] = {
        // First triangle
        -0.9f, -0.5f, 0.0f,  // Left 
        -0.0f, -0.5f, 0.0f,  // Right
        -0.45f, 0.5f, 0.0f,  // Top 
    };
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

    glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

    m_trangleColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
}

void MainWindow::Update(double dt)
{
}

void MainWindow::Render3D()
{
    glUseProgram(shaderProgram);
    int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
    glUniform4f(vertexColorLocation, m_trangleColor.x, m_trangleColor.y, m_trangleColor.z, m_trangleColor.w);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3); // We set the count to 6 since we're drawing 6 vertices now (2 triangles); not 3!
    glBindVertexArray(0);
}

void MainWindow::Render()
{
    static float f = 0.0f;
    static int counter = 0;
    
    ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
    ImGui::ColorEdit3("clear color", (float*)&m_trangleColor); // Edit 3 floats representing a color
    ImGui::End();    
}