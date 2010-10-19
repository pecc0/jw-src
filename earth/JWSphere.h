/*
 * JWSphere.h
 *
 *  Created on: Oct 18, 2010
 *      Author: Petko
 */

#ifndef JWSPHERE_H_
#define JWSPHERE_H_

#include "ISceneNode.h"
#include <irrlicht.h>
#include "JWTriangle.h"

using namespace irr;

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

class JWSphere: public irr::scene::ISceneNode {

	core::aabbox3d<f32> Box;
	video::S3DVertex OctahedronVertices[6];
	video::SMaterial Material;
	JWTriangle OctahedronTriangles[8];

public:
	JWSphere(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id);
	virtual ~JWSphere();

	virtual void OnRegisterSceneNode();

	virtual void render();

	virtual const core::aabbox3d<f32>& getBoundingBox() const;

	virtual u32 getMaterialCount();

	virtual video::SMaterial& getMaterial(u32 i);
};

#endif /* JWSPHERE_H_ */
