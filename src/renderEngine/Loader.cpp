/*
 * Loader.cpp
 *
 *  Created on: 28 mar 2016
 *      Author: lorenzo
 */

#include "Loader.h"

Loader::Loader() {
}

Loader::~Loader() {
}

RawModel Loader::loadToVAO(float positions[], int positionsLen,
                           float textureCoords[], int textureCoordsLen,
                           float normals[], int normalsLen,
                           int indices[], int indicesLen) {
    GLuint vaoID = createVAO();
    bindIndicesBuffer(indices, indicesLen);
    storeDataInAttributeList(0, 3, positions, positionsLen);
    storeDataInAttributeList(1, 2, textureCoords, textureCoordsLen);
    storeDataInAttributeList(2, 3, normals, normalsLen);
    unbindVAO();
    return RawModel(vaoID, indicesLen);
}

// Used in GUI rendering
RawModel Loader::loadToVAO(float positions[], int positionsLen, int dimensions) {
    GLuint vaoID = createVAO();
    storeDataInAttributeList(0, dimensions, positions, positionsLen);
    unbindVAO();
    return RawModel(vaoID, positionsLen/dimensions);
}

void Loader::cleanUp() {
    for(unsigned int i=0; i < vaos.size(); i++){
        GLuint vao = vaos[i];
        glDeleteVertexArrays(1, &vao);
    }
    for(unsigned int i=0; i < vbos.size(); i++){
        GLuint vbo = vbos[i];
        glDeleteBuffers(1, &vbo);
    }
    for(unsigned int i=0; i < textures.size(); i++){
        GLuint texture = textures[i];
        glDeleteTextures(1, &texture);
    }
}

void Loader::unbindVAO() {
    glBindVertexArray(0);
}

void Loader::storeDataInAttributeList(int attributeNumber, int coordinateSize, float data[], int dataLen) {
    GLuint vboID;
    glGenBuffers(1, &vboID);
    vbos.push_back(vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, dataLen*sizeof(float), data, GL_STATIC_DRAW);
    glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLuint Loader::createVAO() {
    GLuint vaoID;
    glGenVertexArrays(1, &vaoID);
    vaos.push_back(vaoID);
    glBindVertexArray(vaoID);
    return vaoID;
}

GLuint Loader::loadTexture(const char * fileName) {
    GLuint textureID = TextureLoader::getTexture(fileName);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.4f);
    textures.push_back(textureID);
    return textureID;
}

GLuint Loader::loadCubeMap(const char * textureFiles[]) {
    GLuint texID;
    glGenTextures(1, &texID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texID);

    for(int i=0; i<6; i++) {
        TextureData data = TextureData(textureFiles[i]);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, data.getWidth(), data.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, &(*data.getBuffer())[0]);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    textures.push_back(texID);
    return texID;
}

void Loader::bindIndicesBuffer(int indices[], int indicesLen) {
    GLuint vboID;
    glGenBuffers(1, &vboID);
    vbos.push_back(vboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesLen*sizeof(int), indices, GL_STATIC_DRAW);
}
