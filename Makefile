CC=g++
CFLAGS = -g -Wall
GPATH = ./src/graph
SPATH = ./src
OPATH = ./objectFiles

all: app

app: app.cpp minimalSeparator.o graph.o
	$(CC) $(CFLAGS) app.cpp $(OPATH)/minimalSeparator.o  $(OPATH)/graph.o -o app

minimalSeparator.o: $(SPATH)/minimalSeparator.cpp $(SPATH)/minimalSeparator.h
	$(CC) $(CFLAGS) -c $(SPATH)/minimalSeparator.cpp -o $(OPATH)/minimalSeparator.o

graph.o: $(GPATH)/graph.cpp $(GPATH)/graph.h
	$(CC) $(CFLAGS) -c $(GPATH)/graph.cpp -o $(OPATH)/graph.o

clean:
	rm $(OPATH)/*.o app