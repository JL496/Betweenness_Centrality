CC = gcc
FFLAGS = -Wall -std=c99 -Xpreprocessor - fopenmp
LFLAGS = -lgomp

OBJECTS = main.o \
subreddits.o \
dijkstra.o \
minheap.o \
graph.o \
radixsort.o

main.exe: $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o main.exe -lm

%.o: %.c
	$(CC) $(FFLAGS) -c $<

clean:
	rm -f $(OBJECTS) main.exe