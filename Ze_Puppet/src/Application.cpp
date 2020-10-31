#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Renderer.h"

#include "tests/TestPuppet.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "Util/Camera.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

/* ---------- Camera ---------- */
Camera camera;
glm::mat4 MVP = camera.GetViewProjection();
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

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
    if (button == GLFW_MOUSE_BUTTON_RIGHT)
        camera.ProcessMouseButton(button, action);
}
/* ---------- End ---------- */

GLFWwindow* Init_GLFW();
void Init_GLEW();
void Init_IMGUI(GLFWwindow* window);

int main()
{
    GLFWwindow* window = Init_GLFW();
    if (window == nullptr)
        return -1;

    Init_GLEW();

    {
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        Init_IMGUI(window);

        test::TestPuppet Puppet("res/objects/test.obj");
        //test::TestPuppet Puppet("res/objects/puppet.obj");
        std::cout << "Puppet size = " << Puppet.m_objects.size() << std::endl;
        /* ---------- Test ---------- */
        /*float positions[] = {
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
        };*/
        std::vector<float> positions = Puppet.m_objects[0].GetVertices();
        std::vector<unsigned int> indices = Puppet.m_objects[0].GetIndices();

        VertexArray va;
        VertexBuffer vb(&positions[0], positions.size() * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(3);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(&indices[0], indices.size());

        /*glm::mat4 m_Perspective = glm::perspective(glm::pi<float>() * 0.25f, 4.0f / 3.0f, 0.1f, 1000.0f);
        glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 5.0f);
        glm::vec3 m_Right = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
        m_Perspective = m_Perspective* glm::lookAt(m_Position, m_Position + m_Right, m_Up);*/

        Shader shader("res/shaders/Basic.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
        //shader.SetUniformMat4f("u_MVP", m_Perspective);

        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        shader.Unbind();

        Renderer renderer;

        float r = 0.0f;
        float increment = 0.05f;

        //GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
        /* ---------- End ---------- */

        while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
        {
            processInput(window);
            renderer.Clear();

            shader.Bind();
            shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

            MVP = camera.GetViewProjection();
            shader.SetUniformMat4f("u_MVP", MVP);

            renderer.Draw(va, ib, shader);

            if (r > 1.0f)
                increment = -0.05f;
            else if (r < 0.0f)
                increment = 0.05f;

            r += increment;
            /*Puppet.OnUpdate(0.0f);
            Puppet.OnRender();*/

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            //Puppet.OnImGuiRender();

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

GLFWwindow* Init_GLFW()
{
    GLFWwindow* window;

    if (!glfwInit())
        return nullptr;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "The Puppet", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    glfwSwapInterval(1);

    return window;
}

void Init_GLEW()
{
    if (glewInit() != GLEW_OK)
        std::cout << "[-] Error glewInit()" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;
}

void Init_IMGUI(GLFWwindow* window)
{
    const char* glsl_version = "#version 130";

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    ImGui::StyleColorsDark();
}