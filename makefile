CC=g++
CXXFLAGS= -fopenmp -lpthread

%.o: %.c
	$(CC) -c -o $@ $^ $(CXXFLAGS)

output: backtrackingSAT.o 
	$(CC) -o $@ $^ $(CXXFLAGS)
	
clean: 
	rm *.o
	rm output