/*
 * ShaderProgram.cpp
 *
 *  Created on: 29 mar 2016
 *      Author: lorenzo
 */

#include "ShaderProgram.h"

ShaderProgram::~ShaderProgram() {
}

void ShaderProgram::init(const char * vertexFile, const char * fragmentFile) {
    vertexShaderID = loadShader(vertexFile, GL_VERTEX_SHADER);
    fragmentShaderID = loadShader(fragmentFile, GL_FRAGMENT_SHADER);

    programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    bindAttributes();
    glLinkProgram(programID);
    glValidateProgram(programID);
    getAllUniformLocations();
}

void ShaderProgram::start() {
    glUseProgram(programID);
}

void ShaderProgram::stop() {
    glUseProgram(0);
}

void ShaderProgram::cleanUp() {
    stop();
    glDetachShader(programID, vertexShaderID);
    glDetachShader(programID, fragmentShaderID);

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    glDeleteProgram(programID);
}

void ShaderProgram::bindAttribute(GLuint attribute, const char * variableName) {
    glBindAttribLocation(programID, attribute, variableName);
}

GLuint ShaderProgram::loadShader(const char * file, GLenum type) {

    std::string shaderSource;
    std::ifstream shaderStream(file, std::ios::in);
    if(shaderStream.is_open()){
        std::string line = "";
        while(getline(shaderStream, line)) {
            shaderSource += "\n" + line;
        }
        shaderStream.close();
    }
    else {
        fprintf(stderr, "Impossible to open %s\n", file);
        return 0;
    }

    // Compile Shader
    printf("Compiling shader : %s\n", file);
    GLuint shaderID = glCreateShader(type);
    char const * sourcePointer = shaderSource.c_str();
    glShaderSource(shaderID, 1, &sourcePointer , NULL);
    glCompileShader(shaderID);

    // Check Shader
    GLint result = GL_FALSE;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
    int infoLogLength;
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 1) {
        std::vector<char> shaderErrorMessage(infoLogLength+1);
        glGetShaderInfoLog(shaderID, infoLogLength, NULL, &shaderErrorMessage[0]);
        fprintf(stderr, "%s\n", &shaderErrorMessage[0]);
    }

    return shaderID;
}

int ShaderProgram::getUniformLocation(const char * uniformName) {
    return glGetUniformLocation(programID, uniformName);
}

void ShaderProgram::loadFloat(int location, float value) {
    glUniform1f(location, value);
}

void ShaderProgram::loadVector(int location, glm::vec3 vector) {
    glUniform3f(location, vector.x, vector.y, vector.z);
}

void ShaderProgram::loadBoolean(int location, bool value) {
    float toLoad = 0;
    if (value) {
        toLoad = 1;
    }
    glUniform1f(location, toLoad);
}

void ShaderProgram::loadMatrix(int location, glm::mat4 matrix) {
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderProgram::loadInt(int location, int value) {
    glUniform1i(location, value);
}

void ShaderProgram::load2DVector(int location, glm::vec2 vector) {
    glUniform2f(location, vector.x, vector.y);
}
