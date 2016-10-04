///***********************************************************************
// created:    Feb 27 2016
// author:     Petskull
// *************************************************************************/
//
///***************************************************************************
// *   Copyright (C) 2004 - 2015 Paul D Turner & The CEGUI Development Team
// *
// *   Permission is hereby granted, free of charge, to any person obtaining
// *   a copy of this software and associated documentation files (the
// *   "Software"), to deal in the Software without restriction, including
// *   without limitation the rights to use, copy, modify, merge, publish,
// *   distribute, sublicense, and/or sell copies of the Software, and to
// *   permit persons to whom the Software is furnished to do so, subject to
// *   the following conditions:
// *
// *   The above copyright notice and this permission notice shall be
// *   included in all copies or substantial portions of the Software.
// *
// *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// *   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// *   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// *   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
// *   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// *   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// *   OTHER DEALINGS IN THE SOFTWARE.
// ***************************************************************************/
//
///**************************************************************************
// * The following libs (and corresponding headers) are needed to compile and to link:
// * OgreMain
// * OIS
// * CEGUIBase-0
// * CEGUIOgreRenderer-0
// ***************************************************************************/
//#define OGRE_STATIC_GLES2
//#define OGRE_STATIC_ParticleFX
//#define OGRE_STATIC_OctreeSceneManager
//// Ogre3D 1.10 cloned on 160226 https://bitbucket.org/sinbad/ogre
//#include <Ogre.h>
//#include <OgreAndroidEGLWindow.h>
//#include <OIS.h>
//#include <iostream>
//
//#include <android/log.h>
//
//#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "CEGUI", __VA_ARGS__)
//
//#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
//#include <android/native_window.h>
//#include <android/native_activity.h>
//#include <android_native_app_glue.h>
//#endif
//
//#include "RTShaderHelper.h"
//#ifdef OGRE_STATIC_LIB
//#   include "OgreStaticPluginLoader.h"
//#endif
//
//// CEGUI 0.8.4 cloned on 160226 from https://bitbucket.org/cegui/cegui
//#include <CEGUI/CEGUI.h>
//#include <CEGUI/RendererModules/Ogre/Renderer.h>
//
//#ifdef OGRE_STATIC_LIB
//static Ogre::StaticPluginLoader* mStaticPluginLoader;
//#endif
//static Ogre::ShaderGeneratorTechniqueResolverListener* gMatListener = NULL;
//static Ogre::RenderWindow* mRenderWnd;
//static Ogre::Root* mRoot;
//
//typedef struct { /* For moving data between App and AppListener */
//	android_app* droid_app;
//	Ogre::Root* ogre_root;
//	Ogre::RenderWindow *ogre_win;
//	OIS::ParamList *ois_pl;
//	CEGUI::OgreRenderer *cegui_renderer;
//} AppPak;
//
///* This AppListener class will house all callback from Ogre's rendering and window events, as well as OIS's Keyboard and Mouse events. */
//class AppListener: public Ogre::FrameListener,
//		public Ogre::WindowEventListener,
//		public OIS::KeyListener,
//		public OIS::MouseListener {
//public:
//	AppListener(AppPak *new_app_pak) :
//			keep_running(true) {
//		app_pak = new_app_pak;
//
//		ois_input_man = OIS::InputManager::createInputSystem(*app_pak->ois_pl);
//		ois_kb = static_cast<OIS::Keyboard*>(ois_input_man->createInputObject(
//				OIS::OISKeyboard, true));
//		ois_mouse = static_cast<OIS::Mouse*>(ois_input_man->createInputObject(
//				OIS::OISMouse, true));
//		ois_kb->setEventCallback(this);
//		ois_mouse->setEventCallback(this);
//
//		windowResized(app_pak->ogre_win);
//
//		MAX_BUTTON_NUM = 0;
//	}
//	~AppListener() {
//		OIS::InputManager::destroyInputSystem(ois_input_man);
//	}
//
//	// --- Ogre::FrameListener Callbacks ---------------------------//
//	bool frameRenderingQueued(const Ogre::FrameEvent& evt) {
//		Ogre::WindowEventUtilities::messagePump();
//
//		// For some reason, injectTimePulse(delta_time) currently must be done both
//		// on the GUIContext and also on CEGUI::System itself everytime.
//		CEGUI::System::getSingleton().getDefaultGUIContext().injectTimePulse(
//				(float) evt.timeSinceLastFrame);
//		CEGUI::System::getSingleton().injectTimePulse(
//				(float) evt.timeSinceLastFrame);
//
//		// If our OIS::Keyboard or our OIS::Mouse has been destroyed (say, by closing the window), end the rendering
//		if (ois_kb && ois_mouse) {
//			ois_kb->capture();
//			ois_mouse->capture();
//		} else {
//			return false;
//		}
//
//		//CEGUI::System::getSingleton().renderAllGUIContexts();	// By bootstrapping Ogre directly, we don't have to call this.  Ogre does it automatically.
//
//		return keep_running;	// Return false ends Ogre's rendering
//	}
//
//	// --- OIS::KeyListener and OIS::MouseListener Callbacks -------//
//	bool keyPressed(const OIS::KeyEvent &arg) {
//		CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(
//				(CEGUI::Key::Scan) arg.key);
//		CEGUI::System::getSingleton().getDefaultGUIContext().injectChar(
//				(CEGUI::Key::Scan) arg.text);
//
//		if (arg.key == OIS::KC_ESCAPE) {
//			keep_running = false;
//		}
//		return true;
//	}
//	bool keyReleased(const OIS::KeyEvent &arg) {
//		CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(
//				(CEGUI::Key::Scan) arg.key);
//		return true;
//	}
//	bool mouseMoved(const OIS::MouseEvent &arg) {
//		CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(
//				(float) arg.state.X.rel, (float) arg.state.Y.rel);
//		//CEGUI::System::getSingleton().getDefaultGUIContext().injectMousePosition(200.f, 200.f);	// Another way to control the mouse cursor
//		return true;
//	}
//	bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id) {
//		CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(
//				convertButton(id));
//		return true;
//	}
//	bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id) {
//		CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(
//				convertButton(id));
//		return true;
//	}
//
//	// --- Ogre::WindowEventListener Callbacks ---------------------//
//	void windowResized(Ogre::RenderWindow* rw) {
//		unsigned int width, height, depth;
//		int left, top;
//		app_pak->ogre_win->getMetrics(width, height, depth, left, top);
//
//		const OIS::MouseState &ms = ois_mouse->getMouseState();
//		ms.width = width;
//		ms.height = height;
//
//		CEGUI::System::getSingleton().notifyDisplaySizeChanged(
//				CEGUI::Sizef((float) width, (float) height));
//	}
//	void windowClosed(Ogre::RenderWindow* rw) {
//		if (rw == app_pak->ogre_win) {
//			if (ois_input_man) {
//				ois_input_man->destroyInputObject(ois_mouse);
//				ois_input_man->destroyInputObject(ois_kb);
//				ois_mouse = NULL;
//				ois_kb = NULL;
//
//				OIS::InputManager::destroyInputSystem(ois_input_man);
//				ois_input_man = 0;
//			}
//		}
//	}
//
//	// Convert OIS MouseButton event to CEGUI MouseButton event
//	CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID) {
//		switch (buttonID) {
//		case OIS::MB_Left:
//			return CEGUI::LeftButton;
//		case OIS::MB_Right:
//			return CEGUI::RightButton;
//		case OIS::MB_Middle:
//			return CEGUI::MiddleButton;
//		default:
//			return CEGUI::LeftButton;
//		}
//	}
//
//private:
//	AppPak *app_pak;
//	bool keep_running;
//
//	OIS::InputManager *ois_input_man;
//	OIS::Mouse *ois_mouse;
//	OIS::Keyboard *ois_kb;
//
//	unsigned int MAX_BUTTON_NUM;
//};
//
//class App {
//public:
//	void go(android_app* app) { /* Entry Point Called by main() */
//		Setup(app);
//		CreateGUIContext();
//		CreateGUIRootWindow();
////		app_pak.ogre_root->startRendering();
//	}
//
//	void Shutdown() {
//		// --- Shutdown Ogre, OIS, and CEGUI --- //
//		app_pak.ogre_root->getAutoCreatedWindow()->removeAllViewports();
//		Ogre::WindowEventUtilities::removeWindowEventListener(app_pak.ogre_win,
//				app_listener);
//		app_listener->windowClosed(app_pak.ogre_win);
//		app_pak.ogre_root->removeFrameListener(app_listener);
//		delete app_listener;
//
//		delete app_pak.ogre_root;
//		delete app_pak.ois_pl;
//	}
//
//	void DestroyGUIRootWindow() {
//		CEGUI::WindowManager::getSingleton().destroyWindow(ui_root_win);
//	}
//private:
//	void Setup(android_app* app) { /* Here we set up the basic libs of Ogre, OIS, and CEGUI */
//		// --- Init Ogre --- //
//		app_pak.droid_app = app;
////		app_pak.ogre_root = new Ogre::Root("", "", "Ogre.log");
//		app_pak.ogre_root = Ogre::Root::getSingletonPtr();
//		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
//				"./media", "FileSystem", "General");
//		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
//				"./media/CEGUI/imagesets/", "FileSystem", "imagesets");
//		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
//				"./media/CEGUI/schemes/", "FileSystem", "schemes");
//		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
//				"./media/CEGUI/fonts/", "FileSystem", "fonts");
//		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
//				"./media/CEGUI/looknfeel/", "FileSystem", "looknfeel");
//		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
//				"./media/CEGUI/layouts/", "FileSystem", "layouts");
//		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
//				"./media/CEGUI/lua_scripts/", "FileSystem", "lua_scripts");
//
//#ifdef _DEBUG
//		app_pak.ogre_root->loadPlugin(Ogre::String("RenderSystem_GL_d"));
//		app_pak.ogre_root->loadPlugin(Ogre::String("Plugin_OctreeSceneManager_d"));
//#else
//		app_pak.ogre_root->loadPlugin("RenderSystem_GL");
//		app_pak.ogre_root->loadPlugin("Plugin_OctreeSceneManager");
//#endif
//
//		Ogre::RenderSystem* rs = app_pak.ogre_root->getRenderSystemByName(
//				"OpenGL Rendering Subsystem");
//		if (!(rs->getName() == "OpenGL Rendering Subsystem")) {
//			return;
//		}
////		rs->setConfigOption("Full Screen", "No");
////		rs->setConfigOption("VSync", "No");
////		rs->setConfigOption("Video Mode", "1024 x 768 @ 32-bit");
////		app_pak.ogre_root->setRenderSystem(rs);
//
//		if (mRenderWnd) {
//			app_pak.ogre_win = mRenderWnd;
//		} else {
//			LOGI("mRenderWnd is null!");
//			return;
//		}
//
//		Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
//		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
//
//		//---------[ CEGUI works fine without these, but the black background does not redraw. ]---------//
//		// --- Ogre Scene Manager --- //
//		Ogre::SceneManager *scene_man = app_pak.ogre_root->createSceneManager(
//				"OctreeSceneManager", "DefaultSceneManager");
//
//		Ogre::RTShader::ShaderGenerator::getSingletonPtr()->addSceneManager(
//				scene_man);
//		// --- Camera --- //
//		Ogre::Camera *main_cam = scene_man->createCamera("MainCam");
//		main_cam->setPosition(Ogre::Vector3(40, 20, 80));
//		main_cam->lookAt(Ogre::Vector3(0, 0, 0));
//		main_cam->setNearClipDistance(5);
//
//		// --- Viewport --- //
//		Ogre::Viewport* vp = app_pak.ogre_win->addViewport(main_cam);
//		vp->setBackgroundColour(
//				Ogre::ColourValue(17.f / 255.f, 17.f / 255.f, 17.f / 255.f));
//		vp->setMaterialScheme(
//				Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME);
//		Ogre::RTShader::ShaderGenerator::getSingletonPtr()->invalidateScheme(
//				Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME);
//		main_cam->setAspectRatio(
//				Ogre::Real(vp->getActualWidth())
//						/ Ogre::Real(vp->getActualHeight()));
//		//----------------------------------------------[|]----------------------------------------------//
//
//		// --- Init OIS --- //
//		Ogre::LogManager::getSingletonPtr()->logMessage(
//				"*** Initializing OIS ***");
//		size_t windowHnd = 0;
//		std::ostringstream windowHndStr;
//		app_pak.ogre_win->getCustomAttribute("WINDOW", &windowHnd);
//		windowHndStr << windowHnd;
//		app_pak.ois_pl = new OIS::ParamList();
//		app_pak.ois_pl->insert(
//				std::make_pair(std::string("WINDOW"), windowHndStr.str()));
//
//		// --- Init CEGUI --- //
//		Ogre::LogManager::getSingletonPtr()->logMessage(
//				"*** Initializing CEGUI ***");
//		app_pak.cegui_renderer = &CEGUI::OgreRenderer::bootstrapSystem();
//		CEGUI::System::getSingleton().notifyDisplaySizeChanged(
//				CEGUI::Sizef(1024.f, 768.f));
//		CEGUI::Logger::getSingleton().setLoggingLevel(CEGUI::Informative);
//
//		// setup CEGUI default resource groups
//		CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
//		CEGUI::Scheme::setDefaultResourceGroup("schemes");
//		CEGUI::Font::setDefaultResourceGroup("fonts");
//		CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeel");
//		CEGUI::WindowManager::setDefaultResourceGroup("layouts");
//		CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");
//
//		// --- Init Ogre/OIS Listeners --- //
//		app_listener = new AppListener(&app_pak);
//		app_pak.ogre_root->addFrameListener(app_listener);
//		Ogre::WindowEventUtilities::addWindowEventListener(app_pak.ogre_win,
//				app_listener);
//
//	}
//	void CreateGUIContext() {
//		// --- Create resources we need --- //
//		CEGUI::SchemeManager::getSingleton().createFromFile(
//				"VanillaSkin.scheme");
//		CEGUI::SchemeManager::getSingleton().createFromFile(
//				"AlfiskoSkin.scheme");
//		CEGUI::FontManager::getSingleton().createFromFile("DejaVuSans-12.font");
//
//		// --- Create our GUIContext and set its defaults --- //
//		CEGUI::System::getSingleton().createGUIContext(
//				app_pak.cegui_renderer->getDefaultRenderTarget());
//		CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultFont(
//				"DejaVuSans-12");
//		CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage(
//				"Vanilla-Images/MouseArrow");
//		//CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().show();		// Only important to bring cursor back from hide()
//	}
//	void CreateGUIRootWindow() {
//		ui_root_win = CEGUI::WindowManager::getSingleton().loadLayoutFromFile(
//				"application_templates.layout");
//		CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(
//				ui_root_win);
//	}
//
//	AppPak app_pak;
//	AppListener *app_listener;
//
//	CEGUI::Window *ui_root_win;
//};
//
//static App my_app;
//
////-------------------------------------------------------------------[ Init ]---//
////std::wstring s2ws(const std::string& s){
////	int len;
////	int slength = (int)s.length() + 1;
////	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
////	wchar_t* buf = new wchar_t[len];
////	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
////	std::wstring r(buf);
////	delete[] buf;
////	return r;
////}
//static int32_t handleInput(struct android_app* app, AInputEvent* event) {
//	if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {
//		int action = (int) (AMOTION_EVENT_ACTION_MASK
//				& AMotionEvent_getAction(event));
//		if (action == 0) {
//
//		}
//	} else {
//
//	}
//	return 1;
//}
//
//static void handleCmd(struct android_app* app, int32_t cmd) {
//	switch (cmd) {
//	case APP_CMD_SAVE_STATE:
//		break;
//	case APP_CMD_INIT_WINDOW:
//		if (app->window && mRoot) {
//			AConfiguration* config = AConfiguration_new();
//			AConfiguration_fromAssetManager(config,
//					app->activity->assetManager);
//
//			if (!mRenderWnd) {
//				Ogre::NameValuePairList opt;
//				opt["externalWindowHandle"] = Ogre::StringConverter::toString(
//						reinterpret_cast<size_t>(app->window));
//				opt["androidConfig"] = Ogre::StringConverter::toString(
//						reinterpret_cast<size_t>(config));
//
//				mRenderWnd = Ogre::Root::getSingleton().createRenderWindow(
//						"OgreWindow", 0, 0, false, &opt);
//
//				Ogre::RTShader::ShaderGenerator::initialize();
//				Ogre::RTShader::ShaderGenerator::getSingletonPtr()->setTargetLanguage(
//						"glsles");
//				gMatListener =
//						new Ogre::ShaderGeneratorTechniqueResolverListener();
//				Ogre::MaterialManager::getSingleton().addListener(gMatListener);
//				my_app.go(app);
//
//			} else {
//				static_cast<Ogre::AndroidEGLWindow*>(mRenderWnd)->_createInternalResources(
//						app->window, config);
//			}
//
//			AConfiguration_delete(config);
//		}
//		break;
//	case APP_CMD_TERM_WINDOW:
//		if (mRoot && mRenderWnd)
//			static_cast<Ogre::AndroidEGLWindow*>(mRenderWnd)->_destroyInternalResources();
//		break;
//	case APP_CMD_GAINED_FOCUS:
//		break;
//	case APP_CMD_LOST_FOCUS:
//		break;
//	case APP_CMD_CONFIG_CHANGED:
//		break;
//	}
//}
//
//void android_main(struct android_app* state) {
//	app_dummy();
//
//	if (mRoot == NULL) {
//		mRoot = new Ogre::Root();
//#ifdef OGRE_STATIC_LIB
//		mStaticPluginLoader = new Ogre::StaticPluginLoader();
//		mStaticPluginLoader->load();
//#endif
//		mRoot->setRenderSystem(mRoot->getAvailableRenderers().at(0));
//		mRoot->initialise(false);
//	}
//
//	state->onAppCmd = &handleCmd;
//	state->onInputEvent = &handleInput;
//
//	int ident, events;
//	struct android_poll_source* source;
//
//	while (true) {
//		while ((ident = ALooper_pollAll(0, NULL, &events, (void**) &source))
//				>= 0) {
//			if (source != NULL)
//				source->process(state, source);
//
//			if (state->destroyRequested != 0)
//				return;
//		}
//
//		if (mRenderWnd != NULL && mRenderWnd->isActive()) {
//			mRenderWnd->windowMovedOrResized();
//			mRoot->renderOneFrame();
//		}
//	}
//}
