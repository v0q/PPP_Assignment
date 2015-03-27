QT += opengl
QT -= core
QT -= gui

CONFIG += console
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
               models/*

INCLUDEPATH += ./include
INCLUDEPATH += /usr/local/include

QMAKE_CXXFLAGS += $$system(sdl2-config  --cflags)
QMAKE_CXXFLAGS += -std=c++11

LIBS += $$system(sdl2-config  --libs)
LIBS += -L/usr/local/lib -lSDL2_image

macx:LIBS += -framework OpenGL
macx:LIBS += -framework glut
macx:DEFINES +=DARWIN
