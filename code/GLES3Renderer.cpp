#include "GLES3Renderer.h"

#define MAX_LOADSTRING 100
#define VPOSITION 0
#define VCOLOR 1
#define VTEXCOORD 2

unsigned int nProgramHandler;

unsigned int vao[1];
unsigned int ibo[1];
unsigned int vbo[1];

static const unsigned short vertex_indices[] = { 0, 1, 2, 2, 0, 3 };

static float uWVPMatrix[16] = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, };

static Vertex* pVertex = new Vertex[4];

void GLES3Renderer::InitVertex(Vertex* p) {
	p[0].position = FmVec4(-1.0f, -1.0f, 0.0f, 1.0f);
	p[0].color = FmVec4(1.0f, 1.0f, 1.0f, 1.0f);

	p[1].position = FmVec4(1.0f, -1.0f, 0.0f, 1.0f);
	p[1].color = FmVec4(1.0f, 1.0f, 0.0f, 1.0f);

	p[2].position = FmVec4(1.0f, 1.0f, 0.0f, 1.0f);
	p[2].color = FmVec4(1.0f, 0.0f, 1.0f, 1.0f);

	p[3].position = FmVec4(-1.0f, 1.0f, 0.0f, 1.0f);
	p[3].color = FmVec4(0.0f, 1.0f, 1.0f, 1.0f);
}

bool GLES3Renderer::Init() {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	nProgramHandler = Shader::CreateProgram("res/scripts/test.vsh",
			"res/scripts/test.fsh");

	InitVertex(pVertex);

	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);

	glGenBuffers(1, ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertex_indices),
			vertex_indices, GL_STATIC_DRAW);

	glGenBuffers(1, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 4, NULL, GL_DYNAMIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * 4, pVertex);

	glUseProgram(nProgramHandler);

	//LoadTexture("..\\Resource\\aaa.jpg");

	return true;
}

void GLES3Renderer::Render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(vao[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

// 	int fColor = glGetUniformLocation(nProgramHandler,"sTexture");
// 	int fColor1 = glGetUniformLocation(nProgramHandler,"sTexture1");

	int mat = glGetUniformLocation(nProgramHandler, "uWVPMatrix");
	glUniformMatrix4fv(mat, 1, GL_FALSE, uWVPMatrix);

// 	glUniform1i(0,fColor);
// 	glActiveTexture(GL_TEXTURE0);
// 	glBindTexture(GL_TEXTURE_2D,1);

	glVertexAttribPointer(VPOSITION, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(VCOLOR, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
			(void*) (4 * sizeof(float)));
	//glVertexAttribPointer(VTEXCOORD,2,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)(8 * sizeof(float)));

	glEnableVertexAttribArray(VPOSITION);
	glEnableVertexAttribArray(VCOLOR);
	//glEnableVertexAttribArray(VTEXCOORD); 

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, NULL);
}

#if defined(ANDROID) || defined(__ANDROID__)
void GLES3Renderer::setAAssetManager(AAssetManager* assetMgr) {
	this->assetMgr = assetMgr;
}
#endif// android