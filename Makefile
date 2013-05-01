CXX_FLAGS := -O2 -DNDEBUG -Wall -g -march=core2 -std=c++11
CXX       := g++
VPATH	:= dispatcher gui
INSTALL_DIR := ./
export CXX
export CXX_FLAGS

all: qtbc-gui qtbc

qtbc-gui: qttest.pro mainwindow.ui
	qmake gui/qttest.pro -o gui/Makefile
	$(MAKE) -C gui
	mv gui/$@ ${INSTALL_DIR}

.PHONY : qtbc
qtbc:
	$(MAKE) -C dispatcher
	cp dispatcher/$@ ${INSTALL_DIR}

clean:
	-$(MAKE) clean -C gui
	-$(MAKE) clean -C dispatcher

