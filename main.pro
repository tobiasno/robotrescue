TEMPLATE = app
TARGET = robotrescue
 
QT = core gui
 
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

HEADERS += include/*.h
SOURCES += src/*.cpp
