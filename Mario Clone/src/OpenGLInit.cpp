#include "GL\glew.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <tuple>
#include <windows.h>
#include <thread>
#include <chrono>
#include <conio.h>

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

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

Map* map;

int main()
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

    float marioPosition[] = {
        //Position              //Textue coordinates (mario left and right flip)
        0.0f, 0.0f,             0.0f, 0.0f,    1.0f, 0.0f,
        0.0f, QUAD_SIZE,        0.0f, 1.0f,    1.0f, 1.0f,
        QUAD_SIZE, 0.0f,        1.0f, 0.0f,    0.0f, 0.0f,
        QUAD_SIZE, QUAD_SIZE,   1.0f, 1.0f,    0.0f, 1.0f
    };

    float blockPosition[] = {
        //Position              //Textue coordinates (static)
        0.0f, 0.0f,             0.0f, 0.0f,
        0.0f, QUAD_SIZE,        0.0f, 1.0f,
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
    VertexBuffer vb(24 * sizeof(float), marioPosition);
    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    layout.Push<float>(2);
    IndexBuffer ib(6, indexes);
    ib.Bind();
    va.AddBuffer(vb, layout);

    Shader shader("res/Shaders/Basic.shader");
    shader.Bind();
    map = new Map("../Map Builder/res/map.txt", shader, va, ib);
    Renderer renderer;
    Textures tex(shader);

    renderer.Clear();
    va.Unbind();
    ib.Unbind();

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
    glfwSetKeyCallback(window, key_callback);

    glClearColor(0.6f, 0.83f, 0.98f, 1.0f);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        map->OnRender();
        Sleep(30);

        //naprawic zmiane textur przy tworzeniu mapy

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_A && action == GLFW_PRESS) {
        //LEFT
        map->moveLeft = true;
    }
    if (key == GLFW_KEY_D && action == GLFW_PRESS) {
        //RIGHT
        map->moveRight = true;
    }
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        //JUMP
        if (map->canJump) {
            map->CheckStandingLocation();
            map->whileJumping = true;
            map->isFalling = false;
        }
    }
    if (key == GLFW_KEY_A && action == GLFW_RELEASE) {
        //LEFT
        map->moveLeft = false;
    }
    if (key == GLFW_KEY_D && action == GLFW_RELEASE) {
        //RIGHT
        map->moveRight = false;
    }
}

