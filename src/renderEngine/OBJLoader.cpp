/*
 * OBJLoader.cpp
 *
 *  Created on: 31 mar 2016
 *      Author: lorenzo
 */

#include "OBJLoader.h"

OBJLoader::OBJLoader() {
}

OBJLoader::~OBJLoader() {
}

RawModel OBJLoader::loadObjModel(const char * fileName, Loader * loader) {
    printf("Loading OBJ file : %s\n", fileName);

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> textures;
    std::vector<glm::vec3> normals;
    std::vector<int> indices;

    float * verticesArray;
    float * textureArray;
    float * normalsArray;
    int * indicesArray;

    FILE * file = fopen(fileName, "r");
    if( file == NULL ){
        fprintf(stderr, "Impossible to open the file %s\n", fileName);
        return RawModel(-1, -1);
    }

    // NOTE: lineStart is used also in the second loop
    char lineStart[128];

    while(1) {
        int res = fscanf(file, "%s", lineStart);
        if (res == EOF) {
            fprintf(stderr, "Malformed OBJ file '%s' Try exporting with other options\n", fileName);
            return RawModel(-1, -1);
        }

        if ( strcmp(lineStart, "v") == 0 ){
            // Vertex coords line
            glm::vec3 vertex;
            int matches = fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
            if (matches != 3){
                fprintf(stderr, "Malformed OBJ file '%s' Try exporting with other options\n", fileName);
                return RawModel(-1, -1);
            }
            vertices.push_back(vertex);
        }else if ( strcmp(lineStart, "vt") == 0 ){
            // Texture coords line
            glm::vec2 texture;
            int matches = fscanf(file, "%f %f\n", &texture.x, &texture.y );
            if (matches != 2){
                fprintf(stderr, "Malformed OBJ file '%s' Try exporting with other options\n", fileName);
                return RawModel(-1, -1);
            }
            textures.push_back(texture);
        }else if (strcmp(lineStart, "vn") == 0 ){
            // Vertex normal line
            glm::vec3 normal;
            int matches = fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
            if (matches != 3){
                fprintf(stderr, "Malformed OBJ file '%s' Try exporting with other options\n", fileName);
                return RawModel(-1, -1);
            }
            normals.push_back(normal);
        }else if ( strcmp(lineStart, "f") == 0 ){
            // First face line, we aready read all the vertices coords, texture coords and normals
            // Time to read face triplets and sort vertices data
            // End this loop and go to the next one
            textureArray = new float[vertices.size() * 2];
            normalsArray = new float[vertices.size() * 3];
            break;
        }
    }

    int res = 44; // something different than EOF
    while(res != EOF) {
        if (strcmp(lineStart, "f") != 0) {
            // A comment or something we're not interested in
            // Go to next line
            res = fscanf(file, "%s", lineStart);
            continue;
        }

        int vertexIndex[3], textureIndex[3], normalIndex[3];
        int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &textureIndex[0], &normalIndex[0], &vertexIndex[1], &textureIndex[1], &normalIndex[1], &vertexIndex[2], &textureIndex[2], &normalIndex[2] );
        if (matches != 9){
            fprintf(stderr, "Malformed OBJ file '%s' Try exporting with other options\n", fileName);
            delete[] textureArray;
            delete[] normalsArray;
            return RawModel(-1, -1);
        }

        int vertexData[3];
        // Process each of the 3 vertices of the triangular face
        for(int i=0; i<3; i++) {
            vertexData[0] = vertexIndex[i];
            vertexData[1] = textureIndex[i];
            vertexData[2] = normalIndex[i];
            processVertex(vertexData, &indices, &textures, &normals, textureArray, normalsArray);
        }

        res = fscanf(file, "%s", lineStart);
    }

    verticesArray = new float[vertices.size() * 3];
    indicesArray = new int[indices.size()];

    int vertexPointer = 0;
    for(unsigned int i=0; i<vertices.size(); i++){
        glm::vec3 vertex = vertices[i];
        verticesArray[vertexPointer++] = vertex.x;
        verticesArray[vertexPointer++] = vertex.y;
        verticesArray[vertexPointer++] = vertex.z;
    }

    for (unsigned int i = 0; i < indices.size(); i++) {
        indicesArray[i] = indices[i];
    }

    RawModel rawModel = loader->loadToVAO(verticesArray, vertices.size()*3,
                                            textureArray, vertices.size()*2,
                                            normalsArray, vertices.size()*3,
                                            indicesArray, indices.size());

    delete[] verticesArray;
    delete[] textureArray;
    delete[] normalsArray;
    delete[] indicesArray;

    return rawModel;
}

void OBJLoader::processVertex(int vertexData[],
                              std::vector<int> * indices, std::vector<glm::vec2> * textures,
                              std::vector<glm::vec3> * normals, float textureArray[],
                              float normalsArray[]) {
    int currentVertexPointer = vertexData[0] - 1;
    indices->push_back(currentVertexPointer);

    glm::vec2 currentTex = (*textures)[vertexData[1] - 1];
    textureArray[currentVertexPointer * 2] = currentTex.x;
    textureArray[currentVertexPointer * 2 + 1] = 1 - currentTex.y;

    glm::vec3 currentNorm = (*normals)[vertexData[2] - 1];
    normalsArray[currentVertexPointer * 3] = currentNorm.x;
    normalsArray[currentVertexPointer * 3 + 1] = currentNorm.y;
    normalsArray[currentVertexPointer * 3 + 2] = currentNorm.z;
}
