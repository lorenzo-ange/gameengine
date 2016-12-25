/*
 * Terrain.cpp
 *
 *  Created on: 02 apr 2016
 *      Author: lorenzo
 */

#include "Terrain.h"

const float Terrain::SIZE = 800;
const float Terrain::MAX_HEIGHT = 20;
const float Terrain::MAX_PIXEL_COLOUR = 256 * 256 * 256;

Terrain::Terrain(int gridX, int gridZ,
                 Loader * loader,
                 TerrainTexturePack * texturePack,
                 TerrainTexture * blendMap,
                 const char * heightMap) {
    this->x = (float) gridX * SIZE;
    this->z = (float) gridZ * SIZE;
    this->model = new RawModel(generateTerrain(loader, heightMap));
    this->texturePack = texturePack;
    this->blendMap = blendMap;

}

Terrain::~Terrain() {
    delete model;
    delete[] heights;
}

RawModel Terrain::generateTerrain(Loader * loader, const char * heightMap){
    std::vector<unsigned char> image; //the raw pixels
    unsigned int imageWidth, imageHeight;

    SDL_Surface *surface = IMG_Load(heightMap);
    if(surface == NULL) {
        fprintf(stderr, "SDL loader error for '%s'", heightMap);
        return RawModel(-1, -1);
    }
    else {
        std::vector<unsigned char> tmp((unsigned char *) surface->pixels,
                                       (unsigned char *) surface->pixels + surface->w * surface->h * 4);
        imageWidth = (unsigned int) surface->w;
        imageHeight = (unsigned int) surface->h;
        for (unsigned int i = 0; i < tmp.size(); i++) {
            image.push_back(tmp[i]);
        }
        SDL_FreeSurface(surface);
    }

    vertexCount = imageHeight;

    heights = new float[vertexCount*vertexCount];

    int count = vertexCount * vertexCount;
    float * vertices = new float[count * 3];
    float * normals = new float[count * 3];
    float * textureCoords = new float[count*2];
    int * indices = new int[6*(vertexCount-1)*(vertexCount-1)];
    int vertexPointer = 0;

    for(int i=0;i<vertexCount;i++){
        for(int j=0;j<vertexCount;j++){
            vertices[vertexPointer*3] = (float)j/((float)vertexCount - 1) * SIZE;
            float height = getHeight(j, i, &image, imageWidth, imageHeight);
            heights[j * vertexCount + i] = height;
            vertices[vertexPointer*3+1] = height;
            vertices[vertexPointer*3+2] = (float)i/((float)vertexCount - 1) * SIZE;
            glm::vec3 normal = calculateNormal(j, i, &image, imageWidth, imageHeight);
            normals[vertexPointer*3] = normal.x;
            normals[vertexPointer*3+1] = normal.y;
            normals[vertexPointer*3+2] = normal.z;
            textureCoords[vertexPointer*2] = (float)j/((float)vertexCount - 1);
            textureCoords[vertexPointer*2+1] = (float)i/((float)vertexCount - 1);
            vertexPointer++;
        }
    }
    int pointer = 0;
    for(int gz=0;gz<vertexCount-1;gz++){
        for(int gx=0;gx<vertexCount-1;gx++){
            int topLeft = (gz*vertexCount)+gx;
            int topRight = topLeft + 1;
            int bottomLeft = ((gz+1)*vertexCount)+gx;
            int bottomRight = bottomLeft + 1;
            indices[pointer++] = topLeft;
            indices[pointer++] = bottomLeft;
            indices[pointer++] = topRight;
            indices[pointer++] = topRight;
            indices[pointer++] = bottomLeft;
            indices[pointer++] = bottomRight;
        }
    }

    RawModel model = loader->loadToVAO(vertices, count * 3,
                                       textureCoords, count * 2,
                                       normals, count * 3,
                                       indices, 6*(vertexCount-1)*(vertexCount-1));
    delete[] vertices;
    delete[] normals;
    delete[] indices;
    delete[] textureCoords;

    return model;
}

float Terrain::getHeight(int x, int z, std::vector<unsigned char>* image, int imageWidth, int imageHeight) {
    if(x<0 || x>=imageHeight || z<0 || z>=imageHeight) {
        return 0;
    }

    // simulate "int getRGB(int x, int y)" of java BufferedImage
    // that returns an integer representing a pixel of the image
    // the int returned is in TYPE_INT_ARGB format "AAAARRRRGGGGBBBB"
    // this int is signed and always negative because AAAA is "1111...1111"
    unsigned int offset = x*4 + z*imageWidth*4;
    unsigned char r = (*image)[offset];
    unsigned char g = (*image)[offset+1];
    unsigned char b = (*image)[offset+2];
    unsigned char a = (*image)[offset+3];
    int height_i = 0 - (~((a << 24) | (r << 16) | (g << 8) | b) + 1);

    float height = height_i;
    height += MAX_PIXEL_COLOUR/2.0f;
    height /= MAX_PIXEL_COLOUR/2.0f;
    height *= MAX_HEIGHT;
    return height;
}

float Terrain::getHeightOfTerrain(float worldX, float worldZ) {
    float terrainX = worldX - this->x;
    float terrainZ = worldZ - this->z;
    float gridSquareSize = SIZE / ((float) vertexCount - 1);
    int gridX = (int) floor(terrainX / gridSquareSize);
    int gridZ = (int) floor(terrainZ / gridSquareSize);
    if(gridX >= vertexCount-1 || gridZ >= vertexCount-1 || gridX < 0 || gridZ < 0) {
        return 0;
    }

    float xCoord = (float) fmod(terrainX, gridSquareSize) / gridSquareSize;
    float zCoord = (float) fmod(terrainZ, gridSquareSize) / gridSquareSize;
    float answer;
    if(xCoord < (1-zCoord)) {
        answer = barryCentric(glm::vec3(0, heights[gridX * vertexCount + gridZ], 0),
                                     glm::vec3(1, heights[(gridX + 1) * vertexCount + gridZ], 0),
                                     glm::vec3(0, heights[gridX * vertexCount + (gridZ + 1)], 1),
                                     glm::vec2(xCoord, zCoord));
    }
    else {
        answer = barryCentric(glm::vec3(1, heights[(gridX + 1) * vertexCount + gridZ], 0),
                                     glm::vec3(1, heights[(gridX + 1) * vertexCount + (gridZ + 1)], 1),
                                     glm::vec3(0, heights[(gridX) * vertexCount + (gridZ + 1)], 1),
                                     glm::vec2(xCoord, zCoord));

    }
    return answer;
}

glm::vec3 Terrain::calculateNormal(int x, int z,
                                   std::vector<unsigned char>* image,
                                   int imageWidth, int imageHeight) {

    float heightL = getHeight(x-1, z, image, imageWidth, imageHeight);
    float heightR = getHeight(x+1, z, image, imageWidth, imageHeight);
    float heightD = getHeight(x, z-1, image, imageWidth, imageHeight);
    float heightU = getHeight(x, z+1, image, imageWidth, imageHeight);
    glm::vec3 normal = glm::vec3(heightL - heightR, 2.0f, heightD - heightU);
    normal = glm::normalize(normal);
    return normal;

}

float Terrain::barryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos) {
    float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
    float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
    float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
    float l3 = 1.0f - l1 - l2;
    return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}
