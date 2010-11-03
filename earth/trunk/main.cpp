/** Example 003 Custom SceneNode

 This Tutorial is more advanced than the previous ones.
 If you are currently just playing around with the Irrlicht
 engine, you may want to look at other examples first.
 This tutorials shows how to create a custom scene node and
 how to use it in the engine. A custom scene node is needed
 if you want to implement a render technique the Irrlicht
 Engine currently does not support. For example, you can write
 an indoor portal based renderer or an advanced terrain scene
 node with it. By creating custom scene nodes, you can
 easily extend the Irrlicht Engine and adapt it to your own
 needs.

 I will keep the tutorial simple: Keep everything very
 short, everything in one .cpp file, and I'll use the engine
 here as in all other tutorials.

 To start, I include the header files, use the irr namespace,
 and tell the linker to link with the .lib file.
 */
#include <irrlicht.h>
//#include "driverChoice.h"
#include "EarthVisualization.h"
#include "irrlitch/JWSceneNodeAnimatorCameraFPS.h"

using namespace core;
using namespace irr;
using namespace irr::scene;
using namespace gui;

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

enum
{
	GUI_ID_TRANSPARENCY_SCROLL_BAR = 101
};

#define GUI_X 5
#define GUI_Y 5

IrrlichtDevice *g_Device;
JWSceneNodeAnimatorCameraFPS* g_CameraAnimator;

class MyEventReceiver: public IEventReceiver
{
public:
	virtual bool OnEvent(const SEvent& event)
	{
		// Escape swaps Camera Input
		if (event.EventType == EET_KEY_INPUT_EVENT
				&& event.KeyInput.PressedDown == false)
		{
			if (event.KeyInput.Key == irr::KEY_ESCAPE)
			{
				if (g_Device)
				{
					scene::ICameraSceneNode * camera =
							g_Device->getSceneManager()->getActiveCamera();
					if (camera)
					{
						camera->setInputReceiverEnabled(
								!camera->isInputReceiverEnabled());
					}
					return true;
				}
			}
		}
		else if (event.EventType == EET_GUI_EVENT)
		{
			s32 id = event.GUIEvent.Caller->getID();
			//IGUIEnvironment* env = g_Device->getGUIEnvironment();
			switch (event.GUIEvent.EventType)
			{
			case EGET_SCROLL_BAR_CHANGED:
				if (id == GUI_ID_TRANSPARENCY_SCROLL_BAR)
				{
					const s32 pos =
							((IGUIScrollBar*) event.GUIEvent.Caller)->getPos();
					g_CameraAnimator->setMoveSpeed(pos / 10000.0);
				}
				break;
			default:
				break;
			}

		}
		else if (event.EventType == EET_USER_EVENT)
		{
			//event.UserEvent.UserData1
			int a = 1;
		}

		return false;
	}
};

/*
 That's it. The Scene node is done. Now we simply have to start
 the engine, create the scene node and a camera, and look at the result.
 */
