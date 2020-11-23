pagerank : pagerank.o Graph.o
	gcc -o pagerank pagerank.o Graph.o

Graph.o : Graph.h Graph.c
	gcc -c Graph.c Graph.h

pagerank.o : pagerank.c
	gcc -c pagerank.c



