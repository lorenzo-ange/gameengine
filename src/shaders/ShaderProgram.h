/*
 * ShaderProgram.h
 *
 *  Created on: 29 mar 2016
 *      Author: lorenzo
 */

#ifndef SHADERS_SHADERPROGRAM_H_
#define SHADERS_SHADERPROGRAM_H_

#include <GL/glew.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class ShaderProgram {
public:
    virtual ~ShaderProgram();

    void init(const char * vertexFile, const char * fragmentFile);
    void start();
    void stop();
    void cleanUp();

protected:
    virtual void bindAttributes() = 0;
    void bindAttribute(GLuint attribute, const char * variableName);

    virtual void getAllUniformLocations() = 0;
    int getUniformLocation(const char * uniformName);

    void loadInt(int location, int value);
    void loadFloat(int location, float value);
    void loadVector(int location, glm::vec3 vector);
    void load2DVector(int location, glm::vec2 vector);
    void loadBoolean(int location, bool value);
    void loadMatrix(int location, glm::mat4 matrix);

private:
    GLuint programID;
    GLuint vertexShaderID;
    GLuint fragmentShaderID;

    static GLuint loadShader(const char * file, GLenum type);
};

#endif /* SHADERS_SHADERPROGRAM_H_ */
