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


SOURCES += src/Asteroids.cpp \
           src/Audio.cpp \
           src/Camera.cpp \
           src/LoadOBJ.cpp \
           src/main.cpp \
           src/Particles.cpp \
           src/Planet.cpp \
           src/Player.cpp \
           src/Projectile.cpp \
           src/Sdl_gl.cpp \
           src/TextureOBJ.cpp \
           src/World.cpp \
           src/NCCA/GLFunctions.cpp \
           src/NCCA/Mat4.cpp \
           src/NCCA/Vec4.cpp
HEADERS += include/Asteroids.h \
           include/Audio.h \
           include/Camera.h \
           include/Defs.h \
           include/frames.h \
           include/Icosahedron.h \
           include/LoadOBJ.h \
           include/Particles.h \
           include/Planet.h \
           include/Player.h \
           include/Projectile.h \
           include/Sdl_gl.h \
           include/TextureOBJ.h \
           include/World.h \
           include/NCCA/GLFunctions.h \
           include/NCCA/Mat4.h \
           include/NCCA/Vec4.h
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
