QT += core
QT += widgets

CONFIG += c++17

#greaterThan(QT_MAJOR_VERSION,5): QT += core5compat


#CONFIG += force_debug_info
#CONFIG += debug_info

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    ChartForm.cpp \
    ChartFormGraphicsPlotItem.cpp \
    ChartFormScaleWidget.cpp \
    ChartFormScene.cpp \
    ChartFormScrollBar.cpp \
    ChartFormSource.cpp \
    Errors.cpp \
    MainScaleRepository.cpp \
    UnitsRepository.cpp \
    main.cpp \
    mainwindow.cpp
    main.cpp


HEADERS += \
    ChartForm.h \
    ChartFormGraphicsPlotItem.h \
    ChartFormScaleWidget.h \
    ChartFormScene.h \
    ChartFormScrollBar.h \
    ChartFormSource.h \
    MainScaleRepository.h \
    UnitsRepository.h \
    mainwindow.h

INCLUDEPATH += ../

INCLUDEPATH += $$PWD/hwFace


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES +=
