#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "headers/Utility/Utility.h"


const int WINDOW_WIDTH = 800;
const int WIDOW_HEIGHT = 600;


void frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

unsigned int setup2DTriangle() {
    float vertices[] {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f
    };

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    const char *vertexShaderSource = "#version 330 core\n"
                                        "layout (location = 0) in vec3 aPos; \n"
                                        "\n"
                                        "void main() {\n"
                                        "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); \n"
                                        "}\0";  // this will be moved to a glsl file

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    project_utility::shaderInfo(vertexShader);

    const char *fragmentShaderSource = "#version 330 core\n"
                                          "out vec4 FragColor;\n"
                                          "\n"
                                          "void main() {\n"
                                          "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                          "}\0"; // \0 pff c strings
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    project_utility::shaderInfo(fragmentShader);

    // shader program to link all shaders
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    project_utility::shaderLinkingInfo(shaderProgram);

    // delete shaders after they've been linked to the shader programs
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // right now we've sent the gpu vertex data and instructed it how to process
    // that data with a vertex and fragment shader but it has no idea how it should
    // link the vertex data to the actual vertex shader

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    return shaderProgram;

//    glUseProgram(shaderProgram);
}

int main() {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WIDOW_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        throw "Failed to create GLFW window";
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, WINDOW_WIDTH, WIDOW_HEIGHT);

    glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);

    unsigned int shaderProgram = setup2DTriangle();

    // render loop
    while (!glfwWindowShouldClose(window)) {

        // input
        processInput(window);

        // rendering commands here

        // check and call events and swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    glfwTerminate();

    return 0;
}


