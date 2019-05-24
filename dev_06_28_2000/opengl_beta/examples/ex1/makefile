#
# app makefile
#
# Copyright (C) 1994 Be Inc.  All Rights Reserved
#

SHELL		:= /bin/sh

TYPE = APP
GROUP = Demos

#######
include $(BUILDHOME)/buildprefs/make.pre
#######

INCLUDES	+= -I${BUILDHOME}/headers/opengl

APP_NAME	:= GLViewer
TARGET		:= $(OBJ_DIR)/$(APP_NAME)
RESOURCE_FORK	:= $(APP_NAME).rsrc
CFLAGS		:= $(CFLAGS)

LDFLAGS		+= -lbe -lGL2 -lgame

VPATH += src
SRCS := GLViewer.cpp Wind.cpp FPS.cpp Model.cpp Scene.cpp

OBJS := $(SRCS_LIST_TO_OBJS)

default:$(TARGET)
		cp $(TARGET) $(APP_NAME)

$(TARGET):	$(OBJ_DIR) $(OBJS)
		$(LD) -o $@ $(OBJS) $(LDFLAGS)
		$(SETVERSION) $@ $(SYSTEM_VERSION) $(APP_VERSION)
		cp teapot.data $(INSTALL_ETC)/teapot.data
		chmod 777 $(INSTALL_ETC)/teapot.data

tar:		$(TARGET)
		-cd $(dir $(TARGET)); tar cv $(notdir $(TARGET))

floppy:		$(TARGET)
		-cd $(dir $(TARGET)); bf copy dos:$(notdir $(TARGET)) $(notdir $(TARGET))

clean::
		rm -f [a-z] bid $(APP_NAME)

#######
include $(BUILDHOME)/buildprefs/make.post
#######
