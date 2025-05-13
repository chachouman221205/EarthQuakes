MAIN_FILE = web.c
OUTPUT = /home/chachou/WebHub/EarthQuake/index.js

COMPILER = emcc
PARAMS = -I/home/chachou/raylib/src -L/home/chachou/raylib/build_web/raylib -lraylib -s USE_GLFW=3 -s ASYNCIFY -s FULL_ES2=1
#PARAMS = -I/home/chachou/raylib/src -L/home/chachou/raylib/build_web/raylib -lraylib -s USE_GLFW=3 -s ASYNCIFY -s WASM=1 -s ALLOW_MEMORY_GROWTH=1 -s EXPORTED_FUNCTIONS="['_main']" -s EXPORTED_RUNTIME_METHODS="['ccall','cwrap']"


OBJ_DIR = ../obj

$(OUTPUT): $(OBJ_DIR)/button.o
	$(COMPILER) $(PARAMS) -o $(OUTPUT) $(MAIN_FILE) $(OBJ_DIR)/button.o
	make clean

$(OBJ_DIR)/button.o: button.c
	@mkdir -p $(OBJ_DIR)
	$(COMPILER) $(PARAMS) -c button.c -o $@

clean:
	rm -r $(OBJ_DIR)

re: clean all

.PHONY: test clean