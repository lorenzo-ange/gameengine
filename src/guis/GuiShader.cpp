/*
 * GuiShader.cpp
 *
 *  Created on: 06 apr 2016
 *      Author: lorenzo
 */

#include "GuiShader.h"

const char * GuiShader::VERTEX_FILE = "src/guis/guiVertexShader.txt";
const char * GuiShader::FRAGMENT_FILE = "src/guis/guiFragmentShader.txt";

GuiShader::GuiShader() {
    init(VERTEX_FILE, FRAGMENT_FILE);
}

GuiShader::~GuiShader() {
}

void GuiShader::bindAttributes() {
    bindAttribute(0, "position");
}

void GuiShader::loadTransformationMatrix(glm::mat4 matrix) {
    loadMatrix(location_transformationMatrix, matrix);
}

void GuiShader::getAllUniformLocations() {
    location_transformationMatrix = getUniformLocation("transformationMatrix");
}
