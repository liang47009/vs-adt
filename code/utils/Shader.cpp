/*
 * Copyright 2013 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <EGL/egl.h>
#include <GLES2/gl2.h>

#include "shader.h"
//#include "JNIHelper.h"
#define CEGUI_NEW_PT(T, Allocator) new T
#define CEGUI_NEW_ARRAY_PT(T, count, Allocator) new T[count]
#define CEGUI_DELETE_PT(ptr, T, Allocator) delete ptr
#define CEGUI_DELETE_ARRAY_PT(ptr, T, count, Allocator) delete [] ptr

//---------------------------------------------------------------------------
//readFile
//---------------------------------------------------------------------------
bool shader::ReadFile(const char* fileName, std::vector<uint8_t>* buffer_ref) {
#if defined(__ANDROID__) || defined(ANDROID)
	if (shader::mAssetManager) {
		//Fallback to assetManager
		AAsset* assetFile = AAssetManager_open(shader::mAssetManager, fileName,
				AASSET_MODE_BUFFER);
		if (!assetFile) {
			LOGI("file not exist: %s", fileName);
			//		pthread_mutex_unlock(&mutex_);
			return false;
		}
		int32_t size = AAsset_getLength(assetFile);

		unsigned char* const buffer =
				CEGUI_NEW_ARRAY_PT(unsigned char, size, RawDataContainer);
		int size_read = AAsset_read(assetFile, buffer, size);
		if (size_read != size) {
			CEGUI_DELETE_ARRAY_PT(buffer, unsigned char, size, BufferAllocator);
			LOGI("size_read: %d, size:%d", size_read, size);
			return false;
		}
		if (buffer == NULL) {
			AAsset_close(assetFile);
			LOGI("no data found: %s", fileName);
			//		pthread_mutex_unlock(&mutex_);
			return false;
		} else {
			LOGI("data buffer: %s", fileName);
		}
		buffer_ref->reserve(size);
		buffer_ref->assign(buffer, buffer + size);
		AAsset_close(assetFile);
		//	pthread_mutex_unlock(&mutex_);
		return true;
	} else {
		LOGI("mAssetManager not found!");
		return false;
	}
#elif defined(WIN32)
	std::string temp("../");
	temp.append(fileName);
	FILE* fp = fopen(temp.c_str(), "rb");
	if (fp == NULL) {
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

bool shader::CompileShader(GLuint *shader, const GLenum type,
		const char *str_file_name,
		const std::map<std::string, std::string>& map_parameters) {
	std::vector<uint8_t> data;
	if (!ReadFile(str_file_name, &data)) {
		LOGI("Can not open a file:%s", str_file_name);
		return false;
	}

	const char REPLACEMENT_TAG = '*';
	//Fill-in parameters
	std::string str(data.begin(), data.end());
	std::string str_replacement_map(data.size(), ' ');

	std::map<std::string, std::string>::const_iterator it =
			map_parameters.begin();
	std::map<std::string, std::string>::const_iterator itEnd =
			map_parameters.end();
	while (it != itEnd) {
		size_t pos = 0;
		while ((pos = str.find(it->first, pos)) != std::string::npos) {
			//Check if the sub string is already touched

			size_t replaced_pos = str_replacement_map.find(REPLACEMENT_TAG,
					pos);
			if (replaced_pos == std::string::npos || replaced_pos > pos) {

				str.replace(pos, it->first.length(), it->second);
				str_replacement_map.replace(pos, it->first.length(),
						it->first.length(), REPLACEMENT_TAG);
				pos += it->second.length();
			} else {
				//The replacement target has been touched by other tag, skipping them
				pos += it->second.length();
			}
		}
		it++;
	}

	LOGI("Patched Shdader:\n%s", str.c_str());
	std::vector<uint8_t> v(str.begin(), str.end());
	str.clear();
	return shader::CompileShader(shader, type, v);
}

bool shader::CompileShader(GLuint *shader, const GLenum type,
		const GLchar *source, const int32_t iSize) {
	if (source == NULL || iSize <= 0)
		return false;

	*shader = glCreateShader(type);
	glShaderSource(*shader, 1, &source, &iSize); //Not specifying 3rd parameter (size) could be troublesome..

	glCompileShader(*shader);

#if defined(DEBUG)
	GLint logLength;
	glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0) {
		GLchar *log = (GLchar *) malloc(logLength);
		glGetShaderInfoLog(*shader, logLength, &logLength, log);
//		LOGI("Shader compile log:\n%s", log);
		free(log);
	}
#endif

	GLint status;
	glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);
	if (status == 0) {
		glDeleteShader(*shader);
		return false;
	}

	return true;
}

bool shader::CompileShader(GLuint *shader, const GLenum type,
		std::vector<uint8_t>& data) {
	if (!data.size())
		return false;

	const GLchar *source = (GLchar *) &data[0];
	int32_t iSize = data.size();
	return shader::CompileShader(shader, type, source, iSize);
}

bool shader::CompileShader(GLuint *shader, const GLenum type,
		const char *strFileName) {
	std::vector<uint8_t> data;
	bool b = ReadFile(strFileName, &data);
	if (!b) {
		LOGI("Can not open a file:%s", strFileName);
		return false;
	}

	return shader::CompileShader(shader, type, data);
}

bool shader::LinkProgram(const GLuint prog) {
	GLint status;

	glLinkProgram(prog);

#if defined(DEBUG)
	GLint logLength;
	glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0) {
		GLchar *log = (GLchar *) malloc(logLength);
		glGetProgramInfoLog(prog, logLength, &logLength, log);
//		LOGI("Program link log:\n%s", log);
		free(log);
	}
#endif

	glGetProgramiv(prog, GL_LINK_STATUS, &status);
	if (status == 0) {
//		LOGI("Program link failed\n");
		return false;
	}

	return true;
}

bool shader::ValidateProgram(const GLuint prog) {
	GLint logLength, status;

	glValidateProgram(prog);
	glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0) {
		GLchar *log = (GLchar *) malloc(logLength);
		glGetProgramInfoLog(prog, logLength, &logLength, log);
//		LOGI("Program validate log:\n%s", log);
		free(log);
	}

	glGetProgramiv(prog, GL_VALIDATE_STATUS, &status);
	if (status == 0)
		return false;

	return true;
}
