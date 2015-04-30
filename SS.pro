QT += opengl
QT -= core
QT -= gui

CONFIG += console
CONFIG += c++11
CONFIG -= qt
CONFIG -= app_bundle

TARGET = super_stardust
DESTDIR = .
cache()


SOURCES += src/*.cpp \
           src/NCCA/*.cpp
HEADERS += include/*.h \
           include/NCCA/*.h
OTHER_FILES += textures/* \
               models/* \
               sounds/* \
               Resources.txt

INCLUDEPATH += ./include
INCLUDEPATH += /usr/local/include

QMAKE_CXXFLAGS += $$system(sdl2-config  --cflags)
QMAKE_CXXFLAGS += -std=c++0x

LIBS += $$system(sdl2-config  --libs)
LIBS += -L/usr/local/lib -lSDL2_image -lSDL2_mixer -lvorbis -logg

macx:LIBS += -framework OpenGL
macx:LIBS += -framework glut
macx:DEFINES +=DARWIN

linux-* {
    DEFINES += LINUX
    LIBS+= -lGLEW -lglut -lGLU
}

linux-clang {
    DEFINES += LINUX
    LIBS+= -lGLEW -lglut -lGLU
}
