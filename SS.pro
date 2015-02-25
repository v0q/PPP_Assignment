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

INCLUDEPATH += ./include
INCLUDEPATH += /usr/local/include

QMAKE_CXXFLAGS += $$system(sdl2-config  --cflags)

LIBS += $$system(sdl2-config  --libs)
LIBS += -L/usr/local/lib

macx:LIBS+= -framework OpenGL
macx:DEFINES+=DARWIN
