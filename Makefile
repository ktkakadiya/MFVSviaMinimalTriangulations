CC=g++
CFLAGS = -g -Wall
GPATH = ./src/graph
SPATH = ./src
OPATH = ./objectFiles

all: app

app: app.cpp minimumFeedbackVertexSet.o potentialMaximalClique.o fullComponents.o  minimalSeparator.o graph.o setOperations.o
	$(CC) $(CFLAGS) app.cpp $(OPATH)/minimumFeedbackVertexSet.o $(OPATH)/potentialMaximalClique.o $(OPATH)/fullComponents.o $(OPATH)/minimalSeparator.o  $(OPATH)/graph.o $(OPATH)/setOperations.o -o app

minimumFeedbackVertexSet.o: $(SPATH)/minimumFeedbackVertexSet.cpp $(SPATH)/minimumFeedbackVertexSet.h
	$(CC) $(CFLAGS) -c $(SPATH)/minimumFeedbackVertexSet.cpp -o $(OPATH)/minimumFeedbackVertexSet.o

potentialMaximalClique.o: $(SPATH)/potentialMaximalClique.cpp $(SPATH)/potentialMaximalClique.h
	$(CC) $(CFLAGS) -c $(SPATH)/potentialMaximalClique.cpp -o $(OPATH)/potentialMaximalClique.o

fullComponents.o: $(SPATH)/fullComponents.cpp $(SPATH)/fullComponents.h
	$(CC) $(CFLAGS) -c $(SPATH)/fullComponents.cpp -o $(OPATH)/fullComponents.o
	
minimalSeparator.o: $(SPATH)/minimalSeparator.cpp $(SPATH)/minimalSeparator.h
	$(CC) $(CFLAGS) -c $(SPATH)/minimalSeparator.cpp -o $(OPATH)/minimalSeparator.o

graph.o: $(GPATH)/graph.cpp $(GPATH)/graph.h
	$(CC) $(CFLAGS) -c $(GPATH)/graph.cpp -o $(OPATH)/graph.o

setOperations.o: $(SPATH)/setOperations.cpp $(SPATH)/setOperations.h
	$(CC) $(CFLAGS) -c $(SPATH)/setOperations.cpp -o $(OPATH)/setOperations.o
	
clean:
	rm $(OPATH)/*.o app