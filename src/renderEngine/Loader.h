/*
 * Loader.h
 *
 *  Created on: 28 mar 2016
 *      Author: lorenzo
 */

#ifndef RENDERENGINE_LOADER_H_
#define RENDERENGINE_LOADER_H_

#include <vector>
#include <GL/glew.h>
#include "../models/RawModel.h"
#include "../textures/TextureLoader.h"
#include "../textures/TextureData.h"

class Loader {
public:
    Loader();
    virtual ~Loader();

    RawModel loadToVAO(float positions[], int positionsLen,
                       float textureCoords[], int textureCoordsLen,
                       float normals[], int normalsLen,
                       int indices[], int indicesLen);
    RawModel loadToVAO(float positions[], int positionsLen, int dimensions);
    GLuint loadTexture(const char * fileName);
    GLuint loadCubeMap(const char * textureFiles[]);
    void cleanUp();

private:
    std::vector<GLuint> vaos;
    std::vector<GLuint> vbos;
    std::vector<GLuint> textures;

    void unbindVAO();
    void storeDataInAttributeList(int attributeNumber, int coordinateSize, float data[], int dataLen);
    GLuint createVAO();

    void bindIndicesBuffer(int indices[], int indicesLen);
};

#endif /* RENDERENGINE_LOADER_H_ */
