all: dpwas

dpwas: weighted_activity_DP.o
	g++ weighted_activity_DP.o -o dpwas

weighted_activity_DP.o: weighted_activity_DP.cpp
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
	./dpwas input.txt output.txt
d2: 
	./dpwas outy.txt output1.txt
a:
	./activities_generator
c:
	-rm -f *.o gwas dpwas