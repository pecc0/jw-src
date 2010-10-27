/*
 * JWSphere.cpp
 *
 *  Created on: Oct 26, 2010
 *      Author: Petko
 */

#include "JWSphere.h"
namespace jw
{

bool isVertexUndeletable(KEY key) {
	return key <= (8 << 14);
}

JWSphere::JWSphere()
{
	m_mapVertices = AutoCleanHashMap<core::vector3df> (1046527, 8 << 14, &isVertexUndeletable);
	m_mapVertices.put(0, core::vector3df(0, 20, 0));
	m_mapVertices.put(1, core::vector3df(-20, 0, 0));
	m_mapVertices.put(2, core::vector3df(0, 0, -20));
	m_mapVertices.put(3, core::vector3df(0, 0, 20));
	//OctahedronVertices[4] = NULL;
	//OctahedronVertices[5] = NULL;
	m_mapVertices.put(6, core::vector3df(20, 0, 0));
	m_mapVertices.put(7, core::vector3df(0, -20, 0));
	//Vertices[3].Color = video::SColor(255,
	//		0, 0, 255);

	m_vmapTriangles[0] = AutoCleanHashMap<JWTriangle> (8);
	m_vmapTriangles[1] = AutoCleanHashMap<JWTriangle> (8 << 2);
	m_vmapTriangles[2] = AutoCleanHashMap<JWTriangle> (8 << 4);
	m_vmapTriangles[3] = AutoCleanHashMap<JWTriangle> (8 << 6);
	m_vmapTriangles[4] = AutoCleanHashMap<JWTriangle> (8 << 8);
	m_vmapTriangles[5] = AutoCleanHashMap<JWTriangle> (8 << 10);
	m_vmapTriangles[6] = AutoCleanHashMap<JWTriangle> (8 << 12);
	m_vmapTriangles[7] = AutoCleanHashMap<JWTriangle> (8 << 14);

	AutoCleanHashMap<JWTriangle> & octahedronTriangles = m_vmapTriangles[0];

	octahedronTriangles.put(0, JWTriangle(0b000, 0b001, 0b100, 0b010));
	octahedronTriangles.put(1, JWTriangle(0b001, 0b000, 0b011, 0b101));
	octahedronTriangles.put(2, JWTriangle(0b010, 0b110, 0b011, 0b000));
	octahedronTriangles.put(3, JWTriangle(0b011, 0b001, 0b010, 0b111));
	octahedronTriangles.put(4, JWTriangle(0b100, 0b000, 0b101, 0b110));
	octahedronTriangles.put(5, JWTriangle(0b101, 0b111, 0b100, 0b001));
	octahedronTriangles.put(6, JWTriangle(0b110, 0b010, 0b100, 0b111));
	octahedronTriangles.put(7, JWTriangle(0b111, 0b101, 0b011, 0b110));

}

JWSphere::~JWSphere()
{
	// TODO Auto-generated destructor stub
}

u32 JWSphere::getTriangleVertex(u32 triangle, int level, int i)
{
	AutoCleanHashMap<JWTriangle> & trianglesMap = m_vmapTriangles[level];

	JWTriangle * tr = trianglesMap.get(triangle);
	int edge = i;
	JWTriangle * best;
	//Max 6 triangles around the vertex
	for (int j = 0; j < 6; j++)
	{
		if (edge == 0)
		{
			best = tr;
			if (tr->isUpside())
			{
				break;
			}
		}
		JWTriangle * neighb = trianglesMap.get(tr->getNeighbour(edge));
		int nghbEdge;

		//what is the index of current triangle in the neighbor's list
		for (nghbEdge = 0; nghbEdge < 3; nghbEdge++)
		{
			if (neighb->getNeighbour(nghbEdge) == tr->getTrIndex())
			{
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
}
