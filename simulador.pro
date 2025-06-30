QT += core widgets multimedia multimediawidgets

CONFIG += c++17

TARGET = simulador
TEMPLATE = app

# Definir directorios
INCLUDEPATH += includes

# Archivos fuente de la aplicación principal
SOURCES += \
    src/simulador/main.cpp \
    src/simulador/mainwindow.cpp

# Archivos header de la aplicación principal
HEADERS += \
    src/simulador/mainwindow.h

# Archivos UI
FORMS += \
    src/simulador/mainwindow.ui

# Archivos fuente de la biblioteca pubsub_core
SOURCES += \
    src/Broker.cpp \
    src/Component.cpp \
    src/Follower.cpp \
    src/Publisher.cpp \
    src/Recorder.cpp \
    src/VideoPublisher.cpp \
    src/VideoFollower.cpp

# Archivos header de la biblioteca pubsub_core
HEADERS += \
    includes/Broker.h \
    includes/Component.h \
    includes/Follower.h \
    includes/Publisher.h \
    includes/Recorder.h \
    includes/Subscriber.h \
    includes/VideoFollower.h \
    includes/VideoPublisher.h

# Configuración específica para macOS
macx {
    CONFIG += app_bundle
    QMAKE_INFO_PLIST = Info.plist
}

# Configuración de salida
DESTDIR = build
OBJECTS_DIR = build/obj
MOC_DIR = build/moc
UI_DIR = build/ui
RCC_DIR = build/rcc

# Configuración de depuración y release
CONFIG(debug, debug|release) {
    TARGET = $${TARGET}_debug
}
