LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE_TAGS := optional
LOCAL_DEX_PREOPT := false
LOCAL_SRC_FILES := $(call all-java-files-under, src)
LOCAL_PACKAGE_NAME := TestTvoutCircle
LOCAL_CERTIFICATE := platform
LOCAL_JAVA_LIBRARIES := actions
include $(BUILD_PACKAGE)