int main()
{
	// ask user for driver
	video::E_DRIVER_TYPE driverType = video::EDT_OPENGL; //FIXME: hardcoded driverChoiceConsole();
	if (driverType == video::EDT_COUNT)
		return 1;

	// create device

	MyEventReceiver receiver;

	g_Device = createDevice(driverType, core::dimension2d<u32>(640, 480), 16,
			false, false, false, &receiver);

	if (g_Device == 0)
		return 1; // could not create selected driver.

	// create engine and camera

	g_Device->setWindowCaption(L"Custom Scene Node - Irrlicht Engine Demo");

	video::IVideoDriver* driver = g_Device->getVideoDriver();
	scene::ISceneManager* smgr = g_Device->getSceneManager();

	IGUIEnvironment* env = g_Device->getGUIEnvironment();

	IGUISkin* skin = env->getSkin();
	IGUIFont* font = env->getFont("../../media/fonthaettenschweiler.bmp");
	if (font)
		skin->setFont(font);

	skin->setFont(env->getBuiltInFont(), EGDF_TOOLTIP);

	env->addStaticText(L"Movement speed:", rect<s32> (GUI_X, GUI_Y,
			GUI_X + 200, GUI_Y + 20), true);
	IGUIScrollBar* scrollbar = env->addScrollBar(true, rect<s32> (GUI_X, GUI_Y
			+ 25, GUI_X + 200, GUI_Y + 45), 0, GUI_ID_TRANSPARENCY_SCROLL_BAR);
	scrollbar->setMax(500);
	scrollbar->setMin(1);

	scrollbar->setPos(255);

	// add a camera scene node
	scene::ICameraSceneNode* camera = smgr->addCameraSceneNodeFPS();
	//scene::ICameraSceneNode* camera = addCameraSceneNodeFPS(smgr);

	g_CameraAnimator = JWSceneNodeAnimatorCameraFPS::injectOnFPSCamera(camera);
	g_CameraAnimator->setMoveSpeed(scrollbar->getPos() / 5000.0);

	SKeyMap keyMap[] =
	{
	{ EKA_MOVE_FORWARD, KEY_KEY_W },
	{ EKA_MOVE_BACKWARD, KEY_KEY_S },
	{ EKA_STRAFE_LEFT, KEY_KEY_A },
	{ EKA_STRAFE_RIGHT, KEY_KEY_D },
	{ EKA_JUMP_UP, KEY_SPACE },
	{ EKA_CROUCH, KEY_LSHIFT }, };
	g_CameraAnimator->setKeyMap(keyMap, 6);

	camera->setFarValue(20000.f);
	camera->setPosition(core::vector3df(0, 0, -200));
	camera->setTarget(core::vector3df(0, 30, 0));

	//camera->setFarValue(20000.f);

	//camera->setPosition(core::vector3df(0,0,-200));

	// Maya cameras reposition themselves relative to their target, so target the location
	// where the mesh scene node is placed.
	//camera->setTarget(core::vector3df(0, 0, 0));

	//smgr->addCameraSceneNode(0, core::vector3df(0,-40,0), core::vector3df(0,0,0));

	/*
	 Create our scene node. I don't check the result of calling new, as it
	 should throw an exception rather than returning 0 on failure. Because
	 the new node will create itself with a reference count of 1, and then
	 will have another reference added by its parent scene node when it is
	 added to the scene, I need to drop my reference to it. Best practice is
	 to drop it only *after* I have finished using it, regardless of what
	 the reference count of the object is after creation.
	 */
	EarthVisualization *myNode = new EarthVisualization(
			smgr->getRootSceneNode(), smgr, 666);

	/*
	 To animate something in this boring scene consisting only of one
	 tetraeder, and to show that you now can use your scene node like any
	 other scene node in the engine, we add an animator to the scene node,
	 which rotates the node a little bit.
	 irr::scene::ISceneManager::createRotationAnimator() could return 0, so
	 should be checked.
	 */
	scene::ISceneNodeAnimator* anim = 0;
	//smgr->createRotationAnimator(core::vector3df(0.8f, 0, 0.8f));


	if (anim)
	{
		myNode->addAnimator(anim);

		/*
		 I'm done referring to anim, so must
		 irr::IReferenceCounted::drop() this reference now because it
		 was produced by a createFoo() function. As I shouldn't refer to
		 it again, ensure that I can't by setting to 0.
		 */
		anim->drop();
		anim = 0;
	}

	/*
	 I'm done with my CSampleSceneNode object, and so must drop my reference.
	 This won't delete the object, yet, because it is still attached to the
	 scene graph, which prevents the deletion until the graph is deleted or the
	 custom scene node is removed from it.
	 */
	myNode->drop();
	myNode = 0; // As I shouldn't refer to it again, ensure that I can't

	/*
	 Now draw everything and finish.
	 */
	u32 frames = 0;
	while (g_Device->run())
	{
		driver->beginScene(true, true, video::SColor(0, 100, 100, 100));

		smgr->drawAll();

		env->drawAll();

		driver->endScene();
		if (++frames == 100)
		{
			core::stringw str = L"Irrlicht Engine [";
			str += driver->getName();
			str += L"] FPS: ";
			str += (s32) driver->getFPS();

			g_Device->setWindowCaption(str.c_str());
			frames = 0;
		}
	}

	g_Device->drop();

	return 0;
}

/*
 That's it. Compile and play around with the program.
 **/
