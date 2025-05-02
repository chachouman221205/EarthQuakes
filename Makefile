MAIN_FILE = main.c
OUTPUT = EarthQuake.exe

COMPILER = gcc
PARAMS = -Wall -Wfatal-errors -Werror -g -o $(OUTPUT)

OBJ_DIR = obj

EarthQuake.exe: graph/graph.o
	$(COMPILER) $(PARAMS) main.c graph.o

graph.o: incidence_matrix.o

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -r $(OBJ_DIR)

re: clean all
