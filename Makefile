all:
	make -C ./client/
	make -C ./server/
	mv ./client/client ./cli
	mv ./server/server ./ser
