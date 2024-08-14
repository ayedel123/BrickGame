GPP = gcc -lstdc++ 
CFLAGS =  -Werror -Wall -Wextra -std=c++17 

PILK = pilk.c
FRONTEND = gui/cli/user_input/*.cc \
			gui/cli/stats/*.cc \
			gui/cli/timer/*.cc \
			gui/cli/ui/*.cc \
			gui/cli/window/*.cc \
			gui/cli/get_signal_console/get_signal_console.cc

TETRIS_BACK = brick_game/back/bricks/*.cc \
				brick_game/back/brick_movement/*.cc \
				brick_game/back/game_info/*.cc \
				brick_game/back/field/*.cc

TETRIS = brick_game/tetris/*.cc \
				brick_game/tetris/full_line_handler/*.cc

SNAKE = brick_game/snake/*.cc

TEST_SOURCES = brick_game/test/brick_game_test.cc

MAIN = brick_game/main.cc

CURSES = -lncurses
CHECK_FLAGS = -lcheck
LIBS = $(CURSES)
G_FLAGS = -lpthread -g -fprofile-arcs -ftest-coverage
DIST_DIR = game_archive
OPEN_COMMAND = open


UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
TESTFLAGS=-lgtest -lgtest_main -lrt -lstdc++ -pthread -lm -g
endif
ifeq ($(UNAME), Darwin)
TESTFLAGS=-lgtest -lgtest_main -lstdc++ -pthread -lm -g
endif


DVI = dvi/README.html

OS := $(shell uname)

ifeq ($(OS),Darwin)
    OPEN_COMMAND= open
    CHECK_FLAGS = -lcheck
else
    OPEN_COMMAND= xdg-open
    CHECK_FLAGS = -lcheck -lm -lpthread -lrt -lsubunit
endif

all: gcov_report install run

install_cli: ${MAIN} ${TETRIS_BACK} $(FRONTEND) ${TETRIS} ${SNAKE}
	$(GPP) $(CFLAGS) $^ $(LIBS) -lstdc++ -o brick_game_cli.out

uninstall:
	rm -f tetris.out

gcov_report: clean clean_record
	$(GPP) $(CFLAGS) $(TETRIS_BACK) $(TEST_SOURCES) $(CHECK_FLAGS) $(G_FLAGS) -o GcovReport
	./GcovReport
	@lcov -t "GcovReport" -o GcovReport.info --no-external -c -d .
	@genhtml -o report GcovReport.info
	open ./report/index-sort-f.html
	make clean_gcov

dist: clean_dist
	mkdir -p ${DIST_DIR}
	cp -rf MakeFile ${DIST_DIR}
	cp -rf gui ${DIST_DIR}
	cp -rf brick_game ${DIST_DIR}
	cp -rf dvi_data ${DIST_DIR}
	tar -cvf game_archive.tar ${DIST_DIR}
	rm -rf ${DIST_DIR}

dvi:
	$(OPEN_COMMAND) dvi_data/README.html

run: 
	./tetris.out

test: clean
	$(GPP) $(TETRIS_BACK) $(FRONTEND) $(TETRIS) $(SNAKE) $(TEST_SOURCES) $(TESTFLAGS) $(LIBS) -lstdc++ -o test.out
	./test.out

valgrind:
	valgrind --tool=memcheck --leak-check=yes  ./test.out

clang:
	@cp ../../../../materials/linters/.clang-format .clang-format
	@find .. -type f -name "*.c" -exec clang-format -n -style=Google {} \;
	@find .. -type f -name "*.h" -exec clang-format -n -style=Google {} \;
	@rm .clang-format


clean: clean_gcov clean_dist
	rm -rf *.o *.out *_record test.out bepis report 

clean_gcov: clean_record
	rm -rf GcovReport *.gcda *.gcno GcovReport.dSYM *.info

clean_record:
	rm -rf record

clean_dist:
	rm -rf ${DIST_DIR} game_archive.tar