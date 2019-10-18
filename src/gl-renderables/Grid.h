/*
 * Grid.h
 *
 *  Created on: 11 Apr 2019
 *      Author: mc18g13
 */

#ifndef GRID_H_
#define GRID_H_

#include "Renderable.h"

class Grid : public Renderable {
public:
	Grid();
	void addNumbersToIndices(unsigned int *array, unsigned int index);
	virtual ~Grid();

    float lineSpacing = 100.0f;
    float totalWidth = 6000.0f;

    int arrayElementsForPairOfVertices = 2 * arrayElementsForOneVertex;

};

#endif /* GRID_H_ */
