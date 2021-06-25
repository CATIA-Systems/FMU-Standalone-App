QT += widgets

HEADERS = \
    FMU.h \
    MainWindow.h \
    Simulator.h

SOURCES = \
    FMU.cpp \
    main.cpp \
    MainWindow.cpp \
    Simulator.cpp

RESOURCES = resources.qrc

FORMS = MainWindow.ui

INCLUDEPATH += ../include

unix:LIBS += -ldl

# install
# target.path = $$[QT_INSTALL_EXAMPLES]/widgets/widgets/calculator
# INSTALLS += target
