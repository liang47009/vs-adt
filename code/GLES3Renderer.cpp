#include "GLES3Renderer.h"

GLuint CreateSimpleTexture2D() {
	// Use tightly packed data
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Generate a texture object
	GLuint texture;
	glGenTextures(1, &texture);

	// Bind the texture object
	glBindTexture(GL_TEXTURE_2D, texture);

	// Load the texture: 2x2 Image, 3 bytes per pixel (R, G, B)
	const size_t width = 2;
	const size_t height = 2;
	GLubyte pixels[width * height * 3] = { 255, 0, 0, // Red
		0, 255, 0, // Green
		0, 0, 255, // Blue
		255, 255, 0, // Yellow
	};
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, pixels);
	// Set the filtering mode
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	return texture;
}

bool GLES3Renderer::Init(unsigned long width, unsigned long height) {
	GLuint vert_shader, frag_shader;
	//	char *vert_shader_pathname, *frag_shader_pathname;
	const char* strVsh = "res/scripts/test.vsh";
	const char* strFsh = "res/scripts/test.fsh";

	// Create shader program
	gProgram = glCreateProgram();
	// Create and compile vertex shader
	if (!shader::CompileShader(&vert_shader, GL_VERTEX_SHADER,
		strVsh)) {
		glDeleteProgram(gProgram);
		return false;
	}

	// Create and compile fragment shader
	if (!shader::CompileShader(&frag_shader, GL_FRAGMENT_SHADER,
		strFsh)) {
		glDeleteProgram(gProgram);
		return false;
	}

	// Attach vertex shader to program
	glAttachShader(gProgram, vert_shader);

	// Attach fragment shader to program
	glAttachShader(gProgram, frag_shader);

	if (!shader::LinkProgram(gProgram)) {
		LOGI("link error!");
		return;
	}
	// Use the program object
	glUseProgram(gProgram);

	// Get the attribute locations
	gPositionLoc = glGetAttribLocation(gProgram, "a_position");
	gTexCoordLoc = glGetAttribLocation(gProgram, "a_texCoord");
	// Get the sampler location
	gSamplerLoc = glGetUniformLocation(gProgram, "s_texture");
	// Load the texture
	gTexture = CreateSimpleTexture2D();
	//	gTexture = CreateSimpleTexture2D(gAssetMgr, "texture/brick.png");

	glClearColor(0.3f, 0.3f, 0.3f, 0.3f);
	// Set the viewport
	glViewport(0, 0, width, height);
	return true;
}

GLfloat vertices[] = { 
	-0.5f, 0.5f, 0.0f, // Position 0
	0.0f, 0.0f, // TexCoord 0
	-0.5f, -0.5f, 0.0f, // Position 1
	0.0f, 1.0f, // TexCoord 1
	0.5f, -0.5f, 0.0f, // Position 2
	1.0f, 1.0f, // TexCoord 2
	0.5f, 0.5f, 0.0f, // Position 3
	1.0f, 0.0f // TexCoord 3
};

GLushort indices[] = { 0, 1, 2, 0, 2, 3 };

void GLES3Renderer::Render() {

	// Clear the color buffer
	glClear(GL_COLOR_BUFFER_BIT);

	// Load the vertex position
	glVertexAttribPointer(gPositionLoc, 3, GL_FLOAT, GL_FALSE,
		5 * sizeof(GLfloat), vertices);
	// Load the texture coordinate
	glVertexAttribPointer(gTexCoordLoc, 2, GL_FLOAT, GL_FALSE,
		5 * sizeof(GLfloat), vertices + 3);

	glEnableVertexAttribArray(gPositionLoc);
	glEnableVertexAttribArray(gTexCoordLoc);

	// Bind the texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gTexture);

	// Set the texture sampler to texture unit to 0
	glUniform1i(gSamplerLoc, 0);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
}

