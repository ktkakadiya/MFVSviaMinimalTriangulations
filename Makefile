CC=g++
CFLAGS = -g -Wall
GPATH = ./src/graph
OPATH = ./objectFiles

all: app

app: app.cpp graph.o graphNode.o
	$(CC) $(CFLAGS) app.cpp $(OPATH)/graph.o $(OPATH)/graphNode.o -o app

graph.o: $(GPATH)/graph.cpp $(GPATH)/graph.h
	$(CC) $(CFLAGS) -c $(GPATH)/graph.cpp -o $(OPATH)/graph.o

graphNode.o: $(GPATH)/graphNode.cpp $(GPATH)/graphNode.h
	$(CC) $(CFLAGS) -c $(GPATH)/graphNode.cpp -o $(OPATH)/graphNode.o

clean:
	rm $(OPATH)/*.o app