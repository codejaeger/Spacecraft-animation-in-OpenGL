CC=g++ -std=c++17

OPENGLLIB= -lGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB)
LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-I/usr/local/include -I./
MKDIR_P=mkdir -p
OUT_DIR = bin

BIN1=bin/a3-model-0
SRCS1=src/earth/a3-model-0.cpp src/earth/gl_framework.cpp src/earth/shader_util.cpp src/earth/hierarchy_node.cpp
INCLUDES1=src/earth/gl_framework.hpp src/earth/shader_util.hpp src/earth/a3-model-0.hpp src/earth/hierarchy_node.hpp

BIN2=bin/a3-model-1
SRCS2=src/launch_pad/a3-model-1.cpp src/launch_pad/gl_framework.cpp src/launch_pad/shader_util.cpp src/launch_pad/hierarchy_node.cpp
INCLUDES2=src/launch_pad/gl_framework.hpp src/launch_pad/shader_util.hpp src/launch_pad/a3-model-1.hpp src/launch_pad/hierarchy_node.hpp

BIN3=bin/a3-model-2
SRCS3=src/pslv_rocket/a3-model-2.cpp src/pslv_rocket/gl_framework.cpp src/pslv_rocket/shader_util.cpp src/pslv_rocket/hierarchy_node.cpp
INCLUDES3=src/pslv_rocket/gl_framework.hpp src/pslv_rocket/shader_util.hpp src/pslv_rocket/a3-model-2.hpp src/pslv_rocket/hierarchy_node.hpp

BIN4=bin/a3-model-3
SRCS4=src/payload/a3-model-3.cpp src/payload/gl_framework.cpp src/payload/shader_util.cpp src/payload/hierarchy_node.cpp
INCLUDES4=src/payload/gl_framework.hpp src/payload/shader_util.hpp src/payload/a3-model-3.hpp src/payload/hierarchy_node.hpp

BIN5=bin/a3-scene
SRCS5=src/main_file/a3-scene.cpp src/main_file/gl_framework.cpp src/main_file/shader_util.cpp src/main_file/hierarchy_node.cpp
INCLUDES5=src/main_file/gl_framework.hpp src/main_file/shader_util.hpp src/main_file/a3-scene.hpp src/main_file/hierarchy_node.hpp

all: directories $(BIN1) $(BIN2) $(BIN3) $(BIN4) $(BIN5)

$(BIN1): $(SRCS1) $(INCLUDES1)
	g++ $(CPPFLAGS) $(SRCS1) -o $(BIN1) $(LDFLAGS) $(LIBS)

$(BIN2): $(SRCS2) $(INCLUDES2)
	g++ $(CPPFLAGS) $(SRCS2) -o $(BIN2) $(LDFLAGS) $(LIBS)

$(BIN3): $(SRCS3) $(INCLUDES3)
	g++ $(CPPFLAGS) $(SRCS3) -o $(BIN3) $(LDFLAGS) $(LIBS)

$(BIN4): $(SRCS4) $(INCLUDES4)
	g++ $(CPPFLAGS) $(SRCS4) -o $(BIN4) $(LDFLAGS) $(LIBS)

$(BIN5): $(SRCS5) $(INCLUDES5)
	g++ $(CPPFLAGS) $(SRCS5) -o $(BIN5) $(LDFLAGS) $(LIBS)

directories : $(OUT_DIR)

$(OUT_DIR):
	$(MKDIR_P) $(OUT_DIR)

clean:
	rm -f *~ *.o $(BIN)
	rm -r $(OUT_DIR)