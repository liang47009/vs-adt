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

#ifndef UTILS_SHADER_H_
#define UTILS_SHADER_H_

//#include <jni.h>

#include <vector>
#include <map>
#include <string>

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#if defined(ANDROID) || defined(__ANDROID__)
#include <android/log.h>
#include <android/asset_manager.h>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "mufeng", __VA_ARGS__))

#endif
//#include <android/log.h>

//#include "JNIHelper.h"

namespace shader {
#if defined(ANDROID) || defined(__ANDROID__)
	static AAssetManager* mAssetManager = NULL;
#endif

/******************************************************************
 * Shader compiler helper
 * namespace: ndkHelper::shader
 *
 */
bool ReadFile(const char* fileName, std::vector<uint8_t>* buffer_ref);
/******************************************************************
 * CompileShader() with vector
 *
 * arguments:
 *  out: shader, shader variable
 *  in: type, shader type (i.e. GL_VERTEX_SHADER/GL_FRAGMENT_SHADER)
 *  in: data, source vector
 * return: true if a shader compilation succeeded, false if it failed
 *
 */
bool CompileShader(GLuint *shader, const GLenum type,
		std::vector<uint8_t>& data);

/******************************************************************
 * CompileShader() with buffer
 *
 * arguments:
 *  out: shader, shader variable
 *  in: type, shader type (i.e. GL_VERTEX_SHADER/GL_FRAGMENT_SHADER)
 *  in: source, source buffer
 *  in: iSize, buffer size
 * return: true if a shader compilation succeeded, false if it failed
 *
 */
bool CompileShader(GLuint *shader, const GLenum type, const GLchar *source,
		const int32_t iSize);

/******************************************************************
 * CompileShader() with filename
 *
 * arguments:
 *  out: shader, shader variable
 *  in: type, shader type (i.e. GL_VERTEX_SHADER/GL_FRAGMENT_SHADER)
 *  in: strFilename, filename
 * return: true if a shader compilation succeeded, false if it failed
 *
 */
bool CompileShader(GLuint *shader, const GLenum type, const char *strFileName);

/******************************************************************
 * CompileShader() with std::map helps patching on a shader on the fly.
 *
 * arguments:
 *  out: shader, shader variable
 *  in: type, shader type (i.e. GL_VERTEX_SHADER/GL_FRAGMENT_SHADER)
 *  in: mapParameters
 *      For a example,
 *      map : %KEY% -> %VALUE% replaces all %KEY% entries in the given shader code to %VALUE"
 * return: true if a shader compilation succeeded, false if it failed
 *
 */
bool CompileShader(GLuint *shader, const GLenum type, const char *str_file_name,
		const std::map<std::string, std::string>& map_parameters);

/******************************************************************
 * LinkProgram()
 *
 * arguments:
 *  in: program, program
 * return: true if a shader linkage succeeded, false if it failed
 *
 */
bool LinkProgram(const GLuint prog);

/******************************************************************
 * validateProgram()
 *
 * arguments:
 *  in: program, program
 * return: true if a shader validation succeeded, false if it failed
 *
 */
bool ValidateProgram(const GLuint prog);
} //namespace shader

#endif// UTILS_SHADER_H_
