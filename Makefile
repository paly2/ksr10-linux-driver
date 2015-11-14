EXEC=ksr10
CC=g++
CFLAGS=-lusb-1.0
all:
	$(CC) *.cpp -o $(EXEC) $(CFLAGS) 
clean:
	rm $(EXEC) 
