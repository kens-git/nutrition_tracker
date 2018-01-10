QT       += sql
QT       -= gui

TARGET = Model
TEMPLATE = lib

DEFINES += MODEL_LIBRARY

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        DatabaseManager.cpp \
    FoodDAO.cpp \
    CategoryModel.cpp \
    FoodModel.cpp \
    IntakeTargetDAO.cpp \
    IntakeTargetModel.cpp \
    IntakeDAO.cpp \
    IntakeModel.cpp

HEADERS += \
        DatabaseManager.hpp \
        model_global.h \ 
    FoodDAO.hpp \
    Food.hpp \
    CategoryModel.hpp \
    FoodModel.hpp \
    IntakeTarget.hpp \
    IntakeTargetDAO.hpp \
    IntakeTargetModel.hpp \
    IntakeDAO.hpp \
    IntakeModel.hpp
