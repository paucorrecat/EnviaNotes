#-------------------------------------------------
#
# Project created by QtCreator 2014-10-30T22:48:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EnviaNotes
TEMPLATE = app

SOURCES += \
    EnviaNotes.cpp \
    sendemail.cpp

# Location of SMTP Library
SMTP_LIBRARY_LOCATION = $$PWD/SmtpClient/release/lib

win32:CONFIG(release, debug|release): LIBS += -L$$SMTP_LIBRARY_LOCATION/release/ -lSMTPMime2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$SMTP_LIBRARY_LOCATION/debug/ -lSMTPMime2
else:unix: LIBS += -L$$SMTP_LIBRARY_LOCATION -lSmtpMime

INCLUDEPATH += $$SMTP_LIBRARY_LOCATION/../include/smtpmime
DEPENDPATH += $$SMTP_LIBRARY_LOCATION

HEADERS += \
    sendemail.h

FORMS += \
    sendemail.ui
