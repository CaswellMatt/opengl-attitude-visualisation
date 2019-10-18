/*
 * RenderableData.h
 *
 *  Created on: 13 May 2019
 *      Author: mc18g13
 */

#ifndef RENDERABLEDATA_H_
#define RENDERABLEDATA_H_

#include "Renderable.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class RenderableData {
public:
    RenderableData(Renderable &object);
	virtual ~RenderableData();

    VertexArray vertexArray;
    VertexBuffer vertexBuffer;
    IndexBuffer indexBuffer;
    VertexBufferLayout layout;

	void createVerticesForPositionAndColour();
};

#endif /* SRC_GL_RENDERABLES_RENDERABLEDATA_H_ */
