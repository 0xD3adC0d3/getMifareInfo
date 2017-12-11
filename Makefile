getMifareInfo : main.o
	rm -fr ./bin
	mkdir ./bin
	gcc main.c -o ./bin/getMifareInfo -lnfc -lfreefare -g
	rm -f *.o
