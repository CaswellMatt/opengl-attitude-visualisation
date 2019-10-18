/*
 * Cylinder.h
 *
 *  Created on: 26 Apr 2019
 *      Author: mc18g13
 */

#ifndef CYLINDER_H_
#define CYLINDER_H_
#include <Renderable.h>

class Cylinder : public Renderable {
public:
	Cylinder(vec3 unitVectorDirectionOfCylinder, vec3 startPointCoordinate, vec3 color, float length, float radius);

private:
	void calculateVertices(vec3 unitVectorDirectionOfCylinder, vec3 startPointCoordinate, vec3 color, float length, float radius);
	void calculateIndices();
};

#endif /* CYLINDER_H_ */
