prim : main.o scanner.o array.o vertex.o binheap.o dll.o
	gcc main.o scanner.o array.o vertex.o binheap.o dll.o -o prim -lm
main.o : main.c scanner.h array.h vertex.h binheap.h dll.h node.h
	gcc -Wall -g -std=c99 -Wextra -c main.c scanner.h array.h vertex.h binheap.h dll.h node.h
scanner.o: scanner.c scanner.h
	gcc -Wall -g -std=c99 -Wextra -c scanner.c 
array.o: array.c array.h
	gcc -Wall -g -std=c99 -Wextra -c array.c 
vertex.o: vertex.c vertex.h
	gcc -Wall -g -std=c99 -Wextra -c vertex.c
binheap.o: binheap.c binheap.h
	gcc -Wall -g -std=c99 -Wextra -c binheap.c
dll.o: dll.c dll.h
	gcc -Wall -g -std=c99 -Wextra -c dll.c
clean:
	rm *.o *.h.gch prim
tester: test1 test2 test3 test4 test5 test6 test7 test8 test9 test10 test11 test12 test13 test14 test15 test16 test17
test1:
	./prim
test2:
	./prim empty.txt
test3:
	./prim simpleGraph.txt
test4:
	./prim bigGraph.txt
test5:
	./prim bigGraph2.txt
test6:
	./prim graph23f.txt
test7:
	./prim graphe.txt
test8:
	./prim graph1.txt
test9:
	./prim graph2.txt
test10:
	./prim graph3.txt
test11:
	./prim graph4.txt
test12:
	./prim graph5.txt
test13:
	./prim graph6.txt
test14:
	./prim graph7.txt
test15:
	./prim graph8.txt
test16:
	./prim graph9.txt
test17:
	./prim graph10.txt