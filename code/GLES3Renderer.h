#ifndef TEST_DEMO_H
#define TEST_DEMO_H

#include <egl/egl.h>
#include <GLES2/gl2.h>
//#include <GLES3/gl3.h>
#include "tool.h"
#include "utils/Shader.h"
#include "utils/math.h"
#include "Texture.h"

class GLES3Renderer {
public:
	void InitVertex(Vertex* p);
	bool Init(unsigned long width, unsigned long height);
	void Render();
	GLuint gProgram;
	GLuint gPositionLoc;
	GLuint gTexCoordLoc;
	GLuint gSamplerLoc;
	GLuint gTexture;
};

#endif // !TEST_DEMO_H
