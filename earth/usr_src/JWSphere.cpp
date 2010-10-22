/*
 * JWSphere.cpp
 *
 *  Created on: Oct 18, 2010
 *      Author: Petko
 */

#include "JWSphere.h"



JWSphere::JWSphere(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id) :
	scene::ISceneNode(parent, mgr, id) {

	Material.Wireframe = false;
	Material.Lighting = false;

	OctahedronVertices[0] = video::S3DVertex(0, 20, 0, 0, 1, 0, video::SColor(255, 0,
			0, 0), 0, 0);
	OctahedronVertices[1] = video::S3DVertex(-20, 0, 0, -1, 0, 0, video::SColor(255, 0,
			255, 0), 0, 0);
	OctahedronVertices[2] = video::S3DVertex(0, 0, -20, 0, 0, -1, video::SColor(255, 0,
			255, 0), 0, 0);
	OctahedronVertices[3] = video::S3DVertex(0, 0, 20, 0, 0, 1, video::SColor(255,
			0, 255, 0), 0, 0);

	//OctahedronVertices[4] = NULL;
	//OctahedronVertices[5] = NULL;

	OctahedronVertices[6] = video::S3DVertex(20, 0, 0, 1, 0, 0, video::SColor(255,
				0, 255, 0), 0, 0);
	OctahedronVertices[7] = video::S3DVertex(0, -20, 0, 0, -1, 0, video::SColor(255,
					0, 255, 0), 0, 0);
	//Vertices[3].Color = video::SColor(255,
	//		0, 0, 255);

	OctahedronTriangles[0] = JWTriangle(0b000, 0b001, 0b100, 0b010);
	OctahedronTriangles[1] = JWTriangle(0b001, 0b000, 0b011, 0b101);
	OctahedronTriangles[2] = JWTriangle(0b010, 0b110, 0b011, 0b000);
	OctahedronTriangles[3] = JWTriangle(0b011, 0b001, 0b010, 0b111);
	OctahedronTriangles[4] = JWTriangle(0b100, 0b000, 0b101, 0b110);
	OctahedronTriangles[5] = JWTriangle(0b101, 0b111, 0b100, 0b001);
	OctahedronTriangles[6] = JWTriangle(0b110, 0b010, 0b100, 0b111);
	OctahedronTriangles[7] = JWTriangle(0b111, 0b101, 0b011, 0b110);

	/*
	 The Irrlicht Engine needs to know the bounding box of a scene node.
	 It will use it for automatic culling and other things. Hence, we
	 need to create a bounding box from the 4 vertices we use.
	 If you do not want the engine to use the box for automatic culling,
	 and/or don't want to create the box, you could also call
	 irr::scene::ISceneNode::setAutomaticCulling() with irr::scene::EAC_OFF.
	 */
	Box.reset(OctahedronVertices[0].Pos);
	for (s32 i = 1; i < 4; ++i)
	{
		Box.addInternalPoint(OctahedronVertices[i].Pos);
	}
}

JWSphere::~JWSphere() {
	// TODO Auto-generated destructor stub
}

void JWSphere::OnRegisterSceneNode() {
	if (IsVisible)
		SceneManager->registerNodeForRendering(this);

	ISceneNode::OnRegisterSceneNode();
}

void JWSphere::render() {
	u32 indices[] = { 2, 3, 0,  2, 1, 3,  1, 0, 3,  2, 0, 1 };
	video::IVideoDriver* driver = SceneManager->getVideoDriver();

	driver->setMaterial(Material);
	driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
	driver->drawVertexPrimitiveList(&OctahedronVertices[0], 4, &indices[0], 4,
			video::EVT_STANDARD, scene::EPT_TRIANGLES, video::EIT_32BIT);

}

const core::aabbox3d<f32>& JWSphere::getBoundingBox() const {
	return Box;
}

u32 JWSphere::getMaterialCount() {
	return 1;
}

video::SMaterial& JWSphere::getMaterial(u32 i) {
	return Material;
}

u32 JWSphere::getTriangleVertex(u32 triangle, int i)
{
    JWTriangle & tr = OctahedronTriangles[triangle];
    int edge = i;
    JWTriangle * best;
    //Max 6 triangles around the vertex
    for (int j = 0; j < 6; j++) {
    	JWTriangle & neighb = OctahedronTriangles[tr.getNeighbour(edge)];
    	int nghbEdge;
    	for (nghbEdge = 0; nghbEdge < 3; nghbEdge++) {
    		if (neighb.getNeighbour(nghbEdge) == tr.getTrIndex()) {
    			break;
    		}
    	}
    	edge = (nghbEdge + 1) % 3;
    	tr = OctahedronTriangles[tr.getNeighbour(edge)];
    	if (edge == 0) {
    		best = &tr;
    		if (tr.isUpside()) {
    			break;
    		}
    	}

    }
    //So, in worst case, we found a triangle for which the searched vertex is at index 0,
    //and in the best case, this triangle is upside
    return best->getTrIndex();
}



