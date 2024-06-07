TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    cell.cpp \
    environment.cpp \
    inhabitant.cpp \
    main.cpp \
    neighborhood.cpp \
    organism.cpp \
    randomgenerator.cpp \
    speciments.cpp
HEADERS += \
    cell.h \
    environment.h \
    inhabitant.h \
    neighborhood.h \
    organism.h \
    randomgenerator.h \
    settings.h \
    speciments.h
