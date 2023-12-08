CC = gcc
CFLAGS = -Wall -ansi -pedantic
OBJ = game.o gamePrint.o gameMove.o random.o terminal.o
EXEC = traffic

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

game.o: game.c gamePrint.h random.h
	$(CC) $(CFLAGS) -c game.c

gamePrint.o: gamePrint.c gamePrint.h gameMove.h
	$(CC) $(CFLAGS) -c gamePrint.c

gameMove.o: gameMove.c gameMove.h gamePrint.h terminal.h
	$(CC) $(CFLAGS) -c gameMove.c

random.o: random.c random.h
	$(CC) $(CFLAGS) -c random.c

terminal.o: terminal.c terminal.h
	$(CC) $(CFLAGS) -c terminal.c

clean:
	rm -f $(EXEC) $(OBJ)
