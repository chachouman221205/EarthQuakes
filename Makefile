MAIN_FILE = main.c
OUTPUT = EarthQuake.exe

COMPILER = gcc
PARAMS = -Wall -Wfatal-errors -Werror -g -o $(OUTPUT)

OBJ_DIR = obj

$(OUTPUT): $(OBJ_DIR)/graph.o $(OBJ_DIR)/incidence_matrix.o $(OBJ_DIR)/linked_list.o
	cd test/gen_files && ./file_gen.exe
	$(COMPILER) $(PARAMS) main.c $(OBJ_DIR)/graph.o $(OBJ_DIR)/incidence_matrix.o $(OBJ_DIR)/linked_list.o
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

clean:
	rm -r $(OBJ_DIR)

re: clean all
