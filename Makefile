############################# Makefile ##########################
.:mrproper teste.o server client clean
run-server: all 
		./servidor 7777
run-client: all 
		./client
all: mrproper teste.o server client clean
server: socket-server.o utils.o stack.o server.o
		gcc -pthread -o servidor teste.o socket-server.o utils.o stack.o server.o
client: socket-client.o utils.o stack.o  client.o
		gcc -o cliente teste.o socket-client.o utils.o stack.o client.o
teste.o: teste.c
		gcc -o teste.o -c teste.c -W -Wall -ansi -pedantic
socket-server.o: server/socket-server.c
		gcc -o socket-server.o -c server/socket-server.c -W -Wall -ansi -pedantic
server.o: server/server.c teste.h
		gcc -o server.o -c server/server.c -W -Wall -ansi -pedantic
socket-client.o: client/socket-client.c
		gcc -o socket-client.o -c client/socket-client.c -W -Wall -ansi -pedantic
client.o: client/client.c teste.h
		gcc -o client.o -c client/client.c -W -Wall -ansi -pedantic
utils.o: utils.c
		gcc -o utils.o -c utils.c -W -Wall -ansi -pedantic
stack.o: stack.c
		gcc -o stack.o -c stack.c -W -Wall -ansi -pedantic
clean:
		rm -rf *.o
mrproper:
		rm -rf servidor cliente