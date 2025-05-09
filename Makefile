MAIN_FILE = main.c
OUTPUT = EarthQuake.exe

COMPILER = gcc
PARAMS = -Wall -Wfatal-errors -Werror -g -o $(OUTPUT)

OBJ_DIR = obj

$(OUTPUT): $(OBJ_DIR)/graph.o $(OBJ_DIR)/incidence_matrix.o $(OBJ_DIR)/linked_list.o

	$(COMPILER) $(PARAMS) main.c $(OBJ_DIR)/graph.o $(OBJ_DIR)/incidence_matrix.o $(OBJ_DIR)/linked_list.o
	make clean

$(OBJ_DIR)/file_gen.o: test/gen_files/file_gen.c
	@mkdir -p $(OBJ_DIR)
	$(COMPILER) $(PARAMS) -c test/gen_files/file_gen.c -o $@

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

test:
	cd test/gen_files && gcc -o file_gen.exe file_gen.c && ./file_gen.exe

clean:
	rm -r $(OBJ_DIR)

re: clean all
