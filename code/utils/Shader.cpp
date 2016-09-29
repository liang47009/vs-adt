#include <stdlib.h>
#include <iostream>
#include <fstream>

#include <GLES2/gl2.h>

#include "utils/Shader.h"

#if defined(__ANDROID__) || defined(ANDROID)
AAssetManager* Shader::mAssetManager = NULL;
#endif

//---------------------------------------------------------------------------
//readFile
//---------------------------------------------------------------------------
bool Shader::ReadFile(const char* fileName, std::vector<uint8_t>* buffer_ref) {
#if defined(__ANDROID__) || defined(ANDROID)
		if (mAssetManager) {
			//Fallback to assetManager
			AAsset* assetFile = AAssetManager_open(mAssetManager, fileName,
					AASSET_MODE_BUFFER);
			if (!assetFile) {
				//		pthread_mutex_unlock(&mutex_);
				return false;
			}
			uint8_t* data = (uint8_t*) AAsset_getBuffer(assetFile);
			int32_t size = AAsset_getLength(assetFile);
			if (data == NULL) {
				AAsset_close(assetFile);
				//		pthread_mutex_unlock(&mutex_);
				return false;
			}
			buffer_ref->reserve(size);
			buffer_ref->assign(data, data + size);
			AAsset_close(assetFile);
			//	pthread_mutex_unlock(&mutex_);
			return true;
		} else {

			return false;
		}
#elif defined(WIN32)
	std::string temp("../");
	temp.append(fileName);
	FILE* fp = fopen(temp.c_str(), "rb");
	if (fp == NULL)	{
		return false;
	}

	char buffer[1024];
	size_t realRead = fread(buffer, sizeof(char), sizeof(buffer) - 1, fp);
	fclose(fp);

	buffer[realRead] = '\0';
	const char* Buf = buffer;
	buffer_ref->reserve(realRead);
	buffer_ref->assign(Buf, Buf + realRead);
	return true;
#else
	return false;
#endif
}

GLuint Shader::LoadShader(int type, const char* strFileName) {
	GLuint shader = glCreateShader(type);

	std::vector<uint8_t> data;

	bool read = ReadFile(strFileName, &data);

	if (!read) {
		return -1;
	}

	const GLchar *source = (GLchar *) &data[0];

	int32_t iSize = data.size();

	if (source == NULL || iSize <= 0) {
		return -1;
	}
	glShaderSource(shader, 1, &source, &iSize);

	glCompileShader(shader);

	GLint bShaderCompiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &bShaderCompiled);

	if (!bShaderCompiled) {
		int i32InfoLogLength, i32CharsWritten;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &i32InfoLogLength);

		char* pszInfoLog = new char[i32InfoLogLength + 1];
		glGetShaderInfoLog(shader, i32InfoLogLength, &i32CharsWritten,
				pszInfoLog);

		pszInfoLog[i32InfoLogLength] = '\0';
		delete[] pszInfoLog;

		return -1;
	}

	return shader;
}

int Shader::CreateProgram(std::string strVs, std::string strPs) {
	int vertexShader = LoadShader(GL_VERTEX_SHADER, strVs.c_str());
	if (vertexShader == -1) {
		return -1;
	}

	int pixelShader = LoadShader(GL_FRAGMENT_SHADER, strPs.c_str());
	if (pixelShader == -1) {
		return -1;
	}

	int program = glCreateProgram();
	if (program != 0) {
		glAttachShader(program, vertexShader);
		glAttachShader(program, pixelShader);

		glBindAttribLocation(program, 0, "iPos");
		glBindAttribLocation(program, 1, "iColor");
		glBindAttribLocation(program, 2, "iTexCoord");

		int err = glGetError();
		printf("%d", err);
		glLinkProgram(program);
		err = glGetError();
		printf("%d", err);
	}

	int linkStatus;
	glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
	if (linkStatus != GL_TRUE) {
		glDeleteProgram(program);
		program = 0;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(pixelShader);

	return program;
}
