# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH:= $(call my-dir)

CODE_CPP_PATH := $(LOCAL_PATH)/../../../../../

MY_CPP_LIST := $(wildcard $(CODE_CPP_PATH)/*.c)
MY_CPP_LIST += $(wildcard $(CODE_CPP_PATH)/*.cpp)
MY_CPP_LIST += $(wildcard $(CODE_CPP_PATH)/*/*.c)
MY_CPP_LIST += $(wildcard $(CODE_CPP_PATH)/*/*.cpp)
MY_CPP_LIST += $(wildcard $(CODE_CPP_PATH)/*/*/*.c)
MY_CPP_LIST += $(wildcard $(CODE_CPP_PATH)/*/*/*.cpp)
MY_CPP_LIST += $(wildcard $(CODE_CPP_PATH)/*/*/*/*.cpp)
MY_CPP_LIST += $(wildcard $(CODE_CPP_PATH)/*/*/*/*/*.cpp)

include $(CLEAR_VARS)

LOCAL_MODULE    		:= mufeng

LOCAL_C_INCLUDES 		:= $(CODE_CPP_PATH)code

LOCAL_SRC_FILES 		:= $(MY_CPP_LIST:$(LOCAL_PATH)/%=%)

#LOCAL_CFLAGS 			:= -pg

LOCAL_LDLIBS    		:= -llog -landroid -lm -lz -lEGL -lGLESv2 -lGLESv3 -lGLESv1_CM

LOCAL_STATIC_LIBRARIES 	:= cpufeatures android_native_app_glue 

include $(BUILD_SHARED_LIBRARY)

$(call import-module, android/cpufeatures)
$(call import-module, android/native_app_glue)
#$(call import-module, android-ndk-profiler)
