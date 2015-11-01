TEMPLATE = app

QT += qml quick sql
CONFIG += c++11
CONFIG+=qml_debug

SOURCES += main.cpp \
    npsmodel.cpp \
    portfolio.cpp \
    scheme.cpp \
    transaction.cpp \
    xirrtransaction.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    npsmodel.h \
    portfolio.h \
    scheme.h \
    transaction.h \
    xirrtransaction.h

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

contains(ANDROID_TARGET_ARCH,x86) {
    ANDROID_EXTRA_LIBS = \
        $$PWD/../../../Qt5.5.1/5.5/android_x86/plugins/sqldrivers/libqsqlite.so
}

