QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QMAKE_CFLAGS_WARN_ON -= -Wextra
QMAKE_CXXFLAGS_WARN_ON -= -Wextra

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../src/QT_calc/Controller/controller.cpp \
    ../src/QT_calc/View/dialog_range.cpp \
    ../src/QT_calc/View/main.cpp \
    ../src/QT_calc/View/mainwindow.cpp \
    ../src/QT_calc/Model/model.cpp \
    ../src/QT_calc/View/plot.cpp \
    ../src/QT_calc/qcustomplot.cpp

HEADERS += \
    ../src/QT_calc/Controller/controller.h \
    ../src/QT_calc/View/dialog_range.h \
    ../src/QT_calc/View/mainwindow.h \
    ../src/QT_calc/Model/model.h \
    ../src/QT_calc/View/plot.h \
    ../src/QT_calc/qcustomplot.h

FORMS += \
    ../src/QT_calc/View/dialog_range.ui \
    ../src/QT_calc/View/mainwindow.ui \
    ../src/QT_calc/View/plot.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
