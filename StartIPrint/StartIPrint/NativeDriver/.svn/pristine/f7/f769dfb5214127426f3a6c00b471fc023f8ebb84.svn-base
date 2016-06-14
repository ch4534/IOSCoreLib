LOCAL_PATH:= $(call my-dir)
LIBUSB_ROOT_REL:= ../..
LIBUSB_ROOT_ABS:= $(LOCAL_PATH)/../..

#libNativeDriver

include $(CLEAR_VARS)

LIBUSB_ROOT_REL:= ../..
LIBUSB_ROOT_ABS:= $(LOCAL_PATH)/../..

# All of the source files that we will compile.
# 具体到底需要哪些c代码，没有仔细研究过
LOCAL_SRC_FILES:= \
                  $(LIBUSB_ROOT_REL)/libNativeDriver/cn_com_itep_corelib_Driver_NativeDriver.cpp \
                  $(LIBUSB_ROOT_REL)/libNativeDriver/Driver.cpp \
                  $(LIBUSB_ROOT_REL)/libNativeDriver/OKIDriver.cpp \
                  $(LIBUSB_ROOT_REL)/libNativeDriver/OLIDriver.cpp \
                  $(LIBUSB_ROOT_REL)/libNativeDriver/LQDriver.cpp \
                  $(LIBUSB_ROOT_REL)/libNativeDriver/MPDriver.cpp \
                  $(LIBUSB_ROOT_REL)/libNativeDriver/EPOSTPDriver.cpp \
                  $(LIBUSB_ROOT_REL)/libNativeDriver/EPOSADriver.cpp


LOCAL_LDLIBS := -llog

LOCAL_SHARED_LIBRARIES := \
     libandroid_runtime

# No static libraries.
LOCAL_STATIC_LIBRARIES := \
     libbz

# Also need the JNI headers.
LOCAL_C_INCLUDES += \
    $(LIBUSB_ROOT_REL)/libNativeDriver/ \
    $(JNI_H_INCLUDE) external/bzip2

# No special compiler flags.
LOCAL_CFLAGS +=

# This is the target being built.
LOCAL_MODULE:= NativeDriver

include $(BUILD_SHARED_LIBRARY)