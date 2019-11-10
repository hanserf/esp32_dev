#
# This is a project Makefile. It is assumed the directory this Makefile resides in is a
# project subdirectory.
#

PROJECT_NAME := ESP32-dev
EXTRA_COMPONENT_DIRS = $(PROJECT_PATH)/main $(PROJECT_PATH)/src $(PROJECT_PATH)/src/cmd
COMPONENT_EXTRA_INCLUDE = $(PROJECT_PATH)include $(PROJECT_PATH)include/cmd
include $(IDF_PATH)/make/project.mk

