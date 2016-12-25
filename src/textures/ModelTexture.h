/*
 * ModelTexture.h
 *
 *  Created on: 30 mar 2016
 *      Author: lorenzo
 */

#ifndef TEXTURES_MODELTEXTURE_H_
#define TEXTURES_MODELTEXTURE_H_

class ModelTexture {
public:
    ModelTexture(int id);
    virtual ~ModelTexture();

    int getID() const {
        return textureID;
    }

    float getReflectivity() const {
        return reflectivity;
    }

    void setReflectivity(float reflectivity) {
        this->reflectivity = reflectivity;
    }

    float getShineDamper() const {
        return shineDamper;
    }

    void setShineDamper(float shineDamper) {
        this->shineDamper = shineDamper;
    }

    bool isHasTransparency() const {
        return hasTransparency;
    }

    void setHasTransparency(bool hasTransparency = false) {
        this->hasTransparency = hasTransparency;
    }

    bool isUseFakeLighting() const {
        return useFakeLighting;
    }

    void setUseFakeLighting(bool useFakeLighting) {
        this->useFakeLighting = useFakeLighting;
    }

    int getNumberOfRows() const {
        return numberOfRows;
    }

    void setNumberOfRows(int numberOfRows) {
        this->numberOfRows = numberOfRows;
    }

private:
    int textureID;
    float shineDamper;
    float reflectivity;
    bool hasTransparency;
    bool useFakeLighting;
    int numberOfRows;
};

#endif /* TEXTURES_MODELTEXTURE_H_ */
