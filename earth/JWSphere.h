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
#include <hash_map>

using namespace irr;
using namespace __gnu_cxx;

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

struct UnsignedHash {
	size_t operator()(const u32 __s) const {
		return __s;
	}
};

struct UnsignedEquals {
	size_t operator()(const u32& __x, const u32& __y) const {
		return __x == __y;
	}
};

class JWSphere: public irr::scene::ISceneNode {

	core::aabbox3d<f32> Box;
	video::S3DVertex OctahedronVertices[8]; // indexes 4 and 5 are not used
	video::SMaterial Material;
	// OctahedronTriangles[8];

	hash_map<u32, JWTriangle, UnsignedHash, UnsignedEquals> OctahedronTriangles;
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
