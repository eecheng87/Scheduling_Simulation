TARGET  = scheduling_simulator
SRC_DIR = ./
INC_DIR = ./
CC = gcc
CFLAGS += -std=gnu99 -Wall -g
SRC     = $(wildcard $(SRC_DIR)*.c)
OBJ     = $(SRC:%.c=%.o) #$(patsubst %.c, %.o, $(SRC))
DEP     = $(SRC:%.c=%.d) #$(patsubst %.o, %.d, $(OBJ))

GIT_HOOKS := .git/hooks/applied

.PHONY: clean

$(TARGET) : $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(GIT_HOOKS):
	scripts/install-git-hooks

all: $(GIT_HOOKS) $(TARGET)

test1:
	make clean;\
	cd testcase1;\
	cp -f * ..;\
	cd ..;\
	make all;

test2:
	make clean;\
	cd testcase2;\
	cp -f * ..;\
	cd ..;\
	make all;

# Include all .d files
-include $(DEP)

# Build target for every single object file.
# The potential dependency on header files is covered by calling `-include $(DEP)`.
%.o : %.c
	$(CC) $(CFLAGS) -MMD -c $< -o $@

## clean
clean:
	rm -f $(TARGET) $(OBJ) $(DEP) config.[ch] task_set.[ch] answer_output.txt