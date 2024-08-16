QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIBS += -lncurses

SOURCES += \
    ../../../brick_game/back/brick_movement/check_collision.cc \
    ../../../brick_game/back/brick_movement/get_move_data.cc \
    ../../../brick_game/back/brick_movement/move_brick.cc \
    ../../../brick_game/back/bricks/bricks.cc \
    ../../../brick_game/back/field/field.cc \
    ../../../brick_game/back/game_info/game_info.cc \
    ../../../brick_game/snake/snake_fsm.cc \
    ../../../brick_game/snake/snake_game_loop.cc \
    ../../../brick_game/snake/snake_update_current_state.cc \
    ../../../brick_game/tetris/tetris_base.cc \
    ../../../brick_game/tetris/tetris_fsm.cc \
    ../../../brick_game/tetris/tetris_game_loop.cc \
    ../../cli/get_signal_console/get_signal_console.cc \
    ../../cli/stats/stats.cc \
    ../../cli/timer/timer.cc \
    ../../cli/ui/ui.cc \
    ../../cli/user_input/user_input.cc \
    ../../cli/window/window.cc \
    ../get_signal_desctop/get_signal_desktop.cc \
    gamewindow.cpp \
    get_brush.cc \
    main.cpp \
    mainwindow.cpp \
    next_brick_widget.cpp

HEADERS += \
    ../../../brick_game/back/back.h \
    ../../../brick_game/back/brick_movement/check_collision.h \
    ../../../brick_game/back/brick_movement/get_move_data.h \
    ../../../brick_game/back/brick_movement/move_brick.h \
    ../../../brick_game/back/bricks/bricks.h \
    ../../../brick_game/back/common/defines.h \
    ../../../brick_game/back/field/field.h \
    ../../../brick_game/back/game_info/game_info.h \
    ../../../brick_game/snake/snake.h \
    ../../../brick_game/snake/snake_class.h \
    ../../../brick_game/snake/snake_fsm.h \
    ../../../brick_game/snake/snake_game_loop.h \
    ../../../brick_game/snake/snake_update_current_state.h \
    ../../../brick_game/tetris/full_line_handler/full_line_handler.h \
    ../../../brick_game/tetris/tetris.h \
    ../../../brick_game/tetris/tetris_base.h \
    ../../../brick_game/tetris/tetris_defines.h \
    ../../../brick_game/tetris/tetris_fsm.h \
    ../../../brick_game/tetris/tetris_game_loop.h \
    ../../cli/cli.h \
    ../../cli/get_signal_console/get_signal_console.h \
    ../../cli/stats/stats.h \
    ../../cli/timer/timer.h \
    ../../cli/ui/ui.h \
    ../../cli/user_input/user_input.h \
    ../../cli/window/window.h \
    ../get_signal_desctop/get_signal_desktop.h \
    get_brush.h \
    gamewindow.h \
    mainwindow.h \
    next_brick_widget.h

FORMS += \
    gamewindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    res/1.png \
    res/2.png \
    res/3.png \
    res/4.png \
    res/5.png

RESOURCES += \
    res.qrc
