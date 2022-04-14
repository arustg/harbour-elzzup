TARGET = harbour-elzzup

CONFIG += sailfishapp

DEFINES += APP_VERSION=\\\"$$VERSION\\\"

SOURCES += \
    src/helpers/appeventhandler.cpp \
    src/helpers/appsettings.cpp \
    src/helpers/util.cpp \
    src/main.cpp \
    src/puzzle/creation/imageprocessor.cpp \
    src/puzzle/creation/shapeprocessor.cpp \
    src/puzzle/puzzlegame.cpp \
    src/puzzle/puzzlepiece.cpp \
    src/puzzle/puzzlepieceprimitive.cpp \
    src/puzzleboarditem.cpp

HEADERS += \
    src/helpers/appeventhandler.h \
    src/helpers/appsettings.h \
    src/helpers/util.h \
    src/puzzle/creation/helpertypes.h \
    src/puzzle/creation/imageprocessor.h \
    src/puzzle/creation/shapeprocessor.h \
    src/puzzle/puzzlegame.h \
    src/puzzle/puzzlepiece.h \
    src/puzzle/puzzlepieceprimitive.h \
    src/puzzleboarditem.h

DISTFILES += \
    images/add.png \
    qml/FirstPage_old.qml \
    qml/GamePage.qml \
    qml/cover/CoverPage.qml \
    rpm/harbour-elzzup.changes.in \
    rpm/harbour-elzzup.changes.run.in \
    rpm/harbour-elzzup.spec \
    rpm/harbour-elzzup.yaml \
    translations/*.ts \
    harbour-elzzup.desktop

INSTALLS += images
    images.files = images
    images.path = /usr/share/$${TARGET}

SAILFISHAPP_ICONS = 86x86 108x108 128x128 172x172 256x256

CONFIG += sailfishapp_i18n

TRANSLATIONS += translations/harbour-elzzup-de.ts

