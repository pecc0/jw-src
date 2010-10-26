/*
 * JWSphere.cpp
 *
 *  Created on: Oct 26, 2010
 *      Author: Petko
 */

#include "JWSphere.h"

JWSphere::JWSphere() {
	m_OctahedronVertices[0] = core::vector3df(0, 20, 0);
	m_OctahedronVertices[1] = core::vector3df(-20, 0, 0);
	m_OctahedronVertices[2] = core::vector3df(0, 0, -20);
	m_OctahedronVertices[3] = core::vector3df(0, 0, 20);
	//OctahedronVertices[4] = NULL;
	//OctahedronVertices[5] = NULL;
	m_OctahedronVertices[6] = core::vector3df(20, 0, 0);
	m_OctahedronVertices[7] = core::vector3df(0, -20, 0);
	//Vertices[3].Color = video::SColor(255,
	//		0, 0, 255);
	m_mapOctahedronTriangles[0] = JWTriangle(0b000, 0b001, 0b100, 0b010);
	m_mapOctahedronTriangles[1] = JWTriangle(0b001, 0b000, 0b011, 0b101);
	m_mapOctahedronTriangles[2] = JWTriangle(0b010, 0b110, 0b011, 0b000);
	m_mapOctahedronTriangles[3] = JWTriangle(0b011, 0b001, 0b010, 0b111);
	m_mapOctahedronTriangles[4] = JWTriangle(0b100, 0b000, 0b101, 0b110);
	m_mapOctahedronTriangles[5] = JWTriangle(0b101, 0b111, 0b100, 0b001);
	m_mapOctahedronTriangles[6] = JWTriangle(0b110, 0b010, 0b100, 0b111);
	m_mapOctahedronTriangles[7] = JWTriangle(0b111, 0b101, 0b011, 0b110);
}

JWSphere::~JWSphere() {
	// TODO Auto-generated destructor stub
}

u32 JWSphere::getTriangleVertex(u32 triangle, int i) {
	JWTriangle * tr = &(m_mapOctahedronTriangles[triangle]);
	int edge = i;
	JWTriangle * best;
	//Max 6 triangles around the vertex
	for (int j = 0; j < 6; j++) {
		if (edge == 0) {
			best = tr;
			if (tr->isUpside()) {
				break;
			}
		}
		JWTriangle * neighb =
				&(m_mapOctahedronTriangles[tr->getNeighbour(edge)]);
		int nghbEdge;

		//what is the index of current triangle in the neighbor's list
		for (nghbEdge = 0; nghbEdge < 3; nghbEdge++) {
			if (neighb->getNeighbour(nghbEdge) == tr->getTrIndex()) {
				break;
			}
		}
		//go counterclockwise in and continue with the neighbor.
		//This ensures we rotate around the same vertex
		edge = (nghbEdge + 1) % 3;
		tr = neighb;
	}
	//So, in worst case, we found a triangle for which the searched vertex is at index 0,
	//and in the best case, this triangle is upside
	return best->getTrIndex();
}
