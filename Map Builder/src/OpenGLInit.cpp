#include "GL\glew.h"
#include <GLFW/glfw3.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <tuple>
#include <windows.h>
#include <thread>
#include <chrono>

#include "Renderer.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "Textures.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Map.h"
#include "Menu.h"

Map* map;

void mouse_position_callback(GLFWwindow* window, double xpos, double ypos /*int button, int action, int mods*/);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WIDTH, HEIGHT, "Mario", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Changing OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Changing OpenGL profile

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glewInit();

    if (glewInit() != GLEW_OK)
        std::cout << "Error" << std::endl;

    float position[] = {
        //Position              //Textue coordinates
        0.0f,      0.0f,        0.0f, 0.0f,
        0.0f,      QUAD_SIZE,   0.0f, 1.0f,
        QUAD_SIZE, 0.0f,        1.0f, 0.0f,
        QUAD_SIZE, QUAD_SIZE,   1.0f, 1.0f
    };

    unsigned int indexes[] = {
        0, 1, 2,
        2, 1, 3
    };

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    VertexArray va;
    VertexBuffer vb(16 * sizeof(float), position);
    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);

    IndexBuffer ib(6, indexes);
    ib.Bind();
    va.AddBuffer(vb, layout);

    Shader shader("res/Shaders/Basic.shader");
    shader.Bind();
    Menu menu;
    map = new Map("res/map.txt", shader, va, ib, menu);

    va.Unbind();
    ib.Unbind();
    
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, mouse_position_callback); //maybe set it to some other mouse function (onMove)

    // Initialize ImGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Tell OpenGL a new frame is about to begin
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // ImGUI window creation
        ImGui::Begin("Map builder");
        menu.MenuCheckBox();
        map->WindowClear();
        map->MapSave();
        // Ends the window
        ImGui::End();
        map->DrawMapElements();

        // Renders the ImGUI elements
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    // Deletes all ImGUI instances
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {   
        double xpos, ypos;
        //getting cursor position
        glfwGetCursorPos(window, &xpos, &ypos);
        map->PassMouseCoord(glm::vec2((float)xpos, (float)ypos));
        map->ChangeClickState();
        map->SaveToString();  
    }
}


void mouse_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        map->PassMouseCoord(glm::vec2((float)xpos, (float)ypos));
        map->ChangeClickState();
        map->SaveToString();
    }
}