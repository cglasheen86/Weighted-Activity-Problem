all: gwas dpwas

dpwas: weighted_activity_DP.cpp
	g++ dpwas.o -o dpwas

dpwas.o: weighted_activity_DP.cpp
	g++ -g -c weighted_activity_DP.cpp

gwas: greedy.o
	g++ greedy.o -o gwas

greedy.o: greedy.cpp
	g++ -g -c greedy.cpp

gt:
	./gwas greedy1.txt

dt:
	./weighted_activity_DP input.txt output.txt

c:
	-rm -f *.o gwas dpwas