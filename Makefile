MAIN_FILE = main.c
OUTPUT = EarthQuake.exe
WEB_OUTPUT = /home/chachou/WebHub/EarthQuake/index.js

COMPILER ?= gcc
PARAMS ?= -Wall -Wfatal-errors -Werror -g 
WEB_COMPILER = emcc
WEB_PARAMS = -I/home/chachou/raylib/src -L/home/chachou/raylib/build_web/raylib -lraylib -s USE_GLFW=3 -s ASYNCIFY -s FULL_ES2=1


OBJ_DIR ?= obj

$(OUTPUT): obj
	$(COMPILER) $(PARAMS) -o $(OUTPUT) $(MAIN_FILE) $(OBJ_DIR)/graph.o $(OBJ_DIR)/incidence_matrix.o $(OBJ_DIR)/linked_list.o
	make clean


$(OBJ_DIR)/graph.o: graph/graph.c
	@mkdir -p $(OBJ_DIR)
	$(COMPILER) $(PARAMS) -c graph/graph.c -o $@

$(OBJ_DIR)/incidence_matrix.o:	graph/incidence_matrix.c
	@mkdir -p $(OBJ_DIR)
	$(COMPILER) $(PARAMS) -c graph/incidence_matrix.c -o $@

$(OBJ_DIR)/linked_list.o: graph/linked_list.c
	@mkdir -p $(OBJ_DIR)
	$(COMPILER) $(PARAMS) -c graph/linked_list.c -o $@



$(OBJ_DIR)/web.o: web_interface/web.c
	@mkdir -p $(OBJ_DIR)
	$(COMPILER) $(PARAMS) -c web_interface/web.c -o $@

$(OBJ_DIR)/button.o: web_interface/button.c
	@mkdir -p $(OBJ_DIR)
	$(COMPILER) $(PARAMS) -c web_interface/button.c -o $@

$(OBJ_DIR)/geometry.o: web_interface/geometry.c
	@mkdir -p $(OBJ_DIR)
	$(COMPILER) $(PARAMS) -c web_interface/geometry.c -o $@


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(COMPILER) $(PARAMS) -c $< -o $@

obj: $(OBJ_DIR)/graph.o $(OBJ_DIR)/incidence_matrix.o $(OBJ_DIR)/linked_list.o
obj_web:$(OBJ_DIR)/web.o $(OBJ_DIR)/button.o $(OBJ_DIR)/geometry.o

test: obj obj_web
	$(COMPILER) $(PARAMS) -o test/gen_files/file_gen.exe test/gen_files/file_gen.c $(OBJ_DIR)/graph.o $(OBJ_DIR)/incidence_matrix.o $(OBJ_DIR)/linked_list.o
	make
	cd test/gen_files && ./file_gen.exe

clean:
	rm -rf obj

web:
	make PARAMS="$(WEB_PARAMS)" COMPILER=$(WEB_COMPILER) obj
	$(WEB_COMPILER) $(WEB_PARAMS) -o $(WEB_OUTPUT) $(OBJ_DIR)/*.o
	make clean
	
re: clean all

.PHONY: test clean obj