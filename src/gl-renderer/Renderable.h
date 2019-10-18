/*
 * Renderable.h
 *
 *  Created on: 29 Apr 2019
 *      Author: mc18g13
 */

#ifndef RENDERABLE_H_
#define RENDERABLE_H_

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "GLMathematics.h"

class Renderable : public GLMathematics {
protected:
	static const unsigned arrayElementsForOneVertex = 6;
	float* vertices;
	unsigned int* indices;
	unsigned int vertexArrayLength;
	unsigned int vertexCount;
	unsigned int indexArrayLength;
	unsigned int totalVertexElements;

	void createVertexArray(unsigned int size);
	void createIndexArray(unsigned int size);

    void createVerticesForPositionAndColour();

public:
	virtual ~Renderable();

	void setup(unsigned int vertexCount,
			   unsigned int vertexArraySize,
			   unsigned int indexArraySize);

	float* getVertices();
	unsigned int* getIndices();

	unsigned int getVertexCount();
	unsigned int getVertexArrayLength();
	unsigned int getIndexArrayLength();
	unsigned int getTotalVertexElements();

	void printVertices();
	void printIndices();

};

#endif /* RENDERABLE_H_ */
