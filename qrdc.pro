VERSION = 0.0.1
TARGET = qrdc
TEMPLATE = app
QT = gui core sql
CONFIG += qt \
 warn_on \
 console \
 debug_and_release \
 build_all
DESTDIR = bin
OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build
FORMS = ui/mainwindow.ui \
 ui/protocol.ui \
 ui/var.ui \
 ui/host.ui \
 ui/connection.ui \
 ui/settings.ui
HEADERS = src/mainwindowimpl.h \
 src/protocolimpl.h \
 src/hostimpl.h \
 src/dialogimpl.h \
 src/varimpl.h \
 src/connectionimpl.h \
 src/settingsimpl.h
SOURCES = src/mainwindowimpl.cpp \
 src/main.cpp \
 src/protocolimpl.cpp \
 src/hostimpl.cpp \
 src/dialogimpl.cpp \
 src/varimpl.cpp \
 src/connectionimpl.cpp \
 src/settingsimpl.cpp \
 src/impex.cpp
TRANSLATIONS += i18n/qrdc_ru.ts
RESOURCES += qrdc.qrc
target.path = /usr/bin
translations.path = $$[QT_INSTALL_TRANSLATIONS]
translations.files = i18n/*.qm
desktop.path = /usr/share/applications
desktop.files = contrib/qrdc.desktop
icon.path = /usr/share/pixmaps
icon.files = contrib/qrdc.png
isEmpty(QMAKE_LRELEASE) {
 win32 {
  QMAKE_LRELEASE =   $$[QT_INSTALL_BINS]\\lrelease.exe
}
else:QMAKE_LRELEASE =  $$[QT_INSTALL_BINS]/lrelease-qt4
}
isEmpty(TS_DIR) {
 TS_DIR =  i18n
}
;TSQM.name = $$QMAKE_LRELEASE
;TSQM.input = TRANSLATIONS
;TSQM.output = $$TS_DIR/${QMAKE_FILE_BASE}.qm
;TSQM.commands = $$QMAKE_LRELEASE
;TSQM.CONFIG = no_link
;QMAKE_EXTRA_COMPILERS += TSQM
;PRE_TARGETDEPS += compiler_TSQM_make_all
INSTALLS += target translations desktop icon
