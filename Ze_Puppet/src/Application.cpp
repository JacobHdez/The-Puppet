#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Renderer.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Util/Camera.h"

/* ---------- Settings ---------- */
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
/* ---------- End ---------- */

/* ---------- Camera ---------- */
Camera camera;
glm::mat4 MVP = camera.GetViewProjection();
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
/* ---------- End ---------- */

GLFWwindow* Init_GLFW();

void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

int main(void)
{
    GLFWwindow* window = Init_GLFW();
    if (window == nullptr)
        return -1;

    {
        /* ---------- TEST ---------- */
        float positions[] = {
            -1.0f, -1.0f, -1.0f, // 0
             1.0f, -1.0f, -1.0f, // 1
             1.0f,  1.0f, -1.0f, // 2
             1.0f,  1.0f,  1.0f, // 3
            -1.0f,  1.0f,  1.0f, // 4
            -1.0f, -1.0f,  1.0f, // 5
            -1.0f,  1.0f, -1.0f, // 6
             1.0f, -1.0f,  1.0f, // 7
        };

        unsigned int indices[] = {
            0, 1, 2,
            2, 0, 6,
            6, 2, 4,
            2, 4, 3,
            4, 6, 0,
            0, 4, 5,
            1, 2, 7,
            2, 7, 3,
            0, 1, 7, 
            7, 0, 5,
            3, 4, 7,
            4, 7, 5
        };

        VertexArray va;
        VertexBuffer vb(positions, 8 * 3 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(3);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 12 * 3);

        Shader shader("res/shaders/Basic.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
        shader.SetUniformMat4f("u_MVP", MVP);

        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        shader.Unbind();

        Renderer renderer;

        float r = 0.0f;
        float increment = 0.05f;

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
        {
            processInput(window);

            renderer.Clear();

            shader.Bind();
            shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

            MVP = camera.GetViewProjection();
            /*MVP = glm::rotate(MVP, glm::radians(0.5f), glm::vec3(-1.0f, 0.0f, 0.0f));
            MVP = glm::rotate(MVP, glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            MVP = glm::rotate(MVP, glm::radians(0.5f), glm::vec3(0.0f, 0.0f, -1.0f));*/
            shader.SetUniformMat4f("u_MVP", MVP);

            renderer.Draw(va, ib, shader);

            if (r > 1.0f)
                increment = -0.05f;
            else if (r < 0.0f)
                increment = 0.05f;

            r += increment;


            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}

GLFWwindow* Init_GLFW()
{
    GLFWwindow* window;

    if (!glfwInit())
        return nullptr;

    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    glfwSwapInterval(5);

    if (glewInit() != GLEW_OK)
        std::cout << "[-] Error glewInit()" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;

    return window;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(GLFW_KEY_W);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(GLFW_KEY_S);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(GLFW_KEY_A);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(GLFW_KEY_D);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    GLCall(glViewport(0, 0, width, height));
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll((float)xoffset, (float)yoffset);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    std::cout << button << " - " << action << " - " << mods << std::endl;
}