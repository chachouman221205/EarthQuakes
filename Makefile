MAIN_FILE = main.c
OUTPUT = EarthQuake.exe

COMPILER = gcc
PARAMS = -Wall -Wfatal-errors -Werror -g 

OBJ_DIR = obj

$(OUTPUT): $(OBJ_DIR)/graph.o $(OBJ_DIR)/incidence_matrix.o $(OBJ_DIR)/linked_list.o
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


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(COMPILER) $(PARAMS) -c $< -o $@

obj: $(OBJ_DIR)/graph.o $(OBJ_DIR)/incidence_matrix.o $(OBJ_DIR)/linked_list.o

test: $(OBJ_DIR)/graph.o $(OBJ_DIR)/incidence_matrix.o $(OBJ_DIR)/linked_list.o
	$(COMPILER) $(PARAMS) -o test/gen_files/file_gen.exe test/gen_files/file_gen.c $(OBJ_DIR)/graph.o $(OBJ_DIR)/incidence_matrix.o $(OBJ_DIR)/linked_list.o
	cd test/gen_files && ./file_gen.exe

clean:
	rm -r $(OBJ_DIR)

web:
	make
	emcc web_interface/web.c -o /home/chachou/WebHub/EarthQuake/index.js -I/home/chachou/raylib/src -L/home/chachou/raylib/build_web/raylib -lraylib -s USE_GLFW=3 -s ASYNCIFY -s FULL_ES2=1

re: clean all

.PHONY: test clean obj