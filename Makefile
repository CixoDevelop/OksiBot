API_BIN=ToInstall/OksiServer
API_SRC=OksiSource/Server.cpp
SERVICE=ToInstall/OksiServer.service

INSTALL_DIR=/opt/Oksi/
INSTALL_BIN=/opt/Oksi/OksiServer
INSTALL_SERVICE=/etc/systemd/system/OksiServer.service

all: clear build

.PHONY: clear

clear:
	rm $(API_BIN) -f

build:
	g++ -std=c++11 $(API_SRC) -o $(API_BIN) -lpigpio -lpthread  -I.

install:
	mkdir $(INSTALL_DIR)
	cp $(API_BIN) $(INSTALL_BIN)
	cp $(SERVICE) $(INSTALL_SERVICE)
	systemctl enable --now OksiServer
	
uninstall:
	systemctl disable --now OksiServer
	rm $(INSTALL_SERVICE)
	rm $(INSTALL_BIN)
	rmdir $(INSTALL_DIR)
run:
	./$(API_BIN)
