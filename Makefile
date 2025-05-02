MAIN_FILE = main.c
OUTPUT = EarthQuake.exe

COMPILER = gcc
PARAMS = -Wall -Wfatal-errors -Werror -g -o $(OUTPUT)

OBJ_DIR = obj

$(OUTPUT): $(OBJ_DIR)/graph.o
	$(COMPILER) $(PARAMS) main.c graph/graph.o

$(OBJ_DIR)/graph.o:
	@mkdir -p $(OBJ_DIR)
	$(COMPILER) $(PARAMS) -c graph/graph.c -o $@

$(OBJ_DIR)/incidence_matrix.o:

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(COMPILER) $(PARAMS) -c $< -o $@

clean:
	rm -r $(OBJ_DIR)

re: clean all
