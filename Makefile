all: shortcut server client

server:
	make -C ./ser/
	cp ./ser/server ./server

client:
	make -C ./cli/
	cp ./cli/client ./client

re: clean all

shortcut:
	rm -f ./client
	rm -f ./server

clean: shortcut
	make -C ./cli clean
	make -C ./ser clean

fclean: clean
	make -C ./cli fclean
	make -C ./ser fclean
	rm -f ./client
	rm -f ./server
