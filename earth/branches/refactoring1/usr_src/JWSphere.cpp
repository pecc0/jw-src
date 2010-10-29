/*
 * JWSphere.cpp
 *
 *  Created on: Oct 26, 2010
 *      Author: Petko
 */

#include "LoggerFactory.h"
#include "JWSphere.h"

using namespace jw;

bool isVertexUndeletable(KEY key)
{
	return key <= (8 << 14); //8 << 14 = 8 << (PERSISTENT_CACHED_LEVEL * 2)
}

jw::JWSphere::JWSphere() :
	log(LoggerFactory::getLogger("com.jw.JWSphere"))
{
	log->info("Initialize JWSphere");
	m_mapVertices = AutoCleanHashMap<core::vector3df> (1046527, 0.8, 0.2, 8
			<< 14, &isVertexUndeletable);
	m_mapVertices.init();

	m_mapVertices.put(0, core::vector3df(0, SPHERE_RADIUS, 0));
	m_mapVertices.put(1, core::vector3df(-SPHERE_RADIUS, 0, 0));
	m_mapVertices.put(2, core::vector3df(0, 0, -SPHERE_RADIUS));
	m_mapVertices.put(3, core::vector3df(0, 0, SPHERE_RADIUS));
	//OctahedronVertices[4] = NULL;
	//OctahedronVertices[5] = NULL;
	m_mapVertices.put(6, core::vector3df(SPHERE_RADIUS, 0, 0));
	m_mapVertices.put(7, core::vector3df(0, -SPHERE_RADIUS, 0));
	//Vertices[3].Color = video::SColor(255,
	//		0, 0, 255);

	//Triangles which will not be deleted
	m_vmapTriangles[0] = AutoCleanHashMap<JWTriangle> (8, 2.0); //2.0 assure that auto clearing is disabled
	m_vmapTriangles[1] = AutoCleanHashMap<JWTriangle> (8 << 2, 2.0);
	m_vmapTriangles[2] = AutoCleanHashMap<JWTriangle> (8 << 4, 2.0);
	m_vmapTriangles[3] = AutoCleanHashMap<JWTriangle> (8 << 6, 2.0);
	m_vmapTriangles[4] = AutoCleanHashMap<JWTriangle> (8 << 8, 2.0);
	m_vmapTriangles[5] = AutoCleanHashMap<JWTriangle> (8 << 10, 2.0);
	m_vmapTriangles[6] = AutoCleanHashMap<JWTriangle> (8 << 12, 2.0);
	//8 << 14 = 8 << (PERSISTENT_CACHED_LEVEL * 2)
	m_vmapTriangles[7] = AutoCleanHashMap<JWTriangle> (8 << 14, 2.0);
	//End of Triangles which will not be deleted

	for (int i = 0; i < 8; i++)
	{
		m_vmapTriangles[i].init();
	}

	AutoCleanHashMap<JWTriangle> & octahedronTriangles = m_vmapTriangles[0];

	octahedronTriangles.put(0, JWTriangle(0b000, 0b001, 0b100, 0b010));
	octahedronTriangles.put(1, JWTriangle(0b001, 0b000, 0b011, 0b101));
	octahedronTriangles.put(2, JWTriangle(0b010, 0b110, 0b011, 0b000));
	octahedronTriangles.put(3, JWTriangle(0b011, 0b001, 0b010, 0b111));
	octahedronTriangles.put(4, JWTriangle(0b100, 0b000, 0b101, 0b110));
	octahedronTriangles.put(5, JWTriangle(0b101, 0b111, 0b100, 0b001));
	octahedronTriangles.put(6, JWTriangle(0b110, 0b010, 0b100, 0b111));
	octahedronTriangles.put(7, JWTriangle(0b111, 0b101, 0b011, 0b110));

	log->info("Initialize JWSphere ended");
}

jw::JWSphere::~JWSphere()
{
	// TODO Auto-generated destructor stub
}

core::vector3df* jw::JWSphere::getVertex(u32 key)
{
	core::vector3df *result = m_mapVertices.get(key);
	if (!result)
	{
		//find the level of the biggest triangle in which the vertex is at internal position 0
		//The ID of the triangle is equal to the ID (key) of the vertex
		int level = MAX_TRIANGLE_LEVELS;
		//u32 triangleId = key;

		while (level > 0)
		{
			if (((key >> (level * 2 + 1)) & 0b11) == 0b00)
			{
				level--;
			}
			else
			{
				break;
			}
		}
		//level 0 should be cached
		if (level == 0)
		{
			log->error("Vertex %d should be in cache and never deleted", key);
			return NULL;
		}

		//up one level - will divide the parent triangle
		--level;

		//The ID of the parent of the triangle whose index the vertex received
		u32 parentTriangleId = key & (0xEFFFFFFF >> (MAX_TRIANGLE_LEVELS * 2
				- level * 2));

		divideTriangle(parentTriangleId, level);

		//now it must be in the map
		result = m_mapVertices.get(key);

	}
	return result;
}

JWTriangle* jw::JWSphere::getTriangle(u32 key, int level)
{
	AutoCleanHashMap<JWTriangle> & trianglesMap = m_vmapTriangles[level];
	JWTriangle* result;
	result = trianglesMap.get(key);
	if (result == NULL)
	{
		//TODO Calculate and add to map
		return NULL;
	}
	else
	{
		return result;
	}
}

