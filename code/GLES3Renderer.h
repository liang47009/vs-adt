#ifndef TEST_DEMO_H
#define TEST_DEMO_H

#include <egl/egl.h>
//#include <GLES2/gl2.h>
#include <GLES3/gl3.h>
#include "tool.h"
#include "utils/Shader.h"
#include "utils/math.h"
#include "Texture.h"
#if defined(ANDROID) || defined(__ANDROID__)
#include <android/asset_manager.h>
#endif// android

class GLES3Renderer
{
public:
	void InitVertex(Vertex* p);
	bool Init();
	void Render();

#if defined(ANDROID) || defined(__ANDROID__)
	void setAAssetManager(AAssetManager* assetMgr);

	AAssetManager* assetMgr;
#endif// android
};

#endif // !TEST_DEMO_H
