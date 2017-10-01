all: ser cli

ser:
	make -C ./server/
	mv ./server/server ./ser

cli:
	make -C ./client/
	mv ./client/client ./cli

re: clean all

clean:
	make -C ./client clean
	make -C ./server clean
	rm -f ./cli
	rm -f ./ser

fclean: clean
	make -C ./client fclean
	make -C ./server fclean
	rm -f ./cli
	rm -f ./ser
