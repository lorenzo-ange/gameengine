/*
 * OBJLoader.h
 *
 *  Created on: 31 mar 2016
 *      Author: lorenzo
 */

#ifndef RENDERENGINE_OBJLOADER_H_
#define RENDERENGINE_OBJLOADER_H_

#include <vector>
#include <stdio.h>
#include <string>
#include <glm/glm.hpp>
#include "../models/RawModel.h"
#include "Loader.h"

class OBJLoader {
public:
    OBJLoader();
    virtual ~OBJLoader();

    static RawModel loadObjModel(const char * fileName, Loader * loader);

private:

   static void processVertex(int vertexData[],
                             std::vector<int> * indices,
                             std::vector<glm::vec2> * textures,
                             std::vector<glm::vec3> * normals,
                             float textureArray[],
                             float normalsArray[]);
};

#endif /* RENDERENGINE_OBJLOADER_H_ */
