QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

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
    Backend/action.cpp \
    Backend/controller.cpp \
    Backend/csv_file.cpp \
    Backend/file_repository.cpp \
    Backend/guardian_statue.cpp \
    Backend/html_file.cpp \
    Backend/repository.cpp \
    Backend/tests.cpp \
    Backend/utils.cpp \
    admin_window.cpp \
    general_listview_model.cpp \
    main.cpp \
    mainwindow.cpp \
    mylist_widget.cpp \
    user_window.cpp

HEADERS += \
    Backend/action.h \
    Backend/controller.h \
    Backend/csv_file.h \
    Backend/exceptions.h \
    Backend/file_repository.h \
    Backend/guardian_statue.h \
    Backend/html_file.h \
    Backend/repository.h \
    Backend/tests.h \
    Backend/utils.h \
    Backend/validators.h \
    admin_window.h \
    general_listview_model.h \
    mainwindow.h \
    mylist_widget.h \
    user_window.h

FORMS += \
    admin_window.ui \
    mainwindow.ui \
    mylist_widget.ui \
    user_window.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    config.txt \
    csv_file1.csv \
    csv_file2.csv \
    html_file1.html \
    html_file2.html
