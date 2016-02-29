OS := $(shell uname)
ARCH := $(shell uname -m)

ifeq ($(OS), Linux)
  ifeq ($(ARCH), x86_64)
    LEAP_LIBRARY := ../lib/x64/libLeap.so -Wl,-rpath,../lib/x64
  else
    LEAP_LIBRARY := ../lib/x86/libLeap.so -Wl,-rpath,../lib/x86
  endif
else
  # OS X
  LEAP_LIBRARY := ../lib/libLeap.dylib
endif

gestures: gestures.cpp
	$(CXX) -std=c++0x -Wall -g -I../include gestures.cpp -o gestures $(LEAP_LIBRARY)
ifeq ($(OS), Darwin)
	install_name_tool -change @loader_path/libLeap.dylib ../lib/libLeap.dylib gestures
endif

clean:
	rm -rf gestures gestures.dSYM
