/*
 * Application.cpp
 *
 *  Created on: 2016年10月4日
 *      Author: XIAYUNFENG
 */
#include "Application.h"

Ogre::DataStreamPtr Application::openAPKFile(const Ogre::String& fileName) {
	Ogre::DataStreamPtr stream;
	AAsset* asset = AAssetManager_open(gAssetMgr, fileName.c_str(),
			AASSET_MODE_BUFFER);
	if (asset) {
		off_t length = AAsset_getLength(asset);
		void* membuf = OGRE_MALLOC(length, Ogre::MEMCATEGORY_GENERAL);
		memcpy(membuf, AAsset_getBuffer(asset), length);
		AAsset_close(asset);

		stream = Ogre::DataStreamPtr(
				new Ogre::MemoryDataStream(membuf, length, true, true));
	}
	return stream;
}

void Application::setupScene() {
	Ogre::ConfigFile cf;
	cf.load(openAPKFile("resources.cfg"));

	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
	while (seci.hasMoreElements()) {
		Ogre::String sec, type, arch;
		sec = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap* settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;

		for (i = settings->begin(); i != settings->end(); i++) {
			type = i->first;
			arch = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch,
					type, sec);
		}
	}

	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	Ogre::RTShader::ShaderGenerator::initialize();
	Ogre::RTShader::ShaderGenerator::getSingletonPtr()->setTargetLanguage(
			"glsles");
	gMatListener = new Ogre::ShaderGeneratorTechniqueResolverListener();
	Ogre::MaterialManager::getSingleton().addListener(gMatListener);

	gSceneMgr = gRoot->createSceneManager(Ogre::ST_GENERIC);
	Ogre::RTShader::ShaderGenerator::getSingletonPtr()->addSceneManager(
			gSceneMgr);

	Ogre::Camera* camera = gSceneMgr->createCamera("MyCam");
	camera->setNearClipDistance(1.0f);
	camera->setFarClipDistance(100000.0f);
	camera->setPosition(0, 0, 20.0f);
	camera->lookAt(0, 0, 0);
	camera->setAutoAspectRatio(true);

	Ogre::SceneNode* pNode =
			gSceneMgr->getRootSceneNode()->createChildSceneNode();
//	Ogre::Entity* pEntity = gSceneMgr->createEntity("SinbadInstance",
//			"Sinbad.mesh");
//	pNode->attachObject(pEntity);

	Ogre::Light* pDirLight = gSceneMgr->createLight();
	pDirLight->setDirection(Ogre::Vector3(0, -1, 0));
	pDirLight->setType(Ogre::Light::LT_DIRECTIONAL);
	pNode->attachObject(pDirLight);

	Ogre::Viewport* vp = gRenderWnd->addViewport(camera);
	vp->setBackgroundColour(Ogre::ColourValue(0.3, 0.3, 0.3, 0.3));
	vp->setMaterialScheme(Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME);

	Ogre::RTShader::ShaderGenerator::getSingletonPtr()->invalidateScheme(
			Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME);

	// --- Init CEGUI --- //
	Ogre::LogManager::getSingletonPtr()->logMessage(
			"*** Initializing CEGUI ***");
	CEGUI::OgreRenderer* renderer;
	renderer = &CEGUI::OgreRenderer::bootstrapSystem();

	CEGUI::Logger::getSingleton().setLoggingLevel(CEGUI::Informative);

	// setup CEGUI default resource groups
	CEGUI::ImageManager::setImagesetDefaultResourceGroup("General");
	CEGUI::Scheme::setDefaultResourceGroup("General");
	CEGUI::Font::setDefaultResourceGroup("General");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("General");
	CEGUI::WindowManager::setDefaultResourceGroup("General");
	CEGUI::ScriptModule::setDefaultResourceGroup("General");

	// --- Create resources we need --- //
	CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
	CEGUI::SchemeManager::getSingleton().createFromFile("VanillaSkin.scheme");
	CEGUI::SchemeManager::getSingleton().createFromFile("AlfiskoSkin.scheme");
	CEGUI::FontManager::getSingleton().createFromFile("DejaVuSans-12.font");

	// --- Create our GUIContext and set its defaults --- //
	CEGUI::System::getSingleton().createGUIContext(
			renderer->getDefaultRenderTarget());
	CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultFont(
			"DejaVuSans-12");
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage(
			"Vanilla-Images/MouseArrow");
	//CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().show();
	// Only important to bring cursor back from hide()
	CEGUI::Window* ui_root_win =
			CEGUI::WindowManager::getSingleton().loadLayoutFromFile(
					"application_templates.layout");
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(
			ui_root_win);

}

