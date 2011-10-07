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
DEMO_PATH:=demo
GAMETUTOR_PATH:=gametutor

########################################################################################################
include $(CLEAR_VARS)

LOCAL_MODULE     := openal
LOCAL_ARM_MODE   := arm
LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(GAMETUTOR_PATH)/libs/openal \
					$(LOCAL_PATH)/$(GAMETUTOR_PATH)/libs/openal_lib_for_Android_Only/OpenAL32 \
					$(LOCAL_PATH)/$(GAMETUTOR_PATH)/libs/openal_lib_for_Android_Only/OpenAL32/Include

LOCAL_SRC_FILES  := $(GAMETUTOR_PATH)/libs/openal_lib_for_Android_Only/OpenAL32/alAuxEffectSlot.c \
                    $(GAMETUTOR_PATH)/libs/openal_lib_for_Android_Only/OpenAL32/alBuffer.c        \
                    $(GAMETUTOR_PATH)/libs/openal_lib_for_Android_Only/OpenAL32/alDatabuffer.c    \
                    $(GAMETUTOR_PATH)/libs/openal_lib_for_Android_Only/OpenAL32/alEffect.c        \
                    $(GAMETUTOR_PATH)/libs/openal_lib_for_Android_Only/OpenAL32/alError.c         \
                    $(GAMETUTOR_PATH)/libs/openal_lib_for_Android_Only/OpenAL32/alExtension.c     \
                    $(GAMETUTOR_PATH)/libs/openal_lib_for_Android_Only/OpenAL32/alFilter.c        \
                    $(GAMETUTOR_PATH)/libs/openal_lib_for_Android_Only/OpenAL32/alListener.c      \
                    $(GAMETUTOR_PATH)/libs/openal_lib_for_Android_Only/OpenAL32/alSource.c        \
                    $(GAMETUTOR_PATH)/libs/openal_lib_for_Android_Only/OpenAL32/alState.c         \
                    $(GAMETUTOR_PATH)/libs/openal_lib_for_Android_Only/OpenAL32/alThunk.c         \
                    $(GAMETUTOR_PATH)/libs/openal_lib_for_Android_Only/Alc/ALc.c                  \
                    $(GAMETUTOR_PATH)/libs/openal_lib_for_Android_Only/Alc/alcConfig.c            \
                    $(GAMETUTOR_PATH)/libs/openal_lib_for_Android_Only/Alc/alcEcho.c              \
                    $(GAMETUTOR_PATH)/libs/openal_lib_for_Android_Only/Alc/alcModulator.c         \
                    $(GAMETUTOR_PATH)/libs/openal_lib_for_Android_Only/Alc/alcReverb.c            \
                    $(GAMETUTOR_PATH)/libs/openal_lib_for_Android_Only/Alc/alcRing.c              \
                    $(GAMETUTOR_PATH)/libs/openal_lib_for_Android_Only/Alc/alcThread.c            \
                    $(GAMETUTOR_PATH)/libs/openal_lib_for_Android_Only/Alc/ALu.c                  \
                    $(GAMETUTOR_PATH)/libs/openal_lib_for_Android_Only/Alc/android.c              \
                    $(GAMETUTOR_PATH)/libs/openal_lib_for_Android_Only/Alc/bs2b.c                 \
                    $(GAMETUTOR_PATH)/libs/openal_lib_for_Android_Only/Alc/null.c 

LOCAL_CFLAGS     := -DAL_BUILD_LIBRARY -DAL_ALEXT_PROTOTYPES
LOCAL_LDLIBS     := -llog -Wl,-s

include $(BUILD_STATIC_LIBRARY)

########################################################################################################

include $(CLEAR_VARS)

LOCAL_MODULE     := tremolo
LOCAL_ARM_MODE   := arm
LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(GAMETUTOR_PATH)/libs/openal \
					$(LOCAL_PATH)/$(GAMETUTOR_PATH)/libs/openal/tremolo \
					$(LOCAL_PATH)/$(GAMETUTOR_PATH)/libs/openal_lib_for_Android_Only/OpenAL32 \
					$(LOCAL_PATH)/$(GAMETUTOR_PATH)/libs/openal_lib_for_Android_Only/OpenAL32/Include

					