u32 jw::JWSphere::getTriangleVertex(u32 triangle, int level, int i)
{
	JWTriangle * tr = getTriangle(triangle, level);
	int edge = i;
	JWTriangle * best;
	//Max 6 triangles around the vertex
	for (int j = 0; j < 6; j++)
	{
		if (edge == 0)
		{

			if (tr->isUpside(level))
			{
				best = tr;
				break;
			}
			else
			{
				//There are cases when for same vertex is at #0 for 2 downside
				//triangles only. I choose the lower index in this case
				if (best == NULL || best->getTrIndex() > tr->getTrIndex())
				{
					best = tr;
				}
			}
		}
		JWTriangle * neighb = getTrNeighbour(tr, level, edge);

		//what is the index of current triangle in the neighbor's list
		int nghbEdge = neighb->getNeighborInternalIndex(tr->getTrIndex());

		//go counterclockwise in and continue with the neighbor.
		//This ensures we rotate around the same vertex
		edge = (nghbEdge + 1) % 3;
		tr = neighb;
	}
	//So, in worst case, we found a triangle for which the searched vertex is at index 0,
	//and in the best case, this triangle is upside
	return best->getTrIndex();
}

void jw::JWSphere::divideTriangle(u32 triangle, int level)
{
	if (level < MAX_TRIANGLE_LEVELS)
	{
		JWTriangle* tr = getTriangle(triangle, level);
		JWTriangle* nghs[3];
		core::vector3df* verteces[3];
		for (int edge = 0; edge < 3; edge++)
		{
			nghs[edge] = getTrNeighbour(tr, level, edge);
			verteces[edge]
					= getVertex(getTriangleVertex(triangle, level, edge));

		}

		u32 newTrianglesIndexes[4];
		for (int i = 0; i < 4; i++)
		{
			newTrianglesIndexes[i] = tr->getChildIndex(i, level);
		}
		for (int edge = 0; edge < 3; edge++)
		{
			JWTriangle* ngh1 = nghs[edge];
			JWTriangle* ngh2 = nghs[(edge + 2) % 3];

			//in most cases nghEdge will be equal to edge, but in some border cases
			//it is not, anyway we need to handle that cases too :)
			int nghEdge1 = ngh1->getNeighborInternalIndex(triangle);
			int nghEdge2 = ngh2->getNeighborInternalIndex(triangle);

			u32 subNgh1 = ngh1->getChildIndex((nghEdge1 + 1) % 3, level);
			u32 subNgh2 = ngh2->getChildIndex(nghEdge2, level);

			u32 subNgh3 = ngh1->getChildIndex(nghEdge1, level);

			//u32 iV1 = tr->getChildIndex(edge, level);
			//u32 iV2 = tr->getChildIndex((edge + 1) % 3, level);

			JWTriangle newTriangle;
			newTriangle.setTileIndex(newTrianglesIndexes[edge]);
			newTriangle.setNeighbor(subNgh1, edge);
			newTriangle.setNeighbor(newTrianglesIndexes[0b11], (edge + 1) % 3);
			newTriangle.setNeighbor(subNgh2, (edge + 2) % 3);

			m_vmapTriangles[level + 1].put(newTrianglesIndexes[edge],
					&newTriangle);

			core::vector3df* v1 = verteces[edge];
			core::vector3df* v2 = verteces[(edge + 1) % 3];

			core::vector3df newVertex = (*v1) + (*v2);
			newVertex.setLength(SPHERE_RADIUS);

			u32 vertexIndex;

			if (tr->isUpside(level))
			{
				if (edge == 1)
				{
					if (ngh1->isUpside(level))
					{
						//happens rarely
						if (nghEdge1 == 1)
						{
							//it's complicated - for this vertex we have 2 triangles for which the
							//vertex is at position 0, and both of them are downside
							vertexIndex = min(ngh1->getChildIndex(0b11, level),
									newTrianglesIndexes[0b11]);
						}
						else if (nghEdge1 == 0)
						{
							vertexIndex = subNgh1;
						}
						else
						{
							vertexIndex = subNgh3;
						}
					}
					else
					{
						vertexIndex = ngh1->getChildIndex(0b11, level);
					}
				}
				else
				{
					vertexIndex = newTrianglesIndexes[(edge + 1) % 3];
				}
			}
			else
			{
				if (edge == 1)
				{
					vertexIndex = newTrianglesIndexes[0b00];
				} else {

				}
			}

			m_mapVertices.put(vertexIndex, &newVertex);
		}
		JWTriangle middleTriangle(newTrianglesIndexes[3],
				newTrianglesIndexes[2], newTrianglesIndexes[0],
				newTrianglesIndexes[1]);

		m_vmapTriangles[level + 1].put(newTrianglesIndexes[3], &middleTriangle);
	}
	else
	{
		log->warn("Trying to divide triangle %X at "
			"level %d > MAX_TRIANGLE_LEVELS", triangle, level);
	}
}

JWTriangle *jw::JWSphere::getTrNeighbour(JWTriangle *triangle, int level,
		int edge)
{
	return getTriangle(triangle->getNeighbour(edge), level);
	/*
	 if (triangle->isNeighbourGenerated(edge))
	 {
	 return getTriangle(triangle->getNeighbour(edge), level);
	 }
	 else
	 {
	 //This should fix all links. I hope triangle is taken from the pool.
	 //divideTriangle will manage the triangle to which I have pointer
	 divideTriangle(triangle->getNeighbour(edge), level - 1);

	 //now triangle->isNeighbourGenerated(edge) should return true
	 return getTriangle(triangle->getNeighbour(edge), level);
	 }
	 */
}

