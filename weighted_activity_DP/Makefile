all: gwas

dpwas: weighted_activity_DP.cpp
	g++ dpwas.o -o dpwas

dpwas.o: weighted_activity_DP.cpp
	g++ -g -c weighted_activity_DP.cpp

gwas: greedy.o
	g++ greedy.o -o gwas

greedy.o: greedy.cpp
	g++ -g -c greedy.cpp

g1:
	./gwas greedy1.txt greedy_out.txt
g2:
	./gwas greedy2.txt greedy_out.txt

d1:
	./weighted_activity_DP input.txt output.txt

c:
	-rm -f *.o gwas dpwas