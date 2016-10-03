#
#             QUALCOMM, Advanced Content Group - Snapdragon SDK
#
#                Copyright (c) 2013 QUALCOMM Technologies, Inc. 
#                            All Rights Reserved. 
#                         QUALCOMM Proprietary/GTDR
#

LOCAL_PATH := $(call my-dir)

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
	LOCAL_CFLAGS := -g $(LOCAL_C_INCLUDES:%=-I%) -DHALTI -D_OGLES3 -DUSE_PTHREADS -DUSE_GLES3_WRAPPER
	LOCAL_CFLAGS += -pthread -DSCE_PFX_USE_SIMD_VECTORMATH -DOS_ANDROID
	LOCAL_CFLAGS += -ffast-math -funsafe-math-optimizations -fno-strict-aliasing
#	LOCAL_CFLAGS += -mfpu=neon -mfloat-abi=softfp 
else
	# VFP mode
	LOCAL_CFLAGS := $(LOCAL_C_INCLUDES:%=-I%) -DUSE_PTHREADS -pthread -DOS_ANDROID
	LOCAL_CFLAGS += -mfpu=vfp -mfloat-abi=softfp
endif

LOCAL_CFLAGS += -DCORE_GL_CONTEXT

LOCAL_MODULE := app

LOCAL_SRC_FILES := $(MY_CPP_LIST:$(LOCAL_PATH)/%=%)

LOCAL_C_INCLUDES := $(LOCAL_PATH) $(LOCAL_PATH)/Framework $(LOCAL_PATH)/Framework/Android

LOCAL_LDLIBS := -llog -landroid -lEGL -lGLESv3

LOCAL_CFLAGS += -Wno-psabi -Wno-conversion-null -Wno-write-strings
#-Wcast-align

LOCAL_STATIC_LIBRARIES := android_native_app_glue

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)
