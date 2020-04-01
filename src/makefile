all:
	make sam-ael
	make host

sam-ael: sam-ael.c
	gcc -ldl sam-ael.c -o sam-ael

host: host.c
	gcc host.c -o host

clean:
	rm sam-ael host
