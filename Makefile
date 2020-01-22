CC = g++
CFLAGS  = -g

all : network_opt_sparse network_opt_dense

network_opt_sparse: heapStruct.cc  main.cc  genRandGraph.cc  routing_algo.cc
	$(CC) $(CFLAGS) -D PRINTPATH -D SPARSE -o network_opt_sparse heapStruct.cc  main.cc  genRandGraph.cc  routing_algo.cc

network_opt_dense: heapStruct.cc  main.cc  genRandGraph.cc  routing_algo.cc
	$(CC) $(CFLAGS) -D PRINTPATH -o network_opt_dense heapStruct.cc  main.cc  genRandGraph.cc  routing_algo.cc

clean:
	rm -rf network_opt_dense network_opt_sparse

