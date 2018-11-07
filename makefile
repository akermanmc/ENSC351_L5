CC=g++
CFLAGS= -fopenmp -lpthread

%.o: %.c
	$(CC) -c -o $@ $^ $(CFLAGS)

output: backtrackingSAT.o 
	$(CC) -o $@ $^ $(CFLAGS)
	
clean: 
	rm *.o
	rm output