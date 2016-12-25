/*
 * GuiShader.h
 *
 *  Created on: 06 apr 2016
 *      Author: lorenzo
 */

#ifndef GUIS_GUISHADER_H_
#define GUIS_GUISHADER_H_

#include "../shaders/ShaderProgram.h"

class GuiShader : public ShaderProgram {
public:
    GuiShader();
    virtual ~GuiShader();

    void loadTransformationMatrix(glm::mat4 matrix);

protected:
    void bindAttributes();
    void getAllUniformLocations();

private:
    static const char * VERTEX_FILE;
    static const char * FRAGMENT_FILE;
    GLint location_transformationMatrix;
};

#endif /* GUIS_GUISHADER_H_ */
