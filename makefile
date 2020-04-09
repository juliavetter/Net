all: net

net: mylib.o net.o grid.o node.o
	gcc -Wall -g -o net mylib.o net.o grid.o node.o
net.o: net.c net.h mylib.h
	gcc -Wall -g -c net.c
mylib.o: mylib.c mylib.h
	gcc -Wall -g -c mylib.c
grid.o: grid.c net.h mylib.h
	gcc -Wall -g -c grid.c
node.o: node.c net.h mylib.h
	gcc -Wall -g -c node.c

clean:
	rm *.o net
