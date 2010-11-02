/*
 * JWSceneNodeAnimatorCameraFPS.cpp
 *
 *  Created on: Nov 2, 2010
 *      Author: Petko
 */

#include "irrlitch/JWSceneNodeAnimatorCameraFPS.h"

namespace irr
{
namespace scene
{

JWSceneNodeAnimatorCameraFPS::JWSceneNodeAnimatorCameraFPS(
		ISceneNodeAnimatorCameraFPS* wrapped) :
	m_Wrapped(wrapped)
{
	m_Wrapped->grab();
}

JWSceneNodeAnimatorCameraFPS::~JWSceneNodeAnimatorCameraFPS()
{
	m_Wrapped->drop();
}

f32 JWSceneNodeAnimatorCameraFPS::getRotateSpeed() const
{
	return m_Wrapped->getRotateSpeed();
}

void JWSceneNodeAnimatorCameraFPS::setKeyMap(SKeyMap *map, u32 count)
{
	m_Wrapped->setKeyMap(map, count);
}

void JWSceneNodeAnimatorCameraFPS::setRotateSpeed(f32 rotateSpeed)
{
	m_Wrapped->setRotateSpeed(rotateSpeed);
}

void JWSceneNodeAnimatorCameraFPS::setMoveSpeed(f32 moveSpeed)
{
	m_Wrapped->setMoveSpeed(moveSpeed);
}

f32 JWSceneNodeAnimatorCameraFPS::getMoveSpeed() const
{
	return m_Wrapped->getMoveSpeed();
}

bool JWSceneNodeAnimatorCameraFPS::OnEvent(const SEvent & event)
{
	return m_Wrapped->OnEvent(event);
}

void JWSceneNodeAnimatorCameraFPS::animateNode(ISceneNode *node, u32 timeMs)
{
	m_Wrapped->animateNode(node, timeMs);
}


void JWSceneNodeAnimatorCameraFPS::setVerticalMovement(bool allow)
{
}

ISceneNodeAnimator *JWSceneNodeAnimatorCameraFPS::createClone(ISceneNode *node,
		ISceneManager *newManager)
{

	return new JWSceneNodeAnimatorCameraFPS(
			(ISceneNodeAnimatorCameraFPS*)((m_Wrapped->createClone(node, newManager))));
    }

    void JWSceneNodeAnimatorCameraFPS::setInvertMouse(bool invert)
    {
        m_Wrapped->setInvertMouse(invert);
    }

    JWSceneNodeAnimatorCameraFPS *JWSceneNodeAnimatorCameraFPS::injectOnFPSCamera(ICameraSceneNode *fpsCamera)
    {
        JWSceneNodeAnimatorCameraFPS *result = new JWSceneNodeAnimatorCameraFPS((ISceneNodeAnimatorCameraFPS*)(((((*(fpsCamera->getAnimators().begin())))))));
        fpsCamera->removeAnimators();
        fpsCamera->addAnimator(result);
        result->drop();
        return result;
    }

    bool JWSceneNodeAnimatorCameraFPS::hasFinished(void)
    {
        return m_Wrapped->hasFinished();
    }

    ESCENE_NODE_ANIMATOR_TYPE JWSceneNodeAnimatorCameraFPS::getType() const
    {
    	return m_Wrapped->getType();
    }

}
}