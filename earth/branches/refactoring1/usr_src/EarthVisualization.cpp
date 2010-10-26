/*
 * JWSphere.cpp
 *
 *  Created on: Oct 18, 2010
 *      Author: Petko
 */

#include "EarthVisualization.h"

EarthVisualization::EarthVisualization() :
	scene::ISceneNode(0, 0, 0)
{
	init();
}

EarthVisualization::EarthVisualization(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id) :
	scene::ISceneNode(parent, mgr, id)
{

	m_Material.Wireframe = true;
	m_Material.Lighting = false;
	init();

	/*
	 The Irrlicht Engine needs to know the bounding box of a scene node.
	 It will use it for automatic culling and other things. Hence, we
	 need to create a bounding box from the 4 vertices we use.
	 If you do not want the engine to use the box for automatic culling,
	 and/or don't want to create the box, you could also call
	 irr::scene::ISceneNode::setAutomaticCulling() with irr::scene::EAC_OFF.
	 */
	m_Box.reset(m_OctahedronVertices[0].Pos);
	for (s32 i = 1; i < 4; ++i)
	{
		m_Box.addInternalPoint(m_OctahedronVertices[i].Pos);
	}
}

void EarthVisualization::init()
{
	m_vIndices = 0;

	generateIndeces();
}

void EarthVisualization::clear()
{
	delete[] m_vIndices;
}

EarthVisualization::~EarthVisualization()
{
	clear();
}

void EarthVisualization::OnRegisterSceneNode()
{
	if (IsVisible)
		SceneManager->registerNodeForRendering(this);

	ISceneNode::OnRegisterSceneNode();
}

void EarthVisualization::render()
{
	video::IVideoDriver* driver = SceneManager->getVideoDriver();

	driver->setMaterial(m_Material);
	driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
	driver->drawVertexPrimitiveList(&m_OctahedronVertices[0], 8, m_vIndices,
			m_mapOctahedronTriangles.size(), video::EVT_STANDARD, scene::EPT_TRIANGLES, video::EIT_32BIT);

}

const core::aabbox3d<f32>& EarthVisualization::getBoundingBox() const
{
	return m_Box;
}

u32 EarthVisualization::getMaterialCount()
{
	return 1;
}

video::SMaterial& EarthVisualization::getMaterial(u32 i)
{
	return m_Material;
}


void EarthVisualization::generateIndeces()
{
	clear();
	m_vIndices = new u32[m_mapOctahedronTriangles.size() * 3];

	int i = 0;

	TrianglesMap::iterator it = m_mapOctahedronTriangles.begin();
	for (; it != m_mapOctahedronTriangles.end(); ++it)
	{
		//it->first
		for (int j = 2; j >= 0; --j) {
			m_vIndices[i++] = getTriangleVertex(it->first, j);
		}
	}
}

