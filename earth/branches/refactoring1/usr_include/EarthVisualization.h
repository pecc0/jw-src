/*
 * JWSphere.h
 *
 *  Created on: Oct 18, 2010
 *      Author: Petko
 */

#ifndef EARTHVIS_H_
#define EARTHVIS_H_

#include "ISceneNode.h"
#include <irrlicht.h>
#include "JWTriangle.h"
#include <hash_map>

using namespace irr;
using namespace __gnu_cxx;

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif



class EarthVisualization: public irr::scene::ISceneNode
{
	core::aabbox3d<f32> m_Box;

    video::SMaterial m_Material;

    u32 * m_vIndices;
    void init();
    void clear();
public:
    EarthVisualization();
    EarthVisualization(scene::ISceneNode *parent, scene::ISceneManager *mgr, s32 id);
    virtual ~EarthVisualization();
    virtual void OnRegisterSceneNode();
    virtual void render();
    const virtual core::aabbox3d<f32>& getBoundingBox() const;

	virtual u32 getMaterialCount();

	virtual video::SMaterial& getMaterial(u32 i);

	void generateIndeces();
};

#endif /* EARTHVIS_H_ */
