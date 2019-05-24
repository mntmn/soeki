NAME= soeki.proj
TYPE= APP
SRCS= goutextri2.cpp networ.cpp network.cpp independent/engine.cpp independent/gfx32.cpp independent/processing.cpp independent/structures.cpp independent/zones.cpp platform/beos/assd.cpp platform/beos/master.cpp platform/beos/textures.cpp platform/beos/storage.cpp
RSRCS=
LIBS= /boot/system/lib/libroot.so /boot/system/lib/libbe.so /boot/system/lib/libgame.so /boot/system/lib/libnetapi.so /boot/system/lib/libdevice.so /boot/system/lib/libtranslation.so
LIBPATHS=
SYSTEM_INCLUDE_PATHS= /boot/develop/headers/be /boot/develop/headers/cpp /boot/develop/headers/posix /boot/home/config/include
LOCAL_INCLUDE_PATHS= . ./independent ./platform/beos
OPTIMIZE=NONE
#	specify any preprocessor symbols to be defined.  The symbols will not
#	have their values set automatically; you must supply the value (if any)
#	to use.  For example, setting DEFINES to "DEBUG=1" will cause the
#	compiler option "-DDEBUG=1" to be used.  Setting DEFINES to "DEBUG"
#	would pass "-DDEBUG" on the compiler's command line.
DEFINES=
#	specify special warning levels
#	if unspecified default warnings will be used
#	NONE = supress all warnings
#	ALL = enable all warnings
WARNINGS =
# Build with debugging symbols if set to TRUE
SYMBOLS=
COMPILER_FLAGS=-I.
LINKER_FLAGS=

## include the makefile-engine
include $(BUILDHOME)/etc/makefile-engine
