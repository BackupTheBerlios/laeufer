TEMPLATE	= app
CONFIG		= qt warn_on release
HEADERS		= debugTreiberGUIimpl.h \
		  debug_driver.h
SOURCES		= debugTreiberGUIimpl.cc \
		  debug_driver.cc \
		  main.cc
INTERFACES	= debugTreiberGUI.ui
INCLUDEPATH +=../lib/
unix:LIBS += -L../lib/ -llaeufer
