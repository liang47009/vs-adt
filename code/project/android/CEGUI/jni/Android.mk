#
#             QUALCOMM, Advanced Content Group - Snapdragon SDK
#
#                Copyright (c) 2013 QUALCOMM Technologies, Inc. 
#                            All Rights Reserved. 
#                         QUALCOMM Proprietary/GTDR
#

LOCAL_PATH := $(call my-dir)

PREBUILD_LIB_PATH := $(LOCAL_PATH)/../deps/lib/$(TARGET_ARCH_ABI)
PREBUILD_INC_PATH := $(LOCAL_PATH)/deps/include

#include $(CLEAR_VARS)
#
#LOCAL_MODULE 			:= OgreMainStatic
#LOCAL_EXPORT_C_INCLUDES := $(PREBUILD_INC_PATH)/OGRE
#LOCAL_SRC_FILES 		:= $(PREBUILD_LIB_PATH)/libOgreMainStatic.a
#
#include $(PREBUILT_STATIC_LIBRARY)
#
#include $(CLEAR_VARS)
#
#LOCAL_MODULE 			:= RenderSystem_GLES2Static
#LOCAL_EXPORT_C_INCLUDES := $(PREBUILD_INC_PATH)/OGRE/RenderSystems/GLES2 $(PREBUILD_INC_PATH)/OGRE/RenderSystems/GLES2/ANDROID
#LOCAL_SRC_FILES 		:= $(PREBUILD_LIB_PATH)/OGRE/libRenderSystem_GLES2Static.a
#
#include $(PREBUILT_STATIC_LIBRARY)
#
#include $(CLEAR_VARS)
#
#LOCAL_MODULE 			:= OIS
#LOCAL_EXPORT_C_INCLUDES := $(PREBUILD_INC_PATH)/OIS
#LOCAL_SRC_FILES 		:= $(PREBUILD_LIB_PATH)/libOIS.a
#
#include $(PREBUILT_STATIC_LIBRARY)
#
#include $(CLEAR_VARS)
#
#LOCAL_MODULE 			:= freetype
#LOCAL_EXPORT_C_INCLUDES := $(PREBUILD_INC_PATH)/freetype
#LOCAL_SRC_FILES 		:= $(PREBUILD_LIB_PATH)/libfreetype.a
#
#include $(PREBUILT_STATIC_LIBRARY)

#include $(CLEAR_VARS)
#
#LOCAL_MODULE 			:= freeimage
#LOCAL_EXPORT_C_INCLUDES := $(PREBUILD_INC_PATH)
#LOCAL_SRC_FILES 		:= $(PREBUILD_LIB_PATH)/libfreeimage.a
#
#include $(PREBUILT_STATIC_LIBRARY)

#include $(CLEAR_VARS)
#
#LOCAL_MODULE 			:= zlib
#LOCAL_EXPORT_C_INCLUDES := $(PREBUILD_INC_PATH)
#LOCAL_SRC_FILES 		:= $(PREBUILD_LIB_PATH)/libzlib.a
#
#include $(PREBUILT_STATIC_LIBRARY)
#
#include $(CLEAR_VARS)
#
#LOCAL_MODULE 			:= zzip
#LOCAL_EXPORT_C_INCLUDES := $(PREBUILD_INC_PATH)/zzip
#LOCAL_SRC_FILES 		:= $(PREBUILD_LIB_PATH)/libzzip.a
#
#include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE 			:= tinyxml
LOCAL_EXPORT_C_INCLUDES := $(PREBUILD_INC_PATH)
LOCAL_SRC_FILES 		:= $(PREBUILD_LIB_PATH)/libtinyxml.a

include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE 			:= pcre
LOCAL_EXPORT_C_INCLUDES := $(PREBUILD_INC_PATH)
LOCAL_SRC_FILES 		:= $(PREBUILD_LIB_PATH)/libpcre.a

include $(PREBUILT_STATIC_LIBRARY)

MY_CPP_LIST := $(wildcard $(LOCAL_PATH)/*.c)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/*/*.c)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/*/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/*/*/*.c)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/*/*/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/*/*/*/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/*/*/*/*/*.cpp)

include $(CLEAR_VARS)

# Use this to enable/disable NEON (disabling switches to VFP mode)
ENABLE_NEON		:= true

ifeq ($(ENABLE_NEON),true)
	# NEON mode
	# Enable or disable NEON. Don't forget to apply, or not apply, -mfpu=neon and -mfloat-abi=softfp
	# flags in addition, e.g., if this is true both of those need to be included in LOCAL_CFLAGS
	# to avoid the possibility that ndk-build will "forget" to add them on some files
	LOCAL_ARM_NEON := true
	TARGET_CFLAGS := $(filter-out -ffpu=vfp,$(TARGET_CFLAGS))
	LOCAL_CFLAGS := -g $(LOCAL_C_INCLUDES:%=-I%) -DHALTI -DUSE_PTHREADS -DUSE_GLES3_WRAPPER
	LOCAL_CFLAGS += -pthread -DSCE_PFX_USE_SIMD_VECTORMATH -DOS_ANDROID
	LOCAL_CFLAGS += -ffast-math -funsafe-math-optimizations -fno-strict-aliasing
#	LOCAL_CFLAGS += -D_OGLES3
#	LOCAL_CFLAGS += -mfpu=neon -mfloat-abi=softfp 
else
	# VFP mode
	LOCAL_CFLAGS := $(LOCAL_C_INCLUDES:%=-I%) -DUSE_PTHREADS -pthread -DOS_ANDROID
	LOCAL_CFLAGS += -mfpu=vfp -mfloat-abi=softfp
endif

#LOCAL_CFLAGS += -DCORE_GL_CONTEXT

LOCAL_MODULE := CEGUI

LOCAL_SRC_FILES := $(MY_CPP_LIST:$(LOCAL_PATH)/%=%)

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
				$(LOCAL_PATH)/Framework \
				$(LOCAL_PATH)/Framework/Android\
				$(LOCAL_PATH)/CEGUI/include 

LOCAL_LDLIBS := -llog -landroid -lEGL -lGLESv2

LOCAL_CFLAGS += -Wno-psabi -Wno-conversion-null -Wno-write-strings
#-Wcast-align

LOCAL_STATIC_LIBRARIES := OgreMain OgreGLES2 OgreRTShaderSystem OctreeSceneManager ParticleFX \
				android_native_app_glue android_support \
				freetype freeimage tinyxml zlib minizip OIS pcre \
				 zzip cpufeatures
#LOCAL_WHOLE_STATIC_LIBRARIES := 
include $(BUILD_SHARED_LIBRARY)

$(call import-module, ogre/minizip)
$(call import-module, ogre/freeimage)
$(call import-module, ogre/freetype)
$(call import-module, ogre/OgreMain)
$(call import-module, ogre/RenderSystems)
$(call import-module, ogre/PlugIns)
$(call import-module, ogre/Components)
$(call import-module, ogre/OIS)
$(call import-module, ogre/zlib)
$(call import-module, ogre/zziplib)
$(call import-module, android/support)
$(call import-module, android/cpufeatures)
$(call import-module, android/native_app_glue)
