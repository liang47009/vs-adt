#define OGRE_STATIC_GLES2
#define OGRE_STATIC_ParticleFX
#define OGRE_STATIC_OctreeSceneManager
#include "OgreStaticPluginLoader.h"

#include <EGL/egl.h>
#include <android/log.h>
#include <android_native_app_glue.h>

#include "Ogre.h"
#include "OgreRenderWindow.h"
#include "OgreStringConverter.h"
#include "Android/OgreAndroidEGLWindow.h"
#include "Android/OgreAPKFileSystemArchive.h"
#include "Android/OgreAPKZipArchive.h"
#include "Application.h"

static Ogre::Root* gRoot = NULL;
static AAssetManager* gAssetMgr = NULL;
static Ogre::RenderWindow* gRenderWnd = NULL;
static Ogre::StaticPluginLoader* gStaticPluginLoader = NULL;
//static Ogre::SceneManager* gSceneMgr = NULL;
//static Ogre::ShaderGeneratorTechniqueResolverListener* gMatListener = NULL;

static int32_t handleInput(struct android_app* app, AInputEvent* event) {
	return 1;
}

static void handleCmd(struct android_app* app, int32_t cmd) {
	switch (cmd) {
	case APP_CMD_SAVE_STATE:
		break;
	case APP_CMD_INIT_WINDOW:
		if (app->window && gRoot) {
			AConfiguration* config = AConfiguration_new();
			AConfiguration_fromAssetManager(config,
					app->activity->assetManager);
			gAssetMgr = app->activity->assetManager;

			if (!gRenderWnd) {
				Ogre::ArchiveManager::getSingleton().addArchiveFactory(
						new Ogre::APKFileSystemArchiveFactory(
								app->activity->assetManager));
				Ogre::ArchiveManager::getSingleton().addArchiveFactory(
						new Ogre::APKZipArchiveFactory(
								app->activity->assetManager));

				Ogre::NameValuePairList opt;
				opt["externalWindowHandle"] = Ogre::StringConverter::toString(
						(int) app->window);
				opt["androidConfig"] = Ogre::StringConverter::toString(
						(int) config);

				gRenderWnd = gRoot->createRenderWindow("OgreWindow", 0, 0,
						false, &opt);

				Application app;
				app.gRoot = gRoot;
				app.gAssetMgr = gAssetMgr;
				app.gRenderWnd = gRenderWnd;
				app.setupScene();
			} else {
				static_cast<Ogre::AndroidEGLWindow*>(gRenderWnd)->_createInternalResources(
						app->window, config);
			}
			AConfiguration_delete(config);
		}
		break;
	case APP_CMD_TERM_WINDOW:
		if (gRoot && gRenderWnd)
			static_cast<Ogre::AndroidEGLWindow*>(gRenderWnd)->_destroyInternalResources();
		break;
	case APP_CMD_GAINED_FOCUS:
		break;
	case APP_CMD_LOST_FOCUS:
		break;
	}
}

void android_main(struct android_app* state) {
	app_dummy();

	if (gRoot == NULL) {
		gRoot = new Ogre::Root();
#ifdef OGRE_STATIC_LIB
		gStaticPluginLoader = new Ogre::StaticPluginLoader();
		gStaticPluginLoader->load();
#endif
		gRoot->setRenderSystem(gRoot->getAvailableRenderers().at(0));
		gRoot->initialise(false);
	}

	state->onAppCmd = &handleCmd;
	state->onInputEvent = &handleInput;

	int ident, events;
	struct android_poll_source* source;

	while (true) {
		while ((ident = ALooper_pollAll(0, NULL, &events, (void**) &source))
				>= 0) {
			if (source != NULL)
				source->process(state, source);

			if (state->destroyRequested != 0)
				return;
		}

		if (gRenderWnd != NULL && gRenderWnd->isActive()) {
			gRenderWnd->windowMovedOrResized();
			gRoot->renderOneFrame();
		}
	}
}
