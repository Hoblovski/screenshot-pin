QT += widgets

HEADERS             = screenshot.h \
    screencover.h \
    clickablelabel.h
SOURCES             = main.cpp \
                      screenshot.cpp \
    screencover.cpp \
    clickablelabel.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/desktop/screenshot
INSTALLS += target

FORMS +=

# for windows to work
win32-g++:LIBS += libUser32
win32-msvc*:LIBS += User32.lib
