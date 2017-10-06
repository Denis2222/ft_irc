all: server client

server:
	make -C ./ser/
	cp ./ser/server ./server

client:
	make -C ./cli/
	cp ./cli/client ./client

re: clean all

clean:
	make -C ./cli clean
	make -C ./ser clean
	rm -f ./client
	rm -f ./server

fclean: clean
	make -C ./cli fclean
	make -C ./ser fclean
	rm -f ./client
	rm -f ./server
