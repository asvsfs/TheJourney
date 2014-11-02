/*
-----------------------------------------------------------------------------
Filename:    BasicTutorial2.h
-----------------------------------------------------------------------------
 
This source file is part of the
   ___                 __    __ _ _    _ 
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/                              
	  Tutorial Framework
	  http://www.ogre3d.org/tikiwiki/
-----------------------------------------------------------------------------
*/
#ifndef __BasicTutorial2_h_
#define __BasicTutorial2_h_
#include "stdafx.h"
#include "BaseApplication.h"
 #include "Singleton.h"
class BasicTutorial2 : public BaseApplication , public CSingleton<BasicTutorial2>
{
public:
	BasicTutorial2(void);
	virtual ~BasicTutorial2(void);
 
protected:
	virtual void createScene(void);
	virtual void createCamera(void);
	virtual void createViewports(void);

	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

	void createColourCube();
	Ogre::ManualObject* createCubeMesh (Ogre::String name, Ogre::String matName) ;
};
 
#endif // #ifndef __BasicTutorial2_h_