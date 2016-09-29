#ifndef UTILS_SHADER_H
#define UTILS_SHADER_H

#include <vector>

#if defined(__ANDROID__) || defined(ANDROID)
#include <android/asset_manager.h>
#include <pthread.h>
#endif

class Shader {
public:
	static GLuint LoadShader(int type, const char* strFileName);
	static int CreateProgram(std::string strVs, std::string strPs);
	static bool ReadFile(const char* fileName, std::vector<uint8_t>* buffer_ref);
#if defined(__ANDROID__) || defined(ANDROID)
	static AAssetManager* mAssetManager;
#endif
};

#endif//UTILS_SHADER_H
