CC=g++
CFLAGS = -g -Wall
GPATH = ./src/graph
SPATH = ./src
OPATH = ./objectFiles

all: app

app: app.cpp minimumFeedbackVertexSet.o fullComponents.o  minimalSeparator.o graph.o
	$(CC) $(CFLAGS) app.cpp $(OPATH)/minimumFeedbackVertexSet.o $(OPATH)/fullComponents.o $(OPATH)/minimalSeparator.o  $(OPATH)/graph.o -o app

minimumFeedbackVertexSet.o: $(SPATH)/minimumFeedbackVertexSet.cpp $(SPATH)/minimumFeedbackVertexSet.h
	$(CC) $(CFLAGS) -c $(SPATH)/minimumFeedbackVertexSet.cpp -o $(OPATH)/minimumFeedbackVertexSet.o

fullComponents.o: $(SPATH)/fullComponents.cpp $(SPATH)/fullComponents.h
	$(CC) $(CFLAGS) -c $(SPATH)/fullComponents.cpp -o $(OPATH)/fullComponents.o
	
minimalSeparator.o: $(SPATH)/minimalSeparator.cpp $(SPATH)/minimalSeparator.h
	$(CC) $(CFLAGS) -c $(SPATH)/minimalSeparator.cpp -o $(OPATH)/minimalSeparator.o

graph.o: $(GPATH)/graph.cpp $(GPATH)/graph.h
	$(CC) $(CFLAGS) -c $(GPATH)/graph.cpp -o $(OPATH)/graph.o

clean:
	rm $(OPATH)/*.o app