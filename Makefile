all: ser cli

ser:
	make -C ./server/
	mv ./server/server ./ser

cli:
	make -C ./client/
	mv ./client/client ./cli

re: fclean all

clean:
	make -C ./client clean
	make -C ./server clean

fclean: clean
	make -C ./client fclean
	make -C ./server fclean
	rm -f ./cli
	rm -f ./ser