LOCAL_SRC_FILES  := $(GAMETUTOR_PATH)/libs/openal_lib_for_Android_Only/tremolo/bitwise.c      \
                    $(GAMETUTOR_PATH)/libs/openal_lib_for_Android_Only/tremolo/bitwiseARM.s   \
                    $(GAMETUTOR_PATH)/libs/openal_lib_for_Android_Only/tremolo/codebook.c     \
                    $(GAMETUTOR_PATH)/libs/openal_lib_for_Android_Only/tremolo/dpen.s         \
                    $(GAMETUTOR_PATH)/libs/openal_lib_for_Android_Only/tremolo/dsp.c          \
                    $(GAMETUTOR_PATH)/libs/openal_lib_for_Android_Only/tremolo/floor0.c       \
                    $(GAMETUTOR_PATH)/libs/openal_lib_for_Android_Only/tremolo/floor1.c       \
                    $(GAMETUTOR_PATH)/libs/openal_lib_for_Android_Only/tremolo/floor1ARM.s    \
                    $(GAMETUTOR_PATH)/libs/openal_lib_for_Android_Only/tremolo/floor1LARM.s   \
                    $(GAMETUTOR_PATH)/libs/openal_lib_for_Android_Only/tremolo/floor_lookup.c \
                    $(GAMETUTOR_PATH)/libs/openal_lib_for_Android_Only/tremolo/framing.c      \
                    $(GAMETUTOR_PATH)/libs/openal_lib_for_Android_Only/tremolo/info.c         \
                    $(GAMETUTOR_PATH)/libs/openal_lib_for_Android_Only/tremolo/mapping0.c     \
                    $(GAMETUTOR_PATH)/libs/openal_lib_for_Android_Only/tremolo/mdct.c         \
                    $(GAMETUTOR_PATH)/libs/openal_lib_for_Android_Only/tremolo/mdctARM.s      \
                    $(GAMETUTOR_PATH)/libs/openal_lib_for_Android_Only/tremolo/mdctLARM.s     \
                    $(GAMETUTOR_PATH)/libs/openal_lib_for_Android_Only/tremolo/misc.c         \
                    $(GAMETUTOR_PATH)/libs/openal_lib_for_Android_Only/tremolo/res012.c       \
                    $(GAMETUTOR_PATH)/libs/openal_lib_for_Android_Only/tremolo/speed.s        \
                    $(GAMETUTOR_PATH)/libs/openal_lib_for_Android_Only/tremolo/vorbisfile.c   \
                    $(GAMETUTOR_PATH)/libs/openal_lib_for_Android_Only/tremolo/speed.s

LOCAL_CFLAGS     := -D_ARM_ASSEM_

include $(BUILD_STATIC_LIBRARY)

########################################################################################################

include $(CLEAR_VARS)

LOCAL_ARM_MODE := arm

ndk-build V=1

LOCAL_MODULE    := 	gl2jni
LOCAL_CFLAGS    := 	-Werror -DANDROID																	\
					-fpermissive 																		\
					-frtti

LOCAL_C_INCLUDES:= 	$(LOCAL_PATH)/$(GAMETUTOR_PATH)/header 												\
					$(LOCAL_PATH)/$(GAMETUTOR_PATH)/libs/ogl 											\
					$(LOCAL_PATH)/$(GAMETUTOR_PATH)/libs/openal 										\
					$(LOCAL_PATH)/$(GAMETUTOR_PATH)/libs/openal/tremolo 								\
					$(LOCAL_PATH)/$(GAMETUTOR_PATH)/libs/openal_lib_for_Android_Only/OpenAL32 			\
					$(LOCAL_PATH)/$(GAMETUTOR_PATH)/libs/openal_lib_for_Android_Only/OpenAL32/Include	\
					$(LOCAL_PATH)/$(GAMETUTOR_PATH)/libs/openal_lib_for_Android_Only/OpenAL32/Include	\
					$(LOCAL_PATH)/$(DEMO_PATH)															\
					$(LOCAL_PATH)/$(DEMO_PATH)/ObjectGame
					

