#include <glad/glad.h>
#include <iostream>
#include "Utility/Utility.h"

namespace project_utility {

    void shaderInfo(unsigned int shader) {
        int success;
        char infoLog[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    }

    void shaderLinkingInfo(unsigned int shaderProgram) {
        int success;
        char infoLog[512];

        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(shaderProgram, 512, nullptr, infoLog);
        }
    }
}
