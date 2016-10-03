APP_ABI := armeabi-v7a x86
NDK_TOOLCHAIN_VERSION := 4.8
APP_STL		:= gnustl_static
APP_CFLAGS	:= -Wno-error=format-security 
APP_CFLAGS	+= -D__ANDROID__ -DANDROID -DDEBUG -DUSE_NDK_PROFILER
APP_CPPFLAGS := -Wall -Wextra -fexceptions -frtti -fpermissive -std=c++11
APP_PLATFORM := android-21
