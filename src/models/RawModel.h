/*
 * RawModel.h
 *
 *  Created on: 28 mar 2016
 *      Author: lorenzo
 */

#ifndef MODELS_RAWMODEL_H_
#define MODELS_RAWMODEL_H_

class RawModel {
public:
    RawModel(int vaoID, int vertexCount);
    virtual ~RawModel();

    int getVaoID() const {
        return vaoID;
    }

    int getVertexCount() const {
        return vertexCount;
    }

private:
    int vaoID;
    int vertexCount;
};

#endif /* MODELS_RAWMODEL_H_ */
