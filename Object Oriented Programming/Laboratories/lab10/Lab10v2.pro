QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    admin_gui.cpp \
    lab9/AdminFile.cpp \
    lab9/Controller.cpp \
    lab9/Domain.cpp \
    lab9/Iterator.cpp \
    lab9/Repository.cpp \
    lab9/Tests.cpp \
    lab9/UserFile.cpp \
    main.cpp \
    main_gui.cpp \
    user_gui.cpp

HEADERS += \
    admin_gui.h \
    lab9/AdminFile.h \
    lab9/Controller.h \
    lab9/Domain.h \
    lab9/DynamicArray.h \
    lab9/Exceptions.h \
    lab9/Iterator.h \
    lab9/Repository.h \
    lab9/Tests.h \
    lab9/UserFile.h \
    lab9/Validators.h \
    main_gui.h \
    user_gui.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    lab9/csvfile.csv \
    lab9/dataout.txt \
    lab9/htmlfile.html \
    lab9/new_csv.csv
