QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    autor.cpp \
    ayuda.cpp \
    copiarmatrices.cpp \
    direccion.cpp \
    graficarfuncion.cpp \
    main.cpp \
    mainwindow.cpp \
    operaciones.cpp \
    pye.cpp \
    resultado.cpp

HEADERS += \
    autor.h \
    ayuda.h \
    copiarmatrices.h \
    direccion.h \
    graficarfuncion.h \
    mainwindow.h \
    operaciones.h \
    pye.h \
    resultado.h

FORMS += \
    autor.ui \
    ayuda.ui \
    copiarmatrices.ui \
    direccion.ui \
    graficarfuncion.ui \
    mainwindow.ui \
    operaciones.ui \
    pye.ui \
    resultado.ui

TRANSLATIONS += \
    main_es_MX.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    iconos.qrc

DISTFILES += \
    QtCharts/.cmake.conf \
    QtCharts/.tag \
    QtCharts/CMakeLists.txt \
    QtCharts/LICENSE.GPL3 \
    QtCharts/README \
    QtCharts/conanfile.py \
    QtCharts/configure.cmake \
    QtCharts/dependencies.yaml \
    QtCharts/qt_cmdline.cmake \
    QtCharts/sync.profile


CONFIG+="debug_and_release build_all"
CONFIG+=static
