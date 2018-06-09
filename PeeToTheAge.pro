QT += widgets network
requires(qtConfig(combobox))

HEADERS     = window.h
SOURCES     = main.cpp \
              window.cpp \
              HelloHandler.cpp

LIBS += -lpistache -lpthread

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/widgets/lineedits
INSTALLS += target