LOCAL_SRC_FILES := 	$(DEMO_PATH)/CExample.cpp 															\
					$(DEMO_PATH)/CStateLogo.cpp 														\
					$(DEMO_PATH)/CStatePoster.cpp 														\
					$(DEMO_PATH)/CStateIngame.cpp														\
					$(DEMO_PATH)/CStateLoading.cpp 														\
					$(DEMO_PATH)/CStateHelp.cpp 														\
					$(DEMO_PATH)/CStateAbout.cpp 														\
					$(DEMO_PATH)/CStateOption.cpp 														\
					$(DEMO_PATH)/CStateAskSound.cpp														\
					$(DEMO_PATH)/CStateChooseLevel.cpp													\
					$(DEMO_PATH)/CStateMenu.cpp 														\
					$(DEMO_PATH)/WOTMapfile.cpp 														\
					$(DEMO_PATH)/CObjectManagement.cpp 													\
					$(DEMO_PATH)/ObjectGame/PathEle.cpp	 												\
					$(DEMO_PATH)/ObjectGame/EnemyObject.cpp 											\
					$(DEMO_PATH)/ObjectGame/GameObject.cpp 												\
					$(DEMO_PATH)/ObjectGame/MapObject.cpp 												\
					$(DEMO_PATH)/ObjectGame/TowerObject.cpp 											\
					$(DEMO_PATH)/ObjectGame/TreeObject.cpp 												\
					$(DEMO_PATH)/ObjectGame/BulletObject.cpp 											\
					$(DEMO_PATH)/ObjectGame/LibAI.cpp 													\
					$(DEMO_PATH)/ObjectGame/CInfoPanel.cpp 												\
					$(DEMO_PATH)/main.cpp 																\
					$(GAMETUTOR_PATH)/source/CControllerEventManager.cpp 								\
					$(GAMETUTOR_PATH)/source/CGraphics2D.cpp 											\
					$(GAMETUTOR_PATH)/source/CStateManagement.cpp 										\
					$(GAMETUTOR_PATH)/source/CDevice.cpp 												\
					$(GAMETUTOR_PATH)/source/CImage.cpp 												\
					$(GAMETUTOR_PATH)/source/CStringBufferStream.cpp 									\
					$(GAMETUTOR_PATH)/source/CFpsController.cpp 										\
					$(GAMETUTOR_PATH)/source/CRandom.cpp 												\
					$(GAMETUTOR_PATH)/source/CToken.cpp 												\
					$(GAMETUTOR_PATH)/source/Matrix.cpp 												\
					$(GAMETUTOR_PATH)/source/CGame.cpp 													\
					$(GAMETUTOR_PATH)/source/CSprite.cpp 												\
					$(GAMETUTOR_PATH)/source/CVSView.cpp 												\
					$(GAMETUTOR_PATH)/source/CObject3D.cpp	 											\
					$(GAMETUTOR_PATH)/source/CMD2Model.cpp 												\
					$(GAMETUTOR_PATH)/source/vec3f.cpp 													\
					$(GAMETUTOR_PATH)/source/CAndroidView.cpp											\
					$(GAMETUTOR_PATH)/source/SoundDriver.cpp											\
					$(GAMETUTOR_PATH)/source/CButton.cpp												\
					$(GAMETUTOR_PATH)/source/CDropdownButton.cpp										\
					$(GAMETUTOR_PATH)/source/MyParticle.cpp												\
					$(GAMETUTOR_PATH)/source/MyParticleSystem.cpp										\
					$(GAMETUTOR_PATH)/source/CModelManager.cpp											\
					$(GAMETUTOR_PATH)/source/CSkyBox.cpp												\
					$(GAMETUTOR_PATH)/source/CCamera.cpp
					

LOCAL_LDLIBS    := -llog -lGLESv2

LOCAL_STATIC_LIBRARIES := 	libtremolo	\
							libopenal

include $(BUILD_SHARED_LIBRARY)
