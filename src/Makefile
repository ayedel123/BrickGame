GPP = gcc -lstdc++ 
CFLAGS =  -Werror -Wall -Wextra -std=c++17 

FRONTEND = gui/cli/user_input/*.cc \
			gui/cli/stats/*.cc \
			gui/cli/timer/*.cc \
			gui/cli/ui/*.cc \
			gui/cli/window/*.cc \
			gui/cli/get_signal_console/get_signal_console.cc

E_FRONTEND = $(patsubst %, -e %, $(FRONTEND))

BACK = brick_game/back/bricks/*.cc \
				brick_game/back/brick_movement/*.cc \
				brick_game/back/game_info/*.cc \
				brick_game/back/field/*.cc

TETRIS_BASIC = brick_game/tetris/tetris_fsm.cc \
				brick_game/tetris/tetris_base.cc

TETRIS_GAME = brick_game/tetris/tetris_game_loop.cc

TETRIS = $(TETRIS_BASIC) $(TETRIS_GAME)

SNAKE_BASIC = brick_game/snake/snake_fsm.cc \
		brick_game/snake/snake_update_current_state.cc

SNAKE_GAME = brick_game/snake/snake_game_loop.cc

SNAKE = $(SNAKE_BASIC) $(SNAKE_GAME)

TEST_SOURCES = brick_game/test/brick_game_test.cc \
				brick_game/test/back_test/add_points_test.cc \
				brick_game/test/back_test/check_collision_test.cc \
				brick_game/test/back_test/move_brick_test.cc \
				brick_game/test/tetris_test/full_line_handler_test.cc \
				brick_game/test/tetris_test/tetris_fsm_test.cc \
				brick_game/test/tetris_test/tetris_handle_collision_test.cc \
				brick_game/test/snake_test/snake_fsm_test.cc \
				brick_game/test/snake_test/snake_functions_test.cc
				

MAIN = brick_game/main.cc

CURSES = -lncurses
LIBS = $(CURSES)
GCOV = -lgcov --coverage -fprofile-arcs -ftest-coverage
DIST_DIR = game_archive
OPEN_COMMAND = open

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
GCOV_FIX =
TESTFLAGS=-lgtest -lgtest_main -lrt -lstdc++ -pthread -lm -g
endif
ifeq ($(UNAME), Darwin)
GCOV_FIX = --ignore-errors inconsistent
TESTFLAGS=-lgtest -lgtest_main -lstdc++ -pthread -lm -g
endif


DVI = dvi/README.html

OS := $(shell uname)

QT_PRO = ./gui/desktop/brick_game/brick_game.pro
QT_MAKEFILE_NAME = QtMakefile.mk

all: clean gcov_report install

run_desktop:
ifeq ($(OS), Linux)
	./qt_calc
else
	brick_game.app/Contents/MacOS/brick_game
endif

run_cli:
	./brick_game_cli.out

install_cli: ${MAIN} ${BACK} $(FRONTEND) ${TETRIS} ${SNAKE}
	$(GPP) $(CFLAGS) $^ $(LIBS) -lstdc++ -o brick_game_cli.out

install_desktop:
	qmake -o $(QT_MAKEFILE_NAME) $(QT_PRO)
	make -f $(QT_MAKEFILE_NAME)
	make -f $(QT_MAKEFILE_NAME) clean --silent
	rm -rf $(QT_MAKEFILE_NAME)
	rm -rf .qmake.stash

install: uninstall install_cli install_desktop
	
uninstall:
	rm -f brick_game_cli.out
	rm -rf $(QT_MAKEFILE_NAME)
	rm -rf .qmake.stash 
	rm -rf brick_game.app
	rm -rf gui/desktop/brick_game/build

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

test: clean
	$(GPP) $(BACK) $(FRONTEND) $(TETRIS_BASIC) $(SNAKE_BASIC) $(TEST_SOURCES) $(TESTFLAGS) $(LIBS) -lstdc++ -o test.out
	./test.out

gcov_report: clean
	$(GPP) $(BACK) $(TETRIS_BASIC) $(SNAKE_BASIC) $(TEST_SOURCES) $(TESTFLAGS) $(GCOV) $(FRONTEND) $(LIBS)  -lstdc++  -o gcov_report.out
	./gcov_report.out
	@lcov -t "gcov_report" -o coverage.info $(GCOV_FIX) --no-external -c -d .
	@lcov -r coverage.info -o report.info \
		$(GCOV_FIX) --no-external \
		gui/cli/user_input/user_input.cc \
		gui/cli/stats/stats.cc \
		gui/cli/timer/timer.cc \
		gui/cli/ui/ui.cc \
		gui/cli/window/window.cc \
		gui/cli/get_signal_console/get_signal_console.cc
	@genhtml -o report report.info
	@make clean_gcov
	open report/index.html

valgrind:
	valgrind --tool=memcheck --leak-check=yes  ./test.out

style_check:
	@cp ../materials/linters/.clang-format .clang-format
	@find .. -type f -name "*.cc" -exec clang-format -n {} \;
	@find .. -type f -name "*.h" -exec clang-format -n {} \;
	@rm .clang-format

clang: style_check
	@cp ../materials/linters/.clang-format .clang-format
	@find .. -type f -name "*.cc" -exec clang-format -i {} \;
	@find .. -type f -name "*.h" -exec clang-format -i {} \;
	@rm .clang-format


clean: clean_gcov clean_dist uninstall
	rm -rf *.o *.out *_record test.out bepis report

clean_gcov: clean_record
	rm -rf GcovReport *.gcda *.gcno *.dSYM *.info

clean_record:
	rm -rf record

clean_dist:
	rm -rf ${DIST_DIR} game_archive.tar