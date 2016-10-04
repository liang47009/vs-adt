/*
 * Application.h
 *
 *  Created on: 2016年10月4日
 *      Author: XIAYUNFENG
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <android/asset_manager.h>

#include <Ogre.h>

#include <CEGUI/CEGUI.h>
#include <CEGUI/System.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

#include "RTShaderHelper.h"

class Application {
public:
	Ogre::Root* gRoot;
	AAssetManager* gAssetMgr;
	Ogre::RenderWindow* gRenderWnd;

	void setupScene();
	Ogre::DataStreamPtr openAPKFile(const Ogre::String& fileName);
private:
	Ogre::SceneManager* gSceneMgr = NULL;
	Ogre::ShaderGeneratorTechniqueResolverListener* gMatListener = NULL;
};

#endif /* APPLICATION_H_ */
