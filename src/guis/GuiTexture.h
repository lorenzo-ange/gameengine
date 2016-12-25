/*
 * GuiTexture.h
 *
 *  Created on: 06 apr 2016
 *      Author: lorenzo
 */

#ifndef GUIS_GUITEXTURE_H_
#define GUIS_GUITEXTURE_H_

#include <glm/glm.hpp>

class GuiTexture {
public:
    GuiTexture(int texture, glm::vec2 position, glm::vec2 scale);
    virtual ~GuiTexture();

    const glm::vec2 getPosition() const {
        return position;
    }

    const glm::vec2 getScale() const {
        return scale;
    }

    int getTexture() const {
        return texture;
    }

private:
    int texture;
    glm::vec2 position;
    glm::vec2 scale;
};

#endif /* GUIS_GUITEXTURE_H_ */
