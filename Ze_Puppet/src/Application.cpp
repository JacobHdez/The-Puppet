#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Renderer.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Util/Camera.h"

#include "tests/TestPuppet.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Camera camera;
glm::mat4 MVP = camera.GetViewProjection();
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

GLFWwindow* Init_GLFW();
void Init_GLEW();
void Init_IMGUI(GLFWwindow* window);

void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

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

        test::TestPuppet Puppet("res/objects/Owl.obj");

        /* ---------- Light ---------- */
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
        va.Setup();
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 12 * 3);

        glm::vec3 lightPos(5.0f, 5.0f, 5.0f);

        glm::mat4 model(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f));

        Shader lightingShader("res/shaders/Lighting.shader");
        lightingShader.Bind();
        lightingShader.SetUniform4f("u_lightColor", 1.0f, 1.0f, 1.0f, 1.0f);
        lightingShader.SetUniformMat4f("u_MVP", MVP * model);

        float r = 0.0f;
        float increment = 0.005f;
        /* ---------- End ---------- */

        Shader shader("res/shaders/Basic02.shader");
        shader.Bind();
        shader.SetUniform3f("u_objectColor", 1.0f, 0.5f, 0.31f); // Coral
        shader.SetUniform3f("u_lightColor", 1.0f, 1.0f, 1.0f);
        shader.SetUniform3f("u_lightPos", lightPos.x, lightPos.y, lightPos.z);
        shader.SetUniformMat4f("u_VP", MVP);
        shader.SetUniformMat4f("u_model", glm::mat4(1.0f));

        Renderer renderer;

        GLCall(glEnable(GL_DEPTH_TEST));
        GLCall(glDepthFunc(GL_LESS));

        double lastTime = glfwGetTime();
        int nbFrames = 0;
        while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
        {
            double currentTime = glfwGetTime();
            nbFrames++;
            if (currentTime - lastTime >= 1.0) {
                std::cout << (1000.0 / double(nbFrames)) << " ms/frame" << std::endl;
                nbFrames = 0;
                lastTime += 1.0;
            }

            processInput(window);
            renderer.Clear();
            MVP = camera.GetViewProjection();

            Puppet.OnUpdate(0.0f);

            shader.Bind();
            shader.SetUniform3f("u_lightColor", r, 1.0f, 1.0f);
            shader.SetUniformMat4f("u_VP", MVP);
            Puppet.OnRender(shader);

            lightingShader.Bind();
            lightingShader.SetUniform4f("u_lightColor", r, 1.0f, 1.0f, 1.0f);
            lightingShader.SetUniformMat4f("u_MVP", MVP*model);
            renderer.Draw(va, ib, lightingShader);

            if (r > 1.0f)
                increment *= -1;
            else if (r < 0.0f)
                increment *= -1;

            r += increment;

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
    camera.SetAspect((float)width/height);
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